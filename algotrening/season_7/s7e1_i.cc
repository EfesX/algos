#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

struct item_t {
    int id;
    int volume;         // объем
    int cost;           // стоимость
    int max_pressure;   // максимальное выдерживаемое давление
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // n - кол-во товаров
    // s - базовый объем отсека ровера
    int n,s;
    cin >> n >> s;

    vector<item_t> items(n);
    int total_volume = 0;       // объем, необходимый для размещения всех товаров

    for(int i = 0; i < n; i++) {
        items[i].id = i + 1;                // 1-based индексация
        cin >> items[i].volume;
        cin >> items[i].cost;
        cin >> items[i].max_pressure;
        total_volume += items[i].volume;
    }

    // сортируем в порядке убывания выдерживаемого давления
    sort(begin(items), end(items), [](const item_t& a, const item_t& b){
        return a.max_pressure > b.max_pressure;
    });

    // dp[i][j] хранит максимальную стоимость i товаров при объеме j
    vector<vector<int>> dp(n + 1, vector<int>(total_volume + 1, 0));

    // заполняем таблицу
    for(int i = 1; i <= items.size(); ++i) {
        const item_t& item = items[i - 1];

        for(int j = 1; j < dp[i].size(); ++j)
        {
            dp[i][j] = dp[i - 1][j];
            
            // товар не влезает в объем j
            if(j - item.volume < 0) continue;
            // товар не выдерживает давления
            if(j - s > item.max_pressure) continue;

            // если стоимость текущего товара + стоимость товаров в остатке объема превышает
            // стоимость товаров для текущего объема (без текущего товара), то берем текущий товар
            dp[i][j] = max(dp[i - 1][j], item.cost + dp[i - 1][j - item.volume]);
        }
    }

   // восстанавливаем ответ
    int i = dp.size() - 1;
    int j = max_element(dp[i].begin(), dp[i].end()) - dp[i].begin();

    long long total_cost = dp[i][j];

    list<int> selected;

    while(i > 0 && j > 0)
    {
        if(dp[i][j] == dp[i-1][j])
        {
            i--;
            continue;
        }

        selected.emplace_front(items[i - 1].id);
        i--;
        j -= items[i].volume;
    }

    cout << selected.size() << " " << total_cost << endl;
    copy(begin(selected), end(selected), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
