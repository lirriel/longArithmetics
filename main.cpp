#include <iostream>
#include "arithmetics.h"

#define DEBUG


void extended_euclid(long a, long b, long *x, long *y, long *d)

/* calculates a * *x + b * *y = gcd(a, b) = *d */

{

    long q, r, x1, x2, y1, y2;


    if (b == 0) {

        *d = a, *x = 1, *y = 0;

        return;

    }

    x2 = 1, x1 = 0, y2 = 0, y1 = 1;

#ifdef DEBUG
    printf("------------------------------");
    printf("-------------------\n");
    printf("q    r    x    y    a    b    ");
    printf("x2   x1   y2   y1\n");
    printf("------------------------------");
    printf("-------------------\n");
#endif

    while (b > 0) {

        q = a / b, r = a - q * b;

        *x = x2 - q * x1, *y = y2 - q * y1;

        a = b, b = r;

        x2 = x1, x1 = *x, y2 = y1, y1 = *y;

#ifdef DEBUG
        printf("%4ld %4ld %4ld %4ld ", q, r, *x, *y);
        printf("%4ld %4ld %4ld %4ld ", a, b, x2, x1);
        printf("%4ld %4ld\n", y2, y1);
#endif

    }

    *d = a, *x = x2, *y = y2;

#ifdef DEBUG
    printf("------------------------------");
    printf("-------------------\n");
#endif

}

long long mulmod (unsigned long long a, unsigned long long b, const unsigned long long n)
{
    // ������� ������, ���������� �� �������� ���������� ������������ � �����
    if (a >= n)
        a %= n;
    if (b >= n)
        b %= n;
    unsigned long long res = 0;
    while (b)
        if (b % 2 != 0)
        {
            res += a;
            while (res >= n)
                res -= n;
            --b;
        }
        else
        {
            a *= 2;
            while (a >= n)
                a -= n;
            b /= 2;
        }
    a = res;
    return a;
}

int main() {
    std::cout << "YOU SUCK, World!" << std::endl;
    arithmetics arithmetics1;

    arithmetics1.setSeed(arithmetics1.to_binary(231530));


    long long a1 = 9973, b1 = 16, c1 = 21;
//    long long d1 = mulmod(a1, b1, c1);
//    printf("d = %lli", d1);

    arithmetics::bigInt a = arithmetics1.to_binary(2222);
    arithmetics::bigInt b = arithmetics1.to_binary(2442);
    arithmetics::bigInt c = arithmetics1.to_binary(8);

//    arithmetics::bigInt d = arithmetics1.multiply_mod(a, b, c);
//    printf("d = %lli", arithmetics1.to_dec(d));

   /* bool p = arithmetics1.isPrime(a);
    if (p)
        std::cout << "\nTRUE";
    else
        std::cout << "\nFalse";*/

   arithmetics1.generateKeys(a, b, c);
    arithmetics::result open = arithmetics1.openKey;
    arithmetics::result closed = arithmetics1.closedKey;
//    std::cout<< "closed key: " << arithmetics1.to_dec(closed.first) << " " << arithmetics1.to_dec(closed.second) << std::endl;
//    std::cout<< "open key: " << arithmetics1.to_dec(open.first) << " " << arithmetics1.to_dec(open.second) << std::endl;
    arithmetics::bigInt c_ = arithmetics1.encrypt(arithmetics1.to_binary(12394));
    std::cout << "encr: " << arithmetics1.to_dec(c_) << std::endl;
    c_ = arithmetics1.decrypt(c_);
    std::cout << "decr: " << arithmetics1.to_dec(c_);

    /*a = arithmetics1.random(40);
    printf("%lli", arithmetics1.to_dec(a));*/
    return 0;
}