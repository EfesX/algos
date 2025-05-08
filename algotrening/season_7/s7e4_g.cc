#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_set>

using namespace std;

struct dsu_t {
    vector<int> parent; // Массив для хранения родительских вершин
    int cmps;           // Количество компонент связности в графе

    dsu_t(int n) :
        parent(n + 1), // Инициализируем массив parent размером n+1 (вершины нумеруются с 1)
        cmps(n)        // Изначально каждая вершина - отдельная компонента
    {
        // Заполняем массив parent числами от 0 до n (вершина i имеет родителя i)
        iota(begin(parent), end(parent), 0);
    }

    // Функция поиска корня вершины u с применением сжатия путей
    int find(int u) {
        if(parent[u] != u)                // Если u не является своим собственным родителем
            parent[u] = find(parent[u]);  // Рекурсивно ищем корень и применяем сжатие пути
        return parent[u];                 // Возвращаем корень
    }

    // Функция объединения множеств, содержащих u и v
    void union_sets(int u, int v) {
        // находим корни
        int root_u = find(u);
        int root_v = find(v);

        // Если корни одинаковые, вершины уже в одном множестве
        if (root_u == root_v) return;

        parent[root_v] = root_u; // Объединяем множества, делая root_u родителем для root_v
        cmps--;                  // Уменьшаем количество компонент связности
    }

    // Проверка, является ли граф связным (все вершины в одной компоненте)
    bool is_connected(){
        return (cmps == 1);
    }
};


int main(){
    int n, m;
    cin >> n >> m;

    dsu_t dsu(n);
    int res = 0;  // Счётчик добавленных мостов

    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; // Чтение очередного моста

        if(dsu.is_connected()) break;

        // Объединяем множества, содержащие острова a и b
        dsu.union_sets(a, b);
        res++;
    }

    // Вывод результата - минимального количества рёбер для связности
    // Если граф уже связный, выведется количество рёбер, которое было достаточно
    // Если нет - выведется количество всех рёбер, но граф останется несвязным
    cout << res << endl;

    return 0;
}