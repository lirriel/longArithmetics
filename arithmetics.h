//
// Created by MiBook on 07.01.2018.
//

#ifndef LONGAR_ARITHMETICS_H
#define LONGAR_ARITHMETICS_H

#include <assert.h>
#include "vector"
#include <string>

class arithmetics
{
public:
    arithmetics() {
        zero = to_binary(0);
        one = to_binary(1);
        two = to_binary(2);
    }
    typedef std::vector<int> bigInt;
    typedef std::pair <bigInt, bigInt> result;

    bigInt stringToBinary(std::string s);

    bigInt sum(bigInt A, bigInt B);

    bigInt trim(bigInt A);

    int compare(bigInt A, bigInt B);

    bigInt subtract(bigInt A, bigInt B);

    bigInt timesBase(bigInt A, int k);

    bigInt divide(bigInt A, bigInt B);

    bigInt mod(bigInt A, bigInt B);

    bigInt karatsuba(bigInt A, bigInt B);

    bigInt to_binary(int x);

    bigInt normalize(bigInt A);

    int to_dec(bigInt a);

    bigInt rand();

    bigInt b_pow(bigInt a, bigInt n);

    void print(bigInt a);

    void transform_num(bigInt n, bigInt& p, bigInt& q);

    template <typename V>
    void pop_front(V & v)
    {
        assert(!v.empty());
        v.erase(v.begin());
    }

    void setSeed(bigInt a);

    bool isPrime(bigInt A);

    bigInt gcd(bigInt A, bigInt B);

private:
    bool miller_rabin(bigInt n, bigInt b);

    result divisionAlgo(bigInt A, bigInt B);

    result divisionMainAlgo(bigInt A, bigInt B);

    bigInt seed;
    bigInt zero;
    bigInt one;
    bigInt two;
};


#endif //LONGAR_ARITHMETICS_H
