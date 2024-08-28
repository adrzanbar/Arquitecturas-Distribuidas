#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

long double calcular_logaritmo_taylor(long double x, int n_terms) {
    if (x <= 1) return 0;
    
    long double y = (x - 1) / (x + 1);
    long double y_squared = y * y;
    long double result = y;
    long double term = y;
    
    for (int i = 1; i < n_terms; i += 2) {
        term *= y_squared;
        result += term / (2 * i + 1);
    }
    
    return 2 * result;
}

int main() {
    long double num;
    int n_terms = 10000000;

    cout << "Ingrese el número (mayor a 1500000): ";
    cin >> num;

    auto start = chrono::high_resolution_clock::now();
    long double resultado = calcular_logaritmo_taylor(num, n_terms);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(15);
    cout << "ln(" << num << ") = " << resultado << endl;
    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos." << endl;

    return 0;
}
