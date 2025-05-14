#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <algorithm>
#include <sstream>

using namespace std;

// Максимальный размер битовой последовательности
constexpr int MAXBITS = 131072; 

// Функция для кодирования строки с использованием кода Хэмминга
string hamming_encode(const string& str) 
{
    bitset<MAXBITS> bs(0);      // Битовый набор для хранения закодированных данных
    unordered_set<int> powers;  // Множество позиций контрольных бит (степени двойки - 1)

    // Находим все позиции контрольных бит (1, 2, 4, 8, ... - 1)
    size_t maxpow = 1;
    while (maxpow <= str.size()) {
        powers.emplace(maxpow - 1); // Добавляем позицию (индексация с 0)
        maxpow = (maxpow << 1);     // Умножаем на 2 (сдвиг влево)
    }

    // Заполняем битовый набор данными, пропуская контрольные биты
    int pos = 0; // Начинаем с позиции 0
    for (size_t i = 0; i < str.size(); i++) 
    {
        int bit = str[str.size() - i - 1] == '1' ? 1 : 0; // Читаем биты строки в обратном порядке
        while (powers.count(pos)) pos++;                  // Пропускаем позиции контрольных бит
        bs[pos++] = bit;                                  // Устанавливаем бит данных
    }

    // Копируем степени двойки в вектор и сортируем для удобства
    vector<int> powers_v(powers.size());
    copy(begin(powers), end(powers), begin(powers_v));
    sort(powers_v.begin(), powers_v.end());

    // Вычисляем значения контрольных бит
    for (size_t i = 0; i < powers_v.size(); i++) 
    {
        const int& pwr = powers_v[i]; // Позиция текущего контрольного бита

        // Проходим по всем битам данных и вычисляем XOR для контрольного бита
        for (size_t j = 0; j < str.size() + powers.size(); j++) 
        {
            if (powers.count(j)) continue; // Пропускаем другие контрольные биты
            
            bitset<32> bsi(j + 1); // Представляем позицию бита в бинарном виде

            // Если i-й бит в позиции j+1 установлен, то XOR с текущим битом данных
            if (bsi[i]) bs[pwr] = bs[pwr] ^ bs[j];
        }
    }

    // Формируем результат, включая контрольные биты
    string res;
    for (--pos; pos >= 0; pos--) // Идём в обратном порядке для правильного вывода
        res += bs[pos] ? '1' : '0';
    
    return res;
}

// Функция для декодирования строки с исправлением ошибок
string hamming_decode(const string& str) 
{
    bitset<MAXBITS> bs(str);   // Битовый набор для хранения принятых данных
    unordered_set<int> powers; // Множество позиций контрольных бит

    // Находим все позиции контрольных бит (1, 2, 4, 8, ... - 1)
    size_t power = 1;
    while (power < str.size()) {
        powers.emplace(power - 1);
        power = power << 1;
    }

    // Копируем степени двойки в вектор и сортируем
    vector<int> powers_v(powers.size());
    copy(begin(powers), end(powers), begin(powers_v));
    sort(powers_v.begin(), powers_v.end());

    // Вычисляем синдром ошибки
    bitset<32> sindrome; // Будет содержать биты синдрома

    for (size_t i = 0; i < powers_v.size(); i++) 
    {
        const int& pwr = powers_v[i]; // Позиция текущего контрольного бита

        int bit = 0; // Вычисляемое значение для синдрома

        // Проходим по всем битам данных и вычисляем XOR
        for (size_t j = 0; j < str.size(); j++) 
        {
            if (powers.count(j)) continue; // Пропускаем другие контрольные биты
            
            bitset<32> bsi(j + 1); // Позиция бита в бинарном виде
            if (!bsi[i]) continue; // Нас интересуют только биты, где i-й бит установлен
            
            bit = bit ^ bs[j]; // XOR с текущим битом данных
        }
        // Сравниваем вычисленный бит с контрольным битом
        sindrome[i] = !(bit == bs[pwr]); // Инвертируем, так как ищем несовпадение
    }

    // Если синдром не нулевой, исправляем ошибку
    if (sindrome.to_ulong() != 0)
        // Инвертируем бит в ошибочной позиции (индексация с 0)
        bs[sindrome.to_ulong() - 1] = !bs[sindrome.to_ulong() - 1];

    // Извлекаем исходные данные, исключая контрольные биты
    ostringstream res;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (powers.count(i)) continue; // Пропускаем контрольные биты
        res << bs[i];                  // Добавляем биты данных
    }

    return res.str();
}

int main() 
{
    int nlaunch;
    string str;
    cin >> nlaunch >> str;
    string res = nlaunch == 1 ? hamming_encode(str) : hamming_decode(str);
    cout << res << endl;
    
    return 0;
}
