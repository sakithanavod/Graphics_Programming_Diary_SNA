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
**Table of Contents**
* TOC
{:toc}

## Rotation
### Rotation in 2D
A 2D rotation about the origin has only one parameter, the angle $$\theta$$, which defines the amount of rotation.

The standard convention found in most math books is to consider counterclockwise rotation positive and clockwise rotation negative.
{: .notice--primary}

![Alt Text]({{ site.baseurl }}/assets/maths/math48.png)

$$R(\theta) = \begin{pmatrix}-p' \\-q'\end{pmatrix}=\begin{pmatrix}\cos \theta & \sin \theta \\-\sin \theta & \cos \theta\end{pmatrix}$$

### Usage of 4x4 matrix

Example : 

$$
R_x(\theta) = 
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & \cos \theta & \sin \theta & 0 \\
0 & -\sin \theta & \cos \theta & 0 \\
0 & 0 & 0 & 1 \\
\end{bmatrix}
$$


We use a 4x4 matrix in 3D graphics to represent transformations (translation, rotation, scaling, etc.) because it allows us to include translation in the transformation pipeline and work seamlessly with homogeneous coordinates.

We use a $$4 \times 4$$ matrix in 3D graphics to represent transformations (translation, rotation, scaling, etc.) because it allows us to include translation in the transformation pipeline and work seamlessly with homogeneous coordinates. Here's a detailed explanation:

1. **Homogeneous Coordinates**:
In 3D space, a point is typically represented by $$(x, y, z)$$, which uses 3D Cartesian coordinates.
However, to apply transformations consistently, we use homogeneous coordinates by adding an extra dimension $$w$$, resulting in $$(x, y, z, w)$$.
For points in 3D space, we typically set $$w = 1$$ (so $$(x, y, z, 1)$$), allowing the use of matrix operations that can handle translation, which cannot be represented with a standard $$3 \times 3$$ matrix.

2. **Translation Representation:**
In a 3x3 matrix, you cannot represent translation because it affects the $${x, y, z}$$ coordinates directly, not just through multiplication.
By using a 4x4 matrix, we can represent translation in the last column:

$$
T = 
\begin{bmatrix}
1 & 0 & 0 & t_x \\
0 & 1 & 0 & t_y \\
0 & 0 & 1 & t_z \\
0 & 0 & 0 & 1 \\
\end{bmatrix}
$$

Here, $${t_x, t_y, t_z}$$ represent the translation along the $${x, y, z}$$ axes, respectively.

### 3D Rotation about Cardinal Axes
In 3D, rotation occurs about an **axis** rather than a point, with the term *axis* taking on its more commonplace meaning of a line about which something rotates.

An axis of rotation does not necessarily have to be one of the cardinal x, y, or z axes
{: .notice--warning}

we’ll need to establish which direction of rotation is considered “positive” and which is considered “negative.” We’re going
to obey the **left-hand** rule for this.

#### Rotation about the x-axis
Let’s start with rotation about the x-axis, as shown in below. Constructing a matrix from the rotated basis vectors, we have:

$$R_x(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}1 & 0 & 0 \\0 & \cos \theta & \sin \theta \\0 & -\sin \theta & \cos\theta\end{pmatrix}$$

