#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct group_t {
    int id;
    int size;           
    int id_classroom;
};

struct classroom_t {
    int id;
    int computers;
    bool used;
};

int main(){
    // n - кол-во групп
    // m - кол-во аудиторий
    int n,m;
    cin >> n >> m;

    int total_assigned = 0;

    vector<group_t> groups(n);
    vector<classroom_t> classrooms(m);

    for(int i = 0; i < n; ++i){
        groups[i].id = i;
        groups[i].id_classroom = 0;
        cin >> groups[i].size;
    }

    for(int i = 0; i < m; ++i){
        classrooms[i].id = i + 1; // +1 потому что нумерация с 1
        cin >> classrooms[i].computers;
        classrooms[i].used = false;
    }

    // сортируем по возрастанию кол-ва компьютеров
    sort(begin(classrooms), end(classrooms), [](const classroom_t& a, const classroom_t& b){
        return a.computers < b.computers;
    });

    // идея алгоритма: назначаем для группы первую подходящую по кол-ву компов аудиторию.
    // поскольку аудитории отсортированы по возрастанию, такое назначение даст оптимальный результат.
    // наверно можно слегка ускорить алгоритм, если использовать std::list<classroom_t> и удалять аудиторию
    // из листа после назначения. тогда следующие проходы по листу могут быть короче
    for(group_t& group : groups){
        for(size_t i = 0; i < classrooms.size(); i++){
            if(classrooms[i].used) 
                continue;

            if(classrooms[i].computers < group.size + 1) // +1 потому что дополнительный комп нужен учителю
                continue;

            classrooms[i].used = true;
            group.id_classroom = classrooms[i].id;
            total_assigned++;
            break;
        }
    }

    cout << total_assigned << endl;
    transform(begin(groups), end(groups), ostream_iterator<int>(cout, " "), 
    [](const group_t& group){
        return group.id_classroom;
    });

    cout << endl;

    return 0;
}