//
// Created by MiBook on 07.01.2018.
//

#include <afxres.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "arithmetics.h"
#include<iterator>

arithmetics::bigInt arithmetics::sum(bigInt A, bigInt B)
{
    if (A.size() > B.size())
        while (A.size() != B.size())
            B.insert(B.begin() + 1, 0);

    if (B.size() > A.size())
        while (A.size() != B.size())
            A.insert(A.begin() + 1, 0);

    for (int i = B.size() - 1; i > 0; i--)
    {
        B[i] += A[i];
        B[i - 1] += (B[i] / 2);
        B[i] %= 2;
    }
    if (B[0] == 1)
        B.insert(std::begin(B), 0);
    return B;
}

int arithmetics::compare(bigInt A, bigInt B)
{
    A = trim(A);
    B = trim(B);
    int size_A = A.size();
    int size_B = B.size();

    if (size_A > size_B) // 1 -> A > B
        return 1;

    if (size_B > size_A) // 2 -> A < B
        return 2;

    int j = 1;
    while (j < size_A && A[j] == B[j])
        j++;

    if (j == size_A) // 3 -> A = B
        return 3;

    if (A[j] > B[j])
        return 1;
    else
        return 2;
}

arithmetics::bigInt arithmetics::subtract(bigInt A, bigInt B)
{
    int k = compare(A, B);
    if (k == 2)
        A.swap(B);

    int length = A.size();
    int delta = length - B.size();

    int r = 0;
    int i;
    for (i = length - 1; i - delta > 0 ; --i)
    {
        A[i] -= B[i - delta] + r;

        if (A[i] < 0)
        {
            r = 1;
            A[i] += 2;
        }
        else
        {
            r = 0;
        }
    }

    if (r == 1)
    {
        while (A[i] != 1) {
            A[i] = 1;
            i--;
        }
        A[i] = 0;
    }
    while (A.size() > 2 && A[1] == 0)
        A.erase(A.begin() + 1);

    return A;
}

arithmetics::bigInt arithmetics::to_binary(int x) {
    int m;
    bigInt arr;

    if (x == 0)
    {
        for (int i = 0; i < 2; ++i)
            arr.push_back(0);
        return arr;
    }

    for (int i = 0; x > 0; i++)
    {
        m =  x % 2;
        x = x / 2;
        arr.push_back(m);
    }
    std::reverse(std::begin(arr), std::end(arr));
    arr.insert(std::begin(arr), 0);
    return arr;
}

void arithmetics::print(bigInt a)
{
    std::cout << a[0] << " ";
    for (int i = 1; i < a.size(); ++i)
        std::cout << a[i];
}

int arithmetics::to_dec(bigInt a)
{
    int x = 0;
    for (int i = a.size() - 1; i > 0; --i)
        x += (a[i] * pow(2, a.size() - i - 1));

    return x;
}

arithmetics::bigInt arithmetics::karatsuba(bigInt A, bigInt B)
{
    bigInt C;
    C.push_back(0);

    if (A.size() == 2 && B.size() == 2)
    {
        C.push_back(A[1] * B[1]);
        return C;
    }

    if (A.size() > B.size())
        while (A.size() != B.size())
            B.insert(B.begin() + 1, 0);

    if (B.size() > A.size())
        while (A.size() != B.size())
            A.insert(A.begin() + 1, 0);

    int f = (A.size() - 1) / 2;
    int s = A.size() - f - 1;

    bigInt Xl;
    std::copy(A.begin() + 1, A.begin() + f + 1, std::back_inserter(Xl));
    Xl.insert(Xl.begin(), 0);
    Xl = normalize(Xl);

    bigInt Xr;
    std::copy(A.begin() + f + 1, A.end(), std::back_inserter(Xr));
    Xr.insert(Xr.begin(), 0);
    Xr = normalize(Xr);

    bigInt Yl;
    std::copy(B.begin() + 1, B.begin() + f + 1, std::back_inserter(Yl));
    Yl.insert(Yl.begin(), 0);
    Yl = normalize(Yl);

    bigInt Yr;
    std::copy(B.begin() + f + 1, B.end(), std::back_inserter(Yr));
    Yr.insert(Yr.begin(), 0);
    Yr = normalize(Yr);

    bigInt P1 = karatsuba(Xl, Yl);

    bigInt P2 = karatsuba(Xr, Yr);

    bigInt P3 = karatsuba(sum(Xl, Xr), sum(Yl, Yr));

    bigInt P;
    std::copy(P1.begin(), P1.end(), std::back_inserter(P));
    for (int i = 0; i < 2 * s; ++i)
        P.push_back(0);

    bigInt P4 = subtract(P3, sum(P1,P2));
    for (int i = 0; i < s; ++i)
        P4.push_back(0);

    bigInt P5 = sum(P2,P4);
    bigInt P6 = sum(P5, P);
    P6 = normalize(P6);
    return P6;
}

