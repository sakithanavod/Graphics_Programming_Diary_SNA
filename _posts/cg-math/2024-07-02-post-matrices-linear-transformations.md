---
title: "Matrices and Linear Transformations"
date: 2024-07-02 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

This chapter continues our investigation of transformations

<!--more-->

## Rotation
### Rotation in 2D
A 2D rotation about the origin has only one parameter, the angle $$\theta$$, which defines the amount of rotation.

The standard convention found in most math books is to consider counterclockwise rotation positive and clockwise rotation negative.
{: .notice--primary}

![Alt Text]({{ site.baseurl }}/assets/maths/math48.png)

$$R(\theta) = \begin{pmatrix}-p' \\-q'\end{pmatrix}=\begin{pmatrix}\cos \theta & \sin \theta \\-\sin \theta & \cos \theta\end{pmatrix}$$

### 3D Rotation about Cardinal Axes
In 3D, rotation occurs about an **axis** rather than a point, with the term *axis* taking on its more commonplace meaning of a line about which something rotates.

An axis of rotation does not necessarily have to be one of the cardinal x, y, or z axes
{: .notice--warning}

we’ll need to establish which direction of rotation is considered “positive” and which is considered “negative.” We’re going
to obey the **left-hand** rule for this. 

#### Rotation about the x-axis
Let’s start with rotation about the x-axis, as shown in below. Constructing a matrix from the rotated basis vectors, we have:

$$R_x(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}1 & 0 & 0 \\0 & \cos \theta & \sin \theta \\0 & -\sin \theta & \cos\theta\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math49.png)

#### Rotation about the y-axis
Rotation about the y-axis is similar. The matrix to rotate about the y-axis is:

$$R_y(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}\cos \theta & 0 & -\sin \theta \\0 & 1 & 0 \\\sin \theta & 0 & \cos\theta\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math50.png)

#### Rotation about the z-axis
And finally, rotation about the z-axis is done with the matrix:

$$R_z(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}\cos \theta & \sin \theta & 0 \\ -\sin \theta  & \cos \theta & 0 \\0 & 0 & 1\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math51.png)

### 3D Rotation about an Arbitrary Axis
This is more complicated and less common than rotating about a cardinal axis. 

As before, we define $$(\theta)$$ to be the amount of rotation about the axis. The axis will be defined by a unit vector $$\mathbf{\hat{n}}$$..

Let’s derive a matrix to rotate about $$\mathbf{\hat{n}}$$ by the angle $$(\theta)$$. In other words, we wish to derive the matrix $$R(\mathbf{\hat{n}}, \theta)$$ such that when we multiply a vector $${v}$$ by $$R(\mathbf{\hat{n}}, \theta)$$

the resulting vector $$\mathbf{v}'$$ is the result of rotating $${v}$$ about $$\mathbf{\hat{n}}$$ by the angle $$(\theta)$$:

$$\begin{equation}
\mathbf{v}' = R(\mathbf{\hat{n}}, \theta) \mathbf{v}
\end{equation}$$

#### Rodrigues' rotation formula
Rodrigues' rotation formula is a method for rotating a vector in three-dimensional space by an axis and an angle. This formula is particularly useful in computer graphics, robotics, and other fields that require efficient and straightforward vector rotation computations.

**Rodrigues' Rotation Formula**
Given:
* A vector v to be rotated
* An axis of rotation represented by a unit vector n
* An angle of rotation $$(\theta)$$

The rotated vector $$\mathbf{v}'$$ is given by:

$$\begin{equation}
\mathbf{v}' = \mathbf{v} \cos\theta + (\mathbf{\hat{n}} \times \mathbf{v}) \sin\theta + \mathbf{\hat{n}} (\mathbf{\hat{n}} \cdot \mathbf{v})(1 - \cos\theta)
\end{equation}$$

We can use this to derive Rodrigues' rotation matrix from Rodrigues' rotation formula. To derive the rotation matrix, we need to express this formula in matrix form. Here’s the step-by-step process:

**1. Express Cross Product as a Matrix Multiplication:**

The cross product $$(\mathbf{\hat{n}} \times \mathbf{v})$$ can be represented using a **skew-symmetric matrix** $${N}$$. 
For $${n} = (n_x, n_y, n_z).$$ the skew-symmetric matrix $${N}$$ is:

$$
\mathbf{N} = \begin{bmatrix}
0 & -n_z & n_y \\
n_z & 0 & -n_x \\
-n_y & n_x & 0
\end{bmatrix}
$$

Then $$(\mathbf{\hat{n}} \times \mathbf{v}) = {Nv}$$

