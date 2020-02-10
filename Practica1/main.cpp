#include "include/Diccionario.h"
#include "include/AffineCipher.h"
#include "include/VigenareCipher.h"
#include <iterator>
#include <algorithm> 
#include <map>
#include <string>
using namespace std;

std:: string generateVigenereRandomKey(int length, DiccAP d)
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
int main(int argc, char const **argv){

  srand(time(NULL));

  int encryptionMethod = atoi(argv[1]); //1 is for vigenere 2 is for affine

  std::string input,plainTextNameFile;
  std::cout<<"Dame el mensaje a encriptar: \n";
  std::getline(std::cin, input);
  std::cout<<"Ingresa el nombre del archivo para guardar el plainText: \n";
  std::getline(std::cin, plainTextNameFile);
  std::fstream newFile;
  newFile.open(plainTextNameFile+".txt",ios::out);
  newFile << input;
  newFile.close();
  ////////////////////////////////////////////////

  int* key = nullptr;
  DiccAP d = leer_mapa("filename.txt");
  cout<<"LEN: "<<d->len<<"\n";
  AffineCipher ac(d);
  VigenareCipher vc(d);

  std::string mensaje,line;
  std::fstream infile;
  infile.open (plainTextNameFile+".txt",ios::in); //read from the plainText
  
  while(getline(infile,line)) // To get you through all the lines.
  {
    mensaje+=line;
  }
  infile.close();

  if (encryptionMethod == 1 && argv[2] != NULL)
  {
    std::string customKey;
    cout<<"ingresa la llave: \n";
    std::getline(std::cin, customKey);
    std::string cmessage = vc.Encrypt(mensaje,customKey);
    std::fstream newFileCipher;
    newFileCipher.open(plainTextNameFile+".vig",ios::out);
    newFileCipher << cmessage;
    newFileCipher.close();
    std::string message = vc.Decrypt(cmessage,customKey);
    cout<<"cmessage:"<<cmessage<<"\n";
    cout<<"message:"<<message<<"\n";
    imprimir_diccionario(d);
  }
  else if (encryptionMethod == 1)
  {
    std::string vigenereRandomKey;
    vigenereRandomKey = generateVigenereRandomKey(5,d);
    cout<<"cifrando con llave:"<<vigenereRandomKey<<"\n";
    std::string cmessage = vc.Encrypt(mensaje,vigenereRandomKey);
    std::fstream newFileCipher;
    newFileCipher.open(plainTextNameFile+".vig",ios::out);
    newFileCipher << cmessage;
    newFileCipher.close();
    std::string message = vc.Decrypt(cmessage,vigenereRandomKey);
    cout<<"cmessage:"<<cmessage<<"\n";
    cout<<"message:"<<message<<"\n"; 
  }
  else if (encryptionMethod == 2 && argv[2] != NULL)
  {
    key = (int*)calloc(sizeof(int),2);
    cout<<"ingresa la llave a: \n";
    cin>>key[0];
    cout<<"ingresa la llave b: \n";
    cin>>key[1];
    int zn=d->map.size();
    if ( __gcd(key[0], zn) == 1)
    {
      std::string cmessage= ac.Encrypt(mensaje,key[0],key[1]);
      std::fstream newFileCipher2;
      newFileCipher2.open(plainTextNameFile+".aff",ios::out);
      newFileCipher2 << cmessage;
      newFileCipher2.close();
      std::string message = ac.Decrypt(cmessage,key[0],key[1]);
      cout<<"cmessage: "<<cmessage<<"\n";
      cout<<"message: "<<message<<"\n";
    }
    else {cout<<"llaves no validas";}

  }
  else if(encryptionMethod == 2)
  {
    key = ac.GenerateRandomKey();
    cout<<"a: "<<key[0]<<"\n";
    cout<<"b: "<<key[1]<<"\n";
    std::string cmessage= ac.Encrypt(mensaje,key[0],key[1]);
    std::fstream newFileCipher2;
    newFileCipher2.open(plainTextNameFile+".aff",ios::out);
    newFileCipher2 << cmessage;
    newFileCipher2.close();
    std::string message = ac.Decrypt(cmessage,key[0],key[1]);
    cout<<"cmessage: "<<cmessage<<"\n";
    cout<<"message: "<<message<<"\n";
  }
return 0;
}
