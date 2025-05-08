/* Простая река */

#include <iostream>
#include <list>

using namespace std;

struct node_t 
{
    size_t len;
    node_t *next;
    node_t *prev;
};

size_t company_build(size_t n, list<node_t*>& ll) 
{
    size_t sum_sq = 0;

    node_t* prev = nullptr;

    for(size_t i = 0; i < n; i++)
    {
        if(prev == nullptr)
        {
            prev = new node_t;
            prev->next = nullptr;
            prev->prev = nullptr;

            cin >> prev->len;
            ll.push_back(prev);

            sum_sq += prev->len * prev->len;

            continue;
        }

        node_t *curr = new node_t;
        curr->next = nullptr;

        cin >> curr->len;

        curr->prev = prev;
        prev->next = curr;

        ll.push_back(curr);

        sum_sq += curr->len * curr->len;

        prev = curr;
    }

    return sum_sq;
}

size_t company_remove(list<node_t*>& ll, list<node_t*>::iterator pos, list<node_t*>::iterator& next_pos, size_t sum_sq) 
{
    node_t *node = *pos;
    sum_sq -= node->len * node->len;

    if(node->prev && !node->next)
    {
        sum_sq -= node->prev->len * node->prev->len;
        
        node->prev->len += node->len;
        node->prev->next = nullptr;

        sum_sq += node->prev->len * node->prev->len;
    } 
    else if(!node->prev && node->next)
    {
        sum_sq -= node->next->len * node->next->len;

        node->next->len += node->len;
        node->next->prev = nullptr;

        sum_sq += node->next->len * node->next->len;
    } 
    else 
    {
        sum_sq -= node->prev->len * node->prev->len;
        sum_sq -= node->next->len * node->next->len;

        size_t l = node->len / 2;
        size_t r = node->len - l;

        node->prev->len += l;
        node->next->len += r;

        node->prev->next = node->next;
        node->next->prev = node->prev;

        sum_sq += node->prev->len * node->prev->len;
        sum_sq += node->next->len * node->next->len;
    }

    delete node;
    next_pos = ll.erase(pos);

    return sum_sq;
}

size_t company_split(list<node_t*>& ll, list<node_t*>::iterator pos, list<node_t*>::iterator& next_pos, size_t sum_sq) 
{
    node_t *node = *pos;

    node_t *l = new node_t;
    node_t *r = new node_t;

    l->len = node->len / 2;
    r->len = node->len - l->len;

    sum_sq -= node->len * node->len;

    l->prev = node->prev;
    l->next = r;
    r->prev = l;
    r->next = node->next;

    if(node->prev) node->prev->next = l;
    if(node->next) node->next->prev = r;

    sum_sq += l->len * l->len;
    sum_sq += r->len * r->len;

    *pos = l;
    next_pos = ll.insert(next(pos), r);

    delete node;

    return sum_sq;
}

int main()
{
    size_t n; cin >> n;

    list<node_t*> ll;
    size_t total_sum_sq = company_build(n, ll);

    size_t k; cin >> k;

    cout << total_sum_sq << endl;

    auto curr_pos = ll.begin();
    size_t curr_idx = 0;

    for(size_t i = 0; i < k; i++)
    {
        size_t cmd, idx;
        cin >> cmd >> idx;

        idx--;

        // ограничения задачи позволяют просто проитерироваться на нужную позицию
        if(curr_idx < idx){
            while(curr_idx != idx){
                ++curr_idx;
                ++curr_pos;
            }
        } else {
            while(curr_idx != idx){
                --curr_idx;
                --curr_pos;
            }
        }

        if(cmd == 1) {
            total_sum_sq = company_remove(ll, curr_pos, curr_pos, total_sum_sq);
        } else if(cmd == 2) { 
            total_sum_sq = company_split(ll, curr_pos, curr_pos, total_sum_sq);
            curr_idx++;
        }

        cout << total_sum_sq << endl;
    }

    for(auto it = ll.begin(); it != ll.end(); it++)
        delete *it;

    return 0;
}