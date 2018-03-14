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
#include <stdlib.h>     /* srand, rand */
#include <time.h>
//#define DEBUG

arithmetics::bigInt arithmetics::sum(bigInt A, bigInt B)
{
    bool f = false;
    if (A[0] == 1  && B[0] == 1) {
        B[0] = 0;
        A[0] = 0;
        f = true;
    }

    if (A[0] == 1 && B[0] == 0) {
        A[0] = 0;
        return subtract(B, A);
    }

    if (B[0] == 1 && A[0] == 0) {
        B[0] = 0;
        return subtract(A, B);
    }

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
    if (f) B[0] = 1;
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
    if (A[0] == 0 && B[0] == 1) {
        B[0] = 0;
        return sum(A, B);
    }

    if (A[0] == 1 && B[0] == 0) {
        B[0] = 1;
        return sum(A,B);
    }
    // вычитание положительного из отрицательного!!!!
    int k = compare(A, B);
    bool  f = false;
    if (k == 2) {
        if (A[0] == 0 && B[0] == 0)
            f = true;
        A.swap(B);
    }

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
    if (f)
        A[0] = 1;
    else
        A[0] = 0;
    return A;
}

arithmetics::bigInt arithmetics::to_binary(int x) {
    int m;
    bigInt arr;
    bool f = false;
    if (x < 0) {
        f = true;
        x = -x;
    }
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
    if (f)
        arr[0] = 1;
    return arr;
}

void arithmetics::print(bigInt a)
{
    std::cout << a[0] << " ";
    for (int i = 1; i < a.size(); ++i)
        std::cout << a[i];
}

long long arithmetics::to_dec(bigInt a)
{
    long long x = 0;
    for (long long i = a.size() - 1; i > 0; --i)
        x += (a[i] * pow(2, a.size() - i - 1));
    if (a[0] == 1)
        x *= -1;
    return x;
}

