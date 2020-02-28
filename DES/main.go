package main

import (
	"fmt"
	"io/ioutil"
)

func main() {
	data, err := ioutil.ReadFile("test.txt")
	arrxor := []bool{true, false, true, false, true, true, false, false}
	for _, i := range data {
		fmt.Println(i)
		arr := getArr(i, 8)
		result, err := BinXOR(arrxor, arr)
		if err != nil {
			return
		}
		fmt.Println(result)
	}
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}
}
