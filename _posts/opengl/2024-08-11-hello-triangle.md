---
title: "Hello Triangle"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---
{% include mathJax.html %}

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

Clip space : Any vertices that lie outside the view frustum (the visible area defined by the camera) will be clipped (discarded)
{: .notice--success}

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

The first thing we need to do is write the vertex shader in the shader language **GLSL (OpenGL Shading Language)** and then compile this shader so we can use it in our application.

```cpp
/*
* This specifies the version of GLSL being used. In this case, 
* it is version 330, which corresponds to OpenGL 3.3.
*/
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

### Input Layout

* `layout (location = 0) in vec3 aPos;` defines an input variable for the vertex shader.
* The keyword `in` specifies that this variable is being passed in from the application, typically a vertex position.
* The `location = 0` indicates the *attribute index* for this input. The data at index 0 of the vertex attribute array (often provided via a Vertex Buffer Object or VBO) will be mapped to this variable `aPos`.
* `vec3 aPos` means the variable `aPos` is a 3-component vector (representing the vertex's position in 3D space).

### Main Function

```cpp
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

* `void main()` is the entry point of the shader.
* `gl_Position` is a built-in output variable in the vertex shader. It determines the final position of the vertex in **clip space**, which is used by the graphics pipeline to render the vertex onto the screen.
* The vertex position (`aPos`) is converted from a `vec3` (3D vector) to a `vec4` (4D homogeneous vector) by adding a `w` coordinate of `1.0.` This is required by OpenGL to perform the perspective divide and map the 3D position to 2D screen space.

Typically, in more advanced applications, this is where you'd apply transformations (e.g., multiplying by a model-view-projection matrix) to convert the vertex position from object space to world space, view space, and finally clip space.
{: .notice--success}

### Example of a Typical Vertex Transformation

1. Object Space Position: $$(x_{\text{obj}}, y_{\text{obj}}, z_{\text{obj}})$$
2. Model Transformation (World Space): $$p_{\text{world}} = \text{ModelMatrix} \times p_{\text{object}}$$
3. View Transformation (Camera Space): $$p_{\text{view}} = \text{ViewMatrix} \times p_{\text{world}}$$
4. Projection Transformation (Clip Space): $$p_{\text{clip}} = \text{ProjectionMatrix} \times p_{\text{view}}$$ (can be Perspective Projection or Orthographic Projection)
5. Perspective Divide (NDC): $$p_{\text{ndc}} = \frac{p_{\text{clip}}}{w_{\text{clip}}}$$ (clip space vector is divided by the 
w-component)
6. Viewport Transformation (Screen Space): After NDC, the coordinates are mapped to the viewport (using `glViewport`), and rasterization occurs to determine which pixels the geometry covers.

 OpenGL handles the transformation from Clip Space → NDC → Screen Space internally after the vertex shader. You don't need to manually perform these steps.
{: .notice--success}

###  Example Vertex Shader with Model, View, and Projection Transformations

```cpp
#version 330 core

// Input: The position of the vertex in object space (local coordinates)
layout (location = 0) in vec3 aPos;

// Uniforms: Matrices for transformations (supplied by the CPU side)
uniform mat4 model;      // Model matrix: Transforms object space to world space
uniform mat4 view;       // View matrix: Transforms world space to view (camera) space
uniform mat4 projection; // Projection matrix: Transforms view space to clip space

// Output: This will be passed to the fragment shader
void main()
{
    // Apply the Model-View-Projection (MVP) matrix to the vertex position
    // First, apply the model matrix to transform the vertex from object space to world space
    // Then, apply the view matrix to transform it from world space to view space
    // Finally, apply the projection matrix to transform it from view space to clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
```

###   Example of how vertex shaders receives matrix data from CPU side
``` cpp
// Calculate MVP matrices using a math library like GLM
glm::mat4 model = glm::translate(glm::mat4(1.0f), objectPosition);
glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, upVector);
glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

// Use the shader program
glUseProgram(shaderProgram);

// Set the uniform values for the matrices in the shader
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

// Render the object
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, vertexCount);

```

### Compiling a vertex shader
We take the source code for the vertex shader and store it in a const C string at the top of the code file for now:

```cpp
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
```
In order for OpenGL to use the shader it has to dynamically compile it at run-time from its source code.

The first thing we need to do is create a shader object, again referenced by an ID. So we store the vertex shader as an unsigned int and create the shader with `glCreateShader`:

