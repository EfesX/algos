#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;

    vector<int> distances(n);
    for(int i = 0; i < n; i++)
        cin >> distances[i];

    size_t l = 0;
    size_t r = 0;
    
    int ans = 0;

    while(r < distances.size())
        if(distances[r] - distances[l] > k)
            ans += distances.size() - r, l++;
        else r++;

    cout << ans << endl;

    return 0;
}