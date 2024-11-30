#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void findAllLIS(vector<int>& arr) {
    int n = arr.size();

    // Inisialisasi tabel DP dengan panjang 1 untuk setiap elemen
    vector<int> lis_lengths(n, 1);

    // Loop melalui elemen array untuk menghitung panjang LIS
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && lis_lengths[i] < lis_lengths[j] + 1) {
                lis_lengths[i] = lis_lengths[j] + 1;
            }
        }
    }

    // Cetak lis_lengths
    cout << "lis_lengths: ";
    printArray(lis_lengths);

    // Cari panjang maksimum dari LIS
    int max_length = *max_element(lis_lengths.begin(), lis_lengths.end());
    cout << "Panjang Largest Monotonically Increasing Subsequence: " << max_length << endl;

    // Inisialisasi vektor untuk menyimpan semua LIS yang memiliki panjang maksimal
    vector<vector<int>> all_lis_sequences;

    // Rekursif untuk mencari semua LIS dengan panjang maksimal
    function<void(vector<int>, int, int)> findLIS = [&](vector<int> current_sequence, int current_length, int current_index) {
        if (current_length == 0) {
            reverse(current_sequence.begin(), current_sequence.end());
            all_lis_sequences.push_back(current_sequence);
            return;
        }

        for (int i = current_index - 1; i >= 0; --i) {
            if (lis_lengths[i] == current_length && arr[i] < current_sequence.back()) {
                current_sequence.push_back(arr[i]);
                findLIS(current_sequence, current_length - 1, i);
                current_sequence.pop_back();  // Backtrack
            }
        }
    };

    // Temukan semua LIS dengan panjang maksimal
    for (int i = 0; i < n; ++i) {
        if (lis_lengths[i] == max_length) {
            findLIS({arr[i]}, max_length - 1, i);
        }
    }

    // Cetak semua LIS dengan panjang maksimal
    for (const auto& lis_sequence : all_lis_sequences) {
        printVector(lis_sequence);
    }
}

int main() {
    vector<int> arr = {4, 1, 13, 7, 0, 2, 8, 11, 3};
    findAllLIS(arr);

    return 0;
}
