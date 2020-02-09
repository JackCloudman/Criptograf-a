#include "include/Diccionario.h"
#include "include/AffineCipher.h"
#include "include/VigenareCipher.h"
using namespace std;

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
  key = ac.GenerateRandomKey();
  cout<<"a: "<<key[0]<<"\n";
  cout<<"b: "<<key[1]<<"\n";
  VigenareCipher vc(d);

  std::string mensaje,line;
  std::fstream infile;
  infile.open (plainTextNameFile+".txt",ios::in); //read from the plainText
  
  while(getline(infile,line)) // To get you through all the lines.
  {
    mensaje+=line;
  }
  infile.close();

  if (encryptionMethod == 1)
  {
    
    std::string cmessage = vc.Encrypt(mensaje,"key");
    std::fstream newFileCipher;
    newFileCipher.open(plainTextNameFile+".vig",ios::out);
    newFileCipher << cmessage;
    newFileCipher.close();
    std::string message = vc.Decrypt(cmessage,"key");
    cout<<"cmessage:"<<cmessage<<"\n";
    cout<<"message:"<<message<<"\n";
    imprimir_diccionario(d);
  }
  else
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
return 0;
}
