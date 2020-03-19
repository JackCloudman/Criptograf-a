package main

func OFBMode(key []bool, data []byte, c chan byte) {
	IV := DesEncrypt(GenerateRandomIV(), key)
	for _, i := range data {
		imessage := getArr(i, 8)
		result, _ := BinXOR(imessage, IV)
		c <- byte(getInt(result))
		IV = DesEncrypt(IV, key)
	}
}
