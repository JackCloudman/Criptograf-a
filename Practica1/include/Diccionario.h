#ifndef __DICCIONARIO_H__
#define  __DICCIONARIO_H__
#include <map>
#include <string>
#include <iostream>
#include <fstream>
typedef struct{
  std::map<std::string,int> map;
  int len;
} Diccionario;
typedef Diccionario* DiccAP;
DiccAP leer_mapa(std::string filename);
void imprimir_diccionario(DiccAP);
std::string find_val(DiccAP d,int val);
#endif
