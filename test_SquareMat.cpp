#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
using namespace matrix;

TEST_CASE("Basic construction and access") {
    SquareMat A(3, 2.5);
    CHECK(A.getN() == 3);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            CHECK(A(i, j) == doctest::Approx(2.5));
}

TEST_CASE("Operator + and -") {
    SquareMat A(2, 1), B(2, 3);
    SquareMat C = A + B;
    SquareMat D = B - A;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            CHECK(C(i, j) == 4);
            CHECK(D(i, j) == 2);
        }
}

TEST_CASE("Scalar operations") {
    SquareMat A(2, 2);
    SquareMat B = A * 3;
    SquareMat C = 3 * A;
    SquareMat D = A / 2;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            CHECK(B(i, j) == 6);
            CHECK(C(i, j) == 6);
            CHECK(D(i, j) == 1);
        }
}

TEST_CASE("Matrix multiplication") {
    SquareMat A(2);
    A(0,0)=1; A(0,1)=2;
    A(1,0)=3; A(1,1)=4;

    SquareMat B(2);
    B(0,0)=5; B(0,1)=6;
    B(1,0)=7; B(1,1)=8;

    SquareMat C = A * B;
    CHECK(C(0,0) == 19);
    CHECK(C(0,1) == 22);
    CHECK(C(1,0) == 43);
    CHECK(C(1,1) == 50);
}

TEST_CASE("Transpose ~") {
    SquareMat A(2);
    A(0,0)=1; A(0,1)=2;
    A(1,0)=3; A(1,1)=4;

    SquareMat T = ~A;
    CHECK(T(0,0) == 1);
    CHECK(T(0,1) == 3);
    CHECK(T(1,0) == 2);
    CHECK(T(1,1) == 4);
}

TEST_CASE("Increment and Decrement") {
    SquareMat A(2, 5);
    SquareMat B = A++;
    CHECK(B(0,0) == 5);
    CHECK(A(0,0) == 6);

    SquareMat C = --A;
    CHECK(C(0,0) == 5);
    CHECK(A(0,0) == 5);
}

TEST_CASE("Determinant") {
    SquareMat A(1);
    A(0,0) = 7;
    CHECK(!A == 7);

    SquareMat B(2);
    B(0,0)=1; B(0,1)=2;
    B(1,0)=3; B(1,1)=4;
    CHECK(!B == doctest::Approx(-2));

    SquareMat C(3);
    C(0,0)=6; C(0,1)=1; C(0,2)=1;
    C(1,0)=4; C(1,1)=-2; C(1,2)=5;
    C(2,0)=2; C(2,1)=8; C(2,2)=7;
    CHECK(!C == doctest::Approx(-306));
}

TEST_CASE("Matrix equality and comparisons") {
    SquareMat A(2, 1.5);
    SquareMat B(2, 3.0);
    SquareMat C(2, 1.5);

    CHECK(A == C);
    CHECK(A != B);
    CHECK(A < B);
    CHECK(B > A);
    CHECK(A <= C);
    CHECK(B >= A);
}

TEST_CASE("Element-wise product %") {
    SquareMat A(2), B(2);
    A(0,0)=1; A(0,1)=2;
    A(1,0)=3; A(1,1)=4;

    B(0,0)=5; B(0,1)=6;
    B(1,0)=7; B(1,1)=8;

    SquareMat C = A % B;
    CHECK(C(0,0) == 5);
    CHECK(C(0,1) == 12);
    CHECK(C(1,0) == 21);
    CHECK(C(1,1) == 32);
}
