#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // n - кол-во золотых слитков
    // m - максимальный вес, который выдерживает рюкзак
    int n,m;
    cin >> n >> m;

    vector<int> backpack(m + 1, -1); // backpack[i] хранит максимальный вес, который можно набрать в рюкзак с m == i
    backpack[0] = 0;                 // база динамики

    // накопленный вес золотых слитков
    int max_gold_weight = -1;

    while(n--)
    {
        int gold; cin >> gold;

        for(int i = m; i >= 0; --i)
        {
            if(backpack[i] < 0) continue;
            if(i + gold > m) continue;

            backpack[i + gold] = max(i + gold, backpack[i + gold]);
            max_gold_weight = max(max_gold_weight, backpack[i + gold]);
        }
    }

    cout << max_gold_weight << endl;
    
    return 0;
}
