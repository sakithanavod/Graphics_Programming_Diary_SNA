---
title: "More on Matrices #1"
date: 2024-11-10 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

This chapter considered matrices and geometric transforms in detail. Determinant of a Matrix, Geometric Interpretation of Determinant

<!--more-->

**Table of Contents**
* TOC
{:toc}


## Determinant of a Matrix
For **square matrices**, there is a special scalar called the *determinant* of the matrix.The determinant has many useful properties in linear algebra, and it also has interesting geometric interpretations.

### Determinants of 2 × 2 and 3 × 3 matrices
The determinant of a square matrix $$M$$ is denoted $$|M|$$ or, in some other books, as $$\text{det } M$$. The determinant of nonsquare matrix is undefined.

The determinant of a 2 × 2 matrix is given by:

$$
|M| =
\begin{vmatrix}
m_{11} & m_{12} \\
m_{21} & m_{22} \\
\end{vmatrix}
= m_{11} m_{22} - m_{12} m_{21}.
$$

Notice that when we write the determinant of a matrix, we replace the brackets with vertical lines.
{: .notice--success}

This equation can be remembered easier with the following diagram. Simply multiply entries along the diagonal and back-diagonal, then subtract the back-diagonal term from the diagonal term.

![Alt Text]({{ site.baseurl }}/assets/maths/math59.png)

Some examples help to clarify the simple calculation:

$$
\begin{vmatrix}
a & b \\
c & d \\
\end{vmatrix}
= ad - bc.
$$

The determinant of a 3 × 3 matrix is given by:

$$
\text{Determinant of a 3 × 3 matrix}
$$

$$
\begin{vmatrix}
m_{11} & m_{12} & m_{13} \\
m_{21} & m_{22} & m_{23} \\
m_{31} & m_{32} & m_{33} \\
\end{vmatrix}
$$

$$
\text{det}(M) = m_{11}(m_{22} m_{33} - m_{23} m_{32}) - m_{12}(m_{21} m_{33} - m_{23} m_{31}) + m_{13}(m_{21} m_{32} - m_{22} m_{31})
$$

Some examples help to clarify the simple calculation:

![Alt Text]({{ site.baseurl }}/assets/maths/math60.jpg)

### Minors and Cofactors
Before we can look at determinants in the general case, we need to introduce some other constructs: *minors and cofactors*

**The Minor**

Assume $$M$$ is a matrix with $$r$$ rows and $$c$$ columns. Consider the matrix obtained by deleting row $$i$$ and column $$j$$ from $$M$$.

This matrix will obviously have $$r - 1$$ rows and $$c - 1$$ columns. The determinant of this submatrix, denoted $$M_{ij}$$, is known as a minor of $$M$$.

For example, the minor $$M_{12}$$ is the **determinant** of the 2 × 2 matrix that is the result of deleting **row 1** and **column 2** from the 3 × 3 matrix $$M$$:

$$\textbf{A minor of a 3 × 3 matrix:}$$

$$
M = 
\begin{bmatrix}
-4 & -3 & 3 \\
0 & 2 & -2 \\
1 & 4 & -1 \\
\end{bmatrix}
\implies M_{12} = 
\begin{vmatrix}
0 & -2 \\
1 & -1 \\
\end{vmatrix}
= (0 \cdot -1) - (-2 \cdot 1) = 2.
$$

So the minor of $$M_{12}$$ is 2.

**The Cofactor**

The cofactor of a square matrix $$M$$ is a value associated with each element of the matrix. It is used to calculate the determinant of the matrix or its inverse. 

The cofactor takes into account the minor of an element, which is the **determinant of the submatrix** formed by removing the row and column of that element, and applies a **sign based** on the element’s position.

**Definition of a Cofactor:**

Given a square matrix $$M$$ with elements $$m_{ij}$$, the cofactor $$C_{ij}$$ of an element $$m_{ij}$$ is defined as:

$$
C_{ij} = (-1)^{i + j} \cdot M_{ij}
$$

Where:
- $$(-1)^{i + j}$$ is the sign associated with the position of the element $$m_{ij}$$. The sign alternates in a checkerboard pattern:
  - Positive $${+}$$ if $$i + j$$ is even.
  - Negative $${-}$$ if $$i + j$$ is odd.
- $$M_{ij}$$ is the minor of $$m_{ij}$$, which is the determinant of the submatrix formed by deleting the $$i$$th row and $$j$$th column of $$M$$.

