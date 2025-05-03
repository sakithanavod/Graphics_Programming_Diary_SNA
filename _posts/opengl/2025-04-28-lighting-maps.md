---
title: "Lighting maps"
excerpt_separator: "<!--more-->"
categories:
 - OpenGL 
tags:
 - opengl
---
{% include mathJax.html %}

In the previous chapter we discussed the possibility of each object having a unique material of its own that reacts differently to light. This is great for giving each object a unique look in comparison to other objects, but still doesn't offer much flexibility on the visual output of an object.

<!--more-->

**Table of Contents**
* TOC
{:toc}

##  OpenGL Rendering Pipeline Overview

1. Vertex Processing
- Your vertices (positions, normals, tex coords, etc.) go into the vertex shader
- Output: transformed positions ($$gl\_Position$$) in clip space
- This step runs once per vertex

2. Primitive Assembly
- OpenGL connects vertices into primitives (triangles, lines, etc.)

3. Clipping
- Any part of the triangle outside the view frustum is clipped

4. Perspective Division + Viewport Transform
- $$gl\_Position$$ is converted to Normalized Device Coordinates (NDC) by dividing by $$w$$
- Then NDC → screen space (pixels)

5. Rasterization
- This is where triangles are turned into fragments
- For each screen pixel covered by the triangle, a fragment is created
- Interpolates values (e.g. TexCoords, normals, colors) across the triangle surface

6. Fragment Shader (Pixel Shader)
- Runs once per fragment
- Computes final color, lighting, textures, etc.
- Can discard fragments or write depth

7. Per-Fragment Tests
- Depth test, stencil test, alpha test, blending, etc.
- Decides if the fragment is written to the framebuffer

Final Output: A Pixel on the Screen
- Only the fragment that passes all tests will write its color to the actual pixel on the screen

## What Is a Fragment in OpenGL?
A fragment in OpenGL is not exactly a pixel, but it's the **data for a pixel** candidate during rasterization — it contains all the information needed to compute the final color of a pixel on the screen.

Each fragment includes:
* Its position on the screen
* Interpolated values like texture coordinates, normals, colors
* Depth and stencil info

Only one fragment per pixel usually survives (after depth test), and becomes the actual pixel color.

**Think of a Pixel Like a Slot on the Screen**

Only one fragment is ultimately used per pixel, but multiple fragments can compete for that pixel during rendering. Here’s how:

*What Actually Happens*

**A Fragment Is a "Pixel Candidate"**

Each time a **triangle** overlaps a screen pixel, one fragment is generated for that triangle at that pixel.

So if 3 triangles overlap the same pixel, you get 3 fragments — one from each triangle — all with:

* Their own depth value
* Their own color, lighting, texture values

**The Depth Test Decides Which Fragment "Wins"**

OpenGL runs a depth test (if enabled) to compare which fragment is closest to the camera. Only the one passing the test is written to the screen. The rest are **discarded** silently.

**Imagine this 1-pixel area:**

```cpp
[Pixel]
  ^
  | <- Fragment from Triangle A (depth = 0.5)
  | <- Fragment from Triangle B (depth = 0.7)
  | <- Fragment from Triangle C (depth = 0.4) ← closest (wins)

```

The fragment from Triangle C passes the depth test and becomes the final color of the pixel.

## Lighting maps
In the previous chapter we defined a material for an entire object as a whole. Objects in the real world however usually do not consist of a single material, but of several materials. 

Think of a car: its exterior consists of a shiny fabric, it has windows that partly reflect the surrounding environment, its tires are all but shiny so they don't have specular highlights and it has rims that are super shiny.

The car also has diffuse and ambient colors that are not the same for the entire object; a car displays many different ambient/diffuse colors. All by all, such an object has different material properties for each of its different parts.

So the material system in the previous chapter isn't sufficient for all but the simplest models so we need to extend the system by introducing diffuse and specular maps.

These allow us to influence the diffuse (and indirectly the ambient component since they should be the same anyways) and the specular component of an object with much more precision.

## Diffuse maps

What Are Diffuse Colors?
Diffuse color refers to the base color of a surface that is visible under direct light, coming from all directions. It represents how a material scatters light in many directions when illuminated.
{: .notice--primary}

What we want is some way to set the diffuse colors of an object for each individual fragment. Some sort of system where we can retrieve a color value based on the fragment's position on the object?

This should probably all sound familiar and we've been using such a system for a while now. This sounds just like textures we've extensively discussed in one of the earlier chapters and it basically is just that: a texture.

We're just using a different name for the same underlying principle: using an image wrapped around an object that we can index for unique color values per fragment. 

In lit scenes this is usually called a diffuse map (this is generally how 3D artists call them before PBR) since a texture image represents all of the object's diffuse colors.

### Why Do We Care About Fragments for Diffuse Maps?
When rendering a 3D object with a texture (diffuse map), you want:
* Each fragment (i.e. each spot on the triangle surface) to use the correct color from the texture.
* That texture gives the diffuse color for that spot on the surface.


### Sampling Diffuse maps

To demonstrate diffuse maps we're going to use the following image of a wooden container with a steel border:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl44.png)

