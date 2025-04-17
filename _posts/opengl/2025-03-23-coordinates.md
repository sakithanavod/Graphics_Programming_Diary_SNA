---
title: "Coordinate Systems"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---
{% include mathJax.html %}

OpenGL expects all the vertices, that we want to become visible, to be in normalized device coordinates after each vertex shader run. 

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Coordinate Systems

In the last chapter we learned how we can use matrices to our advantage by transforming all vertices with transformation matrices. OpenGL expects all the vertices, that we want to become visible, to be in *normalized* device coordinates after each vertex shader run.

That is, the x, y and z coordinates of each vertex should be between -1.0 and 1.0; coordinates outside this range will not be visible. 
{: .notice--warning}

### NDC

What we usually do, is specify the coordinates in a range (or space) we determine ourselves and in the vertex shader transform these coordinates to normalized device coordinates (NDC).

These NDC are then given to the rasterizer to transform them to 2D coordinates/pixels on your screen.

#### NDC (Normalized Device Coordinates)
NDC (Normalized Device Coordinates) is a coordinate system used in the 3D graphics rendering pipeline after the Projection Transformation and just before the Viewport Transformation.

#### Why NDC Is Important:
Only the parts of your scene that fall within the NDC cube are visible on screen. Anything outside is clipped.

#### NDC Cube

The NDC cube is a canonical 3D space in OpenGL that all geometry gets transformed into before rasterization (i.e., before turning triangles into pixels).

It’s called "normalized" because its coordinates are always in a fixed range — regardless of screen size, camera settings, etc.

It’s a cube defined by:

```cpp
x ∈ [-1, 1]
y ∈ [-1, 1]
z ∈ [-1, 1]
```

![Alt Text]({{ site.baseurl }}/assets/opengl/gl26.png)

**Coordinate System (in OpenGL)**
* Left-handed (due to projection)
* Origin (0, 0, 0) is in the center of the cube

* Axes:
    * X: Left to right
        * -1 = left side of the screen
        * +1 = right side
    * Y: Bottom to top
        * -1 = bottom of the screen
        * +1 = top
    * Z: Near to far (in OpenGL)
        * -1 = near plane (closest to camera)
        * +1 = far plane (farthest away)

**Summery**

NDC (Normalized Device Coordinates) is a normalized coordinate system in OpenGL where all visible vertices are mapped after the **projection and perspective divide**. It represents how the camera sees the world — so positions are expressed in a standard cube ranging from [-1, 1] on all three axes.

This NDC cube:
* Has X ∈ [-1, 1] → left to right on screen
* Y ∈ [-1, 1] → bottom to top on screen
* Z ∈ [-1, 1] → depth, from near plane (-1) to far plane (+1)

This cube acts as the clipping volume: OpenGL will clip or discard any geometry outside this cube.

The Z component (depth) in NDC tells how far a vertex is from the camera within this normalized space. After mapping to [0, 1], it is used by the depth buffer for visibility testing — closer fragments win over farther ones.

OpenGL automatically maps the Z value from NDC into [0, 1] during the viewport transformation.
{: .notice--success}

So in short:

NDC is a canonical cube that contains all visible geometry, from the camera's perspective, including position and depth, ready for the final step of viewport transformation and rasterization.
{: .notice--success}

### Transformation Flow:
1. Object Space Position: $$(x_{\text{obj}}, y_{\text{obj}}, z_{\text{obj}})$$
2. Model Transformation (World Space): $$p_{\text{world}} = \text{ModelMatrix} \times p_{\text{object}}$$
3. View Transformation (Camera Space): $$p_{\text{view}} = \text{ViewMatrix} \times p_{\text{world}}$$
4. Projection Transformation (Clip Space): $$p_{\text{clip}} = \text{ProjectionMatrix} \times p_{\text{view}}$$ (can be Perspective Projection or Orthographic Projection)
5. Perspective Divide (NDC): $$p_{\text{ndc}} = \frac{p_{\text{clip}}}{w_{\text{clip}}}$$ (clip space vector is divided by the 
w-component)
6. Viewport Transformation (Screen Space): After NDC, the coordinates are mapped to the viewport (using `glViewport`), and rasterization occurs to determine which pixels the geometry covers.