$$\textbf{Calculating a Cofactor:}$$
To compute the cofactor $$C_{ij}$$ of an element $$m_{ij}$$:
1. **Form the Submatrix:** Remove the $$i$$th row and $$j$$th column from $$M$$ to form the submatrix $$M_{ij}$$.
2. **Compute the Minor $$M_{ij}$$:** Calculate the determinant of the submatrix $$M_{ij}$$.
3. **Apply the Sign:** Multiply the minor by $$(-1)^{i + j}$$ to get the cofactor $$C_{ij}$$.

$$\textbf{Example:}$$
Given a 3×3 matrix:

$$
M = 
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9 \\
\end{bmatrix}
$$

Let's calculate the cofactor $$C_{12}$$ (the cofactor of the element in the first row, second column, which is $$m_{12} = 2$$):

1. **Form the Submatrix by removing the first row and second column:**
$$
M_{12} = 
\begin{bmatrix}
4 & 6 \\
7 & 9 \\
\end{bmatrix}
$$
2. **Compute the Minor:**
$$
M_{12} = \det \begin{bmatrix}
4 & 6 \\
7 & 9 \\
\end{bmatrix} = (4 \cdot 9) - (6 \cdot 7) = 36 - 42 = -6
$$
3. **Apply the Sign:**

$$
C_{12} = (-1)^{1 + 2} \cdot (-6) = (-1)^3 \cdot (-6) = -1 \cdot (-6) = 6
$$

So, the cofactor $$C_{12}$$ is 6.

**Sign Pattern for Cofactors:**

The sign pattern $$(-1)^{i + j}$$ for a 3×3 matrix looks like this:

$$
\begin{bmatrix}
+ & - & + \\
- & + & - \\
+ & - & + \\
\end{bmatrix}
$$

This pattern indicates that the cofactor's sign alternates in a checkerboard manner, starting with a positive sign at the top left.

### Determinants of Arbitrary $${n × n}$$ Matrices
Calculating the determinant of an arbitrary $$n \times n$$ matrix is a more complex process compared to $$2 \times 2$$ or $$3 \times 3$$ matrices, as the number of terms increases significantly with the size of the matrix. Here’s how to approach the computation:

**General Definition of the Determinant for an $$n \times n$$  Matrix:**

Given an $$n \times n$$ matrix $$M$$ with elements $$m_{ij}$$, the determinant $$\text{det}(M)$$ can be computed recursively using cofactor expansion (also known as Laplace expansion). 

The expansion can be done along any row or column, but it is typically done along the first row for simplicity.

$$\textbf{Determinant Formula:}$$

$$
\text{det}(M) = \sum_{j=1}^{n} (-1)^{1 + j} \cdot m_{1j} \cdot M_{1j}
$$

where:
- $$m_{1j}$$ are the elements of the first row.
- $$M_{1j}$$ are the minors of the corresponding elements in the first row.

**Steps to Calculate the Determinant of an $$n \times n$$ Matrix:**

1. **Choose a Row or Column:**
   It is often beneficial to choose a row or column that contains the most zeros, as this reduces the number of terms in the expansion.
2. **Form Submatrices:**
   For each element $$m_{ij}$$ in the chosen row or column, create a submatrix by removing the row and column containing $$m_{ij}$$.
3. **Calculate the Minor:**
   Compute the determinant of each submatrix recursively.
4. **Apply the Sign Factor:**
   Multiply each minor by $$(-1)^{i + j}$$ and the corresponding matrix element $$m_{ij}$$.
5. **Sum the Results:**
   Add the signed terms to get the determinant.

**Example Calculation for a $$4 \times 4$$ Matrix:**

Given a $$4 \times 4$$ matrix:

$$
M =
\begin{bmatrix}
1 & 2 & 3 & 4 \\
5 & 6 & 7 & 8 \\
9 & 10 & 11 & 12 \\
13 & 14 & 15 & 16 \\
\end{bmatrix}
$$

Expand along the first row:

$$
\text{det}(M) =
1 \cdot \text{det}
\begin{bmatrix}
6 & 7 & 8 \\
10 & 11 & 12 \\
14 & 15 & 16 \\
\end{bmatrix}
- 2 \cdot \text{det}
\begin{bmatrix}
5 & 7 & 8 \\
9 & 11 & 12 \\
13 & 15 & 16 \\
\end{bmatrix}
+ 3 \cdot \text{det}
\begin{bmatrix}
5 & 6 & 8 \\
9 & 10 & 12 \\
13 & 14 & 16 \\
\end{bmatrix}
- 4 \cdot \text{det}
\begin{bmatrix}
5 & 6 & 7 \\
9 & 10 & 11 \\
13 & 14 & 15 \\
\end{bmatrix}
$$

Calculate each $$3 \times 3$$ determinant recursively using the method described earlier.

