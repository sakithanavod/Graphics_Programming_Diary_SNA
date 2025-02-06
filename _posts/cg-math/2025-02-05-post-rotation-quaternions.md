---
title: "Quaternions"
date: 2025-02-05 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

This chapter tackles Quaternions! the bridge algebra and geometry, Quaternions offers an elegant framework for describing orientations in three-dimensional space.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Quaternions
Quaternions are a mathematical tool used to represent 3D rotations. They provide a compact, efficient, and robust way to avoid some limitations of other rotation representations, such as gimbal lock in Euler angles. Quaternions are widely used in computer graphics, robotics, and physics simulations.

A quaternion is a four-dimensional complex number with one real part and three imaginary parts:
$$
q = w + xi + yj + zk
$$
where:

- $$w$$ is the scalar (real) part.
- $$x, y, z$$ are the vector (imaginary) parts.
- $$i, j, k$$ are imaginary units with the following relationships:
  $$
  i^2 = j^2 = k^2 = ijk = -1.
  $$

**For 3D Rotations**, quaternions are represented as:
$$
q = [w, v]
$$
where:

- $$w = \cos\left(\frac{\theta}{2}\right)$$ (rotation magnitude).
- $$v = (x, y, z) = \hat{u} \sin\left(\frac{\theta}{2}\right),$$  
  with $$\hat{u}$$ being the unit vector along the axis of rotation and $$\theta$$ the rotation angle.

So the quaternion for this rotation is:

$$
q = \left[\cos\left(\frac{\theta}{2}\right), \sin\left(\frac{\theta}{2}\right) \cdot (u_x, u_y, u_z)\right].
$$

So:

- $$w = \cos\left(\frac{\theta}{2}\right):$$ Encodes the magnitude of the rotation.
- $$(x, y, z) = \sin\left(\frac{\theta}{2}\right) \cdot (u_x, u_y, u_z):$$ Encodes the axis of rotation.

**Intuition Behind the 4 Numbers**

- $$w:$$ Determines how much of the rotation is from the scalar part.
- $$(x, y, z):$$ Encodes the axis and the sine component of the rotation.

Together, these 4 numbers uniquely define any 3D rotation.

**Why Divide the Angle by 2?**

The quaternion rotation formula uses half the angle because of the way quaternions double-cover the sphere of orientations in 3D.  

- A full rotation of $$2\pi$$ radians results in the same orientation as $$0$$, so quaternions naturally handle this symmetry by encoding the angle as $$\frac{\theta}{2}$$.

### Example #1

Suppose we want to rotate an object by $$90^\circ$$ ($$\frac{\pi}{2}$$) around the $$z$$-axis ($$u = (0, 0, 1)$$):

1. **Compute $$w$$:**
   $$
   w = \cos\left(\frac{\theta}{2}\right) = \cos\left(\frac{\pi}{4}\right) = \frac{\sqrt{2}}{2}.
   $$

2. **Compute $$(x, y, z)$$:**
   $$
   (x, y, z) = \sin\left(\frac{\theta}{2}\right) \cdot (u_x, u_y, u_z) = \sin\left(\frac{\pi}{4}\right) \cdot (0, 0, 1) = \frac{\sqrt{2}}{2} \cdot (0, 0, 1).
   $$

3. **The quaternion is:**
   $$
   q = \left[\frac{\sqrt{2}}{2}, \left(0, 0, \frac{\sqrt{2}}{2}\right)\right].
   $$

### Example #2
**Example: Calculating a Quaternion for a 45° Rotation Around an Arbitrary Axis**

Suppose we want to rotate an object by $$45^\circ$$ ($$\frac{\pi}{4}$$ radians) around the axis $$u = (1, 2, 2)$$.

---

**Step 1: Normalize the Rotation Axis**

The axis of rotation $$u = (1, 2, 2)$$ must be a unit vector. Normalize it as follows:

$$
\|u\| = \sqrt{u_x^2 + u_y^2 + u_z^2} = \sqrt{1^2 + 2^2 + 2^2} = \sqrt{9} = 3.
$$

Normalize $$u$$:
$$
\hat{u} = \left(\frac{1}{3}, \frac{2}{3}, \frac{2}{3}\right).
$$

---

**Step 2: Compute the Quaternion Components**

