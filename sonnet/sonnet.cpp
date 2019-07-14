#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */
int count_words(const char* line){
  int count = 1;
  char word[512];
  while(get_word(line, count, word)){
    ++count;
  }
  return count-1;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending){
  ifstream in_stream;
  char line[512];
  char text [100];
  strcpy(phonetic_ending, "");
  in_stream.open("dictionary.txt");
  in_stream.getline(line, 512);
  while(!in_stream.eof()){
    if(get_word(line, 1, text) && !strcmp(text, word)){
      in_stream.close();
      int count;
      count = count_words(line);
      int vowel;
      vowel = find_vowel(line, count);
      for(int i=vowel; i<count+1; ++i){
	char temp[16];
	get_word(line, i, temp);
	strcat(phonetic_ending, temp);
      }
      return true;
    }
    in_stream.getline(line, 512);
  }
  in_stream.close();
  return false;
}

int find_vowel(const char* line, int length){
  for(int i=length; i>0; --i){
    char temp[16];
    get_word(line, i, temp);
    int counter = 0;
    while(temp[counter] != '\0'){
      if(temp[counter] == 'A' || temp[counter] == 'E' || temp[counter] == 'I' || temp[counter] == 'O' || temp[counter] == 'U'){
	return i;
      }
      ++counter;
    }
  }
  return -1;
}

bool find_rhyme_scheme(const char* filename, char* scheme){
 ifstream in_stream;
 char line[512];
 int counter=0;
 in_stream.open(filename);
 if(in_stream.fail()){
   return false;
 }
 in_stream.getline(line, 512);
 rhyming_letter(RESET);
 while(!in_stream.eof()){
   int count;
   char word[256];
   char phonetic[16];
   count = count_words(line);
   get_word(line, count, word);
   if(find_phonetic_ending(word, phonetic)){
     scheme[counter] = rhyming_letter(phonetic);
     ++counter;
   }
   in_stream.getline(line, 512);
 }
 scheme[counter] = '\0';
 return true;
}

const char* identify_sonnet(const char* filename){
  char scheme[156];
  if(find_rhyme_scheme(filename, scheme)){
    if(!strcmp(scheme, "ababcdcdefefgg")){
      return "Shakespearean";
    }else if(!strcmp(scheme, "abbaabbacdcdcd")){
      return "Petrarchan";
    }else if(!strcmp(scheme, "ababbcbccdcdee")){
      return "Spenserian";
    }
  }
  return "Unkown";
}
