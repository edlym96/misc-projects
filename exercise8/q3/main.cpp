#include <iostream>

using namespace std;

int greatest_common_divisor(int m, int n){
  if(m==n){
    return m;
  }
  if(m < n-m){
    greatest_common_divisor(m,n-m);
  }else{
    greatest_common_divisor(n-m,m);
  }
}

int main(){
  int m, n;
  cout << "Input the first value: ";
  cin >> m;
  cout << "Input the second value(must be bigger than first value): ";
  cin >> n;

  cout << greatest_common_divisor(m,n) << endl;
  return 0;
}
