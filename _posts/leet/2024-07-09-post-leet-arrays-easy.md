---
title: "Leet Code Cheat Sheet: Arrays"
excerpt_separator: "<!--more-->"
categories:
 - LeetCode 
tags:
 - Leet
---

Leet Code array problems

<!--more-->

## Arrays
### [1920. Build Array From Permutation](https://leetcode.com/problems/build-array-from-permutation/description/)

To solve this problem without using extra space, we need to find a way to store both the *original value* and the *new value* within the **same array**. 

One way to achieve this is to use the fact that all elements in the array are distinct and in the range from `0` to `nums.length - 1`.

We can **encode** two numbers in one position by leveraging the **size of the array**. Specifically, we can store the new value in a way that it can be extracted later without losing the original value. Here is the step-by-step approach:

**Encoding Two Values:**

For each index `i`, we want to store both `nums[i]` and `nums[nums[i]]` in `nums[i]`. We can encode the new value `nums[nums[i]]` and the original value `nums[i]` using the formula:

```
nums[i] = nums[i] + (nums[nums[i]] % n) * n;
```

This works under certain conditions:

* Array Length: The array length `n` must be known and should be used consistently for both encoding and decoding.
* Value Range: The values in the array should be in the range `[0,n−1]` to ensure the encoding and decoding process works correctly.
{: .notice--warning}

Here, `n` is the length of the array. This ensures that the new value is stored in the higher bits while the original value is preserved.

**Decoding the New Values:**

After encoding all values, we need to extract the new values by dividing each element by n:

```
nums[i]=nums[i]/n
```
Here is the implementation of the above approach in C++:

```cpp
#include <vector>
using namespace std;

vector<int> buildArray(vector<int>& nums) {
    int n = nums.size();

    // First pass: Encode two values into each element
    for (int i = 0; i < n; ++i) {
        nums[i] = nums[i] + (nums[nums[i]] % n) * n;
    }

    // Second pass: Decode the new values
    for (int i = 0; i < n; ++i) {
        nums[i] = nums[i] / n;
    }

    return nums;
}

```
#### Concept
If you have an array of length `n` and an index `i`, using `i % n` ensures that the index wraps around within the bounds of the array. This works because the modulo operation ensures that the result is always within the range `[0, n-1]`.

**Example**

Let's say you have an array nums of length `n = 6` and you want to wrap around the index.

* If i = 7, then i % 6 = 1.
* If i = 13, then i % 6 = 1.
* If i = -1, then (i % n + n) % n = (-1 % 6 + 6) % 6 = 5.

Adding `n` when `i < 0` ensures that the result of the modulo operation is always non-negative. By adding `n` to the result before taking modulo `n` again, we ensure that the index wraps around correctly to a positive value within the range `[0, n-1]`.