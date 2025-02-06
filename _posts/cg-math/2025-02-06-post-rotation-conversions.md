---
title: "Rotation Conversions"
date: 2025-02-06 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

How to handle conversions between Euler angles, rotation matrices, axis-angle, and quaternions.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Converting between Representations

### Euler angles to a matrix

Euler angles represent rotations around the X, Y, and Z axes using three angles $$ (\alpha, \beta, \gamma) $$, typically referred to as:

- **Roll** $$ (\alpha) $$ → Rotation around the $$ X $$-axis.
- **Pitch** $$ (\beta) $$ → Rotation around the $$ Y $$-axis.
- **Yaw** $$ (\gamma) $$ → Rotation around the $$ Z $$-axis.

A rotation matrix is a $$ 3 \times 3 $$ matrix that applies a rotation to a vector in 3D space.

---

#### 1. Rotation Matrices for Each Axis - using 2D rotation formulas

**Rotation Around the X-Axis (Roll, $$ \alpha $$)**

$$ R_x =
\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos\alpha & -\sin\alpha \\
0 & \sin\alpha & \cos\alpha
\end{bmatrix} $$

**Rotation Around the Y-Axis (Pitch, $$ \beta $$)**

$$ R_y =
\begin{bmatrix}
\cos\beta & 0 & \sin\beta \\
0 & 1 & 0 \\
-\sin\beta & 0 & \cos\beta
\end{bmatrix} $$

**Rotation Around the Z-Axis (Yaw, $$ \gamma $$)**

$$ R_z =
\begin{bmatrix}
\cos\gamma & -\sin\gamma & 0 \\
\sin\gamma & \cos\gamma & 0 \\
0 & 0 & 1
\end{bmatrix} $$

---

#### 2. Computing the Final Rotation Matrix

The order of rotations matters. A common convention is **Z-Y-X (Yaw-Pitch-Roll)**, meaning:

$$ R = R_z R_y R_x $$

This means:
1. Rotate around $$ X $$.
2. Rotate around $$ Y $$.
3. Rotate around $$ Z $$.

Expanding:

$$ R =
\begin{bmatrix}
\cos\gamma & -\sin\gamma & 0 \\
\sin\gamma & \cos\gamma & 0 \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
\cos\beta & 0 & \sin\beta \\
0 & 1 & 0 \\
-\sin\beta & 0 & \cos\beta
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\
0 & \cos\alpha & -\sin\alpha \\
0 & \sin\alpha & \cos\alpha
\end{bmatrix}
$$

Multiplying these matrices results in:

$$ R =
\begin{bmatrix}
\cos\gamma\cos\beta & \sin\gamma\cos\beta & -\sin\beta \\
\cos\gamma\sin\beta\sin\alpha - \sin\gamma\cos\alpha & \sin\gamma\sin\beta\sin\alpha + \cos\gamma\cos\alpha & \cos\beta\sin\alpha \\
\cos\gamma\sin\beta\cos\alpha + \sin\gamma\sin\alpha & \sin\gamma\sin\beta\cos\alpha - \cos\gamma\sin\alpha & \cos\beta\cos\alpha
\end{bmatrix}
$$

---

#### 3. Summary of Steps

1. Compute the individual rotation matrices $$ R_x, R_y, R_z $$.
2. Multiply them in the correct order (e.g., **Z-Y-X** or another convention).
3. The result is a **$$ 3 \times 3 $$ rotation matrix**.

This final matrix represents the combined rotation in 3D space.


### Matrix to Euler angles.

Given a $$ 3 \times 3 $$ rotation matrix, we can extract the Euler angles (roll, pitch, yaw) using trigonometric relationships.

---

#### 1. Understanding the Rotation Matrix

A rotation matrix $$ R $$ representing a rotation in 3D space can be written as:

$$
R =
\begin{bmatrix}
r_{00} & r_{01} & r_{02} \\
r_{10} & r_{11} & r_{12} \\
r_{20} & r_{21} & r_{22}
\end{bmatrix}
$$

where:

- Each row/column represents how unit vectors transform under the rotation.
- The matrix is orthogonal (i.e., $$ R^T R = I $$).
- The goal is to find the Euler angles $$ (\alpha, \beta, \gamma) $$ such that:

  $$ R = R_z(\gamma) R_y(\beta) R_x(\alpha) $$

  where:

  - $$ \alpha $$ = Roll (rotation about X-axis)
  - $$ \beta $$ = Pitch (rotation about Y-axis)
  - $$ \gamma $$ = Yaw (rotation about Z-axis)

