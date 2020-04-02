from AES import AES
import sys

def main():
    f = open(sys.argv[3],"w")
    key = parseInput(sys.argv[2])
    aes = AES()
    if sys.argv[1]=="128":

        if len(key) != 16:
            print("Longitud de la llave invalido")
            exit(1)

        keyS = aes.KeyExpansion(key, 16, 176) #AES 128
        hexlist = [hex(x)[2:] if x>15 else "0"+hex(x)[2:] for x in keyS]
        matrixKey =[ hexlist[i:i+16] for i in range(0,len(hexlist),16)]
        #f.write(str(matrixKey))
    elif sys.argv[1]=="192":
        if len(key) != 24:
            print("Longitud de la llave invalido")
            exit(1)
        keyS = aes.KeyExpansion(key, 24, 208)
        print(keyS)
        hexlist = [hex(x)[2:] if x>15 else "0"+hex(x)[2:] for x in keyS]
        matrixKey = [ hexlist[i:i+24] for i in range(0,len(hexlist),24)]
        #f.write(str(matrixKey))

    # Formato
    f.write("".join(matrixKey[0])+"\n")
    matrixKey = matrixKey[1:]
    for row in matrixKey:
        f.write("".join(row)+"\n")
    f.close()
    return
def parseInput(data):
    if len(data) //2 == 16: # longitud de 128 bits
        numeros = [ int(data[i:i+2],16) for i in range(0, 32, 2) ]
    elif len(data) // 2 == 24:
        numeros = [ int(data[i:i+2],16) for i in range(0, 48, 2) ]
    else:
        print("Tamaño de la llave no valido!")
        exit(0)
    return numeros
if __name__ == '__main__':
    # Uso: python3 main.py 128/192 key outputfilename
    if len(sys.argv) != 4:
        print("Help:\npython3 main.py 128/192 key outFilename")
        exit(1)
    main()
