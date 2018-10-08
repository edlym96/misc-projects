#include <iostream>
#include <cmath>

using namespace std;

bool check_prime(int number);

int main(){
  
  int number=0;
  do{
    cout << "Please input a number between 1 and 1000";
    cin >> number;
  }while(number>1000 || number<0);
  
  if(check_prime(number)){
    cout << number << " is a prime number" << endl;
  }else{
    cout << number << " is not a prime number" << endl;
  }
  return 0;
}

bool check_prime(int number){
  bool is_prime=true;
  int root=0;

  root=sqrt(number);

  for(int i=2;i<=root;++i){
    if(number % i == 0){
      is_prime=false;
      return is_prime;
    }
  }
  return is_prime;
}
