#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

struct pair_hash 
{
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2> &p) const 
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

int main() {
    int W, H, N;
    cin >> W >> H >> N;
    
    vector<tuple<int, int, int, int>> photos;
    for (int i = 0; i < N; ++i) 
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        photos.emplace_back(x1, y1, x2, y2);
    }

    auto [x1, y1, x2, y2] = photos[0];
    unordered_set<pair<int, int>, pair_hash> possible_positions;

    for (int x = x1; x <= x2; ++x)
        for (int y = y1; y <= y2; ++y)
            possible_positions.insert({x, y});
    
    bool possible = true;

    for (int i = 1; i < N; ++i) 
    {
        auto [x1_curr, y1_curr, x2_curr, y2_curr] = photos[i];
        unordered_set<pair<int, int>, pair_hash> new_positions;
        
        // проверяем все клетки текущего фото
        for (int x = x1_curr; x <= x2_curr; ++x) {
            for (int y = y1_curr; y <= y2_curr; ++y) {
                // проверяем есть ли соседняя клетка в предыдущих позициях
                for (auto [dx, dy] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) 
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (possible_positions.count({nx, ny})) 
                    {
                        new_positions.insert({x, y});
                        break;
                    }
                }
            }
        }
        
        if (new_positions.empty()) 
        {
            possible = false;
            break;
        }
        possible_positions = move(new_positions);
    }
    
    cout << (possible ? "Yes" : "No") << endl;
    
    return 0;
}

