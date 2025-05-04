# SquareMat – Assignment Submission  
**Square Matrix Implementation in Modern C++**

**Student:** Adi Gam Zu Letova 
**Semester:** Spring 2025  


* Square-matrix class written **without STL containers** (`double*` manual storage).
* Full **Rule-of-Three** compliance (ctor, copy-ctor, dtor, assignment).
* Every requested **operator overload**.
* Extensive **unit-test suite** using *doctest*.
* **Valgrind** memory-safety verification (zero leaks / errors).
* Self-contained **Makefile** (`make`, `run`, `test`, `valgrind`, `clean`).

---

## 📁 Project Layout

| File | Purpose |
|------|---------|
| `SquareMat.hpp` | Public interface (all operator declarations). |
| `SquareMat.cpp` | Implementation – contiguous `double* data`, manual memory, Rule-of-Three. |
| `main.cpp` | Small demo / playground. |
| `test_SquareMat.cpp` | Unit tests (55 assertions) with *doctest*. |
| `doctest.h` | Single-header testing framework. |
| `Makefile` | Build / run / test / valgrind / clean targets. |
| `README.md` | This document. |

---

## ✔️ Requirement Mapping

| Assignment requirement | Where implemented |
|------------------------|-------------------|
| No `vector` / `string` / STL | `double* data` in `SquareMat.hpp`; no STL includes. |
| Rule-of-Three | Constructor, copy-ctor, destructor, `operator=` in `SquareMat.cpp`. |
| Accessors `mat(i,j)` and `mat[i][j]` | `operator()` + `operator[]` (row pointer). |
| Operators `+ − * / % ^`, unary `-`, transpose `~`, determinant `!`, `++/--` | All in `SquareMat.cpp`. |
| Scalar multiply both sides | `mat * s` and `s * mat`. |
| Comparisons by **sum of elements** | `== != < <= > >=` rely on private `sum()`. |
| Unit tests | `test_SquareMat.cpp` – 9 cases, 55 assertions, all pass. |
| Valgrind clean | `make valgrind` → *no leaks, no errors*. |

---

## 🛠️ Build & Run

```bash
# Build demo program
make            # (same as make all)
# Run demo
make run
# Run unit tests
make test
# Memory-check demo + tests (requires Valgrind)
make valgrind
# Remove all objects/binaries
make clean
