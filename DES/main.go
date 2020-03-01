package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	key := []bool{true, false, true, false, false, false, false, false, true, false}
	filename := "test.txt"
	// Weas para leer de un archivo y leer byte por byte
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}
	f, err := os.Create(filename + ".des")
	if err != nil {
		fmt.Println(err)
		return
	}
	for _, i := range data {
		imessage := getArr(i, 8)
		result := getInt(DesEncrypt(imessage, key))
		writeFile(f, []byte{byte(result)})
	}
	/*
		message := []bool{true, false, true, true, true, true, false, true}
		Cmessage := DesEncrypt(message, key)
		Dmessage := DesDecrypt(Cmessage, key)
		log.Println(Cmessage)
		log.Println(Dmessage)*/
}
func writeFile(f *os.File, data []byte) {
	f.Write(data)
}
