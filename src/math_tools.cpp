//
// Created by moezen on 18-1-29.
//

#include "include/math_tools.h"
float wrap2pi(float x)
{

    x=x+M_PI;
    x=x - M_2PI * (int)(x /(M_2PI));

    if (x < 0) x+= M_2PI;
    return x-M_PI;
}
