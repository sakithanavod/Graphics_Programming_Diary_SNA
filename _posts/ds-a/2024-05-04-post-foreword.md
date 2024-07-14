---
title: "Data Structures and Algorithms - Introduction"
excerpt_separator: "<!--more-->"
categories:
 - Data Structures and Algorithms 
tags:
 - DSA
---
{% include mathJax.html %}

Curated list of data structures and algorithms that are particularly useful in game development

<!--more-->
## Algorithm Analysis

### Time Complexity
Time complexity is a way to analyze the efficiency of an algorithm by quantifying the amount of time it takes as a function of the size of the input. It helps in comparing algorithms and understanding how they scale with increasing input sizes.

#### Big O Notation (O)
Big O notation describes the upper bound of an algorithm's running time. It gives the worst-case scenario for the time complexity, ensuring the algorithm will not run longer than this bound.

##### Examples of Time complexity:

* O(1): Constant time. The algorithm's running time does not change with the size of the input.
* O(log n): Logarithmic time. The running time increases logarithmically with the input size.
* O(n): Linear time. The running time increases linearly with the input size.
* O(n log n): Linearithmic time. Common in efficient sorting algorithms like merge sort and quicksort.
* O(n^2): Quadratic time. The running time increases quadratically with the input size. Common in simple sorting algorithms like bubble sort, insertion sort, and selection sort.
* O(2^n): Exponential time. The running time doubles with each additional element in the input.
* O(n!): Factorial time. The running time grows factorially with the input size.

![Alt Text]({{ site.baseurl }}/assets/dsa/dsa1.jpeg)

##### How to Calculate Big O Notation
To determine the Big O notation for an algorithm, follow these steps:

1. **Identify the Basic Operations:** Determine which operations *dominate* the running time as the input size increases. Look for *loops*, *recursive calls*, or any *repeated work.*

2. **Count the Operations:** Count the number of times the basic operations are executed in terms of `n`.

3. **Express in Terms of `n`:** Express the total running time as a function of `n`.

4. **Simplify the Expression:** Simplify the function by keeping the *dominant* terms and ignoring the *constant factors* and *lower-order* terms.

##### Example 1

```cpp
#include <iostream>
#include <vector>

int sumArray(const std::vector<int>& arr) {
    int sum = 0; // 1 operation
    for (int i = 0; i < arr.size(); ++i) { // n operations
        sum += arr[i]; // n operations
    }
    return sum; // 1 operation
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    int sum = sumArray(arr);
    std::cout << "Sum of array elements: " << sum << std::endl;
    return 0;
}
```

##### Step-by-Step Analysis
1. Identify the Basic Operations:
    - `sum = 0;` (assignment)
    - `for (int i = 0; i < arr.size(); ++i)` (loop iteration and comparison)
    - `sum += arr[i];` (addition and assignment)
    - `return sum;` (return statement)

2.  Count the Number of Operations:
    - `sum = 0;` executes once.
    - `for (int i = 0; i < arr.size(); ++i)` executes **n** times (where n is the size of the array).
    - `sum += arr[i];` executes n times.
    - `return sum;` executes once.

3.  Express the Total Operations as a Function of n:
    - Total operations: **1+n+n+1=2n+2**

4.  Simplify the Expression:
    - Focus on the term with the highest growth rate: 2n
    - Ignore lower-order terms and constant factors: 2n

5.  Determine the Big O Notation:
    - The simplified expression 2n indicates that the algorithm's time complexity is linear.
    - The Big O notation is **O(n).**

##### Example 2

```cpp
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate mid point

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            left = mid + 1;

        // If x is smaller, ignore right half
        else
            right = mid - 1;
    }

    // If we reach here, then the element was not present
    return -1;
}

```

##### Step-by-Step Analysis
1. Identify the Basic Operations:
    -  Loop condition check: `left <= right`
    -  Calculation of mid point: `mid = left + (right - left) / 2`
    -  Comparison: `arr[mid] == x`
    -  Adjusting `left` or `right` based on the comparison: `left = mid + 1` or `right = mid - 1`
    -  Return statement: `return mid` or `return -1`

