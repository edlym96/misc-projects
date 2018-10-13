#include <iostream>

using namespace std;

int fibonacci(int num);

int main(){
  int value;
  cout << "Enter fibonacci sequence index: " << endl;
  cin >> value;
  cout << fibonacci(value) << endl;
  return 0;
}

int fibonacci(int num){
  if(num<=2){
    return 1;
  }
  return fibonacci(num-1)+fibonacci(num-2);
}
