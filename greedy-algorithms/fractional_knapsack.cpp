#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);
    double totalValue = 0.0;
    int remaining = capacity;

    for (const auto& item : items) {
        if (remaining <= 0) break;
        if (item.weight <= remaining) {
            totalValue += item.value;
            remaining -= item.weight;
        } else {
            totalValue += item.value * ((double)remaining / item.weight);
            remaining = 0;
        }
    }
    return totalValue;
}

int main() {
    int n, capacity;
    cout << "Enter number of items and capacity: ";
    cin >> n >> capacity;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight for item " << i+1 << ": ";
        cin >> items[i].value >> items[i].weight;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    double maxValue = fractionalKnapsack(capacity, items);
    cout << "Maximum value: " << maxValue << endl;

    return 0;
}