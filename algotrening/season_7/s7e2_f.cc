#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class segtree_t {
private:
    int sz_origin;          // Исходный размер массива
    vector<int> tree;       // Дерево отрезков для хранения максимальных значений
    vector<int> idxs;       // Массив для хранения индексов максимальных элементов

    // Рекурсивная функция построения дерева отрезков
    inline void build(int v, int tl, int tr, const vector<int>& arr){
        // Базовый случай: листовой узел
        if(tl == tr){
            tree[v] = arr[tl];  // Сохраняем значение элемента
            idxs[v] = tl;       // Сохраняем его индекс
            return;
        }

        // Разделяем текущий отрезок на два подотрезка
        const int tm = (tl + tr) >> 1;  // Середина отрезка
        const int lch = v << 1;         // Левый потомок
        const int rch = lch | 1;        // Правый потомок

        // Рекурсивно строим левое и правое поддерево
        build(lch,     tl, tm, arr);
        build(rch, tm + 1, tr, arr);

        // Обновляем максимум и его индекс в текущем узле
        if(tree[lch] > tree[rch]) {
            tree[v] = tree[lch];
            idxs[v] = idxs[lch];
        } 
        else if(tree[lch] < tree[rch]) {
            tree[v] = tree[rch];
            idxs[v] = idxs[rch];
        }
        else {
            // Если значения равны, сохраняем правое (можно и левое - зависит от требования)
            tree[v] = tree[rch];
            idxs[v] = idxs[rch];
        }
    }

    // Функция обновления значения в дереве
    inline void update(int v, int tl, int tr, int pos, int value){
        // Базовый случай: дошли до нужного листа
        if(tl == tr){
            tree[v] = value;  // Обновляем значение
            idxs[v] = tl;     // Индекс остается тем же
            return;
        }

        const int tm = (tl + tr) >> 1;  // Середина отрезка
        const int lch = v << 1;         // Левый потомок
        const int rch = lch | 1;        // Правый потомок

        // Рекурсивно обновляем в левом или правом поддереве
        if (pos <= tm)
            update(lch, tl, tm, pos, value);
        else 
            update(rch, tm + 1, tr, pos, value);

        // После обновления пересчитываем максимум для текущего узла
        if(tree[lch] > tree[rch]) {
            tree[v] = tree[lch];
            idxs[v] = idxs[lch];
        } 
        else if(tree[lch] < tree[rch]) {
            tree[v] = tree[rch];
            idxs[v] = idxs[rch];
        } 
        else {
            tree[v] = tree[rch];
            idxs[v] = idxs[rch];
        }
    }

    // Рекурсивная функция поиска первого элемента ≥ value, начиная с позиции start
    inline int above(int v, int tl, int tr, int start, int value) const {
        // Если максимальное значение в поддереве меньше искомого - нет решения
        if(value > tree[v])
            return -1;

        // Если текущий отрезок полностью правее start
        if(start > tr)
            return -1;

        // Если дошли до листа - возвращаем его индекс
        if(tl == tr)
            return idxs[v];

        const int tm = (tl + tr) >> 1;      // Середина отрезка
        const int l_ch_idx = v << 1;        // Левый потомок
        const int r_ch_idx = l_ch_idx | 1;  // Правый потомок

        // Сначала ищем в левом поддереве (чтобы найти первый подходящий элемент)
        int res = above(l_ch_idx, tl, tm, start, value);
        if(res != -1)
            return res;

        // Если в левом не нашли, ищем в правом
        return above(r_ch_idx, tm + 1, tr, start, value);
    }

public:
    // Конструктор - строит дерево отрезков из переданного массива
    segtree_t(const vector<int>& arr) :
        sz_origin(arr.size()),
        tree(sz_origin << 2),    // Размер дерева - 4*N
        idxs(sz_origin << 2)      // То же для массива индексов
    {
        build(1, 0, sz_origin - 1, arr);
    }

    // Публичный интерфейс для поиска первого элемента ≥ value, начиная с start
    inline int above(int start, int value) const {
        // Проверка граничных условий
        if(start >= sz_origin) return -1;    // Старт за пределами массива
        if(value > tree[1]) return -1;       // Искомое значение больше глобального максимума

        // Запускаем рекурсивный поиск
        return above(1, 0, sz_origin - 1, start, value);
    }

    // Публичный интерфейс для обновления значения
    inline void update(int pos, int value) {
        update(1, 0, sz_origin - 1, pos, value);
    }
};

int main(){
    // Оптимизация ввода/вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K; 
    cin >> N >> K;  // Читаем размер массива и количество запросов

    vector<int> arr(N);
    // Эффективное чтение массива
    copy_n(istream_iterator<int>(cin), N, begin(arr));

    // Строим дерево отрезков
    segtree_t st(arr);

    // Обрабатываем K запросов
    while(K--){
        int cmd, idx, val;
        cin >> cmd >> idx >> val;
        idx--;   // Переводим в 0-индексацию

        if(cmd == 1) {
            // Запрос на поиск: находим первый элемент ≥ val, начиная с idx
            int res = st.above(idx, val);
            res = (res == -1) ? -1 : res + 1;  // Переводим обратно в 1-индексацию для вывода
            cout << res << endl;
        } else {
            // Запрос на обновление: обновляем значение в позиции idx
            st.update(idx, val);
        }
    }

    return 0;
}
