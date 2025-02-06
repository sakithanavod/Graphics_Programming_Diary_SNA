---
title: "Rotation in Three Dimensions"
date: 2024-12-25 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

This chapter tackles the difficult problem of describing the orientation of an object in 3D. It also discusses the closely related concepts of rotation and angular displacement.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## What Exactly is “Orientation”?
Intuitively, we know that the “orientation” of an object basically tells us what direction the object is facing. However, “**orientation**” is not exactly the same as “**direction.**”

For example, a vector has a direction, but not an orientation. The difference is that when a vector points in a certain direction, you can twist the vector along its length, and there is no real change to the vector, since a vector has no thickness or dimension other than its length.

![Alt Text]({{ site.baseurl }}/assets/maths/math77.png)

In contrast to a simple vector, consider an object, such as a jet, facing a certain direction. If we twist the jet in the same way that we twisted the vector, we will change the orientation of the jet.

![Alt Text]({{ site.baseurl }}/assets/maths/math78.png)

Orientation definition : Orientation refers to the angular disposition of an object in space. It not only defines "where" something is pointing but also how it is rotated around that direction vector.
{: .notice--success}

## Matrix Form
A rotation matrix provides a mathematical framework to describe how an object is oriented in 3D space relative to a reference frame. Orientation goes beyond simple direction, including the rotational alignment of the object along and around its axes.

**Role of Rotation Matrices in Orientation**

A rotation matrix specifies how to transform a vector or coordinate system from one orientation to another. It captures:

1. **Alignment:** Which way the object’s local axes (e.g., forward, up, and right) are aligned in the world or another reference frame.
2. **Twist Around Axes:** Rotational position about the object’s local forward (or another principal) axis.

**Examples:**
- A camera's orientation defines where it is looking (direction) and how it is tilted (roll).
- A rigid body's orientation tells you not only where its front is pointing but also whether it is upright or rotated.

---

**Mathematics of Rotation Matrices for Orientation**

1. **Transformation of Axes:**
   A rotation matrix $${R}$$ transforms the object’s local coordinate axes to the global coordinate frame:
   $$
   \begin{bmatrix} 
   x_{\text{world}} \\ 
   y_{\text{world}} \\ 
   z_{\text{world}} 
   \end{bmatrix}
   = R \cdot 
   \begin{bmatrix} 
   x_{\text{local}} \\ 
   y_{\text{local}} \\ 
   z_{\text{local}} 
   \end{bmatrix}.
   $$
   Each column of $${R}$$ represents the direction of one of the local axes in the global frame.

2. **Basis Vectors:**
   The columns of $${R}$$ are unit vectors that define the orientation of the object’s local axes:
   - The first column is the transformed right vector.
   - The second column is the transformed up vector.
   - The third column is the transformed forward vector.

   **For instance:**
   $$
   R = 
   \begin{bmatrix} 
   r_x & u_x & f_x \\ 
   r_y & u_y & f_y \\ 
   r_z & u_z & f_z 
   \end{bmatrix},
   $$
   where $${r}$$, $${u}$$, and $${f}$$ represent the right, up, and forward vectors of the object in world space.

---

**Converting Between Frames:**

1. **To World Frame:**
   Use $${R}$$ to transform local vectors to the world frame:
   $$
   \mathbf{v}_{\text{world}} = R \cdot \mathbf{v}_{\text{local}}.
   $$

2. **To Local Frame:**
   Use the transpose (or inverse) of $${R}$$ to transform world vectors to the local frame:
   $$
   \mathbf{v}_{\text{local}} = R^T \cdot \mathbf{v}_{\text{world}}.
   $$

---

**Using Rotation Matrices to Describe Orientation**

1. **Object Alignment:**
   The rotation matrix provides a complete description of how an object is rotated from its reference alignment.
   - A rotation matrix aligned with the identity matrix ($${R = I}$$) means the object is in its default orientation.
   - Any other rotation matrix specifies how the object’s axes are rotated relative to this default.

2. **Changing Orientation:**
   To rotate an object by a specific angle around an axis, use a rotation matrix for that axis:
   $$
   R_{\text{new}} = R_{\text{axis}}(\theta) \cdot R_{\text{current}}.
   $$
   This updates the object’s orientation by combining its current orientation with the desired rotation.

3. **Combining Rotations:**
   Concatenate multiple rotations to describe a complex orientation:
   $$
   R_{\text{total}} = R_3 \cdot R_2 \cdot R_1.
   $$

4. **Orientation Relative to Another Object:**
   If $${R_a}$$ is the rotation matrix of object $${A}$$ and $${R_b}$$ is the rotation matrix of object $${B}$$:
   $$
   R_{\text{relative}} = R_b^{-1} \cdot R_a.
   $$
   This gives the orientation of $${A}$$ relative to $${B}$$.


### Advantages of Matrix Form
* Complete Information: Encodes full 3D orientation, including twist around the principal axis.
* Easy Transformation: Can directly transform vectors between frames.
* Chainable: Multiplication of matrices allows chaining of rotations.
* Format used by graphics API : Can be directly used when working with graphic API's

