#include <iostream>
#include <string>
#include "print_pyramid.h"

using namespace std;

void print_pyramid(int height){
  for(int i=0; i< height;++i){
    cout << string(height-i-1,' ');
    cout << string((i+1)*2,'*') << endl;
  }
}