Using a diffuse map in shaders is exactly like we showed in the texture chapter. This time however we store the texture as a sampler2D inside the Material struct. We replace the earlier defined `vec3` diffuse color vector with the diffuse map.

Keep in mind that sampler2D is a so called opaque type which means we can't instantiate these types, but only define them as uniforms. If the struct would be instantiated other than as a uniform (like a function parameter) GLSL could throw strange errors; the same thus applies to any struct holding such opaque types.
{: .notice--warning}

We also remove the ambient material color vector since the ambient color is equal to the diffuse color anyways now that we control ambient with the light. So there's no need to store it separately:

```cpp
struct Material {
    sampler2D diffuse;
    vec3      specular;
    float     shininess;
}; 
...
in vec2 TexCoords;
```

Note that we are going to need texture coordinates again in the fragment shader, so we declared an extra input variable. Then we simply sample from the texture to retrieve the fragment's diffuse color value:

```cpp
vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
```

Also, don't forget to set the ambient material's color equal to the diffuse material's color as well:

```cpp
vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
```

or

```cpp
vec3 diffuseColor = texture(material.diffuse, TexCoords).rgb;

vec3 ambient = light.ambient * diffuseColor;
vec3 diffuse = light.diffuse * diff * diffuseColor;
```

And that's all it takes to use a diffuse map. As you can see it is nothing new, but it does provide a dramatic increase in visual quality. 

To get it working we do need to update the vertex data with texture coordinates, transfer them as vertex attributes to the fragment shader, load the texture, and bind the texture to the appropriate texture unit.
{: .notice--success}

```cpp
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
...
out vec2 TexCoords;

void main()
{
    ...
    TexCoords = aTexCoords;
}  
```

Be sure to update the **vertex attribute pointers** of both VAOs to match the new vertex data and load the container image as a texture. Before rendering the cube we want to assign the right texture unit to the `material.diffuse` uniform sampler and bind the container texture to this texture unit:
{: .notice--primary}

```cpp
lightingShader.setInt("material.diffuse", 0);
...
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, diffuseMap);
```

Now using a diffuse map we get an enormous boost in detail again and this time the container really starts to shine (quite literally). 

## Specular maps
You probably noticed that the specular highlight looks a bit odd since the object is a container that mostly consists of wood and wood doesn't have specular highlights like that. 

We can fix this by setting the specular material of the object to vec3(0.0) 

but that would mean that the steel borders of the container would stop showing specular highlights as well and steel **should** show specular highlights.

We would like to control what parts of the object should show a specular highlight with varying intensity. This is a problem that sounds familiar. Coincidence? I think not.

We can also use a texture map just for specular highlights. This means we need to generate a black and white (or colors if you feel like it) texture that defines the specular intensities of each part of the object. An example of a specular map is the following image:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl45.png)

The intensity of the specular highlight comes from the **brightness** of each pixel in the image. Each pixel of the specular map can be displayed as a color vector where black represents the color vector vec3(0.0) and gray the color vector vec3(0.5) for example. 

In the fragment shader we then sample the corresponding color value and multiply this value with the light's specular intensity. 

The more 'white' a pixel is, the higher the result of the multiplication and thus the brighter the specular component of an object becomes.

Because the container mostly consists of wood, and wood as a material should have no specular highlights, the entire wooden section of the diffuse texture was converted to black: 

black sections do not have any specular highlight. The steel border of the container has varying specular intensities with the steel itself being relatively susceptible to specular highlights while the cracks are not.

In your fragment shader:

```glsl
vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
```
* spec is the intensity based on light and angle.
* texture(...) returns the intensity mask per fragment (from the specular map).
* So black → kills specular, white → lets it through fully, gray → partial control.

## Sampling specular maps
A specular map is just like any other texture so the code is similar to the diffuse map code. Make sure to properly load the image and generate a texture object.

Since we're using another texture sampler in the same fragment shader we have to use a different texture unit (see Textures) for the specular map so let's bind it to the appropriate texture unit before rendering:

```cpp
lightingShader.setInt("material.specular", 1);
...
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, specularMap);  
```

Then update the material properties of the fragment shader to accept a sampler2D as its specular component instead of a vec3:

```cpp
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};  
```

And lastly we want to sample the specular map to retrieve the fragment's corresponding specular intensity:

```cpp
vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
FragColor = vec4(ambient + diffuse + specular, 1.0);   
```

By using a specular map we can specify with enormous detail what parts of an object have shiny properties and we can even control the corresponding intensity. Specular maps give us an **added layer of control** over lighting on top of the diffuse map.

If you would now run the application you can clearly see that the container's material now closely resembles that of an actual wooden container with steel frames:

![Alt Text]({{ site.baseurl }}/assets/opengl/gl46.png)

Using diffuse and specular maps we can really add an enormous amount of detail into relatively simple objects. We can even add more detail into the objects using other texture maps like **normal/bump maps and/or reflection maps**, but that is something we'll reserve for later chapters. 

![Spinning Cube]({{ site.baseurl }}/assets/opengl/materials.gif)

[Download Lighting + Materials Source]({{ site.baseurl }}/assets/opengl/demo_lighting_materials.rar){:target="_blank"}