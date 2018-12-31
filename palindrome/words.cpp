#include <iostream>
#include <cctype>
#include <cstring>
#include "words.h"

void reverse(const char str1[], char str2[]){
  int length = strlen(str1);
  for(int i = 0; i < length; ++i){
    str2[i] = str1[length-i-1];
  }
  str2[length] = '\0';
}

bool compare(const char str1[], const char str2[]){
  //  if(str1 == NULL || str2 == NULL) return false;
  int index1 = 0;
  int index2 = 0;
  while(!isalpha(str1[index1]) && str1[index1] != '\0'){
    ++index1;
  }
  while(!isalpha(str2[index2]) && str2[index2] != '\0'){
    ++index2;
  }
  //  std::cout << index1 << index2 << std::endl;
  //std::cout << str1[index1] << str2[index2] << std::endl;
  if(str1[index1] == '\0' && str2[index2] == '\0'){
    return true;
  }
  if(toupper(str1[index1]) == toupper(str2[index2])){
    char new_str1[strlen(str1)-index1];
    char new_str2[strlen(str2)-index2];
    for(int i=index1+1; i < strlen(str1); ++i){
      new_str1[i-(index1+1)] = str1[i];
    }
    new_str1[strlen(str1)-index1-1] = '\0';
    for(int i=index2+1; i < strlen(str2); ++i){
      new_str2[i-(index2+1)] = str2[i];
    }
    new_str2[strlen(str2)-index2-1] = '\0';
    //std::cout << new_str1 << " followed by " << new_str2 << std::endl;
    if(compare(new_str1, new_str2)){
      return true;
    }
  }
  return false;
}
