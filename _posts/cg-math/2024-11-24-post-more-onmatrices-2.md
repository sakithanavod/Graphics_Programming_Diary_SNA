---
title: "More on Matrices #2"
date: 2024-11-24 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

More on to Matrices : Inverse of a Matrix, Orthogonal Matrices, 4×4 Homogeneous Matrices

<!--more-->

**Table of Contents**
* TOC
{:toc}


## Inverse of a Matrix
Another important operation that applies only to square matrices is the inverse of a matrix. This section discusses the matrix inverse from a mathematical and geometric perspective.

The inverse of a matrix $$M$$ is a matrix $$M^{-1}$$ such that when it is multiplied by $$M$$, it results in the identity matrix $$I$$. Mathematically, this is represented as:

$$
M \cdot M^{-1} = M^{-1} \cdot M = I
$$

### Conditions for Inverses
A matrix $$M$$ has an inverse if:

- It is square (i.e., it has the same number of rows and columns).
- The determinant of $$M$$ is non-zero ($$\text{det}(M) \neq 0$$).

If a matrix has an inverse, it is said to be *invertible* or *nonsingular*. A matrix that **does not** have an inverse is said to be *noninvertible* or *singular*
{: .notice--success}

A zero determinant indicates that the rows (or columns) form a set of linearly dependant vectors. exampe: $$2x + 3y = 5$$ and $$4x + 6y = 10$$ second equation is the multiplication of first one by 2
{: .notice--warning}


### Properties of Inverse Matrices

**Uniqueness of Solutions in Linear Systems**

Imagine you have a system of linear equations like this:

$$
M \mathbf{x} = \mathbf{b}
$$

where:

- $$M$$ is a matrix representing the **coefficients** of the equations.
- $$\mathbf{x}$$ is the vector(example [x y]) of unknowns (the solution we are trying to find).
- $$\mathbf{b}$$ is the result **vector** (the constants on the right side of the equation).

Side note on coefficients:

![Alt Text]({{ site.baseurl }}/assets/maths/math61.png)

**What Does "Uniqueness of Solutions" Mean?**

When we say a system has a unique solution, it means that there is **only one set of values** for the unknowns x that satisfies all the equations at the same time.

![Alt Text]({{ site.baseurl }}/assets/maths/math62.png)

Note that this point represents the unique solution to the system of equations. Which means both linear equations **only** intersects at this point.
{: .notice--success}

Note that there could be linear equations that never intersects (No Solution), or could have infinite intersection points.
{: .notice--warning}

**Role of an Invertible Matrix:**

If the matrix $$M$$ is invertible (i.e., it has an inverse $$M^{-1}$$), then the system $$M \mathbf{x} = \mathbf{b}$$ has a **unique solution.**

The solution can be found by multiplying both sides of the equation by $$M^{-1}$$:

$$
\mathbf{x} = M^{-1} \mathbf{b}
$$

This tells us that for any given $$\mathbf{b}$$, there is exactly one $$\mathbf{x}$$ that satisfies the equation.

#### Invertible Matrix and Vector Equality
For any invertible matrix $$M$$, if you have a vector equation $$\mathbf{v} M = 0$$, this equation is only true when $$\mathbf{v}$$ is the zero vector (i.e., $$\mathbf{v} = 0$$).

This property implies that if $$M$$ has an inverse ($$M^{-1}$$), the only solution to $$\mathbf{v} M = 0$$ is the trivial solution $$\mathbf{v} = 0$$.

Why is this true?

If $$\mathbf{v} M = 0$$ and $$M$$ is invertible, we can multiply both sides by $$M^{-1}$$:

$$
\mathbf{v} M \cdot M^{-1} = 0 \cdot M^{-1}
$$

Since $$M \cdot M^{-1} = I$$ (the identity matrix), this simplifies to:

$$
\mathbf{v} = 0
$$

This shows that the only solution is the zero vector.

#### Linear Independence of Rows and Columns in an Invertible Matrix

The rows and columns of an invertible matrix $$M$$ are linearly independent.

* Linear independence means that no row (or column) can be written as a linear combination of the other rows (or columns).
* This property is crucial because it ensures that the matrix transformation represented by $$M$$ maps vectors uniquely and maintains their dimensional integrity (i.e., it does not collapse the space).

Therefore, if $$M$$ matrix is invertible then the rows and columns of an invertible matrix $$M$$ are linearly independent
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/maths/math63.png)

#### Recap

**Determinant and Invertibility:**

If the determinant of a square matrix $$M$$ is non-zero ($$\text{det}(M) \neq 0$$), then:

- $$M$$ is invertible (has an inverse).
- The matrix represents a transformation that preserves the dimensionality of the space it acts upon.

**Linear Independence:**

If $$M$$ is invertible ($$\text{det}(M) \neq 0$$), its rows and columns are linearly independent.

- Linear independence means that no row or column can be expressed as a linear combination of the others, ensuring the matrix spans the full space.
- In the context of a 2D matrix, the equations represented by the rows or columns intersect at exactly one unique point, confirming a unique solution.

**Determinant of Zero and Linear Dependence**

If the determinant of a square matrix $$M$$ is zero ($$\text{det}(M) = 0$$), then:

- $$M$$ does not have an inverse, making it singular.
- The rows and columns of $$M$$ are linearly dependent, meaning at least one can be expressed as a linear combination of the others.

Geometrically, applying a transformation represented by such a matrix would collapse the space into a lower dimension (e.g., a 2D plane into a line or a 3D space into a plane). This collapse means that information is lost, and the transformation is not reversible.

3D graphics and other applications involving **linear transformations**, it's important to know whether a matrix is singular or invertible before applying certain operations.
{: .notice--warning}

