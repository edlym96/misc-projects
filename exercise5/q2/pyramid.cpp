#include<iostream>
#include"print_pyramid.h"

using namespace std;

int main(){
  int height=0;

  do{
     cout << "Pick a height (between 1 and 30)";
     cin >> height;
  }while(height<1 || height>30);

  print_pyramid(height);
  return 0;
}