The quaternion representing a rotation of angle $$\theta = 45^\circ = \frac{\pi}{4}$$ around $$\hat{u}$$ is given by:
$$
q = \left[\cos\left(\frac{\theta}{2}\right), \sin\left(\frac{\theta}{2}\right) \cdot \hat{u}\right].
$$

1. **Compute $$\cos\left(\frac{\theta}{2}\right)$$:**
   $$
   \cos\left(\frac{\theta}{2}\right) = \cos\left(\frac{\pi}{8}\right).
   $$
   Using a calculator or trigonometric table:
   $$
   \cos\left(\frac{\pi}{8}\right) \approx 0.9239.
   $$

2. **Compute $$\sin\left(\frac{\theta}{2}\right)$$:**
   $$
   \sin\left(\frac{\theta}{2}\right) = \sin\left(\frac{\pi}{8}\right).
   $$
   Using a calculator or trigonometric table:
   $$
   \sin\left(\frac{\pi}{8}\right) \approx 0.3827.
   $$

3. **Scale the normalized axis $$\hat{u}$$ by $$\sin\left(\frac{\theta}{2}\right)$$:**
   $$
   (x, y, z) = 0.3827 \cdot \left(\frac{1}{3}, \frac{2}{3}, \frac{2}{3}\right) = \left(0.1276, 0.2552, 0.2552\right).
   $$

---

**Step 3: Write the Quaternion**

The quaternion $$q$$ is:
$$
q = \left[\cos\left(\frac{\pi}{8}\right), \sin\left(\frac{\pi}{8}\right) \cdot \hat{u}\right].
$$

Substitute the computed values:
$$
q \approx \left[0.9239, \left(0.1276, 0.2552, 0.2552\right)\right].
$$

---

**Interpretation**

1. **Axis of Rotation:** $$u = (1, 2, 2)$$ (normalized to $$\hat{u} = \left(\frac{1}{3}, \frac{2}{3}, \frac{2}{3}\right)$$).
2. **Rotation Angle:** $$45^\circ$$ ($$\frac{\pi}{4}$$ radians).

The quaternion encodes this rotation compactly:
- The scalar part $$w = \cos\left(\frac{\theta}{2}\right)$$ encodes the "amount" of rotation.
- The vector part $$(x, y, z) = \sin\left(\frac{\theta}{2}\right) \cdot \hat{u}$$ encodes the rotation axis.

The vector part $$(x,y,z)$$ of the quaternion encodes the direction of the rotation axis scaled by $$\sin(\theta/2)$$.
{: .notice--success}

#### Breakdown:

**1. Unit Axis Direction:**
The unit vector $$(u_x, u_y, u_z)$$ represents the direction of the rotation axis in 3D space.

**2. Scaling by Sine Function:**
The $$\sin(\theta/2)$$ factor determines how strongly the axis influences the quaternion.

- When $$\theta = 0$$ (no rotation), $$\sin(0) = 0$$, meaning the vector part is zero.
- As $$\theta$$ increases, $$\sin(\theta/2)$$ grows, increasing the magnitude of the vector part.
- At $$\theta = 180^\circ$$ (or $$\pi$$ radians), $$\sin(\pi/2) = 1$$, meaning the vector part reaches its maximum contribution.


#### Double-Cover Property of Quaternions

**Quaternions and the 4D Hypersphere**

Quaternions are mathematical constructs that extend complex numbers to four dimensions. A quaternion used for rotation, often denoted as:
$$
q = w + x i + y j + z k,
$$
represents a point on a unit 4D hypersphere ($$S^3$$) in quaternion space. The unit quaternion satisfies the constraint:
$$
w^2 + x^2 + y^2 + z^2 = 1.
$$

This hypersphere in 4D space is used to encode rotations in 3D because of the special relationship between quaternions and rotations.

---

**Representing Rotations**

Quaternions encode rotations using an axis-angle representation. A unit quaternion corresponding to a rotation of angle $$\theta$$ around a normalized axis $$v = (x, y, z)$$ is given by:
$$
q = \cos\left(\frac{\theta}{2}\right) + v \sin\left(\frac{\theta}{2}\right),
$$
where:
$$
v = x i + y j + z k,
$$
and $$\theta$$ is the angle of rotation.

The quaternion representation of a rotation only encodes the angle $$\frac{\theta}{2}$$, not the full angle $$\theta$$. This is crucial because:

- A full $$360^\circ$$ rotation in 3D corresponds to a $$180^\circ$$ change in the quaternion angle $$\frac{\theta}{2}$$.
- This ensures that the quaternion space ($$S^3$$) doubles back on itself, creating a double cover of the rotation group $$SO(3)$$, which describes 3D rotations.

