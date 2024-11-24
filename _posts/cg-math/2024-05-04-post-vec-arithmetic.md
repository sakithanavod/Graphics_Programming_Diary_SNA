---
title: "Vector Arithmetic"
excerpt_separator: "<!--more-->"
usemathjax: true
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

Involves performing mathematical operations such as addition, subtraction, scalar multiplication, and dot/cross
 product on vectors. 

<!--more-->

**Table of Contents**
* TOC
{:toc}

## Vector Multiplication by a Scalar
Although we cannot add a vector and a scalar, we can multiply a vector by a scalar.
*The result is a vector that is parallel to the original vector, with a different length and possibly opposite direction.*

![Alt Text]({{ site.baseurl }}/assets/maths/math3.png)

<p>Geometrically, multiplying a vector by a scalar k has the effect of scaling the length by a factor of |k|. For example, to double the length of a vector we would multiply the vector by 2.</p>

## Vector Addition and Subtraction

### Adding two vectors:

We can add vectors $$\overrightarrow{a}$$ and $$\overrightarrow{b}$$ geometrically by positioning the vectors so that the head of a touches the tail of b and then drawing a vector from the tail of a to the head of b resulting $$\overrightarrow{(a+b)}$$.

![Alt Text]({{ site.baseurl }}/assets/maths/math4.png)

When adding two vectors, it will result in what we call a resultant vector that combines the effects of the original vectors, starting from the origin
{: .notice--success}

### Subtracting two vectors:

When subtracting a vector, we can *negate* (multiplying by -1) the vector that we want to subtract then do the vector addition which leads to,

$$\overrightarrow{ab} = \overrightarrow{b} + (-\overrightarrow{a})$$

$$\overrightarrow{ab} = \overrightarrow{b} - \overrightarrow{a}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math5.png)

If we have two points a and b, and if we subtract a from b then we get $$\overrightarrow{ab}$$.

$$\overrightarrow{ab} = b-a$$

$$\overrightarrow{ab} = (b_x - a_x , b_y - a_y)$$

**The point at the arrow of the vector should always come first.**

Another way to remember is, if it's (b-a) then vector starts from a and point towards b.
{: .notice}

Vector subtraction gives the displacement (vector) a to b and it holds the direction from a to b and also the distance (magnitude).
{: .notice--success}

If you have trouble remembering this, it might be a good idea to make a function to build a vector.

```
-- gives a vector from (x1,y1) point to (x2,y2) 
function vector(x1, y1, x2, y2)
    return x2 - x1, y2 - y1
end
```

**Example Usage of Vector Arithmetic**

![Alt Text]({{ site.baseurl }}/assets/maths/math6.png)

## Vector Multiplication

We can also multiply two vectors together. There are two types of vector products

* *Dot Product*
* *Cross Product*

### Dot Product:

The dot product of two vectors is the sum of the products of corresponding components, resulting in a *scalar* :

$${a.b} = (a_xb_x + a_yb_y)$$

Example:

$$\left[ 4 , 6 \right].\left[ -3 , 7 \right] = (4)(-3) + (6)(7) = 30$$

**Geometric Interpretation**

Now let’s discuss the more important aspect of the dot product: what it means geometrically.

*Context 1 : Projection*

![Alt Text]({{ site.baseurl }}/assets/maths/math9.png)

Assume for the moment that $$\hat{\mathbf{a}}$$ is a unit vector, and b is a vector of any length. Now take b and project it onto a line parallel to 
$$\hat{\mathbf{a}}$$

We can define the dot product $$\hat{\mathbf{a}} · b$$ as the **signed length** of the projection of b onto this line.
{: .notice--success}

*When we want to define this without unit vectors, we can say,*

The dot product $$\overrightarrow{a}.\overrightarrow{b}$$ is equal to the signed length of the projection of $$\overrightarrow{b}$$ onto any line parallel to $$\overrightarrow{a}$$ ( if the angle between them is $$\cos \theta$$ then, signed length of projection of $$\overrightarrow{b}$$ on to $$\overrightarrow{a}$$ is $${\left\lVert b \right\rVert}.\cos \theta$$ ), multiplied by the length of a.
{: .notice--success}


