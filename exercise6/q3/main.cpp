#include <iostream>
#include <cstring>

using namespace std;

const int MAX_SIZE = 800;
void remove_duplicates(char a[], int position);

int main(){
  char str[MAX_SIZE];

  cout << "Input string: " << endl;
  cin.getline(str, MAX_SIZE);

  int count=0;
  while(str[count] !='\0'){
    remove_duplicates(str, count);
    cout << str[count] << str << endl;
    count ++;
  }
  cout << "string with removed duplicates is: " << endl;
  cout << str << endl;
  return 0;
}

void remove_duplicates(char a[], int position){
  int count=position+1;
  while(a[count]!='\0'){
    if(a[count] == a[position]){
      int remove_index=count;
      while(a[remove_index]!='\0'){
	a[remove_index]=a[remove_index+1];
	remove_index++;
      }
      count--;
    }
    count++;
  }
}