---

**Avoiding Redundancy**

Due to the double-cover property:

- Two distinct quaternions, $$q$$ and $$-q$$, represent the same rotation in 3D space.
- This is because negating a quaternion $$q$$ flips all components but leaves the encoded rotation unchanged in 3D.

**Example:**
A rotation of $$\theta = 360^\circ$$ corresponds to $$\frac{\theta}{2} = 180^\circ$$, where the quaternion $$q$$ represents the same rotation as $$-q$$.

---

**Key Implication**

This double-covering ensures that every possible 3D rotation is represented without ambiguity while leveraging the mathematical efficiency of quaternions.

### Quaternion Negation

Quaternion negation refers to negating all components of the quaternion:

$$
q = [w, (x, y, z)] \quad \text{becomes} \quad -q = [-w, (-x, -y, -z)].
$$

---

**Negation Does Not Affect Rotation:**

A quaternion $$q$$ and its negation $$-q$$ represent the same rotation. 

- This is because quaternions double-cover the rotation group $$SO(3)$$, meaning both $$q$$ and $$-q$$ describe the same orientation.

Example:

If 
$$
q = \left[\cos\left(\frac{\theta}{2}\right), \sin\left(\frac{\theta}{2}\right) (u_x, u_y, u_z)\right],
$$
then:
$$
-q = \left[-\cos\left(\frac{\theta}{2}\right), -\sin\left(\frac{\theta}{2}\right) (u_x, u_y, u_z)\right].
$$

Both $$q$$ and $$-q$$ will rotate a vector $$v$$ to the same orientation when applied.

We will explore why this is the case once we go through quaternion multiplication.
{: .notice--warning}

### Quaternion Magnitude
The magnitude $$\|q\|$$ of a quaternion $$q$$ is given by:
$$
\|q\| = \sqrt{w^2 + x^2 + y^2 + z^2}.
$$

In terms of the vector $$\mathbf{v}$$, this can be rewritten as:
$$
\|q\| = \sqrt{w^2 + \|\mathbf{v}\|^2},
$$

where $$\|\mathbf{v}\|$$ is the Euclidean norm (magnitude) of the vector part $$\mathbf{v}$$, defined as:
$$
\|\mathbf{v}\| = \sqrt{x^2 + y^2 + z^2}.
$$

### Quaternion Conjugate

The conjugate of a quaternion is a simple operation that flips the sign of the vector (imaginary) part while keeping the scalar (real) part unchanged.

**Definition**

For a quaternion:
$$
q = w + x i + y j + z k
$$
The conjugate of $$q$$, denoted as $$q^*$$, is:
$$
q^* = w - x i - y j - z k
$$

**Properties**

1. The conjugate reverses the rotation represented by the quaternion.
2. It is analogous to the complex conjugate for complex numbers.

The product of a quaternion and its conjugate gives the square of the quaternion's magnitude:
$$
q \cdot q^* = |q|^2 = w^2 + x^2 + y^2 + z^2.
$$
{: .notice--success}


**Geometric Interpretation**

If $$q$$ represents a rotation, then $$q^*$$ represents the opposite rotation.
{: .notice--success}

For an example a quaternion 
* $$q$$ rotates an object counterclockwise (or on the "positive side") by $$\theta = +60^\circ$$, 
* its conjugate $$q^*$$ rotates the object clockwise (or on the "negative side") by $$\theta = -60^\circ$$.

### Quaternion Inverse

The inverse of a quaternion effectively "undoes" the rotation or transformation represented by the quaternion. For a quaternion $$q$$, the inverse is defined as:

$$
q^{-1} = \frac{q^*}{\|q\|^2}
$$

**Calculation**

Given $$q = w + xi + yj + zk$$:

1. Compute the conjugate:
   $$
   q^* = w - xi - yj - zk
   $$

2. Compute the magnitude squared:
   $$
   \|q\|^2 = w^2 + x^2 + y^2 + z^2
   $$

3. Divide the conjugate by the magnitude squared:
   $$
   q^{-1} = \frac{q^*}{w^2 + x^2 + y^2 + z^2}
   $$

**Special Case for Unit Quaternions**

For a unit quaternion ($$\|q\| = 1$$), the inverse simplifies to just the conjugate:

$$
q^{-1} = q^*
$$

