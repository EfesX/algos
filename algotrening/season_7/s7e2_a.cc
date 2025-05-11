#include <iostream>
#include <vector>

using namespace std;

struct sparse_table_t {
    // матрица для хранения максимумов на отрезках
    vector<vector<int>> maxv;
    // матрица кол-ва максимумов на отрезках
    vector<vector<int>> cntv;

    // быстрое вычисление логарифма (работает в GCC)
    static inline int fast_log2(int x){
        return 31 - __builtin_clz(x);
    }

    sparse_table_t(const vector<int>& array) {
        const int n = array.size();
        const int k = fast_log2(n) + 1;

        maxv.resize(k, vector<int>(n, 0));
        cntv.resize(k, vector<int>(n, 0));


        // заполняем таблицы
        maxv[0] = array;
        cntv[0] = vector<int>(n, 1);

        for (int i = 1; i < k; i++) 
        {
            const int sz = n - (1 << i) + 1;

            for (int j = 0; j < sz; j++) 
            {
                const int left      = maxv[i - 1][j];
                const int right     = maxv[i - 1][j + (1 << (i - 1))];
                const int left_cnt  = cntv[i - 1][j];
                const int right_cnt = cntv[i - 1][j + (1 << (i - 1))];

                if (left > right) 
                {
                    maxv[i][j] = left;
                    cntv[i][j] = left_cnt;
                } 
                else if (right > left) 
                {
                    maxv[i][j] = right;
                    cntv[i][j] = right_cnt;
                } 
                else 
                {
                    maxv[i][j] = left;
                    cntv[i][j] = left_cnt + right_cnt;
                }
            }
        }
    }

    inline pair<int, int> query_max(int l, int r) const
    {
        int k = fast_log2(r - l + 1);

        const int left_max = maxv[k][l];
        const int right_max = maxv[k][r - (1 << k) + 1];

        if (left_max > right_max)
            return { left_max, cntv[k][l] };
        
        if (right_max > left_max)
            return { right_max, cntv[k][r - (1 << k) + 1] };
        
        // если left_max == right_max, то надо правильно
        // посчитать кол-во максимов на соответструющих подотрезках
        const int max_val = left_max;
        int total = 0;
        while (l <= r) 
        {
            total += (maxv[k][l] == max_val) ? cntv[k][l] : 0;
            l += (1 << k);
            k = fast_log2(r - l + 1);
        }

        return { left_max, total };
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sparse_table_t st(arr);

    int k;
    cin >> k;

    while(k--)
    {
        int l, r;
        cin >> l >> r;
        const auto [max_val, cnt] = st.query_max(--l, --r);
        cout << max_val << " " << cnt << endl;
    }

    return 0;
}