---
title: "Vector Arithmetic"
excerpt_separator: "<!--more-->"
usemathjax: true
categories:
 - CG Math
tags:
 - Maths
---
{% include mathJax.html %}

Involves performing mathematical operations such as addition, subtraction, scalar multiplication, and dot product on vectors. 

<!--more-->

## Vector Multiplication by a Scalar
Although we cannot add a vector and a scalar, we can multiply a vector by a scalar.
*The result is a vector that is parallel to the original vector, with a different length and possibly opposite direction.*

![Alt Text](/assets/maths/math3.png)

<p>Geometrically, multiplying a vector by a scalar k has the effect of scaling the length by a factor of |k|. For example, to double the length of a vector we would multiply the vector by 2.</p>

## Vector Addition and Subtraction

### Adding two vectors:

We can add vectors $$\overrightarrow{a}$$ and $$\overrightarrow{b}$$ geometrically by positioning the vectors so that the head of a touches the tail of b and then drawing a vector from the tail of a to the head of b resulting $$\overrightarrow{(a+b)}$$.

![Alt Text](/assets/maths/math4.png)

When adding two vectors, it will result in what we call a resultant vector that combines the effects of the original vectors, starting from the origin
{: .notice--success}

### Subtracting two vectors:

When subtracting a vector, we can *negate* (multiplying by -1) the vector that we want to subtract then do the vector addition which leads to,

$$\overrightarrow{ab} = \overrightarrow{b} + (-\overrightarrow{a})$$

$$\overrightarrow{ab} = \overrightarrow{b} - \overrightarrow{a}$$

![Alt Text](/assets/maths/math5.png)

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

![Alt Text](/assets/maths/math6.png)

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

![Alt Text](/assets/maths/math9.png)

Assume for the moment that $$\hat{\mathbf{a}}$$ is a unit vector, and b is a vector of any length. Now take b and project it onto a line parallel to 
$$\hat{\mathbf{a}}$$

We can define the dot product $$\hat{\mathbf{a}} · b$$ as the **signed length** of the projection of b onto this line.
{: .notice--success}

*When we want to define this without unit vectors, we can say,*

The dot product $$\hat{a}.\hat{b}$$ is equal to the signed length of the projection of $$\hat{b}$$ onto any line parallel to $$\hat{a}$$, multiplied by the length of a.
{: .notice--success}


We have drawn the projections as arrows, but remember that the result of a dot product is a scalar, not a vector.
{: .notice--warning}

What does it mean for the dot product to measure a *signed length?* It means the value will be negative when the projection of b points in the opposite direction from $$\hat{\mathbf{a}}$$, and the projection has zero length (it is a single point) when $$\hat{\mathbf{a}}$$ and b are perpendicular. 

![Alt Text](/assets/maths/math10.png)

In other words, the sign of the dot product can give us a rough classification of the relative directions of the two vectors.

![Alt Text](/assets/maths/math11.png)

Before we switch to the second context of the dot product, let’s check out one more very common use of the dot product as a projection. 

Assume once more that $$\hat{\mathbf{a}}$$ is a unit vector and b has arbitrary length. Using the dot product, it’s possible to separate b into two values, $${b_x}$$ and $${b_y}$$ (read “b parallel” and “b perp”), which are parallel and perpendicular to $$\hat{\mathbf{a}}$$, respectively, such that 

$${b} =  {b_x} + {b_y}$$

![Alt Text](/assets/maths/math12.png)

Using dot product,

$${b_x} = \hat{\mathbf{a}}.b$$

$${b} =  {b_x} + {b_y}$$

$${b} =  \hat{\mathbf{a}}.b + {b_y}$$

So,

$${b_y} = {b} - \hat{\mathbf{a}}.b$$

*Context 2 : Trigonometry*

Now let’s examine the dot product through the lens of trigonometry. This is the more common geometric interpretation of the dot product, which
places a bit more emphasis on the angle between the vectors. 

![Alt Text](/assets/maths/math13.png)

Consider the right triangle on the right-hand side of above image. As the figure shows, the length of the hypotenuse is 1 (since $$\hat{\mathbf{b}}$$ is a unit vector) and the length of the base is equal to the dot product $$\hat{\mathbf{a}}$$ · $$\hat{\mathbf{b}}$$.

Therefore,

$$\cos \theta = \frac{\hat{\mathbf{a}}.\hat{\mathbf{b}}}{1}$$

In other words, the dot product of two unit vectors is equal to the cosine of the angle between them.
{: .notice--success}

Let's remove the unit vectors now,

![Alt Text](/assets/maths/math14.png)

Using above equation, we can say,

$$\cos \theta = \frac{a}{\left\lVert a \right\rVert} . \frac{b}{\left\lVert b \right\rVert}$$

Therefore,

$$a.b = {\left\lVert a \right\rVert}{\left\lVert b \right\rVert}\cos \theta$$

### Cross Product: