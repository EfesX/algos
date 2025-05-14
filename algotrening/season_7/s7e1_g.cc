/**
 * Нужно узнать можно ли построить из заданного набора кирпичей
 * две прямоугольные стены обладающих определеными характеристиками 
 * (см. условие задачи)
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct brick_t {
    int id;
    int len;
    int color;
};

using bricks_set = vector<brick_t>;
using bricks_by_color = vector<bricks_set>;

ostream& operator<<(ostream& out, const vector<int>& vec){
    for(auto v : vec) out << v << " ";
    return out;
}

/**
 * Т.к. известно, что, как минимум, одну прямоугольную стену (назовем ее оригинальной)
 * можно построить из всех кирпичей, то
 * нужно найти такие длины, разделив по которым оригинальную стену
 * можно получить две новые прямоугольные стены.
 * 
 * get_possible_lengths находит такие длины и сохраняет их в len_candidates
*/
bool get_possible_lengths(bricks_by_color& bricks, vector<int>& len_candidates)
{
    // считаем длину оригинальной стены
    const int wall_len = accumulate(begin(bricks[0]), end(bricks[0]), 0, [](int sum, const brick_t& b){
        return sum + b.len;
    });

    // строит и заполняет массив динамики из кирпичей заданного цвета
    auto dp_build = [&bricks, &wall_len](int color) 
    {
        // dp[i] - true если из некого подможества кирпичей 
        // возможно построить стену длиной i
        vector<bool> dp(wall_len + 1, false); 
        dp[0] = true;

        // перебираем кирпичи заданного цвета
        for(const brick_t& brick : bricks[color])
        {
            const int brick_len = brick.len;

            for(int i = dp.size() - 1; i >= 0; --i)
            {
                if(dp[i] == false) continue;
                if(i + brick_len >= static_cast<int>(dp.size())) continue;
                dp[i + brick_len] = dp[i];
            }
        }

        return dp;
    };

    // заполним dp для первого цвета.
    // в дальнейшем если для какого-либо из последующих
    // цветов не будет набираться кирпичей, чтобы построить 
    // стену длиной i то и в этом dp[i] будет false.
    // таким образом, можно поддерживать один dp
    // динамически обновляя его после обработки очередного цвета
    vector<bool> dp = dp_build(0);

    for(size_t color = 1; color < bricks.size(); ++color)
    {
        vector<bool> vec = dp_build(color);
        for(size_t i = 0; i < vec.size(); i++)
            dp[i] = dp[i] & vec[i];
    }

    // начинаем с единицы, потому что стена длиной 0 нас не интересует.
    // заканчиваем dp.size() - 1, потому что максимальная длина стены нас не интересует,
    // потому что тогда не останется кирпичей на вторую стену
    for(size_t i = 1; i < dp.size() - 1; i++)
        if(dp[i] == true) len_candidates.emplace_back(i);

    return true;
}

// по заданной длине выбирает кирпичи для постройки стены
void build_wall(bricks_by_color& bricks, int len_required, vector<int>& result)
{   
    // перебираем цвета
    for(size_t color = 0; color < bricks.size(); ++color)
    {
        const bricks_set& curr_bricks = bricks[color];

        vector<vector<int>> dp(curr_bricks.size() + 1, vector<int>(len_required + 1, 0));

        for(size_t i = 1; i < dp[0].size(); ++i)
            if(i >= static_cast<size_t>(curr_bricks[0].len)) dp[1][i] = curr_bricks[0].len;

        for(size_t i = 1; i <= curr_bricks.size(); ++i)
        {
            const brick_t& brick = curr_bricks[i - 1];

            for(int j = 1; j <= len_required; ++j)
            {
                if(brick.len <= j)
                    dp[i][j] = max(
                        brick.len + dp[i - 1][j - brick.len], 
                        dp[i - 1][j]
                    );
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        // восстанавливаем ответ
        int i = dp.size() - 1;
        int j = dp[i].size() - 1;
    
        while(i > 0 && j >= 0)
        {
            if(dp[i][j] != dp[i - 1][j])
            {
                result.push_back(curr_bricks[i - 1].id);
                j -= curr_bricks[i - 1].len;
            }
            --i;
        }
    }
}


int main(){
    // n - кол-во кирпичиков
    // k - кол-во цветов 
    int n,k;
    cin >> n >> k;

    // bricks[color][i] - длина i-ото кирпича имеющего цвет color
    bricks_by_color bricks(k);

    for(int i = 0; i < n; ++i)
    {
        brick_t brick;
        brick.id = i + 1; // +1 потому что нумерация с 1
        cin >> brick.len; 
        cin >> brick.color;
        brick.color--;    // будем использовать 0-based нумерацию цветов

        bricks[brick.color].emplace_back(brick);
    }

    // рассчитаем валидные длины разбиения оригинальной стены на две стены
    vector<int> len_candidates;
    bool ok = get_possible_lengths(bricks, len_candidates);

    // если валидных длин не нашлось
    if(len_candidates.size() == 0 || !ok) 
    {
        cout << "NO" << endl;
        return 0;
    }

    // строим стену с одной из валидных длин. 
    // можем взять любую из валидных длин.
    // еще раз напомним: раз мы можем построить
    // стену с этой длиной, значит мы точно сможем
    // построить и вторую стену из оставшихся кирпичей
    vector<int> result;
    build_wall(bricks, len_candidates[0], result);

    cout << "YES" << endl;
    cout << result << endl;

    return 0;
}