If a matrix is singular (i.e., $$\text{det}(M) = 0$$), applying it in the context of transformations that require the matrix to be invertible is not appropriate and can be considered an invalid transformation in those cases. Due to **Loss of Dimensionality** and those transformations could not be **reversed.**
{: .notice--danger}

### Matrix Inverse—Official Linear Algebra Rules

To compute the inverse of a matrix, we divide the **classical adjoint by the determinant**: 

$$M^{-1} = \frac{\text{adj } M}{|M|}$$

#### Inverse of a  $$2 \times 2$$ Matrix

Given a matrix:
$$
M = \begin{bmatrix}
a & b \\
c & d \\
\end{bmatrix},
$$

the inverse $$M^{-1}$$ is given by:
$$
M^{-1} = \frac{1}{\text{det}(M)} \cdot \text{adj}(M),
$$

where: $$\text{det}(M) = ad - bc$$ is the determinant of the matrix.

The adjoint matrix $$\text{adj}(M)$$ for a $$2 \times 2$$ matrix is:

$$
\text{adj}(M) = \begin{bmatrix}
d & -b \\
-c & a \\
\end{bmatrix}.
$$

Putting it together, the inverse can be expressed as:

$$
M^{-1} = \frac{1}{ad - bc} \begin{bmatrix}
d & -b \\
-c & a \\
\end{bmatrix}.
$$

You can calculate cofactor matrix then transpose the cofactor matrix to get the adjugate matrix
{: .notice--success}

#### Inverse of a $$3 \times 3$$ Matrix

Given:

$$
M = \begin{bmatrix}
a & b & c \\
d & e & f \\
g & h & i \\
\end{bmatrix}
$$

Steps:

1. Calculate the determinant $$\text{det}(M)$$. If $$\text{det}(M) = 0$$, the matrix does not have an inverse.
2. Find the cofactor matrix by computing the cofactor for each element.
3. Transpose the cofactor matrix to get the adjugate matrix $$\text{adj}(M)$$.
4. Divide the adjugate matrix by $$\text{det}(M)$$ to find the inverse:
$$
M^{-1} = \frac{1}{\text{det}(M)} \cdot \text{adj}(M)
$$

##### Example

Given:
$$
M = \begin{bmatrix}
1 & 2 & 3 \\
0 & 1 & 4 \\
5 & 6 & 0 \\
\end{bmatrix}
$$

**Calculate the determinant:**

$$
\text{det}(M) = 1 \cdot (1 \cdot 0 - 4 \cdot 6) - 2 \cdot (0 \cdot 0 - 4 \cdot 5) + 3 \cdot (0 \cdot 6 - 1 \cdot 5)
$$
$$
\text{det}(M) = 1 \cdot (-24) - 2 \cdot (-20) + 3 \cdot (-5)
$$
$$
\text{det}(M) = -24 + 40 - 15 = 1
$$

**Find the cofactor matrix:**

$$
C = \begin{bmatrix}
\text{det}\begin{bmatrix} 1 & 4 \\ 6 & 0 \end{bmatrix} & -\text{det}\begin{bmatrix} 0 & 4 \\ 5 & 0 \end{bmatrix} & \text{det}\begin{bmatrix} 0 & 1 \\ 5 & 6 \end{bmatrix} \\
-\text{det}\begin{bmatrix} 2 & 3 \\ 6 & 0 \end{bmatrix} & \text{det}\begin{bmatrix} 1 & 3 \\ 5 & 0 \end{bmatrix} & -\text{det}\begin{bmatrix} 1 & 2 \\ 5 & 6 \end{bmatrix} \\
\text{det}\begin{bmatrix} 2 & 3 \\ 1 & 4 \end{bmatrix} & -\text{det}\begin{bmatrix} 1 & 3 \\ 0 & 4 \end{bmatrix} & \text{det}\begin{bmatrix} 1 & 2 \\ 0 & 1 \end{bmatrix} \\
\end{bmatrix}
$$

**Transpose $$C$$ to get $$\text{adj}(M)$$.**

**Divide $$\text{adj}(M)$$ by $$\text{det}(M)$$ to get $$M^{-1}$$:**

$$
M^{-1} = \frac{1}{1} \cdot \text{adj}(M)
$$

##### General Method for Larger Matrices:
For matrices larger than  $$3 \times 3$$, use methods like *Gaussian elimination*, *LU decomposition*, or specialized software libraries (e.g., NumPy in Python or GLM in C++ for graphics programming) to compute the inverse.

#### Important properties concerning matrix inverses

**Inverse of the Inverse:** 
$$(M^{-1})^{-1} = M$$

* If $$M$$ is nonsingular (invertible), then taking the inverse of $$M^{-1}$$ results in the original matrix $$M$$.

**Identity Matrix:** 
$$I^{-1} = I$$

* The identity matrix is its own inverse. Any square matrix $$I$$ with ones on the diagonal and zeros elsewhere satisfies this property. Other matrices that are their own inverses include reflection matrices and rotation matrices that rotate by 180° about any axis.

**Inverse of the Transpose:** 
$$(M^T)^{-1} = (M^{-1})^T$$

* The inverse of the transpose of a matrix is equal to the transpose of the inverse of the matrix. This property is useful when working with coordinate transformations and rotations in computer graphics.

**Inverse of a Matrix Product:** 
$$(AB)^{-1} = B^{-1} A^{-1}$$

* The inverse of a product of two matrices is the product of the inverses of the matrices, but taken in reverse order. This property extends to more than two matrices:
$$(M_1 M_2 \cdots M_{n-1} M_n)^{-1} = M_n^{-1} M_{n-1}^{-1} \cdots M_2^{-1} M_1^{-1}$$

**Determinant of the Inverse:** 
$$|M^{-1}| = \frac{1}{|M|}$$

* The determinant of the inverse of a matrix is the reciprocal of the determinant of the original matrix. This implies that if $$\text{det}(M) \neq 0$$, then $$M$$ is invertible, and the determinant of $$M^{-1}$$ will be a non-zero value.

