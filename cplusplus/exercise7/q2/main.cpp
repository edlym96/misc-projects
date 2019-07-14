#include <iostream>
#include <cstring>

using namespace std;

const int MAX_SIZE=800;

bool compare_string(char str_1[],char str_2[]);
bool compare_string_pointer(char *ptr_1, char *ptr_2);

int main(){
  char string_1[MAX_SIZE];
  char string_2[MAX_SIZE];
  char *pointer_1;
  char *pointer_2;

  cout << "Please input the first string without spaces or uppercase" << endl;
  cin.getline(string_1, MAX_SIZE);

  cout << "Please input the second string without spaces or uppercase" << endl;
  cin.getline(string_2, MAX_SIZE);

  pointer_1=string_1;
  pointer_2=string_2;
  
  if(compare_string_pointer(pointer_1,pointer_2)){
    cout << string_1 << " is alphabetically smaller than " << string_2 << "!" << endl;
  }else{
    cout << string_2 << " is alphabetically smaller than " << string_1 << "!" << endl;
  }

  return 0;
}

bool compare_string(char str_1[],char str_2[]){
  int count=0;
  while (str_1[count]!='\0'){
    if(str_1[count]<str_2[count]){
      return true;
    }else if(str_1[count]>str_2[count]){
      return false;
    }
    count++;
  }
  if (str_2[count]){
    return true;
  }else{
    return false;
  }
}

bool compare_string_pointer(char* ptr_1,char* ptr_2){
  while (*ptr_1!='\0'){
    if(*ptr_1<*ptr_2){
      return true;
    }else if(*ptr_1>*ptr_2){
      return false;
    }
    ptr_1++;
    ptr_2++;
  }
  if (*ptr_2){
    return true;
  }else{
    return false;
  }
}
