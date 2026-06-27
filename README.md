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