## The global picture

To transform the coordinates from one space to the next coordinate space we'll use several transformation matrices of which the most important are the **model, view and projection matrix**.

Our vertex coordinates first start in local space as local coordinates and are then further processed to world coordinates, view coordinates, clip coordinates and eventually end up as screen coordinates. The following image displays the process and shows what each transformation does:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl20.png)


1. Local coordinates are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.
2. The next step is to transform the local coordinates to world-space coordinates which are coordinates in respect of a larger world. These coordinates are relative to some global origin of the world, together with many other objects also placed relative to this world's origin.
3. Next we transform the world coordinates to view-space coordinates in such a way that each coordinate is as seen from the camera or viewer's point of view.
4. After the coordinates are in view space we want to project them to clip coordinates. Clip coordinates are processed to the -1.0 and 1.0 range and determine which vertices will end up on the screen. Projection to clip-space coordinates can add perspective if using perspective projection.
5. And lastly we transform the clip coordinates to screen coordinates in a process we call viewport transform that transforms the coordinates from -1.0 and 1.0 to the coordinate range defined by glViewport. The resulting coordinates are then sent to the rasterizer to turn them into fragments.

### Local space

Local space is the coordinate space that is local to your object, i.e. where your object begins in. Imagine that you've created your cube in a modeling software package (like Blender). The origin of your cube is probably at (0,0,0) even though your cube may end up at a different location in your final application.

Probably all the models you've created all have (0,0,0) as their initial position. All the vertices of your model are therefore in local space: they are all local to your object.

### World space

If we would import all our objects directly in the application they would probably all be somewhere positioned inside each other at the world's origin of (0,0,0) which is not what we want. We want to define a position for each object to position them inside a larger world. The coordinates in world space are exactly what they sound like: the coordinates of all your vertices relative to a (game) world. 

This is the coordinate space where you want your objects transformed to in such a way that they're all scattered around the place (preferably in a realistic fashion). The coordinates of your object are transformed from local to world space; this is accomplished with the **model matrix.**

The **model matrix** is a transformation matrix that *translates, scales and/or rotates* your object to place it in the world at a location/orientation they belong to.

Think of it as transforming a house by scaling it down (it was a bit too large in local space), translating it to a suburbia town and rotating it a bit to the left on the y-axis so that it neatly fits with the neighboring houses.
{: .notice--primary}

### View space

The view space is what people usually refer to as the camera of OpenGL (it is sometimes also known as camera space or eye space). The view space is the result of transforming your world-space coordinates to coordinates that are in front of the user's view. 

The view space is thus the space as seen from the camera's point of view. This is usually accomplished with a combination of translations and rotations to translate/rotate the scene so that certain items are transformed to the front of the camera. 

Think of it as moving the entire world so the camera is at the origin (0,0,0) and facing down the -Z axis.
{: .notice--primary}

These combined transformations are generally stored inside a view matrix that transforms world coordinates to view space. In the next chapter we'll extensively discuss how to create such a view matrix to simulate a camera.

### Clip space

At the end of each vertex shader run, OpenGL expects the coordinates to be within a specific range and any coordinate that falls outside this range is clipped. Coordinates that are clipped are discarded, so the remaining coordinates will end up as fragments visible on your screen. This is also where clip space gets its name from.

Because specifying all the visible coordinates to be within the range -1.0 and 1.0 isn't really intuitive, we specify our own coordinate set to work in and convert those back to **NDC** as OpenGL expects them.

To transform vertex coordinates from view to clip-space we define a so called projection matrix that specifies a range of coordinates e.g. -1000 and 1000 in each dimension. The projection matrix then converts coordinates within this specified range to normalized device coordinates (-1.0, 1.0) *(not directly, a step called **Perspective Division** sits in between)*.

All coordinates outside this range will not be mapped between -1.0 and 1.0 and therefore be clipped. With this range we specified in the projection matrix, a coordinate of (1250, 500, 750) would not be visible, since the x coordinate is out of range and thus gets converted to a coordinate higher than 1.0 in NDC and is therefore clipped.

