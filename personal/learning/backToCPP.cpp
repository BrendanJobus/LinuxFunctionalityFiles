#include <iostream>
#include <cassert>
#include "backToCPP.hpp"

class Fraction {
private:
    int m_numerator;
    int m_denominator;   

public:
    Fraction(int numerator = 0, int denominator = 1) : m_numerator{numerator}, m_denominator{denominator}
    {
        assert(denominator != 0);
    }

    int getNumerator() { return m_numerator; }
    int getDenomintor() { return m_denominator; }
    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};




int main() {
    Fraction f;
    Fraction frac{5, 3};
    std::cout << frac.getNumerator() << "/" << frac.getDenomintor() << '\n';
    return 0;
}