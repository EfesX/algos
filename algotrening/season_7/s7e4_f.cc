#include <iostream>
#include <vector>
#include <unordered_set>
#include <numeric>

using namespace std;

struct dsu_t {
    vector<int> parent;

    dsu_t(int n) :
        parent(n) // Индексация копилок с 1 до N
    {
        // Каждая копилка изначально является своей собственной родительской
        iota(begin(parent), end(parent), 0);
    }

    // Метод find с эвристикой сжатия пути
    // Находит корневую копилку для текущей копилки
    // Асимптотика: почти O(1)
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);  // Сжатие пути для оптимизации
        return parent[u];
    }

    // Объединение двух множеств копилок
    // Асимптотика: почти O(1)
    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        // копилки уже связаны
        if (root_u == root_v) return;

        // Объединяем множества (копилка v теперь принадлежит множеству u)
        parent[root_v] = root_u;
    }
};

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    vector<int> keys(N); // Массив, где keys[i] - номер копилки, в которой лежит ключ от i-й копилки
    dsu_t dsu(N);
    unordered_set<int> root_components; // Множество для хранения корней компонент связности
    
    // Считываем информацию о расположении ключей и строим граф зависимостей
    for (int i = 0; i < N; ++i) {
        // Ключ от i-й копилки находится в копилке keys[i]
        cin >> keys[i];
        --keys[i];
        // Объединяем множества i и keys[i], так как они связаны
        dsu.union_sets(i, keys[i]);
    }

    // Второй проход для сбора корней компонент
    for (int i = 0; i < N; ++i) {
        // Находим корневую копилку для текущей
        int root = dsu.find(i); 
        // Добавляем корень в множество компонент связности
        root_components.insert(root);
    }

    // Выводим минимальное количество копилок, которые нужно разбить
    cout << root_components.size() << endl;

    return 0;
}
