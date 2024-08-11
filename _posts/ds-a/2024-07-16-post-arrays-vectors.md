---
title: "Arrays and Vectors"
excerpt_separator: "<!--more-->"
categories:
 - dsa
tags:
 - DSA
---
{% include mathJax.html %}

Most basic data structure to hold data together.

<!--more-->
## Arrays
An array is a collection of elements, all of the **same type**, stored in contiguous memory locations. Each element can be accessed directly using an index.

### Memory Allocation:
* **Contiguous Memory:** All elements of an array are stored in contiguous memory locations. This means that the elements are placed sequentially in memory.

* **Fixed Size:** The size of the array is determined at the time of its creation and remains constant throughout its lifetime.

### Detailed Explanation:
#### Memory Layout: 
When you declare an array, a block of memory is allocated to hold all the elements. For example, in an array int arr[5], memory for 5 integers is allocated contiguously.

If the base address of the array is `1000` and each integer takes 4 bytes, the elements will be stored at addresses `1000`, `1004`, `1008`, `1012`, and `1016`.

#### Index Calculation:
Accessing `arr[i]` involves calculating the address as `base_address + i * size_of_element`. For example, accessing `arr[3]` would result in `1000 + 3*4 = 1012`.

## Vectors
A vector is a dynamic array provided by the *C++ Standard Library*. Unlike arrays, vectors can change size dynamically, meaning they can grow or shrink as needed.

Vectors manage their own memory. They start with an initial capacity and allocate more memory as needed. When the vector’s size **exceeds** its capacity, it allocates a new block of memory (usually doubling the current capacity), copies the existing elements to the new block, and frees the old block.

### Memory Allocation:
* **Dynamic Size:** Vectors can resize themselves automatically when elements are added or removed.
* **Capacity:** Vectors allocate extra memory to accommodate future growth. The capacity is the total amount of memory allocated, which can be more than the current size (number of elements).

### Basic Operations:
* Accessing Elements: `vec[i]` constant time, O(1), since vectors use contiguous memory.
* Modifying Elements: `vec[i] = value` Modifying an element by index is also O(1).
* Adding Elements: `vec.push_back(value)` Adding an element to the end of the vector is typically amortized O(1) (If the vector’s capacity is exceeded, it reallocates more memory, which can be O(n) in the worst case)
* Insert: `vec.insert(vec.begin() + index, value)` Inserting an element at a specific position requires shifting elements, which is O(n) in the worst case.
* Removing Elements: `vec.pop_back()` (O(1)) or `vec.erase(vec.begin() + index)` (Removing an element at a specific position requires shifting elements, which is O(n) in the worst case.)

## Vector Implementation C++

```cpp
#include <iostream>

template <typename T>
class SVector
{
public:
    SVector(): m_Data(nullptr), m_Size(0), m_Capacity(0) {}
    ~SVector()
    {
        delete[] m_Data;
    }

    SVector(const SVector& other)
    {
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Data = new T[m_Capacity];

        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i] = other.m_Data[i];
        }
    }

    SVector(SVector&& other) noexcept
        :   m_Data(other.m_Data),
            m_Size(other.m_Size),
            m_Capacity(other.m_Capacity)     
    {
        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }

    void push_back(const T& value)
    {
        if (m_Capacity == m_Size)
        {
            resize(m_Capacity == 0 ? 1 : m_Capacity * 2);
        }

        // add new element to data
        m_Data[m_Size++] = value;
    }

    void pop_back()
    {
        if (m_Size != 0)
        {
            m_Data[--m_Size].~T();
        }
        else
        {
            throw std::out_of_range("vector is empty");
        }
    }

    T& operator[](size_t index)
    {
        if (index >= m_Size)
        {
            throw std::out_of_range("ndex out of range");
        }

        return m_Data[index];
    }

    SVector& operator=(const SVector& other)
    {
        if (this == &other)
        {
            return *this; // Self-assignment check
        }

        delete[] m_Data; // Free the existing resource

        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Data = new T[m_Capacity];

        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i] = other.m_Data[i];
        }

        return *this;
    }

    SVector& operator=(SVector&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_Data;

        m_Data = other.m_Data;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;

        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }

    size_t GetSize() { return m_Size; }
    size_t GetCapacity() { return m_Capacity; }

private:
    T* m_Data;
    size_t m_Size;
    size_t m_Capacity;

    void resize(size_t newCapacity)
    {
        T* newdata = new T[newCapacity];
        for (size_t i = 0; i < m_Size; i++)
        {
            newdata[i] = m_Data[i];
        }

        delete[] m_Data;
        m_Data = newdata;
        m_Capacity = newCapacity;
    }
};

int main()
{
    SVector<int> vec;

    // Adding elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Accessing elements
    std::cout << "Element at index 0: " << vec[0] << std::endl;
    std::cout << "Element at index 1: " << vec[1] << std::endl;
    std::cout << "Element at index 2: " << vec[2] << std::endl;

    // Modifying elements
    vec[1] = 25;
    std::cout << "Modified element at index 1: " << vec[1] << std::endl;

    // Removing elements
    vec.pop_back();
    std::cout << "Size after removing element: " << vec.GetSize() << std::endl;

    // Displaying all elements
    for (size_t i = 0; i < vec.GetSize(); ++i) {
        std::cout << "Element at index " << i << ": " << vec[i] << std::endl;
    }

    // Copy constructor
    SVector<int> vec2 = vec;
    std::cout << "Copied vector element at index 0: " << vec2[0] << std::endl;

    // Move constructor
    SVector<int> vec3 = std::move(vec2);
    std::cout << "Moved vector element at index 0: " << vec3[0] << std::endl;

    // Copy assignment operator
    SVector<int> vec4;
    vec4 = vec;
    std::cout << "Copy assigned vector element at index 0: " << vec4[0] << std::endl;

    // Move assignment operator
    SVector<int> vec5;
    vec5 = std::move(vec4);
    std::cout << "Move assigned vector element at index 0: " << vec5[0] << std::endl;

    return 0;
}

```