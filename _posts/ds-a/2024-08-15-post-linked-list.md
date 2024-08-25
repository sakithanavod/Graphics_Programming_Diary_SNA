---
title: "Linked List"
excerpt_separator: "<!--more-->"
categories:
 - dsa
tags:
 - DSA
---
{% include mathJax.html %}

A linked list is a data structure that consists of a sequence of elements, where each element is connected to the next by a reference or pointer.

<!--more-->
## Linked list
A linked list is a data structure that consists of a sequence of elements, where each element is connected to the next by a reference or pointer. 

It's a fundamental concept in computer science, and understanding its structure and operations is essential for many programming tasks.

## Structure of a Linked List

### Node
The building block of a linked list. Each node typically contains two components:

1. *Data:* The value or information the node holds.
2. *Pointer/Reference:* A reference to the next node in the sequence. In some cases, there might be an additional reference to the previous node (in the case of a *doubly linked list*).

### Head
The first node in the linked list. It serves as the entry point to the list.

### Tail
The last node in the linked list, usually having a reference pointing to `null` (or None in some languages), indicating the end of the list.

## Types of Linked Lists

1. **Singly Linked List:** Each node points only to the next node. This is the simplest form of a linked list.
2. **Doubly Linked List:** Each node contains two pointers: one pointing to the next node and another pointing to the previous node. This allows traversal in both directions.
3. **Circular Linked List:** In this variation, the last node points back to the first node, forming a loop.

## Basic Operations on Linked Lists
### Insertion
* *At the Beginning:* A new node is added before the head, and the new node becomes the new head.
* *At the End:* A new node is added after the last node, and the last node's pointer is updated to point to the new node.
* *In the Middle:* A new node is inserted between two existing nodes.

### Deletion
* *At the Beginning:* The head node is removed, and the next node becomes the new head.
* *At the End:* The last node is removed, and the second last node becomes the new tail.
* *In the Middle:* A node between two other nodes is removed, and the surrounding nodes' pointers are updated accordingly.

### Traversal
Visiting each node in the linked list, typically starting from the head and following the pointers to the next node until reaching the end.

### Search
Finding a node with a specific value by traversing the list.

### Nth node in a Linked List
A function that takes a linked list and an integer index and returns the data value stored in the node at that index position. 

### Reversal
Reversing the order of nodes in the linked list, so the head becomes the tail and vice versa.

## Advanced Concepts

### Detecting Loops
In a circular or erroneous linked list, you may need to detect if there's a loop, where a node points back to a previous node.

### Merging Two Linked Lists
Combining two linked lists into one, either by appending one to the other or merging in a sorted order.

### Sorting a Linked List
Implementing algorithms like merge sort or quicksort specifically adapted for linked lists.

## Applications of Linked Lists

### Implementation of Stacks and Queues
Linked lists can be used to efficiently implement these abstract data types.

### Dynamic Memory Allocation
Linked lists are often used to manage memory blocks in dynamic memory allocation.

### Polynomial Representation
Linked lists can represent polynomials where each node stores a term's coefficient and exponent.

## Linked Lists vs Arrays

**Linked List**

* Data Structure: Non-contiguous
* Memory Allocation: Typically allocated one by one to individual elements
* Insertion/Deletion: Efficient
* Access: Sequential

**Array**

* Data Structure: Contiguous
* Memory Allocation: Typically allocated to the whole array
* Insertion/Deletion: Inefficient
* Access: Random

## Linked List Implementation C++

```cpp
#include <iostream>
#include <vector>

template <typename T>
class SNode
{
public:
    SNode(T data):   
            m_Data(data),
            m_Next(nullptr)
    {
    }

    inline T GetValue() { return m_Data; }
    inline SNode<T>* GetNext() { return m_Next; }

    void SetNext(SNode<T>* next) { m_Next = next; }

    void SetValue(T value) 
    {
        m_Data = value;
    }

private:
    T m_Data;
    SNode<T>* m_Next;
};

template <typename T>
class SLinkedList
{
public:
    SLinkedList() = default;

    ~SLinkedList()
    {
        Clear();
    }

    void AddNode(const T& value)
    {
        SNode<T>* newNode = new SNode<T>(value);
        if (m_Tail)
        {
            m_Tail->SetNext(newNode);
            m_Tail = newNode;
        }
        else
        {
            m_Head = m_Tail = newNode;
        }
        m_NodeCount++;
    }

    void Insert(const T& value, unsigned int index)
    {
        if (index > m_NodeCount)
        {
            throw std::out_of_range("Index out of bounds");
        }

        if (index == 0)
        {
            m_Head = new SNode<T>(value, m_Head);
            if (!m_Tail)
            {
                m_Tail = m_Head;
            }
        }
        else
        {
            SNode<T>* prev = GetNodeByID(index - 1);
            SNode<T>* newNode = new SNode<T>(value, prev->GetNext());
            prev->SetNext(newNode);

            if (newNode->GetNext() == nullptr)
            {
                m_Tail = newNode;
            }
        }

        m_NodeCount++;
    }

    void PrintNodeValues() const
    {
        unsigned int count = 0;
        SNode<T>* currentNode = m_Head;

        while (count != m_NodeCount)
        {
            std::cout << "ID: " << count << " Value: " << currentNode->GetValue() << std::endl;
            currentNode = currentNode->GetNext();

            count++;
        }
    }

    void Delete(unsigned int index)
    {
        SNode<T>* temp = nullptr;

        if (index == 0)
        {
            temp = m_Head;
            m_Head = m_Head->GetNext();
            if (m_Head == nullptr)
            {
                m_Tail = nullptr;
            }
        }
        else
        {
            SNode<T>* prev = GetNodeByID(index - 1);
            temp = prev->GetNext();
            prev->SetNext(temp->GetNext());

            if (prev->GetNext() == nullptr)
            {
                m_Tail = prev;
            }
        }

        delete temp;
        m_NodeCount--;
    }

    void Reverse()
    {
        SNode<T>* prev = nullptr;
        SNode<T>* current = m_Head;
        SNode<T>* next = nullptr;
        m_Tail = m_Head;

        while (current != nullptr)
        {
            next = current->GetNext();
            current->SetNext(prev);
            prev = current;
            current = next;
        }

        m_Head = prev;
    }

    void Clear()
    {
        while (m_Head)
        {
            SNode<T>* temp = m_Head;
            m_Head = m_Head->GetNext();
            delete temp;
        }

        m_Tail = nullptr;
        m_NodeCount = 0;
    }

private:
    unsigned int m_NodeCount = 0;

    SNode<T>* m_Head = nullptr;
    SNode<T>* m_Tail = nullptr;


    SNode<T>* GetNodeByID(unsigned int id)
    {
        if (id >= m_NodeCount)
        {
            throw std::out_of_range("Index out of bounds");
        }

        SNode<T>* current = m_Head;
        for (unsigned int i = 0; i < id; ++i)
        {
            current = current->GetNext();
        }

        return current;
    }
};

```