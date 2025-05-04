// adi.gamzu@msmail.ariel.ac.il
#include "SquareMat.hpp"
#include <algorithm>   // std::copy, std::fill
#include <numeric>     // std::accumulate
#include <stdexcept>   // std::invalid_argument, std::out_of_range
#include <iostream>

using namespace matrix;

/* ====================================================================
   Rule-of-Three
   ================================================================= */

/** @brief Construct an @c n×n matrix filled with @p initVal.
 *  @param n_      dimension (must be > 0)  
 *  @param initVal value to fill every element with  
 *  @throw std::invalid_argument if @p n_ ≤ 0                                   */
SquareMat::SquareMat(int n_, double initVal) : data(nullptr), n(n_)
{
    if (n <= 0) throw std::invalid_argument("n must be positive");
    data = new double[n * n];
    std::fill(data, data + n * n, initVal);
}

/** @brief Deep-copy constructor (O(n²)). */
SquareMat::SquareMat(const SquareMat& other) : data(nullptr), n(other.n)
{
    data = new double[n * n];
    std::copy(other.data, other.data + n * n, data);
}

/** @brief Copy-assignment operator.  
 *  Handles self-assignment and re-allocation when @p other.n differs. */
SquareMat& SquareMat::operator=(const SquareMat& other)
{
    if (this == &other) return *this;

    if (n != other.n) {
        delete[] data;
        n = other.n;
        data = new double[n * n];
    }
    std::copy(other.data, other.data + n * n, data);
    return *this;
}

/** @brief Destructor – frees the contiguous @c double* buffer. */
SquareMat::~SquareMat() { delete[] data; }

/* ====================================================================
   Element access
   ================================================================= */

/** @brief Mutable access to element (i,j) with bounds checking.  
 *  @throw std::out_of_range if indices are outside [0,n-1].                */
double& SquareMat::operator()(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        throw std::out_of_range("index out of range");
    return data[i * n + j];
}

/** @brief Const access to element (i,j) with bounds checking. */
const double& SquareMat::operator()(int i, int j) const
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        throw std::out_of_range("index out of range");
    return data[i * n + j];
}

/** @brief Row pointer (mutable) – enables @c mat[i][j] syntax. */
double* SquareMat::operator[](int i)
{
    if (i < 0 || i >= n) throw std::out_of_range("row index out of range");
    return data + i * n;
}

/** @brief Row pointer (const). */
const double* SquareMat::operator[](int i) const
{
    if (i < 0 || i >= n) throw std::out_of_range("row index out of range");
    return data + i * n;
}

/* ====================================================================
   Helper
   ================================================================= */

/** @brief Sum of all elements – used for comparison operators. */
double SquareMat::sum() const
{
    return std::accumulate(data, data + n * n, 0.0);
}

/* ====================================================================
   Arithmetic operators
   ================================================================= */

/** @brief Element-wise product (*Hadamard*) of two matrices.  
 *  @throw std::invalid_argument if dimensions differ.                     */
SquareMat SquareMat::operator%(const SquareMat& other) const {
    if (n != other.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = data[k] * other.data[k];
    return res;
}

/** @brief Matrix addition (creates new matrix). */
SquareMat SquareMat::operator+(const SquareMat& rhs) const
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = data[k] + rhs.data[k];
    return res;
}

/** @brief In-place addition. */
SquareMat& SquareMat::operator+=(const SquareMat& rhs)
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    for (int k = 0; k < n * n; ++k)
        data[k] += rhs.data[k];
    return *this;
}

/** @brief Matrix subtraction (creates new matrix). */
SquareMat SquareMat::operator-(const SquareMat& rhs) const
{
    if (n != rhs.n) throw std::invalid_argument("dimension mismatch");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = data[k] - rhs.data[k];
    return res;
}

/** @brief Unary minus – returns @c (-mat). */
SquareMat SquareMat::operator-() const
{
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = -data[k];
    return res;
}

/* ------------------ matrix × matrix ------------------ */

/** @brief Classic O(n³) matrix multiplication. */
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

/** @brief In-place matrix multiplication. */
SquareMat& SquareMat::operator*=(const SquareMat& rhs)
{
    *this = *this * rhs;
    return *this;
}

/* ------------------ matrix × scalar ------------------ */

