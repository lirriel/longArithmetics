//
// Created by MiBook on 07.01.2018.
//

#ifndef LONGAR_ARITHMETICS_H
#define LONGAR_ARITHMETICS_H

#include <assert.h>
#include "vector"

class arithmetics
{
public:
    typedef std::vector<int> bigInt;
    typedef std::pair <bigInt, bigInt> result;

    bigInt sum(bigInt A, bigInt B);

    bigInt trim(bigInt A);

    int compare(bigInt A, bigInt B);

    bigInt subtract(bigInt A, bigInt B);

    bigInt timesBase(bigInt A, int k);

    result divisionAlgo(bigInt A, bigInt B);

    result divisionMainAlgo(bigInt A, bigInt B);

    bigInt karatsuba(bigInt A, bigInt B);

    bigInt to_binary(int x);

    bigInt normalize(bigInt A);

    int to_dec(bigInt a);

    bigInt rand();

    void print(bigInt a);

    template <typename V>
    void pop_front(V & v)
    {
        assert(!v.empty());
        v.erase(v.begin());
    }

    bigInt x_0;

};


#endif //LONGAR_ARITHMETICS_H
