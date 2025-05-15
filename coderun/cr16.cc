#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct metro_t {
    unordered_map<int, set<int>> lines;
    unordered_map<int, set<int>> stations;

    int cnt_stations;
    int cnt_lines;

    metro_t(istream& in) {
        in >> cnt_stations >> cnt_lines;

        for (int i = 0; i < cnt_lines; i++) {
            int p;
            in >> p;
            for (int j = 0; j < p; j++) {
                int st;
                in >> st;
                lines[i].insert(st);
                stations[st].insert(i);
            }
        }
    }

    int get_hops(int start, int stop) {
        if (start == stop) return 0;
        if (start > cnt_stations || stop > cnt_stations) return -1;
        if (stations.find(start) == stations.end() || stations.find(stop) == stations.end()) return -1;

        vector<bool> visited_line(cnt_lines, false);
        queue<tuple<int, int, int>> q;  // {станция, текущая линия, количество пересадок}

        // Добавляем все линии начальной станции в очередь
        for (int line : stations[start]) {
            q.push({start, line, 0});
        }

        while (!q.empty()) {
            auto [station, line, hops] = q.front();
            q.pop();

            if (visited_line[line]) continue;
            visited_line[line] = true;

            for (int next_station : lines[line]) {
                if (next_station == stop) {
                    return hops;
                }

                // Перебираем все линии next_station (кроме текущей)
                for (int next_line : stations[next_station]) {
                    if (next_line != line) {
                        q.push({next_station, next_line, hops + 1});
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    metro_t metro(cin);

    int start, stop;
    cin >> start >> stop;

    cout << metro.get_hops(start, stop) << endl;

    return 0;
}