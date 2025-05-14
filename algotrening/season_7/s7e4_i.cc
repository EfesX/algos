#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct snowman_t 
{
    int parent;         // индекс предка
    int top_mass;       // масса верхнего шара
    size_t total_mass;  // суммарная масса

    snowman_t(int parent, int top_mass, size_t total_mass) : parent(parent), top_mass(top_mass), total_mass(total_mass)
    {}

    snowman_t(const snowman_t& oth){
        parent     = oth.parent;
        top_mass   = oth.top_mass;
        total_mass = oth.total_mass;
    }
};

int main()
{
    int n; cin >> n;
    size_t total_mass = 0;

    vector<snowman_t> snowmen;
    snowmen.reserve(n + 1);
    snowmen.emplace_back(-1, 0, 0); // "нулевой" снеговик

    for(int i = 0; i < n; ++i){
        int t,m;
        cin >> t >> m;

        // клонировать и добавить шар массой m
        if(m != 0) {
            const snowman_t& parent  = snowmen[t];
            snowmen.emplace_back(
                t,                      // отмечаем индекс предка (от кого клонировались)
                m,                      // новая масса верхнего шара
                parent.total_mass + m   // суммарная масса равна массе предка плюс масса нового шара 
            );
        } 
        // клонировать и удалить верхний шар
        else {
            // при удалении верхнего шара из предка, можно заметить, что текущий снеговик становится идентичным предку предка (дедушке)
            const snowman_t& grandpa = snowmen[snowmen[t].parent];
            snowmen.emplace_back(grandpa);
        }

        // считаем суммарную массу
        total_mass += snowmen.back().total_mass;
    }

    cout << total_mass << endl;

    return 0;
}