#include <iostream>

using namespace std;

int main(){
  int step,temp_fahrenheit;
  float temp_low,temp_high,temp_celsius,temp_kelvin;

  std::cout.precision(2);
  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::left);

  cout << "Please input the lowest fahrenheit temperature";
  cin >> temp_low;
  cout << "Please input the highest fahrenheit temperature";
  cin >> temp_high;
  cout << "Please input desired step size";
  cin >> step;

  cout.width(20);
  cout << "Fahrenheit";
  cout.width(20);
  cout << "Celsius";
  cout << "Kelvin" << endl;
  
  for(int i=temp_low;i<temp_high+step;i+=step){
    if((i-temp_high)<step && (i-temp_high)>0){
      i-=(i-temp_high);
    }
    temp_fahrenheit = i;
    temp_celsius = (static_cast<float>(temp_fahrenheit)-32)*5/9;
    temp_kelvin = temp_celsius+273.15;
    cout.width(20);
    cout << temp_fahrenheit;
    cout.width(20);
    cout << temp_celsius;
    cout << temp_kelvin << endl;
  }
  
  return 0;
}
  
  
