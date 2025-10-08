#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <vector>
#include <algorithm>

#define BASE_SIZE (sizeof(BASE)*8) 

using namespace std;

typedef unsigned int BASE;
typedef unsigned long long int DBASE;


class BN {
private:
    int maxlen;     
    int len;        
    BASE *coef;     

public:
    
    BN() : maxlen(1), len(1) {
        coef = new BASE[maxlen];
        coef[0] = 0;
        
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
                cout << (int)coef[i] << " "; 
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
    
    bool operator == (const BN &var) {
        if (len != var.len){
            return false;
        }
        for (int i=0;i<len;i++){
            if (coef[i]!=var.coef[i]){
                return false;
            }
        }
        return true;
    }
    
    bool operator != (const BN &var) {
        if (len != var.len){
            return true;
        }
        for (int i=0;i<len;i++){
            if (coef[i]!=var.coef[i]){
                return true;
            }
        }
        return false;
    }
    
    bool operator < (const BN& var){
        if(len < var.len){
            return true;
        }
        if(len > var.len){
            return false;
        }
        for(int i = len-1; i>-1; i--){
            if (coef[i] > var.coef[i])
            {
                return false;
            }
            if (coef[i] < var.coef[i])
            {
                return true;
            }
        }
        return false;
    }
    
    bool operator > (const BN& var){
        if(len > var.len){
            return true;
        }
        if(len < var.len){
            return false;
        }
        for(int i = len-1; i>-1; i--){
            if (coef[i] < var.coef[i])
            {
                return false;
            }
            if (coef[i] > var.coef[i])
            {
                return true;
            }
        }
        return false;
    }
    bool operator >= (const BN& var){
        if(len > var.len){
            return true;
        }
        if(len < var.len){
            return false;
        }
        for(int i = len-1; i>-1; i--){
            if (coef[i] < var.coef[i])
            {
                return false;
            }
            if (coef[i] > var.coef[i])
            {
                return true;
            }
        }
        return true;
    }
    
    bool operator <= (const BN& var){
        if(len < var.len){
            return true;
        }
        if(len > var.len){
            return false;
        }
        for(int i = len-1; i>-1; i--){
            if (coef[i] > var.coef[i])
            {
                return false;
            }
            if (coef[i] < var.coef[i])
            {
                return true;
            }
        }
        return true;
    }
    
    BN operator + (const BASE& var) {
        BN res(*this);
        DBASE tmp = (DBASE)res.coef[0] + (DBASE)var;
        res.coef[0] = (BASE)tmp;
        BASE k = (BASE)(tmp >> BASE_SIZE);
        int j = 1;
        
        for (;j < res.len; j++) {
            tmp = (DBASE)res.coef[0] + (DBASE)k;
            res.coef[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
        }
        
        res.coef[j] = k;
        while (res.len > 1 && res.coef[res.len - 1] == 0) {
            res.len--;
        }
        return res;
    }
    
    BN operator + (const BN& var) {
        int maxl = max(len, var.len) + 1;
        int mint = min(len, var.len);
        BN res;
        delete[] res.coef;
        res.coef = new BASE[maxl];
        res.maxlen = maxl;
        
        DBASE tmp;
        int k = 0; // разряд переноса
        int j = 0;
        
        for(j = 0; j < mint; j++){
            tmp = (DBASE)coef[j] + (DBASE)var.coef[j] + k;
            res.coef[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
        }
        for(; j < len; j++){
            tmp = coef[j] + k;
            res.coef[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
        }
        for(; j < var.len; j++){
            tmp = (DBASE)var.coef[j] + (DBASE)k;
            res.coef[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
        }
        if (k > 0){
            res.coef[j++] = k;
        }
        res.len = j;
        return res;
    }
    
    BN operator += (const BN& var) {
        *this = *this + var;
        return *this;
    }
    
    BN operator - (const BN& var) {
        if (*this < var) {
            cerr << "Error";
        }
        int maxl = max(len, var.len);
        BN res;
        delete[] res.coef;
        res.coef = new BASE[maxl];
        res.maxlen = maxl;
        res.len = maxl;
        
        DBASE tmp;
        int k = 0; //займ
        int j = 0;
        
        for (j = 0; j < var.len; j++){
            tmp = ((DBASE)1 << BASE_SIZE) | (DBASE)coef[j];
            tmp -= (DBASE)var.coef[j] + k;
            res.coef[j] = (BASE)tmp;
            k = !(tmp >> BASE_SIZE);
        }
        for (; j < len; j++){
            tmp = ((DBASE)1 << BASE_SIZE) | (DBASE)coef[j];
            tmp -= k;
            res.coef[j] = (BASE)tmp;
            k = !(tmp >> BASE_SIZE);
        }
        res.len = len;
        while (res.len > 1 && res.coef[res.len - 1] == 0) {
            res.len--;
        }
        return res;
    }
    
    BN operator - (const BASE& var) {
        BN res;
        delete[] res.coef;
        res.maxlen = maxlen;
        res.coef = new BASE[res.maxlen];
        fill(res.coef, res.coef + res.maxlen, 0);
        
        DBASE tmp = (((DBASE)1 ) << BASE_SIZE) + coef[0];
        tmp -= var;
        res.coef[0] = (BASE)tmp;
        int k = !(tmp >> BASE_SIZE);
        int i = 1;
        for (; i < len; i++) {
            tmp = ((DBASE)1 << BASE_SIZE) + coef[i] - k;
            res.coef[i] = (BASE)tmp;
            k = !(tmp >> BASE_SIZE);
            res.coef[i] = coef[i];
        }
        res.len = len;
        while (res.len > 1 && res.coef[res.len - 1] == 0) res.len--;
        return res;
    }
    
    BN operator -= (const BN& var) {
        *this = *this - var;
        return *this;
    }
    
    BN operator * (const BASE& var) {
        DBASE tmp;
        int maxl = len + 1;
        int j = 0;
        BASE k = 0;
        BN res;
        delete[] res.coef;
        res.coef = new BASE[maxl];
        fill(res.coef, res.coef + maxl, 0); 
        res.maxlen = maxl;
        
        for (; j < len; j++) {
            tmp = (DBASE)coef[j] * (DBASE)var + (DBASE)k;
            res.coef[j] = (BASE)tmp;
            k = (BASE)(tmp >> BASE_SIZE);
        }
        res.coef[j] = k;
        res.len = maxl;
        
        while (res.len > 1 && res.coef[res.len - 1] == 0) {
            res.len--;
        }
        return res;
    }
    
    BN operator *= (const BASE& var) {
        *this = *this * var;
        return *this;
    }
    
    BN operator * (const BN& var) { // Умножение на БЧ
        int j = 0;
        DBASE tmp;
        int maxl = len + var.len;
        BN res;
        delete[] res.coef;
        res.coef = new BASE[maxl];
        fill(res.coef, res.coef + maxl, 0);
        res.maxlen = maxl;
        
        for (; j < var.len; j++) {
            if (var.coef[j] != 0) {
                int i = 0;
                BASE k = 0;
                for (; i < len; i++) {
                    tmp = ((DBASE)coef[i] * (DBASE)var.coef[j] + (DBASE)res.coef[i+j] + (DBASE)k);
                    res.coef[i+j] = (BASE)tmp;
                    k = (BASE)(tmp >> BASE_SIZE);
                }
                res.coef[len+j] = k;
            }
        }
        res.len = len + var.len;
        while (res.len > 1 && res.coef[res.len - 1] == 0) {
            res.len--;
        }
        return res;
    }
    
    BN operator / (const BASE& var) { // Деление на число
        int j = 0;
        BASE r = 0;
        DBASE tmp;
        int maxl = len;
        BN res;
        delete[] res.coef;
        res.coef = new BASE[maxl];
        fill(res.coef, res.coef + maxl, 0); 
        res.maxlen = maxl;
        
        for(;j < len; j++) {
            tmp = (((DBASE)r << BASE_SIZE) + (DBASE)coef[len-1-j]);
            res.coef[len-1-j] = (BASE)(tmp/(DBASE)var);
            r = (BASE)(tmp%(DBASE)var);
        }
        res.len = len;
        while (res.len > 1 && res.coef[res.len - 1] == 0) {
            res.len--;
        }
        return res;
    }
    
    BN operator % (const BASE& var) {
        if (var == 0) {
            cerr << "Error" << endl;
            exit(1);
        }
        DBASE tmp;
        int j = 0;
        BASE r = 0;
        for (; j < len; j++) {
            tmp = ((DBASE)r << BASE_SIZE) + coef[len-1-j];
            r = (BASE)(tmp % var);
        }
        BN res(1,0);
        res.coef[0] = r;
        res.len = 1;
        return res;
    }
    
    BN operator / (BN& var) { // Деление на БЧ
        if (var.len == 1 && var.coef[0] == 0) {
            throw invalid_argument("деление на нуль");
        }
        if (*this < var) {
            BN zero;
            return zero;
        }
        if (*this == var) {
            BN one;
            delete[] one.coef;
            one.coef = new BASE[1];
            one.maxlen = 1;
            one.coef[0] = 1;
            one.len = 1;
            return one;
        }
        if (var.len == 1) {
            return *this / var.coef[0];
        }
        int m = len - var.len;
        DBASE b = ((DBASE)1 << BASE_SIZE);
        
        DBASE d = b / ((DBASE)var.coef[var.len - 1] + 1);
        
        BN u = *this;
        u *= (BASE)d;
        
        BN v = var;
        v *= (BASE)d;
        
        if (u.len == len) {
            BASE* new_coef = new BASE[u.len + 1];
            memcpy(new_coef, u.coef, u.len * sizeof(BASE));
            new_coef[u.len] = 0;
            delete[] u.coef;
            u.coef = new_coef;
            u.len++;
            u.maxlen = u.len;
        }
        
        BN q;
        delete[] q.coef;
        q.coef = new BASE[m + 1];
        q.maxlen = m + 1;
        q.len = m + 1;
        fill(q.coef, q.coef + q.len, 0);
        
        for (int j = m; j >= 0; j--) {
            DBASE qhat;
            DBASE rhat;
            
            DBASE dividend = ((DBASE)u.coef[j + var.len] << BASE_SIZE) + u.coef[j + var.len - 1];
            qhat = dividend / v.coef[v.len - 1];
            rhat = dividend % v.coef[v.len - 1];
            
            while (qhat >= b || 
                   (var.len > 1 && qhat * v.coef[v.len - 2] > (rhat << BASE_SIZE) + u.coef[j + var.len - 2])) {
                qhat--;
                rhat += v.coef[v.len - 1];
                if (rhat >= b) break;
            }
            
            DBASE k = 0;
            DBASE t;
            
            for(int i = 0; i < v.len; i++) {
                DBASE p = qhat * v.coef[i] + k;
                k = p >> BASE_SIZE;
                p &= ((DBASE)1 << BASE_SIZE) - 1;
                
                if (u.coef[j + i] >= p) {
                    u.coef[j + i] -= (BASE)p;
                } else {
                    u.coef[j + i] = (BASE)((((DBASE)1 << BASE_SIZE) + u.coef[j + i]) - p);
                    k++;
                }
            }
            
            if (k > u.coef[j + v.len]) {
                qhat--;
                BASE carry = 0;
                for (int i = 0; i < v.len; i++) {
                    DBASE sum = (DBASE)u.coef[j + i] + v.coef[i] + carry;
                    u.coef[j + i] = (BASE)sum;
                    carry = (BASE)(sum >> BASE_SIZE);
                }
                u.coef[j + v.len] += carry;
            } else {
                u.coef[j + v.len] -= (BASE)k;
            }
            
            q.coef[j] = (BASE)qhat;
        }
        
        // нормализация результата
        while (q.len > 1 && q.coef[q.len - 1] == 0) {
            q.len--;
        }
        
        return q;
    }
    
    BN operator % ( BN& var) {
        if (var.len == 1 && var.coef[0] == 0) {
            throw invalid_argument("деление на нуль");
        }
        BN quotient = *this / var;
        BN product = quotient * var;
        return *this - product;
    }
    
    void vvod_10() {
        string s;
        cin >> s;
        
        for (char c : s) {
            if (!isdigit(c)) {
                cerr << "Error" << endl;
                exit(1);
            }
        }
    
        len = 1;
        delete[] coef;
        coef = new BASE[1]();
        maxlen = 1;
        coef[0] = 0;
    
        
        for (char c : s) {
            BASE k = c - '0';
            
            for (int i = 0; i < len; i++) {
                DBASE tmp = (DBASE)coef[i] * 10 + k;
                coef[i] = (BASE)tmp;
                k = (BASE)(tmp >> BASE_SIZE);
            }
    
            
            if (k > 0) {
                if (len == maxlen) {
                    
                    BASE* new_coef = new BASE[maxlen + 1]();
                    copy(coef, coef + len, new_coef);
                    delete[] coef;
                    coef = new_coef;
                    maxlen++;
                }
                coef[len++] = k;
            }
        }
    }
    
    void vyvod_10() {
        if (len == 0 || (len == 1 && coef[0] == 0)) {
            cout << "0\n";
            return;
        }
    
        int tmp_len = len;
        BASE* tmp = new BASE[tmp_len];
        memcpy(tmp, coef, tmp_len * sizeof(BASE));
    
        string result;
        bool f = true;
    
        while (f) {
            DBASE t = 0;
            f = false;
    
            
            for (int i = tmp_len - 1; i >= 0; i--) {
                DBASE var = (t << BASE_SIZE) | tmp[i];
                tmp[i] = (BASE)(var / 10);
                t = var % 10;
                
                if (tmp[i] != 0) {
                    f = true;
                }
            }
    
            result += (char)('0' + t);
    
            while (tmp_len > 1 && tmp[tmp_len - 1] == 0) {
                tmp_len--;
            }
        }
    
        delete[] tmp;
    
        reverse(result.begin(), result.end());
        cout << result << endl;
    }
    
    friend istream& operator>>(istream& is, BN& num) {
        string s;
        is >> s;
        int len = (s.length()-1)/(BASE_SIZE/4)+1;
        int maxlen = len;
        
        // delete[] num.coef;
        // fill(num.coef, num.coef + maxlen,0);
        
        int j = 0;
        int k = 0;
        BASE tmp = 0;
        for (int i = s.length()-1; i >= 0; i--){
            if ('0' <= s[i] && s[i] <= '9')
                tmp |= (BASE)(s[i] - '0')<<k;
            else if ('a' <= s[i] && s[i] <= 'f')
                tmp |= (BASE)(s[i] - 'a' + 10)<<k;
            else if ('A' <= s[i] && s[i] <= 'F')
                tmp |= (BASE)(s[i] - 'A' + 10)<<k;
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
            num.coef[j++] = tmp;
        }
        num.len = j;
        while (num.len > 1 && num.coef[num.len - 1] == 0) {
            num.len--;
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const BN& num) {
        os << "BN: ";
        for (int i = num.len - 1; i >= 0; i--) {
            os.width(BASE_SIZE/4);
            os.fill('0');
            os << hex << (int)num.coef[i];
            if(i > 0) os << " ";
        }
        return os;
    }
};

void test() {
    const int max_length = 1000;
    int N = 1000;
    do {
        int len_A = rand() % max_length + 1;
        int len_D = rand() % max_length + 1;
        
        
        BN A(len_A, true); // случайное число размера len_A
        BN D(len_D, true); // случайное число размера len_D
        
        
        if (D == BN()) continue; // защита от деления на ноль
        
        
        BN Q = A / D;
        BN R = A % D;
        
        
        // Проверка условий: A == Q*D + R и R < D
        if (!(A == Q * D + R && R < D)) {
            cout << "Ошибка при тестировании деления!" << endl;
            cout << "A: " << A << "\nD: " << D << "\nQ: " << Q << "\nR: " << R << endl;
            break;
        }
    } while (--N);
    
    if (N == 0) {
        cout << "Тестирование успешно завершено!" << endl;
    }
}
int main()
{
    srand(time(0)); 
    test();
    // cout << "конструктор 1: ";
    // BN a1;
    // cout << "\n";
    // int n;
    // bool mode;
    // cout << "Введите n и mode: " << endl;
    // cin >> n;
    // cin >> mode;

    // cout << "рандом-конструктор a2: ";
    // BN a2(n, mode); 

    // cout << "конструктор копирования: \n";
    // BN a3(a2); 
    // cout << a3; 

    // cout << "\n оператор присваивания: \n";
    // BN a4;
    // a4 = a2; 
    // cout << a4; 
    
    // cout << "\n оператор == : \n";
    // if (a4 == a2)
    //     cout << "yes" << endl;
    // else
    //     cout << "no" << endl;
    // cout << "\n оператор >= : \n";
    // if (a4 >= a2)
    //     cout << "yes" << endl;
    // else 
    //     cout << "no" << endl;
    // cout << "\n оператор > : \n";
    // if (a4 > a2)
    //     cout << "yes" << endl;
    // else 
    //     cout << "no" << endl;
    
    // cout << "Сумма b & s: \n" << "n and mode: \n";

    // BN b(5,1);
    // BN s(4,1);
    // cout << "\n"<< "b: " << b << endl;
    // cout << "s: " << s << endl;
    // BN res = b + s;
    // cout << res << endl;
    
    // cout << "Сумма b & 7: \n";
    // BN sum = b + 7;
    // cout << sum << endl;
    
    // cout << "Разность b & s: \n";
    // cout << res - s << endl;
        
    // cout << "\n HEX-ввод: \n";
    // BN a5;
    // cin >> a5;
    
    // cout << "Hex-вывод: " << a5;
    
    // cout << "\n Умножение(BASE) a2 * 3: ";
    // BN mult2 = a2 * 3;
    // cout << mult2 << endl;
    
    // cout << "\n Умножение(BN) a2 * a2: ";
    // BN mult3 = a2 * a3;
    // cout << mult3 << endl;
    
    // cout << "\n Деление(BASE) mult(BN) / 2: ";
    // BN del = mult3 / 2;
    // cout << del << endl;
    
    // cout << "\n Деление(BASE) mult(BN) % 2: ";
    // BN r = mult3 % 2;
    // cout << r << endl;
    
    // BN c;
    // cout << "\n Dec-ввод: ";
    // c.vvod_10();
    
    // cout << "\n Dec-вывод: ";
    // c.vyvod_10();
    return 0;
}
