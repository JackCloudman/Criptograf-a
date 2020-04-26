from Cifrador import Cifrador
CIPHERS = ["AES","3DES","RC2",]
MODES = ["ECB","CBC","CFB","OFB","CTR",]
def main():
    with open("imagen.HEIC",'rb') as f:
        data = f.read()
    for cipher in CIPHERS:
        for mode in MODES:
            c = Cifrador(cipher,mode)
            # Cifrar
            with open("filename_%s_%s.encrypt"%(cipher,mode),'wb') as f:
                ct = c.Cifrar(data)
                f.write(ct)
                dd = c.get_data()
                print(dd) # Datos para poder descifrar
            # Descifrar
            dc = Cifrador(cipher,mode,dd["key"],dd["iv"],dd["nonce"]) # Se necesita una nueva instancia para descifrar
            with open("filename_%s_%s.decrypt"%(cipher,mode),'wb') as f:
                f.write(dc.Descifrar(ct))

if __name__ == '__main__':
    main()
