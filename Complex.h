//
// Created by Artem on 18.04.2022.
//

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex
{
    long long a; //a+b*i
    long long b; //a+b*i
public:
    Complex() : a(0), b(0) {};
    Complex(long long a, long long b) : a(a), b(b) {};
    explicit Complex(long long a) : a(a), b(0) {};

    void random(const long long &n);

    friend double abs(const Complex &c);
    friend std::ostream& operator <<(std::ostream &out, const Complex &c);

    friend bool operator ==(const Complex &c1, const Complex &c2);
    friend bool operator !=(const Complex &c1, const Complex &c2);
    friend bool operator >(const Complex &c1, const Complex &c2);
    friend bool operator <(const Complex &c1, const Complex &c2);
    friend bool operator >=(const Complex &c1, const Complex &c2);
    friend bool operator <=(const Complex &c1, const Complex &c2);
};

#endif
