#include <iostream>


using namespace std;

int main(){
  int temp_fahrenheit;
  float temp_celsius,temp_kelvin;

  std::cout.precision(2);
  std::cout.setf(std::ios::fixed);
  
  for(int i=0;i<21;++i){
    temp_fahrenheit = i*20;
    temp_celsius = (static_cast<float>(temp_fahrenheit)-32)*5/9;
    temp_kelvin = temp_celsius+273.15;
    cout << temp_fahrenheit << "  ";
    cout << temp_celsius << "  ";
    cout << temp_kelvin << endl;
    
  }
  
  return 0;
}
  
  