Note that if only a part of a primitive e.g. a triangle is outside the clipping volume OpenGL will reconstruct the triangle as one or more triangles to fit inside the clipping range
{: .notice--success}

This viewing box a projection matrix creates is called a frustum and each coordinate that ends up inside this frustum will end up on the user's screen. The total process to convert coordinates within a specified range to NDC that can easily be mapped to 2D view-space coordinates is called projection since the projection matrix projects 3D coordinates to the easy-to-map-to-2D normalized device coordinates.

Once all the vertices are transformed to clip space a final operation called **perspective division** is performed where we divide the x, y and z components of the position vectors by the vector's **homogeneous w component**;

perspective division is what transforms the 4D clip space coordinates to 3D normalized device coordinates. This step is performed automatically at the end of the vertex shader step.

It is after this stage where the resulting coordinates are mapped to screen coordinates (using the settings of `glViewport`) and turned into fragments.

The projection matrix to transform view coordinates to clip coordinates usually takes two different forms, where each form defines its own unique frustum. We can either create an 

1. orthographic projection matrix 
2. perspective projection matrix.

#### Orthographic projection

An orthographic projection matrix defines a cube-like frustum box that defines the clipping space where each vertex outside this box is clipped. When creating an orthographic projection matrix we specify the width, height and length of the visible frustum. 

All the coordinates inside this frustum will end up within the NDC range after transformed by its matrix and thus won't be clipped. The frustum looks a bit like a container:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl21.png)

The frustum defines the visible coordinates and is specified by a width, a height and a near and far plane. Any coordinate in front of the near plane is **clipped** and the same applies to coordinates behind the far plane.

The orthographic frustum **directly** maps all coordinates inside the frustum to normalized device coordinates without any special side effects since it won't touch the w component of the transformed vector; if the w component remains equal to 1.0 perspective division won't change the coordinates.

Raw orthographic projection matrix:

```cpp
// Inputs:
float left, right, bottom, top, near, far;

// Resulting 4x4 orthographic matrix:
glm::mat4 projection = {
    { 2/(right-left),     0,                  0,              -(right+left)/(right-left) },
    { 0,                  2/(top-bottom),     0,              -(top+bottom)/(top-bottom) },
    { 0,                  0,         -2/(far-near),            -(far+near)/(far-near)     },
    { 0,                  0,                  0,                                1         }
};
```

Or with GLM:

```cpp
glm::mat4 projection = glm::ortho(left, right, bottom, top, near, far);
```

* The first two parameters specify the left and right coordinate of the frustum 
* and the third and fourth parameter specify the bottom and top part of the frustum. With those 4 points we've defined the size of the near and far planes 
* and the 5th and 6th parameter then define the distances between the near and far plane. This specific projection matrix transforms all coordinates between these x, y and z range values to normalized device coordinates.

**Visualization:**
You're defining a viewing box like this:

```cpp
X: [0, 800]
Y: [0, 600]
Z: [0.1, 100]
```

* The camera looks along the -Z axis, so objects must be between Z = 0.1 and Z = 100 (not behind the camera).
* (0, 0) is the bottom-left of the screen.
* (800, 600) is the top-right.
* Useful for UI rendering, 2D games, or pixel-perfect layout.

Note about Z range: Even in orthographic projection, depth (Z) still matters: Objects with lower Z values are closer to the camera.
This helps with layering — e.g., draw background at Z = 10, UI at Z = 0.5, etc. The near and far values define what range of Z values are visible — outside of it gets clipped.
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/opengl/gl22.png)

An orthographic projection matrix directly maps coordinates to the 2D plane that is your screen, but in reality a direct projection produces unrealistic results since the projection doesn't take perspective into account. That is something the perspective projection matrix fixes for us.
{: .notice--warning}

#### Perspective projection

If you ever were to enjoy the graphics the real life has to offer you'll notice that objects that are farther away appear much smaller. This weird effect is something we call perspective. Perspective is especially noticeable when looking down the end of an infinite motorway or railway as seen in the following image:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl23.png)

