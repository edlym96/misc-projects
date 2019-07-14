#include <iostream>
#include <fstream>
using namespace std;

int get_total_characters();
char get_character(int index);

int main(){
  int total_characters=get_total_characters();

  while(total_characters >0){
    cout << get_character(total_characters);
    total_characters--;
  }
  return 0;
}

int get_total_characters(){
  ifstream in_stream;
  char character;
  int count=0;

  in_stream.open("q3.cpp");
  in_stream.get(character);
  
  while(!in_stream.eof()){
    count++;
    //cout << character;
    in_stream.get(character);
  }
  in_stream.close();
  return count;
}

char get_character(int index){
  ifstream in_stream;
  char character;

  in_stream.open("q3.cpp");
  in_stream.get(character);

  for(int i=0;i<index;i++){
    in_stream.get(character);
  }
  return character;
}
