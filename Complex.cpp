//
// Created by Artem on 18.04.2022.
//

#include <random>
#include <string>
#include "Complex.h"

std::random_device rd;
std::mt19937 mersenne(rd());

void Complex::randomIntComponents(const unsigned &n)
{
    a = mersenne() % (n+1);
    b = mersenne() % (n+1);
    if(mersenne() % 2) a=-a;
    if(mersenne() % 2) b=-b;
}

double abs(const Complex &c)
{
    return std::sqrt(c.a*c.a + c.b*c.b);
}

std::ostream& operator <<(std::ostream &out, const Complex &c)
{
    std::string str;
    if(c == Complex(0,0))
    {
        out << "0";
        return out;
    }
    if(c.a != 0)
    {
        str = std::to_string(c.a);
    }
    if(c.b != 0)
    {
        if(c.b>0 && c.a!=0)
        {
            str += "+";
        }
        str += std::to_string(c.b)+"i";
    }
    out << str;
    return out;
}

bool operator ==(const Complex &c1, const Complex &c2)
{
    return (c1.a==c2.a && c1.b==c2.b);
}

bool operator !=(const Complex &c1, const Complex &c2)
{
    return !(c1==c2);
}

bool operator >(const Complex &c1, const Complex &c2)
{
    if(abs(c1) != abs(c2)) return (abs(c1) > abs(c2));
    if(c1.a != c2.a) return (c1.a > c2.a);
    if(c1.b != c2.b) return (c1.b > c2.b);
    return false;
}

bool operator <(const Complex &c1, const Complex &c2)
{
    return !(c1>c2 || c1==c2);
}

bool operator >=(const Complex &c1, const Complex &c2)
{
    return (c1>c2 || c1==c2);
}

bool operator <=(const Complex &c1, const Complex &c2)
{
    return (c1<c2 || c1==c2);
}
