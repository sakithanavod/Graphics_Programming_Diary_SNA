---
title: "Multiple Coordinate Spaces"
date: 2024-05-12 12:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
---
{% include mathJax.html %}

This chapter gives some examples of common coordinate spaces that are used for graphics and games.

<!--more-->

## Why Bother with Multiple Coordinate Spaces?

For an example. a certain point a, we may not know the coordinates of a in the “world” coordinate system. But we may be able to express a relative to some *other* coordinate system.

## Some Useful Coordinate Spaces

### World Space

The *world coordinate system* is a special coordinate system that establishes the “global” reference frame for all other coordinate systems to be specified. 

In other words, we can express the position of other coordinate spaces in terms of the world coordinate space, but we cannot express the world coordinate space in terms of any larger, outer coordinate space.
{: .notice--primary}

### Object Space
*Object space* is the coordinate space associated with a particular object. Every object has its own independent object space.

When an object moves or changes orientation, the object coordinate space associated with that object is carried along with it, so it moves or changes orientation too.

For example, If we were to ask you to “take one step forward,” we are giving you an instruction in your object space. We have no idea which way you will move in absolute terms. Some of you will move north, some south because concepts such as “forward,” “back,” “left,” and “right” are meaningful in object coordinate space. (if it was like “go east” then it's expressed in world space)
{: .notice--primary}

### Camera Space
One especially important example of an object space is *camera space*, which is the object space associated with the viewpoint used for rendering.

In camera space, the camera is at the origin, with +x pointing to the right, +z pointing forward (into the screen, the direction the camera is facing),and +y pointing “up.” (Not “up” with respect to the world, “up” with respect to the top of the camera.)

OpenGL tradition is right-handed, with −z pointing into the screen and +z coming out of the screen towards the viewer.
{: .notice--warning}

![Alt Text]({{ site.baseurl }}/assets/maths/math30.png)

Note carefully the differences between camera space, which is a 3D space, and screen space, which is a 2D space. The mapping of camera space coordinates to screen-space coordinates involves an operation known as projection.
{: .notice--primary}

### Upright Space
An object’s upright space is, in a certain sense, “halfway” between world space and its object space.

The axes of upright space are parallel with the axes of world space, but the origin of upright space is coincident (same as) with the origin of object space.
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/maths/math31.png)

**Why is upright space interesting?**

* To transform a point between object space and upright space requires only rotation. **because origin is same for both upright space and object space.**
* To transform a point between upright space and world space requires only a change of location (usually called as a translation) **because The axes of upright space are parallel with the axes of world space.** 

![Alt Text]({{ site.baseurl }}/assets/maths/math32.png)

## Basis Vectors and Coordinate Space Transformations
sometimes certain questions can be answered only in particular coordinate spaces. When the question is best asked in one space, and the information we need in order to answer that question is known in a different space, we have a problem to solve.

Example: suppose that we wish to render an image of the robot picking up the sandwich, and that the scene is illuminated by the light mounted on her shoulder. We know the position of the light within the robot’s object space, but to properly light the scene, we must know the position of the light in world space.
{: .notice--primary}

Therefore, We need to transform the position from world space to object space or from object space to world space. and we call this *coordinate space transformation*
{: .notice--success}

### Understanding Coordinate Space Transformations With an Example
*Imagine a scenario where,*

Our goal is to transform the vertices of the model from their “home” location to some new location according to the desired position and orientation of the robot based on the following sketch. (and currently robot is at world origin location)

![Alt Text]({{ site.baseurl }}/assets/maths/math33.png)

To achieve this, we can first rotate her clockwise $$120^{\circ}$$ Then we translate 18 ft east and 10 ft north, which according, to our conventions, is a 3D displacement of [18, 0, 10].

![Alt Text]({{ site.baseurl }}/assets/maths/math34.png)

But why rotate first then translate? Can't we just translate first then rotate?
{: .notice--warning}

The answer is **NO**, because,

When we rotate the object first, the center of rotation is the origin. Rotation about the origin and translation are two primitive tools we have at our disposal.

If we rotate second, then that rotation will occur about a point that is *not* the origin. Rotation about the origin is a *linear transform*, but rotation about any other point is an *affine transform*.

Linear Transformations 
![Alt Text]({{ site.baseurl }}/assets/maths/math35.png)

Affine Transform
![Alt Text]({{ site.baseurl }}/assets/maths/math36.png)

So how to perform a rotation about an arbitrary point? we have to do following sequence of transformations:

