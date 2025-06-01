#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int closestMeetingNode(vector<int>& edges, int node1, int node2)
        {
            const int& sz = edges.size();
    
            vector<vector<int>> vv;
    
            for(int val : { node1, node2 })
            {
                int pathlen = 0;
                vector<int> row(sz, -1);
                vector<bool> visited(sz, false);
    
                while(val != -1)
                {
                    if(visited[val])
                        break;
    
                    row[val] = pathlen++;
    
                    if(val == -1)
                        break;
    
                    visited[val] = true;
                    val = edges[val];
                }
    
                vv.emplace_back(move(row));
            }
    
            for(int i = 0; i < sz; i++)
                if(vv[0][i] != -1 && vv[1][i] != -1)
                    vv[0][i] = max(vv[0][i], vv[1][i]);
                else
                    vv[0][i] = INT_MAX;
    
            auto it = min_element(vv[0].begin(), vv[0].end());
            if(*it == INT_MAX) return -1;
            return distance(vv[0].begin(), it);
        }
    };

    int main(){
        return 0;
    }