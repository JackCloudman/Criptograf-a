#include "include/Diccionario.h"
#include "include/AffineCipher.h"
#include "include/VigenareCipher.h"
#include <iterator>
#include <map>
#include <string>
using namespace std;
DiccAP d = leer_mapa("diccionario.txt");
void ParseAffineKey(std::string key,int *a,int *b){
  sscanf(key.c_str(),"%d,%d",a,b);
}
void Vigenare(std::string cifrar_or_descifrar,std::string key,std::string filename){
  VigenareCipher vc(d);
  std::string message,cmessage,line;
  std::fstream infile;
  std::fstream outfile;
  infile.open(filename,ios::in); //read from the plainText

  //Decrypt
  if(cifrar_or_descifrar.compare("-d")==0){
    if(key.compare("-r")==0){
      cout<<"La llave para descifrar no puede ser aleatoria!\n";
      exit(1);
    }
    outfile.open(filename+".vig_decrypted",ios::out);
    while(getline(infile,line)){
      message = vc.Decrypt(line,key);
      outfile <<message<<"\n";
    }
    outfile.close();
  }
  //Encrypt
  else if(cifrar_or_descifrar.compare("-e")==0){
    //Llave aleatoria
    if(key.compare("-r")==0){
      key = vc.GenerateRandomKey(10,d);
      cout<<"Tu llave es: "<<key<<"\n";
    }
    outfile.open(filename+".vig", ios::out);
    while(getline(infile,line)){
      cmessage = vc.Encrypt(line,key);
      outfile <<cmessage<<endl;
    }
    outfile.close();
  }

  infile.close();
}
void Affine(std::string cifrar_or_descifrar,std::string key,std::string filename){
  AffineCipher ac(d);
  std::string message,cmessage,line;
  std::fstream infile;
  std::fstream outfile;
  int a,b;
  int *affine_key;
  infile.open(filename,ios::in); //read from the plainText

  //Decrypt
  if(cifrar_or_descifrar.compare("-d")==0){
    if(key.compare("-r")==0){
      cout<<"La llave para descifrar no puede ser aleatoria!\n";
      exit(1);
    }
    ParseAffineKey(key,&a,&b);
    outfile.open(filename+".aff_decrypted",ios::out);
    while(getline(infile,line)){
      message = ac.Decrypt(line,a,b);
      outfile <<message<<"\n";
    }
    outfile.close();
  }
  //Encrypt
  else if(cifrar_or_descifrar.compare("-e")==0){
    //Llave aleatoria
    if(key.compare("-r")==0){
      affine_key = ac.GenerateRandomKey();
      a = affine_key[0];
      b = affine_key[1];
      cout<<"Tu llave es (a,b): ("<<a<<","<<b<<")\n";
    }else{
      ParseAffineKey(key,&a,&b);
    }
    outfile.open(filename+".aff", ios::out);
    while(getline(infile,line)){
      cmessage = ac.Encrypt(line,a,b);
      outfile <<cmessage<<endl;
    }
    outfile.close();
  }

  infile.close();
}
int main(int argc, char *argv[]){
  srand(time(NULL));
  d = leer_mapa("diccionario.txt");

  if(argc <5){
    cout<<"Forma de usarse: ./practica1 -v/-a -d/-e -r/key filename\n";
    exit(1);
  }

  std::string filename,key,cifrar_or_descifrar,algoritmo;
  algoritmo = argv[1];
  cifrar_or_descifrar = argv[2];
  key = argv[3];
  filename = argv[4];
//  cout<<algoritmo<<"\n"<<cifrar_or_descifrar<<"\n"<<key<<"\n"<<filename<<"\n";

  if(algoritmo.compare("-v")==0){
    Vigenare(cifrar_or_descifrar,key,filename);
  }
  else if( algoritmo.compare("-a") == 0){
    Affine(cifrar_or_descifrar,key,filename);
  }else{
    cout<<"Solo se puede -a o -v para el algoritmo!\n";
  }

  return 0;
}