This is why unit quaternions are particularly useful for representing rotations, as their inverse is computationally simple.
{: .notice--success}

### Quaternion Multiplication (Hamilton Product)

#### Quaternion Multiplication Rules

The quaternion multiplication rules are:

$$ i^2 = j^2 = k^2 = ijk = -1 $$

$$ ij = k, \quad ji = -k $$

$$ jk = i, \quad kj = -i $$

$$ ki = j, \quad ik = -j $$

These are similar to the cross-product rules in vector algebra.

Given two quaternions:

$$
q_1 = (w_1, x_1, y_1, z_1), \quad q_2 = (w_2, x_2, y_2, z_2)
$$

We simplify and group terms:

$$
(w_1 w_2 - x_1 x_2 - y_1 y_2 - z_1 z_2) 
+ (w_1 x_2 + x_1 w_2 + y_1 z_2 - z_1 y_2) i $$

$$+ (w_1 y_2 - x_1 z_2 + y_1 w_2 + z_1 x_2) j 
+ (w_1 z_2 + x_1 y_2 - y_1 x_2 + z_1 w_2) k
$$

Their product is given by:

$$
q_1 q_2 =
\begin{bmatrix}
w_1 w_2 - x_1 x_2 - y_1 y_2 - z_1 z_2 \\
w_1 x_2 + x_1 w_2 + y_1 z_2 - z_1 y_2 \\
w_1 y_2 + y_1 w_2 + z_1 x_2 - x_1 z_2 \\
w_1 z_2 + z_1 w_2 + x_1 y_2 - y_1 x_2
\end{bmatrix}
$$

Alternatively, in vector notation:

$$
q_1 q_2 = (w_1 w_2 - \mathbf{v}_1 \cdot \mathbf{v}_2, \quad w_1 \mathbf{v}_2 + w_2 \mathbf{v}_1 + \mathbf{v}_1 \times \mathbf{v}_2)
$$

where:

- $$\mathbf{v}_1 = (x_1, y_1, z_1)$$ and $$\mathbf{v}_2 = (x_2, y_2, z_2)$$ are the vector parts of the quaternions,
- $$\mathbf{v}_1 \cdot \mathbf{v}_2$$ is the dot product,
- $$\mathbf{v}_1 \times \mathbf{v}_2$$ is the cross product.


#### Properties of quaternion multiplication

##### Associativity and Non-Commutativity of Quaternion Multiplication
Quaternion multiplication is **associative**, meaning:

$$
(q_1 q_2) q_3 = q_1 (q_2 q_3)
$$

for any quaternions $$( q_1, q_2, q_3)$$.

However, quaternion multiplication is **not commutative**, meaning:

$$
q_1 q_2 \neq q_2 q_1
$$

in general.

##### Magnitude of Quaternion Product

The magnitude of the product of two quaternions satisfies:

$$
\| q_1 q_2 \| = \| q_1 \| \| q_2 \|
$$

Means the magnitude of a quaternion product is equal to the product of the magnitude

This property ensures that quaternion multiplication preserves the norm.

##### Inverse of a Quaternion Product

The inverse of a product of two quaternions follows the rule:

$$
(q_1 q_2)^{-1} = q_2^{-1} q_1^{-1}
$$

More generally, for a sequence of quaternion multiplications:

$$
(q_1 q_2 \cdots q_{n-1} q_n)^{-1} = q_n^{-1} q_{n-1}^{-1} \cdots q_2^{-1} q_1^{-1}
$$

This property is crucial when working with transformations in quaternion algebra.
{: .notice--success}

#### Using Quaternion Multiplication for Rotations

A vector $$v$$ is rotated using a quaternion $$q$$ by applying the following transformation:

$$
v' = q v q^{-1}
$$

where:

- $$v$$ is treated as a **pure quaternion** $$(0, v_x, v_y, v_z)$$ (notice a zero scalar part).
- $$q$$ is a unit quaternion representing the rotation.
- $$q^{-1}$$ is the inverse (or conjugate, if $$ q $$ is a unit quaternion) of $$ q $$.

This equation describes how quaternion rotation works, preserving orientation without suffering from gimbal lock.

##### Computation Steps

**1. Representing a Vector as a Quaternion**

A 3D vector  $$ v = (v_x, v_y, v_z) $$ is written as a pure quaternion (with a zero scalar part):

$$ v = (0, v_x, v_y, v_z) $$

