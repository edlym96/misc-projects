#include <iostream>
#include "conversions.h"

using namespace std;
  void print_preliminary_message();
  void input_table_specifications(int& lowest_entry,int& highest_entry,int& step_entry);

  void print_message_echoing_input(int lowest_entry, int highest_entry, int step_entry);
  void print_table(int lowest_entry, int highest_entry, int step_entry);

int main(){
  int lower = 0;
  int upper = 0;
  int step = 1;
  
  print_preliminary_message();

  input_table_specifications(lower,upper,step);

  print_message_echoing_input(lower,upper,step);

  print_table(lower, upper, step);

  return 0;

}

void print_preliminary_message(){
  cout << "This program will output a table of temperatures in fahrenheit, celsius and kelvin"<< endl;
}

void input_table_specifications(int& lowest_entry, int& highest_entry, int& step_entry){
  cout << "Please input the lowest entry of the table";
  cin >> lowest_entry;
  cout << "Please input the highest entry of the table";
  cin >> highest_entry;
  cout << "Please input the step size of the table";
  cin >> step_entry;
}

void print_message_echoing_input(int lowest_entry, int highest_entry, int step_entry){
  cout << "Your input for the lowest entry of the table is ";
  cout << lowest_entry << endl;
  cout << "Your input for the highest entry of the table is ";
  cout << highest_entry << endl;
  cout << "Your input for the step size of the table is ";
  cout << step_entry << endl;
}

void print_table(int lowest_entry, int highest_entry, int step_entry){
  cout.setf(ios::left|ios::fixed);
  cout.precision(2);

  cout.width(20);
  cout << "Fahrenheit";
  cout.width(20);
  cout << "Celsius";
  cout << "Kelvin" << endl;
  for(int i=lowest_entry;i<highest_entry+step_entry;i+=step_entry){
    if((i-highest_entry)<step_entry && (i-highest_entry)>0){
      i-=(i-highest_entry);
    }
    cout.width(20);
    cout << i;
    cout.width(20);
    cout << celsius_of(i);
    cout << absolute_value_of(i) << endl;
  }
}

