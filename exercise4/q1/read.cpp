#include <iostream>
#include <fstream>

using namespace std;

int main(){
  ifstream in_stream;
  char character;
  
  in_stream.open("hello_world.cpp");
  in_stream.get(character);

  while(!in_stream.eof()){
    cout << character;
    in_stream.get(character);
  }

  in_stream.close();
  
  return 0;
}
