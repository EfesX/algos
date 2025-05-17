#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;

    unordered_map<string,int> outgoing;
    unordered_map<string,int> incoming;

    unordered_map<string, pair<string,int>> addresses;

    for(int i = 0; i < N; i++){
        string s_from, s_to;
        int n_from, n_to;

        cin >> s_from >> n_from >> s_to >> n_to;

        string key_from = s_from + to_string(n_from);
        outgoing[key_from]++;
        addresses[key_from] = {s_from, n_from};

        string key_to = s_to + to_string(n_to);
        incoming[key_to]++;
        addresses[key_to] = {s_to, n_to};
    }

    vector<pair<string,int>> start;
    vector<pair<string,int>> finish;

    for(const auto& [k,v] : addresses){
        const int& out = outgoing[k];
        const int& in = incoming[k];

        if (out == in + 1)
            start.push_back(v);
        else if (in == out + 1)
            finish.push_back(v);
        else if (out != in)
        {
            cout << -1 << endl;
            return 0;
        }
    }

    if(start.size() != 1 || finish.size() != 1) {
        cout << -1 << endl;
        return 0;
    }

    cout << start[0].first << " " << start[0].second << " ";
    cout << finish[0].first << " " << finish[0].second << endl;

    return 0;
}