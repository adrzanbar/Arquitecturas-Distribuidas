#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

const int n_terms = 10000000;
mutex mtx;

void calcular_parcial(long double x, int start, int end, long double& result) {
    long double y = (x - 1) / (x + 1);
    long double y_squared = y * y;
    long double partial_sum = 0;
    long double term = y;
    
    for (int i = start; i < end; i += 2) {
        partial_sum += term / (2 * i + 1);
        term *= y_squared;
    }
    
    lock_guard<mutex> guard(mtx);
    result += partial_sum;
}

int main() {
    long double num;
    int num_threads;
    
    cout << "Ingrese el número (mayor a 1500000): ";
    cin >> num;
    cout << "Ingrese el número de hilos: ";
    cin >> num_threads;

    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    long double result = 0;

    int terms_per_thread = n_terms / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start_index = i * terms_per_thread;
        int end_index = (i + 1) * terms_per_thread;
        threads.emplace_back(calcular_parcial, num, start_index, end_index, ref(result));
    }

    for (auto& th : threads) {
        th.join();
    }

    result *= 2;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(15);
    cout << "ln(" << num << ") = " << result << endl;
    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos." << endl;

    return 0;
}
