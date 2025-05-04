#include "SquareMat.hpp"
#include <algorithm>   // std::copy, std::fill
#include <numeric>     // std::accumulate
#include <stdexcept>   // std::invalid_argument, std::out_of_range
#include <iostream>
using namespace matrix;

/* ---------- Rule of Three ---------- */

SquareMat::SquareMat(int n_, double initVal) : data(nullptr), n(n_)
{
    if (n <= 0) throw std::invalid_argument("n must be positive");
    data = new double[n * n];
    std::fill(data, data + n * n, initVal);
}

SquareMat::SquareMat(const SquareMat& other) : data(nullptr), n(other.n)
{
    data = new double[n * n];
    std::copy(other.data, other.data + n * n, data);
}

SquareMat& SquareMat::operator=(const SquareMat& other)
{
    if (this == &other) return *this;

    if (n != other.n) {                // צריך להקצות מחדש
        delete[] data;
        n = other.n;
        data = new double[n * n];
    }
    std::copy(other.data, other.data + n * n, data);
    return *this;
}

SquareMat::~SquareMat()
{
    delete[] data;
}

/* ---------- גישה לאיברים ---------- */

double& SquareMat::operator()(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        throw std::out_of_range("index out of range");
    return data[i * n + j];
}

const double& SquareMat::operator()(int i, int j) const
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        throw std::out_of_range("index out of range");
    return data[i * n + j];
}

double* SquareMat::operator[](int i)
{
    if (i < 0 || i >= n) throw std::out_of_range("row index out of range");
    return data + i * n;          // מצביע לתחילת השורה
}

const double* SquareMat::operator[](int i) const
{
    if (i < 0 || i >= n) throw std::out_of_range("row index out of range");
    return data + i * n;
}

/* ---------- פונקציית-עזר לסכום ---------- */
double SquareMat::sum() const
{
    return std::accumulate(data, data + n * n, 0.0);
}

/* ---------- אופרטורים אריתמטיים ---------- */
SquareMat SquareMat::operator%(const SquareMat& other) const {
    if (n != other.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) {
        res.data[k] = data[k] * other.data[k];
    }
    return res;
}

SquareMat SquareMat::operator+(const SquareMat& rhs) const
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) res.data[k] = data[k] + rhs.data[k];
    return res;
}

SquareMat& SquareMat::operator+=(const SquareMat& rhs)
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    for (int k = 0; k < n * n; ++k) data[k] += rhs.data[k];
    return *this;
}

SquareMat SquareMat::operator-(const SquareMat& rhs) const
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) res.data[k] = data[k] - rhs.data[k];
    return res;
}

SquareMat SquareMat::operator-() const
{
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) res.data[k] = -data[k];
    return res;
}

/* --- כפל מטריצות --- */
SquareMat SquareMat::operator*(const SquareMat& rhs) const
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n, 0.0);

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k)
            for (int j = 0; j < n; ++j)
                res(i, j) += (*this)(i, k) * rhs(k, j);

    return res;
}

SquareMat& SquareMat::operator*=(const SquareMat& rhs)
{
    *this = *this * rhs;
    return *this;
}

/* --- סקלר --- */

SquareMat SquareMat::operator*(double s) const
{
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) res.data[k] = data[k] * s;
    return res;
}

SquareMat& SquareMat::operator*=(double s)
{
    for (int k = 0; k < n * n; ++k) data[k] *= s;
    return *this;
}

SquareMat operator*(double s, const SquareMat& m) { return m * s; }

SquareMat SquareMat::operator/(double s) const
{
    if (s == 0) throw std::invalid_argument("division by zero");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k) res.data[k] = data[k] / s;
    return res;
}

SquareMat& SquareMat::operator/=(double s)
{
    if (s == 0) throw std::invalid_argument("division by zero");
    for (int k = 0; k < n * n; ++k) data[k] /= s;
    return *this;
}

/* --- השוואה (ע"פ סכום איברים) --- */

bool SquareMat::operator==(const SquareMat& rhs) const { return sum() == rhs.sum(); }
bool SquareMat::operator!=(const SquareMat& rhs) const { return !(*this == rhs); }
bool SquareMat::operator< (const SquareMat& rhs) const { return sum()  < rhs.sum(); }
bool SquareMat::operator<=(const SquareMat& rhs) const { return sum() <= rhs.sum(); }
bool SquareMat::operator> (const SquareMat& rhs) const { return sum()  > rhs.sum(); }
bool SquareMat::operator>=(const SquareMat& rhs) const { return sum() >= rhs.sum(); }

/* ---------- טרנספוז ---------- */

SquareMat SquareMat::operator~() const
{
    SquareMat res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res(j, i) = (*this)(i, j);
    return res;
}

/* ---------- ++ / -- ---------- */

SquareMat& SquareMat::operator++()          { for (int k = 0; k < n * n; ++k) ++data[k]; return *this; }
SquareMat  SquareMat::operator++(int)       { SquareMat tmp(*this); ++(*this); return tmp; }
SquareMat& SquareMat::operator--()          { for (int k = 0; k < n * n; ++k) --data[k]; return *this; }
SquareMat  SquareMat::operator--(int)       { SquareMat tmp(*this); --(*this); return tmp; }

/* ---------- חזקת מטריצה (שלם לא-שלילי) ---------- */

SquareMat SquareMat::operator^(int e) const
{
    if (e < 0) throw std::invalid_argument("negative exponent");

    SquareMat base(*this);
    SquareMat res(n, 0.0);
    for (int i = 0; i < n; ++i) res(i, i) = 1;   // יחידה

    while (e) {
        if (e & 1) res *= base;
        base *= base;
        e >>= 1;
    }
    return res;
}

/* ---------- דטרמיננטה (רק n ≤ 3 לשם דוגמה) ---------- */

double SquareMat::operator!() const {
    if (n == 1)
        return data[0];

    if (n == 2)
        return data[0] * data[3] - data[1] * data[2];

    double det = 0.0;

    for (int k = 0; k < n; ++k) {
        // צור מטריצה מוקטנת (minor)
        SquareMat temp(n - 1);

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == k) continue; // דילוג על העמודה שנמחקת

                int newRow = i - 1;
                int newCol = (j < k) ? j : j - 1;

                temp(newRow, newCol) = (*this)(i, j);
            }
        }

        double cofactor = (k % 2 == 0 ? 1 : -1) * (*this)(0, k) * !temp;
        det += cofactor;
    }

    return det;
}

    
 
/* ---------- הדפסה ---------- */

int SquareMat::getN() const {
    return n;
}

namespace matrix {

std::ostream& operator<<(std::ostream& os, const SquareMat& m) {
    for (int i = 0; i < m.getN(); ++i) {
        os << "[ ";
        for (int j = 0; j < m.getN(); ++j) {
            os << m(i, j);
            if (j + 1 < m.getN()) os << ' ';
        }
        os << " ]\n";
    }
    return os;
}

SquareMat operator*(double s, const SquareMat& m) {
    return m * s;
}

} // namespace matrix

    


