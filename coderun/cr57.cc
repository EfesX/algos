#include <iostream>
#include <unordered_set>

using namespace std;

int main(){
    string s1,s2;
    cin >> s1 >> s2;

    size_t result = 0;

    unordered_set<string_view> us;

    for(size_t i = 0; i < s2.size() - 1; ++i)
        us.insert(string_view(&s2[i], 2));
    

    for(size_t i = 0; i < s1.size() - 1; ++i)
        if(us.count(string_view(&s1[i], 2)))
            result++;

    cout << result << endl;

    return 0;
}