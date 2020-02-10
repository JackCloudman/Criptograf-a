#ifndef __AFFINE_CIPHER_H__
#define __AFFINE_CIPHER_H__
#include "Diccionario.h"
#include "Euclides.h"
#include "Utils.h"

#include<stdlib.h>
#include <algorithm>
class AffineCipher
{
    public:
      AffineCipher(DiccAP dic);
      std::string Encrypt(std::string message,int keya,int keyb);
      std::string Decrypt(std::string message,int keya,int keyb);
      int* GenerateRandomKey();
    private:
      DiccAP d;
};
#endif
