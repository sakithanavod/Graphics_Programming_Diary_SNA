---
title: "Bitwise Operations"
excerpt_separator: "<!--more-->"
categories:
 - C++, Bitwise
tags:
 - C++
---
{% include mathJax.html %}

Bitwise operations are essential in low-level programming and manipulating data at the bit level. 

<!--more-->

**Table of Contents**
* TOC
{:toc}

# How to convert an integer to its binary format
## Using the `std::bitset` Class
The `std::bitset` class template provides a convenient way to convert integers to binary strings.

```cpp
#include <iostream>
#include <bitset>

int main() {
    int number = 42;
    std::bitset<8> binary(number);  // Convert to 8-bit binary representation
    std::cout << "Binary representation of " << number << " is " << binary << std::endl;

    return 0;
}
```

# Bitwise Must Know
## Significant bits
#### What is least significant bit (LSB).
The least significant bit (LSB) is the bit in a binary number that has the lowest value, or represents the smallest unit place in the number. It is the bit that is **farthest to the right** in the binary representation of the number.

Consider the binary number `1011`: **Position of LSB:** The rightmost bit (1 in this case)
{: .notice--success}

#### What is most significant bit (MSB).
The sign bit, also known as the most significant bit (MSB), is the bit in a binary number that indicates the **sign of the number in signed binary representations**. 

It is the **leftmost bit** in the binary representation of the number.

Consider an 8-bit binary number in two's complement representation:
* Positive Number Example:
    - Binary: `00001011` (11 in decimal)
    - MSB: `0` (indicating a positive number)

* Negative Number Example:
    - Binary: 11110101 (-11 in decimal)
    - MSB: `1` (indicating a negative number)


## One's complement
One's complement is a method for representing signed integers (positive or negative integers) in binary form. In one's complement, the negative of a number is formed by inverting all the bits of the number (i.e., changing all 1s to 0s and all 0s to 1s). This system is distinct from the more commonly used *two's complement* representation.

### Characteristics of One's Complement
1. *Bit Inversion:* To find the one's complement of a binary number, invert all the bits.
2. *Two Representations of Zero:* In one's complement, there are two representations of zero: positive zero (all bits are 0) and negative zero (all bits are 1).

*Example*

For an 8-bit binary number, let's look at how to represent the number `5` and its negative `-5`:
* Positive 5 in Binary:
```
00000101  (5 in binary)
```

* Negative 5 in One's Complement:
Invert all bits of `5`
```
11111010  (-5 in one's complement)
```

One's complement is an older method for representing signed integers by inverting all the bits of the number. While it is simpler in terms of bitwise operations, it is less commonly used today due to the complications arising from having **two representations of zero** and the general adoption of *two's complement* in modern computer systems. 
{: .notice--warning}

## Two's complement
Two's complement is the most commonly used method for **representing signed integers** in binary form in modern computer systems.

In two's complement, negative numbers are represented by **inverting all the bits of the positive number (one's complement)** and then adding **one** to the **least significant bit (LSB)**.

### Characteristics of Two's Complement
* **Unique Zero Representation:** Unlike one's complement, two's complement has a single representation for zero.

*Example*

For an 8-bit binary number, let's look at how to represent the number `5` and its negative `-5`:
* Positive 5 in Binary:
```
00000101  (5 in binary)
```

* Negative 5 in Two's Complement:
    - Step 1: Find the one's complement of `5`
   
    ```
    11111010  (Inverting all bits of 5)
    ```
    - Step 2: Add 1 to the one's complement
    
    ```
    11111010
    +      1
    --------
    11111011  (-5 in two's complement)
    ```

*Code sample*

```cpp
int number = 5;
int twosComplement = ~number + 1;  // Compute two's complement
```

# Basic Bitwise Operators
## Bitwise AND (`&`)
Operation: Performs a bit-by-bit AND operation.

```cpp
int a = 5;  // 0101 in binary
int b = 3;  // 0011 in binary
int c = a & b; // 0001 in binary, which is 1
```

## Bitwise OR (`|`)
Operation: Performs a bit-by-bit OR operation.

```cpp
int a = 5;  // 0101 in binary
int b = 3;  // 0011 in binary
int c = a | b; // 0111 in binary, which is 7
```

## Bitwise XOR (`^`)
Performs a bit-by-bit OR operation.

```cpp
int a = 5;  // 0101 in binary
int b = 3;  // 0011 in binary
int c = a | b; // 0111 in binary, which is 7
```

