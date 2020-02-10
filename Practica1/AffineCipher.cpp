#include "include/AffineCipher.h"
using namespace std;

AffineCipher::AffineCipher(DiccAP dic){
  d = dic;
}
std::string AffineCipher::Encrypt(std::string message,int keya,int keyb){
  std::string cmessage= "";
  std::string aux;
  for(char &c: message){
    aux = c;
    int val = Modulo(d->map[aux]*keya+keyb,d->len);
    aux = find_val(d,val);
    cmessage+=aux;
  }
  return cmessage;
}
std::string AffineCipher::Decrypt(std::string cmessage,int keya,int keyb){
  std::string message = "";
  std::string aux;
  Euclides e;
  int inverso = e.GetInverso(keya,d->len);
  if(!inverso){
      cout<<"Llave invalida!\n";
      exit(1);
  }
  for(char &c: cmessage){
    aux = c;
    int val = Modulo((d->map[aux]-keyb)*inverso,d->len);
    aux = find_val(d,val);
    message+=aux;
  }
  return message;
}
int* AffineCipher::GenerateRandomKey(){
  int* key = (int*)calloc(sizeof(int),2);
  key[0] = rand()%d->len;
  key[1] = rand()%d->len;
  Euclides e;
  while(e.GetInverso(key[0],d->len)==0){
    key[0] = rand()%d->len;
  }
  return key;
}