**2. Express Dot Product as Matrix Multiplication:**

The dot product $$\mathbf{\hat{n}} \cdot \mathbf{v}$$ can be written as $$\mathbf{n}^T{v}$$ where $$\mathbf{n}^T$$ is transpose of $${n}$$. So, 

$$\mathbf{\hat{n}} \cdot \mathbf{v} =  \mathbf{n}^T{v}$$

Here's the step-by-step explanation: if,

$$
\mathbf{n} = \begin{bmatrix}
n_x \\
n_y \\
n_z
\end{bmatrix}
\

\mathbf{v} = \begin{bmatrix}
v_x \\
v_y \\
v_z
\end{bmatrix}
$$

The dot product $$\mathbf{\hat{n}} \cdot \mathbf{v} = {n_xv_x + n_yv_y + n_zv_z} $$ 

So,

$$\mathbf{n}^T = \begin{pmatrix}
n_x & n_y & n_z
\end{pmatrix}$$

Therefore,

$$\mathbf{n}^T \mathbf{v} = (n_x, n_y, n_z) \begin{pmatrix}
v_x \\
v_y \\
v_z
\end{pmatrix}$$

This multiplication results in:

$$\mathbf{n}^T \mathbf{v} = {n_xv_x + n_yv_y + n_zv_z} $$ 

This is exactly the dot product $$\mathbf{\hat{n}} \cdot \mathbf{v}$$

Finally we can tell:

 $$\mathbf{\hat{n}} \cdot \mathbf{v} = \mathbf{n}^T{v}$$


**3. Combine All Terms:**

Substitute the matrix forms into the original formula:

$$\mathbf{v}' = \mathbf{v} \cos\theta + \mathbf{N} \mathbf{v} \sin\theta + \mathbf{n} (\mathbf{n}^T \mathbf{v})(1 - \cos\theta)$$

**4. Distribute: $${v}$$**

Notice that we want to express this in the form $$\mathbf{v}' = {Rv}$$, where $${R}$$ is the rotation matrix. We can factor out $${v}$$:

$$\mathbf{v}' = (\cos\theta \mathbf{I} + \sin\theta \mathbf{N} + (1 - \cos\theta) \mathbf{n} \mathbf{n}^T) \mathbf{v}$$

Here, $${I}$$ is the identity matrix.

**5. Construct the Rotation Matrix:**

The rotation matrix $${R}$$ is then given by:

$$R = \cos\theta \mathbf{I} + \sin\theta \mathbf{N} + (1 - \cos\theta) \mathbf{n} \mathbf{n}^T$$

Let's break this down:
* $$\cos\theta {I}$$: Scales the identity matrix by $$\cos\theta$$
* $$\sin\theta {N}$$ : Scales the skew-symmetric matrix by $$\sin\theta$$
* $$(1 - \cos\theta){\mathbf{n} \mathbf{n}^T}$$ :  Outer product of $${n}$$ scaled by  $$(1 - \cos\theta)$$

**6. Final Form of the Rotation Matrix:**

$$
R = \cos\theta \mathbf{I} + \sin\theta \begin{pmatrix}
0 & -n_z & n_y \\
n_z & 0 & -n_x \\
-n_y & n_x & 0 \end{pmatrix}
+ (1 - \cos\theta) \begin{pmatrix}
n_x^2 & n_x n_y & n_x n_z \\
n_y n_x & n_y^2 & n_y n_z \\
n_z n_x & n_z n_y & n_z^2
\end{pmatrix}
$$

Simplifying, the elements of $${R}$$ can be explicitly written as:

$$
R(\mathbf{\hat{n}}, \theta) = \begin{pmatrix}
-p' \\
-q' \\
-r'
\end{pmatrix}
 = \begin{pmatrix}
\cos\theta + n_x^2 (1 - \cos\theta) & n_x n_y (1 - \cos\theta) - n_z \sin\theta & n_x n_z (1 - \cos\theta) + n_y \sin\theta \\
n_y n_x (1 - \cos\theta) + n_z \sin\theta & \cos\theta + n_y^2 (1 - \cos\theta) & n_y n_z (1 - \cos\theta) - n_x \sin\theta \\
n_z n_x (1 - \cos\theta) - n_y \sin\theta & n_z n_y (1 - \cos\theta) + n_x \sin\theta & \cos\theta + n_z^2 (1 - \cos\theta)
\end{pmatrix}
$$

This matrix $${R}$$ can now be used to rotate any vector around the specified axis by the given angle.
{: .notice--success}
