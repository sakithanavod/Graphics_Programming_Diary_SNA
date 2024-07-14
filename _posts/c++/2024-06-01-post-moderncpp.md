---
title: "Smart Pointers & Move Semantics"
excerpt_separator: "<!--more-->"
categories:
 - C++, Modern
tags:
 - C++
---
{% include mathJax.html %}

Let's talk about Smart Pointers, Move Semantics.

<!--more-->

**Table of Contents**
* TOC
{:toc}

# Smart Pointers
Smart pointers are a key feature in modern C++ for automatic memory management and avoiding memory leaks. They are part of the C++ Standard Library and are primarily found in the `<memory>` header.

## Unique Pointer (`std::unique_ptr`)
`std::unique_ptr` is a smart pointer in C++ that provides automatic memory management and ensures that a resource (typically memory) is owned by only one `unique_ptr` at a time. When the `unique_ptr` goes out of scope, the resource it owns is automatically deleted, preventing memory leaks.

### Characteristics
* **Exclusive ownership:** only one `unique_ptr` can own the object at any given time.
* Non-copyable, but movable.

### Basic Usage
When you want sole ownership of a dynamically allocated resource. It's ideal for managing resources that should not be shared, such as file handles or sockets.

```cpp
#include <memory>

int main() {
    // Using std::make_unique
    std::unique_ptr<int> ptr1 = std::make_unique<int>(10);

    // Direct assignment (not recommended due to potential exceptions)
    std::unique_ptr<int> ptr2(new int(20));

    return 0;
}
```

### Unique Ownership
`std::unique_ptr` enforces unique ownership, meaning you **cannot copy** a `unique_ptr`. Attempting to do so will result in a compile-time error.

```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
// std::unique_ptr<int> ptr2 = ptr1; // Error: cannot copy a unique_ptr
```

### Transferring Ownership
You can transfer ownership from one unique_ptr to another using `std::move`.

```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
std::unique_ptr<int> ptr2 = std::move(ptr1);

// Now, ptr1 is nullptr and ptr2 owns the resource
```

### Custom Deleters
`std::unique_ptr` supports custom deleters, allowing you to define how the resource should be deleted.

`std::make_unique` does not directly support custom deleters. Instead, you need to create the std::unique_ptr with the custom deleter manually using the `new` keyword:.
{: .notice--warning}

```cpp
#include <iostream>
#include <memory>

struct CustomDeleter {

    /*
    * overloaded function call operator (also known as the call operator) for a class or struct. 
    * This operator allows an instance of the class or struct to be called as if it were a function. 
    */
    void operator()(int* ptr) const {
        std::cout << "Deleting pointer\n";
        delete ptr;
    }
};

int main() {
    std::unique_ptr<int, CustomDeleter> ptr(new int(10));
    return 0;
}
```

### Array Support
`std::unique_ptr` can also manage arrays by using a different syntax.

```cpp
std::unique_ptr<int[]> arr(new int[10]);
arr[0] = 1;
arr[1] = 2;
```

### Benefits
* **Automatic Resource Management:** Automatically deallocates memory when the `unique_ptr` goes out of scope.
* **Exception Safety:** Ensures that resources are properly cleaned up even in the presence of exceptions.
* **Performance:** Lightweight and minimal overhead compared to raw pointers.

### Limitations
* **Non-Copyable:** std::unique_ptr cannot be copied, only moved. This enforces unique ownership semantics.
* **Compatibility:** Requires C++11 or later.

## Shared Pointer (`std::shared_ptr`)
`std::shared_ptr` is another type of smart pointer in C++ that provides shared ownership of a resource. Unlike `std::unique_ptr`, multiple `std::shared_ptr` instances can own the same resource, and the resource is only deallocated when the last `std::shared_ptr` owning it is destroyed.

### Characteristics
* **Shared ownership:** multiple `shared_ptrs` can own the same resource.
* Uses reference counting to manage the resource's lifetime.
* When the last `shared_ptr` owning the resource is destroyed, the resource is freed.

### Basic Usage
You can create a `std::shared_ptr` using `std::make_shared` or by directly assigning a raw pointer.

```cpp
#include <memory>
#include <iostream>

int main() {
    // Using std::make_shared
    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);

    // Direct assignment (less safe, not recommended)
    std::shared_ptr<int> ptr2(new int(20));

    // Accessing the value
    std::cout << "Value: " << *ptr1 << std::endl;

    return 0;
}
```

### Shared Ownership
Multiple `std::shared_ptr` instances can share ownership of the same resource.

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1; // Both ptr1 and ptr2 now own the resource

std::cout << "ptr1 use count: " << ptr1.use_count() << std::endl; // Outputs 2
std::cout << "ptr2 use count: " << ptr2.use_count() << std::endl; // Outputs 2
```

### Automatic Resource Management
The resource is automatically deallocated when the last `std::shared_ptr` owning it is destroyed.

```cpp
{
    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
    {
        std::shared_ptr<int> ptr2 = ptr1;
        // ptr1 and ptr2 both own the resource
    }
    // ptr2 is out of scope, but ptr1 still owns the resource
}
// ptr1 is out of scope, and the resource is automatically deleted
```

### Custom Deleters
`std::shared_ptr` also supports custom deleters.

```cpp
#include <memory>
#include <iostream>

