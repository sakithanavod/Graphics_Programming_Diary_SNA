---
title: "Lambda Expressions, Keywords & Uniform initialization"
excerpt_separator: "<!--more-->"
categories:
 - C++, Modern
tags:
 - C++
---
{% include mathJax.html %}

Let's talk about Lambda Expressions, Keywords & Uniform initialization

<!--more-->

**Table of Contents**
* TOC
{:toc}

# Lambda Expressions
Lambda expressions, introduced in C++11, provide a concise way to define anonymous function objects directly within your code. They are particularly *useful for short, throwaway functions* that are not *reused* elsewhere.

## Basic Syntax of Lambda Expressions
```cpp
[capture](parameters) -> return_type {
    body
}
```

* **Capture:** Defines which variables from the surrounding scope are accessible within the lambda.
* **Parameters:** Defines the input parameters, similar to a function.
* **Return Type:** Specifies the return type (optional if it can be inferred).
* **Body:** Contains the code to be executed when the lambda is called.

**Example of a Simple Lambda**
```cpp
auto add = [](int a, int b) -> int {
    return a + b;
};
std::cout << add(2, 3) << std::endl;  // Output: 5
```

## Capture Clause
The capture clause defines which variables from the surrounding scope can be accessed inside the lambda.

### Capture by Value
Capturing by value copies the variables into the lambda, so changes to these variables outside the lambda do not affect the captured values.

```cpp
int x = 10;
auto captureByValue = [x]() {
    std::cout << x << std::endl;  // Captures the value of x
};
x = 20;
captureByValue();  // Output: 10
```

When a lambda expression captures a variable by value, it **captures** the value of that variable at the **moment the lambda is created**, not when it is called.
{: .notice--success}

When you write a lambda that captures a variable by value, it makes a **copy of that variable's value** at the time the lambda is created. This **copy** is then used whenever the lambda is called, regardless of any changes to the original variable after the lambda's creation.
{: .notice--warning}

### Capture by Reference
Capturing by reference allows the lambda to access and modify the variables directly.

```cpp
int x = 10;
auto captureByReference = [&x]() {
    std::cout << x << std::endl;  // Captures the reference of x
};
x = 20;
captureByReference();  // Output: 20
```

*Another example*

```cpp
int x = 10;
auto captureByReference = [&x]() {
    x += 5;
};
captureByReference();
std::cout << x << std::endl;  // Output: 15
```

### Default Capture Modes
Lambdas can access all variables within the scope where the lambda is defined:

* Capture All by Value (`[=]`): Captures all variables used in the lambda by value.
* Capture All by Reference (`[&]`): Captures all variables used in the lambda by reference.

```cpp
int x = 10, y = 20;
auto captureAllByValue = [=]() {
    return x + y;
};
auto captureAllByReference = [&]() {
    x += y;
};
captureAllByReference();
std::cout << x << std::endl;  // Output: 30
```

### Mutable Lambdas
By default, lambdas that **capture variables by value** are **not allowed** to modify those variables. To allow modification, you need to use the `mutable` keyword.

```cpp
int x = 10;
auto mutableLambda = [x]() mutable {
    x += 5;
    std::cout << x << std::endl;  // Output: 15
};
mutableLambda();
std::cout << x << std::endl;  // Output: 10 (original x is unchanged)
```

### Lambda with No Capture
If a lambda does not capture any variables from the surrounding scope, it is effectively a regular function.

```cpp
auto noCapture = [](int a, int b) {
    return a + b;
};
std::cout << noCapture(2, 3) << std::endl;  // Output: 5
```

### Returning Lambdas from Functions
Functions can return lambda expressions.

```cpp
auto createLambda() {
    return [](int a, int b) {
        return a + b;
    };
}

auto lambda = createLambda();
std::cout << lambda(3, 4) << std::endl;  // Output: 7
```

### Generic Lambdas
With C++14, lambdas can be generic using the `auto` keyword in their parameter list.

