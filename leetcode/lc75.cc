// heap sort / quick sort

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    inline void heapify(vector<int>& arr, int n, int idx) const 
    {
        int largest  = idx;
        const int left = 2 * idx + 1;
        const int right = 2 * idx + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if(right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != idx){
            swap(arr[idx], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    inline void heap_sort(vector<int>& arr) const 
    {
        int sz = arr.size();
        for(int i = sz / 2 - 1; i >= 0; --i)
            heapify(arr, sz, i);

        for(int i = sz - 1; i >= 0; --i){
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }


    inline int partition(vector<int>& arr, int low, int high){
        const int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
            if (arr[j] < pivot){
                i++;
                swap(arr[i], arr[j]);
            }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    inline void quick_sort(vector<int>& arr, int low, int high){
        if (low < high){
            int pi = partition(arr, low, high);
            quick_sort(arr, low, pi - 1);
            quick_sort(arr, pi + 1, high);
        }
    }

public:
    template<int TYPE = 2>
    void sortColors(vector<int>& nums) {
        if constexpr (TYPE == 1)
            heap_sort(nums);
        else
            quick_sort(nums, 0, nums.size() - 1);
    }
};

int main()
{
    vector<int> colors = {2, 0, 2, 1, 1, 0};
    Solution s;
    s.sortColors(colors);
    for(auto clr : colors) cout << clr << " ";
    cout << endl;
    return 0;
}