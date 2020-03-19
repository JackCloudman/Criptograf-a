package main

import (
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
)

func main() {
	rand.Seed(20)
	key := []bool{true, false, true, false, false, false, false, false, true, false}
	c := make(chan byte)
	filename := "test.txt"
	// Weas para leer de un archivo y leer byte por byte
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}
	f, err := os.Create(filename + ".decrypted")
	if err != nil {
		fmt.Println(err)
		return
	}
	// Funcion que cifrará cada bloque
	go OFBMode(key, data, c)

	for i := 0; i < len(data); i++ {
		result := <-c // Leemos esa respuesta
		writeFile(f, []byte{result})
	}
}
func writeFile(f *os.File, data []byte) {
	f.Write(data)
}
