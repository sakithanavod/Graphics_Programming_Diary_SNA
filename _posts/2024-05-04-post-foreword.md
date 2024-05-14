---
title: "Points & Vectors - Introduction"
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
---
{% include mathJax.html %}

What are points and vectors? How they are related to game development.

<!--more-->

## Different Coordinate Systems

Let's talk about different coordinate systems first.

### Left Handed Coordinate Systems (Using your left hand)

Examples : Unity, Unreal

* X Axis - Thumb Finger Direction
* Y Axis - Index Finger Direction
* Z Axis - Middle Finger Direction (Which means Z goes **AWAY** from you)

![Alt Text]({{ site.baseurl }}/assets/maths/math15.png)

### Right Handed Coordinate Systems (Using your right hand)

Examples : Three.js, Godot

* X Axis - Thumb Finger Direction
* Y Axis - Index Finger Direction
* Z Axis - Middle Finger Direction (Which means Z goes **TOWARDS** you)

![Alt Text]({{ site.baseurl }}/assets/maths/math16.png)

Left-handed and right-handed coordinate systems also differ in the definition of “positive rotation.”

Now, if you tell me to “rotate $$30^{\circ}$$ about the axis,” how do I know which way to rotate? We need to agree between us
that one direction of rotation is the positive direction, and the other direction is the negative direction. The way to find this is to use following rules:

![Alt Text]({{ site.baseurl }}/assets/maths/math17.png)


## Points
Points are used to indicate a location/position relative to the origin of the coordinate system, and that's it! It's very simple. This is how a point is denoted in 2D Cartesian coordinate space.

![Alt Text]({{ site.baseurl }}/assets/maths/coordinate.png)

Here, we denoted a point in 2D coordinate space as **P(x,y).**

## Vectors
Geometrically speaking, a vector is a directed line segment that has **magnitude** and **direction**

![Alt Text]({{ site.baseurl }}/assets/maths/math1.png)

* The *magnitude* of a vector is the length of the vector.
* The *direction* of a vector describes which way the vector is pointing in space.

Examples for vectors are: 
* Displacement : “Take three steps forward.”
* Velocity : “I am traveling northeast at 50 mph.”

Vectors have both magnitude and direction. Usually, we denote vectors as follows:

$$\overrightarrow{AB}$$

## Vectors versus Points
*Points* has location in some coordinate system, but they don't have a size/thickness vise versa *Vectors* has a
magnitude and direction, but no position. So what is their relationship?

Vectors are used to describe displacements, and therefore they can describe **relative positions** (remember vectors don't have a fixed position in space. Instead, they describe how to get from one position to another.).

Imagine you're traveling from one city to another. You could describe your journey using a vector that points from the initial city to the destination city. This vector would indicate the direction you traveled and the distance you covered, but it wouldn't tell you exactly where those cities are located on a map. In essence, vectors allow us to focus on the relationship between points or objects rather than their absolute positions (here we build a relationship between two cities by relatively comparing each other).
{: .notice--primary}

Points are used to specify positions and any method of specifying a position must be relative.

For instance, if you say that a building is located at coordinates (3, 4) on a grid, those coordinates are relative to the origin of that grid. Similarly, if you say that a star is 10 light-years away from Earth, you're specifying its position relative to our planet.
{: .notice--primary}

**The Relationship between Points and Vectors**

![Alt Text]({{ site.baseurl }}/assets/maths/math2.png)

As you can see, if we start at the origin and move by the amount specified by the vector *[x, y]*, we will end up at the location described by the point
*(x, y)*.

We can also say that when we subtract two points, we get a vector. 

Another way of saying this is that the vector *[x, y]* gives the displacement from the origin to the point *(x, y)*.
{: .notice--success}


## Vector Magnitude (Length)

As we have discussed, vectors have magnitude and direction. However, you might have noticed that neither the magnitude nor the direction is expressed
explicitly in the vector so we must compute it. The magnitude of a vector is also known as the *length* of the vector.

![Alt Text]({{ site.baseurl }}/assets/maths/math7.png)

$$\left\lVert \vec{v} \right\rVert = \sqrt{v_x^2 + v_y^2}$$

## Unit Vectors / Normalized Vectors

For many vector quantities, we are concerned only with direction and not magnitude: “Which way am I facing?” “Which way is the surface oriented?” In these cases, it is often convenient to use unit vectors.

A *unit vector* is a vector that has a magnitude of one. Unit vectors are also known as **normalized** vectors.
{: .notice--success}

$$\hat{v} = \frac{v}{\left\lVert v \right\rVert}$$

where, 

$$\hat{v}$$ = unit vector

$${v}$$ = vector that needs to be normalized

$$\left\lVert \vec{v} \right\rVert$$ = length of the vector