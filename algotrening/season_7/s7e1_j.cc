#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iterator>

using namespace std;

struct event_t {
    string name;
    int materiality;

    bool operator<(const event_t& oth) const {
        return materiality < oth.materiality;
    }
};

istream& operator>>(istream& in, event_t& e) {
    in >> e.name >> e.materiality;
    return in;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // n - кол-во событий
    // d - духовная сила
    int n,d;
    cin >> n >> d;

    vector<event_t> events(n);
    int max_materiality = 0;

    for(event_t& event : events){
        cin >> event;
        max_materiality = max(event.materiality, max_materiality);
    }

    // сортируем по возрастанию материальности
    sort(begin(events), end(events));

    // dp[i] - минимальное количество дней для отказа от события
    // имеющего материальность i
    vector<int> dp(max_materiality + 1, INT_MAX);
    dp[0] = 0; // база динамики

    vector<string> result;
    int total_days = 0;

    for(size_t i = 0; i < events.size(); i++)
    {
        const event_t& event = events[i];

        // находим такие события от которых отказались ранее,
        // вернув которые, сможем отказаться от текущего события
        int lower = max(0, event.materiality - d);
        auto mindays = *min_element(
            dp.begin() + lower, 
            dp.begin() + event.materiality + 1
        );

        // если не нашли событий от которых отказались ранее, в пределах материальности d,
        // то выходим, т.к. от текущего и последующих событий больше не сможем отказаться
        // не превысив материальность d 
        if(mindays == INT_MAX) break;

        mindays++; // +1 потому что нужен +1 день для отказа от текущего события

        // заполняем "рюкзак"
        for(int j = max_materiality - event.materiality - 1; j >= 0; j--){
            if(dp[j] == INT_MAX) continue;
            dp[j + event.materiality] = min(dp[j + event.materiality], dp[j] + mindays);
        }

        total_days += mindays;
        result.push_back(event.name);
    }

    sort(begin(result), end(result));

    cout << result.size() << " " << total_days << endl;
    copy(begin(result), end(result), ostream_iterator<string>(cout, "\n"));
    
    return 0;
}
