---
title: "Polar Coordinate Systems"
date: 2024-11-25 09:00:00
excerpt_separator: "<!--more-->"
categories:
 - CG Math
tags:
 - Maths
 - Exercises
---
{% include mathJax.html %}

The Cartesian coordinate system isn’t the only system for mapping out space and defining locations precisely. An alternative to the Cartesian system is the polar coordinate system

<!--more-->

**Table of Contents**
* TOC
{:toc}

## 2D Polar Space
### Locating Points by Using 2D Polar Coordinates
2D polar coordinate space also has an origin (known as the pole), which has the same basic purpose—it defines the “center” of the coordinate space. A polar coordinate space has only one axis, however, sometimes called the polar axis, which is usually depicted as a ray from the origin.

![Alt Text]({{ site.baseurl }}/assets/maths/math70.png)

In the Cartesian coordinate system, we described a 2D point using two signed distances, `x` and `y`. The polar coordinate system uses **one distance** and **one angle**. 

By convention, the distance is usually assigned to the variable r (which is short for “radius”) and the angle is usually called `θ`. The polar coordinate pair `(r, θ)` specifies a point in 2D space as follows:

1. Start at the origin, facing in the direction of the polar axis, and rotate by the angle `θ`. Positive values of `θ` are usually interpreted to mean **counterclockwise rotation**, negative values mean **clockwise rotation**.

2. Now move forward from the origin a distance of `r` units. You have arrived at the point described by the polar coordinates `(r, θ)`.

![Alt Text]({{ site.baseurl }}/assets/maths/math71.png)

In summary, `r` defines the distance from the point to the origin, and `θ` defines the direction of the point from the origin.
{: .notice--success}

below diagram shows several points and their polar coordinates.

![Alt Text]({{ site.baseurl }}/assets/maths/math72.png)

You might have noticed that the diagrams of polar coordinate spaces contain grid lines

* The “grid circles” show lines of constant `r`
* The straight grid lines that pass through the origin show lines of constant `θ`

### Aliasing
Aliasing in polar coordinates occurs when a function or pattern sampled in the radial or angular direction is not represented accurately, leading to distortions or misinterpretations in the sampled data. This can happen due to insufficient resolution in either the radius `(r)` or the angle `(θ)`, or both.

For any given point, there are **infinitely** many polar coordinate pairs that can be used to describe that point
{: .notice--primary}

**Why this happens?**

The infinite nature of polar coordinate pairs arises from the infinite possibilities for the angle  `θ` and the negation of the radius `r`

**Angle Periodicity**

Angles in polar coordinates are periodic, meaning that any angle $${\theta}$$ can have infinitely many equivalent values by adding or subtracting multiples of $$2\pi$$ radians (or $$360^\circ$$ in degrees).

For a given $$(r, \theta)$$:

You can represent the same point using:
$$
(r, \theta), \quad (r, \theta + 2\pi), \quad (r, \theta - 2\pi), \quad (r, \theta + 4\pi), \quad (r, \theta - 4\pi), \dots
$$

Since there are infinitely many integers $${n}$$, the angle $${\theta + 2n\pi}$$ generates an infinite set of values for $${\theta}$$.

**Negative Radius**

The radius $${r}$$ in polar coordinates can be negative, which reflects the point across the origin. When $${r}$$ is negated, the angle $${\theta}$$ is shifted by $${\pi}$$ radians (or $$180^\circ$$):

For a given $$(r, \theta)$$:

You can represent the same point using:
$$
(-r, \theta + \pi), \quad (-r, \theta - \pi), \quad (-r, \theta + 3\pi), \quad (-r, \theta - 3\pi), \dots
$$

Since you can also apply the periodicity rule to $${\theta + \pi}$$ (adding or subtracting $$2\pi$$ infinitely), the negative radius introduces another infinite set of possibilities.

**Combining Both**

Combining the infinite possibilities of angle periodicity and the negative radius, the total number of representations becomes infinite because you can:

- Adjust $${\theta}$$ by $$2n\pi$$ for any integer $${n}$$.
- Switch $${r}$$ to $$-r$$ and adjust $${\theta}$$ by $$(2n+1)\pi$$.

For any point in polar coordinates $$(r, \theta)$$ (excluding the origin), all possible representations (aliases) can be expressed as:

$$
((-1)^n r, \theta + n \cdot 2\pi),
$$

where $${n}$$ is any integer.

