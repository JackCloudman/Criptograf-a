package main

import "math/rand"

var permutacion10 = []int{2, 4, 1, 6, 3, 9, 0, 8, 7, 5}
var permutacion8 = []int{5, 2, 6, 3, 7, 4, 9, 8}
var permutacionInicial = []int{1, 5, 2, 0, 3, 7, 4, 6}
var permutacionInversa = []int{3, 0, 2, 4, 6, 1, 7, 5}
var permutacionExapansion = []int{3, 0, 1, 2, 1, 2, 3, 0}
var permutacion4 = []int{1, 3, 2, 0}
var CajaS0 = [][][]bool{
	{{false, true}, {false, false}, {true, true}, {true, false}},
	{{true, true}, {true, false}, {false, true}, {false, false}},
	{{false, false}, {true, false}, {false, true}, {true, true}},
	{{true, true}, {false, true}, {true, true}, {true, false}}}
var CajaS1 = [][][]bool{
	{{false, false}, {false, true}, {true, false}, {true, true}},
	{{true, false}, {false, false}, {false, true}, {true, true}},
	{{true, true}, {false, false}, {false, true}, {false, false}},
	{{true, false}, {false, true}, {false, false}, {true, true}}}

func DesEncrypt(message, key []bool) []bool {
	message = Permutar(message, permutacionInicial)
	subkey1, subkey2 := genSubKeys(key)
	return Ronda12(message, subkey1, subkey2)

}
func Ronda12(message, subkey1, subkey2 []bool) []bool {
	// RONDA 1
	L, R := SplitArray(message, 4)
	expandidaR := Permutar(R, permutacionExapansion)
	expandidaR, _ = BinXOR(expandidaR, subkey1)
	s0, s1 := SplitArray(expandidaR, 4)
	newL := ConsultarS0(s0[0], s0[3], s0[1], s0[2])
	newL = append(newL, ConsultarS1(s1[0], s1[3], s1[1], s1[2])...)

	newL = Permutar(newL, permutacion4)
	newL, _ = BinXOR(newL, L)
	L = newL
	// RONDA 2
	tempL := L
	L = R
	R = tempL
	expandidaR = Permutar(R, permutacionExapansion)
	expandidaR, _ = BinXOR(expandidaR, subkey2)
	s0, s1 = SplitArray(expandidaR, 4)
	newL = ConsultarS0(s0[0], s0[3], s0[1], s0[2])
	newL = append(newL, ConsultarS1(s1[0], s1[3], s1[1], s1[2])...)

	newL = Permutar(newL, permutacion4)
	newL, _ = BinXOR(newL, L)
	L = newL
	final := append(L, R...)
	final = Permutar(final, permutacionInversa)
	return final
}
func genSubKeys(key []bool) ([]bool, []bool) {
	key = Permutar(key, permutacion10)
	key1, key2 := SplitArray(key, 5)
	key1 = ShiftLeft(key1, 1)
	key2 = ShiftLeft(key2, 1)
	subkey1 := append(key1, key2...)
	subkey1 = Permutar(subkey1, permutacion8)
	key1 = ShiftLeft(key1, 2)
	key2 = ShiftLeft(key2, 2)
	subkey2 := append(key1, key2...)
	subkey2 = Permutar(subkey2, permutacion8)
	return subkey1, subkey2
}
func DesDecrypt(message, key []bool) []bool {
	message = Permutar(message, permutacionInicial)
	subkey1, subkey2 := genSubKeys(key)
	return Ronda12(message, subkey2, subkey1)

}
func ConsultarS0(fila1, fila2, columna1, columna2 bool) []bool {
	fila := getInt([]bool{fila1, fila2})
	columna := getInt([]bool{columna1, columna2})
	return CajaS0[fila][columna]
}
func ConsultarS1(fila1, fila2, columna1, columna2 bool) []bool {
	fila := getInt([]bool{fila1, fila2})
	columna := getInt([]bool{columna1, columna2})
	return CajaS1[fila][columna]
}
func GenerateRandomIV() []bool {
	key := []bool{false, false, false, false, false, false, false, false, false, false}
	for i := 0; i < 8; i++ {
		if rand.Intn(2) == 0 {
			key[i] = false
		} else {
			key[i] = true
		}
	}
	return key
}
