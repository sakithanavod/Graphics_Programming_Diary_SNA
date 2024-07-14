---
title: "Templates In C++"
excerpt_separator: "<!--more-->"
categories:
 - C++, Advanced
tags:
 - C++
---
{% include mathJax.html %}

Let's talk about Templates, Variadic Templates, Template Metaprogramming & SFINAE (Substitution Failure Is Not An Error).

<!--more-->

**Table of Contents**
* TOC
{:toc}

# Templates in C++
Templates in C++ are a powerful feature that allow you to write generic and reusable code. They enable functions and classes to operate with different data types without being rewritten for each one. Templates are a cornerstone of C++ *generic programming*, making code more flexible and maintainable.

## Function Templates
A function template defines a pattern for creating functions based on the provided template arguments. The syntax involves the `template` keyword followed by template parameters in angle brackets.

```cpp
#include <iostream>

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << std::endl; // Outputs 7
    std::cout << add(3.5, 4.5) << std::endl; // Outputs 8
    return 0;
}
```

## Class Templates
A class template defines a pattern for creating classes based on the provided template arguments. Class templates allow you to create generic data structures and other classes.

```cpp
#include <iostream>

template <typename T>
class Box {
public:
    Box(T value) : value(value) {}
    T getValue() const { return value; }
private:
    T value;
};

int main() {
    Box<int> intBox(123);
    Box<std::string> stringBox("Hello");

    std::cout << intBox.getValue() << std::endl; // Outputs 123
    std::cout << stringBox.getValue() << std::endl; // Outputs Hello

    return 0;
}
```

## Template Instantiation
Templates are a compile-time mechanism that allows the compiler to generate code based on the types or values provided as template arguments. This process is known as template instantiation.

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int result1 = add(1, 2);       // Instantiates add<int>(int, int)
    double result2 = add(1.5, 2.5); // Instantiates add<double>(double, double)
    return 0;
}
```

In this example:

* The compiler generates two versions of the add function: one for `int` and one for `double`.
* This process happens at **compile time**, ensuring type safety and optimizing for the specific types used.

### Compile-Time Polymorphism
Templates provide compile-time polymorphism, which is different from runtime polymorphism (achieved through virtual functions). Compile-time polymorphism allows the compiler to select the appropriate template instantiation, resulting in faster and more efficient code.

## Template Specialization
Template specialization allows you to define a **specific implementation** for a particular type. This is useful when the general template implementation is **not suitable** for certain types.

### Example: Full Specialization

```cpp
#include <iostream>

template <typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << "Generic print: " << value << std::endl;
    }
};

// Specialization for int
template <>
class Printer<int> {
public:
    void print(const int& value) {
        std::cout << "Integer print: " << value << std::endl;
    }
};

int main() {
    Printer<std::string> stringPrinter;
    stringPrinter.print("Hello"); // Outputs: Generic print: Hello

    Printer<int> intPrinter;
    intPrinter.print(123); // Outputs: Integer print: 123

    return 0;
}
```

### Example: Partial Specialization
Partial specialization allows you to specialize a template for a subset of its parameters. This is commonly used with class templates but not allowed with function templates.

```cpp
#include <iostream>

template <typename T, typename U>
class Pair {
public:
    Pair(T first, U second) : first(first), second(second) {}
    void print() {
        std::cout << "Pair: " << first << ", " << second << std::endl;
    }
private:
    T first;
    U second;
};

// Partial specialization for pairs of the same type
template <typename T>
class Pair<T, T> {
public:
    Pair(T first, T second) : first(first), second(second) {}
    void print() {
        std::cout << "Matching Pair: " << first << ", " << second << std::endl;
    }
private:
    T first;
    T second;
};

int main() {
    Pair<int, double> pair1(1, 2.5); // two different types: int and double => it calls template <typename T, typename U>
    pair1.print(); // Outputs: Pair: 1, 2.5

    Pair<int, int> pair2(3, 4); // sane types: int and iny => it calls template <typename T, typename T>
    pair2.print(); // Outputs: Matching Pair: 3, 4

    return 0;
}
```

## Variadic Templates
Variadic templates allow a template to accept an arbitrary number of template arguments. This is useful for creating functions or classes that can handle a **variable number** of parameters.

### Key Concepts of Variadic Templates
#### Template Parameter Pack:
A template parameter pack allows you to define a template that can take zero or more **template arguments**.

```cpp
template<typename... Args> //Args is a parameter pack that can hold any number of types.
```

#### Function Parameter Pack:
Similarly, a function parameter pack allows a function to accept zero or more **function arguments.**

```cpp
void func(Args... args); //args is a parameter pack that can hold any number of arguments.
```

#### Expanding Parameter Packs:
Parameter packs can be expanded in the function body using the `...` operator.

```cpp
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';
}
```

#### Usage in Variadic Function Templates
A common use of variadic templates is in creating functions that can accept any number of arguments:

```cpp
#include <iostream>

template <typename T>
void print(T value) {
    std::cout << value << std::endl;
}