- For $$n = 0$$: $$(r, \theta)$$
- For $$n = 1$$: $$(-r, \theta + \pi)$$
- For $$n = 2$$: $$(r, \theta + 2\pi)$$
- For $$n = 3$$: $$(-r, \theta + 3\pi)$$
- For $$n = 4$$: $$(r, \theta + 4\pi)$$

This pattern continues infinitely, alternating the radius sign and incrementing the angle by multiples of $$2\pi$$.

This phenomenon is known as aliasing. Two coordinate pairs are said to be aliases of each other if they have different numeric values but refer to the same point in space.
{: .notice--warning}

#### Canonical Coordinates
canonical coordinates refer to a unique, standardized representation of a point. They are used to avoid ambiguity that arises from having multiple equivalent representations of the same point.

For polar coordinates, canonical coordinates are a way of expressing $$(r, \theta)$$ such that:

1. $$r \geq 0$$ (non-negative radius).
2. $${\theta}$$ is within a specific range, typically:
   - $$0 \leq \theta < 2\pi$$ (for positive angles), or
   - $$-\pi < \theta \leq \pi$$ (for symmetric angles).

**Canonical Coordinates in Polar Coordinates**

Given a polar coordinate pair $$(r, \theta)$$, the canonical coordinates can be determined as follows:

**Ensure Non-Negative Radius ($$r \geq 0$$):**

If $${r < 0}$$, replace $$(r, \theta)$$ with $$(absolute(r), \theta + \pi)$$.

**Normalize the Angle ($$\theta$$):**

Convert $${\theta}$$ to a value within the desired range (e.g., $$0 \leq \theta < 2\pi$$ or $$-\pi < \theta \leq \pi$$) by adding or subtracting multiples of $$2\pi$$:

$$
\theta_{\text{canonical}} = \theta \mod 2\pi.
$$

**Example of Canonical Coordinates**

Point: $$( -5, \frac{7\pi}{4} )$$

1. **Radius:**  
   $$r = -5 \quad \text{(negative)},$$ so:
   $$
   r = |r| = 5, \quad \theta = \frac{7\pi}{4} + \pi = \frac{15\pi}{4}.
   $$

2. **Normalize $${\theta}$$ to $$0 \leq \theta < 2\pi$$:**  
   $$
   \frac{15\pi}{4} \mod 2\pi = \frac{7\pi}{4}.
   $$

**Canonical coordinates:**  
$$
(5, \frac{7\pi}{4}).
$$

### Converting between Cartesian and Polar Coordinates in 2D

![Alt Text]({{ site.baseurl }}/assets/maths/math72.png)

In a 2D plane, Cartesian coordinates $$(x, y)$$ represent a point using horizontal and vertical distances from the origin.  
Polar coordinates $$(r, \theta)$$ represent the same point using:

- $${r}$$: Radial distance from the origin.
- $${\theta}$$: Angle (in radians or degrees) from the positive x-axis to the line connecting the origin to the point.

#### From Cartesian $$(x, y)$$ to Polar $$(r, \theta)$$:

We can easily compute $${r}$$ by using the Pythagorean theorem:
$$
r = \sqrt{x^2 + y^2}.
$$

Since the square root function always returns the positive root, we don’t have to worry about $${r}$$ causing our computed polar coordinates to be outside the canonical set.

Computing $${r}$$ was pretty easy, so now let’s solve for $${\theta}$$:

$$
\frac{y}{x} = \frac{r \sin \theta}{r \cos \theta},
$$
$$
\frac{y}{x} = \frac{\sin \theta}{\cos \theta},
$$
$$
\frac{y}{x} = \tan \theta,
$$
$$
\theta = \arctan\left(\frac{y}{x}\right).
$$

Unfortunately, there are two problems with this approach:

1. If $$x = 0$$, the division is undefined.
2. The $$\arctan$$ function has a range of only $$[-90^\circ, +90^\circ]$$.

The basic problem is that the division $$\frac{y}{x}$$ effectively discards some useful information like what quadrant it actually belongs too.

To keep this info intact we can use $$\text{atan2}(y, x)$$
{: .notice--success}

**Why Use $${\text{atan2}}$$ Instead of $${\tan^{-1}(y/x)}$$?**

The standard arctangent function $${\tan^{-1}(y/x)}$$:

- Only works for points in Quadrants I and IV because it does not differentiate between positive and negative values of $${x}$$.
- Cannot handle cases where $${x = 0}$$ (division by zero).

$${\text{atan2}(y, x)}$$ resolves these issues:

- It uses both $${y}$$ and $${x}$$ directly to determine the correct quadrant and angle.
- Handles $${x = 0}$$ gracefully, assigning angles $${\pi/2}$$ or $$-\pi/2$$ depending on the sign of $${y}$$.