As you can see, due to perspective the lines seem to coincide at a far enough distance. This is exactly the effect perspective projection tries to mimic and it does so using a *perspective projection matrix.*

The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate in such a way that the **further away a vertex coordinate is from the viewer, the higher this w component becomes.**

Once the coordinates are transformed to clip space they are in the range -w to w (anything outside this range is clipped). OpenGL requires that the visible coordinates fall between the range -1.0 and 1.0 as the final vertex shader output, thus once the coordinates are in clip space, perspective division is applied to the clip space coordinates:

```cpp
vec3 ndc = vec3(clipSpace.x, clipSpace.y, clipSpace.z) / clipSpace.w;
```
Each component of the vertex coordinate is divided by its w component giving smaller vertex coordinates the further away a vertex is from the viewer. This is another reason why the w component is important, since it helps us with perspective projection. 

Raw perspective projection matrix

```cpp
// Inputs:
float fov = 45.0f; // vertical field of view, in degrees
float aspect = width / height; // aspect ratio
float near = 0.1f;
float far = 100.0f;

// Compute f:
float f = 1.0f / tan(fov * 0.5 * PI / 180.0);

// Resulting 4x4 perspective projection matrix:
glm::mat4 projection = {
    { f / aspect,   0,                          0,                               0 },
    { 0,            f,                          0,                               0 },
    { 0,            0,      (far + near)/(near - far),     (2 * far * near)/(near - far) },
    { 0,            0,                         -1,                               0 }
};
```
with GLM

```cpp
glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
```

What `glm::perspective` does is again create a large frustum that defines the visible space, anything outside the frustum will not end up in the clip space volume and will thus become clipped.

A perspective frustum can be visualized as a non-uniformly shaped box from where each coordinate inside this box will be mapped to a point in clip space. An image of a perspective frustum is seen below:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl24.png)

1. Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is. For a realistic view it is usually set to 45 degrees
2. The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
3. The third and fourth parameter set the near and far plane of the frustum. We usually set the near distance to 0.1 and the far distance to 100.0. All the vertices between the near and far plane and inside the frustum will be rendered.

Whenever the near value of your perspective matrix is set too high (like 10.0), OpenGL will clip all coordinates close to the camera (between 0.0 and 10.0), which can give a visual result you maybe have seen before in videogames where you could see through certain objects when moving uncomfortably close to them.
{: .notice--warning}

### Projections

When using orthographic projection, each of the vertex coordinates are directly mapped to clip space without any fancy perspective division (it still does perspective division, but the w component is not manipulated (it stays 1) and thus has no effect).

Because the orthographic projection doesn't use perspective projection, objects farther away do not seem smaller, which produces a weird visual output. For this reason the orthographic projection is mainly used for 2D renderings and for some architectural or engineering applications where we'd rather not have vertices distorted by perspective.

![Alt Text]({{ site.baseurl }}/assets/opengl/gl25.jpg)

## Model-View-Projection (MVP) transformation
We create a transformation matrix for each of the aforementioned steps: model, view and projection matrix. A vertex coordinate is then transformed to clip coordinates as follows:

$$V_{clip} = M_{projection} \cdot M_{view} \cdot M_{model} \cdot V_{local}$$

is the full transformation pipeline in 3D graphics, often referred to as:

**Model-View-Projection (MVP) Transformation**

Each component has a specific job:

Term              | Name                   | Role
------------------|------------------------|------------------------------------------------------------
$$V_{local}$$      | Local Space Position   | The vertex's position in its own object’s coordinate system  
$$M_{model}$$      | Model Matrix           | Moves the vertex from local space to world space  
$$M_{view}$$       | View Matrix            | Transforms from world space to camera (view) space  
$$M_{projection}$$ | Projection Matrix      | Maps view space to clip space, applying perspective  
$$V_{clip}$$       | Clip Space Position    | Final result before perspective divide and NDC  

