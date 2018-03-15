#include <iostream>
#include <time.h>
#include "arithmetics.h"

int main() {
    std::cout << "YOU SUCK, World!" << std::endl;
    arithmetics arithmetics1;

    arithmetics1.setSeed(arithmetics::to_binary(231512222130));


    long long a1 = 9973, b1 = 16, c1 = 21;
//    long long d1 = mulmod(a1, b1, c1);
//    printf("d = %lli", d1);

    arithmetics::bigInt a = arithmetics::to_binary(2222);
    arithmetics::bigInt b = arithmetics::to_binary(2442);
    arithmetics::bigInt c = arithmetics::to_binary(8);

//    arithmetics::bigInt d = arithmetics1.multiply_mod(a, b, c);
//    printf("d = %lli", arithmetics1.to_dec(d));

   /* bool p = arithmetics1.isPrime(a);
    if (p)
        std::cout << "\nTRUE";
    else
        std::cout << "\nFalse";*/
    unsigned int start_time =  clock(); //
   arithmetics1.generateKeys(a, b, c);
    arithmetics::result open = arithmetics1.openKey;
    arithmetics::result closed = arithmetics1.closedKey;
    printf("done\n");
//    std::cout<< "closed key: " << arithmetics1.to_dec(closed.first) << " " << arithmetics1.to_dec(closed.second) << std::endl;
//    std::cout<< "open key: " << arithmetics1.to_dec(open.first) << " " << arithmetics1.to_dec(open.second) << std::endl;
    arithmetics::bigInt c_ = arithmetics1.encrypt(arithmetics1.to_binary(458389122345));
    printf("encr: %lli \n", arithmetics1.to_dec(c_));
    c_ = arithmetics1.decrypt(c_);
    printf("decr: %lli \n", arithmetics1.to_dec(c_));
    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = (end_time - start_time) / 60000; // искомое время
    printf("Time is : %u \n", search_time);
    /*a = arithmetics1.random(40);
    printf("%lli", arithmetics1.to_dec(a));*/
    return 0;
}