### Disadvantages of Matrix Form
* Memory Overhead: Requires 3×3=9 elements to store.
* Numerical Drift: Repeated transformations can lead to loss of orthogonality; requires re-orthogonalization in long computations.
* Interpolation Challenges: Linear interpolation of matrices doesn’t correspond to smooth rotation (for this, quaternions are better).

## Euler Angles
Euler angles are a method for representing the orientation of an object in 3D space by describing its rotation as three sequential angular displacements about specific axes. These rotations are typically relative to a reference coordinate system.

### What Are Euler Angles?
**Definition:**  
Euler angles are a set of three angles $$(\alpha, \beta, \gamma)$$ that represent rotation about the coordinate axes.

**Sequence:**  
The angles are applied in a specified order, such as $$XYZ$$, $$ZYX$$, or $$ZXY$$, depending on the convention used.  
Each rotation corresponds to a rotation about one of the primary axes ($$X, Y, Z$$).

**Purpose:**  
Euler angles provide an intuitive way to describe and manipulate the orientation of an object.

**For example (In a right-handed coordinate system where z-axis points up):**
1. Rotate about the $$Z$$-axis by $$\gamma$$ (yaw).
2. Rotate about the $$Y$$-axis by $$\beta$$ (pitch).
3. Rotate about the $$X$$-axis by $$\alpha$$ (roll).

**Euler Angles and Orientation**

Euler angles describe the orientation of an object relative to a reference frame. The orientation can be visualized as the cumulative effect of three rotations:

- **Yaw ($$\gamma$$):** Rotation about the vertical axis (e.g., $$Z$$).
- **Pitch ($$\beta$$):** Rotation about the side axis (e.g., $$Y$$).
- **Roll ($$\alpha$$):** Rotation about the forward axis (e.g., $$X$$).

By combining these rotations, the Euler angles fully describe how an object's local coordinate system is oriented relative to the global coordinate system.

### Rotation Matrix from Euler Angles

A rotation matrix can be constructed from Euler angles using the specified order of rotations. For an $$XYZ$$ order:

1. **Rotation about the $$X$$-axis:**
   $$
   R_x(\alpha) =
   \begin{bmatrix}
   1 & 0 & 0 \\
   0 & \cos\alpha & -\sin\alpha \\
   0 & \sin\alpha & \cos\alpha
   \end{bmatrix}.
   $$

2. **Rotation about the $$Y$$-axis:**
   $$
   R_y(\beta) =
   \begin{bmatrix}
   \cos\beta & 0 & \sin\beta \\
   0 & 1 & 0 \\
   -\sin\beta & 0 & \cos\beta
   \end{bmatrix}.
   $$

3. **Rotation about the $$Z$$-axis:**
   $$
   R_z(\gamma) =
   \begin{bmatrix}
   \cos\gamma & -\sin\gamma & 0 \\
   \sin\gamma & \cos\gamma & 0 \\
   0 & 0 & 1
   \end{bmatrix}.
   $$

4. **Combined Rotation Matrix for $$XYZ$$ order:**
   $$
   R = R_x(\alpha) \cdot R_y(\beta) \cdot R_z(\gamma).
   $$


### Advantages of Euler Angles
**Intuitiveness:**

- Easy to understand and visualize.
- Aligns with human intuition for describing rotations (e.g., yaw, pitch, roll).

**Compact Representation:**

- Requires only three parameters to describe orientation.

**Direct Application:**

- Suitable for UI sliders and user inputs to control object orientation.

### Disadvantages of Euler Angles

#### Aliasing

Euler angles are typically restricted to ensure that each orientation is represented uniquely within a specified range. These restrictions prevent ambiguity and ensure consistent calculations, particularly when converting between rotation representations

**Yaw, Pitch, Roll**

1. **Yaw ($$\psi$$):**  
   - Rotation about the $$Z$$-axis.  
   - Range: $$[-\pi, \pi]$$ or $$[0, 2\pi]$$.

2. **Pitch ($$\theta$$):**  
   - Rotation about the $$Y$$-axis.  
   - Range: $$[-\pi/2, \pi/2]$$.  
   - Restricted to prevent gimbal lock (critical pitch angles cause loss of a degree of freedom).

3. **Roll ($$\phi$$):**  
   - Rotation about the $$X$$-axis.  
   - Range: $$[-\pi, \pi]$$ or $$[0, 2\pi]$$.


#### Gimbal Lock

[Gimbal Lock Visual Representation](https://www.youtube.com/watch?v=zc8b2Jo7mno)

Gimbal lock happens when two of the three rotation axes in a system align, effectively reducing the system's ability to distinguish rotations in all three dimensions. (Example : When one rotation (e.g., pitch) aligns two axes (e.g., yaw and roll), these two axes collapse into one.)

It causes the system to "lose" a degree of freedom, meaning certain orientations cannot be represented or distinguished. This results in unpredictable or constrained behavior when applying rotations.

##### Effects of Gimbal Lock
* **Loss of Degrees of Freedom:** Cannot represent all possible rotations.
* **Unintuitive Rotations:** Rotating about one axis can unintentionally affect another axis.
* **Numerical Instability:** Interpolating or integrating rotations near gimbal lock can cause erratic behavior.

We can use quaternions do not suffer from gimbal lock because they represent rotation in 4D space, avoiding sequential rotations.
{: .notice--success}