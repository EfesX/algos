#include <iostream>
#include <vector>
#include <numeric>
#include <stack>
#include <list>

using namespace std;

struct dsu_t {
    vector<int> parent;

    dsu_t(int n) :
        parent(n + 1) // +1 потому что вершины нумеруются с 1
    {
        // Инициализация: каждая вершина является своим собственным родителем
        iota(begin(parent), end(parent), 0);
    }

    // Функция поиска корня вершины u с применением сжатия путей
    int find(int u) {
        if(parent[u] != u)                // Если u не является своим собственным родителем
            parent[u] = find(parent[u]);  // Рекурсивно ищем корень и применяем сжатие пути
        return parent[u];                 // Возвращаем корень
    }

    // Объединение множеств, содержащих вершины u и v
    void union_sets(int u, int v) {
        // находим корни
        int root_u = find(u);
        int root_v = find(v);

        // Если корни одинаковые, вершины уже в одном множестве
        if (root_u == root_v) return;

        parent[root_v] = root_u; // Объединяем множества, делая root_u родителем для root_v
    }

    // Проверка, находятся ли вершины в одном множестве
    bool is_same(int u, int v){
        return (find(u) == find(v));
    }
};

int main(){

    int n; // количество вершин
    int m; // количество ребер
    int k; // количество операций

    cin >> n >> m >> k;

    dsu_t dsu(n);

    // Вектор для хранения всех ребер графа
    vector<pair<int,int>> edges;
    // Стек для хранения операций (будем обрабатывать в обратном порядке)
    stack<tuple<string, int, int>> cmds;
    // Список для хранения результатов операций ask (используем list для эффективного добавления в начало)
    list<string> results;

    for(int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        edges.emplace_back(pair{a, b});
    }

    for(int i = 0; i < k; i++){
        string cmd;
        int a,b;
        cin >> cmd >> a >> b;

        // Сохраняем операции в стек (чтобы обрабатывать их в обратном порядке)
        cmds.emplace(tuple{cmd, a, b});
    }

    // Обработка операций в обратном порядке
    while(!cmds.empty()){
        string cmd;
        int a, b;
        tie(cmd, a, b) = move(cmds.top());
        cmds.pop();

        if(cmd == "ask"){
            string ans = dsu.is_same(a, b) ? "YES" : "NO";
            results.emplace_front(move(ans)); // Добавляем в начало, так как обрабатываем в обратном порядке
        } else if(cmd == "cut") {
            // Для cut объединяем вершины (так как идем в обратном порядке, это соответствует добавлению ребра)
            dsu.union_sets(a,b);
        }
    }

    // Вывод результатов (они уже в правильном порядке, так как добавлялись в начало)
    for(auto res : results) cout << res << endl;
    cout << endl;

    return 0;
}