$$\text{atan2}(y, x)$$ can output an angle $${\theta}$$ in radians, where $${\theta \in (-\pi, \pi]}$$, ensures a complete representation of all quadrants:

- $$-\pi < \theta \leq -\pi/2$$: Quadrant III
- $$-\pi/2 < \theta < 0$$: Quadrant IV
- $$0 \leq \theta < \pi/2$$: Quadrant I
- $$\pi/2 < \theta \leq \pi$$: Quadrant II

Given Cartesian coordinates $$(x, y)$$, the polar coordinates are:

$$
r = \sqrt{x^2 + y^2},
\quad
\theta = \text{atan2}(y, x).
$$

- $$\sqrt{x^2 + y^2}$$: Calculates the distance of the point from the origin.
- $$\text{atan2}(y, x)$$: A special function that computes the angle $${\theta}$$ in the correct quadrant based on the signs of $${x}$$ and $${y}$$.  
  This avoids ambiguity and handles points in all quadrants.


#### From Polar $$(r, \theta)$$ to Cartesian $$(x, y):$$

Given polar coordinates $$(r, \theta)$$, the Cartesian coordinates are:

$$
x = r \cos(\theta),
\quad
y = r \sin(\theta).
$$

## 3D Polar Space
Polar coordinates can be used in 3D as well as 2D. As you probably havealready guessed, 3D polar coordinates have three values. But is the third coordinate another linear distance (like r) or is it another angle (like θ)?

Actually, we can choose to do either; there are two different types of 3D polar coordinates

1. If we add a linear distance, we have cylindrical coordinates
2. If we add another angle instead, we have spherical coordinates

### Cylindrical Coordinates

To extend Cartesian coordinates into 3D, we start with the 2D system, used for working in the plane, and add a third axis perpendicular to this plane.

This is basically how cylindrical coordinates work to extend polar coordinates into 3D

![Alt Text]({{ site.baseurl }}/assets/maths/math74.png)

Let’s call the third axis the z-axis, as we do with Cartesian coordinates. To locate the point described by the cylindrical coordinates `(r, θ, z)`.

#### Conversion between 3D Cartesian coordinates and cylindrical coordinates
The *z coordinate* is the **same** in either representation, and we convert between `(x, y)` and `(r, θ)`

### Spherical Coordinates
The more common kind of 3D polar coordinate system is a spherical coordinate system. Whereas a set of cylindrical coordinates has two distances and one angle, a set of spherical coordinates has two angles and one distance.

![Alt Text]({{ site.baseurl }}/assets/maths/math75.png)

Spherical coordinates describe a point in three-dimensional space using:

- $${r}$$: The radial distance from the origin to the point.
- $${\theta}$$: The azimuthal angle, measured in the $$xy$$-plane from the positive $$x$$-axis.
- $${\phi}$$: The polar angle (or inclination), measured from the positive $$z$$-axis.

**Visual Representation**

- $${r}$$: Represents the distance of the point from the origin.
- $${\theta}$$: Represents the angle of the point's projection onto the $$xy$$-plane relative to the positive $$x$$-axis.
- $${\phi}$$: Represents the angle between the radial line and the $$z$$-axis.

**Think of it as:**
- $${r}$$ gives the size of the sphere.
- $${\phi}$$ determines the latitude-like position (north-south direction).
- $${\theta}$$ determines the longitude-like position (east-west direction).

#### Canonical Form of Spherical Coordinates
The canonical form of spherical coordinates ensures that each point in 3D space has a unique, standardized representation. For spherical coordinates $$(r, \theta, \phi):$$

- $$r \geq 0$$: The radial distance is always non-negative.
- $$\theta \in [0, 2\pi)$$: The azimuthal angle is confined to one full rotation in the $$xy$$-plane.
- $$\phi \in [0, \pi]$$: The polar angle is limited to the range between the positive $$z$$-axis and the negative $$z$$-axis.

**Steps to Convert to Canonical Form**

1. **Normalize the Radial Distance ($$r$$):**

   If $$r < 0$$, flip the direction:
   $$
   r_{\text{canonical}} = -r, \quad 
   \theta_{\text{canonical}} = \theta + \pi, \quad 
   \phi_{\text{canonical}} = \pi - \phi.
   $$
   This ensures $$r \geq 0$$.

2. **Normalize the Azimuthal Angle ($$\theta$$):**

   If $$\theta \notin [0, 2\pi)$$, adjust it by adding or subtracting multiples of $$2\pi$$:
   $$
   \theta_{\text{canonical}} = \theta \mod 2\pi.
   $$

