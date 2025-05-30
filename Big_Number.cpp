#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <vector>

#define BASE_SIZE (sizeof(BASE)*8) 

using namespace std;

typedef unsigned short int BASE;


class BN {
private:
    int maxlen;     
    int len;        
    BASE *coef;     

public:
    
    BN() : maxlen(1), len(1) {
        coef = new BASE[maxlen];
        // coef[0] = 0;
        cout << coef[0];
    }

    BN(int maximal, bool randomize): maxlen(maximal), len(maximal) {
        coef = new BASE[maximal];
        int size = BASE_SIZE; 

        if (randomize) {
            int parts = (BASE_SIZE)/4; 
            for (int i = 0; i < maxlen; i++) {
                BASE value = 0;
                for (int j = 1; j < parts; j++) {
                    BASE hex_digit = rand() % 16; 
                    value |= (hex_digit << (j*4)); 
                } 
                coef[i] = value; 
                cout << coef[i] << " "; 
            }

            len = maxlen;
            while (len > 1 && coef[len - 1] == 0)
                len--;
        } else {
            
            fill(coef, coef + maxlen, 0);
            len = 1;
            for (int i = 0; i < maxlen; i++) {
                cout << coef[i] << " ";
            }
        }
        cout << dec << endl; 
    }

    
    BN(const BN& other): maxlen(other.maxlen), len(other.len) {
        coef = new BASE[maxlen];
        memcpy(coef, other.coef, maxlen * sizeof(BASE)); 
    }

   
    ~BN() {
        delete[] coef;
        coef = NULL;
    }

    
    BN& operator=(const BN& other){
        if (this != &other){ 
            delete[] coef;
            BASE *new_coef = new BASE[other.maxlen];
            memcpy(new_coef, other.coef, other.maxlen * sizeof(BASE));

            maxlen = other.maxlen;
            len = other.len;
            coef = new_coef;
        }
        return *this;
    }

    friend istream& operator>>(istream& is, const BN& num) {
        string s;
        is >> s;
        int len = (s.length()-1)/(BASE_SIZE/4)+1;
        int maxlen = len;
        
        // delete[] num.coef;
        
        
        // fill(num.coef, num.coef + maxlen,0);
        
        int j = 0;
        int k = 0;
        int tmp = 0;
        for (int i = s.length()-1; i >= 0; i--){
            if ('0' <= s[i] && s[i] <= '9')
                tmp |= (s[i] - '0')<<k;
            else if ('a' <= s[i] && s[i] <= 'f')
                tmp |= (s[i] - 'a' + 10)<<k;
            else if ('A' <= s[i] && s[i] <= 'F')
                tmp |= (s[i] - 'A' + 10)<<k;
            else {
                cerr << "Error" << s[i];
            }
            k += 4;
            if (k >= BASE_SIZE) {
                num.coef[j++] = tmp;
                tmp = 0;
                k = 0;
            }
        }
        if (k > 0) {
            num.coef[j] = tmp;
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const BN& num) {
        os << "BN: ";
        for (int i = 0; i <= num.len - 1; i++) {
            // os << hex << setw(4) << setfill('0') << num.coef[i] << " ";
            os.width(BASE_SIZE/4);
            os.fill('0');
            os << hex << num.coef[i] << " ";
        }
        return os;
    }
};

int main()
{
    srand(time(0)); 

    cout << "конструктор 1: ";
    BN a1;
    cout << "\n";

    cout << "рандом-конструктор 2: ";
    BN a2(12, 1); 

    cout << "конструктор копирования: \n";
    BN a3(a2); 
    cout << a3; 

    cout << "\n оператор присваивания: \n";
    BN a4;
    a4 = a2; 
    cout << a4; 
    
    cout << "\n HEX-ввод: \n";
    BN a5;
    cin >> a5;
    
    cout << "Hex-вывод: " << a5;

    return 0;
}
