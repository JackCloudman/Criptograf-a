import secrets 
import string
from Crypto.Cipher import Salsa20
from Crypto.Random import get_random_bytes

number = secrets.randbelow(3000) #numero aleatorio 0 - 3000
print(number)

x = secrets.randbits(10) #generación de bits aleatorios
print(bin(x))

alphabet = string.ascii_letters + string.digits 
password = ''.join(secrets.choice(alphabet) for i in range(20))  #generacion se llaves alfanumericas aleatorias
print(password)

randomHex = secrets.token_hex(24) #generación de llaves hex aleatorias
print(randomHex)

########### stream cipher salsa20

with open('TextFile.txt','r') as f:
	plaintext = f.read()

data= plaintext.encode("utf-8")
secret = b'*Thirty-two byte (256 bits) key*'
cipher = Salsa20.new(key=secret)
msg = cipher.nonce + cipher.encrypt(data) #encryption

with open('encrypted.bin','wb') as ciperFile:
	ciperFile.write(msg) #writing ciphered text

with open('encrypted.bin','rb') as f2:
	readmsg=f2.read()

msg_nonce = readmsg[:8]
ciphertext = readmsg[8:]
cipher2 = Salsa20.new(key=secret, nonce=msg_nonce)
plaintext2 = cipher2.decrypt(ciphertext) #decryption

with open('decrypted.txt','w') as decrypedFile:
	decrypedFile.write(plaintext2.decode("utf-8"))