3. **Normalize the Polar Angle ($$\phi$$):**

   If $$\phi \notin [0, \pi]$$, adjust it:
   - If $$\phi < 0$$ or $$\phi > \pi$$, it may require reflection over the poles.

**Example: Normalize $$(r, \theta, \phi)$$**

**Input:** 
$$
(-3, 5\pi, -\pi/3)
$$

**Step 1: Normalize $${r}$$**

$$
r = -3, \quad \text{so flip the direction:}
$$
$$
r = 3, \quad \theta = 5\pi + \pi = 6\pi, \quad \phi = \pi - (-\pi/3) = \pi + \pi/3 = \frac{4\pi}{3}.
$$

**Step 2: Normalize $${\theta}$$**

$$
\theta = 6\pi:
$$
$$
\theta = 6\pi \mod 2\pi = 0.
$$

**Step 3: Normalize $${\phi}$$**

$$
\phi = \frac{4\pi}{3}:
$$
Since $$\phi > \pi$$, reflect it:
$$
\phi = 2\pi - \frac{4\pi}{3} = \frac{2\pi}{3}.
$$

**Canonical form:**
$$
(r, \theta, \phi) = (3, 0, \frac{2\pi}{3}).
$$

To ensure $${\phi \in [0, \pi]}$$:

- If $${\phi > \pi}$$, use:
  $$
  \phi = 2\pi - \phi.
  $$

- If $${\phi < 0}$$, bring it into the range by adding $$2\pi$$ repeatedly:
  $$
  \phi = \phi + 2\pi \quad \text{(repeat until $0 \leq \phi \leq \pi$)}.
  $$

#### Converting between Spherical and Cartesian Coordinates
![Alt Text]({{ site.baseurl }}/assets/maths/math76.png)

**Step 1: Decomposing $${r}$$ into Vertical and Horizontal Components**

The radial distance $${r}$$ can be broken into:

- **A vertical component along the $${z}$$-axis:**
  $$
  z = r \cdot \cos(\phi)
  $$
  This comes directly from the definition of the polar angle $${\phi}$$, where:
  $$
  \cos(\phi) = \frac{z}{r} \quad \implies \quad z = r \cdot \cos(\phi).
  $$

- **A horizontal component in the $${xy}$$-plane:**
  $$
  d = r \cdot \sin(\phi)
  $$
  Here, $${d}$$ is the projection of $${r}$$ onto the $${xy}$$-plane. The relationship comes from the Pythagorean theorem:
  $$
  \sin(\phi) = \frac{d}{r} \quad \implies \quad d = r \cdot \sin(\phi).
  $$

---

**Step 2: Decomposing $${d}$$ into $${x}$$ and $${y}$$**

In the $${xy}$$-plane, the azimuthal angle $${\theta}$$ determines the direction of the point. The horizontal component $${d}$$ can be further decomposed:

- $${x}$$: The projection of $${d}$$ along the $${x}$$-axis:
  $$
  x = d \cdot \cos(\theta) = r \cdot \sin(\phi) \cdot \cos(\theta).
  $$

- $${y}$$: The projection of $${d}$$ along the $${y}$$-axis:
  $$
  y = d \cdot \sin(\theta) = r \cdot \sin(\phi) \cdot \sin(\theta).
  $$

---

**Step 3: Combine All Components**

The final formulas for the Cartesian coordinates are:

- $${x:}$$
  $$
  x = r \cdot \sin(\phi) \cdot \cos(\theta).
  $$

- $${y:}$$
  $$
  y = r \cdot \sin(\phi) \cdot \sin(\theta).
  $$

- $${z:}$$
  $$
  z = r \cdot \cos(\phi).
  $$

#### From Cartesian $$(x, y, z)$$ to Spherical $$(r, \theta, \phi)$$:

Given Cartesian coordinates $$(x, y, z)$$, the spherical coordinates are:

1. **Radial Distance ($$r$$):**
   $$
   r = \sqrt{x^2 + y^2 + z^2}.
   $$

2. **Azimuthal Angle ($$\theta$$):**
   $$
   \theta = \text{atan2}(y, x),
   $$
   where $$\text{atan2}(y, x)$$ ensures the angle is in the correct quadrant.

3. **Polar Angle ($$\phi$$):**
   $$
   \phi = \arccos\left(\frac{z}{r}\right),
   $$
   provided $$r \neq 0$$ to avoid division by zero.