We have drawn the projections as arrows, but remember that the result of a dot product is a scalar, not a vector.
{: .notice--warning}

What does it mean for the dot product to measure a *signed length?* It means the value will be negative when the projection of b points in the opposite direction from $$\hat{\mathbf{a}}$$, and the projection has zero length (it is a single point) when $$\hat{\mathbf{a}}$$ and b are perpendicular. 

![Alt Text]({{ site.baseurl }}/assets/maths/math10.png)

In other words, the sign of the dot product can give us a rough classification of the relative directions of the two vectors.

![Alt Text]({{ site.baseurl }}/assets/maths/math11.png)

Before we switch to the second context of the dot product, let’s check out one more very common use of the dot product as a projection. 

Assume once more that $$\hat{\mathbf{a}}$$ is a unit vector and b has arbitrary length. Using the dot product, it’s possible to separate b into two values, $${b_x}$$ and $${b_y}$$ (read “b parallel” and “b perp”), which are parallel and perpendicular to $$\hat{\mathbf{a}}$$, respectively, such that 

$${b} =  {b_x} + {b_y}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math12.png)

Using dot product,

$${b_x} = \hat{\mathbf{a}}.b$$

$${b} =  {b_x} + {b_y}$$

$$
\mathbf{b}_{\perp} = \mathbf{b} - (\hat{\mathbf{a}} \cdot \mathbf{b}) \hat{\mathbf{a}}
$$

*Context 2 : Trigonometry*

Now let’s examine the dot product through the lens of trigonometry. This is the more common geometric interpretation of the dot product, which
places a bit more emphasis on the angle between the vectors. 

![Alt Text]({{ site.baseurl }}/assets/maths/math13.png)

Consider the right triangle on the right-hand side of above image. As the figure shows, the length of the hypotenuse is 1 (since $$\hat{\mathbf{b}}$$ is a unit vector) and the length of the base is equal to the dot product $$\hat{\mathbf{a}}$$ · $$\hat{\mathbf{b}}$$.

Therefore,

$$\cos \theta = \frac{\hat{\mathbf{a}}.\hat{\mathbf{b}}}{1}$$

In other words, the dot product of two unit vectors is equal to the cosine of the angle between them.
{: .notice--success}

Let's remove the unit vectors now,

![Alt Text]({{ site.baseurl }}/assets/maths/math14.png)

Using above equation, we can say,

$$\cos \theta = \frac{a}{\left\lVert a \right\rVert} . \frac{b}{\left\lVert b \right\rVert}$$

Therefore,

$$a.b = {\left\lVert a \right\rVert}{\left\lVert b \right\rVert}\cos \theta$$

*Let's check what happens when you use dot product on the vector it self*

$$\overrightarrow{a} . \overrightarrow{a} = {\left\lVert a \right\rVert} . {\left\lVert a \right\rVert}\cos \theta $$

Now $$cos0^{\circ} = 1 $$, therefore,

$$\overrightarrow{a} . \overrightarrow{a} = {\left\lVert a \right\rVert}^2$$

When you take the dot product of a vector with itself, you're essentially finding the square of its magnitude.
{: .notice--success}

#### Dot Product Recap!

