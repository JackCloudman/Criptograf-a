from Crypto.Cipher import AES
from Crypto.Cipher import DES3
from Crypto.Cipher import ARC2
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from base64 import b64encode,b64decode
class Cifrador():
    BLOCK_SIZE = 32 # Bytes
    CIPHERS = {
        "AES": AES,
        "3DES": DES3,
        "RC2": ARC2,
    }
    MODES = {
    "ECB": AES.MODE_ECB,
    "CBC": AES.MODE_CBC,
    "CFB": AES.MODE_CFB,
    "OFB": AES.MODE_OFB,
    "CTR": AES.MODE_CTR,
    }
    def __init__(self,CIPHER,MODE,key=None,iv=None,nonce=None):
        key = b64decode(key) if key else get_random_bytes(24) # Generamos la llave aleatoria

        if CIPHER not in self.CIPHERS:
            return 1
        CIPHER = self.CIPHERS[CIPHER] # Obtenemos el Cipher elejido

        if CIPHER == DES3:
            key = DES3.adjust_key_parity(key) # Key Parity para 3DES

        if MODE not in self.MODES:
            return 1

        mode = self.MODES[MODE] #Obtenemos el modo de operación
        if (CIPHER != AES) and (MODE == "CTR"):
            nonce = b64decode(nonce) if nonce else get_random_bytes(4)
            cipher = CIPHER.new(key,mode,nonce=nonce)
        elif MODE == "ECB":
            cipher = CIPHER.new(key,mode)
        elif MODE == "CTR":
            nonce = b64decode(nonce) if nonce else None
            cipher = CIPHER.new(key,mode,nonce=nonce)
        else:
            iv = b64decode(iv) if iv else None
            cipher = CIPHER.new(key,mode,iv=iv)
        self.cipher = cipher
        self.mode = MODE
        self.key = key

    def get_data(self):
        key = b64encode(self.key).decode('utf-8')
        if self.mode == "ECB":
            data = {"key": key,"nonce":None,"iv":None}
        elif self.mode == "CTR":
            nonce = b64encode(self.cipher.nonce).decode('utf-8')
            data= {"key":key,"nonce":nonce,"iv":None}
        else:
        #elif any(self.mode == mode for mode in ["CBC","OFB","CFB"]:
            iv = b64encode(self.cipher.iv).decode('utf-8')
            data = {"key": key,"nonce":None,"iv":iv}
        return data
    def Cifrar(self,data):
        if self.mode != "CTR":
            return self.cipher.encrypt(pad(data, self.BLOCK_SIZE))
        return self.cipher.encrypt(data)
    def Descifrar(self,data):
        if self.mode != "CTR":
            return unpad(self.cipher.decrypt(data),self.BLOCK_SIZE)
        return self.cipher.decrypt(data)
    def __repr__(self):
        return str(self.get_data())
    def __str__(self):
        return str(self.get_data())