So, the vector $$ v $$ is treated as:

$$ v = 0 + v_x i + v_y j + v_z k $$

**2. Computing $$ q v q^{-1} $$**

*Step 1: Compute the Quaternion Conjugate (Inverse)*

For a unit quaternion $$ q = (w, x, y, z) $$ the **inverse is just the conjugate:**

$$ q^{-1} = (w, -x, -y, -z) $$

If $$ q $$ is not unit-length, the inverse is:

$$ q^{-1} = \frac{q^*}{\|q\|^2} $$

where $$ q^* = (w, -x, -y, -z) $$ and $$ \|q\|^2 = w^2 + x^2 + y^2 + z^2 $$ For unit quaternions,  $$ \|q\|^2 = 1 $$ so $$ q^{-1} $$ simplifies to the conjugate.

*Step 2: Compute $$ qv $$*

Now, we multiply the quaternion $$ q $$ by the vector $$ v $$ (which is treated as a pure quaternion).
Given:

$$ q = (w, x, y, z) $$

$$ v = (0, v_x, v_y, v_z) $$

Using quaternion multiplication:

$$ qv = (-x v_x - y v_y - z v_z, w v_x + y v_z - z v_y, w v_y + z v_x - x v_z, w v_z + x v_y - y v_x) $$

This gives an intermediate quaternion **(after applying half of the rotation transformation)**.

*Step 3: Compute $$ (qv) q^{-1} $$*

Now, we multiply the intermediate quaternion by $$ q^{-1} $$:

