#ifndef APPEND2RPN_H
#define APPEND2RPN_H

#include <cstring>
#include <cstdio>
#include <cstdlib>

void append (char *& rpn, double opnd) {
    char buf[64];
    if (0.0 < opnd - (int)opnd) sprintf(buf, "%f \0", opnd);
    else                        sprintf(buf, "%d \0", (int)opnd);
    rpn = (char *) realloc(rpn, sizeof (char) * (strlen(rpn) + strlen(buf) + 1));
    strcat(rpn, buf);
}

void append ( char*& rpn, char optr ) { 
   int n = strlen ( rpn ); 
   rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + 3 ) ); 
   sprintf ( rpn + n, "%c ", optr ); rpn[n + 2] = '\0'; 
}

#endif