#include "include/Euclides.h"
#include<stdlib.h>
int* Euclides::GetExtendido(int n1,int n2) // n1 es a y n2 es b
{
  int* array = (int*)calloc(sizeof(int),3);
   int x=0,y=0,d=0,x2 = 1,x1 = 0,y2 = 0,y1 = 1,q = 0, r = 0;
  if(n2==0)
  {
  array[0]=n1;
  array[1]=1;
  array[2]=0;
  }
  else
  {
   while(n2>0)
      {
     q = (n1/n2);
      r = n1 - q*n2;
      x = x2-q*x1;
      y = y2 - q*y1;
      n1 = n2;
      n2 = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
      }
      array[0] = n1;   // mcd (n1,n2)
      array[1] = x2;   // x
      array[2] = y2;   // y
    }
    return array;
}
int Euclides::GetInverso(int a,int n){
  int* extendido = GetExtendido(a,n);
  if(extendido[0]!=1)
    return 0;
  return Modulo(extendido[1],n);
}
