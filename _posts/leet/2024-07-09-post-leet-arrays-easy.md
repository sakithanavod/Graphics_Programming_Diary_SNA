---
title: "Leet Code Cheat Sheet"
excerpt_separator: "<!--more-->"
categories:
 - LeetCode 
tags:
 - Leet
---

Leet Code Cheat Sheet

<!--more-->

## Two Pointer Approach
The two-pointer approach is a common algorithmic technique used for solving problems that involve searching or processing elements in arrays or lists.

This technique uses two pointers (or indices) to traverse the data structure, often from different directions or at different speeds.

Key Features of the Two-Pointer Approach:

1. **Efficiency:** It often reduces the time complexity of problems, particularly those involving searching, sorting, or comparing elements in arrays or lists.
2. **Simplicity:** It provides a straightforward way to implement certain algorithms that would be more complex using other methods.
3. **Versatility:** It can be applied to a variety of problems, including those involving two sorted arrays, linked lists, and even strings.

### Common Scenarios for Using the Two-Pointer Approach:

#### Merging Two Sorted Arrays:
the two-pointer technique can efficiently merge two sorted arrays into one sorted array by comparing elements from the end or the beginning of the arrays.

#### Finding Pairs with a Given Sum:
When given a sorted array, you can use two pointers to find pairs of elements that add up to a specific target sum. One pointer starts at the beginning and the other at the end, moving inward until the pair is found.

#### Removing Duplicates from a Sorted Array:
One pointer can traverse the array, while another pointer keeps track of the position for placing unique elements.

#### Reversing a Substring
Two pointers can be used to reverse elements in a substring or subarray by swapping elements from both ends moving towards the center.

### Example Problem: Finding Pairs with a Given Sum

```cpp
#include <iostream>
#include <vector>

using namespace std;

void findPairsWithSum(const vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];

        if (sum == target) {
            cout << "(" << nums[left] << ", " << nums[right] << ")" << endl;
            left++;
            right--;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 10;
    
    findPairsWithSum(nums, target);
    
    return 0;
}

```

## Boyer-Moore Voting Algorithm (For finding the majority element in an array)
The Boyer-Moore Voting Algorithm is a popular algorithm for finding the **majority element** in an array. The majority element is defined as the element that appears more than `[n / 2]` times in the array. The algorithm works in linear time `O(n)` and uses constant space `O(1)`, making it very efficient.

**Steps of the Boyer-Moore Voting Algorithm**

1. **Initialization:** Start with an empty candidate and a counter set to zero.
2. **Traversal:**
    * Iterate through the array.
    * For each element:
        * If the counter is zero, set the current element as the candidate.
        * If the current element is the same as the candidate, increment the counter.
        * If the current element is different from the candidate, decrement the counter.
3. **Result:** After one complete pass through the array, the candidate will be the majority element.

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0];
        int count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};

// Example usage:
int main() {
    Solution solution;
    
    vector<int> nums1 = {3, 2, 3};
    int result1 = solution.majorityElement(nums1);
    // Output: 3
    cout << "Majority Element: " << result1 << endl;
    
    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    int result2 = solution.majorityElement(nums2);
    // Output: 2
    cout << "Majority Element: " << result2 << endl;

    return 0;
}

```

## Three-step reversal method

The three-step reversal method is a common technique for reversing a portion of an array or a string in-place. 

**Steps of three-step reversal method**

1. Reverse the entire array.
2. Reverse the first k elements
3. Reverse the remaining n-k elements

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Function to reverse a portion of the array
void reverseArray(std::vector<int>& arr, int start, int end) {
    while (start < end) {
        std::swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// Function to rotate the array to the right by k steps
void rotateArray(std::vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n; // To handle cases where k > n

    // Step 1: Reverse the entire array
    reverseArray(arr, 0, n - 1);

    // Step 2: Reverse the first k elements
    reverseArray(arr, 0, k - 1);

    // Step 3: Reverse the remaining n-k elements
    reverseArray(arr, k, n - 1);
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    rotateArray(arr, k);

    std::cout << "Rotated array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
