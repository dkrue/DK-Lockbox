/*
  UtilityDK.h - Library for math functions and constants
*/

#ifndef UtilityDK_h
#define UtilityDK_h

#include "Arduino.h"

class UtilityDK
{
  public:
    static int scale(int inNum, int inMin, int inMax, int outMin, int outMax);
    static double scale(double inNum, double inMin, double inMax, double outMin, double outMax);
  private:

};

#endif