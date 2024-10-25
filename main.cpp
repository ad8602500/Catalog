#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Function to decode the y value in the given base
long long decode(const string &value, int base) {
    long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : (tolower(digit) - 'a' + 10));
    }
    return result;
}

// Lagrange Interpolation to find the constant term c
long long lagrangeInterpolation(const vector<int>& x_values, const vector<long long>& y_values, int k) {
    long long c = 0;
    for (int i = 0; i < k; ++i) {
        long long term = y_values[i];
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - x_values[j]) * modInverse(x_values[i] - x_values[j]);
            }
        }
        c += term;
    }
    return c;
}

// Function to compute the modular inverse using Extended Euclidean Algorithm
long long modInverse(long long a, long long m = 1000000007) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

int main() {
    // Read JSON file
    ifstream file("input.json");
    json j;
    file >> j;

    // Extract keys
    int n = j["keys"]["n"];
    int k = j["keys"]["k"];
    vector<int> x_values;
    vector<long long> y_values;

    // Decode the input
    for (int i = 1; i <= n; ++i) {
        int base = j[std::to_string(i)]["base"];
        string value = j[std::to_string(i)]["value"];
        
        int x = i; // key is the index
        long long y = decode(value, base);
        
        x_values.push_back(x);
        y_values.push_back(y);
    }

    // Calculate the constant term c
    long long secret = lagrangeInterpolation(x_values, y_values, k);

    // Output the secret
    cout << "Secret (c) = " << secret << endl;

    return 0;
}