---

#### 2. Extracting Euler Angles

There are multiple conventions for Euler angles, but the most common is **Z-Y-X (yaw-pitch-roll)**.

**Case 1: When $$ r_{20} \neq \pm1 $$ (Normal Case)**

Using trigonometry:

- **Yaw $$ \gamma $$ (Rotation around Z-axis)**:

  $$
  \gamma = \text{atan2}(r_{10}, r_{00})
  $$

- **Pitch $$ \beta $$ (Rotation around Y-axis)**:

  $$
  \beta = \text{asin}(-r_{20})
  $$

- **Roll $$ \alpha $$ (Rotation around X-axis)**:

  $$
  \alpha = \text{atan2}(r_{21}, r_{22})
  $$


##### How did we get $$ \gamma = \text{atan2}(r_{10}, r_{00})? $$

To extract Euler angles from a rotation matrix, we need to understand how each entry in the matrix corresponds to a rotation around the Z, Y, and X axes. Let's go step by step.

---
The full rotation matrix:

$$
R =
\begin{bmatrix}
\cos\gamma \cos\beta & \sin\gamma \cos\beta & -\sin\beta \\
\cos\gamma \sin\beta \sin\alpha - \sin\gamma \cos\alpha & \sin\gamma \sin\beta \sin\alpha + \cos\gamma \cos\alpha & \cos\beta \sin\alpha \\
\cos\gamma \sin\beta \cos\alpha + \sin\gamma \sin\alpha & \sin\gamma \sin\beta \cos\alpha - \cos\gamma \sin\alpha & \cos\beta \cos\alpha
\end{bmatrix}
$$

Labeling the elements:

$$
R =
\begin{bmatrix}
r_{00} & r_{01} & r_{02} \\
r_{10} & r_{11} & r_{12} \\
r_{20} & r_{21} & r_{22}
\end{bmatrix}
$$

---

**For example lets extract the Yaw Angle $$ \gamma $$ (Rotation About Z)**

* Yaw $$ \gamma $$ (rotation around the Z-axis) affects only the first two rows.  
* From $$ R_z(\gamma) $$, we see that the X and Y coordinates are rotated in the XY-plane, while Z remains unchanged.

From the rotation matrix:

$$ r_{00} = \cos\gamma \cos\beta $$

$$ r_{10} = \sin\gamma \cos\beta $$

**Deriving $$ \gamma = \text{atan2}(r_{10}, r_{00}) $$**

Rewriting:

$$
\frac{r_{10}}{r_{00}} = \frac{\sin\gamma \cos\beta}{\cos\gamma \cos\beta}
$$

Since $$ \cos\beta $$ cancels out (as long as $$ \beta \neq \pm90^\circ $$), we get:

$$
\tan\gamma = \frac{r_{10}}{r_{00}}
$$

Taking the inverse tangent:

$$
\gamma = \text{atan2}(r_{10}, r_{00})
$$

---

**Why Use $$ \text{atan2} $$ Instead of $$ \text{atan} $$?**

- $$ \text{atan2}(y, x) $$ returns the correct quadrant for $$ \gamma $$.
- It avoids issues where $$ \cos\gamma $$ could be zero, preventing division by zero errors.

---

**Case 2: Gimbal Lock Cases ($$ r_{20} = \pm1 $$)**

In this case, the pitch angle $$ \beta $$ is $$ \pm90^\circ $$ (or $$ \pm\frac{\pi}{2} $$), causing a singularity. The yaw and roll angles are no longer independent.

- If $$ r_{20} = -1 $$ (Pitch = $$ +90^\circ $$):

  $$
  \beta = +\frac{\pi}{2}
  $$

  $$
  \gamma = 0
  $$

  $$
  \alpha = \text{atan2}(-r_{01}, r_{11})
  $$

- If $$ r_{20} = +1 $$ (Pitch = $$ -90^\circ $$):

  $$
  \beta = -\frac{\pi}{2}
  $$

  $$
  \gamma = 0
  $$

  $$
  \alpha = \text{atan2}(r_{01}, r_{11})
  $$

---

#### 3. Summary of the Conversion Formulas

For a rotation matrix:

