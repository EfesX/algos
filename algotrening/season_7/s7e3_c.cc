#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iterator>
#include <numeric>

using namespace std;

// Количество битов в uint64_t (обычно 64)
const int N_BITS = sizeof(uint64_t) * 8;

// Функция для заполнения массива чисел и анализа их битового представления
inline pair<int,uint64_t> fill_array(vector<uint64_t>& arr){
    int highest_one = 0;       // Наивысший установленный бит среди всех чисел
    uint64_t total_ones = 0;   // Общее количество единичных битов во всех числах

    for (uint64_t i = 0; i < arr.size(); i++) {
        cin >> arr[i];  // Читаем очередное число

        // Создаем битовое представление числа
        auto bs = bitset<N_BITS>(arr[i]);
        // Увеличиваем счетчик единичных битов
        total_ones += bs.count();
        
        // Ищем наивысший установленный бит в текущем числе
        for (int j = N_BITS - 1; j >= 0; j--) {
            if (bs.test(j)) {
                highest_one = max(highest_one, j);
                break;  // После нахождения старшего бита выходим
            }
        }
    }

    return {highest_one, total_ones};
}

// Функция вывода сообщения "impossible" и завершения программы
void impossible(){
    cout << "impossible" << endl;
    exit(EXIT_SUCCESS);
}

// Функция для нахождения позиций первых двух установленных битов в битовом наборе
inline pair<int,int> find_pair_bits(const bitset<N_BITS>& bs)
{
    // Позиции битов (инициализированы -1)
    int bit1 = -1, bit2 = -1;

    for (int i = 0; i < N_BITS; i++) {
        if(!bs.test(i)) continue;

        // Если бит установлен
        if (bit1 == -1) {
            bit1 = i;  // Первый найденный бит
        } else {
            bit2 = i;  // Второй найденный бит
            break;      // Выходим после нахождения пары
        }
    }
    return { bit1, bit2 };
}

int main() 
{
    // Читаем количество чисел
    int n; cin >> n;

    // Заполняем массив и получаем информацию о битах
    vector<uint64_t> arr(n);
    auto [highest_one, total_ones] = fill_array(arr);

    // Если общее количество единичных битов нечетное - решение невозможно
    if (total_ones % 2 != 0)
        impossible();

    // Лямбда-функция для вычисления общего XOR всех чисел в массиве
    auto get_total_xor = [](const vector<uint64_t>& arr) {
        return accumulate(arr.begin(), arr.end(), uint64_t{0}, [](auto a, auto b) {
            return a ^ b;  // Накопление XOR
        });
    };

    // Лямбда-функция для "переворачивания" битов в числах
    // нулевой и первый отличающийся от нулевого
    auto flip_bits = [&highest_one](vector<uint64_t>& arr){
        for(int i = 0; i < arr.size(); i++)
        {
            auto bs = bitset<64>(arr[i]);

            // Пропускаем числа без единичных битов или со всеми битами установленными
            if(bs.count() == 0) continue;
            if(bs.count() == highest_one + 1) continue;

            uint64_t mask = 1;  // Начинаем с младшего бита

            // Ищем первый бит, отличающийся от младшего бита
            for(int k = 0; k < 64; k++)
            {
                if(bs.test(k) != bs[0])
                {
                    // Создаем маску для XOR
                    mask |= (1ULL << k);  
                    break;
                }
            }

            arr[i] ^= mask;  // Применяем маску
            return true;     // Успешно выполнили операцию
        }
        return false;  // Не смогли выполнить операцию
    };

    // Основной цикл алгоритма
    while (true) 
    {
        uint64_t total_xor = get_total_xor(arr);
        // Если в XOR остался 0 или 1 бит - завершаем цикл
        if (bitset<N_BITS>(total_xor).count() <= 1)
            break;

        // Находим позиции первых двух установленных битов в XOR
        auto [bit1, bit2] = find_pair_bits(total_xor);
        if (bit1 == -1 || bit2 == -1) break;

        // Флаг успешного выполнения операции
        bool is_done = false;  

        // Пытаемся найти число, где эти два бита различаются
        for (int i = 0; i < arr.size(); i++) 
        {
            bool b1 = arr[i] & (1ULL << bit1);  // Проверяем bit1
            bool b2 = arr[i] & (1ULL << bit2);  // Проверяем bit2

            if (b1 != b2) 
            {
                // Инвертируем оба бита
                arr[i] ^= ((1ULL << bit1) | (1ULL << bit2));
                // Выходим после успешной операции
                is_done = true;
                break;  
            }
        }

        // Если не нашли подходящее число, пробуем flip_bits
        if (!is_done && !flip_bits(arr))
            // Если flip_bits тоже не помог - решение невозможно
            impossible();  
    }

    // Проверяем, что итоговый XOR равен 0
    uint64_t total_xor = get_total_xor(arr);
    if (total_xor) impossible();

    // Выводим результат
    copy(arr.begin(), arr.end(), ostream_iterator<uint64_t>(cout, " "));
    cout << endl;

    return 0;
}
