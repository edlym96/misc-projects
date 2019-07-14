#include <iostream>
#include"IntegerArray.h"
#include <cmath>

using namespace std;

void input_array(int list[], int n){
  for(int i=0;i<n;++i){
    cout << "Please input the integer: ";
    cin >> list[i];
  }
}

void display_array(int list[], int n){
  cout.setf(ios::left);
  cout.width(15);
  cout << "index" << "element" << endl;
  for(int i=0;i<n;++i){
    cout.width(15);
    cout << i << list[i] << endl;
  }
}

void copy_array(int list1[], int list2[], int n){
  for(int i=0;i<n;++i){
    list1[i]=list2[i];
  }
}

float average(int list[], int n){
  float sum=0;
  for(int i=0;i<n;++i){
    sum+=float(list[i]);
  }
  return (sum/n);
}

float standard_deviation(int list[], int n){
  float sum=0;
  
  for(int i=0;i<n;i++){
    sum += pow(float(list[i])-average(list, n),2);
  }
  return sqrt(sum/n);
}
