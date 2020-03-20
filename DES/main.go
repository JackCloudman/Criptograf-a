package main

import (
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
)

func main() {

	rand.Seed(20)
	//"-d/-e -rKey/key -rIV/IV filename"
	if len(os.Args) != 5 {
		fmt.Println("Ejemplo de uso: ./DES -d -r filename.txt")
		return
	}
	var key []bool
	var IV []bool
	var outFilename string
	filename := os.Args[4]
	if os.Args[1] == "-e" {
		outFilename = filename + ".des"
		if os.Args[2] == "-rKey" {
			key = GenerateRandomKey()
			fmt.Println("Tu llave es: ", key)
		} else {
			key = TextToBin(os.Args[2])
		}
		if os.Args[3] == "-rIV" {
			IV = GenerateRandomIV()
			fmt.Println("Tu IV es: ", IV)
		} else {
			IV = TextToBin(os.Args[3])
		}
	} else {
		outFilename = filename + "des_decrypted"
		if os.Args[2] == "-rKey" {
			fmt.Println("No random key para descifrar")
			return
		}
		key = TextToBin(os.Args[2])
		if os.Args[2] == "-rIV" {
			fmt.Println("No random key para descifrar")
			return
		}
		IV = TextToBin(os.Args[3])
	}
	c := make(chan byte)
	// Weas para leer de un archivo y leer byte por byte
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}
	f, err := os.Create(outFilename)
	if err != nil {
		fmt.Println(err)
		return
	}
	// Funcion que cifrará cada bloque
	go OFBMode(key, IV, data, c)
	for i := 0; i < len(data); i++ {
		result := <-c // Leemos esa respuesta
		writeFile(f, []byte{result})
	}
}
func writeFile(f *os.File, data []byte) {
	f.Write(data)
}
