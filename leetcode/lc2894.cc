#include <iostream>

using namespace std;

class Solution {
public:
    int differenceOfSums(int n, int m)
    {   
        int sum1 = 0, sum2 = 0;
        for(int i = 1; i <= n; ++i){
            sum1 += (i % m == 0) ? 0 : i;
            sum2 += (i % m == 0) ? i : 0;
        }

        return (sum1 - sum2);
    }
};

int main()
{
    Solution s;
    cout << s.differenceOfSums(10,3) << endl;
    cout << s.differenceOfSums( 5,6) << endl;
    cout << s.differenceOfSums( 5,1) << endl;

    return 0;
}