### Matrix Inverse—Geometric Interpretation 
The geometric interpretation of the inverse of a matrix is that it effectively reverses the transformation applied by the original matrix. 

When you transform a vector $$v$$ using a matrix $$M$$, you change the vector’s coordinates in some way—scaling, rotating, translating, etc., depending on the properties of $$M$$. 

Applying the inverse matrix $$M^{-1}$$ to this transformed vector undoes these changes, returning the vector to its original state.

Key Points:

1. **Undoing Transformations:** If $$M$$ represents a transformation (e.g., rotation, scaling, or shearing), then $$M^{-1}$$ represents a transformation that reverses the effect of $$M$$.
2. **Sequence Verification:** Algebraically, the property $$(vM)M^{-1} = v$$ holds because $$M \times M^{-1}$$ is the identity matrix $$I$$, which does not change the vector:
$$
v(MM^{-1}) = vI = v.
$$

**Geometric Example**

- Rotation: If $$M$$ rotates vectors by $$\theta$$ degrees, then $$M^{-1}$$ rotates them by $$-\theta$$ degrees.
- Scaling: If $$M$$ scales vectors by a factor $$k$$, then $$M^{-1}$$ scales them by $$\frac{1}{k}$$.

**Applications:** This property is crucial in various applications, such as solving systems of linear equations, computer graphics (to reverse transformations or compute object positions), and robotics (for reversing movements).

## Orthogonal Matrices

### Orthogonal Matrices—Official Linear Algebra Rules

An orthogonal matrix $$Q$$ is a square matrix whose rows and columns are **orthonormal vectors.** Mathematically, $$Q$$ satisfies the following condition:
$$
Q^T Q = Q Q^T = I,
$$
where $$Q^T$$ is the transpose of $$Q$$, and $$I$$ is the identity matrix.

**Properties of Orthogonal Matrices:**
1. **Inverse:** The inverse of an orthogonal matrix is its transpose:
$$
Q^{-1} = Q^T.
$$
2. **Determinant:** The determinant of an orthogonal matrix is either $$+1$$ or $$-1$$.
3. **Preservation of Norms:** Orthogonal matrices preserve the length (norm) of vectors. If $$v$$ is a vector, then:
$$
\|Qv\| = \|v\|.
$$

#### Examples

* Identity Matrix (2D)
$$
I = \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix}
$$

* Identity Matrix (3D)
$$
I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}
$$

* 2D Rotation Matrix
$$
R(\theta) = \begin{bmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) & \cos(\theta) \end{bmatrix}
$$

* 90-degree Rotation Matrix
$$
R(90^\circ) = \begin{bmatrix} 0 & -1 \\ 1 & 0 \end{bmatrix}
$$

* 3D Rotation Matrix (about the z-axis)
$$
R_z(\theta) = \begin{bmatrix} \cos(\theta) & -\sin(\theta) & 0 \\ \sin(\theta) & \cos(\theta) & 0 \\ 0 & 0 & 1 \end{bmatrix}
$$

* Reflection Matrix (across the x-axis)
$$
M = \begin{bmatrix} 1 & 0 \\ 0 & -1 \end{bmatrix}
$$

### Why this is important
One of the powerful properties of orthogonal matrices is that they simplify many computations due to their unique characteristics. Specifically:

**Inverse of an Orthogonal Matrix**

If \( Q \) is an orthogonal matrix, its inverse is simply its transpose:

$$
Q^{-1} = Q^{T}.
$$

**Why This Matters:**
* **Computational Efficiency:** Computing the inverse of a matrix can be computationally expensive, especially for large matrices. The standard methods for finding inverses (such as Gaussian elimination) involve complex calculations.
* **Orthogonal Matrices:** With orthogonal matrices, this computation is avoided because $$Q^{T}$$ is straightforward to calculate and significantly faster than calculating a general inverse.

Remember we need inverse of matrices often in computer graphics because we need to **Reversing Transformations** in some cases to return to the original coordinate space.
{: .notice--success}

### Orthogonal Matrices—Geometric Interpretation

#### Orthonormal vectors
Orthonormal vectors are vectors that are both **orthogonal** (perpendicular to each other) and **normalized** (having a magnitude, or length, of 1). Let's break down these two properties:

* **Orthogonal Vectors:**
Vectors are orthogonal if they are perpendicular to each other. Mathematically, two vectors $$u$$ and $$v$$ are orthogonal if their dot product is zero:
$$
u \cdot v = 0.
$$
This condition means there is a 90-degree angle between the vectors.

* **Normalized Vectors:**
A vector is normalized if it has a length (magnitude) of 1. To normalize a vector $$v$$, you divide it by its magnitude $$\|v\|$$:
$$
v_{\text{normalized}} = \frac{v}{\|v\|}.
$$

**Orthonormal Vectors**

Vectors are orthonormal if they meet both of these conditions: they are orthogonal to each other and each vector has a length of 1

Consider the following set of vectors in 2D:
$$
u_1 = \begin{bmatrix} 1 \\ 0 \end{bmatrix}, \quad u_2 = \begin{bmatrix} 0 \\ 1 \end{bmatrix}.
$$

These vectors are orthogonal because:
$$
u_1 \cdot u_2 = 1 \cdot 0 + 0 \cdot 1 = 0.
$$

They are also normalized because:
$$
\|u_1\| = 1 \quad \text{and} \quad \|u_2\| = 1.
$$

So, $$u_1$$ and $$u_2$$ form an orthonormal set.

For a matrix to be orthogonal, its rows and columns must consist of orthonormal vectors.

### Interpretation

* **Orthonormal Vectors:** 
Vectors that are both orthogonal (perpendicular to each other) and normalized (each vector has a length of 1).