struct CustomDeleter {
    void operator()(int* ptr) const {
        std::cout << "Deleting pointer with value: " << *ptr << "\n";
        delete ptr;
    }
};

int main() {
    std::shared_ptr<int> ptr(new int(15), CustomDeleter());

    return 0;
}
```

### Circular References
One potential issue with `std::shared_ptr` is circular references, which can prevent the resource from being deallocated.

```cpp
#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;
    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();
    node1->next = node2;
    node2->next = node1;

    // This creates a circular reference, causing a memory leak
    return 0;
}

```

#### Break Circular References
To resolve this, you can use `std::weak_ptr`, which provides a non-owning reference.

```cpp
#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Use weak_ptr to break circular reference
    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();
    node1->next = node2;
    node2->prev = node1; // Use weak_ptr

    return 0;
}
```

## Weak Pointer (`std::weak_ptr`)
A `std::weak_ptr` is a smart pointer that holds a non-owning ("weak") reference to an object managed by `std::shared_ptr`. It is used to prevent cyclic references that can cause memory leaks.

### Characteristics
* Non-owning: `std::weak_ptr` does not increase the reference count of the object it points to.
* Observation: It can observe an object managed by `std::shared_ptr` without participating in the ownership.
* Expiry Check: It provides mechanisms to check whether the object it points to has been destroyed.

### Basic Usage
You create a `std::weak_ptr` from a `std::shared_ptr`:

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp = sp; // wp is now observing sp

    // Use lock() to create a shared_ptr from the weak_ptr
    if (std::shared_ptr<int> sp2 = wp.lock()) {
        std::cout << "sp2 value: " << *sp2 << std::endl;
    } else {
        std::cout << "The object has been destroyed" << std::endl;
    }

    return 0;
}
```

### Checking Expiry
You can check whether the `std::weak_ptr` is still valid using `expired()` and `lock()`:

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp = sp;

    sp.reset(); // Destroy the managed object

    if (wp.expired()) {
        std::cout << "The object has been destroyed" << std::endl;
    } else {
        std::cout << "The object is still alive" << std::endl;
    }

    return 0;
}
```

### Avoiding Circular References
`std::weak_ptr` is useful for breaking circular references, which can cause memory leaks if not handled properly

[Circular References](#circular-references)

### Conversion from `std::weak_ptr` to `std::shared_ptr`
The lock() function in `std::weak_ptr` is used to create a `std::shared_ptr` from a `std::weak_ptr`. This operation attempts to acquire a shared ownership of the resource managed by the `std::shared_ptr` that the `std::weak_ptr` is observing. 

If the original `std::shared_ptr` is still valid (i.e., it has not been destroyed), lock() returns a new std::shared_ptr that shares ownership of the managed object. If the original `std::shared_ptr` has been destroyed, lock() returns an empty `std::shared_ptr`.

## Best Practices
* Prefer `unique_ptr` when exclusive ownership is needed.
* Use `make_shared` and `make_unique` for creating smart pointers as they are more efficient and safe.
* Use `weak_ptr` to break cyclic dependencies in graphs or trees.

# Move Semantics
Move semantics in C++ are a powerful feature introduced in C++11, allowing resources to be transferred from one object to another, thus optimizing performance and resource management. 

## Lvalues and Rvalues in C++
In C++, lvalues and rvalues are categories of expressions that describe the types of values they produce and how they can be used.

### Lvalues
* **Definition:** An lvalue (locator value) refers to an object that occupies some identifiable location in memory (i.e., it has a persistent address).
* **Characteristics:** 
    - Can appear on the **left-hand side** or **the right-hand** side of an assignment.
    - Has a lifespan beyond the single expression in which it appears.
    - *Examples:* variables, dereferenced pointers, array elements, function calls returning a reference.

### Rvalues
* **Definition:** An rvalue (read value) refers to a temporary object or a value that does not have a persistent memory address.
* **Characteristics:** 
    - Can appear only on the **right-hand** side of an assignment.
    - Has a lifespan within the single expression in which it appears.
    - *Examples:*  literals, temporary objects, function calls returning a non-reference value.

### Example of L & R Values
```cpp
int x = 10;     // x is an lvalue
int y = 20;     // y is an lvalue
x = y;          // x and y are lvalues
x = 10;         // 10 is an rvalue
int* p = &x;    // x is an lvalue
*p = 30;        // *p is an lvalue
std::string s = std::string("hello"); //// std::string("hello") is a temporary rvalue

