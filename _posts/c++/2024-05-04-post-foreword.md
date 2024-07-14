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

**Table of Contents**
* TOC
{:toc}


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
## Const References
Declares a reference to a constant variable, preventing modification through the reference.
``` cpp
int x = 10;
const int& ref = x;
// ref = 20; // Error: ref is const
```
## Const Member Functions
Declares a member function that does not modify the object it belongs to.

``` cpp
class MyClass {
public:
    int getValue() const {
        return value;
    }
private:
    int value;
};

void foo(const MyClass& obj) {
    int v = obj.getValue(); // OK: getValue is const because get value ensure we don't change the object
}
```

## Const and Mutable
Allows a member of an object to be modified even if the object is const.

``` cpp
class MyClass {
public:
    void setValue(int v) const {
        value = v; // Allowed because value is mutable
    }
private:
    mutable int value;
};
```

## Const Correctness in Function Parameters and Return Types
### Function Parameters
Pass by Const Reference/Pointer: **Avoids** copying large objects while preventing modification.
``` cpp
//Pass by Const Reference
void foo(const MyClass& obj);

//Pass by Const Pointer
void foo(const int* ptr);
```

### Function Return Types
Returning Const Reference: Ensures the returned reference **cannot** be used to modify the object.
``` cpp
const MyClass& getConstObject() const;
```

### Const Correctness and Overloading
Function Overloading with Const:
``` cpp
class MyClass {
public:
    void foo();
    void foo() const;
};

MyClass obj;
obj.foo(); // Calls non-const version

const MyClass constObj;
constObj.foo(); // Calls const version
```
## Usage of constant expressions
This keyword introduced in C++11 that allows for the specification of constant expressions, enabling the evaluation of expressions at *compile time* rather than at *runtime*. This can lead to more efficient and optimized code, as the compiler can perform calculations during compilation and embed the results directly into the binary.

Use Cases: Constants, array sizes, metaprogramming, and performance-critical code.

### `constexpr` Variables.

``` cpp
constexpr int value = 10;  // Evaluated at compile time

int main() {
    int array[value];  // Size of array is known at compile time
    return 0;
}
```

### `constexpr` Functions.
A `constexpr` function is a function that can be evaluated at compile time if its arguments are constant expressions

``` cpp
constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int result = square(5);  // Evaluated at compile time
    // result is computed as 25 during compilation
    return 0;
}
```
#### What does it mean by Evaluated at compile time?
it means that the compiler computes the value of the expression during the *compilation process* rather than at runtime. This allows the compiler to embed the computed result directly into the *program's binary*, leading to more efficient and faster code execution since these calculations do not need to be performed repeatedly during program execution.

*Benefits of Compile-Time Evaluation*
* **Performance Improvement:** Since the computation is done once during compilation, the program does not spend time performing these calculations at runtime.
* **Reduced Binary Size:** The results of the computations are directly embedded in the binary, potentially reducing the size of the generated machine code.
* **Code Safety and Optimization:** Ensures that certain values are constant and cannot change, making the code safer and allowing the compiler to perform more aggressive optimizations.

# Casting in C++
Casting in C++ is a way to convert a variable from one type to another. There are several types of casting in C++, each with its own specific use cases and rules.

## Implicit Casting
Automatic type conversion performed by the compiler without explicit instructions from the programmer.

``` cpp
int i = 42;
double d = i; // Implicitly converts int to double
```

## Explicit Casting (Type Casting)
### C-Style Casting

``` cpp
int i = 42;
double d = (double)i; // C-style cast
```
Drawbacks is Less safe and harder to identify in code.
{: .notice--warning}

### C++ Style Casting
C++ provides more explicit and safer casting operators:

#### `static_cast`
*Usage:* Perform well-defined and checked conversions.

``` cpp
int i = 42;
double d = static_cast<double>(i); // Static cast
```
Common Uses:
1. Numeric conversions.
2. Converting pointers within an inheritance hierarchy.
    
    In an inheritance hierarchy, a derived class inherits properties and methods from a base class. You can have pointers to both base and derived class objects. static_cast allows you to convert pointers within this hierarchy safely, as long as the types are related through inheritance.

3. Downcasting: Use `static_cast` only when you are certain of the object type and want to make it clear that the conversion is intentional.