1. Translate the Arbitrary Point to the Origin:
    - This step involves moving the point around which you want to rotate. (let's call this point P)

2. Rotate Around the Origin:
    - Now that the point P is at the origin, apply the rotation.

3. Translate Back to the Original Location:
    - After rotating, translate the points back so that the origin moves back to P.

## Basis Vectors
Basis vectors are a set of vectors that form the basis for a vector space. In three-dimensional space, a set of three linearly independent vectors typically forms the basis for describing *any other vector in that space*. These basis vectors are usually orthogonal (perpendicular) to each other and have a length of 1 unit.

In a Cartesian coordinate system, the basis vectors typically align with the axes of the coordinate system. In three-dimensional Cartesian space, the basis vectors are usually denoted as i,j, and k representing the unit vectors along the x, y, and z axes, respectively.

Here's a brief overview of each basis vector in a Cartesian coordinate system:

* i: The unit vector along the positive x-axis.
* j: The unit vector along the positive y-axis.
* k: The unit vector along the positive z-axis.

These basis vectors are mutually orthogonal, meaning they are perpendicular to each other. Additionally, any vector in three-dimensional space can be expressed as a linear combination of these basis vectors.

For example, a vector v in three-dimensional space can be written as:

$${v} = {a}.{i} + {b}. {j} + {c}. {k}$$

where a, b, and c are scalar coefficients representing the components of the vector along each basis vector.

The coordinates of i, j, and k are *always equal* to [1, 0, 0], [0, 1, 0],and [0, 0, 1], respectively, when expressed using the coordinate space for which they are the basis, but relative to some other basis they will have arbitrary coordinates.
{: .notice--success}

## What is a Vertex?
- *Point in Space*: A vertex is a point in space defined by its coordinates, usually represented as (x,y,z) in a 3D Cartesian coordinate system.
- *Geometric Primitive*: In geometric terms, a vertex is a fundamental unit of geometric primitives such as points, lines, and polygons. For example, in a polygon, vertices define the corners or endpoints of the shape.
- *Attributes*: A vertex may also carry additional attributes such as color, texture coordinates, normals (for shading), or other custom data.

In a 3D model of a cube, each corner of the cube would be represented by a vertex. The cube would be defined by eight vertices, each with its own (x,y,z) coordinates.
{: .notice--primary}

## Object Transformation Matrix
An object transformation matrix is a 4x4 matrix used in computer graphics to transform the vertices of an object from its local (object) coordinate space to the world coordinate space. This matrix encapsulates the translation, rotation, and scaling operations applied to the object.

### Constructing the Object Transformation Matrix

![Alt Text]({{ site.baseurl }}/assets/maths/math38.png)

Let's say that object $${N}$$ is scaled, rotate and translated by some amount and above diagram shows the end result of the transformation of the object within world space. Based on that we can construct *"Object Transformation Matrix"*

1. Calculate Scaling Matrix $${S}$$
2. Calculate Rotation Matrix $${R}$$
3. Calculate Translation Matrix $${T}$$

Therefore, The combined transformation matrix $${M}$$ is obtained by multiplying the individual matrices in the order of scaling, rotation, and translation:

$${M} = {T}.{R}.{S}$$

### Using the Object Transformation Matrix
To transform a vertex ($$v_{\text{model}}$$) from *object space to world space*, you multiply it by the object transformation matrix:

$$v_{\text{world}} = {M}.v_{\text{model}}$$

To transform a vertex from world space back to object space, you need to use the inverse of the object's transformation matrix. This process effectively reverses the translation, rotation, and scaling applied to the vertex, converting its coordinates from the global coordinate system back to the local coordinate system of the object. ($$v_{\text{model}} = {M^{-1}}.v_{\text{world}}$$)
{: .notice--success}

## Overview of Vertex Transformation in Rendering
In the context of rendering a 3D object, each vertex's position needs to be transformed using the transformation matrix before rendering it on the screen. This transformation typically happens in the vertex shader on the GPU. Here’s how the process generally works:

1. Model (Object) Space: Vertices are initially defined in the model's local coordinate system.
2. World Space: Vertices are transformed from model space to world space using the object's transformation matrix.
3. View (Camera) Space: Vertices are then transformed from world space to view space using the view matrix.
4. Clip Space: Finally, vertices are transformed from view space to clip space using the projection matrix.

### Steps Involved
1. Obtain Vertex Position:
- Each vertex’s position in model space is obtained from the mesh data. 

2. Apply Transformation Matrices:
- Model Matrix (M): Transforms vertices from model space to world space.
- View Matrix (V): Transforms vertices from world space to view space.
- Projection Matrix (P): Transforms vertices from view space to clip space.

### Vertex Shader Example
```
#version 330 core

// Input attributes from the vertex buffer
layout(location = 0) in vec3 aPosition;  // Vertex position in model space
layout(location = 1) in vec3 aNormal;    // Vertex normal

// Uniform matrices
uniform mat4 uModelMatrix;       // Model matrix
uniform mat4 uViewMatrix;        // View matrix
uniform mat4 uProjectionMatrix;  // Projection matrix

// Output to the fragment shader
out vec3 vNormal;  // Transformed normal

void main()
{
    // Calculate the model-view-projection matrix
    mat4 modelViewProjectionMatrix = uProjectionMatrix * uViewMatrix * uModelMatrix;
    
    // Transform the vertex position from model space to clip space
    gl_Position = modelViewProjectionMatrix * vec4(aPosition, 1.0);

    // Transform the normal to view space (assuming no non-uniform scaling)
    vNormal = (uModelMatrix * vec4(aNormal, 0.0)).xyz;
}

```
### Matrix Multiplication Order
The order of multiplication is crucial:

1. Model Matrix: $${v_{\text{world}} = {M}.v_{\text{model}} }$$
2. View Matrix: $${v_{\text{view}} = {V}.v_{\text{world}}}$$
3. Projection Matrix: $${v_{\text{clip}} = {V}.v_{\text{view}}}$$

Combined in the vertex shader as:

 $${v_{\text{clip}} = {P}.{V}.{M}.v_{\text{model}}}$$