arithmetics::bigInt arithmetics::normalize(bigInt A) {
    while (A.size() > 2 && A[1] == 0)
        A.erase(A.begin() + 1);
    return A;
}

arithmetics::bigInt arithmetics::timesBase(bigInt A, int k) {
    for (int i = 0; i < k; ++i)
        A.push_back(0);
    return A;
}

arithmetics::result arithmetics::divisionAlgo(bigInt A, bigInt B) {
//    std::cout<< "mult: " << to_dec(A) << " " << to_dec(B) << std::endl;
    bigInt q = to_binary(0);
    bigInt R = bigInt();
    if (compare(A, timesBase(B, 1)) != 2) {
        result r = divisionAlgo(subtract(A, timesBase(B, 1)), B);
        r.first = sum(r.first, to_binary(2));
//        std::cout<< "res: " << to_dec(r.first) << std::endl;
        return r;
    }
    while (A.size() <= B.size())
        A.insert(A.begin() + 1, 0);
    q = to_binary(std::min(static_cast<int>(floor((A.at(1) * 2 + A.at(2)) / B.at(1))), 1));
    bigInt T;
    if (compare(q, to_binary(1)) == 3)
        T = B;
    else
        T = bigInt (2, 0);
    for (int i = 0; i < 2; ++i) {
        if (compare(T, A) == 1) {
            q = subtract(q, to_binary(1));
            T = subtract(T, B);
        }
    }
    R = subtract(A, T);
//    std::cout<< "res: " << to_dec(q) << std::endl;
    return std::make_pair(q, R);
}

arithmetics::result arithmetics::divisionMainAlgo(bigInt A, bigInt B) {
//    std::cout<< "multtp: " << to_dec(A) << " " << to_dec(B) << std::endl;
    int m = A.size();
    int n = B.size();
    bigInt R;
    if (m < n)
    {
//        std::cout<< "res: " << 0 << std::endl;
        return std::make_pair(to_binary(0), A);
    }
    if (m == n)
        if (compare(A, B) == 2)
        {
//            std::cout<< "res: " << 0 << std::endl;
            return std::make_pair(to_binary(0), A);
        }
        else
        {
//            std::cout<< "res: " << 1 << std::endl;
            return std::make_pair(to_binary(1), subtract(A, B));
        }

    if (m == n + 1)
        return divisionAlgo(A, B);
    bigInt q = to_binary(0);
    bigInt q1 = to_binary(0);
    bigInt R1;

    bigInt A1(A);
    A1.erase(A1.begin() + n + 1, A1.end());

    bigInt s(A);
    s.erase(s.begin() + 1, s.begin() + n + 1);

    result r1 = divisionAlgo(A1, B);
    q1 = r1.first;
    R1 = r1.second;
    bigInt T = sum(timesBase(R1, m - n - 1), s);

    result r2 = divisionMainAlgo(T, B);
    q = r2.first;
    R = r2.second;
    q = sum(q, karatsuba(q1, timesBase(to_binary(1), m - n - 1)));
//    std::cout<< "res: " << to_dec(q) << std::endl;
    return std::make_pair(q, R);
}

arithmetics::bigInt arithmetics::trim(arithmetics::bigInt A) {
    while (A.size() > 2 && A.at(1) == 0)
        A.erase(A.begin() + 1);
    return A;
}

arithmetics::bigInt arithmetics::rand() {
    bigInt m = to_binary(100000000);
    bigInt a = to_binary(2);
    bigInt c = to_binary(3);
    static bigInt x = x_0; // x объявляется статической переменной
    x = divisionMainAlgo(sum(karatsuba(a, x),c), m).second; // формула
    x_0 = x;
    return x;
}