$$
R =
\begin{bmatrix}
r_{00} & r_{01} & r_{02} \\
r_{10} & r_{11} & r_{12} \\
r_{20} & r_{21} & r_{22}
\end{bmatrix}
$$

The Euler angles **(Z-Y-X order)** are:

- **Yaw**:

  $$
  \gamma = \text{atan2}(r_{10}, r_{00})
  $$

- **Pitch**:

  $$
  \beta = \text{asin}(-r_{20})
  $$

- **Roll**:

  $$
  \alpha = \text{atan2}(r_{21}, r_{22})
  $$

With special cases handled when $$ r_{20} = \pm1 $$.

### Quaternion to a matrix

A unit quaternion 

$$ q = (w, x, y, z) $$ 

can be converted into a $$ 3 \times 3 $$ rotation matrix $$ R $$ that can be used to rotate vectors in 3D space.
The rotation matrix $$ R $$ derived from a quaternion $$ q $$ performs the same transformation as the quaternion sandwich product:

$$ R v = q v q^{-1} $$

where:

- $$ v $$ is a 3D vector represented as a pure quaternion:

  $$ v = (0, v_x, v_y, v_z) $$

- $$ q $$ is the unit quaternion representing a rotation.

- $$ q^{-1} $$ is the inverse of $$ q $$, which for unit quaternions is just the conjugate:

  $$ q^{-1} = (w, -x, -y, -z) $$


This is equivalent to multiplying $$ v $$ by the rotation matrix $$ R $$.
Expanding the quaternion multiplication results in the matrix formulation below.

$$
R =
\begin{bmatrix}
1 - 2y^2 - 2z^2 & 2xy - 2wz & 2xz + 2wy \\
2xy + 2wz & 1 - 2x^2 - 2z^2 & 2yz - 2wx \\
2xz - 2wy & 2yz + 2wx & 1 - 2x^2 - 2y^2
\end{bmatrix}
$$


### Matrix to a quaternion.

To convert a $$ 3 \times 3 $$ rotation matrix $$ R $$ into a quaternion  $$ q = (w, x, y, z) $$,

we use a method that extracts the quaternion components from the matrix elements.

---

#### 1. Rotation Matrix Representation

A rotation matrix $$ R $$ is:

$$
R =
\begin{bmatrix}
r_{00} & r_{01} & r_{02} \\
r_{10} & r_{11} & r_{12} \\
r_{20} & r_{21} & r_{22}
\end{bmatrix}
$$

where each $$ r_{ij} $$ represents an element in the matrix

See expanded version of the matrix above.
{: .notice--warning}

#### 2. Extracting Quaternion Components from $$ R $$

**Derive $$w$$**

The trace of the matrix is the sum of its diagonal elements:

$$ \text{tr}(R) = r_{00} + r_{11} + r_{22} $$

From the rotation matrix, we have:

$$ r_{00} = 1 - 2y^2 - 2z^2 $$

$$ r_{11} = 1 - 2x^2 - 2z^2 $$

$$ r_{22} = 1 - 2x^2 - 2y^2 $$

**Summing these:**

$$
r_{00} + r_{11} + r_{22} = 3 - 2(x^2 + y^2 + z^2 + x^2 + z^2 + x^2 + y^2)
$$

Using the **unit quaternion identity**:

$$ w^2 + x^2 + y^2 + z^2 = 1 $$

we rearrange:

$$ r_{00} + r_{11} + r_{22} = 4w^2 - 1 $$

**Solving for $$ w $$:**

$$ 4w^2 = 1 + r_{00} + r_{11} + r_{22} $$

$$ w = \frac{1}{2} \sqrt{1 + r_{00} + r_{11} + r_{22}} $$

**Once we have $$ w $$ we can extract rest of components like below**

**Extracting $$ x $$**

Look at the off-diagonal element $$ r_{21} $$:

$$ r_{21} = 2yz + 2wx $$

Similarly, look at $$ r_{12} $$:

$$ r_{12} = 2yz - 2wx $$

Subtract these two equations:

$$
r_{21} - r_{12} = (2yz + 2wx) - (2yz - 2wx)
$$

$$
r_{21} - r_{12} = 4wx
$$

Solving for $$ x $$:

$$ x = \frac{r_{21} - r_{12}}{4w} $$

---

**Extracting $$ y $$**

