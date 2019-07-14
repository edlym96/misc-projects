#include <iostream>
#include <math.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include "stamp.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
int leading_zeros(const char* digest){
  int leading_zeros = 0;
  bool is_counting = true;
  for(int i=0; i<strlen(digest); ++i){
    if(!isdigit(digest[i]) && (!islower(digest[i]) || digest[i] > 'f')){
      return -1;
    }
    if(is_counting){
      if(digest[i] == '0'){
	++leading_zeros;
      }else{
	is_counting = false;
      }
    }
  }
  return leading_zeros;
}

bool file_to_SHA1_digest(const char* filename, char* digest){
  char content[35000];
  int index = 0;
  ifstream in_stream;
  in_stream.open(filename);
  if(in_stream.fail()){
    return false;
  }
  in_stream.get(content[index]);
  while(!in_stream.eof()){
    ++index;
    in_stream.get(content[index]);
  }
  text_to_SHA1_digest(content, digest);
  return true;
}

bool make_header(const char* recipient, const char* filename, char* header){
  int counter = 0;
  int attempt_counter = 0;
  char digest[45];
  char header_digest[45];
  char counter_char[16];
  strcpy(header, recipient);
  strcat(header, ":\0");
  if(!file_to_SHA1_digest(filename, digest)){
    return false;
  }
  strcat(header, digest);
  strcat(header, ":\0");
  cout << header << endl;
  char temp[512];
  do{
    strcpy(temp, header);
    if(attempt_counter > 10000000) return false;
    itoa(counter, counter_char);
    strcat(temp, counter_char);
    text_to_SHA1_digest(temp, header_digest);
    ++counter;
    ++attempt_counter;
  }while(leading_zeros(header_digest) != 5);
  strcpy(header, temp);
  return true;
}

void itoa(int number, char* char_array){
  int digits = 0;
  int temp = number;
  do{
    temp /= 10;
    ++digits;
  }while(temp != 0);
  int i = 0;
  for(; i<digits; ++i){
    char_array[i] = (int)number/(int)pow(10, digits-i-1) + '0';
    number = number%(int)pow(10, digits-i-1);
  }
  char_array[i] = '\0';
}

MessageStatus check_header(const char* email_address, const char* header, const char* filename){
  char email[512];
  char message_digest[512];
  int count = 0;
  int email_length = 0;
  for(int i=0; i<strlen(header); ++i){
    if(header[i] == ':'){
      if(count == 0){
	email[i] = '\0';
      }else if(count == 1){
        message_digest[i-email_length-1] = '\0';
      }
      ++count;
    }
    if(count == 0){
      email[i] = header[i];
      ++email_length;
    }else if (count == 1){
      message_digest[i-email_length-1] = header[i];
    }
  }
  if(count != 2){
    return INVALID_HEADER;
  }
  if(strcmp(email_address, email)){
    return WRONG_RECIPIENT;
  }
  
  char test_digest[41];
  if(file_to_SHA1_digest(filename, test_digest)){
    if(strcmp(test_digest, message_digest)){
      return INVALID_MESSAGE_DIGEST;
    }
  }
  strcpy(test_digest, "");
  text_to_SHA1_digest(header, test_digest);
  if(leading_zeros(test_digest) != 5){
    return INVALID_HEADER_DIGEST;
  }
  return VALID_EMAIL;
}
