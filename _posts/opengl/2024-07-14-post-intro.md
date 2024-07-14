---
title: "OpenGL Intro"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---

Since you came here you probably want to learn the inner workings of computer graphics and do all the stuff the cool kids do by yourself.

<!--more-->

**Table of Contents**
* TOC
{:toc}

## OpenGL
Before starting our journey we should first define what OpenGL actually is. OpenGL is mainly considered an API (an Application Programming Interface) that provides us with a large set of functions that we can use to manipulate graphics and images.

The people developing the actual OpenGL libraries are usually the graphics card manufacturers. Each graphics card that you buy supports specific versions of OpenGL which are the versions of OpenGL developed specifically for that card (series).
{: .notice--primary}

## Core-profile vs Immediate mode
### Immediate mode
In the old days, using OpenGL meant developing in immediate mode (often referred to as the fixed function pipeline) which was an easy-to-use method for drawing graphics.

Most of the functionality of OpenGL was hidden inside the library and developers did not have much control over how OpenGL does its calculations.

The immediate mode is really easy to use and understand, but it is also extremely inefficient. For that reason the specification started to deprecate immediate mode functionality from version 3.2 onwards and started motivating developers to develop in OpenGL's core-profile mode, which is a division of OpenGL's specification that removed all old deprecated functionality.

### Core-profile
When using OpenGL's core-profile, OpenGL forces us to use modern practices. Whenever we try to use one of OpenGL's deprecated functions, OpenGL raises an error and stops drawing. The advantage of learning the modern approach is that it is very flexible and efficient. However, it's also more difficult to learn.

## Extensions
A great feature of OpenGL is its support of extensions. Whenever a graphics company comes up with a new technique or a new large optimization for rendering this is often found in an **extension** implemented in the drivers.

This way, a graphics developer can still use these new rendering techniques without having to wait for OpenGL to include the functionality in its future versions, simply by checking if the extension is supported by the graphics card.

The developer has to query whether any of these extensions are available before using them (or use an OpenGL extension library). This allows the developer to do things better or more efficient, based on whether an extension is available:

```cpp
if(GL_ARB_extension_name)
{
    // Do cool new and modern stuff supported by hardware
}
else
{
    // Extension not supported: do it the old way
}
```

## State machine
OpenGL is by itself a large state machine: *a collection of variables that define how OpenGL should currently operate.* The *state* of OpenGL is commonly referred to as the **OpenGL context**. 

When using OpenGL, we often change its state by setting some options, manipulating some buffers and then render using the current context.
{: .notice--success}

Whenever we tell OpenGL that we now want to **draw lines** instead of **triangles** for example, we change the state of OpenGL by changing some context variable that sets how OpenGL should *draw*. As soon as we change the context by telling OpenGL it should draw lines, the **next drawing commands** will now draw lines instead of triangles.

### More Examples for State machine behavior
#### Global State Management
OpenGL operates with a large set of global states that influence its behavior. These states are set using various OpenGL functions and **remain active until they are changed**. Examples of such states include the current color, texture bindings, transformation matrices, and many others.

#### State Changes Affect Subsequent Operations
The changes to OpenGL states affect **all subsequent rendering operations.** For example, setting the current color will affect the color of all vertices drawn afterward until the color state is changed again.

#### Function Calls Modify the State
Many OpenGL function calls modify the internal state of OpenGL. For instance, calling `glEnable(GL_DEPTH_TEST)` enables depth testing, changing the OpenGL state to perform depth testing on subsequent draw calls.

A draw call in OpenGL (or any graphics API) is a command issued by the CPU to the GPU to render a set of primitives (such as points, lines, or triangles) to the screen. 
{: .notice--success}

#### Querying the State
You can query the current state in OpenGL using various `glGet*` functions. This allows you to retrieve the current values of different states. For example, `glGetIntegerv(GL_VIEWPORT, viewport)` retrieves the current viewport dimensions.

When working in OpenGL we will come across several state-changing functions that change the context and several state-using functions that perform some operations based on the current state of OpenGL.
{: .notice--warning}

## Objects
In OpenGL, an object refers to a data structure that encapsulates various types of resources and states needed for rendering. These objects are used to manage and organize the information that the GPU requires to perform tasks such as rendering shapes, applying textures, and processing shaders.

An object in OpenGL is a collection of options that represents a subset of OpenGL's state.
{: .notice--success}

Example workflow: 

```cpp
// create object
unsigned int objectId = 0;
glGenObject(1, &objectId);
// bind/assign object to context (here its GL_WINDOW_TARGET context)
glBindObject(GL_WINDOW_TARGET, objectId);
// set options of object currently bound to GL_WINDOW_TARGET
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);

```

This little piece of code is a workflow you'll frequently see when working with OpenGL. 
1. We first create an object and store a reference to it as an id (the real object's data is stored behind the scenes). 
2. Then we bind the object (using its id) to the target location of the context (the location of the example window object target is defined as `GL_WINDOW_TARGET`).
3. Next we set the window options and finally we un-bind the object by setting the current object id of the window target to 0. 
4. The options we set are stored in the object referenced by objectId and restored as soon as we bind the object back to `GL_WINDOW_TARGET`.

The great thing about using these objects is that we can define more than one object in our application, set their options and whenever we start an operation that uses OpenGL's state, we bind the object with our preferred settings.
{: .notice--primary}

There are objects for example that act as container objects for 3D model data (a house or a character) and whenever we want to **draw** one of them, we **bind** the object containing the model data that we want to draw (we first created and set options for these objects). 

Having several objects allows us to specify many models and whenever we want to draw a specific model, we simply **bind** the corresponding object before drawing without setting all their options again.