* **Rows and Columns:** In an orthogonal matrix, each row and each column is an orthonormal vector. This means:
   - The dot product between any two different rows (or columns) is **0**, which confirms they are orthogonal.
   - The dot product of a row (or column) with itself is **1**, confirming it is normalized.

### Practical use

When dealing with matrices, we often take advantage of orthogonality if we already know a matrix is orthogonal. because
$$
Q^{-1} = Q^{T}.
$$

This operation is much simpler than using more complex matrix inversion algorithms.

But verifying if a matrix is orthogonal can be time-consuming. The process involves checking if:

$$
Q^T Q = Q Q^T = I,
$$

If we perform this check and find the matrix is orthogonal, we benefit from a faster inversion by simply transposing. However, if the matrix is not orthogonal, the time spent on checking becomes wasted, as we still need to compute the **inverse** through a standard method.

Also matrices represented in floating-point arithmetic may not be **perfectly orthogonal** due to numerical **precision errors**. Even if a matrix is theoretically orthogonal, its floating-point representation might have slight deviations.

Knowing that a matrix is orthogonal **in advance** is common in graphics, robotics, and simulations where certain transformations (e.g., rotations) are guaranteed to be orthogonal.

**Avoiding Checks:** In real-world applications, if a process or algorithm inherently produces orthogonal matrices (e.g., QR decomposition or generating rotation matrices), it’s more efficient to assume their orthogonality rather than re-checking it.
{: .notice--primary}

## Orthogonalizing a Matrix
It is sometimes the case that we encounter a matrix that is slightly out of orthogonality. We may have acquired bad data from an external source, or we may have accumulated floating point error (which is called *matrix creep*). For an example, basis vectors used for **bump mapping** (we will talk about this in later chapter)

we will often adjust the basis to be orthogonal, even if the texture mapping gradients aren’t **quite perpendicular.**

In these situations, we would like to **orthogonalize** the matrix, resulting in a matrix that has mutually perpendicular unit vector axes and is (hopefully) as close to the original matrix as possible.

### Gram-Schmidt orthogonalization
The standard algorithm for constructing a set of orthogonal basis vectors (which is what the rows of an orthogonal matrix are).

The basic idea is to go through the basis vectors in order. For each basis vector, we subtract off the portion of that vector that is parallel to the proceeding basis vectors, which must result in a
perpendicular vector.

Here's how the process works for a $$3 \times 3$$ matrix:

Given a $$3 \times 3$$ matrix $${A}$$ with row vectors $${\mathbf{v}_1, \mathbf{v}_2, \mathbf{v}_3}$$:

$$
{A} = \begin{bmatrix} \mathbf{v}_1 \\ \mathbf{v}_2 \\ \mathbf{v}_3 \end{bmatrix},
$$

the goal is to find an orthogonal matrix $${Q}$$ with orthonormal row vectors $${\mathbf{u}_1, \mathbf{u}_2, \mathbf{u}_3}$$.

**Step 01: Start with the First Vector**

Set $${\mathbf{u}_1}$$ as a normalized version of $${\mathbf{v}_1}$$:

$$
\mathbf{u}_1 = \frac{\mathbf{v}_1}{\|\mathbf{v}_1\|}.
$$

**Step 02: Orthogonalize the Second Vector $${v_2}$$**

**Project $${\mathbf{v}_2}$$ onto $${\mathbf{u}_1}$$.**

