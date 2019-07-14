#include <iostream>

using namespace std;

const int MAX = 11;

void quick_sort(int list[MAX], int left, int right);

void swap(int &first, int &second);

void display(int a[], int length);

int binary_search(int target, int list[MAX], int left, int right);

int main(){
  int list[MAX];
  int count, target, left, right;

  for(count = 0; count < MAX; count ++){
    cout << "Enter value of element "<< count <<  ":";
    cin >> list[count];
  }

  cout << "\n\nBefore Quick Sort:\n\n";

  display(list, MAX);

  quick_sort(list,0,MAX-1);

  cout << "\n\nAfter Quick Sort:\n\n";

  display(list, MAX);

  cout << "Input number to search: " << endl;

  cin >> target;

  cout << "Input starting index to search from:" << endl;

  cin >> left;

  cout << "Input final index to search from: " << endl;

  cin >> right;

  cout << binary_search(target,list, left, right) << endl;

  return 0;
}

void quick_sort(int list[], int left, int right){
  int pivot, left_arrow, right_arrow;

  left_arrow = left;
  right_arrow = right;
  pivot = list[(left + right)/2];

  do{
    while(list[right_arrow]>pivot)
      right_arrow--;
    while(list[left_arrow]<pivot)
      left_arrow++;
    if(left_arrow <= right_arrow){
      swap(list[left_arrow], list[right_arrow]);
      left_arrow++;
      right_arrow--;
    }
  }
  while(right_arrow>=left_arrow);

  if(left<right_arrow)
    quick_sort(list, left, right_arrow);
  if(left_arrow < right)
    quick_sort(list, left_arrow, right);
}

void swap(int& first, int& second){
  int temp = first;
  first = second;
  second = temp;
}

void display(int a[], int length){
  for(int count=0; count < length; count++){
    cout << a[count] << " ";
  }
  cout << "\n\n";
}

int binary_search(int target, int list[MAX], int left, int right){
  int midpoint;
  midpoint = (left+right)/2;
  if(midpoint == left || midpoint == right){
    return -1;
  }
  if(list[midpoint]<target){
    binary_search(target, list, midpoint, right);
  }else if(list[midpoint]>target){
    binary_search(target, list, left, midpoint);
  }else if(list[midpoint] == target){
    return midpoint;
  }
}
