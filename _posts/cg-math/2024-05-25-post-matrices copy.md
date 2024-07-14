---
title: "Introduction to Matrices"
date: 2024-05-25 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

Matrices are of fundamental importance in 3D math, where they are primarily used to describe the relationship between two coordinate spaces.They do this by defining a computation to transform vectors from one coordinate space to another.

<!--more-->

## Mathematical Definition of Matrix
In linear algebra, a matrix is a rectangular grid of numbers arranged into rows and columns.

So a vector is an array of scalars, and a matrix is an array of vectors.
{: .notice--success}

Therefore, a **vector** can be considered a matrix with one row or one column.
{: .notice--primary}

### Matrix Dimensions and Notation
we will define the size of a matrix by counting how many rows and columns it contains. We say that a matrix with r rows and c columns
is an r × c (read “r by c”) matrix.

For example, a 4 × 3 matrix has 4 rows and 3 columns:

![Alt Text]({{ site.baseurl }}/assets/maths/math39.png)

### Diagonal Matrix
If all nondiagonal elements in a matrix are zero, then the matrix is a diagonal matrix. The following 4 × 4 matrix is diagonal:

![Alt Text]({{ site.baseurl }}/assets/maths/math42.png)

### Identity Matrix
A special diagonal matrix is the *identity matrix*. The identity matrix of dimension n, denoted $$I_\text{n}$$, is the n × n matrix with 1s on the diagonal and 0s elsewhere. For example, the 3 × 3 identity matrix is:

![Alt Text]({{ site.baseurl }}/assets/maths/math40.png)

### Matrix Transposition
Given an $${r × c}$$ matrix $${M}$$, the transpose of $${M}$$, denoted $${M^T}$$, is the  $${c × r}$$ matrix where the columns are formed from the rows of $${M}$$.

![Alt Text]({{ site.baseurl }}/assets/maths/math41.png)

Any diagonal matrix $${D}$$ is equal to its transpose: $${D^T}$$ = $${D}$$. This includes the identity matrix $${I}$$.
{: .notice--success}

## Multiplying Two Matrices
An $${r × n}$$ matrix $${A}$$ may be multiplied by an $${n × c}$$ matrix $${B}$$. The result, denoted $${AB}$$, is an $${r × c}$$ matrix.

Note that, in order to multiply two matrices number of *columns* in $${A}$$ which is $${n}$$ should match the number of *rows* in $${B}$$ which is also $${n}$$, otherwise the multiplication $${AB}$$ is not defined
{: .notice--warning}

![Alt Text]({{ site.baseurl }}/assets/maths/math43.png)

### Important Matrix Multiplication Notes

* Matrix multiplication is not commutative. In general:

$${AB} \neq {BA}$$

* Matrix multiplication is associative:

$${(AB)C} = {A(BC)}$$

* Transposing the product of two matrices is the same as taking the product of their transposes in reverse order:

$${(AB)^T} = {B^TA^T}$$

## Row versus Column Vectors

Let's say we have vector: 

$${V} = ({x}, {y}, {z})$$

Then Row major vector is,

$$\begin{bmatrix} x & y & z \end{bmatrix}$$

Then Column major vector is,

$$\begin{bmatrix}x \\y \\z\end{bmatrix}$$

What are the differences between these two?
* For example, if we wish to transform a vector **v (row vector)** by the matrices A, B, and C, in that order
we write as:
  
  $${vABC}$$

  with the matrices listed in order of transformation from left to right. 

* If **column vectors** are used, then the vector is on the right, and so the transformations will occur in order from right to left. In this case, we would write:
  
  $${CBAv}$$

Note that,  
* DirectX use *row vectors*.
* OpenGL use *column vectors*.

## Geometric Interpretation of Matrix
### What actually a matrix represent in Geometric form?
A matrix represents a **coordinate space transformation** by describing how points, vectors, or geometric objects are transformed when subjected to specific operations.

Multiplying points or vectors by the transformation matrix applies the corresponding transformation to them, resulting in a change in their position, direction, or size within the coordinate space.

### What is a linear transformation?
A linear transformation is a mathematical operation that maps vectors from **one vector** space to **another** in a way that preserves certain properties. In simpler terms, 

it's a transformation that maintains the structure of vector addition and scalar multiplication.
{: .notice--success}

a linear transformation preserves straight and parallel lines, and that there is no translation—that is, the origin does not move
{: .notice--success}

#### Matrix Representation
Linear transformations can often be represented by matrices. Each linear transformation corresponds to a **unique matrix**, and vice versa. When a linear transformation is represented by a matrix, applying the transformation to a vector is simply done by **matrix-vector multiplication**. and finally we call this as transformation matrix.

What does transformation matrix represents?
* The transformation matrix represents how each of these original basis vectors is transformed under the linear transformation.
* Each row (if its column major then its the column) of the transformation matrix corresponds to the transformed version of one of the original **basis vectors**.

![Alt Text]({{ site.baseurl }}/assets/maths/math45.png)

Examples of linear transformations
* Rotation - A rotation in a plane or in three-dimensional space is a linear transformation because it preserves the lengths of vectors and the angles between them.
* Scale - Uniform scaling (scaling by the same factor along each coordinate axis) is a linear transformation.
* Orthographic projection - Certain types of projections, such as orthogonal projection onto a line or plane, are linear transformations.
* Shearing - Certain types of shearing transformations, such as horizontal or vertical shearing, are linear transformations.

This is what basically happening when we do this:

![Alt Text]({{ site.baseurl }}/assets/maths/math44.png)

Let's take a look at another example:

Examine the following 2 × 2 matrix

$${M} = \begin{bmatrix} 2 & 1 \\  -1 & 2 \end{bmatrix}$$

What sort of transformation does this matrix represent? First, let’s extract the basis vectors p and q (basis vectors) from the rows of the matrix:

$${p} = \begin{bmatrix} 2 & 1 \end{bmatrix}$$

$${q} = \begin{bmatrix} -1 & 2 \end{bmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math46.png)

the +x basis vector is transformed into the vector labeled p above, and the y basis vector is transformed into the vector labeled q.

In this example, we can easily see that part of the transformation represented by matrix M is a counterclockwise rotation of approximately $$26.5^{\circ}$$ and it also scales it.
{: .notice--primary}

By interpreting the rows of a matrix as basis vectors, we have a tool for *deconstructing a matrix*. But we also have a tool for *constructing one!* Given a desired transformation (i.e., rotation, scale, and so on), we can derive a matrix that represents that transformation.

How do we do this? It's easy just figure out what the transformation does to the *basis vectors* and then place those transformed basis vectors into the **rows of a matrix**.

### Example: Rotation in 2D Space
Let's say we want to construct a transformation matrix for a $$90^{\circ}$$ counterclockwise rotation in 2D space. 

A $$90^{\circ}$$ counterclockwise rotation in 2D space transforms the x-axis unit vector [1,0] to 
[0,1], and it transforms the y-axis unit vector [0,1] to [-1,0].

We place the transformed basis vectors into the rows of the matrix.

$$T_{\text{rotate}} = \begin{bmatrix} 0 & 1 \\  -1 & 0 \end{bmatrix}$$

## Exercises

[Download Exercises]({{ site.baseurl }}/assets/exercises/maths/Ex_02/Matrix - Exercises.pdf){:target="_blank"}

[Download Answers]({{ site.baseurl }}/assets/exercises/maths/Ex_02/Matrix - Answers.pdf){:target="_blank"}