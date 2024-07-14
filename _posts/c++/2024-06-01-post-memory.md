---
title: "Memory Management"
excerpt_separator: "<!--more-->"
categories:
 - C++, Memory
tags:
 - C++
---
{% include mathJax.html %}

Memory management in C++ involves the allocation, use, and deallocation of memory in a program. Proper memory management is crucial to ensure the efficiency and stability of applications.

<!--more-->

**Table of Contents**
* TOC
{:toc}

# Stack vs. Heap Memory
## Stack Memory
Stack memory is one of the types of memory allocation used in C++ programs. It is known for its simplicity and efficiency in managing the lifetime of variables.

### Characteristics of Stack Memory
* **Automatic Allocation and Deallocation:** Variables allocated on the stack are automatically created and destroyed when the scope in which they are defined is entered and exited, respectively.
* **Fixed Size:** The size of the stack is fixed at the start of the program, typically determined by the system or specified during program compilation.
* **Fast Access:** Allocation and deallocation of stack memory are very fast because they involve simple pointer arithmetic (moving the stack pointer).
* **LIFO (Last-In-First-Out) Order:** The stack operates in a LIFO manner, where the last allocated memory is the first to be deallocated.

*Example : allocating stack memory*

```cpp
void stackExample() {
    int x = 10;  // Allocated on the stack
}
```

### Stack Overflow
A stack overflow occurs when the stack memory limit is exceeded. This can happen due to deep or infinite recursion, or allocating large local variables.

```cpp
void recursiveFunction() {
    int largeArray[10000]; // Large array allocated on the stack
    recursiveFunction(); // Recursive call
}

int main() {
    recursiveFunction();
    return 0;
}
```

## Heap Memory
Heap memory, also known as *dynamic memory*, is an area of memory used for dynamic allocation. Unlike stack memory, heap memory is not automatically managed and must be **explicitly** allocated and deallocated by the programmer.

### Characteristics of Heap Memory
* **Dynamic Allocation:** Memory can be allocated and deallocated at runtime, allowing for flexible and variable-sized data structures.
* **Manual Management:** The programmer is responsible for allocating and deallocating heap memory using operators like `new` and `delete` or functions like `malloc` and `free`.
* **Large Size:** The heap is generally much larger than the stack, making it suitable for large data structures.
* **Persistent Lifetime:** Heap-allocated memory persists until it is explicitly deallocated, allowing data to outlive the scope in which it was allocated.

*Example : Allocating and Deallocating Heap Memory*

In C++, the `new` operator is used to allocate memory on the heap, and `delete` is used to deallocate that memory.

```cpp
#include <iostream>

int main() {
    // Allocate a single integer on the heap
    int* p = new int;
    *p = 42;

    std::cout << "Value: " << *p << std::endl;

    // Deallocate the memory
    delete p;

    // Allocate an array of integers on the heap
    int* arr = new int[10];

    // Use the array
    for (int i = 0; i < 10; ++i) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Deallocate the array
    delete[] arr;

    return 0;
}
```

### Best Practices for Managing Heap Memory
1. **Always Deallocate Memory:** Ensure that every `new`  has a corresponding `delete` to prevent memory leaks.
2. **Use Smart Pointers:** Prefer using smart pointers (`std::unique_ptr`, `std::shared_ptr`) over raw pointers to automate memory management and avoid leaks.
3. **Avoid Dangling Pointers:** After deallocating memory, set the pointer to `nullptr` to avoid accessing freed memory.

### Disadvantages of Heap Memory
1. **Manual Management:** Requires careful management to avoid memory leaks, dangling pointers, and other issues.
2. **Slower Allocation:** Generally slower than stack allocation due to the complexity of managing dynamic memory.
3. **Fragmentation:** Can suffer from fragmentation, where free memory is split into small, non-contiguous blocks, reducing the efficiency of memory usage.

## Stack vs Heap
![Alt Text]({{ site.baseurl }}/assets/c++/c4.png)

## RAII (Resource Acquisition Is Initialization)
RAII is a programming idiom that ensures resource allocation is tied to object lifetime. Resources are acquired and released using *constructors and destructors*, which helps prevent resource leaks.

*Example : RAII*

```cpp
class RAIIExample {
private:
    int* data;
public:
    RAIIExample() : data(new int(10)) {
        // Resource acquisition
    }

    ~RAIIExample() {
        delete data;  // Resource release
    }
};
```