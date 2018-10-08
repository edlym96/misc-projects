#include <iostream>
#include <fstream>

using namespace std;

int main(){
  ifstream input_stream;
  int count=0;
  char character;

  cout.setf(ios::left);
  cout.width(20);
  cout << "character" << "no. of appearances"<< endl;
  
  for(int i=97;i<=122;++i){
    input_stream.open("q5.cpp");
    input_stream >> character;
    while(!input_stream.fail()){
      // cout << static_cast<int>(character) <<endl;
      if(static_cast<int>(character) == i){
	count++;
      }
      input_stream >> character;
    }
    input_stream.close();
    cout.width(20);
    cout << static_cast<char>(i) << count << endl;
    count = 0;
  }
  return 0;
}
