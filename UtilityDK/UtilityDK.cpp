/*
  UtilityDK.cpp - Library for math functions and constants
*/

#include "Arduino.h"
#include "UtilityDK.h"


// SCALE: Map input value range to output value range
int UtilityDK::scale(int inNum, int inMin, int inMax, int outMin, int outMax)
{
  int result = (((inNum - inMin) * (outMax - outMin)) / (inMax - inMin)) + outMin;
  
  if(result > outMax) result = outMax;
  if(result < outMin) result = outMin;

  return result;  
}

double UtilityDK::scale(double inNum, double inMin, double inMax, double outMin, double outMax)
{
  double result = (((inNum - inMin) * (outMax - outMin)) / (inMax - inMin)) + outMin;
  
  if(result > outMax) result = outMax;
  if(result < outMin) result = outMin;

  return result;  
}
