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
    arithmetics1.setSeed(arithmetics1.to_binary(253));
//    for (int i = 0; i < 100; ++i) {
//        arithmetics::bigInt x1 = arithmetics1.rand();
//        int x = arithmetics1.to_dec(x1);
//        std::cout << x << std::endl;
//    }

    arithmetics::bigInt a = arithmetics1.to_binary(2);
    arithmetics::bigInt b = arithmetics1.to_binary(10);
    std::string s;
    std::cin >> s;
    b = arithmetics1.stringToBinary(s);
    arithmetics1.print(b);
    std::cout << std::endl << arithmetics1.to_dec(b);
//    arithmetics::bigInt c = arithmetics1.b_pow(a, b);
//    arithmetics1.print(c);
//    std::cout << "size = " << c.size();
    return 0;
}