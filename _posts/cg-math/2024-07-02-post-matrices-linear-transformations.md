---
title: "Matrices and Linear Transformations"
date: 2024-07-02 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

This chapter continues our investigation of transformations

<!--more-->

## Rotation
### Rotation in 2D
A 2D rotation about the origin has only one parameter, the angle $$\theta$$, which defines the amount of rotation.

The standard convention found in most math books is to consider counterclockwise rotation positive and clockwise rotation negative.
{: .notice--primary}

![Alt Text]({{ site.baseurl }}/assets/maths/math48.png)

$$R(\theta) = \begin{pmatrix}-p' \\-q'\end{pmatrix}=\begin{pmatrix}\cos \theta & \sin \theta \\-\sin \theta & \cos \theta\end{pmatrix}$$

### 3D Rotation about Cardinal Axes
In 3D, rotation occurs about an **axis** rather than a point, with the term *axis* taking on its more commonplace meaning of a line about which something rotates.

An axis of rotation does not necessarily have to be one of the cardinal x, y, or z axes
{: .notice--warning}

we’ll need to establish which direction of rotation is considered “positive” and which is considered “negative.” We’re going
to obey the **left-hand** rule for this. 

#### Rotation about the x-axis
Let’s start with rotation about the x-axis, as shown in below. Constructing a matrix from the rotated basis vectors, we have:

$$R_x(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}1 & 0 & 0 \\0 & \cos \theta & \sin \theta \\0 & -\sin \theta & \cos\theta\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math49.png)

#### Rotation about the y-axis
Rotation about the y-axis is similar. The matrix to rotate about the y-axis is:

$$R_y(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}\cos \theta & 0 & -\sin \theta \\0 & 1 & 0 \\\sin \theta & 0 & \cos\theta\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math50.png)

#### Rotation about the z-axis
And finally, rotation about the z-axis is done with the matrix:

$$R_z(\theta) =\begin{pmatrix}p' \\q' \\r'\end{pmatrix}=\begin{pmatrix}\cos \theta & \sin \theta & 0 \\ -\sin \theta  & \cos \theta & 0 \\0 & 0 & 1\end{pmatrix}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math51.png)

### 3D Rotation about an Arbitrary Axis