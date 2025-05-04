//adi.gamzu@msmail.ariel.ac.il
#include <iostream>
#include "SquareMat.hpp"

using namespace matrix;

int main()
{
    SquareMat A(2,  3.0);      // מטריצה 2×2 מאותחלת ל-3
    SquareMat B(2, -1.5);      // מטריצה 2×2 מאותחלת ל--1.5
    SquareMat C(3,  2.0);      // מטריצה 3×3 מאותחלת ל-2
    SquareMat D(3,  0.0);      // מטריצה 3×3 הכול אפסים

    std::cout << "A (2×2, 3.0):\n" << A
              << "B (2×2,-1.5):\n" << B
              << "C (3×3, 2.0):\n" << C
              << "D (3×3, 0.0):\n" << D << '\n';

    /* --- צירוף אופרטורים על 2×2 ------------------------------------------ */
    SquareMat E = A + B;           // חיבור
    SquareMat F = A - B;           // חיסור
    SquareMat G = A * B;           // כפל מטריצות
    SquareMat H = 2 * A;           // סקלר תחילה
    SquareMat I = B * -3.0;        // סקלר אחר־כך
    SquareMat J = (A ^ 3);         // חזקת שלוש (2×2)
    SquareMat K = ~A;              // טרנספוז

    std::cout << "E = A + B:\n" << E
              << "F = A - B:\n" << F
              << "G = A * B:\n" << G
              << "H = 2 * A:\n" << H
              << "I = B * (-3):\n" << I
              << "J = A ^ 3:\n" << J
              << "K = ~A (transpose):\n" << K << '\n';

    /* --- בדיקות ++ / -- --------------------------------------------------- */
    std::cout << "Post-increment E++\n";
    std::cout << "Before:\n" << E;
    std::cout << "Returned (old copy):\n" << E++;
    std::cout << "After:\n"  << E << '\n';

    std::cout << "Pre-decrement --F\n";
    std::cout << "Result:\n" << --F << '\n';

    /* --- אופרטורים על 3×3 -------------------------------------------------- */
    // נשנה חלקית את C כדי לבדוק טרנספוז ודטרמיננטה
    for (int i = 0; i < 3; ++i)
        C[i][i] = i + 1;          // 1,2,3 באלכסון

    D = C * 1.5;                  // סקלר
    SquareMat M = C % D;          // כפל איבר-איבר
    SquareMat N = C / 2.0;        // חילוק סקלרי
    SquareMat P = ~C;             // טרנספוז

    std::cout << "Modified C:\n" << C
              << "D = C * 1.5:\n" << D
              << "M = C % D (element-wise):\n" << M
              << "N = C / 2:\n" << N
              << "P = ~C:\n" << P << '\n';

    /* --- השוואות (לפי סכום איברים) --------------------------------------- */
    std::cout << std::boolalpha;   // להדפיס true/false
    std::cout << "A == B ? " << (A == B) << '\n'
              << "A != B ? " << (A != B) << '\n'
              << "A  < B ? " << (A  < B) << '\n'
              << "A >= B ? " << (A >= B) << "\n\n";

    /* --- דטרמיננטות ------------------------------------------------------- */
    // כדי לקבל דטרמיננטה לא-טריוויאלית, ניצור 3×3 חדשה
    SquareMat Q(3,0);
    Q[0][0]= 6;  Q[0][1]= 1;  Q[0][2]= 1;
    Q[1][0]= 4;  Q[1][1]=-2;  Q[1][2]= 5;
    Q[2][0]= 2;  Q[2][1]= 8;  Q[2][2]= 7;

    std::cout << "Q (3×3):\n" << Q
              << "det(Q) = " << !Q << '\n';

    return 0;
}