```cpp
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

Next we attach the shader source code to the shader object and compile the shader:

```cpp
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

The `glShaderSource` function takes:

* First param - the shader object to compile
* Second param - specifies how many strings we're passing as source code
* Third param - the actual source code of the vertex shader
* Fourth param - we can leave the 4th parameter to `NULL`

### Check for compilation errors

```cpp
GLint success;
glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Error: Shader compilation failed\n" << infoLog << std::endl;
}
```

## Writing First Fragment shader

The fragment shader is the second and final shader we're going to create for rendering a triangle. The fragment shader is all about calculating the color output of your pixels. To keep things simple the fragment shader will always output an orange-ish color.

```cpp
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
```

* `out vec4 FragColor;` declares an output variable from the fragment shader.
    * `vec4` stands for a four-component vector, which represents the red (R), green (G), blue (B), and alpha (A) channels of the color in RGBA format.
    * `FragColor` is the variable that will hold the final color that the fragment shader calculates for each pixel. This value is passed on to the framebuffer, where it is eventually rendered to the screen.
    * `out` means this variable is the output of the shader. The value assigned to FragColor determines the final color of the pixel on the screen.
* `FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);` assigns a color to the FragColor output.

### Usage example of a fragment shaders

1. Texturing - Fragment shaders are commonly used to apply textures to surfaces.
2. Lighting Calculations - Fragment shaders are often used to implement lighting models (e.g., Phong, Blinn-Phong, Lambertian) to simulate how light interacts with surfaces.
3. Specular Highlights and Reflections - You can add specular highlights to make objects look shiny or reflective.
4. Color Manipulation - Fragment shaders can modify or manipulate colors in many ways: Color Tinting, Grayscale etc
5. Fog Effects - You can create fog or atmospheric effects by blending the fragment's color with the fog color based on the fragment's distance from the camera.
6. Shadow Mapping - Fragment shaders can implement shadow mapping, where you calculate shadows by checking if a fragment is in shadow based on light direction and depth comparison.

### Compiling a fragment shader

```cpp
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);  // Set output color
}
)";


// Create a shader object
unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Attach the shader source code to the shader object and compile it
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

/* 
* check for compilation errors similar to vertex shader and 
* after compilation we have our shader in fragmentShader
*/
```

Both the shaders are now compiled and the only thing left to do is link both shader objects into a shader program that we can use for rendering. Make sure to check for compile errors here as well!
{: .notice--success}

## Shader program
A shader program object is the **final linked version** of multiple shaders combined. To use the recently compiled shaders we have to *link* them to a shader program object and then activate this shader program when rendering objects.

The activated shader program's shaders will be used when we issue render calls.

When linking the shaders into a program it links the **outputs** of each shader to the **inputs** of the next shader.

This is also where you'll get linking errors if your outputs and inputs do not match.
{: .notice--warning}

```cpp
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
```

The `glCreateProgram` function creates a program and returns the ID reference to the newly created program object. Now we need to attach the previously compiled shaders to the program object and then link them with `glLinkProgram`:

```cpp
// Attach the compiled shaders to the program
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);

// Link the program
glLinkProgram(shaderProgram);
```

Just like shader compilation we can also check if linking a shader program failed and retrieve the corresponding log. However, instead of using `glGetShaderiv` and `glGetShaderInfoLog` we now use: `glGetProgramiv`

```cpp
// Check for linking errors
GLint success;
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Error: Program linking failed\n" << infoLog << std::endl;
}
```

The result is a program object that we can activate by calling `glUseProgram` with the newly created program object as its argument:

```cpp
glUseProgram(shaderProgram);
```

Every shader and rendering call after glUseProgram will now use this program object (and thus the shaders).
{: .notice--success}

Oh yeah, and don't forget to delete the shader objects once we've linked them into the program object; we no longer need them anymore:

```cpp
// Once the shaders are linked, we can delete the shader objects
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

return shaderProgram;
```

Right now we sent the input vertex data to the GPU and instructed the GPU how it should process the vertex data within a vertex and fragment shader.

We're almost there, but not quite yet. OpenGL **does not yet** know how it should interpret the vertex data in memory and how it should connect the vertex data to the vertex shader's attributes. We'll be nice and tell OpenGL how to do that.

