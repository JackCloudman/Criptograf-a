#include "include/Diccionario.h"
#include "include/VigenareCipher.h"
using namespace std;

VigenareCipher::VigenareCipher(DiccAP dic){
  d = dic;
}
std::string VigenareCipher::Encrypt(std::string text,std::string key){
  int key_len = key.length();
  std::string ctext = "";
  std::string aux;
  std::string ki;
  int i=0;

  for(char& c : text){

    aux = c;
    ki = key.at(i);
    int val = (d->map[aux]+d->map[ki])%d->len;
    aux = find_val(d,val);

    i = (i+1)%key_len;
    ctext+=aux;
  }
  return ctext;
}
std::string VigenareCipher::Decrypt(std::string ctext,std::string key){
  int key_len = key.length();
  std::string message = "";
  std::string aux;
  std::string ki;
     int i = 0;
  for(char &c: ctext){
    aux = c;
    ki = key.at(i);
    int val = (d->map[aux]-d->map[ki])%d->len;
    if(val<0){
      val = d->len+val;
    }
    aux = find_val(d,val);
    message+=aux;
    i = (i+1)%key_len;
  }
  return message;
}
std::string VigenareCipher::GenerateRandomKey(int length, DiccAP d)
{

  std::string found;

  for (int i = 0; i < length; ++i)
  {

    std::map<std::string,int>::iterator item =d->map.begin();
    std::advance(item, rand()%d->map.size());
    int somevalue=item->second;

    for (std::map<std::string,int>::iterator it = d->map.begin(); it != d->map.end(); ++it)
      if (it->second == somevalue)
      {
          found+= it->first;
          //cout << found;
      }

  }
  return found;
}
