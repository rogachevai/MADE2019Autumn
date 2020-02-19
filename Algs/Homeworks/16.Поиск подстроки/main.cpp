/*
Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
p <= 30000, n <= 300000.
Использовать один из методов:

- С помощью префикс-функции;
 */
#include <iostream>
#include <vector>
#include <assert.h>


using namespace std;

vector<size_t> prefixFuntionPi (const string & pattern) { //Сама функция Pi.
    vector<size_t> pi(pattern.length());
    pi[0] = 0;
    int l=pattern.length();
    for (int i = 1; i < l; i++) {
        size_t j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        } if (pattern[i] == pattern[j]) {
            pi[i] = j + 1;
        } else {
            pi[i] = 0;
        }
    } return pi;
}

vector<size_t> count (const string & pattern, const string & str, vector<size_t> pi){ //Подсчет Pi для каждого символа в строке
    vector<size_t> entries;
    size_t prevPi = 0;
    for (size_t i = 0; i < str.size(); i++) {
        size_t j = prevPi;
        while (j > 0 && str[i] != pattern[j]) {
            j = pi[j - 1];
        } if (str[i] == pattern[j]) {
            j++;
        } else {
            j = 0;
        } if (j == pattern.length()) { //Если Pi равна длине шаблона, то мы нашли вхождение
            entries.push_back(i - pattern.length() + 1);
        } prevPi = j;
    } return entries;
}

vector<size_t> find (const string & pattern, const string & str) {
    vector<size_t> pi(pattern.length());
    pi = prefixFuntionPi (pattern);
    vector<size_t> res=count( pattern,  str, pi);
    return res;
}

int main() {
    string pattern, str;
    cin >> pattern>> str;
//    assert( pattern.length()<30001);
//    assert( str.length()<30001);
    vector<size_t> entries = find(pattern, str);
    for (size_t i : entries) {
        cout << i <<" ";
    }
    return 0;
}