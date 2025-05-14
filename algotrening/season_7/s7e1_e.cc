#include <iostream>
#include <vector>

using namespace std;

struct item_t {
    int weight; // вес предмета
    int cost;   // стоимость предмета
};

int main()
{
    // n - кол-во предметов
    // m - максимальный вес, который выдерживает рюкзак
    int n, m;
    cin >> n >> m;

    vector<item_t> items(n);
    for(item_t& item : items) cin >> item.weight;
    for(item_t& item : items) cin >> item.cost;

    vector<int> backpack(m + 1, -1); // backpack[i] хранит максимальную стоимость предметов,
                                     // которые можно уложить в рюкзак с m == i
    backpack[0] = 0;                 // база динамики

    int max_cost = 0;

    for(const item_t& item : items)
    {
        for(int i = m; i >= 0; --i)
        {
            if(backpack[i] < 0) continue;
            if(i + item.weight > m) continue;

            backpack[i + item.weight] = max(backpack[i + item.weight], backpack[i] + item.cost);
            max_cost = max(backpack[i + item.weight], max_cost);
        }
    }

    cout << max_cost << endl;

    return 0;
}