Look at the off-diagonal element $$ r_{02} $$:

$$ r_{02} = 2xz + 2wy $$

Similarly, look at $$ r_{20} $$:

$$ r_{20} = 2xz - 2wy $$

Subtract these two equations:

$$
r_{02} - r_{20} = (2xz + 2wy) - (2xz - 2wy)
$$

$$
r_{02} - r_{20} = 4wy
$$

Solving for $$ y $$:

$$ y = \frac{r_{02} - r_{20}}{4w} $$

---

**Extracting $$ z $$**

Look at the off-diagonal element $$ r_{10} $$:

$$ r_{10} = 2xy + 2wz $$

Similarly, look at $$ r_{01} $$:

$$ r_{01} = 2xy - 2wz $$

Subtract these two equations:

$$
r_{10} - r_{01} = (2xy + 2wz) - (2xy - 2wz)
$$

$$
r_{10} - r_{01} = 4wz
$$

Solving for $$ z $$:

$$ z = \frac{r_{10} - r_{01}}{4w} $$


All extracted components:

$$ w = \frac{1}{2} \sqrt{1 + r_{00} + r_{11} + r_{22}} $$

$$ x = \frac{1}{4w} (r_{21} - r_{12}) $$

$$ y = \frac{1}{4w} (r_{02} - r_{20}) $$

$$ z = \frac{1}{4w} (r_{10} - r_{01}) $$


#### 3. Handling Different Cases

If $$ w $$ is small or near zero (which happens when the trace $$ r_{00} + r_{11} + r_{22} $$ is near $$ -1 $$), we compute $$ x, y, z $$ directly:

- If $$ r_{00} $$ is the largest diagonal element:

  $$
  x = \frac{1 + r_{00} - r_{11} - r_{22}}{2}
  $$

  $$
  w = \frac{r_{21} - r_{12}}{4x}
  $$

  $$
  y = \frac{r_{01} + r_{10}}{4x}
  $$

  $$
  z = \frac{r_{02} + r_{20}}{4x}
  $$

- If $$ r_{11} $$ is the largest diagonal element:

  $$
  y = \frac{1 - r_{00} + r_{11} - r_{22}}{2}
  $$

  $$
  w = \frac{r_{02} - r_{20}}{4y}
  $$

  $$
  x = \frac{r_{01} + r_{10}}{4y}
  $$

  $$
  z = \frac{r_{12} + r_{21}}{4y}
  $$

- If $$ r_{22} $$ is the largest diagonal element:

  $$
  z = \frac{1 - r_{00} - r_{11} + r_{22}}{2}
  $$

  $$
  w = \frac{r_{10} - r_{01}}{4z}
  $$

  $$
  x = \frac{r_{02} + r_{20}}{4z}
  $$

  $$
  y = \frac{r_{12} + r_{21}}{4z}
  $$

This approach ensures the quaternion is correctly extracted from a rotation matrix while handling numerical stability issues.

### Euler angles to a quaternion.

#### 1. Understanding the Rotation Order

Euler angles describe rotations around the X, Y, and Z axes. A common convention is **Z-Y-X (yaw-pitch-roll order)**:

$$ q = q_z(\gamma) \cdot q_y(\beta) \cdot q_x(\alpha) $$

where:

- $$ \gamma $$ is the **yaw** (rotation around the Z-axis).
- $$ \beta $$ is the **pitch** (rotation around the Y-axis).
- $$ \alpha $$ is the **roll** (rotation around the X-axis).

Each of these rotations can be represented by a quaternion, and we multiply them to get the final quaternion.

---

#### 2. Constructing Quaternions for Each Rotation

We construct individual quaternions for each axis rotation.

**Rotation Around X-Axis (Roll $$ \alpha $$)**

To get below results apply axis unit vectors (in this case X-Axis means the unit axis is: $$ \hat{u} = (1, 0, 0) $$) to quaternion **Rotation Formula**
{: .notice--success}

A rotation of $$ \alpha $$ around the X-axis is represented by the quaternion:

$$ q_x = \left(\cos \frac{\alpha}{2}, \sin \frac{\alpha}{2}, 0, 0 \right) $$

which expands to:

$$ q_x = (w_x, x, y, z) = \left(\cos \frac{\alpha}{2}, \sin \frac{\alpha}{2}, 0, 0 \right) $$

**Rotation Around Y-Axis (Pitch $$ \beta $$)**

