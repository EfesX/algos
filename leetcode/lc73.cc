#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool flag = false;
        for(int i = 0; i < m; ++i){
            if(matrix[i][0] == 0){
                flag = true;
                break;
            }
        }

        for(int i = 0; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(matrix[i][j] == 0){
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for(int i = 1; i < n; ++i){
            if(matrix[0][i] == 0){
                for(int j = 0; j < m; ++j)
                    matrix[j][i] = 0;
            }
        }

        for(int i = 0; i < m; ++i){
            if(matrix[i][0] == 0)
                matrix[i] = move(vector<int>(n, 0));
        }

        if(flag)
            for(int i = 0; i < m; ++i)
                matrix[i][0] = 0;
    }
};

int main()
{
    vector<vector<int>> m = {
        {0, 1, 2, 0},
        {3, 4, 5, 2},
        {1, 3, 1, 5}
    };

    Solution s;
    s.setZeroes(m);

    for(auto vec : m){
        for(auto n : vec) cout << n << " ";
        cout << endl;
    }

    return 0;
}