## Bitwise NOT (`~`)
Performs a bit-by-bit NOT operation (one's complement).

```cpp
int a = 5;  // 0101 in binary
int c = ~a; // 1010 in binary, which is -6 in two's complement representation
```

## Bitwise Left Shift (`<<`)
Shifts bits to the left, filling with **zeros**.

```cpp
int a = 5;  // 0101 in binary
int c = a << 1; // 1010 in binary, which is 10
```

## Bitwise Right Shift (`>>`)
Shifts bits to the right, filling with the *sign bit (for signed types)* or *zeros (for unsigned types)*.

When using the bitwise right shift operator (`>>`) in C++, the behavior differs between **signed and unsigned** integer types:

### Right Shift Operator for Unsigned Types
For unsigned integer types, the right shift operator shifts bits to the right and fills the leftmost bits with zeros. This is known as a *logical shift*.

```cpp
#include <iostream>

int main() {
    unsigned int x = 8; // Binary: 0000 1000
    unsigned int y = x >> 1; // Binary: 0000 0100, which is 4 in decimal

    std::cout << "Unsigned Right Shift: " << y << std::endl; // Outputs: 4
    return 0;
}
```

### Right Shift Operator for Signed Types
For signed integer types, the right shift operator can behave differently based on the implementation. Most modern C++ compilers implement an arithmetic shift for signed integers, which means the leftmost bits are filled with the **sign bit (the most significant bit)**, preserving the sign of the *original number*. This is known as a *sign-propagating shift*.

```cpp
#include <iostream>

int main() {
    int x = -8; // Binary: 1111 1000 (in two's complement)
    int y = x >> 1; // Binary: 1111 1100, which is -4 in decimal

    std::cout << "Signed Right Shift: " << y << std::endl; // Outputs: -4
    return 0;
}
```

# Bit Masks
A binary pattern used to select or manipulate specific *bits* within a byte or word.

## Common Operations
### Setting Bits: Uses Bitwise `|` (OR)
Changing the bit's value to 1

```cpp
int flags = 0x00; //hexadecimal representation of 0 in binary (0000 0000).
int mask = 0x01; // 0001 in binary (hexadecimal representation of 1 in binary (0000 0001).)

int mask2 = 0x02;   // 0000 0010 (sets the second bit)
int mask3 = 0x04;   // 0000 0100 (sets the third bit)

flags |= mask; // Sets the first bit
```

Performing the bitwise OR operation:

```
  0000 0000  (flags)
| 0000 0001  (mask)
-----------
  0000 0001  (result)
```
*The result is 0000 0001, which means the first bit is now set.*

### Clearing Bits: Uses Bitwise `&` and `~`(AND, NOT)
Changing the bit's value to 0

```cpp
int flags = 0xFF; // 1111 1111 in binary
int mask = 0x01; // 0001 in binary (0000 0001 binary)
flags &= ~mask; // Clears the first bit (~mask is 1111 1110)
```

Performing the bitwise AND operation:

```
  1111 1111  (flags)
& 1111 1110  (~mask)
-----------
  1111 1110  (result)
```

*The result is  1111 1110, which means the first bit is now cleared.*

### Toggling Bits:Uses Bitwise `^`(XOR)
Changing the bit's value to 0 to 1 or 1 to 0

```cpp
int flags = 0x01; // 0001 in binary
int mask = 0x01; // 0001 in binary
flags ^= mask; // Toggles the first bit
```
Performing the bitwise XOR operation:

```
  0000 0001  (flags)
^ 0000 0001  (mask)
-----------
  0000 0000  (result)
```

*The result is 0000 0000, which means the first bit is now toggled.*

### Checking Bits: Uses Bitwise `&` (AND)
Checks whether a specific bit (in this case, the first bit) is set or not

```cpp
int flags = 0x05; // 0101 in binary
int mask = 0x01; // 0001 in binary
bool isSet = (flags & mask) != 0; // Checks if the first bit is set
```
Performing the bitwise AND operation:

```
  0101 (flag)
& 0001 (mask)
------
  0001 (result)
```

*The result is 0001 in binary, which is 0x01 in hexadecimal or 1 in decimal.*

The expression `(flags & mask) != 0` checks if the result of the AND operation is not equal to zero. Since 0001 is not equal to 0, the expression evaluates to true.

# Advanced Bitwise Techniques

## Swapping Values
Using XOR

```cpp
int a = 5;
int b = 3;
a = a ^ b;
b = a ^ b;
a = a ^ b;
// Now a is 3 and b is 5
```

## Checking Power of Two
Using AND

```cpp
bool isPowerOfTwo(int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}
```

## Counting Set Bits (Hamming Weight)
Using Bitwise AND and Shift

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
```

## Reversing Bits
Using Shifts and Masks

```cpp
unsigned int reverseBits(unsigned int n) {
    unsigned int reversed = 0;
    for (int i = 0; i < 32; ++i) {
        if (n & (1 << i))
            reversed |= 1 << (31 - i);
    }
    return reversed;
}
```