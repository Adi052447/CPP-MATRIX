#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <iostream>

namespace matrix {

class SquareMat {
private:
    double* data;   // מערך חד-ממדי בגודל n×n
    int n;          // גודל המטריצה (n×n)

public:
    // ---------- בנאים ו־Rule of 3 ----------
    SquareMat(int n, double initVal = 0.0);
    SquareMat(const SquareMat& other);
    SquareMat& operator=(const SquareMat& other);
    ~SquareMat();

    // ---------- גישה לאיברים ----------
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    double* operator[](int i);
    const double* operator[](int i) const;

    int getN() const;
    double sum() const;

    // ---------- פעולות אריתמטיות ----------
    SquareMat operator+(const SquareMat& rhs) const;
    SquareMat& operator+=(const SquareMat& rhs);

    SquareMat operator-(const SquareMat& rhs) const;
    SquareMat operator-() const;

    SquareMat operator*(const SquareMat& rhs) const;
    SquareMat& operator*=(const SquareMat& rhs);

    SquareMat operator*(double s) const;
    SquareMat& operator*=(double s);

    SquareMat operator/(double s) const;
    SquareMat& operator/=(double s);
    SquareMat operator%(const SquareMat& rhs) const;
    SquareMat operator%(int scalar) const;
    SquareMat& operator%=(const SquareMat& rhs);
    SquareMat& operator%=(int scalar);

    // ---------- השוואות ----------
    bool operator==(const SquareMat& rhs) const;
    bool operator!=(const SquareMat& rhs) const;
    bool operator<(const SquareMat& rhs) const;
    bool operator<=(const SquareMat& rhs) const;
    bool operator>(const SquareMat& rhs) const;
    bool operator>=(const SquareMat& rhs) const;

    // ---------- טרנספוז ----------
    SquareMat operator~() const;

    // ---------- אינקרמנט / דקרמנט ----------
    SquareMat& operator++();       // ++mat
    SquareMat operator++(int);     // mat++
    SquareMat& operator--();       // --mat
    SquareMat operator--(int);     // mat--

    // ---------- חזקה ----------
    SquareMat operator^(int e) const;

    // ---------- דטרמיננטה ----------
    double operator!() const;
};

// ---------- אופרטורים חיצוניים ----------
SquareMat operator*(double s, const SquareMat& m);
std::ostream& operator<<(std::ostream& out, const SquareMat& m);

} // namespace matrix

#endif // SQUAREMAT_HPP
