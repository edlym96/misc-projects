#include <iostream>
#include <cctype>
#include <cstring>
#include "playfair.h"

void prepare(const char input[], char output[]){
  int count = 0;
  for(int i=0; i< strlen(input); ++i){
    if(isalnum(input[i])){
      output[count] = toupper(input[i]);
      ++count;
    }
  }
  if(count % 2){
    output[count] = 'X';
  }
  output[count+1] = '\0';
}

void grid(const char codeword[], char square[6][6]){
  char fill[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int count = 0;
  int track = 0;
  for(int i=0; i<6; ++i){
    for(int j=0; j<6; ++j){
      while(count < strlen(codeword) && occurs_before(codeword, codeword[count], count)){
	++count;
      }
      while(count >= strlen(codeword) && occurs_before(codeword, fill[track], strlen(codeword))){
	++track;
      }
      if(count < strlen(codeword)){
	square[i][j]=codeword[count];
	++count;
      }else{
	square[i][j] = fill[track];
	++track;
      }
    }
  }
}

bool occurs_before(const char str[], char letter, int pos){
  for(int i=0; i<pos; ++i){
    if(str[i] == letter){
      return true;
    }
  }
  return false;
}
  
void bigram(char square[6][6], const char inchar1, const char inchar2, char &outchar1, char &outchar2){
  int row1, row2, col1, col2;
  row1 = get_row(square, inchar1);
  col1 = get_col(square, inchar2);
  row2 = get_row(square, inchar2);
  col2 = get_col(square, inchar1);
  //  std::cout << row1 << col1 << " " << row2 << col2 << std::endl;
  outchar1 = square[row1][col1];
  outchar2 = square[row2][col2];
}

int get_row(char square[6][6], char inchar){
  for(int i=0; i<6; ++i){
    for(int j=0; j<6; ++j){
      if(square[i][j] == inchar){
	return i;
      }
    }
  }
  return -1;
}

int get_col(char square[6][6], char inchar){
  for(int i=0; i<6; ++i){
    for(int j=0; j<6; ++j){
      if(square[i][j] == inchar){
	return j;
      }
    }
  }
  return -1;
}

void encode(char square [6][6], const char* prepared, char* encoded){

  if(*(prepared) != '\0'){
    bigram(square, *prepared, *(prepared+1), *encoded, *(encoded+1));
    encode(square, prepared+2, encoded+2);
  }else{
    return;
  }
}

void decode(char square[6][6], const char encoded[], char decoded[]){
  
}
