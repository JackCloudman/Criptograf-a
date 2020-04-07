import numpy as np
import sys

class GF:
    __POLINOMIOS__ = {3:0xD,  # or 1101
                4:0x13, # or 10011
                5:0x25, # or 100101
                6:0x6D, # or 1101101
                7:0x83,
                8:0x11B} # or 100011011

    def TablaMultiplicacion(self,n,outtype='int64'):

        polynom = self.__POLINOMIOS__[n]
        orden= (2**n-1)
        tabla = np.zeros([orden,orden],dtype='int64')
        for i in range(orden):
            for j in range(orden):
                tabla[i,j] = self.peasantMultiplication(i+1,j+1, polynom, n)

        vhex = np.vectorize(hex)


        if outtype == 'hex':
            vhex = np.vectorize(hex)
            return vhex(tabla)

        else:
            A = tabla
            for idx,element in enumerate(A):
                for idy, x in enumerate(element):
                    A[idx,idy]= "{0:b}".format(A[idx,idy])
            return A

        return tabla

    def peasantMultiplication(self,a, b,poly, n):
        limit = int((2**n)/2)
        limit = hex(limit)
        res = 0
        while (b):
            if (b & 1):
                res ^= a
            if (a & int(limit, 16)):
                a = (a<< 1) ^ poly
            else:
                a = a << 1
            b = b >> 1
        return res
