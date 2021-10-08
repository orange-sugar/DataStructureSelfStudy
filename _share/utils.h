#ifndef UTILS_FUNCS_H
#define UTILS_FUNCS_H

#include <iostream>
#include <climits>

#define __int64 long long
#define _INT_MAX_ 2147483647
#define _INT_MIN_ (-_INT_MAX_-1)


#define myMax(a,b) (((a) > (b)) ? (a) : (b))
#define myMin(a,b) (((a) < (b)) ? (a) : (b))

// template <typename T>
// void print(T& e) { std::cout << e << " "; }

template <typename T> struct Print {
    virtual void operator() (T& e) {std::cout << e << " ";}
};



#endif