The projection of $${\mathbf{v}_2}$$ onto $${\mathbf{u}_1}$$ is defined as: (from dot product - if you don't remember check the section)

$$
\text{proj}_{\mathbf{u}_1}(\mathbf{v}_2) = \left( \frac{\mathbf{v}_2 \cdot \mathbf{u}_1}{\mathbf{u}_1 \cdot \mathbf{u}_1} \right) \mathbf{u}_1.
$$

Since $${\mathbf{u}_1}$$ is already normalized ($$\|\mathbf{u}_1\| = 1$$), this simplifies to:

$$
\text{proj}_{\mathbf{u}_1}(\mathbf{v}_2) = (\mathbf{v}_2 \cdot \mathbf{u}_1) \mathbf{u}_1.
$$

**Subtract the projection from $${\mathbf{v}_2}$$ to make it orthogonal to $${\mathbf{u}_1}$$:**

Compute $${\mathbf{u}_2}$$ by removing the component of $${\mathbf{v}_2}$$ that is parallel to $${\mathbf{u}_1}$$: 

because $$v_2 = v_2(perpendicular) + v_2(parallel)$$

$$
\mathbf{u}_2 = \mathbf{v}_2 - \text{proj}_{\mathbf{u}_1}(\mathbf{v}_2).
$$

Then normalize $${\mathbf{u}_2}$$:

$$
\mathbf{u}_2 = \frac{\mathbf{u}_2}{\|\mathbf{u}_2\|}.
$$

**Step 03: Orthogonalize the Third Vector $${v_3}$$**
​
Project $${\mathbf{v}_3}$$ onto $${\mathbf{u}_1}$$ and $${\mathbf{u}_2}$$.

Compute the projections of $${\mathbf{v}_3}$$ onto both $${\mathbf{u}_1}$$ and $${\mathbf{u}_2}$$:

$$
\text{proj}_{\mathbf{u}_1}(\mathbf{v}_3) = (\mathbf{v}_3 \cdot \mathbf{u}_1) \mathbf{u}_1,
$$
$$
\text{proj}_{\mathbf{u}_2}(\mathbf{v}_3) = (\mathbf{v}_3 \cdot \mathbf{u}_2) \mathbf{u}_2.
$$

Subtract these projections from $${\mathbf{v}_3}$$ to make it orthogonal to both $${\mathbf{u}_1}$$ and $${\mathbf{u}_2}$$.

Compute $${\mathbf{u}_3}$$:

$$
\mathbf{u}_3 = \mathbf{v}_3 - \text{proj}_{\mathbf{u}_1}(\mathbf{v}_3) - \text{proj}_{\mathbf{u}_2}(\mathbf{v}_3).
$$

Normalize $${\mathbf{u}_3}$$.

$$
\mathbf{u}_3 = \frac{\mathbf{u}_3}{\|\mathbf{u}_3\|}.
$$

Final Result

The resulting matrix $${Q}$$ with orthonormal rows is:

$$
Q = \begin{bmatrix} \mathbf{u}_1 \\ \mathbf{u}_2 \\ \mathbf{u}_3 \end{bmatrix}.
$$

## $$4 \times 4$$ Homogeneous Matrices
Up until now, we have used only 2D and 3D vectors. In this section, we introduce 4D vectors and the so-called “homogeneous” coordinate.

4D vectors and $$4 \times 4$$ matrices are nothing more than a notational convenience for what are simple 3D operations.
{: .notice--success}

Homogeneous coordinates extend conventional Cartesian coordinates by adding an extra dimension, allowing us to represent transformations (like translation, rotation, scaling, and perspective) in a 
unified way using matrices. These coordinates are extensively used in computer graphics for transformations in 2D and 3D space.

### Why Homogeneous Coordinates?
In conventional Cartesian coordinates, transformations such as scaling and rotation can already be represented as matrix multiplications.

However, **translation and perspective projections** cannot be represented directly in a simple matrix multiplication without adding an extra dimension.

#### Why Matrix Multiplication Fails
In Cartesian coordinates, a translation operation moves a point $$(x, y)$$ to a new position $$(x', y')$$ by adding a translation vector $$(t_x, t_y)$$:

$$
x' = x + t_x, \quad y' = y + t_y.
$$

Matrix multiplication in standard linear algebra involves **only scaling and combining dimensions** through weighted sums. However, translation requires **adding** a constant ($$t_x, t_y$$) independently to $${x}$$ and $${y}$$. 

A standard $$2 \times 2$$ or $$3 \times 3$$ matrix cannot add constants; it can only scale or rotate dimensions based on the input values.

### Homogeneous coordinates in 2D

In 2D space, a point is typically represented as:

$$
(x, y)
$$

To represent a 2D point in homogeneous coordinates, we add a third component:

$$
(x, y) \rightarrow (x, y, w)
$$

Here, $${w}$$ is the homogeneous component (or scale factor).

- If $${w = 1}$$, the point represents a standard Cartesian point: $$(x, y).$$
- If $${w \neq 1}$$, the Cartesian coordinates can be recovered by dividing $${x}$$ and $${y}$$ by $${w}$$:

Imagine the standard 2D plane as existing in 3D at the plane $$w = 1$$, such that a physical 2D point $$(x, y)$$ is represented in homogeneous space as $$(x, y, 1)$$.

For all points that are not in the plane $$w = 1$$, we can compute the corresponding 2D point by **projecting** the point onto the plane $$w = 1$$, by dividing by $${w}$$. 

Thus, the homogeneous coordinate $$(x, y, w)$$ is mapped to the physical 2D point:
$$
\left( \frac{x}{w}, \frac{y}{w} \right).
$$

![Alt Text]({{ site.baseurl }}/assets/maths/math64.png)

### Homogeneous coordinates in 3D

Just like in 2D we can define Homogeneous Coordinates in 3D as,

$$(x, y, z) \rightarrow (x, y, z, w)$$

Similar to 2D, $${w}$$ is the homogeneous component.

- If $${w = 1}$$, the point is a standard Cartesian point.
- If $${w \neq 1}$$, the Cartesian coordinates are recovered as:
$$
(x, y, z) = \left( \frac{x}{w}, \frac{y}{w}, \frac{z}{w} \right).
$$

### Homogeneous coordinates summery

**Linear Transformations (Non-Homogeneous Coordinates)**

Rotation, scaling, reflection, and shearing are linear transformations.  
They can be fully represented using standard non-homogeneous coordinates because they involve operations like scaling, rotating, or skewing, which are linear.

Example: A $$2 \times 2$$ or $$3 \times 3$$ matrix is enough to perform these transformations.

**Affine Transformations (Homogeneous Coordinates)**

Transformations like translation and perspective projection are not linear because:
- Translation requires adding constants $$(t_x, t_y)$$ to coordinates, which cannot be achieved using standard matrix multiplication.
- Perspective projection involves division by depth $$(z)$$, which is non-linear.

Homogeneous coordinates extend standard Cartesian coordinates by adding an extra dimension $$(w)$$, enabling these affine transformations to be represented as linear matrix operations.

**Unified Framework in Homogeneous Coordinates**

By using homogeneous coordinates, linear transformations (rotation, scaling, etc.) and affine transformations (translation, perspective) can all be represented as $$3 \times 3$$ or $$4 \times 4$$ matrices.  
This unification allows you to:
- Combine multiple transformations (e.g., rotation + translation + scaling) into a single transformation matrix.
- Perform all transformations through matrix multiplication in a consistent manner.

**Why Homogeneous Coordinates Are Better**

Homogeneous coordinates simplify the handling of both linear and affine transformations.  
They make it easier to:
- Combine multiple transformations seamlessly.
- Represent complex transformations like perspective projections.
- Work with pipelines in computer graphics (modeling, viewing, projection).


Let's have this example of a rotation;

Initial 2D Rotation Matrix:

$$
R = \begin{bmatrix} 
\cos(\theta) & -\sin(\theta) & 0 \\ 
\sin(\theta) & \cos(\theta) & 0 \\ 
0 & 0 & 1 
\end{bmatrix}.
$$

Let's say we want to rotate and translate - since we are using Homogeneous coordinates we can do that by adding **Translation Components**

If you add $${t_x}$$ and $${t_y}$$ to the last column, the matrix becomes:

$$
R_T = \begin{bmatrix} 
\cos(\theta) & -\sin(\theta) & t_x \\ 
\sin(\theta) & \cos(\theta) & t_y \\ 
0 & 0 & 1 
\end{bmatrix}.
$$

Applying the Transformation

$$
\begin{bmatrix} 
x' \\ 
y' \\ 
1 
\end{bmatrix}
=
\begin{bmatrix} 
\cos(\theta) & -\sin(\theta) & t_x \\ 
\sin(\theta) & \cos(\theta) & t_y \\ 
0 & 0 & 1 
\end{bmatrix}
\begin{bmatrix} 
x \\ 
y \\ 
1 
\end{bmatrix}.
$$

Expanding the matrix multiplication:

$$
x' = x \cos(\theta) - y \sin(\theta) + t_x,
$$

$$
y' = x \sin(\theta) + y \cos(\theta) + t_y,
$$

$$
w' = 1.
$$

**Now just for fun let's change `w` component where $${w \neq 1}$$.**

where $${w \neq 1}$$, you are altering the homogeneous scaling factor, which will have implications depending on how it is used.

### Effect of Changing $${w}$$

Let’s apply this matrix to a 2D point $$(x, y, 1)$$:

$$
\begin{bmatrix} 
x' \\ 
y' \\ 
w' 
\end{bmatrix}
=
\begin{bmatrix} 
\cos(\theta) & -\sin(\theta) & t_x \\ 
\sin(\theta) & \cos(\theta) & t_y \\ 
0 & 0 & w 
\end{bmatrix}
\begin{bmatrix} 
x \\ 
y \\ 
1 
\end{bmatrix}.
$$

The resulting coordinates are:

$$
x' = x \cos(\theta) - y \sin(\theta) + t_x,
$$

$$
y' = x \sin(\theta) + y \cos(\theta) + t_y,
$$

$$
w' = w.
$$

In homogeneous coordinates, after applying the transformation, you normalize the result by dividing by $${w'}$$ (the final $${w}$$-component):
{: .notice--success}

$$
x_{\text{cartesian}} = \frac{x'}{w'}, \quad y_{\text{cartesian}} = \frac{y'}{w'}.
$$

- If $${w = 1}$$: No change occurs during normalization, and $${x'}$$, $${y'}$$ remain as they are.
- If $${w > 1}$$: The coordinates $$(x', y')$$ will be **scaled closer** to the origin after normalization - because dividing by $${w}$$ reduces the magnitude of the coordinates.
- If $${w < 1}$$: The coordinates $$(x', y')$$ will be **scaled away** from the origin after normalization - because dividing by smaller $${w}$$ increases the magnitude of the coordinates.

This effectively introduces a **scaling effect** to the transformed object, making it appear larger or smaller depending on the value of $${w}$$.

This scaling behavior during normalization is what makes $${w}$$-component adjustments important in transformations like perspective projection and other depth-related calculations.
{: .notice--success}

### Usage of $${w}$$
In computer graphics: the use of the $${w}$$-component in homogeneous coordinates to distinguish between points and vectors.

**1. Distinction Between Points and Vectors in Geometry**

**Points:**
- Represent locations in space.
- Examples: A corner of a cube, the position of a light source.
- Have $${w = 1}$$ in homogeneous coordinates:
$$
\text{Point: } (x, y, z, 1).
$$
- Translation applies to points because they describe a fixed location in space.

**Vectors:**
- Represent directions in space.
- Examples: A surface normal, a direction of motion, or a light ray.
- Have $${w = 0}$$ in homogeneous coordinates:
$$
\text{Vector: } (x, y, z, 0).
$$
- Translation does not apply to vectors because they do not have a fixed location; they describe a direction or difference between points.

---

**2. How $${w}$$ Selectively “Switches Off” Translation**

In a typical $$4 \times 4$$ transformation matrix used in 3D graphics, the last column represents the translation:

$$
M = \begin{bmatrix} 
m_{11} & m_{12} & m_{13} & t_x \\ 
m_{21} & m_{22} & m_{23} & t_y \\ 
m_{31} & m_{32} & m_{33} & t_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix}.
$$

**Transformation of a Point $$(w = 1):$$**

$$
\begin{bmatrix} 
x' \\ 
y' \\ 
z' \\ 
w' 
\end{bmatrix}
=
\begin{bmatrix} 
m_{11} & m_{12} & m_{13} & t_x \\ 
m_{21} & m_{22} & m_{23} & t_y \\ 
m_{31} & m_{32} & m_{33} & t_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
\begin{bmatrix} 
x \\ 
y \\ 
z \\ 
1 
\end{bmatrix}.
$$

**Result:**

$$
x' = m_{11}x + m_{12}y + m_{13}z + t_x,
$$

$$
y' = m_{21}x + m_{22}y + m_{23}z + t_y,
$$

$$
z' = m_{31}x + m_{32}y + m_{33}z + t_z.
$$

The translation terms $$(t_x, t_y, t_z)$$ affect the point, moving it in space.

**Transformation of a Vector $$(w = 0):$$**

$$
\begin{bmatrix} 
x' \\ 
y' \\ 
z' \\ 
w' 
\end{bmatrix}
=
\begin{bmatrix} 
m_{11} & m_{12} & m_{13} & t_x \\ 
m_{21} & m_{22} & m_{23} & t_y \\ 
m_{31} & m_{32} & m_{33} & t_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix}
\begin{bmatrix} 
x \\ 
y \\ 
z \\ 
0 
\end{bmatrix}.
$$

