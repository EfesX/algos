#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <climits>

using namespace std;

// считаем отрезки.
// жадная идея: идем по массиву, увеличивая длину отрезка пока не 
// встретим число меньше либо равное длине отрезка. фиксируем текущую
// длину отрезка, обнуляем ее и идем дальше
void processing(const vector<int>& vec, list<int>& segments){
    int curr_len = 0;
    int min_val = INT_MAX;

    for(size_t i = 0; i < vec.size(); i++)
    {
        min_val = min(min_val, vec[i]);

        if(curr_len >= min_val)
        {
            segments.emplace_back(curr_len);
            min_val = vec[i];
            curr_len = 0;
        }

        curr_len++;
    }

    if(curr_len != 0)
        segments.emplace_back(curr_len);
};

int main()
{
    int t; cin >> t;

    while(t--)
    {
        int n; cin >> n;
        vector<int> vec(n);
        list<int> segments;

        copy_n(istream_iterator<int>(cin), n, begin(vec));
        processing(vec, segments);

        cout << segments.size() << endl;
        copy(begin(segments), end(segments), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    return 0;
}