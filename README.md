# C / C++ Projects

A collection of my programming projects in **C** and **C++**, added one by one as
I complete them. Each project lives in its own folder together with its source files
and a short description.

## Projects

### 1. [`stack/`](stack/) — Dynamic stack of integers (C)

A LIFO stack of integers built on a **dynamically allocated array** that grows
automatically as elements are pushed, using a **capacity-doubling** strategy
(amortized *O(1)* `push`).

- **Interface:** `init`, `destroy`, `push`, `pop`, `isEmpty`
- **Concepts demonstrated:**
  - Dynamic memory management with `malloc` / `realloc` / `free`
  - Growth strategy that avoids reallocating on every `push`
  - Robust error handling (allocation failure, `pop` on an empty stack)
  - Header / implementation separation (`Stack.h` + `Stack.c`)
  - Leak-free design, verified with **Valgrind**
- **Files:** `Stack.h`, `Stack.c`, `TestStack.c`

**Build & run:**
```sh
cd stack
gcc -g -Wall -Wextra -o TestStack Stack.c TestStack.c
./TestStack
valgrind --leak-check=full ./TestStack
```

### 2. [`Stack_cpp/`](Stack_cpp/) — Dynamic stack of integers (C++)

The same stack as a C++ class: constructor/destructor, copy constructor and
copy assignment (deep copy). **Files:** `Stack_cpp.h`, `Stack_cpp.cpp`, `TestStack_cpp.cpp`

### 3. [`Complex_numbers/`](Complex_numbers/) — Complex numbers (C++)

`Complex` class with `+ - * /` (and `+= -= *= /=`), `==`, `!=`, `<<`,
`phase()` and `amplitude()`. **Files:** `Complex.h`, `Complex.cpp`, `TestComplex.cpp`

### 4. [`Polynomial/`](Polynomial/) — Polynomials (C++)

`Poly` class: coefficients by `[]`, evaluation by `()`, `+ - *` and `<<`.
**Files:** `Poly.h`, `Poly.cpp`, `TestPoly.cpp`

### 5. [`Matrix/`](Matrix/) — Matrix with reference counting (C++)

`Matrix` shares data between copies and copies it only on write (copy-on-write),
with element access through a proxy `Cell` class, exceptions for bad index /
dimensions / file, and reading from a CSV file (`read.csv`).
**Files:** `Matrix.h`, `Matrix.cpp`, `TestMatrix.cpp`, `read.csv`

### 6. [`Map/`](Map/) — Template map (C++)

`Map<K, V>` template on a linked list (copying, assignment, adding and finding keys),
used as an employee database and a library of books. `add` throws `DuplicateKey`
for an existing key, `find` returns `nullptr` for a missing one.
**Files:** `Map.h`, `Employee.h`, `Book.h`, `TestMap.cpp`

## Build everything (CMake)

```sh
cmake -S . -B build
cmake --build build
cmake --build build --target valgrind_matrix   # or valgrind_stack_c, valgrind_stack_cpp, valgrind_complex_numbers, valgrind_poly, valgrind_map
```
