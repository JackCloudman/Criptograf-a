package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	// ./main -d/-e -r/tablefile filename
	var table []int
	if len(os.Args) != 4 {
		fmt.Println("Ejemplo de uso: ./Permutar -d -r filename.txt")
		return
	}
	if os.Args[2] == "-r" {
		table = RandomTable(8)
		fmt.Println("Random table: ", table)
	} else {
		table = ReadTable(os.Args[2])
	}
	if os.Args[1] == "-e" {
		Cifrar(os.Args[3], table)
	} else {
		table = GetInversa(table)
		DesCifrar(os.Args[3], table)
	}
}
func Cifrar(filename string, table []int) {
	PermutarArchivo(filename, filename+".crypt", table)
}
func DesCifrar(filename string, table []int) {
	PermutarArchivo(filename, filename+".decrypt", table)
}
func PermutarArchivo(filename, fileoutname string, table []int) {
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		println(err)
	}
	if len(data)%len(table) != 0 {
		dif := len(data) % len(table)
		for i := 0; i < len(table)-dif; i++ {
			data = append(data, []byte("X")[0])
		}
	}
	tam := len(table)
	start := 0
	f, err := os.Create(fileoutname)
	defer f.Close()
	if err != nil {
		fmt.Println(err)
		return
	}
	for start < len(data) {
		result := Permutar(data[start:start+tam], table)
		f.Write(result)
		start = start + tam
	}
}
func Permutar(original []byte, tabla []int) []byte {
	result := make([]byte, len(tabla))
	for i, pos := range tabla {
		result[i] = original[pos]
	}
	return result
}
