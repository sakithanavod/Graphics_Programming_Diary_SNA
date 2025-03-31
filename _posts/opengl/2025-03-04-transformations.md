---
title: "Transformations"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---
{% include mathJax.html %}

Matrices are very powerful mathematical constructs that seem scary at first, but once you'll grow accustomed to them they'll prove extremely useful.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## GLM
GLM stands for OpenGL Mathematics and is a header-only library, which means that we only have to include the proper header files and we're done; no linking and compiling necessary. GLM can be downloaded from their website. Copy the root directory of the header files into your includes folder and let's get rolling.

[Link](https://glm.g-truc.net/0.9.8/index.html)

Let's see if we can put our transformation knowledge to good use by translating a vector of (1,0,0) by (1,1,0) (note that we define it as a glm::vec4 with its homogeneous coordinate set to 1.0:

```cpp
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);  // A point at (1, 0, 0) with w = 1 (homogeneous)
glm::mat4 identity = glm::mat4(1.0f);      // Identity 4x4 matrix

trans = glm::translate(identity, glm::vec3(1.0f, 1.0f, 0.0f));  // Apply translation by (1, 1, 0)

/*
*
*           [1 0 0 1]
* trans =   [0 1 0 1]
*           [0 0 1 0]
*           [0 0 0 1]
*/

vec = trans * vec;  // Multiply transformation matrix with the vector

std::cout << vec.x << vec.y << vec.z << std::endl; // 2.0 1.0 0.0
```

Let's take a look at bit more complicated calculation:

the **pivot-centered rotation** -  To rotate an object around its own local pivot point (which is not at the origin), you temporarily move the object to the origin, rotate it, and then move it back.

Why This Is Needed?

Matrix transformations in OpenGL/GLM (and most graphics APIs) always rotate around the origin. So, if your object is not at the origin, any rotation will behave like it's swinging around the world's origin, not its own local center.

Step-by-Step: Rotate Around a Local Point 

1. **Translate the object so the pivot moves to the origin:**

   $$
   T_1 = \text{translate by } -P
   $$

2. **Apply your rotation:**

   $$
   R = \text{rotation matrix}
   $$

3. **Translate back to the original position:**

   $$
   T_2 = \text{translate by } +P
   $$

```cpp
glm::vec3 pivot(3.0f, 2.0f, 0.0f); // local rotation center
float angle = glm::radians(90.0f);

// Step 1: move to origin
glm::mat4 T1 = glm::translate(glm::mat4(1.0f), -pivot);

// Step 2: rotate (around Z in this case)
glm::mat4 R = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));

// Step 3: move back to original pivot location
glm::mat4 T2 = glm::translate(glm::mat4(1.0f), pivot);

// Final model matrix (applies from right to left)
glm::mat4 model = T2 * R * T1;

```

## How do we get the transformation matrix to the shaders

The next big question is: how do we get the transformation matrix to the shaders? We shortly mentioned before that GLSL also has a mat4 type. So we'll adapt the vertex shader to accept a mat4 uniform variable and multiply the position vector by the matrix uniform:

```cpp
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
  
uniform mat4 transform;

void main()
{
   // Always put the matrix on the left and the vector on the right when multiplying:
   // Otherwise result would be a row vector which opengl does not support
   // Even if it compiles in some shader versions or GPU drivers, it won’t produce what you want. 
   // It flips the whole transformation
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
} 
```

GLSL also has mat2 and mat3 types that allow for swizzling-like operations just like vectors. All the aforementioned math operations (like scalar-matrix multiplication, matrix-vector multiplication and matrix-matrix multiplication) are allowed on the matrix types. Wherever special matrix operations are used we'll be sure to explain what's happening.
{: .notice--primary}

Then we need to pass the transformation matrix to the shader though:

```cpp
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```

Parameters:

* The first argument should be familiar by now which is the uniform's location. 
* The second argument tells OpenGL how many matrices we'd like to send, which is 1. 
* The third argument asks us if we want to transpose our matrix, that is to *swap the columns and rows*. OpenGL developers often use an internal matrix layout called **column-major** ordering which is the default matrix layout in GLM so there is no need to transpose the matrices; we can keep it at GL_FALSE. 
* The last parameter is the actual matrix data - but GLM stores their matrices' data in a way that doesn't always match OpenGL's expectations so we first convert the data with GLM's built-in function `value_ptr` - this gets a `float*` pointer to the start of your glm::mat4 matrix data.

## Let's rotate the container over time

Let's get a little more funky and see if we can rotate the container over time, and for fun we'll also reposition the container at the bottom-right side of the window. To rotate the container over time we have to update the transformation matrix in the render loop because it needs to update each frame. We use GLFW's time function to get an angle over time:

```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
```

Keep in mind that in the previous case we could declare the transformation matrix anywhere, but now we have to create it every iteration to continuously update the rotation. This means we have to re-create the transformation matrix in each iteration of the render loop. Usually when rendering scenes we have several transformation matrices that are re-created with new values each frame.

Here we first rotate the container around the origin (0,0,0) and once it's rotated, we translate its rotated version to the bottom-right corner of the screen. Remember that the **actual transformation order should be read in reverse:** 

even though in code we first translate and then later rotate, the actual transformations first apply a **rotation and then a translation**. 

Understanding all these combinations of transformations and how they apply to objects is difficult to understand. Try and experiment with transformations like these and you'll quickly get a grasp of it.

When you run this code, the quad will appear anchored at the point $$(0.5,\,-0.5)$$ and rotate in place around that anchor. Here’s why:

Internally, GLM post-multiplies the matrix. After these two calls, the final matrix is:

$$trans = T \times R$$

where $$T$$ is the translation matrix and $$R$$ is the rotation matrix.

**Order of Transformations on a Vertex:**

When a vertex $$v$$ is multiplied by $$trans = T \times R$$, the actual operations happen right-to-left:

$$v' = (T \times R)v = T(R(v))$$

* First, the vertex is rotated around the origin by $$R$$.
* Then it is translated by $$T$$.

**Effect on the Quad:**

If the quad’s center is at $$v = (0, 0)$$ originally, rotation around the origin leaves the center at $$(0, 0)$$.

After rotation, you add $$(0.5,\,-0.5)$$.

That places the center at $$(0.5,\,-0.5)$$.

Consequently, the quad’s center never moves away from $$(0.5,\,-0.5)$$; it just spins in place around that point.
{: .notice--success}

![Spinning Quad]({{ site.baseurl }}/assets/opengl/spinning-quad.gif)

## Complete Source

[Download Source]({{ site.baseurl }}/assets/opengl/demo_textures.cpp){:target="_blank"}