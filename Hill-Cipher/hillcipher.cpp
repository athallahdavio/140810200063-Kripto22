#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int key[3][3];

int mod26(int x)
{
    return x >= 0 ? (x % 26) : 26 - (abs(x) % 26);
}

// Perkalian matriks
void multiplyMatrices(int a[1000][3], int a_rows, int a_cols, int b[1000][3], int b_rows, int b_cols, int res[1000][3])
{
    for (int i = 0; i < a_rows; i++)
    {
        for (int j = 0; j < b_cols; j++)
        {
            for (int k = 0; k < b_rows; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
            res[i][j] = mod26(res[i][j]);
        }
    }
}

// Mencari determinan matriks
int findDet(int m[3][3], int n)
{
    int det;
    if (n == 2)
    {
        det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    else
        det = 0;
    return mod26(det);
}

// Invers matriks
int findDetInverse(int R, int D = 26)
{
    int i = 0;
    int p[100] = {0, 1};
    int q[100] = {0};

    while (R != 0)
    {
        q[i] = D / R;
        int oldD = D;
        D = R;
        R = oldD % R;
        if (i > 1)
        {
            p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
        }
        i++;
    }
    if (i == 1)
        return 1;
    else
        return p[i] = mod26(p[i - 2] - p[i - 1] * q[i - 2]);
}

// GCD
int gcd(int m, int n)
{
    if (n > m)
        swap(m, n);

    do
    {
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);

    return m;
}

// Mencari inverse
void findInverse(int m[3][3], int n, int m_inverse[3][3])
{
    int adj[3][3] = {0};

    int det = findDet(m, n);
    int detInverse = findDetInverse(det);

    if (n == 2)
    {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse);
        }
    }
}

// Enkripsi
string encrypt(string plainTeks, int n)
{
    int plaintext[1000][3] = {0};
    int ciphertext[1000][3] = {0};
    int ptloop = 0;

    while (plainTeks.length() % n != 0)
    {
        plainTeks += "x";
    }
    int row = (plainTeks.length()) / n;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plaintext[i][j] = plainTeks[ptloop++] - 'a';
        }
    }

    multiplyMatrices(plaintext, row, n, key, n, n, ciphertext);

    string cipherTeks = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cipherTeks += (ciphertext[i][j] + 'a');
        }
    }
    return cipherTeks;
}

// Dekripsi
string decrypt(string cipherTeks, int n)
{
    int plaintext[1000][3] = {0}; 
    int ciphertext[1000][3] = {0};
    int ctloop = 0;

    int row = cipherTeks.length() / n;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ciphertext[i][j] = cipherTeks[ctloop++] - 'a';
        }
    }

    int k_inverse[3][3] = {0};
    findInverse(key, n, k_inverse);

    multiplyMatrices(ciphertext, row, n, k_inverse, n, n, plaintext);

    string plainTeks = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < n; j++)
        {
            plainTeks += (plaintext[i][j] + 'a');
        }
    }
    return plainTeks;
}

// Mencari key
void findKey()
{
    string plainteks, cipherteks;
    int key[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter;
    int p, c;
    int transpose[2][2];
    cout << "Masukkan Plainteks : ";
    cin.ignore();
    getline(cin, plainteks);

    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }

    cout << "Masukkan Cipherteks : ";
    getline(cin, cipherteks);

    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }

    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if (gcd(det, 26) == 1)
    {
        detInv = findDetInverse(det, 26);

        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1) * plainMatrix[0][1];
        adj[1][0] = (-1) * plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                plainteksInv[i][j] = detInv * adj[i][j];
                if (plainteksInv[i][j] < 0)
                {
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j]) % 26);
                }
                else
                {
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                key[i][j] = 0;
                for (int k = 0; k < 2; k++)
                {
                    key[i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key[i][j] %= 26;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                transpose[j][i] = key[i][j];
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << (transpose[i][j]) << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Tidak dapat menemukan key karena determinan tidak relatif" << endl
             << endl;
    }
}

int main(void)
{
    bool menuActive = true;
    string pt, ct;
    int n;
    int pilih;

    while (menuActive)
    {
        cout << "\nProgram Hill Cipher" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Cari Key" << endl;
        cout << "Pilihan : ";
        cin >> pilih;
        switch (pilih)
        {
        case 1:
            cout << "Masukkan plaintext : ";
            cin >> pt;

            cout << "Masukkan ordo matriks persegi : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << "Matriks[" << i + 1 << "][" << j + 1 << "] : ";
                    cin >> key[i][j];
                }
            }

            ct = encrypt(pt, n);
            cout << "Hasil Enkripsi : " << ct << endl;
            break;
        case 2:
            cout << "Masukkan ciphertext : ";
            cin >> ct;

            cout << "Masukkan ordo matriks persegi : ";
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << "Masukkan matriks[" << i + 1 << "][" << j + 1 << "] : ";
                    cin >> key[i][j];
                }
            }

            cout << "\nChipertext : " << ct << endl;
            cout << "Hasil Dekripsi : " << decrypt(ct, n) << endl;
            break;
        case 3:
            cout << endl;
            findKey();
            break;
        default:
            cout << "\nInvalid Input" << endl;
            break;
        }
    }
}