/* Слабое звено */

#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

struct node_t 
{
    int id;
    int value;
    node_t *prev;
    node_t *next;

    node_t(int id, int value) : 
        id(id), 
        value(value), 
        prev(nullptr), 
        next(nullptr)
    {}
};


int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    if(n == 2) {
        cout << "0 0" << endl;
        return 0;
    }

    list<node_t*> ll;
    queue<node_t*> q;
    vector<int> res(n, 0);
    int round = 1;

    {
        node_t *node = nullptr;
        for(int i = 0; i < n; i++)
        {
            int val; cin >> val;
            node_t *temp = new node_t(i, val);

            if(node == nullptr){
                node = temp;
                ll.push_back(node);
                continue;
            }

            node->next = temp;
            temp->prev = node;
            node = temp;
            ll.push_back(node);
        }
    }

    ll.front()->prev = ll.back();
    ll.back()->next = ll.front();

    for(list<node_t*>::iterator it = ll.begin(); it != ll.end(); it++)
    {
        node_t* node = *it;
        if(node->value < node->next->value && node->value < node->prev->value)
            q.push(node);
    }
    
    while(q.size())
    {
        int sz = q.size();

        while(sz--)
        {
            node_t* node = q.front();
            q.pop();

            if(node->value < node->next->value && node->value < node->prev->value)
            {
                if(node->next == node->prev)
                    continue;

                // обновляем связи
                node->prev->next = node->next;
                node->next->prev = node->prev;

                // добавляем соседей в очередь на обработкку
                q.push(node->prev);
                q.push(node->next);

                // фиксируем текущий раунд для текущего элемента
                res[node->id] = round;
            }
        }

        round++;
    }

    for(size_t i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    cout << endl;

    for(auto it = ll.begin(); it != ll.end(); it++)
        delete *it;

    return 0;
}