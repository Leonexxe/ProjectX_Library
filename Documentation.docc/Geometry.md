#### [projectX Library](./Documentation.md) > [math](./math.md) > [Geometry](./Geometry.md)
# ``Geometry``
#### This file acts as the documentation on the geometry part of the [projectX Library](./Documentation.md).

## ``Overview``

#### This part of the library includes functions that perform geometric operations.

## ``Topics``
1. Rotate2D
2. Distance

<hr>
<a name="vector"></a>

## ``Rotate2D``
The rotate2D function will rotate the point A around the point O by the measure of the angle ⍺ (alpha).
This function uses the following formula: <br>
	x: (cA * Ax-sA * Ay)+Ox<br>	
	y: (sA * Ax+cA * Ay)+Oy<br>
If you look at the implementation you will notice that A is not A but rather A'(Ax-Ox|Ay-Oy)
So if you want to check the results yourself then use this: <br>
	x = (Cos[⍺]*(Ax-Ox)-Sin[⍺]*(Ay-Oy))<br> 
	y = (Sin[⍺]*(Ax-Ox)+Cos[⍺]*(Ay-Oy))<br>
Here you can see a mathematical representation:<br>
![Screenshot of mathematical representation](./Resources/px_math_rotate2D_Formula.png)

#### ``vector<2,vectorType> px::rotate2D(__double__ alpha,vector<2,vectorType> pointA,vector<2,vectorType> pointO)``
This function will rotate A around O by ⍺ and return the rotated point.
