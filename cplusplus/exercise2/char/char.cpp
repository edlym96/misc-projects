#include <iostream>

using namespace std;

int main(){
  char c;
  int c_dec;

  cout << "Please input character";
  cin >> c;
  
  c_dec=static_cast<int>(c);

  if(c_dec>96 && c_dec<123){
    c_dec-=32;
    cout << "The character in uppercase is ";
    cout << static_cast<char>(c_dec) << endl;
  }else if(c<91 && c>64){
    c_dec+=32;
    cout << "The character in lowercase is ";
    cout << static_cast<char>(c_dec) << endl;
  }else{
    cout << "This is not a character" << endl;
  }
  return 0;
}