Note that the order of matrix multiplication is reversed (remember that we need to read matrix multiplication from right to left). The resulting vertex should then be assigned to `gl_Position` in the vertex shader and OpenGL will then automatically perform perspective division and clipping.
{: .notice--success}

The output of the vertex shader requires the coordinates to be in clip-space which is what we just did with the transformation matrices. OpenGL then performs perspective division on the clip-space coordinates to transform them to normalized-device coordinates. OpenGL then uses the parameters from `glViewPort` to map the normalized-device coordinates to screen coordinates where each coordinate corresponds to a point on your screen (in our case a 800x600 screen). This process is called the viewport transform.
{: .notice--primary}

## Going 3D

### Model Matrix

Now that we know how to transform 3D coordinates to 2D coordinates we can start rendering real 3D objects instead of the lame 2D plane we've been showing so far.

To start drawing in 3D we'll first create a **model matrix.** The model matrix consists of translations, scaling and/or rotations we'd like to apply to transform all object's vertices to the global world space. Let's transform our plane a bit by rotating it on the x-axis so it looks like it's laying on the floor. The model matrix then looks like this:

```cpp
glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

/**
* We can build the model matrix like this by passing the result of on to another
* 
* model = Identity;
* model = model * RotationMatrix;
* model = model * ScaleMatrix;
**/
```

By multiplying the vertex coordinates with this model matrix we're transforming the vertex coordinates to world coordinates. Our plane that is slightly on the floor thus represents the plane in the global world.

### View Matrix

Next we need to create a view matrix. We want to move slightly backwards in the scene so the object becomes visible (when in world space we're located at the origin (0,0,0)). To move around the scene, think about the following:

*To move a camera backwards, is the same as moving the entire scene forward.*

That is exactly what a view matrix does, we move the entire scene around inversed to where we want the camera to move.

Because we want to move backwards and since OpenGL is a right-handed system we have to move in the positive z-axis. We do this by translating the scene towards the negative z-axis. This gives the impression that we are moving backwards.

#### Right-handed system

By convention, OpenGL is a right-handed system. What this basically says is that the positive x-axis is to your right, the positive y-axis is up and the positive z-axis is backwards. Think of your screen being the center of the 3 axes and the positive z-axis going through your screen towards you. The axes are drawn as follows:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl25.png)

Note that in normalized device coordinates OpenGL actually uses a left-handed system (the projection matrix switches the handedness).
{: .notice--warning}

#### Why the OpenGL Projection Matrix Flips the Z-Axis
The OpenGL projection matrix flips the Z-axis to match OpenGL’s convention that NDC is a left-handed system, where Z increases from near to far (-1 → +1).

In view space, OpenGL uses a right-handed coordinate system, where:
* X points right
* Y points up
* Z points backward, so Z decreases into the screen (i.e., visible objects have negative Z values)

However, in NDC, the Z-axis must increase into the screen:

* z_ndc = -1 → near plane (closest)
* z_ndc = +1 → far plane (farthest)

This flip in Z direction is mathematically required to remap view-space depth values from [-near, -far] into [-1, +1]. As a result, the coordinate system becomes left-handed in NDC — and that change is baked into the projection matrix and it's built into it.

#### GLM View Matrix

```cpp
glm::mat4 view = glm::mat4(1.0f);
// note that we're translating the scene in the reverse direction of where we want to move
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
```

The camera stays fixed at the origin in view space (position (0, 0, 0)), always looking down the -Z axis.
{: .notice--primary}

In OpenGL, you don't move the camera — you move the world in the opposite direction of the camera’s movement.
{: .notice--success}

What This Line Does:
* Translates the scene backward by 3 units on the Z axis
* Which makes it appear as if the camera moved forward by 3 units

**Mental Model**

What you do in view matrix               | What it feels like in camera space
----------------------------------------|--------------------------------------------
Translate world by $$(0, 0, -3)$$        | Camera moved forward along +Z  
Translate world by $$(0, 0, +5)$$        | Camera moved backward  
Rotate world to the right                | Camera turned left  

### Projection Matrix.

The last thing we need to define is the projection matrix. We want to use perspective projection for our scene so we'll declare the projection matrix like this:

```cpp
glm::mat4 projection;
projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
```
This code is creating a perspective projection matrix using GLM.

`glm::perspective()`

`The glm::perspective()` function creates a projection matrix that maps 3D points into a frustum (a truncated pyramid), which is then transformed into NDC.

It takes four parameters:

* Vertical Field of View (FOV):
    - `glm::radians(45.0f)` converts a 45° field of view (FOV) to radians (because GLM uses radians).
    - This determines how wide the view is. A larger FOV gives a "zoomed-out" effect, while a smaller FOV gives a "zoomed-in" effect.

* Aspect Ratio:
    - 800.0f / 600.0f is the width/height ratio of the window (or screen), ensuring the projection accounts for the aspect of the display.
    - If your screen is square, the aspect ratio would be 1.0f. For a 16:9 screen, it would be around 1.78f.

* Near Plane (near):
    - 0.1f specifies the near clipping plane. Anything closer than this distance (from the camera) will be clipped.
    - It’s important that this value is greater than 0 — otherwise, OpenGL won’t know how to handle the projection mathematically.

* Far Plane (far):
    - 100.0f specifies the far clipping plane. Anything farther than this distance (from the camera) will be clipped.
     - A larger value will give you a greater depth range, but will also lead to depth precision issues (z-fighting) due to limited depth buffer precision.

Note: Even though you provide positive values for near and far clipping planes, the math internally negates them, because in OpenGL, the camera looks into negative Z. (because $$z_{view} < 0$$)
{: .notice--warning}

**What Happens with this Projection Matrix?**

After calling `glm::perspective()`, you get a 4x4 perspective projection matrix, which, when applied, maps 3D coordinates from view space into clip space, and eventually into NDC.

Here’s the key part of how it works:
* The near plane is mapped to z = -1 in NDC
* The far plane is mapped to z = +1 in NDC

The perspective projection matrix created by glm::perspective() looks like this:

```cpp
[ f/aspect  0      0                     0               ]
[ 0         f      0                     0               ]
[ 0         0     (far+near)/(near-far)   (2 * far * near) / (near - far) ]
[ 0         0     -1                    0               ]
```

This matrix transforms 3D geometry into clip space and NDC, giving you the typical perspective effect in 3D graphics.
{: .notice--success}


## Putting it all-together

Now that we created the transformation matrices we should pass them to our shaders. First let's declare the transformation matrices as uniforms in the vertex shader and multiply them with the vertex coordinates:

```cpp
#version 330 core
layout (location = 0) in vec3 aPos;
...
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ...
}
```

We should also send the matrices to the shader (this is usually done each frame since transformation matrices tend to change a lot):

```cpp
// create transformations
glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
	
model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
// Retrieve uniform locations
unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");

// Pass the matrices to the shader using glm::value_ptr for all
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
```

Now that our vertex coordinates are transformed via the model, view and projection matrix the final object should be:

* Tilted backwards to the floor.
* A bit farther away from us.
* Be displayed with perspective (it should get smaller, the further its vertices are).

Let's check if the result actually does fulfill these requirements:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl27.png)

## More 3D

So far we've been working with a 2D plane, even in 3D space, so let's take the adventurous route and extend our 2D plane to a 3D cube. To render a cube we need a total of 36 vertices (6 faces * 2 triangles * 3 vertices each)

```cpp
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //x, y, z, u, v
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
```

36 vertices (6 faces × 2 triangles per face × 3 vertices per triangle)
Each vertex has:
* Position: x, y, z
* Texture coordinates: u, v

The result would be something like this:

![Spinning Cube]({{ site.baseurl }}/assets/opengl/cube.gif)

It does resemble a cube slightly but something's off. Some sides of the cubes are being drawn over other sides of the cube. This happens because when OpenGL draws your cube triangle-by-triangle, fragment by fragment, it will **overwrite** any pixel color that may have already been drawn there before.

Since OpenGL gives no guarantee on the order of triangles rendered (within the same draw call), some triangles are drawn on top of each other even though one should clearly be in front of the other.
{: .notice--warning}

