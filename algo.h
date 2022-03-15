#ifndef ALGO_H
#define ALGO_H

#include <stdio.h>
#include <stdlib.h>
int RK(char pat[], char txt[], int q);
int apply_RK(char *pat, char *txt, int q, FILE *out);
void computeLPSArray(char* pat, int M, int* lps);
int apply_kMP(char *pat, char *txt, int q, FILE *out);
#endif