#### Computational Complexity:

The computational complexity of finding the determinant using cofactor expansion is $$O(n!)$$ in the worst case, which becomes impractical for large matrices.

For matrices larger than $$3 \times 3$$, more efficient algorithms like LU decomposition, Gaussian elimination, or the Bareiss algorithm are used, reducing the time complexity to $$O(n^3)$$.

### Determinant Properties for $$n \times n$$ Matrices:

#### Linearity: 
The determinant is linear in each row and column.

#### Determinant of an Identity Matrix: 
$$
\text{det}(I) = 1,
$$
where $$I$$ is the identity matrix.

#### Row Operations:

* Swapping two rows or columns negates the determinant.
* Multiplying a row or column by a scalar $${c}$$ multiplies the determinant by $${c}$$
* Adding a multiple of one row to another does not change the determinant.

#### Singularity:

A matrix with $$\text{det}(M) = 0$$ is singular, meaning it does not have an **inverse.** - (we will talk about this in next section)

#### Multiplicative Property:

For any two $$n \times n$$ matrices $$A$$ and $$B$$, 

$$
\text{det}(AB) = \text{det}(A) \cdot \text{det}(B).
$$

#### The determinant of the transpose of a matrix

The determinant of the transpose of a matrix is equal to the determinant of the original matrix. Mathematically, for any $$n \times n$$ matrix $$M$$, this property is expressed as:

$$
\text{det}(M^T) = \text{det}(M).
$$

#### If any row or column in a matrix contains all 0s

If **any** row or column in a matrix contains **all zeros**, then the determinant of that matrix is 0. This is a fundamental property of determinants and is crucial for understanding when a matrix is **singular (i.e., non-invertible).**

### Geometric Interpretation of Determinant
The geometric interpretation of the determinant provides insight into how a matrix transformation (when we apply a matrix transformation to a space) affects the space it acts upon.

Remember! applying a matrix means applying it the current coordinate space (which might contains shapes and 3D objects). Ultimately applying a matrix modifies the **coordinate space** hence it automatically modifies the shapes and objects which are already withing the coordinate space.
{: .notice--warning}

#### Area and Volume Scaling:

**For 2D**

For a 2D matrix ($$2 \times 2$$), the absolute value of the determinant represents the scaling factor of the **area of a shape** (e.g., a parallelogram) when transformed by the matrix.

![Alt Text]({{ site.baseurl }}/assets/maths/math60.png)

**Example if determinant of M = 6**

if the absolute value of the determinant as means that If you apply this transformation to a shape (e.g., a unit square), the area of the transformed shape will be scaled by a factor of 6. 

For example, if the original shape has an area of 1 unit, the new area after applying $$M$$ will be 6 units.

**For 3D**

For a 3D matrix ($$3 \times 3$$), the absolute value of the determinant represents the scaling factor of the volume of a shape (e.g., a parallelepiped) when transformed by the matrix.

If the determinant is 1, the transformation preserves the area or volume (i.e., it does not scale it).
{: .notice--primary}

If the determinant is greater than 1, the transformation scales the space up by that factor.
{: .notice--primary}

If the determinant is less than 1 but greater than 0, the transformation scales the space down by that factor.
{: .notice--primary}

#### Orientation

The sign of the determinant indicates whether the transformation preserves or reverses the orientation of the space.

* **A positive determinant** means that the transformation preserves the original orientation of the space.
* **A negative determinant** means that the transformation reverses the orientation (e.g., reflection).

#### Zero Determinant

If the determinant is zero, the transformation collapses the space into a lower dimension (e.g., mapping a 2D plane into a line or a 3D space into a plane - which we say that matrix contains a projection). This indicates that the matrix is **singular** and **non-invertible.**

#### Examples

1. Scaling:
A matrix $$M = \begin{bmatrix} 2 & 0 \\ 0 & 3 \\ \end{bmatrix}$$ scales space by 2 in the $$x$$-direction and by 3 in the $$y$$-direction.
$$
\text{det}(M) = 2 \cdot 3 = 6,
$$
so the area of any shape is scaled by a factor of 6.
2. Rotation:
A rotation matrix 
$$
M = \begin{bmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) & \cos(\theta) \\ \end{bmatrix}
$$ 
has 
$$
\text{det}(M) = 1,
$$ 
indicating that rotation preserves the area and orientation of the space.
3. Reflection:
A reflection matrix 
$$
M = \begin{bmatrix} -1 & 0 \\ 0 & 1 \\ \end{bmatrix}
$$ 
has 
$$
\text{det}(M) = -1,
$$ 
indicating that the transformation preserves the area but reverses the orientation (flips the shape).