#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main(){

    // a - 2
    // b - 3
    // c - 4
    long long a,b,c;
    cin >> a >> b >> c;

    long long l = 0;
    long long r = a*2 + 3*b + c*4 + 1;
    long long ans = r;

    while(l <= r)
    {
        long long m = (l + r) / 2;

        long long total = a*2 + 3*b + c*4 + m*5;
        long long count = a + b + c + m;

        if(count == 0)
        {
            l = m + 1;
            continue;
        }

        // Сравниваем как 2*total и 7*count, чтобы избежать деления (7/2 == 3.5)
        if (2 * total < 7 * count) 
        {
            l = m + 1;
        } 
        else 
        {
            r = m - 1;
            ans = m;
        }
    }

    cout << ans << endl;

    return 0;
}