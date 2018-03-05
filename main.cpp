#include <iostream>
#include "arithmetics.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    arithmetics arithmetics1;

    /*int a = 132932423;
    int b = 432;
    std::vector<int> a1 = arithmetics1.to_binary(a);
    std::vector<int> b1 = arithmetics1.to_binary(b);
    int c = arithmetics1.to_dec(arithmetics1.divisionMainAlgo(a1,b1).first);
    std::cout << c << " " << (a/b);*/
    arithmetics1.x_0 = arithmetics1.to_binary(253);
    for (int i = 0; i < 100; ++i) {
        arithmetics::bigInt x1 = arithmetics1.rand();
        int x = arithmetics1.to_dec(x1);
        std::cout << x << std::endl;
    }
    return 0;
}