#include <bits/stdc++.h>

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}

template<typename T>
void selectionSortGeneric(std::vector<T>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}

int main() {
    std::vector<int> arr = {64, 25, 12, 22, 11};
    selectionSort(arr);
    for(int i=0; i<arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::vector<double> arr_double = {64.5, 25.1, 12.7, 22.3, 11.9};
    selectionSortGeneric(arr_double);
    for(int i=0; i<arr_double.size(); i++)
        std::cout << arr_double[i] << " ";
    std::cout << std::endl;
    
    return 0;
}
