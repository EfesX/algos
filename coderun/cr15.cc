#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <climits>

using namespace std;


const int MAX_N = 30;
bool visited[MAX_N][MAX_N][MAX_N] = {false};  // O(N³) памяти, но быстро

struct coord_hash_t {
    std::size_t operator()(const tuple<int,int,int>& coord) const {
        auto [lvl,x,y] = coord;
        int key = (lvl << 10) | (x << 5) | y;
        return key;
    }
};

int bfs(tuple<int,int,int> start, const vector<vector<vector<bool>>>& walls, int N){
    int slvl,sx,sy;
    tie(slvl,sx,sy) = start;

    queue<tuple<int,int,int,int>> q;
    q.push(make_tuple(get<0>(start), get<1>(start), get<2>(start), 0));

    auto is_possible = [&N, &walls](int lvl, int x, int y) -> bool {
        if(lvl < 0) return false;
        if(lvl >= N) return false;

        if(x < 0) return false;
        if(x >= N) return false;

        if(y < 0) return false;
        if(y >= N) return false;

        if(visited[lvl][x][y]) return false;
        if(walls[lvl][x][y]) return false;

        visited[lvl][x][y] = true;

        return true;
    };

    while(!q.empty())
    {
        auto [lvl,x,y,len] = q.front();
        q.pop();

        if(lvl == 0) return len;

        

        if(is_possible(lvl - 1, x, y)) q.push(make_tuple(lvl - 1, x, y, len + 1));
        if(is_possible(lvl + 1, x, y)) q.push(make_tuple(lvl + 1, x, y, len + 1));
        if(is_possible(lvl, x - 1, y)) q.push(make_tuple(lvl, x - 1, y, len + 1));
        if(is_possible(lvl, x + 1, y)) q.push(make_tuple(lvl, x + 1, y, len + 1));
        if(is_possible(lvl, x, y - 1)) q.push(make_tuple(lvl, x, y - 1, len + 1));
        if(is_possible(lvl, x, y + 1)) q.push(make_tuple(lvl, x, y + 1, len + 1));
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<vector<vector<bool>>> walls(N, vector<vector<bool>>(N, vector<bool>(N, false)));
    tuple<int, int, int> start;

    for (int lvl = 0; lvl < N; ++lvl) {
        for (int x = 0; x < N; ++x) {
            string line; cin >> line;
            for (int y = 0; y < N; ++y) {
                if (line[y] == '#') walls[lvl][x][y] = true;
                else if (line[y] == 'S') start = {lvl, x, y};
            }
        }
    }

    cout << bfs(start, walls, N) << endl;

    return 0;
}