#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE( x ) (sizeof(x))/(sizeof(*x))

char *myfgets(char *, int);
int print_manual(void);
int input_number_in_range(int, int);
int confirm_choice(void);

#endif