**Result:**

$$
x' = m_{11}x + m_{12}y + m_{13}z,
$$

$$
y' = m_{21}x + m_{22}y + m_{23}z,
$$

$$
z' = m_{31}x + m_{32}y + m_{33}z.
$$

The translation terms $$(t_x, t_y, t_z)$$ are ignored, and only rotation, scaling, or shearing affects the vector.

---

**3. Why Is This Useful?**

**A. Different Behavior for Points and Vectors**
- Points (e.g., a vertex position) are **affected** by translation because they describe a location in space.
- Vectors (e.g., surface normals or directions) are **not affected** by translation because they describe directions or differences, not locations.

**B. Unified Transformation Framework**
- Using homogeneous coordinates, we can handle both points and vectors with the same transformation matrix:
  - Points: $${w = 1}$$
  - Vectors: $${w = 0}$$
- This avoids the need for separate equations or systems for translating points and transforming directions.

---

**4. Geometric Interpretation**
- Points with $${w = 1}$$: Represent actual positions in finite space.
- Vectors with $${w = 0}$$: Represent directions or "points at infinity," which extend indefinitely and are not tied to any specific position.

---

**5. Example in Practice**

Suppose you want to rotate and translate a 3D object:
- The vertices of the object (points) are rotated and then translated.
- The surface normals of the object (vectors) are only rotated, preserving their direction relative to the object’s new position.

