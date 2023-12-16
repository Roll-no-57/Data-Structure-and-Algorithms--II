#include <bits/stdc++.h>
using namespace std;
// The given array is 0 indexed
void binarySearch(vector<int> &array, int left, int right, int key)
{
    int leftArr = left;
    int rightArr = right;
    while (leftArr <= rightArr)
    {
        int mid = (leftArr + rightArr) / 2;
        if (array[mid] == key)
        {
            cout << "Found at index " << mid << endl;
            return;
        }
        else if (array[mid] < key)
        {
            leftArr = mid + 1;
        }
        else
        {
            rightArr = mid - 1;
        }
    }

    cout << "Not found" << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8};
    int key = 5;
    binarySearch(array, 0, array.size() - 1, key);
    return 0;
}