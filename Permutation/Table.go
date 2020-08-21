package main

import (
	"encoding/json"
	"io/ioutil"
	"math/rand"
	"time"
)

type Table struct {
	PiX []int `json:"Pi(x)"`
}

func ReadTable(filename string) []int {
	table := Table{}
	file, err := ioutil.ReadFile(filename)
	if err != nil {
		panic("Error al leer el archivon\n" + err.Error())
	}
	json.Unmarshal(file, &table)
	return table.PiX
}
func RandomTable(tam int) []int {
	table := make([]int, tam)
	for i := 0; i < tam; i++ {
		table[i] = i
	}
	rand.Seed(time.Now().UnixNano())
	rand.Shuffle(len(table), func(i, j int) { table[i], table[j] = table[j], table[i] })
	return table
}
func GetInversa(table []int) []int {
	inversa := make([]int, len(table))
	for index, val := range table {
		inversa[val] = index
	}
	return inversa
}
