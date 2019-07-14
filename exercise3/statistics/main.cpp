#include <iostream>
#include <cmath>
#include "statistics.h"

using namespace std;

void test_one_value();
void test_two_values();
void test_three_values();
void test_four_values();

int main(){
  int number_of_n;

  cout.setf(ios::fixed);
  cout.precision(4);
  
  cout << "Please input the number of values";
  cin >> number_of_n;

  
  while(number_of_n != 0){

    switch(number_of_n){
    case 1:test_one_value();
    case 2:test_two_values();
    case 3:test_three_values();
    case 4:test_four_values();
    }

    cout << "Please input the number of values";
    cin >> number_of_n;
  
  }
  return 0;
}

void test_one_value(){
  double n1,a1,a2;
  cout << "Please input the first value: ";
  cin >> n1;
  a1=average(n1);
  a2=standard_deviation(n1);
  cout << "The average is ";
  cout << a1 << endl;
  cout << "The sd is ";
  cout << a2 << endl;
} 

void test_two_values(){
  double n1,n2,a1,a2;
  cout << "Please input the first value: ";
  cin >> n1;
  cout << "Please input the second value: ";
  cin >> n2;
  a1=average(n1,n2);
  a2=standard_deviation(n1,n2);
  cout << "The average is ";
  cout << a1 << endl;
  cout << "The sd is ";
  cout << a2 << endl;
}

void test_three_values(){
  double n1,n2,n3,a1,a2;
  cout << "Please input the first value: ";
  cin >> n1;
  cout << "Please input the second value: ";
  cin >> n2;
  cout << "Please input the third value: ";
  cin >> n3;
  a1=average(n1,n2,n3);
  a2=standard_deviation(n1,n2,n3);
  cout << "The average is ";
  cout << a1 << endl;
  cout << "The sd is ";
  cout << a2 << endl;
}

void test_four_values(){
  double n1,n2,n3,n4,a1,a2;
  cout << "Please input the first value: ";
  cin >> n1;
  cout << "Please input the second value: ";
  cin >> n2;
  cout << "Please input the third value: ";
  cin >> n3;
  cout << "Please input the fourth value: ";
  cin >> n4;
  a1=average(n1,n2,n3,n4);
  a2=standard_deviation(n1,n2,n3,n4);
  cout << "The average is ";
  cout << a1 << endl;
  cout << "The sd is ";
  cout << a2 << endl;
} 