if coordinate system is right-handed then (example of homogenous coordinate system hence extra `w` component: don't worry about this for now),

$$
R_x(\theta) = 
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & \cos \theta & \sin \theta & 0 \\
0 & -\sin \theta & \cos \theta & 0 \\
0 & 0 & 0 & 1 \\
\end{bmatrix}
$$

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

This can be useful when we want to replace vector notation of cross product with matrix notation.
{: .notice--success}

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

This can be useful when we want to replace vector notation of dot product with matrix notation
{: .notice--success}

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

## Scale

We can scale an object to make it proportionally bigger or smaller by a factor of *k*. If we apply this scale to the entire object, thus “dilating” the object about the origin, we are performing a *uniform scale.*

If we wish to “stretch” or “squash” the object, we can apply different scale factors in different directions, resulting in *nonuniform scale*.

### Scaling along the Cardinal Axes

The simplest scale operation applies a separate scale factor along each cardinal axis. In 2D, we have two scale factors, $${k_x}$$ and $${k_x}$$.Image below shows an object with various scale values for $${k_x}$$ and $${k_x}$$.

![Alt Text]({{ site.baseurl }}/assets/maths/math52.png)

As is intuitively obvious, the basis vectors `p` and `q` are independently affected by the corresponding scale factors:

$$
p' = k_x \cdot p = k_x \cdot \begin{bmatrix} 1 & 0 \end{bmatrix} = \begin{bmatrix} k_x & 0 \end{bmatrix}
$$

$$
q' = k_y \cdot q = k_y \cdot \begin{bmatrix} 0 & 1 \end{bmatrix} = \begin{bmatrix} 0 & k_y \end{bmatrix}
$$

Constructing the 2D scale matrix $${S(k_x, k_y)}$$ from these basis vectors, we get

$$
S(k_x, k_y) = 
\begin{pmatrix} 
-p' \\ 
-q' 
\end{pmatrix}
= 
\begin{pmatrix} 
k_x & 0 \\ 
0 & k_y 
\end{pmatrix}
$$

For 3D, we add a third scale factor $${k_z}$$, and the 3D scale matrix is then given by:

$$
S(k_x, k_y, k_z) = 
\begin{pmatrix} 
-p' \\ 
-q' \\ 
-r'
\end{pmatrix}
= 
\begin{pmatrix} 
k_x & 0 & 0 \\ 
0 & k_y & 0 \\ 
0 & 0 & k_z 
\end{pmatrix}
$$

If we multiply any arbitrary vector by this matrix, then, as expected, each component is scaled by the appropriate scale factor:

$$
\begin{bmatrix}
x & y & z
\end{bmatrix}
\begin{bmatrix}
k_x & 0 & 0 \\
0 & k_y & 0 \\
0 & 0 & k_z
\end{bmatrix}
=
\begin{pmatrix}
k_x x & k_y y & k_z z
\end{pmatrix}
$$

In homogeneous coordinates, a scaling matrix is represented as a 4x4 matrix to enable uniform or non-uniform scaling in 3D space. Here is how it looks:

4x4 Scaling Matrix:
$$
S = 
\begin{bmatrix}
s_x & 0 & 0 & 0 \\
0 & s_y & 0 & 0 \\
0 & 0 & s_z & 0 \\
0 & 0 & 0 & 1 \\
\end{bmatrix}
$$

### Scaling in an Arbitrary Direction

We can apply scale independent of the coordinate system used by scaling in an arbitrary direction. We define $${\hat{n}}$$ to be the unit vector parallel to the direction of scale, and `k` to be the scale factor to be applied about the line (in 2D) or plane (in 3D) that passes through the origin and is perpendicular to $${\hat{n}}$$. 

Let’s try to derive an expression: given an arbitrary vector $${v}$$, computes $${v`}$$ in terms of $${v}$$, $${\hat{n}}$$ , and $${k}$$.

![Alt Text]({{ site.baseurl }}/assets/maths/math53.png)

We know that,

$${v=v_⊥+v_∥}$$

also we know,

$${v_∥=(v · {\hat{n}}) {\hat{n}}}$$

because it's the projection of $${v}$$ onto $${\hat{n}}$$. 

Since $${v_⊥}$$ is perpendicular to $${\hat{n}}$$, it will not be affected by the scale operation:

$${v`_⊥=v_⊥}$$

and we know that:
$${v_⊥=v - (v · {\hat{n}}){\hat{n}}}$$

Therefore, 

$${v`_⊥=v - (v · {\hat{n}}){\hat{n}}}$$

See how there is no `k` scale factor
{: .notice--success}

$${v`_∥}$$ is trivially given by:

$${v`_∥=kv_∥}$$

We can derive that,

$${v`_∥=k(v · {\hat{n}}){\hat{n}}}$$

Now we know both $${v`_∥}$$ & $${v`_⊥}$$ so we can find $${v`}$$

$${v`=v`_⊥+v`_∥}$$

$${v`= v - (v.{\hat{n}}){\hat{n}} + k (v.{\hat{n}})}$$

$${v`= v + (k-1)(v.{\hat{n}}){\hat{n}}}$$

Now that we know how to scale an arbitrary vector, we can compute the value of the basis vectors after scale.
for 2D basis vector;

$$\mathbf{p} = \begin{bmatrix} 1 & 0 \end{bmatrix}$$ and $$\mathbf{q} = \begin{bmatrix} 0 & 1 \end{bmatrix}$$

We can derive $${p`}$$ and  $${q`}$$as,

$$
\mathbf{p`} = \begin{bmatrix} 1 + (k - 1) n_x^2 \\ (k - 1) n_x \cdot n_y \end{bmatrix}
$$

$$
\mathbf{q`} = \begin{bmatrix} (k - 1) n_xn_y \\ 1 + (k-1) n_y^2 \end{bmatrix}
$$

Forming a matrix from the basis vectors, we arrive at the 2D matrix to scale by a factor of $${k}$$ in an arbitrary direction specified by the unit vector $${\hat{n}}$$:

$$
S(\hat{n}, k) = \begin{bmatrix} -p' \\ -q' \end{bmatrix} = \begin{bmatrix} 1 + (k - 1) n_x^2 & (k - 1) n_x \cdot n_y \\ (k - 1) n_x \cdot n_y & 1 + (k - 1) n_y^2 \end{bmatrix}
$$

In 3D, the values of the basis vectors are computed by for

$${\mathbf{p} = \begin{bmatrix} 1 & 0 & 0 \end{bmatrix}}$$, $${\mathbf{q} = \begin{bmatrix} 0 & 1 & 0 \end{bmatrix}}$$ and $${\mathbf{r} = \begin{bmatrix} 0 & 0 & 1 \end{bmatrix}}$$

Finally, the 3D matrix to scale by a factor of k in an arbitrary direction specified by the unit vector $${\hat{n}}$$ is

$$
S(\hat{n}, k) =
\begin{bmatrix}
-p' \\
-q' \\
-r'
\end{bmatrix}
=
\begin{bmatrix}
1 + (k - 1) n_x^2 & (k - 1) n_x \cdot n_y & (k - 1) n_x \cdot n_z \\
(k - 1) n_x \cdot n_y & 1 + (k - 1) n_y^2 & (k - 1) n_y \cdot n_z \\
(k - 1) n_x \cdot n_z & (k - 1) n_y \cdot n_z & 1 + (k - 1) n_z^2
\end{bmatrix}
$$

### Orthographic Projection
Orthographic projection is a type of projection used in computer graphics and technical drawing to represent a 3D object in 2D space without perspective distortion. 

Projection refers to an operation that reduces the dimensions of an object, mapping 3D points onto a 2D plane or 2D points onto a 1D axis. 
Unlike perspective projection, where objects appear smaller as they get further away from the camera, orthographic projection maintains the same scale for objects, regardless of their depth.
{: .notice--success}

#### Characteristics
* **Parallel Lines:** In orthographic projection, the lines connecting the original points to their projected points are parallel to each other. This is why it's sometimes called parallel projection.
* **Dimensional Consistency:** Unlike perspective projection, orthographic projection maintains the actual dimensions and proportions of objects without any depth-based distortion. (making orthographic projection ideal for technical drawings, CAD models)

This process essentially projects all points in the scene onto a surface that is perpendicular to the direction of projection.

#### How Orthographic Projection Works
It involves using a scale factor of **zero** in a specific direction, which flattens the object onto a plane (in 3D) or an axis (in 2D).

Imagine a cube in 3D space. In orthographic projection, if we project this cube onto a 2D plane (e.g., the xy-plane), the entire depth component (z-values) is ignored or compressed to zero.
{: .notice--success}

Mathematically, this means the z-coordinate of each vertex of the cube is dropped or disregarded during the projection. The resulting projection shows the view as if you were looking at the object directly from the front, side, or top, without any indication of depth.
{: .notice--primary}

![Alt Text]({{ site.baseurl }}/assets/maths/math54.png)

We will talk about Orthographic Projection in detail later on!

#### Projecting onto a Cardinal Axis or Plane
Cardinal axes and planes are the basic coordinate axes $$(x, y, z)$$ or planes formed by these axes (e.g., the xy-plane). When we project onto these axes or planes, we essentially reduce the dimensionality of the object.

##### Simplest Projection: 
The simplest way to project an object onto a cardinal axis or plane is by simply ignoring (discarding) one of its coordinates. For example, to project a 3D object onto the xy-plane, we discard the z-coordinates.

**Projection Matrices for Cardinal Axes and Planes:**
* Projection onto the x-axis $$P_x$$:
$$
P_x = 
\begin{bmatrix}
1 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 0 \\
\end{bmatrix}
$$
This matrix maps all y-values and z-values to 0, effectively projecting points onto the x-axis.

* Projection onto the y-axis $$P_y$$:
$$
P_y = 
\begin{bmatrix}
0 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 0 \\
\end{bmatrix}
$$
This matrix maps all x-values and z-values to 0, projecting points onto the y-axis.

* Projection onto the xy-plane $$P_{xy}$$:
$$
P_{xy} = 
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 0 \\
\end{bmatrix}
$$
This matrix discards the z-component, flattening the 3D points onto the 2D xy-plane.

* Projection onto the xz-plane $$P_{xz}$$:
$$
P_{xz} = 
\begin{bmatrix}
1 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & 1 \\
\end{bmatrix}
$$
This matrix projects points onto the xz-plane by discarding the y-components.

* Projection onto the yz-plane $$P_{yz}$$:
$$
P_{yz} = 
\begin{bmatrix}
0 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1 \\
\end{bmatrix}
$$
This matrix discards the x-components, projecting points onto the yz-plane.

##### Projecting onto an Arbitrary Line or Plane
Arbitrary projections involve projecting points onto a line (in 2D) or a plane (in 3D) defined by a unit vector $$\hat{n}$$ that is perpendicular to the line or plane. This allows for more flexible projections beyond the standard axes.

**2D Projection onto an Arbitrary Line:**
* Matrix for 2D Projection:
$$
P(\hat{n}) = 
\begin{bmatrix}
1 - n_x^2 & -n_x n_y \\
-n_x n_y & 1 - n_y^2 \\
\end{bmatrix}
$$
Here, $$\hat{n} = (n_x, n_y)$$ is the unit vector perpendicular to the line.

* 3D Projection onto an Arbitrary Plane:
$$
P(\hat{n}) = 
\begin{bmatrix}
1 - n_x^2 & -n_x n_y & -n_x n_z \\
-n_x n_y & 1 - n_y^2 & -n_y n_z \\
-n_x n_z & -n_y n_z & 1 - n_z^2 \\
\end{bmatrix}
$$
$$\hat{n} = (n_x, n_y, n_z)$$ is the unit vector perpendicular to the plane.

**How These Matrices Work**

The projection matrix scales the components along the direction perpendicular to the projection line or plane to zero while retaining the other components. This operation effectively flattens the points onto the desired line or plane.

**Example:**

To project a 3D object onto the xy-plane, you can use the matrix:
$$
P_{xy} = 
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 0 \\
\end{bmatrix}
$$
Multiplying this matrix with a point $$(x, y, z)$$ gives:
$$
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 0 \\
\end{bmatrix}
\cdot
\begin{bmatrix}
x \\
y \\
z \\
\end{bmatrix}
=
\begin{bmatrix}
x \\
y \\
0 \\
\end{bmatrix}
$$
This result shows that the z-component is discarded, leaving a 2D projection on the xy-plane.

## Reflection
Reflection is a transformation that flips an object across a line (in 2D) or a plane (in 3D). This transformation mirrors the object, creating a symmetrical version on the opposite side of the reflection axis or plane.

### 2D Reflection:

![Alt Text]({{ site.baseurl }}/assets/maths/math55.png)

Reflecting an object in 2D involves flipping it across a line that passes through the origin and is perpendicular to a unit vector $$\hat{n} = (n_x, n_y)$$. The reflection matrix $$R(\hat{n})$$ for this transformation is:

**Derivation of 2D Reflection Matrix:**

Given that applying a scale factor of $$-1$$ along the reflection axis achieves reflection, the matrix for reflection about an axis perpendicular to $$\hat{n}$$ is:

We need to start with the concept of reflecting a vector $$\mathbf{v}$$ across a plane (or axis in 2D) defined by a normal vector $$\hat{n}$$.

1. **Initial Concept of Reflection:**
The reflection of a vector $$\mathbf{v}$$ across a plane that is perpendicular to $$\hat{n}$$ involves **"flipping"** the component of $$\mathbf{v}$$ that is parallel to $$\hat{n}$$ and **keeping** the component that is perpendicular to $$\hat{n}$$ unchanged.
2. **Decompose the Vector:**
Any vector $$\mathbf{v}$$ can be decomposed into two components:
- The component parallel to $$\hat{n}$$: 
    $$
    \mathbf{v}_{\parallel} = (\mathbf{v} \cdot \hat{n}) \hat{n} - \textbf{from dot product} \\
    $$
- The component perpendicular to $$\hat{n}$$: 
    $$
    \mathbf{v}_{\perp} = \mathbf{v} - \mathbf{v}_{\parallel}
    $$
3. **Reflection Operation:**
![Alt Text]({{ site.baseurl }}/assets/maths/math56.png)
- When we reflect $$\mathbf{v}$$ across the plane defined by $$\hat{n}$$, the parallel component $$\mathbf{v}_{\parallel}$$ is **flipped**, while the perpendicular component $$\mathbf{v}_{\perp}$$ remains **unchanged.**
- The reflected vector $$\mathbf{v'}$$ can be expressed as:
    $$
    \mathbf{v'} = \mathbf{v}_{\perp} - \mathbf{v}_{\parallel} - \textbf{notice that we just flipped the sign of parallel component} \\
    $$
4. **Substitute the Components:**
- Substitute $$\mathbf{v}_{\parallel} = (\mathbf{v} \cdot \hat{n}) \hat{n}$$ into the equation:
    $$
    \mathbf{v'} = \mathbf{v} - 2(\mathbf{v} \cdot \hat{n}) \hat{n}
    $$
5. **Matrix Representation:**
- We need to represent this transformation in matrix form. Notice that $$(\mathbf{v} \cdot \hat{n}) \hat{n}$$ can be expressed as $$\hat{n} (\hat{n}^T \mathbf{v})$$, where $$\hat{n} \hat{n}^T$$ is an outer product matrix - (**Remember we can convert dot and cross product in which are in vector form in to matrix form**).
- Therefore, the reflection equation becomes:
    $$
    \mathbf{v'} = \mathbf{v} - 2\hat{n} \hat{n}^T \mathbf{v}
    $$
6. **General Matrix Form:**
- To apply this transformation to any vector $$\mathbf{v}$$, we construct the reflection matrix $$R(\hat{n})$$ as:
    $$
    R(\hat{n}) = I - 2\hat{n} \hat{n}^T,
    $$
 - where $$I$$ is the identity matrix.

This can also be written in expanded form:

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2n_x^2 & -2n_x n_y \\
-2n_x n_y & 1 - 2n_y^2 \\
\end{bmatrix}
$$

#### Example Use Case:
If $$\hat{n} = \left(\frac{1}{\sqrt{2}}, \frac{1}{\sqrt{2}}\right)$$ (a 45-degree line), the reflection matrix becomes:

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2\left(\frac{1}{\sqrt{2}}\right)^2 & -2\left(\frac{1}{\sqrt{2}}\right)\left(\frac{1}{\sqrt{2}}\right) \\
-2\left(\frac{1}{\sqrt{2}}\right)\left(\frac{1}{\sqrt{2}}\right) & 1 - 2\left(\frac{1}{\sqrt{2}}\right)^2 \\
\end{bmatrix}
$$

Calculating the values:

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2\left(\frac{1}{2}\right) & -2\left(\frac{1}{2}\right) \\
-2\left(\frac{1}{2}\right) & 1 - 2\left(\frac{1}{2}\right) \\
\end{bmatrix}
=
\begin{bmatrix}
0 & -1 \\
-1 & 0 \\
\end{bmatrix}
$$

Applying this matrix to: $$\mathbf{v} = (3, 2)$$:

$$
\mathbf{v'} = 
\begin{bmatrix}
0 & -1 \\
-1 & 0 \\
\end{bmatrix}
\begin{bmatrix}
3 \\
2 \\
\end{bmatrix}
=
\begin{bmatrix}
-2 \\
-3 \\
\end{bmatrix}
$$


### 3D Reflection:
In 3D, reflection is performed across a plane instead of a line. The plane must pass through the origin for the transformation to remain linear. The reflection matrix $$R(\hat{n})$$ for a plane perpendicular to $$\hat{n} = (n_x, n_y, n_z)$$ is:

**3D Reflection Matrix:**

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2n_x^2 & -2n_x n_y & -2n_x n_z \\
-2n_x n_y & 1 - 2n_y^2 & -2n_y n_z \\
-2n_x n_z & -2n_y n_z & 1 - 2n_z^2 \\
\end{bmatrix}
$$

#### Explanation of the Matrix:
* Diagonal Elements:
The diagonal elements $$1 - 2n_i^2$$ reflect the reduction and reversal of the component of the vector along the corresponding axis.
* Off-Diagonal Elements:
The terms $$-2n_x n_y$$, $$-2n_x n_z$$, and $$-2n_y n_z$$ account for how the components of the vector interact during the reflection.

#### Example Use Case:
To reflect a vector $$\mathbf{v} = (2, 3, 5)$$ across a plane defined by $$\hat{n} = \left(\frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}\right)$$, the reflection matrix $$R(\hat{n})$$ would be:

Reflection Matrix:

Given the unit normal vector $$\hat{n} = \left(\frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}\right)$$, the reflection matrix $$R(\hat{n})$$ is:

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2n_x^2 & -2n_x n_y & -2n_x n_z \\
-2n_x n_y & 1 - 2n_y^2 & -2n_y n_z \\
-2n_x n_z & -2n_y n_z & 1 - 2n_z^2 \\
\end{bmatrix}
$$

*Step 1: Substitute* $$n_x = n_y = n_z = \frac{1}{\sqrt{3}}$$:

$$
R(\hat{n}) = 
\begin{bmatrix}
1 - 2\left(\frac{1}{\sqrt{3}}\right)^2 & -2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) & -2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) \\
-2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) & 1 - 2\left(\frac{1}{\sqrt{3}}\right)^2 & -2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) \\
-2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) & -2\left(\frac{1}{\sqrt{3}}\right)\left(\frac{1}{\sqrt{3}}\right) & 1 - 2\left(\frac{1}{\sqrt{3}}\right)^2 \\
\end{bmatrix}
$$

