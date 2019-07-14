#include <iostream>
#include <cmath>
#include "statistics.h"

double average(double n1){
  return n1;
}

double average(double n1, double n2){
  return (n1+n2)/2;
}

double average(double n1, double n2, double n3){
  return (n1 + n2 + n3)/3;
}

double average(double n1, double n2, double n3, double n4){
  return (n1 + n2 + n3 + n4)/4;
}

double standard_deviation(double n1){
  return 0;
}

double standard_deviation(double n1, double n2){
  return sqrt(average(pow(n1-average(n1,n2),2),pow(n2-average(n1,n2),2)));
}

double standard_deviation(double n1, double n2, double n3){
  return sqrt(average(pow(n1-average(n1,n2,n3),2),pow(n2-average(n1,n2,n3),2),pow(n3-average(n1,n2,n3),2)));
}

double standard_deviation(double n1, double n2, double n3, double n4){
  return sqrt(average(pow(n1-average(n1,n2,n3,n4),2),pow(n2-average(n1,n2,n3,n4),2),pow(n3-average(n1,n2,n3,n4),2),pow(n4-average(n1,n2,n3,n4),2)));
}
