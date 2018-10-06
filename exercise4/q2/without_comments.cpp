#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ifstream in_stream;
  ofstream out_stream;
  char character;
  char next_character;
  bool in_comment = false;

  
  
  cout << "Testing: " << 16/2 << "=" << 4*2 <<".\n\n";

  in_stream.open("q2.cpp");
  out_stream.open("without_comments.cpp");
  
  in_stream.get(character);

  while(!in_stream.eof()){
    if(!in_comment && character=='/'){
      in_stream.get(next_character);
      if(next_character == '*'){
	in_comment=true;
      }else{
 	in_stream.putback(next_character);
      }
    }
    if(in_comment && character=='*'){
      in_stream.get(next_character);
      if(next_character == '/'){
	in_comment=false;
	in_stream.get(character);
      }
    }
    if(!in_comment){
      out_stream.put(character);
      cout << character;
    }
    in_stream.get(character);
  }
  in_stream.close();
  out_stream.close();
  return 0;
}
