#ifndef CALCULATION_H
#define CALCULATION_H

#include <cstdlib>
#include <cmath>
#include "../_share/utils.h"

__int64 facI ( int n ) { __int64 f = 1; while ( n > 1 ) f *= n--; return f; }

double calcu(double a, char op, double b) {
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*' : return a * b;
    case '/' : if ( 0==b ) exit ( -1 ); return a/b; 
    case '^' : return pow ( a, b );
    default  : exit ( -1 );
    }
}

double calcu(char op, double b) {
    switch (op)
    {
    case '!': return (double) facI((int) b);
    default: exit(-1);
    }
}

#endif