This is essential in lighting calculations where normals define how light interacts with surfaces.

---

**Summary**

The $${w}$$-component in homogeneous coordinates distinguishes between points $$(w = 1)$$ and vectors $$(w = 0).$$  
- Points are translated, while vectors are not, allowing for correct geometric behavior.  
This makes homogeneous coordinates a powerful framework for handling both locations and directions in a consistent way.

### Example Usage
**Main code**

```cpp
// Light as a directional light (w = 0)
glm::vec4 lightDir = glm::vec4(-0.2f, -1.0f, -0.3f, 0.0f); // Directional light
glUniform4fv(glGetUniformLocation(shaderProgram, "lightPosition"), 1, glm::value_ptr(lightDir));

// Light as a point light (w = 1)
glm::vec4 lightPos = glm::vec4(1.2f, 1.0f, 2.0f, 1.0f); // Point light
glUniform4fv(glGetUniformLocation(shaderProgram, "lightPosition"), 1, glm::value_ptr(lightPos));
```

**Fragment Shader**

```cpp
 if (lightPosition.w == 0.0)
    {
        // Directional light: Normalize the light direction
        lightDir = normalize(lightPosition.xyz);
    }
    else
    {
        // Point light: Calculate light direction from light position
        lightDir = normalize(lightPosition.xyz - FragPos);
    }
```
Light Position or Direction:
   * `lightPosition.w = 1.0`: The light is treated as a point light (with translation applied).
   * `lightPosition.w = 0.0`: The light is treated as a directional light (translation ignored).

Fragment Shader Logic:
   * The if `(lightPosition.w == 0.0)` block handles directional lights by using the (x,y,z) values directly as a normalized direction.
   * The `else` block handles point lights by calculating the light's direction based on the difference between the light's position and the fragment's position.

### Unlocking affine transformations
Armed with 4 × 4 transform matrices, though, we can now create more general affine transformations that contain translation, such as:

* rotation about an axis that does not pass through the origin,
* scale about a plane that does not pass through the origin,
* reflection about a plane that does not pass through the origin, and
* orthographic projection onto a plane that does not pass through the origin.

The basic idea is to translate the “center” of the transformation to the origin, perform the linear transformation by using the techniques developed, and then transform the center back to its original location.

**Example**

Rotating an object that is **not at the origin** requires a combination of translation and rotation transformations. Here's how it works:

**Steps to Rotate an Object Not at the Origin**

**Translate the Object to the Origin:**

First, move the object to the origin so that rotation can be performed around the global origin.  
Translation matrix to bring the object to the origin:

$$
T_{\text{to origin}} = 
\begin{bmatrix} 
1 & 0 & 0 & -t_x \\ 
0 & 1 & 0 & -t_y \\ 
0 & 0 & 1 & -t_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix},
$$

where $${t_x, t_y, t_z}$$ are the coordinates of the object's center.

**Apply Rotation:**

Perform the desired rotation around the origin using a rotation matrix.  
For example, a rotation around the z-axis:

$$
R_z(\theta) = 
\begin{bmatrix} 
\cos(\theta) & -\sin(\theta) & 0 & 0 \\ 
\sin(\theta) & \cos(\theta) & 0 & 0 \\ 
0 & 0 & 1 & 0 \\ 
0 & 0 & 0 & 1 
\end{bmatrix}.
$$

**Translate the Object Back to Its Original Position:**

After rotation, move the object back to its original location.  
Translation matrix to restore the original position:
$$
T_{\text{back}} = 
\begin{bmatrix} 
1 & 0 & 0 & t_x \\ 
0 & 1 & 0 & t_y \\ 
0 & 0 & 1 & t_z \\ 
0 & 0 & 0 & 1 
\end{bmatrix}.
$$

**Combine the Transformations:**

The final transformation matrix $${M}$$ is:

$$
M = T_{\text{back}} \cdot R_z(\theta) \cdot T_{\text{to origin}}.
$$

```cpp
// Define transformation parameters
glm::vec3 objectPosition = glm::vec3(2.0f, 3.0f, 0.0f); // Object's position
float rotationAngle = glm::radians(90.0f);             // Rotation angle in radians

// Translation to origin
glm::mat4 translationToOrigin = glm::translate(glm::mat4(1.0f), -objectPosition);

// Rotation around z-axis
glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));

// Translation back to original position
glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), objectPosition);

// Combine transformations
glm::mat4 model = translationBack * rotation * translationToOrigin;
```

The matrix $${T_{\text{to origin}}}$$ (which moves the object to the origin) and $${T_{\text{back}}}$$ (which moves the object back to its original position) are inverses of each other.
{: .notice--success}

