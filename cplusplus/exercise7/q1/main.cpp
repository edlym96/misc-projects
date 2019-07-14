#include <iostream>

using namespace std;
typedef int *IntPtrType;

int main(){
  IntPtrType ptr_a, ptr_b, *ptr_c;

  ptr_a = new int; //assign memory to ptr_a
  *ptr_a = 3; //Dereference ptr_a point to the value of integer 3
  ptr_b = ptr_a; //Set ptr b to point to a
  cout << *ptr_a << " " << *ptr_b << "\n"; //print the contents of the pointers

  ptr_b = new int;//assign new memory to pointer b
  *ptr_b = 9; //set the contents of pointer b to 9 with dereference
  cout << *ptr_a << " " << *ptr_b << "\n"; //print the contents of the pointers
  
  *ptr_b = *ptr_a; //change the contents of ptr b to the contents of ptr a
  cout << *ptr_a << " " << *ptr_b << "\n";//print the contents of the pointers

  delete ptr_a;//removes the bit of memory assigned for ptr_a  
  ptr_a = ptr_b; //assign ptr a to the same pointer as b, which is pointing to 3
  cout << *ptr_a << " " << *&*&*&*&*ptr_b << "\n";
  
  ptr_c = &ptr_a;//ptr_c is a pointer of a pointer. It is pointing to the address of pointer a, where pointer a is pointing to the same as pointer b which is the value of 3
  cout << *ptr_a << " " << **ptr_c << "\n";// double dereference of ptr c which is getting the content of pointer c which is the value of pointer b which is 3

  delete ptr_a; // clean pointer a. Since it is set to the same as pointer b, cleaning a will also clean pointer b.
  ptr_a = NULL; // set it ot null

  return 0;
}