Simplify $$\left(\frac{1}{\sqrt{3}}\right)^2 = \frac{1}{3}$$:

$$
R(\hat{n}) = 
\begin{bmatrix}
\frac{1}{3} & -\frac{2}{3} & -\frac{2}{3} \\
-\frac{2}{3} & \frac{1}{3} & -\frac{2}{3} \\
-\frac{2}{3} & -\frac{2}{3} & \frac{1}{3} \\
\end{bmatrix}
$$

*Step 2: Apply the Reflection Matrix to* $$\mathbf{v}$$

Given $$\mathbf{v} = (2, 3, 5)$$, calculate $$\mathbf{v'} = R(\hat{n})\mathbf{v}$$:

$$
\mathbf{v'} = 
\begin{bmatrix}
\frac{1}{3} & -\frac{2}{3} & -\frac{2}{3} \\
-\frac{2}{3} & \frac{1}{3} & -\frac{2}{3} \\
-\frac{2}{3} & -\frac{2}{3} & \frac{1}{3} \\
\end{bmatrix}
\begin{bmatrix}
2 \\
3 \\
5 \\
\end{bmatrix}
$$

*Step 3: By Perform the Matrix Multiplication We get :*

The reflected vector $$\mathbf{v'}$$ is:

$$
\mathbf{v'} = (-4, -4, -4)
$$

This confirms that $$\mathbf{v} = (2, 3, 5)$$ has been reflected across the plane defined by $$\hat{n} = \left(\frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}, \frac{1}{\sqrt{3}}\right)$$.

## Shearing
Shearing is a transformation that “skews” the coordinate space, stretching it non-uniformly. Angles are not preserved; however, surprisingly, **areas and volumes** are. 

The basic idea is to **add a multiple of one coordinate to the other**. For example, in 2D, we might take a multiple of y and add it to x, so that x′ = x + sy.

![Alt Text]({{ site.baseurl }}/assets/maths/math57.png)

### 2D Shearing
In 2D space, shearing can occur along either the x-axis or the y-axis: Firs, lets derive a matrix that skews along x - axis:

#### Step-by-step Derivation:
1. **Definition of Shearing Along the x-axis:**
 * Shearing along the x-axis means each x-coordinate is modified by adding a scaled multiple of the y-coordinate. Mathematically, this can be expressed as:
    $$
    x' = x + sy
    $$
where $$s$$ is the shearing factor and $$x'$$ is the new x-coordinate.

2. **Keeping the y-coordinate Constant:**
 * The y-coordinate does not change during shearing along the x-axis, so:
    $$
    y' = y
    $$

3. **Transformation Matrix Representation:**
 * To represent this transformation in matrix form, we need a matrix that, when multiplied by a vector 
    $$
    \begin{bmatrix}
    x \\
    y \\
    \end{bmatrix}
    $$, 
    results in the sheared coordinates 
    $$
    \begin{bmatrix}
    x' \\
    y' \\
    \end{bmatrix}
    $$.

    We start by expressing the equations in matrix form:

    $$
    \begin{bmatrix}
    x' \\
    y' \\
    \end{bmatrix}
    =
    \begin{bmatrix}
    1 & s \\
    0 & 1 \\
    \end{bmatrix}
    \begin{bmatrix}
    x \\
    y \\
    \end{bmatrix}
    $$

    This multiplication gives:

    $$
    \begin{bmatrix}
    x + sy \\
    y \\
    \end{bmatrix}
    $$

    Which represents the skewed coordinates, This can also done for skewing along y-axis

Therefore,

**Shearing along the x-axis:**
A multiple of the y-coordinate is added to the x-coordinate.
The transformation matrix for shearing along the x-axis is:

$$
H_x(s) = 
\begin{bmatrix}
1 & s \\
0 & 1 \\
\end{bmatrix}
$$

The transformation modifies the x-coordinate according to:

$$
x' = x + sy
$$

where $$s$$ is the shearing factor.

**Shearing along the y-axis:**

A multiple of the x-coordinate is added to the y-coordinate.
The transformation matrix for shearing along the y-axis is:

$$
H_y(s) = 
\begin{bmatrix}
1 & 0 \\
s & 1 \\
\end{bmatrix}
$$

This changes the y-coordinate as:

$$
y' = y + sx
$$

where $$s$$ is the shearing factor.

### 3D Shearing
In 3D space, shearing can involve shifting one coordinate by scaled multiples of the other two coordinates. The matrices for these transformations are:

#### Step-by-step Derivation:

**Definition of Shearing in the xy-plane:**

![Alt Text]({{ site.baseurl }}/assets/maths/math58.png)

For shearing in the xy-plane, the x- and y-coordinates remain the same, while the z-coordinate is modified based on the x- and y-coordinates.

Shearing in the xy-plane typically implies that the transformation matrix operates in a plane parallel to the xy-plane but affects the third coordinate (z).
{: .notice--warning}

Mathematically, the new coordinates can be expressed as:

$$
x' = x
$$

$$
y' = y
$$

$$
z' = z + sx + ty
$$

where $$s$$ and $$t$$ are the shearing factors applied to the x and y coordinates, respectively.

**Constructing the Transformation Matrix**

We want a matrix $$H_{xy}(s, t)$$ that, when multiplied by a vector 
$$
\begin{bmatrix}
x \\
y \\
z \\
\end{bmatrix}
$$,
results in 
$$
\begin{bmatrix}
x' \\
y' \\
z' \\
\end{bmatrix}
$$.

The matrix should keep the x and y coordinates the same and add $$sx + ty$$ to the z-coordinate.

This can be written in matrix form as:

$$
\begin{bmatrix}
x' \\
y' \\
z' \\
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
s & t & 1 \\
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
\end{bmatrix}
$$

**Matrix Multiplication Verification:**

To verify, multiply the matrix by the coordinate vector:

$$
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
s & t & 1 \\
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
\end{bmatrix}
=
\begin{bmatrix}
1 \cdot x + 0 \cdot y + 0 \cdot z \\
0 \cdot x + 1 \cdot y + 0 \cdot z \\
s \cdot x + t \cdot y + 1 \cdot z \\
\end{bmatrix}
=
\begin{bmatrix}
x \\
y \\
z + sx + ty \\
\end{bmatrix}
$$

##### Resulting Shearing Matrix:
The matrix that performs shearing in the xy-plane, where the z-coordinate is affected by the x and y coordinates, is:

**Shearing in the xy-plane:**

$$
H_{xy}(s, t) =
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
s & t & 1 \\
\end{bmatrix}
$$

Just like that we can derive matrices for remaining planes:

**Shearing in the xz-plane:**

$$
H_{xz}(s, t) =
\begin{bmatrix}
1 & s & 0 \\
0 & 1 & 0 \\
0 & t & 1 \\
\end{bmatrix}
$$

The y-coordinate is altered by the x and z coordinates.

**Shearing in the yz-plane:**

$$
H_{yz}(s, t) =
\begin{bmatrix}
1 & 0 & 0 \\
s & 1 & 0 \\
t & 0 & 1 \\
\end{bmatrix}
$$

The x-coordinate is affected by the y and z coordinates.

## Classes of Transformations
### Linear Transformations
A linear transformation is a mathematical function that maps vectors from one space to another while preserving **vector addition and scalar multiplication**. In simpler terms, if a transformation $$F$$ is linear, it should satisfy two main properties:

#### Additivity (Preservation of Addition):
$$
F(\mathbf{a} + \mathbf{b}) = F(\mathbf{a}) + F(\mathbf{b})
$$

This means that transforming the sum of two vectors yields the same result as transforming each vector individually and then adding the results.

#### Homogeneity (Preservation of Scalar Multiplication):
$$
F(k \mathbf{a}) = k F(\mathbf{a})
$$

This states that if a vector is scaled by a scalar $$k$$ before transformation, the result should be the same as transforming the vector first and then scaling the result by $$k$$.

#### Explanation:

Suppose we have two vectors, $$\mathbf{a}$$ and $$\mathbf{b}$$, and a transformation $$F$$ (which could be any linear transformation, such as rotation, scaling, etc.). The transformation $$F$$ acts on these vectors to map them to a new space or change their direction or magnitude.

**Sum of Two Vectors:** 

When we add two vectors $$\mathbf{a}$$ and $$\mathbf{b}$$, we get a new vector:

$$
\mathbf{c} = \mathbf{a} + \mathbf{b}
$$

**Transforming the Sum:** 

Now, if we apply the transformation $$F$$ to the vector $$\mathbf{c}$$, we are transforming the sum of the two original vectors:

$$
F(\mathbf{c}) = F(\mathbf{a} + \mathbf{b})
$$

**Linear Property:**

For $$F$$ to be a linear transformation, it must satisfy the additivity property:

$$
F(\mathbf{a} + \mathbf{b}) = F(\mathbf{a}) + F(\mathbf{b})
$$

This means the transformation of the sum of the two vectors $$\mathbf{a}$$ and $$\mathbf{b}$$ should give the same result as applying the transformation to each vector individually and then adding the transformed vectors.

#### Implications of These Properties:

**Matrix Multiplication as a Linear Transformation**

If a transformation $$F(\mathbf{a})$$ can be expressed as matrix multiplication, 

$$
F(\mathbf{a}) = \mathbf{a}M
$$

where $$M$$ is a square matrix, then it is a **linear transformation.** 

This holds true because matrix multiplication inherently satisfies the properties of **additivity and homogeneity.**

#### Proof of Matrix Multiplication for Linearity

**Additivity:**

Given $$F(\mathbf{a} + \mathbf{b}) = (\mathbf{a} + \mathbf{b})M$$:

$$
(\mathbf{a} + \mathbf{b})M = \mathbf{a}M + \mathbf{b}M = F(\mathbf{a}) + F(\mathbf{b})
$$

This confirms that the transformation preserves addition.

**Homogeneity:**

Given $$F(k \mathbf{a}) = (k \mathbf{a})M$$:

$$
(k \mathbf{a})M = k(\mathbf{a}M) = k F(\mathbf{a})
$$

This confirms that the transformation preserves scalar multiplication.

Any transformation **without translation** that can be expressed using matrix multiplication is **linear**, as it satisfies both additivity and homogeneity.
{: .notice--success}

Linear transformations do not contain translation.
{: .notice--warning}

### Affine transformations
Affine transformations are a type of transformation that preserves points, straight lines, and planes. These transformations can include translation, scaling, rotation, reflection, and shearing. An affine transformation is a more general form of a linear transformation because it includes translation, which shifts the position of objects.

#### Key Characteristics of Affine Transformations:
* **Preserve Collinearity:** Points that lie on a straight line before an affine transformation remain on a straight line after the transformation.
* **Preserve Ratios:** The ratios of distances between points on a line remain constant. For example, the midpoint of a line segment stays the midpoint after an affine transformation.
* **Do Not Preserve Angles or Lengths:** Unlike purely linear transformations, affine transformations do not necessarily preserve the angles between lines or the lengths of line segments.

#### Mathematical Representation:
An affine transformation can be represented mathematically as:

$$
\mathbf{y} = A\mathbf{x} + \mathbf{b}
$$

where:

$$\mathbf{x}$$ is the original vector (point) in the space. \\
$$A$$ is a linear transformation matrix. \\
$$\mathbf{b}$$ is a translation vector.

Any linear transformation can be viewed as an affine transformation with the translation vector $$\mathbf{b} = 0$$. In other words, a linear transformation is a special case of an affine transformation where no translation occurs.
{: .notice--primary}

#### Components of an Affine Transformation:

* Linear Transformation $$A\mathbf{x}$$:
This part of the transformation can include operations such as rotation, scaling, shearing, or reflection.

* Translation $$\mathbf{b}$$:
This shifts the entire space by a constant vector $$\mathbf{b}$$. Unlike purely linear transformations, translation changes the position of the object without affecting its orientation or shape.

#### Example of 2D Affine Transformation:
An example affine transformation matrix in 2D that includes scaling, rotation, and translation looks like:

$$
\begin{bmatrix}
x' \\
y' \\
1 \\
\end{bmatrix}
=
\begin{bmatrix}
a_{11} & a_{12} & t_x \\
a_{21} & a_{22} & t_y \\
0 & 0 & 1 \\
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
1 \\
\end{bmatrix}
$$

where:

- $$a_{11}, a_{12}, a_{21}, a_{22}$$ represent the linear transformation part (e.g., rotation or scaling).
- $$t_x, t_y$$ represent the translation components.

#### Homogeneous Coordinates:

To represent affine transformations using matrix multiplication in a consistent way, we use homogeneous coordinates (we will talk about this in detail in next chapter). In 2D, a point $$(x, y)$$ is represented as $$(x, y, 1)$$, and in 3D, a point $$(x, y, z)$$ is represented as $$(x, y, z, 1)$$.

This allows us to combine linear transformations and translations into a single matrix operation: a 2D example

$$
\mathbf{Y} = M \mathbf{X}
$$

where:

$$
M = 
\begin{bmatrix}
a_{11} & a_{12} & t_x \\
a_{21} & a_{22} & t_y \\
0 & 0 & 1 \\
\end{bmatrix}
$$

and:

$$
\mathbf{X} = 
\begin{bmatrix}
x \\
y \\
1 \\
\end{bmatrix}
$$

#### Affine Transformations in 3D

In 3D, affine transformations are represented with 4x4 matrices to handle 3D points in homogeneous coordinates:

$$
\begin{bmatrix}
x' \\
y' \\
z' \\
1 \\
\end{bmatrix}
=
\begin{bmatrix}
a_{11} & a_{12} & a_{13} & t_x \\
a_{21} & a_{22} & a_{23} & t_y \\
a_{31} & a_{32} & a_{33} & t_z \\
0 & 0 & 0 & 1 \\
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
1 \\
\end{bmatrix}
$$

Any transformation that includes **translation** and can be expressed using matrix multiplication in homogeneous coordinates is an **affine transformation**, not purely linear.
{: .notice--success}

Adding a translation to any of pure **Linear Transformations**, example: Scaling, Rotating, Shearing turns the transformation into an affine transformation
{: .notice--primary}

#### Affine vs. Linear Transformations

Affine transformations use matrix multiplication in homogeneous coordinates, which might make it seem like they should be linear transformations. However, the inclusion of the translation component means they do not satisfy the strict properties of linearity:

Additivity: An affine transformation does not satisfy 

$$
F(\mathbf{a} + \mathbf{b}) = F(\mathbf{a}) + F(\mathbf{b})
$$ 

if there is translation involved because $$F(\mathbf{x})$$ shifts all points by $$\mathbf{b}$$.

Homogeneity: Affine transformations do not satisfy 

$$
F(k \mathbf{a}) = k F(\mathbf{a})
$$ 
due to the constant translation component.
