#include <iostream>
#include <array>
#include <algorithm>
#include <climits>

using namespace std;

struct card_t {
    size_t time;
    size_t cost;
    double ratio;
};

int main()
{
    size_t m; cin >> m;

    array<card_t, 31> cards;

    for(int i = 0; i < 31; ++i){
        cin >> cards[i].time;
        cards[i].cost = 1LL << i;
        cards[i].ratio = static_cast<double>(cards[i].time) / static_cast<double>(cards[i].cost);
    }

    // Сортируем карточки по убыванию ratio. это позволит сперва брать самые выгодные карточки
    sort(begin(cards), end(cards), [](auto a, auto b){
        return a.ratio > b.ratio;
    });

    size_t total_time = 0;
    size_t total_cost = 0;
    size_t min_total  = LLONG_MAX;

    for(const card_t& card : cards)
    {
        // если набрали достаточное количество карточек
        if(total_time >= m) break; 

        // вычисляем, сколько нужно взять текущих карточек, чтобы покрыть оставшееся время
        size_t needed = (m - total_time + card.time - 1) / card.time;
        // обновляем минимальную общую стоимость, если нашли вариант лучше
        min_total = min(min_total, total_cost + needed * card.cost);
        
        // вычисляем сколько можно взять текущих карточек без превышения нужного времени
        size_t take = (m - total_time) / card.time;
        // добавляем стоимость взятых карточек к общей стоимости
        total_cost += take * card.cost;
        // увеличиваем накопленное время на время взятых карточек
        total_time += take * card.time;
    }

    cout << min_total << endl;
    
    return 0;
}