void foo(std::string&& s) {
    // s is an rvalue reference
}
foo(std::string("temp")); // std::string("temp") is a temporary rvalue
```

### Lvalue References
* **Syntax:** `T&` where `T` is a type.
* **Usage:** Used to refer to an lvalue, allowing you to modify the object it refers to.

```cpp
int a = 5;
int& ref = a; // "ref" is an lvalue reference to "a"
ref = 10;     // Modifies "a" to 10
```

### Rvalue References
* **Syntax:**  `T&&` where `T` is a type.
* **Usage:** Used to refer to an rvalue, enabling move semantics and efficient transfer of resources.

```cpp
int&& rref = 5; // "rref" is an rvalue reference to the rvalue 5
```

### Move Semantics and Rvalue References
Move semantics allow the efficient transfer of resources from **temporary objects (rvalues)** to more **permanent objects**, avoiding unnecessary copying.

## Basics of Move Semantics
### Move Constructor
A move constructor is used to initialize an object by transferring resources from an rvalue (temporary object) to the newly created object.

```cpp
class MyClass {
public:
    MyClass(MyClass&& other) noexcept {
        // Transfer ownership of resources from `other` to `this`
        this->data = other.data;
        other.data = nullptr;  // Set the source's pointer to nullptr
    }
    // Other members...
};
```
### Move Assignment Operator
A move assignment operator transfers resources from an rvalue to an existing object.

```cpp
class MyClass {
public:
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete[] data;  // Clean up current resources
            this->data = other.data;
            other.data = nullptr;  // Set the source's pointer to nullptr
        }
        return *this;
    }
    // Other members...
};
```

### Example Usage
```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
    std::vector<int> data;

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move constructor called" << std::endl;
    }

    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        std::cout << "Move assignment operator called" << std::endl;
        return *this;
    }
};

int main() {
    MyClass obj1;
    obj1.data = {1, 2, 3, 4, 5};

    MyClass obj2 = std::move(obj1); // Calls move constructor

    MyClass obj3;
    obj3 = std::move(obj2); // Calls move assignment operator

    return 0;
}
```

### Standard Library Helpers
#### `std::move`
`std::move` casts an lvalue to an rvalue, enabling move semantics.

```cpp
#include <iostream>
#include <utility>

int main() {
    int x = 10;
    int&& r = std::move(x); // r is now an rvalue reference to x
    std::cout << r << std::endl;

    return 0;
}
```

#### `std::forward`
`std::forward` is used to forward arguments while preserving their value category (lvalue or rvalue). It is especially useful in template code for implementing perfect forwarding.

```cpp
#include <iostream>
#include <utility>

void process(int& lref) {
    std::cout << "Lvalue reference called" << std::endl;
}

void process(int&& rref) {
    std::cout << "Rvalue reference called" << std::endl;
}

template <typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg)); // Perfect forwarding
}

int main() {
    int x = 10;
    wrapper(x);         // Calls process(int& lref)
    wrapper(10);        // Calls process(int&& rref)

    return 0;
}
```

When you see a function template like template `<typename T> void wrapper(T&& arg)`, the `T&&` arg does **not** always represent an rvalue reference. Instead, it represents a **forwarding reference.**
{: .notice--warning}

#### Forwarding References
Forwarding references allow a function template to accept *both* lvalues and rvalues.The type deduction and **reference collapsing** rules of C++ come into play here.

#### Reference Collapsing Rules
Reference collapsing rules dictate how combinations of references are treated in C++ when type deductions and template instantiations are performed. These rules are particularly important in the **context of templates and forwarding references**.

When combining references (e.g., through type deduction in templates), the following rules apply:
1. T& & collapses to T&.
2. T& && collapses to T&.
3. T&& & collapses to T&.
3. T&& && collapses to T&&.

##### Why This Matters
These rules ensure that reference types are handled consistently and safely, avoiding scenarios where references to references might lead to ambiguous or undefined behavior.

Let's take this code example:

```cpp
#include <iostream>
#include <utility>

void process(int& lref) {
    std::cout << "Lvalue reference called" << std::endl;
}

void process(int&& rref) {
    std::cout << "Rvalue reference called" << std::endl;
}

template <typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg)); // Perfect forwarding
}

int main() {
    int x = 10;
    wrapper(x);         // Calls process(int& lref)
    wrapper(10);        // Calls process(int&& rref)

    return 0;
}
```

Explanation:
1. `wrapper(x)`
    - `x` is an lvalue.
    - `T` is deduced to `int&` because `x` is an lvalue.
    - `T&&` becomes `int& &&`, which collapses to `int&`.
    - `std::forward<T>(arg)` becomes `std::forward<int&>(arg)`, which forwards `arg` as an lvalue reference.
    - `process(int& lref)` is called.

2. `wrapper(10)`
    - `10` is an rvalue.
    - `T` is deduced to `int ` because `10` is an rvalue.
    - `T&&` becomes `int&& &&`, which collapses to `int&&`.
    - `std::forward<T>(arg)` becomes `std::forward<int&&>(arg)`, which forwards `arg` as an rvalue reference.
    - `process(int&& rref)` is called.
