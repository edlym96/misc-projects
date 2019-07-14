#include <iostream>
using namespace std;
#include "correct.h"
/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(const char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
void text_to_binary(const char* text, char* binary){
  if(*text == '\0'){
    return;
  }
  ascii_to_binary(*text, binary);
  text_to_binary(++text, binary+8);
}

void binary_to_text(const char* binary, char* text){
  if(*binary == '\0'){
    *text = '\0';
    return;
  }
  *text = binary_to_ascii(binary);
  binary_to_text(binary+8, ++text);
}

void add_error_correction(const char* data, char* corrected){
  int no_of_bytes=0;
  //make it handle longer than 4 bits
  while(data[4*no_of_bytes] != '\0'){
    int bit;
    for(int i=2; i>=0; --i){
      if(i == 0){
	*corrected = data[0];
	++corrected;
      }
      bit = 0;
      for(int j=0; j<4; ++j){
	if(j != i){
	  bit += data[4*no_of_bytes+j]-'0';
	}
      }
      if(bit%2 != 0){
	bit = 1;
      }else{
	bit = 0;
      }
      *corrected = bit+'0';
      ++corrected;
    }
    for(int i=1; i<4; ++i){
      *corrected = data[4*no_of_bytes+i];
      ++corrected;
    }
    ++no_of_bytes;
  }
  *corrected = '\0';
}

int decode(const char* received, char* decoded){
  int no_of_decoded = 0;
  int error_counter = 0;

  while(received[7*no_of_decoded] != '\0'){
    char temp[7];
    for(int i=0; i<7; ++i){
      temp[i] = received[7*no_of_decoded+i];
    }
    int value;
    do{
      //      std::cout << "im here" << std::endl;
      value = calculate_value(temp);
      flip(temp, value);
      if(value > 0){
	++error_counter;
      }
    }while(value > 0);
    
    for(int i=0; i<4; ++i){
      int add=0;
      if(i > 0){
	add = 1;
      }
      *decoded = temp[2+add+i];
      ++decoded;
    }
    ++no_of_decoded;
  }
  *decoded = '\0';
  return error_counter;
}

int binary_to_value(int bit1, int bit2, int bit3){
  if(bit1%2 == 0){
    bit1 = 0;
  }else{
    bit1 = 1;
  }
  if(bit2%2 == 0){
    bit2 = 0;
  }else{
    bit2 = 1;
  }
  if(bit3%2 == 0){
    bit3 = 0;
  }else{
    bit3 = 1;
  }
  return bit1*4+bit2*2+bit3;
}

int calculate_value(char encoded[7]){
  int bit1, bit2, bit3;
  bit1 = encoded[3]+encoded[4]+encoded[5]+encoded[6]-4*'0';
  bit2 = encoded[1]+encoded[2]+encoded[5]+encoded[6]-4*'0';
  bit3 = encoded[0]+encoded[2]+encoded[4]+encoded[6]-4*'0';
  //  std::cout << encoded[3] << encoded[4] << encoded[5] << encoded[6] << std::endl;
  return binary_to_value(bit1, bit2, bit3);
}

void flip(char encoded[7], int index){
  if(index > 7 || index < 1){
    return;
  }
  if(encoded[index-1] == '0'){
    encoded[index-1] = '1';
  }else if(encoded[index-1] == '1'){
    encoded[index-1] = '0';
  }else{
    return;
  }
}
