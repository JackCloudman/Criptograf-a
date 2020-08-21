from GaloisField import GF
import sys

def main():
    tabla = GF()

    n = int(sys.argv[1])
    print_mode = sys.argv[2]
    tab= tabla.TablaMultiplicacion(n,print_mode)
    filename = "output_%s_%d.txt"%(print_mode,n)
    f = open(filename,'w')
    # Funciones lambda para mostrar el resultado dependiendo del tipo
    # de output que se solicite.
    if print_mode == "hex":
        print_format = lambda x: str(x)[2:] if len(x)>3 else "0"+str(x)[2:]
    else:
        print_format = lambda x: str(x) if len(str(x)) == n else ("0"*(n-len(str(x))))+str(x)
    for i in tab:
        for j in i:
            f.write(print_format(j)+" ")
            print(print_format(j),end=" ")
        print()
        f.write("\n")
    f.close()


if __name__ == "__main__":
    # python3 main.py n format
   main()