$$ q v q^{-1} = (0, v_x', v_y', v_z') $$

where $$ (v_x', v_y', v_z') $$ is the rotated vector.
After expansion, the formula simplifies to:

$$ v' = v + 2r \times (r \times v) $$

where:

* $$ r = (u_x, u_y, u_z) \sin(\theta / 2) $$ is the scaled rotation axis, and
* $$ r \times v $$ is the cross product.

This matches Rodrigues' rotation formula, proving that quaternion multiplication indeed performs a proper 3D rotation.
{: .notice--success}

### Quaternion “Difference”

In 3D rotations, when we talk about the difference between two quaternions (representing orientations), we are looking for the quaternion that rotates from one orientation to another.

Given two quaternions:

* $$ q_1 $$ represents the starting rotation.
* $$ q_2 $$ represents the target rotation.

We want to find a quaternion $$ q_d $$ that represents the difference, meaning:

$$ q_d = q_1^{-1} q_2 $$

This quaternion $$ q_d $$ tells us how to rotate from $$ q_1 $$ to $$ q_2 $$.

#### Why Use the Inverse?
To "undo" a rotation represented by $$ q_1 $$, we multiply by its inverse, $$ q_1^{-1} $$:

$$ q_d = q_1^{-1} q_2 $$

This works because:

* The inverse of a unit quaternion $$ q = (w, x, y, z) $$ is:

$$ q^{-1} = (w, -x, -y, -z) $$

* When multiplying by the inverse, the result cancels out the original rotation, leaving just the transformation needed to reach $$ q_2 $$.

**Why it works?**

1. If we apply $$ q_2 $$ directly from $$ q_1 $$, we don’t get $$ q_2 $$, we get: $$ q_3 = q_1 q_2 $$
   *  This is because quaternion multiplication compounds rotations rather than transitioning between them.

2. We need a way to rotate from $$ q_1 $$ to exactly $$ q_2 $$, not beyond it.
   * This means we must find the missing rotation that transforms $$ q_1 $$ into $$ q_2 $$.

3. To compensate, we first "undo" $$ q_1 $$ by applying its inverse, $$ q_1^{-1} $$.
   * This brings us back to the original reference frame (identity rotation).
   * Now, when we apply $$ q_2 $$, it moves us exactly to $$ q_2 $$.

4. Thus, the required rotation is: $$ q_d = q_1^{-1} q_2 $$ which represents the exact rotation needed to go from $$ q_1 $$ to $$ q_2 $$.

![Alt Text]({{ site.baseurl }}/assets/maths/math79.png)

### Quaternion Dot Product

The dot product of two quaternions is a scalar value that measures their similarity. It is defined as:

$$ q_1 \cdot q_2 = w_1 w_2 + x_1 x_2 + y_1 y_2 + z_1 z_2 $$

where:

$$ q_1 = (w_1, x_1, y_1, z_1) $$

$$ q_2 = (w_2, x_2, y_2, z_2) $$

This is computed exactly like the dot product of two 4D vectors.

## What Does the Dot Product Tell Us?

The dot product of two unit quaternions (which represent rotations) tells us how similar their orientations are.

- If $$ q_1 \cdot q_2 = 1 $$ → The quaternions are identical (zero rotation difference).
- If $$ q_1 \cdot q_2 = 0 $$ → The quaternions are perpendicular (90° apart in quaternion space).
- If $$ q_1 \cdot q_2 = -1 $$ → The quaternions are opposites (180° apart, representing the same rotation but through opposite paths).

For two **unit quaternions**, the dot product gives: $$ \cos(\theta) $$

where $$ \theta $$ is the half-angle between the two rotations in 4D space. This means:

$$ \theta = \cos^{-1}(q_1 \cdot q_2) $$

This is useful for measuring rotation differences.

### Quaternion Exponentiation

Quaternion exponentiation allows us to scale a rotation represented by a quaternion. This is useful for fractional rotations, smooth interpolation, and motion blending.
For a unit quaternion $$ q $$, exponentiation is defined as:

$$ q^t = e^{t \ln(q)} $$

where:

- $$ t $$ is a scalar,
- $$ \ln(q) $$ is the quaternion logarithm.

#### Why Do We Need Quaternion Exponentiation?

* Fractional Rotations
   If $$ q $$ represents a 90° rotation, then $$ q^{0.5} $$ represents a 45° rotation.

* Smooth Animation & Interpolation
   Quaternion exponentiation helps in SLERP (Spherical Linear Interpolation).

* Rotation Blending
   Allows us to smoothly transition between orientations.

Quaternion exponentiation is given by:

$$ q^t = \cos(t\theta) + \sin(t\theta)(x, y, z) $$

where:
- $$ t $$ is a scalar exponent,
- $$ \theta $$ is the rotation angle associated with the quaternion.
- $$ (x, y, z) $$ is the normalized vector part of $$ q $$.

This formula allows for smooth fractional rotations and interpolation in 3D space.

#### Example

Suppose: $$ q = (w, x, y, z) = (\cos(45^\circ), \sin(45^\circ), 0, 0) $$

This represents a 90° rotation about the X-axis.

**Step 1: Find $$ \theta $$ from $$ w = \cos(\theta / 2) $$** 

$$ \theta = 90^\circ = \frac{\pi}{2} $$

**Step 2: Scale by $$ t = 0.5 $$**

$$ t\theta = \frac{\pi}{4} $$

**Step 3: Compute Exponentiation**

$$ q^{0.5} = \cos(\pi/4) + \sin(\pi/4)(x, y, z) $$

$$ = (0.923, 0.382, 0, 0) $$

This represents a 45° rotation, which is exactly the expected result.


###  Quaternion Interpolation, a.k.a. Slerp

![Alt Text]({{ site.baseurl }}/assets/maths/math80.png)

Spherical Linear Interpolation (SLERP) is a method for **smoothly interpolating between two unit quaternions.** It provides constant angular velocity interpolation, making it ideal for rotations in 3D space.

Given two quaternions $$ q_1 $$ and $$ q_2 $$, SLERP finds an intermediate quaternion $$ q(t) $$ at a fraction $$ t $$ between 0 and 1:

$$ q(t) = \frac{\sin((1 - t)\theta)}{\sin\theta} q_1 + \frac{\sin(t\theta)}{\sin\theta} q_2 $$

where:

- $$ \theta $$ is the angle between $$ q_1 $$ and $$ q_2 $$ in 4D space:
  $$ \theta = \cos^{-1} (q_1 \cdot q_2) $$

- $$ t $$ is the interpolation parameter: $$ (t = 0 $$ gives $$ q_1) $$ and $$ (t = 1 $$ gives $$ q_2) $$

#### Why Use SLERP?

- **Uniform Rotation Speed:** The rotation does not speed up or slow down.
- **Shortest Path Rotation:** It finds the shortest arc between two orientations.
- **Better than Linear Interpolation (LERP):** LERP does not preserve unit quaternions and can cause distortion.

### Step-by-Step Computation

**Step 1: Compute the Dot Product**

The dot product of two unit quaternions tells us their similarity: $$ \cos\theta = q_1 \cdot q_2 $$

If $$ \cos\theta $$ is negative, flip $$ q_2 $$ (since quaternions $$ q $$ and $$ -q $$ represent the same rotation).

**Step 2: Compute the Interpolated Quaternion**

If $$ \theta $$ is small, we can approximate SLERP with Linear Interpolation: $$ q(t) = (1 - t) q_1 + t q_2 $$

Otherwise, use the full SLERP formula:

$$ q(t) = \frac{\sin((1 - t) \theta)}{\sin\theta} q_1 + \frac{\sin(t\theta)}{\sin\theta} q_2 $$

This ensures smooth interpolation.

#### SLERP in Action

Let’s interpolate between:

- $$ q_1 = (1,0,0,0) $$ (Identity rotation)
- $$ q_2 = (0,1,0,0) $$ (180° rotation around X-axis)

Compute: $$ \cos\theta = q_1 \cdot q_2 = 0 $$

So: $$ \theta = 90^\circ $$

Use the SLERP formula at $$ t = 0.5 $$:

$$ q(0.5) = \frac{\sin(0.5 \cdot 90^\circ)}{\sin 90^\circ} q_1 + \frac{\sin(0.5 \cdot 90^\circ)}{\sin 90^\circ} q_2 $$

$$ = \frac{\sin 45^\circ}{\sin 90^\circ} (1,0,0,0) + \frac{\sin 45^\circ}{\sin 90^\circ} (0,1,0,0) $$

$$ = (0.707, 0.707, 0, 0) $$

This result represents a 45° rotation around the X-axis, exactly halfway between $$ q_1 $$ and $$ q_2 $$.

### Advantages and Disadvantages of Quaternions

#### Advantages of Quaternions

1. **No Gimbal Lock :**
Gimbal lock occurs in Euler angles when two rotation axes align, causing the loss of one degree of freedom.  
Quaternions avoid this because they represent rotations in 4D space and don’t suffer from singularities.

2. **More Compact Than Matrices :**
A quaternion stores only 4 values $$ (w, x, y, z) $$, while a rotation matrix requires 9 values (a $$ 3 \times 3 $$ matrix).  
This saves memory and improves computational efficiency.

3. **Fast and Stable Interpolation (SLERP) :**
Spherical Linear Interpolation (SLERP) provides smooth, constant-speed interpolation between rotations.  
Linear interpolation (LERP) of Euler angles causes distortions, while SLERP maintains natural movement.

4. **Computationally Efficient Rotation :**
Applying a quaternion rotation to a vector is faster than using a $$ 3 \times 3 $$ matrix.  
Instead of matrix multiplication, we use the quaternion sandwich product: $$ v' = q v q^{-1} $$
which is more efficient for composite rotations.

5. **Easy to Normalize :**
Floating-point errors can cause rotation matrices to lose their orthogonality.  
Quaternions can be renormalized easily, keeping them stable in iterative computations.

6. **Faster Composition of Rotations :**
To combine two rotations, we use quaternion multiplication, which is cheaper than multiplying two rotation matrices.

---

#### Disadvantages of Quaternions

1. **Harder to Understand Intuitively :**
Unlike Euler angles (pitch, yaw, roll), quaternions don’t directly correspond to human-perceived rotation angles.  
Many developers struggle with interpreting and debugging quaternions.

2. **More Complex Arithmetic :**
Quaternion multiplication follows non-commutative rules: $$ q_1 q_2 \neq q_2 q_1 $$
Quaternion exponentiation and logarithms (used for interpolation) involve trigonometric functions, making them more computationally expensive.

3. **Not Suitable for Direct User Input :**
Euler angles are easier for manual input and keyframe animations.  
If a user wants to enter a specific rotation manually, quaternions are not intuitive.

4. **More Expensive to Convert to Rotation Matrices :**
Some graphics engines (like OpenGL and DirectX) use rotation matrices internally.  
Converting a quaternion to a rotation matrix takes extra computation compared to directly using matrices.

5. **Can Have Ambiguous Representations :**
A quaternion $$ q $$ and its negation $$ -q $$ represent the same rotation.  
This can cause issues in interpolation if not handled properly.

---

#### When to Use Quaternions vs. Other Methods

| **Method**           | **Best Use Case** |
|----------------------|------------------|
| **Quaternions**      | Rotations without gimbal lock, animation blending, physics, and smooth interpolation. |
| **Euler Angles**     | Simple, human-readable rotations (e.g., specifying rotation in UI or keyframes). |
| **Rotation Matrices** | Transforming many vectors, hardware-accelerated graphics rendering. |