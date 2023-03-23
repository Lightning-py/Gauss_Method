#pragma once

#include <iostream>
#include <fstream>
#include <numeric>

#include "tools.hpp"

using tls::frac_type;

class Frac
{
    public:
        frac_type numerator;
        frac_type denominator;
        double representation;

        Frac()
        {
            numerator = 0;
            denominator = 1;
            representation = 0;
        }

        Frac(int num, int den)
        {
            numerator = num;
            denominator = den;

            frac_type gcd = std::gcd(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;
            
            representation = num / den;
        }

        Frac (int num)
        {
            numerator = num;
            denominator = 1;
            representation = num;
        }

        void reduce()
        {
            frac_type gcd = std::gcd(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;

            if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) 
            {
                numerator *= -1;
                denominator *= -1;
            }

        }
};


Frac operator+(Frac frac_1, Frac frac_2)
{
    Frac result(frac_1.numerator * frac_2.denominator + frac_2.numerator * frac_1.denominator, frac_1.denominator * frac_2.denominator);
    result.reduce();
    return result;
}


Frac operator-(Frac frac_1, Frac frac_2)
{
    Frac result(frac_1.numerator * frac_2.denominator - frac_2.numerator * frac_1.denominator, frac_1.denominator * frac_2.denominator);
    result.reduce();
    return result;
}


Frac operator*(Frac frac_1, Frac frac_2)
{
    Frac result(frac_1.numerator * frac_2.numerator, frac_1.denominator * frac_2.denominator);
    result.reduce();
    return result;
}


Frac operator/(Frac frac_1, Frac frac_2)
{
    Frac result(frac_1.numerator * frac_2.denominator, frac_1.denominator * frac_2.numerator);
    result.reduce();
    return result;
}


Frac operator+(frac_type num, Frac frac)
{
    Frac result(frac.numerator + frac.denominator * num, frac.denominator);
    result.reduce();
    return result;
}


Frac operator-(Frac frac, frac_type num)
{
    Frac result(frac.numerator - frac.denominator * num, frac.denominator);
    result.reduce();
    return result;
}


Frac operator*(Frac frac, frac_type num)
{
    Frac result(frac.numerator * num, frac.denominator);
    result.reduce();
    return result;
}


Frac operator/(Frac frac, frac_type num)
{
    if (num == 0) { return Frac(0, 1); }
    Frac result(frac.numerator, frac.denominator * num);
    result.reduce();
    return result;
}


Frac operator*=(Frac& frac, frac_type num)
{
    frac = frac * num;
    return frac;
}

std::ostream& operator<<(std::ostream& stream, const Frac& frac)
{
    stream << frac.numerator << " / " << frac.denominator;
    return stream;
}

std::istream& operator>>(std::istream& stream, Frac& frac)
{
    frac_type numerator;
    frac_type denominator;

    stream >> numerator;
    stream >> denominator;

    frac = Frac(numerator, denominator);

    return stream;
}

bool operator==(Frac frac_1, Frac frac_2)
{
    frac_1.reduce();
    frac_2.reduce();

    if (frac_1.numerator == frac_2.numerator && frac_1.denominator == frac_2.denominator) { return true; }
    return false;
}