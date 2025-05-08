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

    vector<item_t> items(n + 1);
    for(int i = 1; i <= n; i++) cin >> items[i].weight;
    for(int i = 1; i <= n; i++) cin >> items[i].cost;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // перебираем все предметы
    for(int i = 1; i <= n; i++)
    {
        const item_t& item = items[i];

        // каждый предмет пробуем поместить в рюкзаки с выдерживаемым весом от 0 до m
        for(int j = 1; j <= m; j++)
        {
            // если предмет может поместиться в текущий рюкзак...
            if(j >= item.weight)
                // ...то берем этот предмет и, по возможности, если позволяет место,
                // берем предыдущие подходящие по весу предметы...
                dp[i][j] = max(dp[i - 1][j - item.weight] + item.cost, dp[i-1][j]);
            else 
                // ...иначе берем предыдущие предметы для текущего рюкзака
                dp[i][j] = dp[i-1][j];
        }
    }
    

    int i = n;
    int j = m;
    vector<int> selected;

    // восстановление ответа
    while(i > 0 && j > 0)
    {
        if(dp[i][j] != dp[i - 1][j])
        {
            selected.emplace_back(i);
            j -= items[i].weight;
        }
        --i;
    }

    for(auto i = selected.crbegin(); i != selected.crend(); i++) 
        cout << *i << endl;

    return 0;
}