```cpp
auto genericLambda = [](auto a, auto b) {
    return a + b;
};
std::cout << genericLambda(1, 2) << std::endl;  // Output: 3
std::cout << genericLambda(1.5, 2.5) << std::endl;  // Output: 4.0
```

### Using Lambdas with Standard Algorithms
Lambdas are often used with standard algorithms for concise and readable code.

```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
std::for_each(vec.begin(), vec.end(), [](int &n) {
    n *= 2;
});

for (int n : vec) {
    std::cout << n << " ";  // Output: 2 4 6 8 10
}
std::cout << std::endl;
```

### Capturing `this` Pointer
Lambdas can capture the `this` pointer to access members of the enclosing class.

```cpp
class MyClass {
    int x = 10;
public:
    void printX() {
        auto captureThis = [this]() {
            std::cout << this->x << std::endl;
        };
        captureThis();  // Output: 10
    }
};
```

## Common situations where using lambdas is beneficial
### Inline Function Definitions
Lambdas are useful for defining small, inline functions that are used only in a specific context and do not need a separate named function.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    return 0;
}
```

### Sorting and Algorithms
Lambdas are often used with standard library algorithms to define custom comparison or transformation logic.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;
    });

    for (int n : numbers) {
        std::cout << n << " ";
    }
    return 0;
}
```

### Event Handling and Callbacks
Lambdas provide a convenient way to define callback functions, such as event handlers in GUI applications or asynchronous operations.

```cpp
#include <iostream>
#include <functional>

void executeCallback(const std::function<void()>& callback) {
    
    // Simulate some work being done
    std::this_thread::sleep_for(std::chrono::seconds(2));
    callback();
}

int main() {
    executeCallback([]() {
        std::cout << "Callback executed!" << std::endl;
    });
    return 0;
}
```

### Capturing Local Variables
Lambdas can capture local variables by value or by reference, allowing them to access and manipulate those variables even after the variables have gone out of scope in the calling function.

```cpp
#include <iostream>
#include <functional>

void executeCallback(const std::function<void()>& callback) {
    
    // Simulate some work being done
    std::this_thread::sleep_for(std::chrono::seconds(2));
    callback();
}

int main() {
    executeCallback([]() {
        std::cout << "Callback executed!" << std::endl;
    });
    return 0;
}
```

### Custom Deleters with Smart Pointers
Lambdas are useful for defining custom deleters for smart pointers, ensuring that resources are properly cleaned up.

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr(new int(10), [](int* p) {
        std::cout << "Deleting pointer with value: " << *p << std::endl;
        delete p;
    });

    return 0;
}
```

# `auto` Keyword
The `auto` keyword in C++ is a type inference keyword introduced in C++11 that allows the compiler to automatically deduce the type of a variable at compile time. 

## Basic Usage of `auto`
The `auto` keyword can be used to declare variables without explicitly specifying their type. The compiler deduces the type **based on the initializer**.

*Example of using auto*

```cpp
#include <iostream>
#include <vector>

int main() {
    auto x = 42;                // x is deduced to be int
    auto y = 3.14;              // y is deduced to be double
    auto z = "Hello, World!";   // z is deduced to be const char*

    std::cout << x << std::endl; // Output: 42
    std::cout << y << std::endl; // Output: 3.14
    std::cout << z << std::endl; // Output: Hello, World!

    return 0;
}
```

## Advantages of `auto`
1. **Simplifies Code:** Reduces verbosity, especially with complex types like iterators and function pointers.
2. **Improves Readability:** Makes the code easier to read by focusing on the logic rather than type details.
3. **Reduces Type-related Errors:** Minimizes the risk of mismatched types, as the compiler ensures correct type deduction.
4. **Ease of Refactoring:** When changing the type of a variable, only the initializer needs to change, not the declaration.

## Using `auto` with Iterators
Iterators often have complex types that can be cumbersome to declare explicitly. The `auto` keyword simplifies this.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
```

