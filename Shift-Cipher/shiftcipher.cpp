#include <iostream>
#include <string>

using namespace std;

string encrypt(string text, int key)
{
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        //uppercase
        if (isupper(text[i])){
            result += char(int(text[i] + key - 65) % 26 + 65);
        } 
        //lowercase
        else if (islower(text[i])) {
            result += char(int(text[i] + key - 97) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    return result;
}

string decrypt(string text, int key)
{
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        //uppercase
        if (isupper(text[i])){
            result += char((int(text[i] - key - 65) % 26 + 26) % 26 + 65);
        } 
        //lowercase
        else if (islower(text[i])) {
            result += char((int(text[i] - key - 97) % 26 + 26) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    return result;
}

int main()
{
    string plaintext = "", cipherteks = " "; 
    int key;
    cout << "Masukkan Kata: ";
    getline(cin, plaintext);
    cout << "Masukkan Kunci: ";
    cin >> key;
    int pilihan;
    cout << "Menu\n";
    cout << "1. Enkripsi\n";
    cout << "2. Dekripsi\n";
    cout << "Pilihan: ";
    cin >> pilihan; 
    switch (pilihan)
    {
    case 1:
        cout << "\nPlaintext : " << plaintext;
        cout << "\nKunci: " << key;
        cipherteks = encrypt(plaintext, key);
        cout << "\nCiphertext: " << cipherteks;
        break;
    case 2:
        cout << "\nCiphertext: " << plaintext;
        cout << "\nKunci: " << key;
        cout << "\nPlaintext: " << decrypt(plaintext, key);
    default:
        break;
    }
    return 0;
}