#include <iostream>
#include <cctype>
#include <cstring>
#include "piglatin.h"
using namespace std;
int findFirstVowel(const char word[]){
  int index = 0;
  while(word[index] != '\0'){
    if(isalpha(word[index])){
      if(toupper(word[index]) == 'A' || toupper(word[index]) == 'E' || toupper(word[index]) == 'I' || toupper(word[index]) == 'O' || toupper(word[index]) == 'U'){
	return index;
      }
      if((index != 0 && index != (strlen(word)-1)) && word[index] == 'Y'){
	return index;
      }
    }
    ++index;
  }
  return -1;
}

void translateWord(const char english[], char piglatin[]){
  //std::cout << english << std::endl;
  int first_vowel = findFirstVowel(english);
  char add[5];
  strcpy(piglatin, english);
  if(isdigit(english[0]) || !isalnum(english[0])){
    return;
  }
  if(first_vowel == 0){
    strcpy(add, "way");
  }else if(first_vowel < 0){
    strcpy(add, "way");
  }else{
    swap(piglatin, first_vowel);
    strcpy(add, "ay");
  }
  strcat(piglatin, add);
  if(isupper(english[0])){
    piglatin[0]=toupper(piglatin[0]);
  }
}

void swap(char word[], int index){
  char temp[index];
  for(int i=0; i < index; ++i){
    temp[i] = word[i];
  }
  for(int i=index; i < strlen(word); ++i){
    word[i-index] = word[i];
  }
  for(int i=0; i < index; ++i){
    word[i+(strlen(word)-index)] = tolower(temp[i]);
  }
}

void translateStream(istream& inputStream, ostream& outputStream){
  char peek;
  char word[64];
  char answer[68];
  inputStream.get(peek);
  if(inputStream.eof()){
    return;
  }
  int pos = 0;
  if(isalnum(peek)){
    while(isalnum(peek)){
      word[pos] = peek;
      inputStream.get(peek);
      ++pos;
    }
    inputStream.putback(peek);
  }else{
    word[pos] = peek;
    ++pos;
  }
  word[pos] = '\0';
  translateWord(word, answer);
  int index = 0;
  while(answer[index] != '\0'){
    outputStream.put(answer[index]);
    ++index;
  }
  translateStream(inputStream, outputStream);
}