## `auto` and Range-based for Loops
The `auto` keyword is often used with range-based for loops to simplify element type declaration.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (auto value : vec) {
        std::cout << value << " ";
    }

    return 0;
}
```

## Deduction of References and Pointers
When using `auto`, the type deduced can include references and pointers, depending on the initializer.

```cpp
int main() {
    int x = 10;
    int& ref = x;
    int* ptr = &x;

    auto a = ref;  // a is deduced to be int, not int&
    auto b = ptr;  // b is deduced to be int*

    a = 20;
    *b = 30;

    std::cout << "x: " << x << std::endl;  // Output: x: 30
    std::cout << "a: " << a << std::endl;  // Output: a: 20

    return 0;
}
```

## Preserving References with `auto&`
To preserve references, use `auto&` in the declaration.

```cpp
int main() {
    int x = 10;
    int& ref = x;

    auto a = ref;   // a is deduced to be int, not int&
    auto& b = ref;  // b is deduced to be int&

    a = 20;
    b = 30;

    std::cout << "x: " << x << std::endl;  // Output: x: 30
    std::cout << "a: " << a << std::endl;  // Output: a: 20

    return 0;
}
```

## `const` and `auto`
The `auto` keyword can deduce const types. However, if you want `auto` itself to be const, you need to explicitly specify it.

```cpp
int main() {
    const int x = 10;
    auto a = x;        // a is deduced to be int
    const auto b = x;  // b is deduced to be const int

    a = 20;  // OK
    // b = 20;  // Error: b is const

    return 0;
}
```

## `auto` in Function Return Types
C++14 and later allow auto to be used in function return types, enabling return type deduction.

```cpp
#include <iostream>

auto add(int a, int b) {
    return a + b;  // Compiler deduces return type as int
}

int main() {
    std::cout << add(2, 3) << std::endl;  // Output: 5

    return 0;
}
```

## Limitations of `auto`
1. **No Deduction from Function Parameters:** auto cannot be used for function parameters.
2. **No Direct Usage for Class Members:** auto cannot be used directly in member declarations within a class.
3. **Initializer Required:** auto requires an initializer to deduce the type.

# `nullptr ` Keyword
The `nullptr` keyword in C++ is used to represent a null pointer, a pointer that does not point to any object or function. It was introduced in C++11 to replace the traditional use of `NULL` or `0` for null pointers, providing a type-safe and more explicit way to handle null pointers.

## Reasons for Introducing `nullptr`
1. **Type Safety:** `nullptr` is of type std::nullptr_t, which ensures that it can only be assigned to or compared with pointers. This prevents accidental use in non-pointer contexts.
2. **Clarity:** Using `nullptr` explicitly indicates that the intention is to work with pointers, making the code more readable and less error-prone.
3. **Overload Resolution:** `nullptr` helps in resolving function overloads by ensuring that the correct overload is selected when dealing with null pointers.

## Basic Usage

```cpp
int* p = nullptr; // p is a null pointer

//Comparing Pointers with nullptr
if (p == nullptr) {
    std::cout << "p is null" << std::endl;
}
```

## `nullptr` and Function Overloading
One of the key advantages of `nullptr` is its role in function overload resolution. Consider the following example:

```cpp
void foo(int* p) {
    std::cout << "foo(int* p)" << std::endl;
}

void foo(double* p) {
    std::cout << "foo(double* p)" << std::endl;
}

int main() {
    foo(nullptr); // Unambiguous, calls foo(int* p) or foo(double* p) based on context
    return 0;
}
```

Using `0` or `NULL` could lead to ambiguities or unintended function calls:

```cpp
void foo(int* p) {
    std::cout << "foo(int* p)" << std::endl;
}

void foo(double d) {
    std::cout << "foo(double d)" << std::endl;
}

int main() {
    // foo(0); // Ambiguous: could match foo(int* p) or foo(double d)
    // foo(NULL); // Ambiguous: could match foo(int* p) or foo(double d)
    foo(nullptr); // Unambiguous, calls foo(int* p)
    return 0;
}
```

## `std::nullptr_t`
`std::nullptr_t` is the type of `nullptr`. It can be used to write functions that specifically accept `nullptr`.

```cpp
void bar(std::nullptr_t) {
    std::cout << "bar called with nullptr" << std::endl;
}

