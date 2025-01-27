#include <bits/stdc++.h>
using namespace std;

void bucketSort(vector<float>& arr) {
    if (arr.empty()) return;
    
    const int n = arr.size();
    vector<list<float>> buckets(n);
    
    float max_val = arr[0];
    float min_val = arr[0];
    for (float num : arr) {
        max_val = max(max_val, num);
        min_val = min(min_val, num);
    }
    float range = max_val - min_val;
    
    for (float num : arr) {
        if (range == 0) {
            buckets[0].push_back(num);
            continue;
        }
        
        int bucket_idx = (int)((num - min_val) * (n - 1) / range);
        buckets[bucket_idx].push_back(num);
    }
    
    for (auto& bucket : buckets) {
        bucket.sort();
    }
    
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float num : bucket) {
            arr[index++] = num;
        }
    }
}

void bucketSortInt(vector<int>& arr) {
    if (arr.empty()) return;
    
    const int n = arr.size();
    vector<list<int>> buckets(n);
    
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;
    
    for (int num : arr) {
        if (range == 1) {
            buckets[0].push_back(num);
            continue;
        }
        int bucket_idx = (int)((num - min_val) * (n - 1) / (range - 1));
        buckets[bucket_idx].push_back(num);
    }
    
    for (auto& bucket : buckets) {
        bucket.sort();
    }
    
    int index = 0;
    for (const auto& bucket : buckets) {
        for (int num : bucket) {
            arr[index++] = num;
        }
    }
}

int main() {
    vector<float> arr_float = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    bucketSort(arr_float);
    for(int i=0; i<arr_float.size(); i++)
        cout << arr_float[i] << " ";
    cout << endl;
    
    vector<int> arr_int = {54, 12, 84, 34, 95, 25};
    bucketSortInt(arr_int);
    for(int i=0; i<arr_int.size(); i++)
        cout << arr_int[i] << " ";
    cout << endl;
    
    return 0;
}
