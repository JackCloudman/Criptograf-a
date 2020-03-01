package main

import "log"

func main() {
	// Weas para leer de un archivo y leer byte por byte
	/*data, err := ioutil.ReadFile("test.txt")
	arrxor := []bool{true, false, true, false, true, true, false, false}
	for _, i := range data {
		fmt.Println(i)
		arr := getArr(i, 8)
		result, err := BinXOR(arrxor, arr)
		if err != nil {
			return
		}
		fmt.Println(result)
		tabla := []int{0, 0, 6, 2, 5}
		fmt.Println(Permutar(result, tabla))
	}
	if err != nil {
		fmt.Println("File reading error", err)
		return
	}*/
	key := []bool{true, false, true, false, false, false, false, false, true, false}
	message := []bool{true, false, true, true, true, true, false, true}
	Cmessage := DesEncrypt(message, key)
	Dmessage := DesDecrypt(Cmessage, key)
	log.Println(Cmessage)
	log.Println(Dmessage)
}