arithmetics::bigInt arithmetics::karatsuba(bigInt A, bigInt B)
{
    bigInt C;
    bool f1 = false;
    if ((A[0] + B[0]) == 1)
        f1 = true;
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
    if (f1)
        P6[0]=1;
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
    bigInt q = zero;
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

arithmetics::bigInt arithmetics::rnd() {
    bigInt m = to_binary(10000000);
    bigInt a = to_binary(2);
    bigInt c = to_binary(3);
    bigInt x = seed; // x объявляется статической переменной
    x = divisionMainAlgo(sum(karatsuba(a, x),c), m).second; // формула
    seed = x;
    return x;
}

arithmetics::bigInt arithmetics::b_pow(arithmetics::bigInt a, arithmetics::bigInt n) {
    if (compare(n, zero) == 3)
        return a;

    if (compare(n, one) == 3)
        return a;

    if (n[n.size() - 1] == 1)
        return karatsuba(b_pow(a, subtract(n, one)), a);
    else {
        bigInt b = b_pow(a, divBase(n, 1));
        return karatsuba(b, b);
    }
}

arithmetics::bigInt arithmetics::mod(arithmetics::bigInt A, arithmetics::bigInt B) {
    return trim(divisionMainAlgo(A, B).second);
}

arithmetics::bigInt arithmetics::div(arithmetics::bigInt A, arithmetics::bigInt B) {
    return divisionMainAlgo(A, B).first;
}

void arithmetics::setSeed(arithmetics::bigInt a) {
    seed = a;
}

void arithmetics::transform_num(arithmetics::bigInt n, arithmetics::bigInt &p, arithmetics::bigInt &q) {
    bigInt p_res = zero;
    while (n[n.size() - 1] == 0)
    {
        p_res = sum(p_res, one);
        n = divBase(n, 1);
    }
    p = p_res;
    q = n;
}

bool arithmetics::miller_rabin(arithmetics::bigInt n, arithmetics::bigInt b) {
    if (compare(b, two) == 2)
        b = two;

    for (bigInt g; compare(g = gcd(n, b), one) != 3; b = sum(b, one))
        if (compare(n, g) == 1)
            return false;

    bigInt n_1 = subtract(n, one);
    bigInt p, q;

    // n - 1 == q * 2^p
    transform_num(n_1, p, q);
    bigInt remainder = pow_mod(b, q, n);
    if (compare(remainder, one) == 3 || compare(remainder, n_1) == 3)
        return true;

    for (bigInt i = one; compare(i, p) == 2; i = sum(i, one)) {
        remainder = multiply_mod(remainder, remainder, n);
        if (compare(remainder, n_1) == 3)
            return true;
    }

    return false;
}

arithmetics::bigInt arithmetics::gcd(arithmetics::bigInt A, arithmetics::bigInt B) {
    if (compare(B, zero) == 3)
        return A;
    return gcd(B, mod(A, B));
}

bool arithmetics::isPrime(arithmetics::bigInt A) {
    int c = compare(A, two);
    if (c == 3)
        return true;
    if (c == 2 || A[A.size() - 1] == 0)
        return false;

    bigInt B = sum(mod(rnd(), subtract(A, two)), two);
    return miller_rabin(A, B);
}

arithmetics::bigInt arithmetics::stringToBinary(std::string s) {
    bigInt a;
    for (char i : s) {
        int k = i - '0';
        a.push_back(k);
    }
    return a;
}

void arithmetics::generateKeys(arithmetics::bigInt p, arithmetics::bigInt q, arithmetics::bigInt e) {
    bool f = false;
    while (!f)
    {
        p = random(256);
        f = isPrime(p);
//        std::cout << "p = " << to_dec(p) << " : " << f << std::endl;
    }

    while (!isPrime(q) || compare(p, q) == 3)
    {
        q = random(240);
//        std::cout << "q= " << to_dec(q) << std::endl;
    }
    bigInt N = karatsuba(p, q);
    if (!isPrime(p) || !isPrime(q))
        return;

    bigInt eu = euler(p, q);
    while (compare(gcd(eu, e), one) != 3 && compare(eu, e) == 1)
        e = random(120);
    result _openKey = std::make_pair(e, N);
    std::swap(openKey, _openKey);

    if (compare(gcd(e, eu), one) != 3)
        return;

    bigInt x, y; // y is needed
    gcd(eu, e, x, y);
    if (y[0] == 1)
        y = sum(y, eu);
    result _closedKey = std::make_pair(y, N);
    std::swap(closedKey, _closedKey);
}

arithmetics::bigInt
arithmetics::gcd(arithmetics::bigInt A, arithmetics::bigInt B, arithmetics::bigInt &x, arithmetics::bigInt &y) {
    bigInt q, r, x1, x2, y1, y2, d;

    if (compare(B, zero) == 0) {
        d = A;
        x = one;
        y = one;
        return d;
    }

    x2 = one;
    x1 = zero;
    y2 = zero;
    y1 = one;

    while (compare(B, zero) == 1) {
        q = div(A, B);
        r = subtract(A, karatsuba(q , B));

        bigInt pr = karatsuba(q, x1);
        x = subtract(x2, pr);
        pr = karatsuba(q, y1);
        y = subtract(y2, pr);

        A = B;
        B = r;

        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }

    d = A;
    x = x2;
    y = y2;
    return d;
}

arithmetics::bigInt arithmetics::euler(arithmetics::bigInt p, arithmetics::bigInt q) {
    return karatsuba(subtract(p, one), subtract(q, one));;
}

arithmetics::bigInt arithmetics::divBase(arithmetics::bigInt A, int k) {
    A.erase(A.end() - k, A.end());
    if (compare(A, zero) == 3)
        return one;
    return A;
}

arithmetics::bigInt arithmetics::pow_mod(arithmetics::bigInt& A, arithmetics::bigInt B, arithmetics::bigInt n) {
    bigInt r = one;
    while (compare(B, zero) != 3) {
        if (B[B.size() - 1] == 1) {
            r = multiply_mod(r, A, n);
            B[B.size() - 1] = 0;
        }
        else {
            A = multiply_mod(A, A, n);
            B = divBase(B, 1);
        }
    }
    return r;
}

arithmetics::bigInt arithmetics::multiply_mod(arithmetics::bigInt& A, arithmetics::bigInt B, arithmetics::bigInt n) {
    if (compare(A, n) != 2)
        A = mod(A, n);

    if (compare(B, n) != 2)
        B = mod(B, n);

    bigInt r = zero;

    while (compare(B, zero) != 3) {
        if (B[B.size() - 1] == 1) {
            r = sum(r, A);
            while (compare(r, n) != 2)
                r = subtract(r, n);
            B[B.size() - 1] = 0;
        }
        else {
            A = timesBase(A, 1);
            while (compare(A, n) != 2)
                A = subtract(A, n);
            B = divBase(B, 1);
        }
    }

    return r;
}

arithmetics::bigInt arithmetics::encrypt(arithmetics::bigInt m) {
    return pow_mod(m, openKey.first, openKey.second);
}

arithmetics::bigInt arithmetics::decrypt(arithmetics::bigInt c) {
    return pow_mod(c, closedKey.first, closedKey.second);
}

arithmetics::bigInt arithmetics::random(int size) {
    bigInt a;
    a.push_back(0);
    for (int i = 0; i < size; ++i) {
        int j = rand() % 2;
        a.push_back(j);
    }
    a[1] = 1;
    return a;
}

