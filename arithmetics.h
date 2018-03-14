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

    bigInt divBase(bigInt A, int k);

    bigInt div(bigInt A, bigInt B);

    bigInt mod(bigInt A, bigInt B);

    bigInt encrypt(bigInt m);

    bigInt decrypt(bigInt c);

    // A *= B (mod n)
    bigInt multiply_mod(bigInt& A, bigInt B, bigInt n);

    // A ^ B (mod n)
    bigInt pow_mod(bigInt& A, bigInt B, bigInt n);

    bigInt karatsuba(bigInt A, bigInt B);

    bigInt to_binary(int x);

    bigInt normalize(bigInt A);

    long long to_dec(bigInt a);

    bigInt rnd();

    bigInt random(int size);

    bigInt b_pow(bigInt a, bigInt n);

    void print(bigInt a);

    void transform_num(bigInt n, bigInt& p, bigInt& q);

    template <typename V>
    void pop_front(V & v)
    {
        assert(!v.empty());
        v.erase(v.begin());
    }

    bigInt euler(bigInt p, bigInt q);

    void setSeed(bigInt a);

    bool isPrime(bigInt A);

    bigInt gcd(bigInt A, bigInt B);

    bigInt gcd(bigInt A, bigInt B, bigInt& x, bigInt& y);

    void generateKeys(bigInt p, bigInt q, bigInt e);

    result openKey;
    result closedKey;

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
