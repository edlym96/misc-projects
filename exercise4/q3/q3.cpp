#include <iostream>
#include <fstream>
using namespace std;

int main(){
  ifstream in_stream;
  char character;
  int count=0;

  in_stream.open("q3.cpp");
  in_stream.get(character);
  
  while(!in_stream.eof()){
    count++;
    cout << character;
    in_stream.get(character);
  }
  in_stream.close();
  cout << count << endl;
  return 0;
}
