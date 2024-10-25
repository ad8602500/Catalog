# Catalog

# Shamir's Secret Sharing Algorithm Implementation

This project is a C++ implementation of a simplified version of Shamir's Secret Sharing algorithm. It reads polynomial roots from a JSON file, decodes the values, and calculates the constant term \( c \) of the polynomial using Lagrange interpolation.

## Prerequisites

Before running the code, ensure you have the following:

- A C++ compiler (e.g., g++, clang++)
- CMake (optional, for building with CMake)
- [nlohmann/json](https://github.com/nlohmann/json) library for JSON parsing.

## Installation

1. **Clone the repository**:
   ```bash
   git clone <repository_url>
   cd <repository_name>


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


long long decode(const string &value, int base) {
    long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : (tolower(digit) - 'a' + 10));
    }
    return result;
}


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
   
    ifstream file("input.json");
    json j;
    file >> j;

    // Extract keys
    int n = j["keys"]["n"];
    int k = j["keys"]["k"];
    vector<int> x_values;
    vector<long long> y_values;

   
    for (int i = 1; i <= n; ++i) {
        int base = j[std::to_string(i)]["base"];
        string value = j[std::to_string(i)]["value"];
        
        int x = i; // key is the index
        long long y = decode(value, base);
        
        x_values.push_back(x);
        y_values.push_back(y);
    }

 
    long long secret = lagrangeInterpolation(x_values, y_values, k);


    cout << "Secret (c) = " << secret << endl;

    return 0;
}


