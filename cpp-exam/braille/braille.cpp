#include <iostream>
#include <cctype>
#include <cstring>
#include "braille.h"

int encode_character(const char character, char braille[]){
  char suffix[7];
  if(isupper(character)){
    strcpy(braille, ".....0");
  }else if(isdigit(character)){
    strcpy(braille, "..0000");
  }else{
    strcpy(braille, "");
  }
  switch(tolower(character)){
  case 'a':
    strcpy(suffix, "0.....");
    break;
  case 'b':
    strcpy(suffix, "00....");
    break;
  case 'c':
    strcpy(suffix, "0..0..");
    break;
  case 'd':
    strcpy(suffix, "0..00.");
    break;
  case 'e':
    strcpy(suffix, "0...0.");
    break;
  case 'f':
    strcpy(suffix, "00.0..");
    break;
  case 'g':
    strcpy(suffix, "00.00.");
    break;
  case 'h':
    strcpy(suffix, "00..0.");
    break;
  case 'i':
    strcpy(suffix, ".0.0..");
    break;
  case 'j':
    strcpy(suffix, ".0.00.");
    break;
  case 'k':
    strcpy(suffix, "0.0...");
    break;
  case 'l':
    strcpy(suffix, "000...");
    break;
  case 'm':
    strcpy(suffix, "0.00..");
    break;
  case 'n':
    strcpy(suffix, "0.000.");
    break;
  case 'o':
    strcpy(suffix, "0.0.0.");
    break;
  case 'p':
    strcpy(suffix, "0000..");
    break;
  case 'q':
    strcpy(suffix, "00000.");
    break;
  case 'r':
    strcpy(suffix, "000.0.");
    break;
  case 's':
    strcpy(suffix, ".000..");
    break;
  case 't':
    strcpy(suffix, ".0000.");
    break;
  case 'u':
    strcpy(suffix, "0.0..0");
    break;
  case 'v':
    strcpy(suffix, "000..0");
    break;
  case 'w':
    strcpy(suffix, ".0.000");
    break;
  case 'x':
    strcpy(suffix, "0.00.0");
    break;
  case 'y':
    strcpy(suffix, "0.0000");
    break;
  case 'z':
    strcpy(suffix, "0.0.00");
    break;
  case '1':
    strcpy(suffix, "0.....");
    break;
  case '2':
    strcpy(suffix, "00....");
    break;
  case '3':
    strcpy(suffix, "0..0..");
    break;
  case '4':
    strcpy(suffix, "0..00.");
    break;
  case '5':
    strcpy(suffix, "0...0.");
    break;
  case '6':
    strcpy(suffix, "00.0..");
    break;
  case '7':
    strcpy(suffix, "00.00.");
    break;
  case '8':
    strcpy(suffix, "00..0.");
    break;
  case '9':
    strcpy(suffix, ".0.0..");
    break;
  case '0':
    strcpy(suffix, ".0.00.");
    break;
  case '.':
    strcpy(suffix, ".0..00");
    break;
  case ',':
    strcpy(suffix, ".0....");
    break;
  case ';':
    strcpy(suffix, ".00...");
    break;
  case '-':
    strcpy(suffix, "..0..0");
    break;
  case '!':
    strcpy(suffix, ".00.0.");
    break;
  case '?':
    strcpy(suffix, ".00..0");
    break;
  case '(':
    strcpy(suffix, ".00.00");
    break;
  case ')':
    strcpy(suffix, ".00.00");
    break;
  default:
    strcpy(suffix, "......");
    break;
  }
  strcat(braille, suffix);
  return strlen(braille);
}

void encode(const char* plaintext, char* braille){
  if(*plaintext == '\0'){
    return;
  }
  int length = encode_character(*plaintext, braille);
  encode(++plaintext, braille+length);
}

void print_braille(const char* plaintext, std::ostream& output){
  char braille[512];
  encode(plaintext, braille);
  for(int i=0; i<3; ++i){
    int counter = 0;
    int skip = 0;
    while(braille[counter] != '\0'){
      if(counter%3 == i){
	output << braille[counter];
	++skip;
	if(skip%2 == 0){
	  output << ' ';
	}
      }
      ++counter;
    }
    output << '\n';
  }
  int index = 0;
  while(plaintext[index] != '\0'){
    if(isupper(plaintext[index]) || isdigit(plaintext[index])){
      output << "   ";
    }
    output << plaintext[index] << "  ";
    ++index;
  }
}
