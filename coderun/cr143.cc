#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

using namespace std;


int main()
{
    int n;
    cin >> n;

    vector<int> vec(n);
    copy_n(istream_iterator<int>(cin), n, begin(vec));
    
    
    stack<int> st;
    int last_wagen = 0;

    for(size_t i = 0; i < vec.size(); ++i)
    {
        if(vec[i] < last_wagen && vec[i] < st.top())
        {
            cout << "NO" << endl;
            return 0;
        }

        if(st.empty() || st.top() >= vec[i])
        {
            st.push(vec[i]);
            continue;
        }

        if(st.top() < last_wagen)
        {
            cout << "NO" << endl;
            return 0;
        }

        while(!st.empty() && st.top() < vec[i])
        {
            last_wagen = st.top();
            st.pop();
        }

        st.push(vec[i]);
    }

    if(st.top() < last_wagen)
        cout << "NO" << endl;
    else 
        cout << "YES" << endl;


    return 0;
}