A rotation of $$ \beta $$ around the Y-axis is represented by the quaternion:

$$ q_y = \left(\cos \frac{\beta}{2}, 0, \sin \frac{\beta}{2}, 0 \right) $$

which expands to:

$$ q_y = (w_y, x, y, z) = \left(\cos \frac{\beta}{2}, 0, \sin \frac{\beta}{2}, 0 \right) $$

**Rotation Around Z-Axis (Yaw $$ \gamma $$)**

A rotation of $$ \gamma $$ around the Z-axis is represented by the quaternion:

$$ q_z = \left(\cos \frac{\gamma}{2}, 0, 0, \sin \frac{\gamma}{2} \right) $$

which expands to:

$$ q_z = (w_z, x, y, z) = \left(\cos \frac{\gamma}{2}, 0, 0, \sin \frac{\gamma}{2} \right) $$

---

#### 3. Combining Rotations Using Quaternion Multiplication

Now that we have three quaternions $$ q_x $$, $$ q_y $$, and $$ q_z $$, we multiply them to get the final rotation quaternion:

$$ q = q_z q_y q_x $$

**Step 1: Compute $$ q_y q_x $$**

Using quaternion multiplication:

$$ q_y q_x =
\begin{bmatrix}
w_y w_x - x_x y_x - y_x y_y - z_x z_y \\
w_y x_x + w_x y_x + y_y z_x - z_y y_x \\
w_y y_x + w_x z_x - x_x z_y + z_x w_y \\
w_y z_x + w_x y_y - x_x y_x + z_y w_x
\end{bmatrix}
$$

Substituting the values:

$$ q_y q_x =
\begin{bmatrix}
\cos \frac{\beta}{2} \cos \frac{\alpha}{2} - \sin \frac{\beta}{2} \sin \frac{\alpha}{2} \\
\sin \frac{\alpha}{2} \cos \frac{\beta}{2} \\
\cos \frac{\alpha}{2} \sin \frac{\beta}{2} \\
\sin \frac{\alpha}{2} \sin \frac{\beta}{2}
\end{bmatrix}
$$

**Step 2: Compute $$ q_z (q_y q_x) $$**

Using quaternion multiplication:

$$ q = q_z q_y q_x $$

Substituting values:

$$ w = \cos \frac{\alpha}{2} \cos \frac{\beta}{2} \cos \frac{\gamma}{2} + \sin \frac{\alpha}{2} \sin \frac{\beta}{2} \sin \frac{\gamma}{2} $$

$$ x = \sin \frac{\alpha}{2} \cos \frac{\beta}{2} \cos \frac{\gamma}{2} - \cos \frac{\alpha}{2} \sin \frac{\beta}{2} \sin \frac{\gamma}{2} $$

$$ y = \cos \frac{\alpha}{2} \sin \frac{\beta}{2} \cos \frac{\gamma}{2} + \sin \frac{\alpha}{2} \cos \frac{\beta}{2} \sin \frac{\gamma}{2} $$

$$ z = \cos \frac{\alpha}{2} \cos \frac{\beta}{2} \sin \frac{\gamma}{2} - \sin \frac{\alpha}{2} \sin \frac{\beta}{2} \cos \frac{\gamma}{2} $$

---

#### 4. Final Quaternion Formula

Thus, the quaternion corresponding to the Euler angles $$ (\alpha, \beta, \gamma) $$ is:

$$
q =
\begin{bmatrix}
w \\
x \\
y \\
z
\end{bmatrix}
=
\begin{bmatrix}
\cos \frac{\alpha}{2} \cos \frac{\beta}{2} \cos \frac{\gamma}{2} + \sin \frac{\alpha}{2} \sin \frac{\beta}{2} \sin \frac{\gamma}{2} \\
\sin \frac{\alpha}{2} \cos \frac{\beta}{2} \cos \frac{\gamma}{2} - \cos \frac{\alpha}{2} \sin \frac{\beta}{2} \sin \frac{\gamma}{2} \\
\cos \frac{\alpha}{2} \sin \frac{\beta}{2} \cos \frac{\gamma}{2} + \sin \frac{\alpha}{2} \cos \frac{\beta}{2} \sin \frac{\gamma}{2} \\
\cos \frac{\alpha}{2} \cos \frac{\beta}{2} \sin \frac{\gamma}{2} - \sin \frac{\alpha}{2} \sin \frac{\beta}{2} \cos \frac{\gamma}{2}
\end{bmatrix}
$$