/** @brief Multiply every element by scalar @p s (creates new matrix). */
SquareMat SquareMat::operator*(double s) const
{
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = data[k] * s;
    return res;
}

/** @brief In-place scalar multiplication. */
SquareMat& SquareMat::operator*=(double s)
{
    for (int k = 0; k < n * n; ++k)
        data[k] *= s;
    return *this;
}

/** @brief Scalar on the left: @c s * mat. */
SquareMat operator*(double s, const SquareMat& m) { return m * s; }

/* ------------------ scalar division ------------------ */

/** @brief Divide every element by scalar @p s. */
SquareMat SquareMat::operator/(double s) const
{
    if (s == 0) throw std::invalid_argument("division by zero");
    SquareMat res(n);
    for (int k = 0; k < n * n; ++k)
        res.data[k] = data[k] / s;
    return res;
}

/** @brief In-place scalar division. */
SquareMat& SquareMat::operator/=(double s)
{
    if (s == 0) throw std::invalid_argument("division by zero");
    for (int k = 0; k < n * n; ++k)
        data[k] /= s;
    return *this;
}

/* ====================================================================
   Comparison (sum of elements)
   ================================================================= */

bool SquareMat::operator==(const SquareMat& rhs) const { return sum() == rhs.sum(); }
bool SquareMat::operator!=(const SquareMat& rhs) const { return !(*this == rhs); }
bool SquareMat::operator< (const SquareMat& rhs) const { return sum()  < rhs.sum(); }
bool SquareMat::operator<=(const SquareMat& rhs) const { return sum() <= rhs.sum(); }
bool SquareMat::operator> (const SquareMat& rhs) const { return sum()  > rhs.sum(); }
bool SquareMat::operator>=(const SquareMat& rhs) const { return sum() >= rhs.sum(); }

/* ====================================================================
   Transpose
   ================================================================= */

/** @brief Return the transpose (~mat). */
SquareMat SquareMat::operator~() const
{
    SquareMat res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res(j, i) = (*this)(i, j);
    return res;
}

/* ====================================================================
   ++ / -- (prefix & postfix)
   ================================================================= */

SquareMat& SquareMat::operator++()          { for (int k = 0; k < n * n; ++k) ++data[k]; return *this; }
SquareMat  SquareMat::operator++(int)       { SquareMat tmp(*this); ++(*this); return tmp; }
SquareMat& SquareMat::operator--()          { for (int k = 0; k < n * n; ++k) --data[k]; return *this; }
SquareMat  SquareMat::operator--(int)       { SquareMat tmp(*this); --(*this); return tmp; }

/* ====================================================================
   Power
   ================================================================= */

/** @brief Raise matrix to non-negative integer power @p e (binary-exp). */
SquareMat SquareMat::operator^(int e) const
{
    if (e < 0) throw std::invalid_argument("negative exponent");
    SquareMat base(*this);
    SquareMat res(n, 0.0);
    for (int i = 0; i < n; ++i) res(i, i) = 1;   // identity
    while (e) {
        if (e & 1) res *= base;
        base *= base;
        e >>= 1;
    }
    return res;
}

/* ====================================================================
   Determinant demo (n ≤ 3)
   ================================================================= */

/** @brief Determinant using Laplace expansion.  
 *  Only demonstrative for n≤3 – O(n!).                            */
double SquareMat::operator!() const
{
    if (n == 1) return data[0];

    if (n == 2) return data[0] * data[3] - data[1] * data[2];

    double det = 0.0;
    for (int k = 0; k < n; ++k) {
        SquareMat temp(n - 1);
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (j == k) continue;
                int newRow = i - 1;
                int newCol = (j < k) ? j : j - 1;
                temp(newRow, newCol) = (*this)(i, j);
            }
        double cofactor = ((k % 2 == 0) ? 1 : -1) * (*this)(0, k) * !temp;
        det += cofactor;
    }
    return det;
}



/** @brief Return matrix dimension. */
int SquareMat::getN() const { return n; }

namespace matrix {

/** @brief Pretty-print the matrix row-by-row. */
std::ostream& operator<<(std::ostream& os, const SquareMat& m)
{
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

/** @brief Scalar on left: implemented inside namespace for ADL. */
SquareMat operator*(double s, const SquareMat& m) { return m * s; }

} // namespace matrix
