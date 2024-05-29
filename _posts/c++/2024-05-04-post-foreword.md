---
title: "Basic Syntax and Language Features"
excerpt_separator: "<!--more-->"
categories:
 - C++
tags:
 - C++
---

C++ powerful language with an enormous range of features, but before you can harness that power and make effective use of those features, you have to accustom yourself to C++’s way of doing things.

<!--more-->

# Variables and Data Types

## Primitive Data Types
These data types are built-in or predefined data types and can be used directly by the user to declare variables. example: int, char, float, bool, etc. Primitive data types available in C++ are: 

![Alt Text]({{ site.baseurl }}/assets/c++/c1.png)

## Variable Declaration
Declaring a variable involves specifying its type followed by its name.

```cpp
int number;
float decimal;
char letter;
bool flag;
```
### Variable Initialization
In C++, there are several ways to initialize variables, each with its own syntax and use cases. Here's a detailed comparison of direct all the methods.

**Direct Initialization** : Uses parentheses () to initialize a variable.
```cpp
int number(10);
float decimal(3.14);
char letter('A');
bool flag(true);
```
Characteristics:
* Directly calls the constructor for objects.
* For fundamental types, it assigns the value immediately.
* Preferred for non-primitive types (e.g., class objects) to avoid **extra copy** operations.

**Copy Initialization** : Uses the assignment operator = to initialize a variable.
```cpp
int number = 10;
float decimal = 3.14f;
char letter = 'A';
bool flag = true;
```
Characteristics:
* The compiler first creates a *temporary object* using the value on the right-hand side, then copies it to the variable on the left-hand side.
* Can be *less* efficient than direct initialization due to the potential for an extra copy, especially for complex object

**Brace Initialization (Uniform Initialization)** : Uses curly braces {} to initialize a variable. 

```cpp
int number{10};
float decimal{3.14f};
char letter{'A'};
bool flag{true};

// Avoids narrowing conversions
int valid{10};
// int invalid{3.14}; // Error: narrowing conversion
```
Characteristics:
* Introduced in C++11 for uniform initialization across all types.
* Prevents narrowing conversions, where a larger type is converted to a smaller type, potentially losing data.
* Preferred in modern C++ for its consistency and safety.

### Best Practices
* *Initialize*: Variables: Always initialize variables to avoid undefined behavior.
* *Limit Scope*: Declare variables in the smallest possible scope to improve readability and maintainability.
* *Consistency*: Brace initialization is often preferred for its uniformity across different types and contexts.
* *Safety*: Brace initialization helps avoid issues like narrowing conversions.
* *Efficiency*: Direct initialization can be more efficient for complex objects due to the avoidance of extra copy operations.

# Type Modifiers
Type modifiers in C++ are keywords used to alter the properties of fundamental data types, enabling you to define the size and range of variables more precisely.

## Signed and Unsigned Modifiers
### Signed:
* Indicates that a variable can hold both **positive** and **negative** values.
* By default, integer types (int, short, long, char) are signed.

``` cpp
signed int number = -10; // Explicitly signed (optional)
int positiveNumber = 20; // Implicitly signed
```

### Unsigned:
Indicates that a variable can only hold **non-negative values**, effectively *doubling* the maximum positive range.

``` cpp
unsigned int positiveNumber = 20; // Only non-negative values
unsigned int badNumber = -20; //badNumber - will contain garbage value
```

## Short and Long Modifiers
### Short:
Used to reduce the size of an integer variable (usually 16 bits).

``` cpp
short int smallNumber = 32767; // Typically ranges from -32768 to 32767
short smallNumberAlt = 32767; // 'int' is optional
```
### Long:
Used to increase the size of an integer variable.

``` cpp
long int largeNumber = 2147483647; // 32 bits
long largeNumberAlt = 2147483647; // 'int' is optional

// Long long int: Usually 64 bits, offering an extended range
long long int veryLargeNumber = 9223372036854775807LL; // 64 bits
```

## Combining Modifiers
You can combine these modifiers to create specific data types:

``` cpp
unsigned short int usi = 65535; // Typically ranges from 0 to 65535
long double ld = 3.14159265358979323846; // Extended precision for floating points
```
## Size and Range of Modified Types

![Alt Text]({{ site.baseurl }}/assets/c++/c2.png)

# Scope and Lifetime of Variables
Understanding the scope and lifetime of variables in C++ is crucial for managing memory, avoiding bugs, and writing clean, maintainable code. 

## Scope of Variables
**Scope** refers to the region of the program where a variable can be accessed. C++ supports several types of scope:

### Local Scope
* **Block Scope**: Variables declared inside a block (enclosed by {}) are accessible only within that block.
* **Function Scope**: Parameters and local variables declared inside a function are local to that function.

``` cpp
void function() {
    int localVar = 10; // Local to this function
    if (true) {
        int blockVar = 20; // Local to this block
        std::cout << blockVar << std::endl; // Accessible here
    }
    // std::cout << blockVar << std::endl; // Error: blockVar is not accessible here
}
```

### Global Scope
Global Variables: Declared outside any function or block, accessible from any part of the program after their declaration.

``` cpp
int globalVar = 100; // Global variable

void function() {
    std::cout << globalVar << std::endl; // Accessible here
}

int main() {
    function();
    std::cout << globalVar << std::endl; // Accessible here too
    return 0;
}

```

### Namespace Scope
Namespace Variables: Declared within a namespace, accessible using the namespace name.

``` cpp
namespace MyNamespace {
    int namespaceVar = 200;
}

int main() {
    std::cout << MyNamespace::namespaceVar << std::endl; // Accessing namespace variable
    return 0;
}
```

## Lifetime of Variables
**Lifetime** refers to the duration for which a variable exists in memory. The lifetime of a variable *depends* on where and how it is declared.

### Automatic Storage Duration
**Local Variables:** Have automatic storage duration. They are created when the block in which they are defined is entered and destroyed when the block is exited.

``` cpp
void function() {
    int localVar = 10; // Created when the function is called
    // ... use localVar ...
} // Destroyed when the function exits
```
### Static Storage Duration
* **Static Variables:** Retain their value between function calls and exist for the entire lifetime of the program.

``` cpp
void function() {
    static int staticVar = 0; // Initialized only once
    staticVar++;
    std::cout << staticVar << std::endl; // Retains value between calls
}

int main() {
    function(); // Output: 1
    function(); // Output: 2
    function(); // Output: 3
    return 0;
}

```

* **Global Variables:** Also have static storage duration. They exist for the entire lifetime of the program.

``` cpp
int globalVar = 100; // Exists for the entire program duration

int main() {
    // globalVar is accessible and exists throughout the program
    return 0;
}
```
### Dynamic Storage Duration
**Dynamically Allocated Variables:** Managed using `new` and `delete`. They exist until explicitly deallocated.

``` cpp
int main() {
    int* dynamicVar = new int(10); // Allocated on the heap
    // ... use dynamicVar ...
    delete dynamicVar; // Deallocated
    return 0;
}
```

### Best Practices
* *Minimize Global Variables*: Use global variables sparingly to avoid unintended side effects and to make the code easier to understand and maintain.
* *Use Static Variables Wisely*: They can be useful but can also lead to issues if not managed properly (e.g., in multi-threaded environments).
* *Prefer Local Variables*: They are easier to manage and understand within their limited scope.
* *Manage Dynamic Memory Carefully*: Always pair `new` with `delete` to avoid memory leaks, and consider using smart pointers (`std::unique_ptr`, `std::shared_ptr`) for automatic memory management.
* *Namespace Usage*: Use namespaces to avoid name conflicts and to organize code logically.


# Pointers and References
## Pointers
### Basics of Pointers
A pointer is a *variable* that stores the memory address of another variable.

``` cpp
int* ptr; // Pointer to an integer
```
### Pointer Initialization
* **Null Pointer**: A pointer that does not point to any memory location.

``` cpp
int* ptr = nullptr; // Modern C++ (C++11 and later)
int* ptr = NULL;    // Pre-C++11 (less preferred)
```
* Pointer to Variable