### Quaternion to Euler angles.

#### 1. Rotation Matrix from a Quaternion

A quaternion:

$$ q = (w, x, y, z) $$

corresponds to the rotation matrix:

$$
R =
\begin{bmatrix}
1 - 2y^2 - 2z^2 & 2xy - 2wz & 2xz + 2wy \\
2xy + 2wz & 1 - 2x^2 - 2z^2 & 2yz - 2wx \\
2xz - 2wy & 2yz + 2wx & 1 - 2x^2 - 2y^2
\end{bmatrix}
$$

The **Euler angles** (roll, pitch, yaw) correspond to rotations around the **X, Y, and Z axes** in the **Z-Y-X rotation order**.

#### 2. Deriving Each Euler Angle

**Extracting Yaw ($$ \gamma $$, Rotation Around Z-Axis)**

When we rotate a point by $$ \gamma $$ around the **Z-axis**, the **X and Y coordinates** change, but **Z remains the same**.

A **pure Z-axis rotation** is described by the **2D rotation matrix**:

$$
R_z(\gamma) =
\begin{bmatrix}
\cos \gamma & -\sin \gamma & 0 \\
\sin \gamma & \cos \gamma & 0 \\
0 & 0 & 1
\end{bmatrix}
$$

This means:

- $$ r_{00} $$ corresponds to $$ \cos \gamma $$ (**X remains X scaled by** $$ \cos \gamma $$).
- $$ r_{10} $$ corresponds to $$ \sin \gamma $$ (**X moves to Y scaled by** $$ \sin \gamma $$).

The rotation about the **Z-axis** affects the **X and Y coordinates**.  
In a standard **3D rotation matrix** for yaw, we expect:

$$ r_{10} = \sin \gamma, \quad r_{00} = \cos \gamma $$

From our **quaternion-derived matrix**:

$$ r_{10} = 2xy + 2wz $$

$$ r_{00} = 1 - 2x^2 - 2z^2 $$

Using the **atan2 function**:

$$ \gamma = \text{atan2}(r_{10}, r_{00}) $$

Substituting the values:

$$ \gamma = \text{atan2} \left( 2xy + 2wz, 1 - 2x^2 - 2z^2 \right) $$

**Extracting Pitch ($$ \beta $$, Rotation Around Y-Axis)**

The rotation about the **Y-axis** affects the **Z-component** of the vector. We expect:

$$ r_{20} = -\sin \beta $$

From our **quaternion-derived matrix**:

$$ r_{20} = 2xz - 2wy $$

Thus:

$$ \beta = \arcsin (r_{20}) $$

Substituting:

$$ \beta = \arcsin (2xz - 2wy) $$

---

**Extracting Roll ($$ \alpha $$, Rotation Around X-Axis)**

The rotation about the **X-axis** affects the **Y and Z coordinates**.  
In a standard **rotation matrix for roll**, we expect:

$$ r_{21} = \sin \alpha, \quad r_{22} = \cos \alpha $$

From our **quaternion-derived matrix**:

$$ r_{21} = 2yz + 2wx $$

$$ r_{22} = 1 - 2y^2 - 2z^2 $$

Thus:

$$ \alpha = \text{atan2} (r_{21}, r_{22}) $$

Substituting:

$$ \alpha = \text{atan2} (2yz + 2wx, 1 - 2y^2 - 2z^2) $$

---

#### 3. Handling Gimbal Lock Cases

If $$ \beta = 90^\circ $$ (i.e., $$ \sin \beta = \pm 1 $$), we encounter **gimbal lock**.

The yaw ($$ \gamma $$) angle becomes **undefined**.

In this case, we set:

$$ \gamma = 0 $$

and adjust $$ \alpha $$ as follows:

$$ \alpha = \text{atan2} (-2xy - 2wz, 1 - 2y^2 - 2z^2) $$

---

#### 4. Final Formulas

**Euler Angles from Quaternion**

$$ \gamma = \text{atan2} (2xy + 2wz, 1 - 2x^2 - 2z^2) $$

$$ \beta = \arcsin (2xz - 2wy) $$

$$ \alpha = \text{atan2} (2yz + 2wx, 1 - 2y^2 - 2z^2) $$