int main() {
    bar(nullptr); // Calls bar(std::nullptr_t)
    return 0;
}
```

# Uniform initialization
Uniform initialization in C++ is a feature introduced in C++11 that provides a consistent syntax for initializing variables and objects. It uses curly braces `{}` and is intended to unify the various ways of initialization, making the language simpler and reducing ambiguity. This feature also helps prevent certain types of bugs, such as narrowing conversions.

## Benefits of Uniform Initialization
1. **Consistency:** Provides a single, uniform syntax for initializing all types of variables and objects.
2. **Prevents Narrowing Conversions:** Helps avoid unintentional data loss when converting between types.
3. **Initializer Lists:** Facilitates the use of initializer lists, making it easier to initialize containers and aggregates.
4. **Aggregates and PODs:** Supports aggregate initialization for plain old data (POD) types and other aggregate types.

## Basic Syntax

### Basic Types
```cpp
int x{10}; // Direct initialization
int y = {20}; // Copy initialization
int z{}; // Value initialization, z is initialized to 0
```

### User-Defined Types
```cpp
struct Point {
    int x;
    int y;
};

Point p1{1, 2}; // Aggregate initialization
Point p2 = {3, 4}; // Copy initialization
Point p3{}; // Value initialization, p3.x and p3.y are initialized to 0
```

### Containers
```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5}; // Initializer list

    for (int n : v) {
        std::cout << n << " ";
    }

    return 0;
}
```

### Preventing Narrowing Conversions
One of the key advantages of uniform initialization is its ability to prevent narrowing conversions, which can lead to data loss:

```cpp
double d = 3.14;
int x1{d}; // Error: narrowing conversion
int x2 = {d}; // Error: narrowing conversion
int x3(d); // No error, but narrowing conversion happens
int x4 = d; // No error, but narrowing conversion happens
```

### Using `std::initializer_list`
Uniform initialization can be used to initialize containers using `std::initializer_list:`

```cpp
#include <vector>
#include <initializer_list>
#include <iostream>

class MyClass {
public:
    MyClass(std::initializer_list<int> init) {
        for (auto i : init) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyClass obj{1, 2, 3, 4, 5};
    return 0;
}
```

### Constructor Overloading with `std::initializer_list`
When using uniform initialization, constructors that take `std::initializer_list` can be overloaded to handle different initialization scenarios:

```cpp
#include <vector>
#include <initializer_list>
#include <iostream>

class MyClass {
public:
    MyClass(int a, int b) {
        std::cout << "Two arguments: " << a << ", " << b << std::endl;
    }

    MyClass(std::initializer_list<int> init) {
        std::cout << "Initializer list: ";
        for (auto i : init) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyClass obj1{1, 2}; // Calls MyClass(std::initializer_list<int>)
    MyClass obj2(1, 2); // Calls MyClass(int, int)

    return 0;
}
```

### Special Cases
#### Ambiguity with Single Elements
When initializing with a single element, there might be ambiguity between uniform initialization and constructor calls:

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v1{5}; // Initializer list, vector with one element: 5
    std::vector<int> v2(5); // Constructor, vector with 5 default-initialized elements

    std::cout << "v1 size: " << v1.size() << std::endl; // Outputs: v1 size: 1
    std::cout << "v2 size: " << v2.size() << std::endl; // Outputs: v2 size: 5

    return 0;
}
```

#### Dynamic Arrays
Dynamic arrays can also be initialized using uniform initialization:

```cpp
int* arr = new int[3]{1, 2, 3};

for (int i = 0; i < 3; ++i) {
    std::cout << arr[i] << " ";
}

delete[] arr;
```

### Uniform Initialization in Class Constructors
When defining class constructors, uniform initialization can be used for member initialization:

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    Person(std::string name, int age) : name{name}, age{age} {}
};

int main() {
    Person p{"Alice", 30};
    std::cout << "Name: " << p.name << ", Age: " << p.age << std::endl;

    return 0;
}
```