2.  Count the Number of Operations:
    - Each iteration of the loop includes:
        - Loop condition check
        - Midpoint calculation.
        - Comparison to check if `arr[mid] == x`
        - Comparison to check if `arr[mid] < x` or `arr[mid] > x`
        - Adjustment of `left` or `right`

3.  Express the Total Operations as a Function of n Worst Case (O):
    - The worst case occurs when the element `x` is not in the array or is found at the last possible position checked.
    - The loop runs in the worst case: $$\log_2(n)$$ times.
        - This process of halving the search space continues.
        - After `k` iterations, the search space will be reduced to `n / 2^k`.
        - The loop continues until the search space is reduced to a single element, i.e., when `left` equals `right`.
        - This happens when `n / 2^k = 1`, where `k` is the number of iterations.
        - so, $$k = \log_2(n)$$

4.  Simplify the Expression:
    - Focus on the term with the highest growth rate: $$\log_2(n)$$ 

5.  Determine the Big O Notation:
    - Thus, the binary search algorithm performs at most $$\log_2(n)$$ 

## Data Structures
Data structures are ways to organize and store data in a computer so that it can be accessed and modified efficiently. They provide a means to manage large amounts of data, making it easier to perform operations such as searching, sorting, and updating.

1. **Arrays and Vectors**
    - Basic storage, used for dynamic lists of elements
    - Example: Player inventories, level data.

2. **Linked Lists**
    - Useful for dynamic memory management.
    - Example: Undo functionality, game state history.

3. **Stacks and Queues**
    - Stacks: Used for depth-first search (DFS), backtracking.
    - Queues: Used for breadth-first search (BFS), task scheduling.
    - Example: AI decision-making, game event handling.

4. **Hash Tables (Unordered Maps)**
    - Fast lookups, inserts, and deletes.
    - Example: Game asset management, fast access to game objects.

5. **Binary Search Trees (BST)**
    - Used for sorted data and range queries.
    - Example: Leaderboards, balancing game mechanics.

6. **Heaps (Priority Queues)**
    - Efficient priority management.
    - Example: AI pathfinding (A* algorithm), task scheduling.

7. **Graphs**
    - Represent networks of interconnected objects.
    - Example: Pathfinding, game maps, social graphs in multiplayer games.

8. **Spatial Data Structures**
    - Quadtrees and Octrees: Efficiently manage spatial information.
    - KD-Trees: Used for nearest neighbor searches.
    - BVH (Bounding Volume Hierarchy): Used for collision detection.


## Algorithms

1. **Sorting Algorithms**
    - Quick Sort, Merge Sort, Heap Sort: Efficient sorting techniques.
    - Radix Sort: Useful for integer sorting, often used in graphics processing.

2. **Search Algorithms**
    - Binary Search: Fast searching in sorted arrays.
    - Hash-based Search: Fast searching using hash tables.

3. **Graph Algorithms**
    - Dijkstra’s Algorithm: Shortest path in weighted graphs.
    - A Search Algorithm:* Used extensively in pathfinding.
    - DFS and BFS: Fundamental for exploring nodes and paths.

4. **Dynamic Programming**
    - Solving problems by breaking them down into simpler subproblems.
    - Example: Optimal game strategies, resource allocation.

5. **Greedy Algorithms**
    - Making the locally optimal choice at each stage.
    - Example: AI decision-making, scheduling.

6. **Mathematical Algorithms**
    - Linear Algebra: Matrix operations for graphics, physics simulations.
    - Fast Inverse Square Root: Optimization for 3D graphics.

7. **Collision Detection Algorithms**
    - Separating Axis Theorem (SAT): Detecting collisions between convex shapes.
    - Sweep and Prune: Efficient broad-phase collision detection.
    - Ray Casting: Line-of-sight checks, visibility checks.

8. **Memory Management Techniques**
    - Pool Allocators: Efficient memory allocation for game objects.
    - Smart Pointers: Managing resource lifetimes.