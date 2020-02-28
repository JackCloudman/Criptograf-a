package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func getArr(caracter byte, length int) []bool {
	var bin []bool
	data := strconv.FormatInt(int64(caracter), 2)
	if len(data) != 8 {
		ceros := strings.Repeat("0", 8-len(data))
		data = ceros + data
	}
	for _, c := range data {
		if c == 48 {
			bin = append(bin, false)
		} else {
			bin = append(bin, true)
		}
	}
	return bin
}
func getInt(bin []bool) int {
	i := len(bin) - 1
	data := 0
	for _, bit := range bin {
		if bit {
			data += int(math.Pow(2, float64(i)))
		}
		i--
	}
	return data
}
func BinXOR(a, b []bool) ([]bool, error) {
	length := len(a)
	if length != len(b) {
		return nil, fmt.Errorf("Longitud de a y b son distintas")
	}
	result := make([]bool, length)
	for i := 0; i < length; i++ {
		if a[i] == b[i] {
			result[i] = false
		} else {
			result[i] = true
		}
	}
	return result, nil
}
