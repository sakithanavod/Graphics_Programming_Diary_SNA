---
title: "Geometric Primitives"
date: 2025-02-21 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

In computer graphics and computational geometry, we use different strategies to describe geometric shapes.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Representation Techniques
In computer graphics and computational geometry, we use different strategies to describe geometric shapes. 
Each approach has advantages and is suited for specific applications such as rendering, simulation, 
collision detection, and modeling.

### Implicit Representation
An implicit representation defines a shape using a mathematical function that evaluates to zero on the surface of the shape, 
negative inside, and positive outside.

#### Definition
An implicit surface is defined by a function:

$$ f(x, y, z) = 0 $$

where:

- If $$ f(x, y, z) < 0 $$, the point is **inside** the shape.
- If $$ f(x, y, z) > 0 $$, the point is **outside** the shape.
- If $$ f(x, y, z) = 0 $$, the point is **on** the surface.

#### Example: Sphere

For a unit sphere centered at the origin, the implicit equation is:

$$ f(x, y, z) = x^2 + y^2 + z^2 - 1 = 0 $$

This equation defines all points at a distance of 1 from the origin.
{: .notice--success}

##### Implicit Equation for a Sphere Centered at $$ (h, k, l) $$

$$
(x - h)^2 + (y - k)^2 + (z - l)^2 = r^2
$$

where:
- $$ (h, k, l) $$ is the center of the sphere.
- $$ r $$ is the radius of the sphere.

**Point Classification**

- If a point $$ (x, y, z) $$ satisfies:
  $$
  (x - h)^2 + (y - k)^2 + (z - l)^2 = r^2
  $$
  then it lies **on the sphere**.

- If a point $$ (x, y, z) $$ satisfies:
  $$
  (x - h)^2 + (y - k)^2 + (z - l)^2 < r^2
  $$
  then it lies **inside the sphere**.

- If a point $$ (x, y, z) $$ satisfies:
  $$
  (x - h)^2 + (y - k)^2 + (z - l)^2 > r^2
  $$
  then it lies **outside the sphere**.

#### Applications
1. **Ray Tracing**: Implicit surfaces are useful in ray tracing since solving $$ f(x, y, z) = 0 $$ determines the exact intersection points of rays with the surface.
2. **Constructive Solid Geometry (CSG)**: Boolean operations (union, intersection, subtraction) can be efficiently applied using implicit functions.
3. **Collision Detection**: Checking whether a point is inside an object is simple; just evaluate $$ f(x, y, z) $$ and check if it is negative.

#### **Limitations**
- **Rendering Challenges**: Implicit functions may be hard to render directly; we need specialized techniques like **Marching Cubes** to convert them into meshes.
- **Complexity**: Defining complex shapes requires **non-trivial** implicit functions.

### Parametric Representation
A parametric representation expresses a shape in terms of one or more independent parameters.

#### Definition
Instead of using an implicit function like:

$$ f(x, y, z) = 0, $$

parametric equations express coordinates as functions of one or two parameters:

$$ x = f_1(u, v), \quad y = f_2(u, v), \quad z = f_3(u, v) $$

where $$ u $$ and $$ v $$ are parameters.

**Example: Sphere**

A sphere can be described in spherical coordinates using two parameters: 
**longitude** $$ \theta $$ and **latitude** $$ \phi $$:

$$
x = r \cos\theta \sin\phi
$$

$$
y = r \sin\theta \sin\phi
$$

$$
z = r \cos\phi
$$

where:

- $$ 0 \leq \theta < 2\pi $$ (full rotation around the vertical axis),
- $$ 0 \leq \phi \leq \pi $$ (from north pole to south pole).


#### Applications
1. **Curved Surfaces**: Parametric equations allow smooth representation of curves and surfaces, like **Bézier curves** and **NURBS**.
2. **Texture Mapping**: **UV mapping** uses parametric equations to map 2D textures onto 3D surfaces.
3. **Animation & Motion Paths**: Movements of objects are often described using parametric equations.

#### Limitations
- **Point Containment**: Hard to check whether a given point is inside or outside the shape.
- **Ray Tracing**: Parametric surfaces can be **difficult to ray-trace** directly, often requiring numerical solutions.

### Explicit Representation

An **explicit function** defines one coordinate in terms of the others.

#### Definition
An explicit function expresses **one variable as a function of the other two**:

$$ z = f(x, y) $$

This is useful for surfaces that can be written as **height maps**.

**Example: Sphere**

A sphere **cannot** be fully expressed in explicit form, but its **upper hemisphere** can be written as:

$$
z = \sqrt{1 - x^2 - y^2}
$$

This equation gives the **height** $$ z $$ for any given $$ (x, y) $$, but it **cannot** represent shapes with overhangs (e.g., a full sphere).

#### Applications
1. **Height Maps**: Used in terrain generation, where the landscape height is given as:

   $$ z = f(x, y) $$

2. **Function Plotting**: Used in 3D graphs of mathematical functions.

3. **Simple Surfaces**: Suitable for **planes and simple curved surfaces**.

#### **Limitations**
- **Cannot represent** shapes with multiple $$ z $$-values for the same $$ (x, y) $$.
- **Difficult to extend** beyond simple surfaces (e.g., does not handle overhangs well).

### Mesh Representation (Discrete)

A **mesh** is a collection of **discrete points (vertices)** connected by edges and faces to approximate a shape.

#### Definition
A mesh consists of:

- **Vertices**: Points in space.
- **Edges**: Line segments connecting vertices.
- **Faces**: Polygons (usually **triangles** or **quads**) forming the surface.

**Example: Sphere**

A sphere can be **approximated** using:

1. **Tessellation**: Dividing a basic shape (like an **icosahedron**) into smaller **triangles**.
2. **Subdivision Surfaces**: Refining a **coarse shape** into a **smoother one**.

#### Applications
- **Real-Time Rendering**: Used in **game engines** (Unreal, Unity) for **efficient** rendering.
- **3D Modeling**: Used in **CAD software, Blender, Maya** for creating objects.
- **Physics & Collision Detection**: Used in simulations where **exact math-based** representations are **too expensive**.

#### Limitations
- **Approximates smooth surfaces** with **flat polygons**.
- **Higher detail** requires **more vertices**, increasing **memory usage** and **computational cost**.

### Comparison of Representations

| Representation | Pros | Cons |
|---------------|------|------|
| **Implicit** | Easy point containment, useful for ray tracing and CSG | Hard to render directly, complex functions for complex shapes |
| **Parametric** | Good for smooth surfaces, useful for animation and texture mapping | Hard for collision detection, limited by parameter range |
| **Explicit** | Simple for height maps and plotting functions | Cannot represent overhangs or multi-valued surfaces |
| **Mesh** | Efficient for rendering and simulations, widely used in graphics | Only an approximation, requires large memory for high detail |

### Conclusion

Different representations serve different purposes:

- **Implicit forms** are useful in **physics and ray tracing**.
- **Parametric equations** are great for **animation and curved surfaces**.
- **Explicit equations** work well for **height maps**.
- **Meshes** are essential in **modern 3D graphics**.

## Lines and Rays
Now for some specific types of primitives. We begin with what is perhaps the most basic and important one of all: the linear segment. 
Let’s meet the three basic types of linear segments, and also clarify some terminology. In classical geometry, the following definitions are used:

* **Line** - extends infinitely in two directions.
* **Line Segment** -  finite portion of a line that has two endpoints.
* **Ray** -  “half” of a line that has an origin and extends infinitely in one direction.

![Alt Text]({{ site.baseurl }}/assets/maths/math81.png)

### Rays
