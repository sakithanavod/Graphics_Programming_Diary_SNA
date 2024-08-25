---
title: "Hello Triangle"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---

In OpenGL everything is in 3D space, but the screen or window is a 2D array of pixels so a large part of OpenGL's work is about transforming all 3D coordinates to 2D pixels that fit on your screen.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Graphics Pipeline
The process of transforming 3D coordinates to 2D pixels is managed by the **graphics pipeline** of OpenGL.
The graphics pipeline can be divided into two large parts: 

1. First transforms your 3D coordinates into 2D coordinates.
2. Transforms the 2D coordinates into actual colored pixels.

The graphics pipeline can be divided into several steps where each step requires the output of the previous step as its input. All of these steps are highly specialized (they have one specific function) and can easily be executed in *parallel*.

Because of their parallel nature, graphics cards of today have thousands of small processing cores to quickly process your data within the graphics pipeline. The processing cores run small programs on the GPU for each step of the pipeline. These small programs are called **shaders.**

Some of these shaders are configurable by the developer which allows us to write our own shaders to replace the existing default shaders.

Shaders are written in the OpenGL Shading Language (GLSL)
{: .notice--success}

**Now lets go through the graphics pipeline**

![Alt Text]({{ site.baseurl }}/assets/opengl/pipeline.png)

### Vertex Shader
*Purpose:* The vertex shader processes each vertex individually. It is responsible for transforming vertex positions from object space to clip space by applying **model, view, and projection matrices**. It can also manipulate other vertex attributes like normals, texture coordinates, and colors.

#### What is a Vertex?
A vertex is a point in space that defines the corners or endpoints of geometric shapes. In a 3D space, a vertex typically consists of a set of coordinates (x, y, z) that specify its position.

#### Vertex Attributes
Vertices can have additional attributes beyond just position. These attributes are used to determine how the vertex contributes to the final rendered image. Common attributes include:

* Position: The 3D coordinates of the vertex (x, y, z).
* Color: The color associated with the vertex, often used in shading and lighting calculations.
* Normal: A vector that is perpendicular to the surface at the vertex, used in lighting calculations to determine how light interacts with the surface.
* Texture Coordinates (UV): Coordinates used to map textures onto the surface. These are 2D coordinates that correspond to positions on a texture image.
* Tangent and Bitangent: Vectors used in advanced shading techniques like normal mapping to provide additional information about the surface orientation.

```cpp
GLfloat vertices[] = {
    // Positions       // Colors
    0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top vertex (red)
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom-left vertex (green)
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Bottom-right vertex (blue)
};
```

### Shape Assembly
*Purpose:* After vertex shading, the processed vertices are assembled into geometric shapes or primitives. These can be points, lines, or triangles, depending on how the data is organized and the drawing mode specified.

### Geometry Shader (Optional)
*Purpose:* The geometry shader operates on entire primitives (points, lines, triangles) and can output zero or more new primitives. This stage can modify the topology of the scene by generating additional geometry or changing primitive types.
Example use in: Tessellation : subdivide geometry into finer pieces.

### Rasterization
*Purpose:* Converts the geometric primitives into a set of fragments. Each fragment corresponds to a potential pixel on the screen.

### Fragment Shader
*Purpose:* The fragment shader computes the final color and other attributes for each fragment. It typically involves texture sampling, lighting calculations, and per-pixel effects.

### Tests and Blending
*Purpose:* This stage applies several tests to determine whether a fragment should be written to the framebuffer.

* Depth Testing: Determines if a fragment is visible based on its depth value.
* Stencil Testing: Uses a stencil buffer to allow or block fragments based on predefined patterns.
* Blending: Combines the fragment's output color with the existing color in the framebuffer. This is used for effects like transparency and anti-aliasing.

In modern OpenGL we are required to define at least a vertex and fragment shader of our own (there are no default vertex/fragment shaders on the GPU).
{: .notice--warning}

## Vertex input
To start drawing something we have to first give OpenGL some input vertex data.
OpenGL doesn't simply transform all your 3D coordinates to 2D pixels on your screen; OpenGL only processes 3D coordinates when they're in a specific range between **-1.0 and 1.0 on all 3 axes (x, y and z).** 

All coordinates within this so called *normalized device coordinates* range will end up visible on your screen (and all coordinates outside this region won't).
{: .notice--warning}

Because we want to render a single triangle we want to specify a total of three vertices with each vertex having a 3D position.
We define them in normalized device coordinates (the visible region of OpenGL) in a float array:

```cpp
float vertices[] = {
    -0.5f, -0.5f, 0.0f, //left most vertex
     0.5f, -0.5f, 0.0f, //right most vertex
     0.0f,  0.5f, 0.0f  //top vertex
};
```

![Alt Text]({{ site.baseurl }}/assets/opengl/gl2.png)

Your Normalized Device Coordinates (NDC) will then be transformed to screen-space coordinates via the viewport transform using the data you provided with `glViewport`.
{: .notice--success}

The resulting screen-space coordinates are then transformed to fragments as inputs to your fragment shader.
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/opengl/gl3.png)

With the vertex data defined we'd like to send it as input to the first process of the graphics pipeline: the vertex shader. 

This is done by creating memory on the GPU where we store the vertex data, configure how OpenGL should interpret the memory and specify how to send the data to the graphics card.

The vertex shader then processes as much vertices as we tell it to from its memory.

### Vertex Buffer Objects (VBO)
We manage this memory via so called **vertex buffer objects (VBO)** that can store a large number of vertices in the GPU's memory.

The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics card, and keep it there if there's enough memory left, without having to send data one vertex at a time.

VBO's has a unique ID corresponding to that buffer, so we can generate one with a buffer ID using the glGenBuffers function:

```cpp
//single buffer object
unsigned int VBO;
glGenBuffers(1, &VBO); 

//if we need more than one
unsigned int VBOs[2];
glGenBuffers(2, VBOs);  // Generate 2 buffer IDs
```
OpenGL has many types of buffer objects and the buffer type of a vertex buffer object is `GL_ARRAY_BUFFER`. OpenGL allows us to bind to several buffers at once as long as they have a different buffer type. 

We can bind the newly created buffer to the `GL_ARRAY_BUFFER` target with the `glBindBuffer` function:

```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO); 
```

From that point on any buffer calls we make (on the `GL_ARRAY_BUFFER` target) will be used to configure the currently bound buffer, which is `VBO`.

Then we can make a call to the `glBufferData` function that copies the previously defined vertex data into the buffer's memory:

```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

`glBufferData` is a function specifically targeted to copy user-defined data into the currently bound buffer.

1. first argument is the type of the buffer we want to copy data into (in this case it's `GL_ARRAY_BUFFER`)
2. The second argument specifies the size of the data (in bytes) we want to pass to the buffer; a simple `sizeof` of the vertex data suffices.
3. The third parameter is the actual data we want to send.
4. The fourth parameter specifies how we want the graphics card to manage the given data. This can take 3 forms:
    * `GL_STREAM_DRAW`: the data is set only once and used by the GPU at most a few times. (example: dynamic vertex data in real-time simulations.)
    * `GL_STATIC_DRAW`: the data is set only once and used many times. (example : positions of static geometry)
    * `GL_DYNAMIC_DRAW` : the data is changed a lot and used many times. (example : vertex positions in an animation)

The position data of the triangle does not change, is used a lot, and stays the same for every render call so its usage type should best be `GL_STATIC_DRAW`.
{: .notice--success}

As of now we stored the vertex data within memory on the graphics card as managed by a vertex buffer object named VBO. Next we want to create a vertex and fragment shader that actually processes this data, so let's start building those

## Writing First Vertex shader