Luckily, OpenGL stores depth information in a buffer called the z-buffer that allows OpenGL to decide when to draw over a pixel and when not to. Using the z-buffer we can configure OpenGL to do depth-testing.
{: .notice--success}

### Z-buffer

OpenGL stores all its depth information in a z-buffer, also known as a depth buffer. GLFW automatically creates such a buffer for you (just like it has a color-buffer that stores the colors of the output image).

The depth is stored within each fragment (as the fragment's z value) and whenever the fragment wants to output its color, OpenGL compares its depth values with the z-buffer. If the current fragment is behind the other fragment it is discarded, otherwise overwritten. 

This process is called depth testing and is done **automatically** by OpenGL.

However, if we want to make sure OpenGL actually performs the depth testing we first need to tell OpenGL we want to enable depth testing; it is **disabled** by default. 

We can enable depth testing using `glEnable`. The `glEnable` and `glDisable` functions allow us to enable/disable certain functionality in OpenGL. That functionality is then enabled/disabled until another call is made to disable/enable it. Right now we want to enable depth testing by enabling `GL_DEPTH_TEST`:

```cpp
glEnable(GL_DEPTH_TEST);  
```

Since we're using a depth buffer we also want to clear the depth buffer before each render iteration (otherwise the depth information of the previous frame stays in the buffer). Just like clearing the color buffer, we can clear the depth buffer by specifying the `DEPTH_BUFFER_BIT` bit in the `glClear` function:

```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```
**More cubes!**

Say we wanted to display 10 of our cubes on screen. Each cube will look the same but will only differ in where it's located in the world with each a different rotation. 

The graphical layout of the cube is already defined so we don't have to change our buffers or attribute arrays when rendering more objects.
{: .notice--success}

The only thing we have to change for each object is its model matrix where we transform the cubes into the world.

First, let's define a translation vector for each cube that specifies its position in world space. We'll define 10 cube positions in a `glm::vec3 array:`

```cpp
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};
```

Now, within the render loop we want to call glDrawArrays 10 times, but this time send a **different model matrix** to the vertex shader each time before we send out the draw call. 

We will create a small loop within the render loop that renders our object 10 times with a different model matrix each time. Note that we also add a small unique rotation to each container.

```cpp
glBindVertexArray(VAO);
for(unsigned int i = 0; i < 10; i++)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i; 
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ourShader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
```

This snippet of code will update the model matrix each time a new cube is drawn and do this 10 times in total. Right now we should be looking into a world filled with 10 oddly rotated cubes:

![More Cubes]({{ site.baseurl }}/assets/opengl/spin-cubes.gif)

### What is Happening?
**VAO/VBO holds vertex data**

You store the cube’s vertex data (36 vertices) like this:

```cpp
glBindVertexArray(cubeVAO);
glDrawArrays(GL_TRIANGLES, 0, 36);
```
* This cube data is used over and over — no duplication.
* It's in GPU memory once.

**Shader applies transformation**

In your vertex shader:

```cpp
gl_Position = projection * view * model * vec4(aPos, 1.0);
```
* **aPos is the same cube vertex data each time** -  The values in aPos are local vertex positions — meaning they are relative to the cube's origin (the cube’s own local space). These positions don’t change from cube to cube — they are reused.
* But **model changes** every iteration of your C++ loop

That’s what makes each draw produce a cube in a different location and orientation

**CPU tells GPU: draw again with new model matrix**

```cpp
for (int i = 0; i < 10; ++i)
{
    glm::mat4 model = ...;                    // New transform
    shader.setMat4("model", model);           // Upload to GPU
    glDrawArrays(GL_TRIANGLES, 0, 36);        // Draw the same cube data again
}
```

So the vertex positions stay the same, but the transform makes them appear differently on screen.

Think of the cube vertex data as a rubber stamp, and the model matrix as your hand moving it to different spots and rotating it. Stamping action is the draw call and you're stamping the same shape onto different locations each frame for all 10 cubes.
{: .notice--success}

## Complete Source
[Download Source]({{ site.baseurl }}/assets/opengl/demo_3d.cpp){:target="_blank"}