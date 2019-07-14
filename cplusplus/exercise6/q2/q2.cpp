#include <iostream>
#include <cstring>

using namespace std;
void selection_sort(char a[]);
int minimum_from(char a[], int position);
void swap(char& first, char& second);
const int MAXIMUM_LENGTH=80;

int main(){
  char str[MAXIMUM_LENGTH];
  cout << "Type in a string" << endl;
  cin.getline(str, MAXIMUM_LENGTH);
  selection_sort(str);
  cout << "Sorted string: ";
  cout << str << endl;
}

void selection_sort(char a[])
	{
	  int count=0;

	  while(a[count] != '\0'){
	    swap(a[count],a[minimum_from(a,count)]);
	    count++;
	  }
	}
	
int minimum_from(char a[], int position)
	{
		int count = position+1;
		int min_index=position;
		while(a[count]!='\0'){
		  if(a[count] < a[min_index]){
		    min_index=count;
		  }
		  count++;
		}
		return min_index;
	}

void swap(char& first, char& second)
	{
		int temp = first;
		first = second;
		second = temp;
	}
