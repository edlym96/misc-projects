#include <iostream>
#include <cstring>
#include "IntegerArray.h"

using namespace std;

const int SIZE = 5;

int main(){
  int second_list[SIZE];
  int first_list[SIZE];

  cout << "Input Integers for first array: " << endl;
  input_array(first_list, SIZE);
  cout << "Input Integers for first array: " << endl;
  input_array(second_list, SIZE);

  display_array(first_list,SIZE);
  display_array(second_list,SIZE);

  copy_array(first_list, second_list, SIZE);
  cout << "first array after copy: "<< endl;
  display_array(first_list, SIZE);

  cout << average(first_list, SIZE) << endl;
  cout << standard_deviation(first_list, SIZE) << endl;
    
  return 0;
}
