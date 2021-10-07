#ifndef READNUMBER_H
#define READNUMBER_H

#include "stack_vector.h"

void readNumber(char *& p, Stack<double>& stk) {
    stk.push((double) (*p - '0'));
    while (isdigit(*(++p)))
        stk.push(stk.pop() * 10 + (*p - '0'));
    if ('.' != *p) return;
    float fraction = 1;
    while (isdigit(*++p))
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
}

#endif