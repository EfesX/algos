#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <unordered_map>
#include <cstdint>
#include <string>

// Максимальное количество символов для обработки
#define MAXSYMBOLS  200000
// Максимальное количество бит (из расчета 8 бит на символ)
#define MAXBITS     (MAXSYMBOLS * 8)
// Начальная длина кода в битах
#define BITLEN_INIT 5

using namespace std;

// Структура для работы с битовыми последовательностями
struct bithandler_t 
{
    bitset<MAXBITS> bs;  // Битовый массив для хранения данных
    int head;            // Указатель на текущую позицию записи
    int tail;            // Указатель на текущую позицию чтения

    // Конструктор - инициализирует все нулями
    bithandler_t() : bs(0), head(0), tail(0){}

    // Добавление кода заданной длины в битовый массив
    void append(int len, uint32_t code)
    {
        bitset<32> bsc(code);  // Преобразуем число в битовый набор
        for(int i = 0; i < len; i++)
            bs[head++] = bsc[i];  // Записываем биты один за другим
    }

    // Преобразование битового массива в вектор байтов
    vector<uint8_t> compress() 
    {
        vector<uint8_t> res;
        // Обрабатываем биты по 8 (1 байт) за раз
        for(int i = 0; i < head; i += 8)
        {
            bitset<8> byte;
            for(int j = 0; j < 8; j++)
                byte[j] = bs[i + j];  // Заполняем байт

            // Преобразуем биты в число и добавляем в результат
            res.emplace_back(static_cast<uint8_t>(byte.to_ulong()));
        }
        return res;
    }

    // Извлечение кода заданной длины из битового массива
    uint32_t get_code(int len)
    {
        bitset<32> res;
        for(int i = 0; i < len; i++)
            res[i] = bs[tail + i];  // Читаем биты один за другим
        tail += len;  // Сдвигаем указатель чтения
        return static_cast<uint32_t>(res.to_ulong());  // Преобразуем в число
    }

    // Проверка, пуст ли битовый массив для чтения
    bool is_empty(){ return tail > head - 1; }
};

// Функция сжатия строки с использованием алгоритма LZW
vector<uint8_t> lzw_pack(const string& text)
{
    // Инициализация словаря стандартными символами
    unordered_map<string, uint32_t> dict;
    for(int i = 1; i <= 26; i++)
        dict[string{static_cast<char>('a' + i - 1)}] = i;
    dict[string{'-'}] = 0;  // Специальный символ
    
    bithandler_t bw;  // Обработчик битов
    string word;      // Текущее накапливаемое слово
    uint32_t curr_len = BITLEN_INIT;  // Текущая длина кода в битах
    // Максимально возможный размер словаря с текущей длиной кода
    uint32_t dict_max_size = (1 << curr_len);  

    for(size_t i = 0; i < text.size(); i++)
    {
        const char& sym = text[i];  // Текущий символ

        // Если слово + символ есть в словаре, продолжаем накапливать
        if(dict.count(string(word + sym)))
        {
            word += sym;
        } 
        else 
        {
            // Добавляем код слова в битовый поток
            bw.append(curr_len, dict[word]);
            // Добавляем новое слово в словарь
            dict[word + sym] = dict.size();
            word = sym;  // Начинаем новое слово с текущего символа
        }

        // Если словарь заполнен, увеличиваем длину кода
        while(dict.size() > dict_max_size - 1)
        {
            dict_max_size = dict_max_size << 1;
            curr_len++;
        }
    }

    // Добавляем последнее слово
    bw.append(curr_len, dict[word]);
    // Возвращаем сжатые данные в виде байтов
    return bw.compress();
}

// Функция распаковки строки, сжатой алгоритмом LZW
string lzw_unpack(const vector<uint8_t>& packed_text)
{
    // Инициализация словаря стандартными символами
    unordered_map<uint32_t, string> dict;
    for(int i = 1; i <= 26; i++)
        dict[i] = static_cast<char>('a' + i - 1);
    dict[0] = '-';  // Специальный символ
            
    bithandler_t bw;
    // Загружаем все байты в битовый обработчик
    for(auto byte : packed_text)
        bw.append(8, byte);

    uint32_t curr_len = BITLEN_INIT;  // Текущая длина кода в битах
    // Максимально возможный размер словаря с текущей длиной кода
    uint32_t dict_max_size = (1 << curr_len);

    // Читаем первое слово
    string word;
    word += dict[bw.get_code(curr_len)];

    string result;  // Результирующая строка
    string entry;   // Временная переменная для новых записей

    result += word;

    // Пока есть данные для чтения
    while(bw.is_empty() == false)
    {
        // Читаем текущий код
        uint32_t curr_code = bw.get_code(curr_len);

        if(curr_code == 0) break;  // Код 0 - конец данных

        // Обработка кода в зависимости от его наличия в словаре
        if(dict.count(curr_code))
            entry = dict[curr_code];
        else if(curr_code == dict.size())
            entry = word + word[0];  // Специальный случай для LZW
        else 
            throw runtime_error(
                "bad compression code: " + to_string(curr_code)
            );

        // Добавляем найденную строку в результат
        result += entry;
        // Добавляем новую комбинацию в словарь
        dict[dict.size()] = word + entry[0];
        word = entry;  // Обновляем текущее слово

        // Если словарь заполнен, увеличиваем длину кода
        while(dict.size() >= dict_max_size - 1)
        {
            dict_max_size = dict_max_size << 1;
            curr_len++;
        }
    }

    return result;
}

// Главная функция программы
int main()
{
    string cmd;
    cin >> cmd;  // Читаем команду (pack/unpack)

    if(cmd == "pack")  // Режим сжатия
    {
        string text;
        cin >> text;  // Читаем строку для сжатия

        vector<uint8_t> result = lzw_pack(text);  // Сжимаем

        // Выводим размер и сами данные
        cout << result.size() << endl;
        copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    } 
    else if(cmd == "unpack")  // Режим распаковки
    {
        int sz;
        cin >> sz;  // Читаем размер сжатых данных

        vector<uint8_t> packed_text(sz);
        // Читаем сжатые данные
        copy_n(istream_iterator<int>(cin), sz, begin(packed_text));

        // Распаковываем и выводим результат
        cout << lzw_unpack(packed_text) << endl;
    }

    return 0;
}