## $$4 \times 4$$ Matrices and Perspective Projection
We can use the division by $${w}$$ to encapsulate very succinctly the important geometric operation of **perspective projection.**

Perspective projection in 3D also projects onto a 2D plane (just like orthographic projection). However, the projectors are not parallel. In fact, they intersect at a point, known as
the *center of projection*.

![Alt Text]({{ site.baseurl }}/assets/maths/math65.png)

Because the center of projection is in front of the projection plane, the projectors **cross** before striking the plane, and thus the image is **inverted**. As we move an object **farther away** from the center of projection, 
its *orthographic projection* remains **constant**, but the perspective projection gets smaller, as illustrated:

![Alt Text]({{ site.baseurl }}/assets/maths/math66.png)

Let’s examine the geometry behind the perspective projection of a pinhole camera. Consider a 3D coordinate space with the origin at the pinhole (camera's aperture),
the z-axis perpendicular to the projection plane, and the x- and y-axes parallel to the plane of projection,

![Alt Text]({{ site.baseurl }}/assets/maths/math67.png)

**1. Setting Up the Coordinate Space**
- The origin $$(0, 0, 0)$$ is at the pinhole (camera's aperture).
- The z-axis points outward perpendicular to the projection plane.
- The x- and y-axes lie parallel to the projection plane.
- A 3D point $${\mathbf{p} = (p_x, p_y, p_z)}$$ is projected onto the plane at $$z = d$$, where $${d}$$ is the distance from the pinhole to the projection plane.


![Alt Text]({{ site.baseurl }}/assets/maths/math68.png)

**2. Perspective Projection Geometry**

The goal is to compute the coordinates of the projected point $${\mathbf{p}' = (p_x', p_y', p_z')}$$ on the projection plane.

**Key Observation: Similar Triangles**

From the geometry of the setup, a line from the origin (pinhole) to the point $${\mathbf{p}}$$ intersects the projection plane at $${\mathbf{p}'}$$.  
The relationship between the point $${\mathbf{p}}$$ and $${\mathbf{p}'}$$ is derived using similar triangles.

---

**Derivation for $${p_y'}$$:**

From the side view:

- The vertical coordinate of $${\mathbf{p}}$$: $${p_y}$$
- The vertical coordinate of $${\mathbf{p}'}$$: $${p_y'}$$
- $$z$$: Depth of the original point $${\mathbf{p}}$$
- $$d$$: Distance to the projection plane

By similar triangles:
$$
-\frac{p_y'}{d} = \frac{p_y}{z},
$$
where $${p_y'}$$ has a negative sign due to the image being inverted by the pinhole camera.

Rearranging:
$$
p_y' = -\frac{d \cdot p_y}{z}.
$$

**Removing the Minus Signs:**

To simplify computation (and avoid the upside-down effect), we place the projection plane in front of the origin ($$z = d$$, rather than $$z = -d$$). With this adjustment:
$$
p_y' = \frac{d \cdot p_y}{z}.
$$


![Alt Text]({{ site.baseurl }}/assets/maths/math69.png)

---

**Derivation for $${p_x'}$$:**

Using a similar argument for the x-axis:
$$
p_x' = \frac{d \cdot p_x}{z}.
$$

---

**Derivation for $${p_z'}$$:**

For all projected points, $${p_z' = d}$$, since they lie on the projection plane.

**Final Projected Coordinates**

For a point $${\mathbf{p} = (p_x, p_y, p_z)}$$ in 3D, the projected point $${\mathbf{p}'}$$ onto the plane $${z = d}$$ is:

$$
\mathbf{p}' = \left( \frac{d \cdot p_x}{p_z}, \frac{d \cdot p_y}{p_z}, d \right).
$$

### Homogeneous Coordinates

In homogeneous coordinates, we incorporate the division by $$z$$ into the $$w$$-component to make the projection linear and manageable for matrix operations.

The 4D homogeneous coordinates of $${\mathbf{p} = (p_x, p_y, p_z, 1)}$$ are transformed using a perspective projection matrix:

$$
P = 
\begin{bmatrix} 
d & 0 & 0 & 0 \\ 
0 & d & 0 & 0 \\ 
0 & 0 & 1 & 0 \\ 
0 & 0 & 1 & 0 
\end{bmatrix}.
$$

This is the most basic form of **Perspective Matrix** captures basic perspective scaling but ignores FOV, aspect ratio, and depth mapping.
{: .notice--warning}

The expanded matrix incorporates these additional factors to ensure:
* Correct scaling based on FOV and aspect ratio.
* Depth mapping for near/far clipping planes.
* Compatibility with normalized device coordinates (NDC).

**Applying this matrix:**

$$
\mathbf{p}_{\text{homogeneous}}' = P \cdot 
\begin{bmatrix} 
p_x \\ 
p_y \\ 
p_z \\ 
1 
\end{bmatrix}
=
\begin{bmatrix} 
d \cdot p_x \\ 
d \cdot p_y \\ 
p_z \\ 
p_z 
\end{bmatrix}.
$$

**To recover the Cartesian coordinates:**

$$
\mathbf{p}_{\text{cartesian}}' = \left( \frac{d \cdot p_x}{p_z}, \frac{d \cdot p_y}{p_z}, d \right).
$$

**Why Does $${z'} = d$$?**

For all points projected onto the plane, the z-coordinate of the projection is constant and equal to the plane’s depth:
$$
p_z' = d.
$$
This ensures that all points lie on the projection plane.

**Key Points**

- Perspective projection uses similar triangles to compute the projected point.
- The projection depends on the distance to the projection plane ($$d$$) and the depth of the original point ($$z$$).
- Moving the projection plane to $$z = d$$ simplifies calculations and avoids negative signs.
- In graphics, this is typically handled using a $$4 \times 4$$ perspective projection matrix.