1. Dot product can be defined as $$\hat{\mathbf{a}} · b$$ as the **signed length** of the projection of b onto this line.
2. Using this and by removing unit vectors, we can derive that $$a.b = {\left\lVert a \right\rVert}{\left\lVert b \right\rVert}\cos \theta$$
3. Also means that when $${a}$$ and $${b}$$ are unit vectors, dot product between them gives the cosine angle between those two vectors $$\cos \theta = {\hat{\mathbf{a}}.\hat{\mathbf{b}}}$$
4. From this (when a and b are unit vectors) we can say, when the angle between the vectors, $$(\theta)$$, is:
    * $$\theta = 0$$ (vectors are in the same direction):
   $$\cos(\theta) = 1 \Rightarrow a \cdot b = 1$$
    * $$\theta = 90$$ (vectors are perpendicular):
    $$\cos(\theta) = 0 \Rightarrow a \cdot b = 0$$
    * $$ \theta = 180^\circ $$ (vectors are in opposite directions):
   $$\cos(\theta) = -1 \Rightarrow a \cdot b = -1$$
5. When you use dot product on the vector it self, $$\overrightarrow{a} . \overrightarrow{a} = {\left\lVert a \right\rVert} .   {\left\lVert a \right\rVert}\cos \theta $$ and now $$cos0^{\circ} = 1 $$, therefore, $$\overrightarrow{a} . \overrightarrow{a} = {\left\lVert a \right\rVert}^2$$ meaning you're essentially finding the square of its magnitude.

### Cross Product:

the cross product, can be applied only in 3D. Unlike the dot product, which yields a scalar and is commutative, the vector cross product yields a *3D vector* and is not commutative.

If,

$${c} = {\mathbf{a} \times \mathbf{b}}$$

Then,

$${c_x} = {a_y* b_z - a_z*b_y}$$

$${c_y} = {a_z* b_x - a_x*b_z}$$

$${c_z} = {a_x* b_y - a_y*b_x}$$

#### Way to remember

For two 3D vectors $$a = (a_x, a_y, a_z)$$ and $$b = (b_x, b_y, b_z)$$, the cross product $$a \times b$$ can be calculated using the determinant of a 3x3 matrix:

$$
a \times b = \begin{vmatrix} \hat{i} & \hat{j} & \hat{k} \\ a_x & a_y & a_z \\ b_x & b_y & b_z \end{vmatrix}
$$

Expanding this determinant:

$$
a \times b = \hat{i} (a_y b_z - a_z b_y) - \hat{j} (a_x b_z - a_z b_x) + \hat{k} (a_x b_y - a_y b_x)
$$

*Geometric Interpretation*

The cross product yields a vector that is perpendicular to the original two vectors
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/maths/math18.png)

Because cross product is **not commutative**, we need to consider the order of a and b since it affects the direction of the resulting vector. You can determine the resulting vector *direction* by using the "Handy Guide" which uses your **Right Hand** (*only when if it's right handed coordinate system, otherwise use left hand*)

If,

$${\mathbf{a} \times \mathbf{b} = c}$$

![Alt Text]({{ site.baseurl }}/assets/maths/math19.png)

* "a" is index finger
* "b" is middle finger
* "c" is the result

or use,

![Alt Text]({{ site.baseurl }}/assets/maths/math54.jpg)

What is the relationship between the resulting vector of cross product other than it's perpendicular to other two vectors?.

*Context 1 : Determining the direction of rotation between two vectors*

![Alt Text]({{ site.baseurl }}/assets/maths/math21.png)

The direction of rotation between two vectors $${a}$$ and $${b}$$ refers to the orientation of the turn you would make to go from vector $${a}$$ to vector $${b}$$ around a given point (usually the origin). Specifically, this concept tells us whether the turn is clockwise or counterclockwise.
{: .notice--success}

We can determine the direction of $${\mathbf{a} \times \mathbf{b}}$$ by placing the tail of $${b}$$ at the head of $${a}$$, and examining whether we make a clockwise or counterclockwise turn from $${a}$$ to $${b}$$.

Check the sign of the resulting vector's z-component (assuming we're working in 2D or in 3D where the z-axis is perpendicular to the plane containing $${a}$$ and $${b}$$)
{: .notice--success}

For right handed coordinate systems, Z component ($${c_z} = {a_x* b_y - a_y*b_x}$$)
* If the z-component is positive, then you need to make a counterclockwise turn from $${a}$$ to $${b}$$
* If the z-component is negative, then you need to make a clockwise  turn from $${a}$$ to $${b}$$
* If the z-component is zero, the vectors are collinear, meaning they point in the same or opposite directions, and there is no need to turn
{: .notice--primary}

