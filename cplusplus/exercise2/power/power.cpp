#include <iostream>

using namespace std;

int main(){
  int answer;
  int x = 2;
  int n = 3;

  answer=x;
  
  for(int i=1;i<n;++i){
    answer*=x;
  }

  cout << answer << endl;
  return 0;
}
