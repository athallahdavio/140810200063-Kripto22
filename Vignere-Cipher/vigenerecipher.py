def enkripsi(plaintext, key):
    k = 0
    output = ""
    for i in range(len(plaintext)):
        if (plaintext[i].isupper()):
            output += chr((((ord(plaintext[i])-65)+(ord(key[k])-65)) % 26)+65)
            k = k+1
        elif (plaintext[i].islower()):
            output += chr((((ord(plaintext[i])-97)+(ord(key[k])-97)) % 26)+97)
            k = k+1
        else:
            output += " "
    return output


def dekripsi(ciphertext, key):
    k = 0
    output = ""
    for i in range(len(ciphertext)):
        if (ciphertext[i].isupper()):
            output += chr((((ord(ciphertext[i])-65)-(ord(key[k])-65)) % 26)+65)
            k = k+1
        elif (ciphertext[i].islower()):
            output += chr((((ord(ciphertext[i])-97)-(ord(key[k])-97)) % 26)+97)
            k = k+1
        else:
            output += " "
    return output


def generateKey(text, key):
    newKey = key
    while (len(newKey) < len(text)):
        newKey += key
    if (len(newKey) > len(text)):
        n = len(text) - len(newKey)
        newKey = newKey[0:n]
    return newKey

ciphertext = ""
key = ""

plaintext = input("Masukkan Text\t: ")
key = input("Masukkan Kunci\t: ")
ciphertext = enkripsi(plaintext, generateKey(plaintext, key))
print("\nHasil Enkripsi")
print("Plaintext\t:", plaintext)
print("Ciphertext\t:", ciphertext)
print("\nHasil Dekripsi")
print("Ciphertext\t:", plaintext)
print("Plaintext\t:", dekripsi(plaintext, generateKey(plaintext, key)))
