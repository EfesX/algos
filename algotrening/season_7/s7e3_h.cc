#include <iostream>
#include <vector>

using namespace std;

// 3D дерево Фенвика.
// для удобства работы с индексами
// используется 1-based индексация 
class fenwick3d_t {
private:
    int sz;
    vector<vector<vector<int>>> sky;

    int query_sum(int x, int y, int z){
        int result = 0;

        for(int i = x; i > 0; i = prev(i))
            for(int j = y; j > 0; j = prev(j))
                for(int k = z; k > 0; k = prev(k))
                    result += sky[i][j][k];

        return result;
    }

    inline int next(int x) const {
        x += x & -x;
        return x;
    }
    inline int prev(int x) const {
        x -= x & -x;
        return x;
    }
    
public:
    fenwick3d_t(int n) : 
        sz(n),
        sky(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 0)))
    {}

    void update(int x, int y, int z, int delta)
    {
        for(int i = x; i <= sz; i = next(i))
            for(int j = y; j <= sz; j = next(j))
                for(int k = z; k <= sz; k = next(k))
                    sky[i][j][k] += delta;
    }

    int calculate(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        return 
            +query_sum(x2    , y2    , z2    )
            -query_sum(x1 - 1, y2    , z2    )
            -query_sum(x2    , y1 - 1, z2    )
            -query_sum(x2    , y2    , z1 - 1)
            +query_sum(x1 - 1, y1 - 1, z2    )
            +query_sum(x1 - 1, y2    , z1 - 1)
            +query_sum(x2    , y1 - 1, z1 - 1)
            -query_sum(x1 - 1, y1 - 1, z1 - 1);
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    fenwick3d_t ft(n);

    int m = -1;
    while(m != 3)
    {
        cin >> m;

        if(m == 3) break;

        if(m == 1) {
            int x,y,z,k;
            cin >> x >> y >> z >> k;
            ft.update(++x,++y,++z, k);
        } else if(m == 2) {
            int x1,y1,z1,x2,y2,z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << ft.calculate(++x1,++y1,++z1, ++x2,++y2,++z2) << endl;
        }
    }

    return 0;
}
