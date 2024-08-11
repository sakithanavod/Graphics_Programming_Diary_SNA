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

## GLFW
GLFW is a library, written in C, specifically targeted at OpenGL. GLFW gives us the bare necessities required for rendering goodies to the screen. It allows us to create an OpenGL context, define window parameters, and handle user input, which is plenty enough for our purposes.

### Example of using GLFW to create OpenGL context, define window parameters

```cpp
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

```

## GLAD
OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a driver that the specific graphics card supports. 

Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at **run-time.**
{: .notice--warning}

It is then the task of the developer to retrieve the location of the functions he/she needs and store them in function pointers for later use.

```cpp
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
```

functions like `glGenBuffers`, `glBindBuffer`, `glBufferData`, and many others come from OpenGL, and **GLAD** is responsible for loading these function pointers at runtime. GLAD provides access to these functions by querying the graphics driver and making the function pointers available for your application.

## Hello Window
In the main function we first initialize GLFW with `glfwInit`, after which we can configure GLFW using `glfwWindowHint`.

Since we want to use OpenGL version 3.3 we'd like to tell GLFW that 3.3 is the OpenGL version we want to use.

We also tell GLFW we want to explicitly use the core-profile.
```cpp
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
    return 0;
}
```

Next we're required to create a window object. This window object holds all the windowing data and is required by most of GLFW's other functions.

```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);
```
**GLAD**

Next we initialize GLAD before we call any OpenGL function:

```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
} 
```

We pass GLAD the function to load the address of the OpenGL function pointers which is **OS-specific**. GLFW gives us `glfwGetProcAddress` that defines the correct function based on which OS we're compiling for.
{: .notice--primary}

**Viewport**

Before we can start rendering we have to do one last thing. We have to tell OpenGL the **size** of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window.

```cpp
glViewport(0, 0, 800, 600);

// or you can use

int width = 0, height = 0;
glfwGetFramebufferSize(window, &width, &height); //retrieves the window size
glViewport(0, 0, width, height);

```
* The first two parameters of `glViewport` set the location of the *lower left corner* of the window. 
* The third and fourth parameter set the *width* and *height* of the rendering window in pixels

However, the moment a user **resizes** the window the viewport should be adjusted as well.
{: .notice--warning}

We can register a callback function on the window that gets called each time the window is resized.

This resize **callback function** has the following prototype:

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
```
Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
```

Now we do have to tell GLFW we want to call this function on every window resize by registering it:

```cpp
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
```

We don't want the application to draw a single image and then immediately quit and close the window. We want the application to keep drawing images and handling user input until the program has been explicitly told to stop.

For this reason we have to create a while loop, that we now call the **render loop**, that keeps on running until we tell GLFW to stop. The following code shows a very simple render loop:

```cpp
while(!glfwWindowShouldClose(window))
{
    glfwSwapBuffers(window);

    /**
    * glfwPollEvents();
    * checks if any events are triggered (like keyboard input or mouse movement events),
    * updates the window state, and calls the corresponding functions 
    * (which we can register via callback methods)
    */
    glfwPollEvents();
}
```

The `glfwSwapBuffers` will swap the color buffer (a large 2D buffer that contains *color values* for each *pixel* in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
{: .notice--success}

## Double buffer
When an application draws in a *single buffer* the resulting image may display flickering issues. This is because the resulting output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom.

Because this image is not displayed at an instant to the user while still being rendered to, the result may contain artifacts.
{: .notice--warning}

To circumvent these issues, windowing applications apply a **double buffer** for rendering.

* Back Buffer: The buffer where the next frame is rendered.
* Front Buffer: The buffer currently being displayed on the scree

### How Double Buffering Works
1. **Render to Back Buffer:** The application renders the next frame to the back buffer.
2. **Swap Buffers:** Once rendering is complete, the back buffer is swapped with the front buffer.
3. **Display Front Buffer:** The front buffer is displayed on the screen while the back buffer is used for rendering the next frame.

As soon as all the rendering commands are finished we **swap** the back buffer to the front buffer so the image can be displayed without still being rendered to, removing all the aforementioned artifacts.
{: .notice--success}

**Termination**

As soon as we exit the render loop we would like to properly clean/delete all of GLFW's resources that were allocated. We can do this via the `glfwTerminate` function that we call at the end of the `main` function.

```cpp
glfwDestroyWindow(window);

glfwTerminate();

return 0;
```

**Input**

We also want to have some form of input control in GLFW and we can achieve this with several of GLFW's input functions. We'll be using GLFW's `glfwGetKey` function that takes the window as input together with a key. The function returns whether this key is currently being pressed.

We're creating a `processInput` function to keep all input code organized:

```cpp
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
```

We then call `processInput` every iteration of the render loop:

```cpp
while (!glfwWindowShouldClose(window))
{
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

**Rendering**

We want to place all the **rendering commands** in the **render loop**, since we want to execute all the rendering commands each iteration or frame of the loop. This would look a bit like this:

```cpp
// render loop
while(!glfwWindowShouldClose(window))
{
    // input
    processInput(window);

    // rendering commands here example
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    ...

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
}
```

An iteration of the render loop is more commonly called a frame.
{: .notice--success}

At the start of frame we want to clear the screen.Otherwise we would still see the results from the **previous frame.**

We can clear the screen's color buffer using `glClear` where we pass in *buffer bits* to specify which buffer we would like to clear.
The possible bits we can set are:

1. GL_COLOR_BUFFER_BIT
2. GL_DEPTH_BUFFER_BIT
3. GL_STENCIL_BUFFER_BIT

Right now we only care about the color values so we only clear the color buffer.

```cpp
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
```

Note that we also specify the color to clear the screen with using `glClearColor`. Whenever we call `glClear` and clear the color buffer, the entire color buffer will be filled with the color as configured by `glClearColor`. This will result in a dark green-blueish color.

## Complete Source

[Download Source]({{ site.baseurl }}/assets/opengl/main_create_window.cpp){:target="_blank"}