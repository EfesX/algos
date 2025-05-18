#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct coord_t {
    int x, y;
};

int main() {
    coord_t sw, ne, point;
    cin >> sw.x >> sw.y >> ne.x >> ne.y >> point.x >> point.y;

    // Лямбда для вычисления квадрата расстояния
    auto get_sqr_distance = [](coord_t a, coord_t b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return dx*dx + dy*dy;
    };

    // Храним квадраты расстояний
    vector<pair<string, int>> sqr_distances; 

    // Добавляем расстояния до углов
    sqr_distances.emplace_back("SW", get_sqr_distance(point, sw));
    sqr_distances.emplace_back("SE", get_sqr_distance(point, {ne.x, sw.y}));
    sqr_distances.emplace_back("NW", get_sqr_distance(point, {sw.x, ne.y}));
    sqr_distances.emplace_back("NE", get_sqr_distance(point, ne));

    // Проверяем положение точки относительно прямоугольника
    bool west  = point.x < sw.x && point.y >= sw.y && point.y <= ne.y;
    bool east  = point.x > ne.x && point.y >= sw.y && point.y <= ne.y;
    bool north = point.y > ne.y && point.x >= sw.x && point.x <= ne.x;
    bool south = point.y < sw.y && point.x >= sw.x && point.x <= ne.x;

    // Вычисляем минимальные расстояния до сторон
    if (west) {
        int dx = sw.x - point.x;
        sqr_distances.emplace_back("W", dx*dx);
    } 
    else if (east) {
        int dx = point.x - ne.x;
        sqr_distances.emplace_back("E", dx*dx);
    }
    else if (north) {
        int dy = point.y - ne.y;
        sqr_distances.emplace_back("N", dy*dy);
    }
    else if (south) {
        int dy = sw.y - point.y;
        sqr_distances.emplace_back("S", dy*dy);
    }

    // Находим минимальный элемент
    auto min_it = min_element(sqr_distances.begin(), sqr_distances.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    cout << min_it->first << endl;

    return 0;
}