The cross product sign indicates whether the **shortest rotation** is clockwise or counterclockwise.
{: .notice--success}

*Context 2 : Geometric relationship*

As it turns out, length of the resulting vector $${c}$$ is also equal to the area of the parallelogram formed with two sides $${a}$$ and $${b}$$.
{: .notice--success}

![Alt Text]({{ site.baseurl }}/assets/maths/math20.png)

Area of parallelogram is equals to,

$$A = {\left\lVert b \right\rVert} h$$

We solve this equation a bit more, because $$\sin \theta = h/{\left\lVert a \right\rVert}$$

$$A = {\left\lVert b \right\rVert} {\left\lVert a \right\rVert} \sin \theta$$

Finally we get following equation,

$$\left\lVert \mathbf{a} \times \mathbf{b} \right\rVert =  {\left\lVert a \right\rVert} {\left\lVert b \right\rVert} \sin \theta$$

The length of $${\mathbf{a} \times \mathbf{b}}$$ is equal to the product of the magnitudes of $${a}$$ and $${b}$$ and the sine of the angle between $${a}$$ and $${b}$$
{: .notice--success}

But how we get the actual vector returned by the cross product? To that we can do following steps,

* *Calculate the magnitude*: $$\left\lVert \mathbf{a} \times \mathbf{b} \right\rVert =  {\left\lVert a \right\rVert} {\left\lVert b \right\rVert} \sin \theta$$
* *Determine Direction*: Use the right-hand rule (If we are in right handed coordinate system) to determine the direction of the resulting vector.
lets it call $${c} = \mathbf{a} \times \mathbf{b}$$
* *Construct Vector*: Combine the magnitude and direction to construct the resulting vector $${c}$$ Its magnitude is given by the value obtained in step 1, and its direction is determined by the right-hand rule.

So $${c}$$ can be expressed as,

$${c} = \left\lVert \mathbf{a} \times \mathbf{b} \right\rVert . \hat{n}$$

where $$\hat{n}$$ is a unit vector in the direction determined by the right-hand rule.

#### Cross Product Recap!

If,

$${c} = {\mathbf{a} \times \mathbf{b}}$$

1. The cross product $${a×b}$$ yields a vector perpendicular to both $${a}$$ and $${b}$$ (in 3D only).
2. The cross product is not commutative : $${\mathbf{a} \times \mathbf{b}} \neq {\mathbf{b} \times \mathbf{a}} \quad \text{but} \quad {\mathbf{a} \times \mathbf{b}} = -({\mathbf{b} \times \mathbf{a}})$$
3. If you know components of each vector, then you can use component formula to calculate cross product directly.
4. Direction of resulting vector of cross product can be determined by right hand rule.
5. Also if you have the resulting cross product component, then check the $${z}$$ component sign,
    * if it's positive - then resulting cross product vector points towards you and $${a}$$ vector should rotate (shortest) counter clockwise to reach b.
    * if it's negative - then resulting cross product vector points from you and $${a}$$ vector should rotate (shortest) clockwise to reach b.
6. If you know the angle between $${a}$$ and $${b}$$ which is  $$\sin \theta$$ then you can calculate the length of cross product vector by: $$\left\lVert \mathbf{a} \times \mathbf{b} \right\rVert =  {\left\lVert a \right\rVert} {\left\lVert b \right\rVert} \sin \theta$$

## Exercises

[Download Exercises]({{ site.baseurl }}/assets/exercises/maths/Ex_01/Chapter%2001%20-%20Vector%20-%20Excerises.pdf){:target="_blank"}

[Download Answers]({{ site.baseurl }}/assets/exercises/maths/Ex_01/Chapter%2001%20-%20Vector%20-%20Answers.pdf){:target="_blank"}