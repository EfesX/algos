#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct order_t {
    int v_s = 0; // количество S выпадающих на Васины дни
    int v_d = 0; // количество D выпадающих на Васины дни
    int m_s = 0; // количество S выпадающих на Машины дни
    int m_d = 0; // количество D выпадающих на Машины дни

    int priority; // приоритет заказа (насколько выгоден зяказ для Васи)
                  // используется в заказах с нечетной длиной
};

int main()
{
    int N; // кол-во заказов
    cin >> N;

    list<order_t> odd_orders;           // заказы с нечетной длиной
    list<order_t> even_orders_first;    // заказы с четной длиной которые выгодно начинать в Васину смену
    list<order_t> even_orders_second;   // заказы с четной длиной которые выгодно начинать в Машину смену
    
    long long vasya_days = 0; // кол-во дней когда S выпадает на Васину смену
    bool vasya_turn = true;   // флаг васиной смены.

    while(N--)
    {
        string seq; // последовательность дней
        cin >> seq;

        order_t order;
        
        // считаем кол-во Васиных и Машиных дней в заказе
        for(size_t j = 1; j <= seq.size(); j++) {
            order.v_s += ((j % 2 != 0) && (seq[j - 1] == 'S'));
            order.v_d += ((j % 2 != 0) && (seq[j - 1] == 'D'));

            order.m_s += ((j % 2 == 0) && (seq[j - 1] == 'S'));
            order.m_d += ((j % 2 == 0) && (seq[j - 1] == 'D'));
        }

        const int v_profit = order.v_s + order.m_d; // насколько выгоден заказ для Васи
        const int m_profit = order.v_d + order.m_s; // насколько выгоден заказ для Маши
        order.priority = v_profit - m_profit;       // суммарная выгода для Васи

        // заказы четной длины могут быть трех видов
        if(seq.size() % 2 == 0)
        {
            // такие заказы можно посчитать сразу, 
            // т.к. очередность их назначения ничего не меняет
            if(order.v_s + order.m_d == static_cast<int>(seq.size())){
                vasya_days += order.v_s;
                continue;
            }

            // такие заказы выгодно начинать с Васиной смены
            if(order.v_s + order.m_d >= order.m_s + order.v_d) even_orders_first.emplace_back(move(order));
            // такие заказы выгодно начинать с Машиной смены
            else even_orders_second.emplace_back(move(order));
        }
        // заказы нечетной длины далее отсортируются
        else odd_orders.emplace_back(move(order));
    }

    // сортируем по приоритету. таким образом, 
    // в начале оказываются наиболее выгодные для Васи заказы
    odd_orders.sort([](const order_t& a, const order_t& b){
        return a.priority > b.priority;
    });

    // обрабатываем заказы особым образом
    while(odd_orders.size())
    {
        order_t order;

        // если Васина смена, то берем заказ с максимальной выгодой для Васи
        if(vasya_turn){
            order = move(odd_orders.front());
            odd_orders.pop_front();
        // если Машина смена, то берем заказ с минимальной выгодой для Васи
        } else {
            order = move(odd_orders.back());
            odd_orders.pop_back();
        }

        // если васина очередь то плюсуем v_s, иначе m_s, потому что инверсия  
        vasya_days += vasya_turn ? order.v_s : order.m_s;
        // так как заказ с нечетной длиной, то меняется очередность
        vasya_turn = !vasya_turn;

        // при первой же возможности избавляемся от четных заказов
        // если Васина очередь, то извлекаем все заказы из even_orders_first,
        // иначе все заказы из even_orders_second.
        // ма можем извлечь сразу все заказы, так как четные заказы не меняют 
        // очередности.
        if(vasya_turn) {
            while(even_orders_first.size()){
                order = move(even_orders_first.front());
                even_orders_first.pop_front();
                vasya_days += order.v_s;
            }
        } else {
            while (even_orders_second.size()) {
                order = even_orders_second.front();
                even_orders_second.pop_front();
                vasya_days += order.m_s;
            }
        } 
    }

    // извлекаем остатки заказов
    while(even_orders_first.size()){
        auto order = move(even_orders_first.front());
        even_orders_first.pop_front();
        vasya_days += vasya_turn ? order.v_s : order.m_s;
    }
    while(even_orders_second.size()){
        auto order = move(even_orders_second.front());
        even_orders_second.pop_front();
        vasya_days += vasya_turn ? order.v_s : order.m_s;
    }

    cout << vasya_days << endl;

    return 0;
}