## Linking Vertex Attributes
The vertex shader allows us to specify any input we want in the form of vertex attributes and while this allows for great flexibility, it does mean we have to manually specify what part of our input data goes to which vertex attribute in the vertex shader.

This means we have to specify how OpenGL should interpret the vertex data before rendering.

![Alt Text]({{ site.baseurl }}/assets/opengl/gl4.png)

### Vertex Array Object (VAO)
The Vertex Array Object (VAO) is a crucial OpenGL object that stores the configuration of your vertex attributes, such as positions, colors, normals, and texture coordinates.

#### What is a VAO?
A Vertex Array Object (VAO) is an OpenGL object that encapsulates the configuration needed to render vertex data. Specifically, it:

1. Stores Attribute Layouts: The VAO keeps track of all the vertex attribute pointers (e.g., positions, colors, texture coordinates) that specify how vertex data is organized in memory.

2. Binds Buffers: It remembers the associated Vertex Buffer Objects (VBOs) and Element Buffer Objects (EBOs) linked to the vertex attributes.

3. Simplifies Rendering: By using a VAO, you don’t need to repeatedly specify vertex attribute layouts each time you want to render. Instead, you bind the VAO once, and OpenGL knows how to interpret the vertex data.

![Alt Text]({{ site.baseurl }}/assets/opengl/gl5.png)

### Define and enable vertex attributes

This setup allows the GPU to interpret different parts of a vertex structure as separate attributes, such as position, color, and texture coordinates. Let’s break down each `glVertexAttribPointer` line in detail.

```cpp

//Define the example Vertex Structure
struct Vertex {
    glm::vec3 position;   // Position of the vertex in 3D space
    glm::vec3 color;      // Color of the vertex (RGB)
    glm::vec2 texCoords;  // Texture coordinates (UV)
};

//Create the Vertex Array
Vertex vertices[] = {
    // Positions          // Colors           // Texture Coords
    { { 0.5f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } }, // Top Right
    { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom Right
    { {-0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // Bottom Left
    { {-0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }  // Top Left
};

// Indices for the two triangles that make up the quad
unsigned int indices[] = {
    0, 1, 3,  // First triangle
    1, 2, 3   // Second triangle
};
```

Now that we have the basic setup for enabling vertex attributes lets setup up OpenGL Buffers

```cpp
unsigned int VAO, VBO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

// Bind the Vertex Array Object first, then bind and set vertex buffers, and configure vertex attributes
// Bind the VAO first because it needs to store references to the VBO (Vertex Buffer Object) and EBO (Element Buffer Object)
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```
Now we have to configure each vertex attribute:

```cpp
// Position attribute (location = 0)
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
glEnableVertexAttribArray(0);

// Color attribute (location = 1)
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
glEnableVertexAttribArray(1);

// Texture coordinates attribute (location = 2)
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
glEnableVertexAttribArray(2);

// Unbind VAO to avoid unintentional modifications
glBindVertexArray(0);
```

EBO does not need `glVertexAttribPointer` because it stores indices, not attributes.The VAO automatically remembers which EBO was bound, even after unbinding.
{: .notice--warning}

#### Explanation of Parameters for `glVertexAttribPointer`

##### 1st param (Attribute location): 
Specifies the attribute location. This is location = 0 in the vertex shader, used for vertex position and so on.

##### 2nd param (No of components): 
Number of components of the vertex attribute: for pos we have 3 components (x, y, z - vec3), for color which is also have 3 components (r, g, and b - vec3), finally for tex coord we have two components (u and v - vec2)

##### 3rd param (Data type): 
`GL_FLOAT`: The data type is float.

##### 4th param (should normalize flag): 
`GL_FALSE:` Indicates that the data should not be normalized. Setting it to `GL_FALSE` means the data is used as-is.

Make this `GL_TRUE` when passing color data (values ranging from 0 to 255) - by doing so OpenGL will map these values to a 0.0 to 1.0 range.
{: .notice--success}

##### 5th param (stride): 
`sizeof(Vertex):` Specifies the stride, which is the total size of each Vertex structure. It tells OpenGL how many **bytes** it should skip to get to the next vertex’s position.

##### 6th param (offset):

`(void*)0:` This is the offset from the start of the vertex structure to the position attribute. for the first attribute, the offset is 0, for second we use `(void*)offsetof(Vertex, color)` 

