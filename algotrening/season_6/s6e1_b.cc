#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    vector<int> ab(2), cd(2);
    cin >> ab[0] >> ab[1] >> cd[0] >> cd[1];

    int red_shirts  = ab[1] + 1;
    int blue_shirts = ab[0] + 1;
    int red_socks   = cd[1] + 1;
    int blue_socks  = cd[0] + 1;
    int red_suit    = red_shirts + red_socks;
    int blue_suit   = blue_shirts + blue_socks;

    if (ab[0] == 0) return cout << "1 " << cd[0] + 1 << endl, 0;
    if (ab[1] == 0) return cout << "1 " << cd[1] + 1 << endl, 0;
    if (cd[0] == 0) return cout << ab[0] + 1 << " 1" << endl, 0;
    if (cd[1] == 0) return cout << ab[1] + 1 << " 1" << endl, 0;

    if (ab[0] == ab[1] && ab[0] == cd[0] && ab[0] == cd[1]) 
        return cout << ab[0] + 1 << " 1" << endl, 0;


    int abmax = max(ab[0], ab[1]) + 1;
    int cdmax = max(cd[0], cd[1]) + 1;
    int options[] = {
        red_suit, 
        blue_suit, 
        abmax + 1, 
        cdmax + 1
    };
    int min_val = *min_element(begin(options), end(options));

    if (min_val == red_suit) 
        return cout << red_shirts << " " << red_socks << endl, 0;

    if (min_val == blue_suit) 
        return cout << blue_shirts << " " << blue_socks << endl, 0;

    if (min_val == abmax + 1) 
        return cout << abmax << " 1" << endl, 0;

    cout << "1 " << cdmax << endl;

    return 0;
}