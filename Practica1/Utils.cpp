#include "include/Utils.h"
int Modulo(int a,int b){
  int c = a%b;
  if(c<0)
    return b+c;
  return c;
}