``` cpp
class Base {
public:
    virtual ~Base() = default;
    void baseMethod() { /*...*/ }
};

class Derived : public Base {
public:
    void derivedMethod() { /*...*/ }
};

int main() {
    Derived* derivedPtr = new Derived();
    Base* basePtr = static_cast<Base*>(derivedPtr);  // Upcasting

    basePtr->baseMethod();  // Valid, as basePtr is now a Base*.

    Derived* derivedPtr = static_cast<Derived*>(basePtr);  // Downcasting
    derivedPtr->derivedMethod(); // Valid, as basePtr actually points to a Derived object.

    delete derivedPtr;
    return 0;
}
```

####  `dynamic_cast`
Perform safe, runtime-checked downcasting in polymorphic hierarchies.

``` cpp
class Base { virtual void foo() {} };
class Derived : public Base { void foo() override {} };

Base* base = new Derived();
Derived* derived = dynamic_cast<Derived*>(base); // Safe downcast
if (derived) {
    // Successful cast
}
```
Common Uses:
1. Use `dynamic_cast` for safer downcasting: When working with polymorphic types (classes with virtual functions), prefer `dynamic_cast` for downcasting, as it performs a runtime check and returns nullptr if the **cast fails**.
2. Works only with polymorphic types (classes with virtual functions).

**What does it mean by it works with only polymorphic types (Polymorphic Requirement)?**

The polymorphic requirement refers to the need for a class to have at least one virtual function in order for dynamic_cast to work. This requirement is due to how *runtime type information (RTTI)* is implemented in C++.

