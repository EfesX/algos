#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdint>

using namespace std;

// Константы для хеширования:
// P - основание хеша (простое число)
// MOD - модуль для предотвращения переполнения
constexpr int P = 31;
constexpr int MOD = 1e9 + 7;

// Структура узла дерева отрезков
struct node_t {
    uint64_t hash;    // Значение хеша для отрезка
    int lazy;         // Отложенное значение для обновления
    bool has_lazy;    // Флаг наличия отложенного обновления
    int length;       // Длина отрезка, который покрывает узел

    node_t() : 
        hash(0), 
        lazy(0), 
        has_lazy(false), 
        length(0) 
    {}
};

// Класс дерева отрезков с поддержкой хешей и отложенных обновлений
class segtree_t {
private:
    int sz;                // Размер исходного массива
    vector<node_t> tree;   // Данные дерева отрезков
    vector<uint64_t> powers;         // Массив степеней P: powers[i] = P^i % MOD
    vector<uint64_t> prefix_powers;  // Массив префиксных сумм степеней P: prefix_powers[i] = (1 + P + P^2 + ... + P^i) % MOD

    // Рекурсивная функция построения дерева
    inline void build(int v, int tl, int tr, const vector<int>& arr) {
        tree[v].length = tr - tl + 1;
        
        // Если достигли листа - сохраняем значение элемента
        if (tl == tr) {
            tree[v].hash = arr[tl] % MOD;
            return;
        }

        int tm = (tl + tr) >> 1;  // Середина отрезка

        // Рекурсивно строим левое и правое поддерево
        build(2*v,     tl,   tm, arr);
        build(2*v+1, tm+1, tr, arr);

        // Объединяем хеши детей: hash = left_hash * P^right_length + right_hash
        tree[v].hash = (
            tree[2*v].hash * powers[tree[2*v+1].length] + 
            tree[2*v+1].hash
        ) % MOD;
    }

    // Проталкивание отложенного обновления в детей
    inline void push(int v, int tl, int tr) {
        if (!tree[v].has_lazy)
            return;

        // Если узел не лист, передаем отложенное обновление детям
        if (tl != tr) {
            // Устанавливаем отложенное обновление для левого ребенка
            tree[2*v].lazy = tree[v].lazy;
            tree[2*v].has_lazy = true;
            // Хеш отрезка из одинаковых элементов: val * (1 + P + P^2 + ... + P^(len-1))
            tree[2*v].hash = tree[v].lazy * prefix_powers[tree[2*v].length - 1] % MOD;
            
            // Аналогично для правого ребенка
            tree[2*v+1].lazy = tree[v].lazy;
            tree[2*v+1].has_lazy = true;
            tree[2*v+1].hash = tree[v].lazy * prefix_powers[tree[2*v+1].length - 1] % MOD;
        }

        // Сбрасываем флаг отложенного обновления
        tree[v].has_lazy = false;
    }

    // Получение хеша для отрезка [l, r]
    inline uint64_t get_hash(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;  // Пустой отрезок

        // Если текущий отрезок полностью входит в запрашиваемый
        if (l == tl && r == tr)
            return tree[v].hash;

        // Перед обработкой детей проталкиваем отложенные обновления
        push(v, tl, tr);

        int tm = (tl + tr) >> 1;  // Середина отрезка

        // Рекурсивно получаем хеши для левой и правой частей
        uint64_t left_hash  = get_hash(2*v,   tl,   tm,            l, min(r, tm));
        uint64_t right_hash = get_hash(2*v+1, tm+1, tr, max(l, tm+1),          r);

        // Длина правой части отрезка
        int right_len = max(0, r - tm);

        // Объединяем хеши: left_hash * P^right_len + right_hash
        return (left_hash * powers[right_len] + right_hash) % MOD;
    }

    // Обновление отрезка [l, r] значением val
    void update_range(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) return;

        // Если текущий отрезок полностью входит в обновляемый
        if (l == tl && r == tr) {
            // Устанавливаем отложенное обновление
            tree[v].lazy = val;
            tree[v].has_lazy = true;
            // Хеш отрезка из одинаковых элементов: val * (1 + P + P^2 + ... + P^(len-1))
            tree[v].hash = val * prefix_powers[tree[v].length - 1] % MOD;
            return;
        }

        // Перед обработкой детей проталкиваем отложенные обновления
        push(v, tl, tr);

        int tm = (tl + tr) / 2;

        // Рекурсивно обновляем левую и правую части
        update_range(2*v,     tl,   tm,          l, min(r, tm), val);
        update_range(2*v+1, tm+1, tr, max(l, tm+1),       r, val);
        
        // Пересчитываем хеш текущего узла после обновления детей
        tree[v].hash = (tree[2*v].hash * powers[tree[2*v+1].length] + tree[2*v+1].hash) % MOD;
    }

public:
    // Конструктор - инициализирует дерево отрезков для массива arr
    segtree_t(const vector<int>& arr) :
        sz(arr.size()),              // Размер массива
        tree(sz << 2),               // Дерево размером 4*sz
        powers(sz + 1),              // Массив степеней P
        prefix_powers(sz + 1)        // Массив префиксных сумм степеней P
    {
        // Предварительно вычисляем степени P и их префиксные суммы
        powers[0] = 1;
        prefix_powers[0] = 1;

        for (int i = 1; i <= sz; ++i) {
            powers[i] = (powers[i - 1] * P) % MOD;
            prefix_powers[i] = (prefix_powers[i - 1] + powers[i]) % MOD;
        }

        // Строим дерево отрезков
        build(1, 0, sz - 1, arr);
    }
    
    // Интерфейс для обновления отрезка [l, r] (1-based индексация)
    inline void update_range(int l, int r, int value) {
        l--; r--;  // Переход к 0-based индексации
        update_range(1, 0, sz - 1, l, r, value);
    }
    
    // Интерфейс для получения хеша отрезка [l, r] (1-based индексация)
    inline int get_segment_hash(int l, int r) {
        l--; r--;  // Переход к 0-based индексации
        return get_hash(1, 0, sz - 1, l, r);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Чтение входных данных
    int N; cin >> N;  // Размер массива
    vector<int> arr(N);
    copy_n(istream_iterator<int>(cin), N, begin(arr));  // Чтение массива

    // Построение дерева отрезков
    segtree_t st(arr);
    string result;  // Для накопления результатов сравнения хешей

    // Обработка запросов
    int Q; cin >> Q;
    while(Q--) {
        int T, L, R, K;
        cin >> T >> L >> R >> K;

        if (T == 0) {
            // Запрос на обновление: установить элементы [L, R] в значение K
            st.update_range(L, R, K);
        } else {
            // Запрос на сравнение хешей двух подстрок длины K
            // Подстрока начинается в L и подстрока начинается в R
            uint64_t hash1 = st.get_segment_hash(L, L + K - 1);
            uint64_t hash2 = st.get_segment_hash(R, R + K - 1);
            result += (hash1 == hash2) ? '+' : '-';  // '+' если равны, '-' если нет
        }
    }

    // Вывод результата
    cout << result << endl;
    return 0;
}