For an example, this uses the `offsetof` macro to find the **byte offset** of the *color attribute* within the Vertex structure. for third we can use `(void*)offsetof(Vertex, texCoords)` 

Basically this is giving the start location *texCoord* in memory by `sizeof(glm::vec3)` (pos) `+` `sizeof(glm::vec3)` (color).

### Element Buffer Object (EBO) aka Index Buffer Objects (IBOs)
Element Buffer Objects (EBOs), also known as Index Buffer Objects (IBOs), are a type of buffer in OpenGL that allow you to specify *indices* for drawing vertices. This enables you to **reuse vertices** and avoid duplication, which is especially helpful when drawing complex shapes like 3D models or grids, where many vertices are shared between multiple triangles.

#### What is an EBO?
An Element Buffer Object (EBO) is an OpenGL buffer that holds indices (integers) pointing to specific vertices in a vertex array. By using these indices, you can tell OpenGL to reuse vertices when drawing shapes, which reduces memory usage and improves performance.

For example, when drawing a square (which consists of two triangles), you can define four vertices and use an EBO to specify which vertices should form each triangle, avoiding the need to duplicate vertices

#### Benefits of Using an EBO
* Memory Efficiency: By reusing vertices, you store fewer vertices in memory.
* Performance: Reduces the amount of data sent to the GPU by minimizing duplicate vertices.
* Convenience: Makes it easier to define complex shapes with fewer vertices.

#### Example of an EBO with a Simple Quad
Let’s say we want to render a square (quad) made up of two triangles. Without an EBO, we’d need to specify six vertices (three per triangle), even though two of the vertices are duplicates. With an EBO, we can specify only four unique vertices and use indices to draw the triangles.

if we use two triangles:

```cpp
	
float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
}; 
```

As you can see, there is some overlap on the vertices specified. We specify bottom right and top left twice! This is an overhead of 50% since the same rectangle could also be specified with only 4 vertices, instead of 6.
{: .notice--warning}

```cpp
// Define the vertices for a quad
float vertices[] = {
    // Positions      // Colors
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f   // Top Left
};

// Define the indices for the two triangles that make up the quad
unsigned int indices[] = {
    0, 1, 3,  // First triangle (Top Right, Bottom Right, Top Left)
    1, 2, 3   // Second triangle (Bottom Right, Bottom Left, Top Left)
};
```

Next we need to create the element buffer object:

```cpp
unsigned int EBO;
glGenBuffers(1, &EBO);
```

Similar to the VBO we bind the EBO and copy the indices into the buffer with `glBufferData`. Also, just like the VBO we want to place those calls between a bind and an unbind call, although this time we specify `GL_ELEMENT_ARRAY_BUFFER` as the buffer type.


```cpp
// Bind and fill the VBO with vertex data
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Bind and fill the EBO with index data
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

Finally, In the render loop, bind the VAO and use `glDrawElements` instead of `glDrawArrays`. `glDrawElements` uses the indices from the EBO to determine which vertices to draw:

```cpp
// Render loop
while (!glfwWindowShouldClose(window)) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind the VAO and draw using indices
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

* `glDrawElements:`
    - `GL_TRIANGLES:` Specifies that each group of three indices forms a triangle.
    - `6:` Number of indices to draw (two triangles, three indices each).
    - `GL_UNSIGNED_INT:` Data type of the indices in the EBO.
    - `0:` Offset in the EBO, starting from the first index.

How It Works?

![Alt Text]({{ site.baseurl }}/assets/opengl/gl6.png)

When `glDrawElements` is called:

1. OpenGL looks at the indices in the EBO and uses them to access the appropriate vertices in the VBO.
2. For each triangle, OpenGL assembles vertices according to the indices and draws them, reusing vertices as needed without duplicating data in the VBO.

A VAO stores the `glBindBuffer` calls when the target is `GL_ELEMENT_ARRAY_BUFFER`. This also means it stores its unbind calls so make sure you don't unbind the element array buffer before unbinding your VAO, otherwise it doesn't have an EBO configured.
{: .notice--warning}

*Correct Order of Binding and Unbinding*
To ensure that the VAO keeps the EBO binding, follow these steps:

1. Bind the VAO.
2. Bind the EBO while the VAO is active.
3. Unbind the VAO first if you need to unbind anything, as this retains the EBO within the VAO configuration.
4. Only then, if necessary, unbind the EBO (although it’s generally safe to leave the EBO bound).