template <typename T, typename... Args>
void print(T value, Args... args) {
    std::cout << value << std::endl;
    print(args...);
}

int main() {
    print(1, 2.5, "Hello", 'c');
    // Outputs:
    // 1
    // 2.5
    // Hello
    // c

    return 0;
}
```

##### Step-by-Step Breakdown
###### Initial Call:

```cpp
print(1, 2.5, "Hello", 'a');
```

- `T` is `int`
- `Args...` is `double`, `const char*`, `char`

###### First Recursive Call:

```cpp
std::cout << 1 << ' ';
print(2.5, "Hello", 'a');
```

- `T` is `double`
- `Args...` is `const char*, char`

###### Second Recursive Call:

```cpp
std::cout << 2.5 << ' ';
print("Hello", 'a');
```

- `T` is `const char*`
- `Args...` is `char`

###### Third Recursive Call:

```cpp
std::cout << "Hello" << ' ';
print('a');
```

- `T` is `char`
- `Args...` is is empty

###### Base Case:

```cpp
std::cout << 'a' << ' ';
print();
```

- The parameter pack `Args...` is empty, so the recursion stops.

**Why do we need T here in `template<typename T, typename... Args>`?**
In the context of variadic templates, the non-variadic template parameter `T` plays a crucial role in controlling and facilitating the recursive expansion of the parameter pack `Args.... `

Role of T in Variadic Templates:
* Base Case for Recursion:
    - Variadic templates often rely on recursion to process each element in the parameter pack.
    - `T` serves as the first parameter of each recursive step, allowing the function to process one element of the pack at a time.
    - Eventually, the recursion ends when the parameter pack is empty, reaching the base case of the recursion.
* Processing Each Argument:
    - By isolating `T` from `Args...`, we can process the current argument (`T`) and then recursively process the remaining arguments (`Args...`).

## Template Metaprogramming
*Template metaprogramming* leverages the compile-time nature of templates to perform computations at compile time. This is often used for static assertions, type traits, and other compile-time logic.

*Example: Compile-time Factorial Calculation*

```cpp
#include <iostream>

template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

//Specialization for Base Case : auto calls when N is 0.
template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl; // Outputs: 120
    return 0;
}
```

## SFINAE (Substitution Failure Is Not An Error)
SFINAE is a technique used in template metaprogramming to enable or disable functions based on certain conditions. It allows for more flexible and safe template code.

*Example: SFINAE*

```cpp
#include <iostream>
#include <type_traits>

// Function template for integral types
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value) {
    std::cout << "Integral type: " << value << std::endl;
}

// Function template for floating-point types
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
print(T value) {
    std::cout << "Floating-point type: " << value << std::endl;
}

int main() {
    print(10);    // Outputs: Integral type: 10
    print(3.14);  // Outputs: Floating-point type: 3.14
    return 0;
}
```

### Step-by-Step Process
#### Template Declaration:

```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value);
```

* This declares a function template print that takes a single parameter of type `T`.
* The **return type** is determined by `std::enable_if<std::is_integral<T>::value, void>::type`.

#### More on  `std::enable_if<std::is_integral<T>::value, void>::type`
##### `std::is_integral<T>::value`
* `std::is_integral<T>` is a type trait that checks whether T is an integral type (e.g., `int`, `char`, `long`, etc.).
* `std::is_integral<T>::value` is a constant boolean expression that evaluates to true if `T` is an integral type and false otherwise.

##### `std::enable_if`
* `std::enable_if` is a template in the C++ Standard Library that is used for SFINAE (Substitution Failure Is Not An Error).
* It conditionally defines a type if a boolean condition is true, and does not define the type if the condition is false, causing the template instantiation to **fail.**

##### `std::enable_if<condition, T>::type` 

This basically determines the return type, if not valid return type found template function will not be instantiate.
{: .notice--warning}

* std::enable_if takes two template parameters:
    1. `condition`: A boolean expression (in this case, `std::is_integral<T>::value`).
    2. `T`: The type to define if the condition is true (in this case, `void`).

* If `condition` is true, `std::enable_if<condition, T>::type` is defined as `T` (in this case, `void`).
* If `condition` is false, `std::enable_if<condition, T>::type` is not defined, causing a substitution failure in the template instantiation process. (hence template function will not be "enabled")

##### `typename` Keyword
* The typename keyword is used because `std::enable_if<condition, T>::type` is a dependent type, meaning its definition depends on the template parameter `T`.
* Using `typename` informs the compiler that `type` is a type.

### Why use it?
1. Selective Instantiation: For example, you might want a function to be available only for integral types and another version only for floating-point types.
2. Overloading and Specialization: Templates with SFINAE can help in creating more specialized and optimized implementations for certain types while maintaining a generic implementation for other types.
3. Type Traits and Compile-Time Checks: Using type traits (like `std::is_integral`, `std::is_floating_point`) and SFINAE, you can perform compile-time checks that ensure type correctness without runtime overhead.