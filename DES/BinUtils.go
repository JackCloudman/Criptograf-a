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
func Permutar(original []bool, tabla []int) []bool {
	result := make([]bool, len(tabla))
	for i, pos := range tabla {
		result[i] = original[pos]
	}
	return result
}
func ShiftLeft(arr []bool, num int) []bool {
	var left bool
	for i := 0; i < num; i++ {
		left, arr = arr[0], arr[1:]
		arr = append(arr, left)
	}
	return arr
}
func SplitArray(arr []bool, i int) ([]bool, []bool) {
	tempA := make([]bool, i)
	tempB := make([]bool, i)
	copy(tempA, arr[:i])
	copy(tempB, arr[i:])
	return tempA, tempB
}
func TextToBin(original string) []bool {
	bin := make([]bool, len(original))
	for index, i := range original {
		if string(i) == "1" {
			bin[index] = true
		} else {
			bin[index] = false
		}
	}
	return bin
}
