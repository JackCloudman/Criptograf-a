#include "include/Diccionario.h"
#include <iterator>
using namespace std;
DiccAP leer_mapa(std::string filename){
  DiccAP d = new Diccionario();

  fstream new_file;
  new_file.open(filename,ios::in);
  int i = 0;
  if(!new_file){
    cout<<"No such file";
    return nullptr;
  }
  else {
    //new_file >>std::noskipws;
    std::string ch;
    while (!new_file.eof()){
      //new_file>> ch;
      ch=new_file.get();
      if (d->map.find(ch) == d->map.end() ){
        d->map[ch] = i++;
      }
    }
    new_file.close();
  }
  d->len = d->map.size();
    return d;
}
void imprimir_diccionario(DiccAP d){
  cout<<"LEN:"<<d->len<<"\n";
  for (std::map<std::string,int>::iterator it=d->map.begin(); it!=d->map.end(); ++it)
  std::cout << it->first << " => " << it->second << '\n';
}
std::string find_val(DiccAP d,int val){
  std::string key;
  for (auto it = (d->map).begin(); it != (d->map).end(); ++it){
    if (it->second == val){
      return it->first;
        key = it->first ;
        return key;
    }
}
  return nullptr;
}