Polymorphism in C++ allows objects to be treated as instances of their base class rather than their derived class. This is achieved using virtual functions, which enable dynamic (runtime) binding of function calls. Polymorphism is a core feature of object-oriented programming in C++. (We'll talk about Polymorphism more on later)
{: .notice--success}

Runtime Type Information (RTTI) is a mechanism that allows the type of an object to be determined during program execution. RTTI is necessary for dynamic_cast to perform runtime checks and ensure that the cast is valid. RTTI is only available for polymorphic types.
{: .notice--success}

**Polymorphic Requirement for dynamic_cast**

For dynamic_cast to work, the classes involved in the cast must be polymorphic. This means the base class must have at **least one** virtual function. The presence of a virtual function ensures that the class has an associated *vtable* (virtual table), which is used by the compiler to store information about the virtual functions of the class and the actual type of the object.

*Polymorphic Class Example*
``` cpp
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}  // Virtual destructor makes Base a polymorphic class
};

class Derived : public Base {
public:
    void derivedMethod() { std::cout << "Derived method called\n"; }
};

void polymorphicExample(Base* basePtr) {
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr) {
        derivedPtr->derivedMethod();
    } else {
        std::cout << "basePtr is not pointing to a Derived object.\n";
    }
}

int main() {
    Base* base1 = new Base();
    Base* base2 = new Derived();
    
    polymorphicExample(base1);  // Fails, as base1 is not a Derived object
    polymorphicExample(base2);  // Succeeds, as base2 is actually a Derived object

    delete base1;
    delete base2;
    return 0;
}
```

*Non-Polymorphic Class Example*
``` cpp
#include <iostream>

class Base {
public:
    // No virtual functions, so Base is not polymorphic
};

class Derived : public Base {
public:
    void derivedMethod() { std::cout << "Derived method called\n"; }
};

void nonPolymorphicExample(Base* basePtr) {
    // This will cause a compile-time error
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr) {
        derivedPtr->derivedMethod();
    } else {
        std::cout << "basePtr is not pointing to a Derived object.\n";
    }
}

int main() {
    Base* base1 = new Base();
    Base* base2 = new Derived();
    
    nonPolymorphicExample(base1);  // This will cause a compile-time error
    nonPolymorphicExample(base2);  // This will cause a compile-time error

    delete base1;
    delete base2;
    return 0;
}
```
error: cannot `dynamic_cast` ‘basePtr’ (of type ‘class Base*’) to type ‘class Derived*’ (source type is not polymorphic)
{: .notice--danger}

####  `dynamic_cast` vs `static_cast`
`dynamic_cast`

Pros:
* **Runtime Type Checking:** `dynamic_cast` performs a runtime check to ensure the cast is valid. If the cast is invalid (e.g., if the base pointer doesn't actually point to a derived type), it returns `nullptr` (for pointers) or throws a std::bad_cast exception (for references).
* **Safety:** Due to runtime checks, `dynamic_cast` is safer for downcasting in polymorphic hierarchies (where you have at least one virtual function, typically the destructor).

Cons:
* **Performance Overhead:** Because of the runtime checks, `dynamic_cast` can be *slower* than `static_cast`. This overhead can be significant in performance-critical code, especially within tight loops or real-time systems.
* **Polymorphic Requirement:** dynamic_cast only works with polymorphic types (i.e., classes with at least one virtual function). If the class hierarchy is not polymorphic, dynamic_cast cannot be used.

`static_cast`

Pros:
* **Compile-time Checking:** `static_cast` performs type checking at compile time. This makes it faster since there's no runtime overhead.
* **Flexibility:** `static_cast` can be used for non-polymorphic types as well, making it more versatile in certain scenarios.

Cons:
* **No Runtime Checks:** `static_cast` does not perform any runtime checks. If the cast is incorrect (e.g., if the base pointer doesn't actually point to the derived type), the behavior is undefined, potentially leading to **crashes or other hard-to-diagnose bugs**.
* **Potential for Unsafe Casts:** `static_cast` relies on the programmer's guarantee that the cast is safe. Misuse can lead to undefined behavior, which is dangerous.

####  `const_cast`
The `const_cast` operator is specifically designed to add or **remove const** and **volatile** qualifiers from a variable. This is useful when you need to pass a const object to a function that takes a non-const parameter.

``` cpp
#include <iostream>

void modifyValue(int* ptr) {
    *ptr = 10;
}

int main() {
    const int value = 5;
    const int* constPtr = &value;

    // Removing const using const_cast
    int* nonConstPtr = const_cast<int*>(constPtr);

    // Now we can modify the value (though it's undefined behavior if the original object is actually const)
    modifyValue(nonConstPtr);

    std::cout << "Value: " << *constPtr << std::endl;  // Undefined behavior But Out put maybe appears to be correct (due to compiler optimizations)

    return 0;
}
```

Modifying a value through a pointer that was **originally const** is *undefined* behavior. The `const_cast` operator should be used with care, and you should ensure that the object being modified was not originally declared as const.
{: .notice--warning}

A valid use case for `const_cast` is when you are working with legacy code or APIs that do not use const correctly. For example, a function that should accept a const parameter but doesn't
{: .notice--success}

####  `reinterpret_cast`
Perform unsafe conversions between unrelated types.

``` cpp
int i = 42;
void* v = reinterpret_cast<void*>(&i);
int* ip = reinterpret_cast<int*>(v); // Cast back to int pointer
```

`reinterpret_cast` should be used with **caution**. It is typically used in the following scenarios:
* **Type Punning:** When you need to treat a sequence of bits as a different type.
* **Interfacing with Hardware:** When dealing with low-level hardware interfaces where types need to be reinterpreted.
* **Interfacing with C APIs:** When interacting with certain C libraries or APIs that require casting pointers to void* and back.

`reinterpret_cast` can easily lead to undefined behavior if the resulting pointer is dereferenced incorrectly. The types involved in the cast should have a compatible memory layout also it bypasses the C++ type system, which can lead to bugs that are hard to track down. It should be used sparingly and only when necessary.
{: .notice--warning}

# `typedef` vs `using`
In modern C++, `typedef` is still used, but it has largely been superseded by the `using` keyword, which was introduced in C++11. The using keyword provides a more readable and flexible way to create type aliases and is generally preferred over typedef for new code.

*`typedef` example usage:*
``` cpp
// Typedef example
typedef unsigned long ulong;
typedef int (*func_ptr)(double, double);  // Function pointer typedef
```

*`using` example usage:*
``` cpp
#include <iostream>

// Define a function
void foo() {
    std::cout << "Hello from foo!" << std::endl;
}

// Define a function pointer type using 'using'
using voidFuncPtr = void (*)();

int main() {
    // Create a function pointer and assign it to foo
    voidFuncPtr func = &foo;

    // Call the function through the function pointer
    func();  // Outputs: Hello from foo!

    return 0;
}
```

## Advantages of using Over typedef
* **Readability:** using is generally more readable and easier to understand, especially for complex type definitions.
* **Templates:** using works better with templates and can be used to simplify template declarations.

``` cpp
template <typename T>
struct MyContainer {
    using VectorType = std::vector<T>;
};
```