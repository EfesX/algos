#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct sparse_table_t {
    // матрица для хранения максимумов на отрезках
    vector<vector<int>> maxv;
    // матрица номера максимального из нескольких 
    // подряд идущих элементов массива
    vector<vector<int>> idxs;

    // быстрое вычисление логарифма (работает в GCC)
    static inline int fast_log2(int x){
        return 31 - __builtin_clz(x);
    }

    sparse_table_t(const vector<int>& array) {
        const int n = array.size();
        const int k = fast_log2(n) + 1;

        maxv.resize(k, vector<int>(n, 0));
        idxs.resize(k, vector<int>(n, 0));


        // заполняем таблицы
        maxv[0] = array;
        iota(begin(idxs[0]), end(idxs[0]), 1);

        for (int i = 1; i < k; i++) 
        {
            const int sz = n - (1 << i) + 1;

            for (int j = 0; j < sz; j++) 
            {
                const int left      = maxv[i - 1][j];
                const int right     = maxv[i - 1][j + (1 << (i - 1))];
                const int left_idx  = idxs[i - 1][j];
                const int right_idx = idxs[i - 1][j + (1 << (i - 1))];

                if (left > right) 
                {
                    maxv[i][j] = left;
                    idxs[i][j] = left_idx;
                } 
                else if (right >= left) 
                {
                    maxv[i][j] = right;
                    idxs[i][j] = right_idx;
                } 
            }
        }
    }

    inline pair<int,int> query_max(int l, int r) const
    {
        int k = fast_log2(r - l + 1);

        const int left_max = maxv[k][l];
        const int right_max = maxv[k][r - (1 << k) + 1];

        if (left_max > right_max)
            return { left_max, idxs[k][l] };
        
        return { right_max, idxs[k][r - (1 << k) + 1] };
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
        const auto [maxv, idx] = st.query_max(--l, --r);
        cout << maxv << " " << idx << endl;
    }

    return 0;
}
