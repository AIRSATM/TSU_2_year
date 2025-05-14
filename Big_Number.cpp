#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cctype>

#define BASE_SIZE (sizeof(BASE)*8)

using namespace std;

typedef unsigned short int BASE;


class BN {
private:
    int maxlen;
    int len;
    BASE *coef;
public:
    // конструктор по умолчанию
    BN() : maxlen(1), len(1) {
        coef = new BASE[maxlen];
        coef[0] = 0;
        cout << coef[0];
    }

    // конструктор 2 + конструктор 3 (заполняем нулями и заполняем числами случайными)
    BN(int maximal, bool randomize): maxlen(maximal), len(maximal) {
        coef = new BASE[maximal];
        int size = BASE_SIZE;
        maxlen = maximal;
        len = maximal;
        
        if (randomize) {
            int parts = (BASE_SIZE + 3) /4; // храним цифры по частям в динамическом массиве
            for (int i = 0; i < maxlen; i++) {
                BASE value = 0;
                for (int j = 1; j < parts; j++) {
                    BASE hex_digit = rand() % 16;
                   value |= (hex_digit << (j*4));
                } 
            coef[i] = value;
            cout << coef[i] << " ";
            }
            
            // убираем ведущие нули
            len = maxlen;
            while (len > 1 && coef[len - 1] == 0)
                len--;
        } else {
            for (int i = 0; i < maxlen; i++) {
                coef[i] = 0;
                cout << coef[i] << " ";
            }
            len = 1; // обновляем, чтобы не было пустого вывода
        }
    }
    // конструктор копирования
    BN(const BN& other): maxlen(other.maxlen), len(other.len) {
        coef = new BASE[maxlen];
        memcpy(coef,other.coef,maxlen*sizeof(BASE));
    }
    // деструктор
    ~BN() {
        delete[] coef;
        coef = NULL;
    }
    // оператор =
    BN& operator=(const BN& other){
        // if (this != &other){ // сразу проверка на самоприсваивание
        //     // освобождаем старые ресурсы
        //     delete[] coef;
            
        //     // создаем временные копии
        //     BASE *new_coef = new BASE[other.maxlen];
        //     memcpy(new_coef,other.coef,other.maxlen*sizeof(BASE));

        //     // обновляем состояние
        //     maxlen = other.maxlen;
        //     len = other.len;
        //     coef = new_coef;
        // }
        // return *this;
    }
    // ввод в hex
    friend istream& operator >> (istream& is, BN& b_number) {
        // char* s = new char[1000];
        
        // int j = 0;
        // int k = 0;
        
        // unsigned int tmp = 0;
        // is.getline(s,1000);
        
        // b_number.len = (strlen(s) - 1)/((BASE_SIZE/4) + 1);
        // b_number.maxlen = b_number.len;
        // b_number.coef = new BASE[b_number.maxlen];
        // for (int i = 0; i < b_number.len; i++){
        //     b_number.coef[i] = 0;
        // }
        
        // for (int i = strlen(s) - 1; i > -1; i--){
        //     if (s[i] >= '0' && s[i] <= '9')
        //         tmp = s[i] - '0';
        //     else if (s[i] >= 'a' && s[i] <= 'f')
        //         tmp = s[i] - 'a' + 10;
        //     else if (s[i] >= 'A' && s[i] <= 'F')
        //         tmp = s[i] - 'A' + 10;
        //     else
        //         throw invalid_argument("Инвалид!!!");
        // }
        // b_number.coef[j] |= tmp << k;
        // k += 4;
        // if (k >= BASE_SIZE){
        //     k = 0;
        //     j++;
        // }
        // return is;
    }
    // вывод в hex
    friend ostream& operator << (ostream& os, BN& number) {
        // int size = BASE_SIZE;
        // char* s = new char[1000];
        // unsigned int tmp = 0;
        // for (int i = 0; i < number.len - 1; i++){
        //     for (int j = number.len - 1; j > -1; j--){
        //         int k = BASE_SIZE - 4;
        //         tmp = (number.coef[j] >> k)&(0xf);
        //         if (0 <= tmp && tmp <= 9)
        //             s[i] = (char)(tmp + '0');
        //         if (10 <= tmp <= 15)
        //             s[i] = (char)(tmp - 10 + 'a');
        //         k-= 4;
        //         if (k < 0)
        //             k = BASE_SIZE - 4;
        //     }
        // }
        // return os;
    }
    
};

int main()
{
    srand(time(0));
    BN a1;
    cout << "\n";
    BN a2(100,1);
    cout << "\n";
    BN a3;
    cout << "\n";
    // cin >> a3;
    // cout << a3 << endl;
    
    
    return 0;
}