``` cpp
int var = 10;
int* ptr = &var; // ptr holds the address of var
```

### Dereferencing Pointers
Accessing the value stored at the address pointed to by the pointer.

``` cpp
int var = 10;
int* ptr = &var;
int value = *ptr; // value is now 10
```
### Pointer Arithmetic
* Increment/Decrement:

``` cpp
ptr++; // Moves to the next memory location of the pointer type
ptr--; // Moves to the previous memory location
```

* Addition/Subtraction:

``` cpp
ptr += n; // Moves the pointer n locations forward
ptr -= n; // Moves the pointer n locations backward
```
### Arrays and Pointers
*Array Name as Pointer:* The name of an array acts like a **pointer to its first element.**

``` cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;
```
### Dynamic Memory Allocation
Using `new` and `delete`:

``` cpp
int* ptr = new int;    // Allocates memory for an integer
*ptr = 10;
delete ptr;           // Deallocates the memory

int* arr = new int[5]; // Allocates memory for an array of 5 integers
delete[] arr;          // Deallocates the array memory
```
## References
### Basics of References
A reference is an alias for another variable.

``` cpp
int var = 10;
int& ref = var; // ref is a reference to var
```
### Usage of References
* Function Parameters: Pass variables by reference to **avoid copying**.

``` cpp
void increment(int& n) {
    n++;
}

int a = 5;
increment(a); // a is now 6
```
* Return Values: Return by reference to avoid copying large objects.

``` cpp
int& getElement(int* arr, int index) {
    return arr[index];
}
```
### Const References
Immutable References: Prevents modification of the referenced variable.

``` cpp
void print(const int& n) {
    std::cout << n << std::endl;
}
```
## Pointers vs. References
![Alt Text]({{ site.baseurl }}/assets/c++/c3.png)

## Advanced Concepts
### Pointer to Pointer
A pointer that stores the address of another pointer.

``` cpp
int var = 10;
int* ptr = &var;
int** ptr2 = &ptr; // Pointer to pointer to int

// Dereferencing ptr2 (*ptr2) => memory address of ptr
// Dereferencing ptr2 (**ptr2) again => Gets the value of var which is 10
```
### Pointer to Function
A pointer that stores the address of a function.

``` cpp
void foo() {
    std::cout << "Hello" << std::endl;
}

//type  //*name  //address
void (*funcPtr)() = &foo; // Pointer to function
funcPtr(); // Calls foo
```
## Common Pitfalls
* **Dangling Pointers**: Pointers that refer to memory that has been deallocated.
``` cpp
int* ptr = new int(10);
delete ptr;
// ptr is now a dangling pointer
```
* **Memory Leaks**: Memory that is allocated but not deallocated.
``` cpp
int* ptr = new int(10);
// If delete is not called, this is a memory leak
```
* **Null Pointer Dereferencing**: Accessing memory through a null pointer.
``` cpp
int* ptr = nullptr;
// *ptr would cause a runtime error
```

# Const correctness
Const correctness is an important concept in C++ that ensures the immutability of variables and objects when they are not supposed to change. It improves code reliability, readability, and safety by preventing unintended modifications.

## Const Variables
Declares a variable whose value cannot be changed after initialization.
``` cpp
const int x = 10;
// x = 20; // Error: x is const
```
## Constant Pointers
* Pointer to const:
``` cpp
// easy way to remember: const happen before * then value is const
const int* ptr = &x; // Pointer to a constant integer
// *ptr = 20; // Error: cannot modify the value through ptr
int y = 30;
ptr = &y; // OK: ptr itself is not const
```

* Const pointer:
``` cpp
// easy way to remember: const happen after * then pointer is const
int* const ptr = &x; // Const pointer to an integer
*ptr = 20; // OK: can modify the value
// ptr = &y; // Error: ptr is const
```

* Const pointer to const:
``` cpp
const int* const ptr = &x; // Const pointer to a const integer
// *ptr = 20; // Error: cannot modify the value
// ptr = &y; // Error: ptr is const
```