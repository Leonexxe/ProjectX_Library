#### [projectX Library](./Documentation.md) > [math](./math.md)
# ``Math``

#### This file acts as the documentation on the math part of the [projectX Library](./Documentation.md).

## ``Overview``

#### This part of the library includes functions that perform both mathematic and geometric operations.

## ``Topics``
1. [Random](#random)
2. [Vector](#vector)
3. [Range](#range)
4. [Geometry](./Geometry.md)
	- 2 dimensional Geometry
	- n-dimensional Geometry

<hr>
<a name="random"></a>

## ``Random``
The random function generates a random integer and returns it as the type passed to the ``returnType`` template argument
#### ``px::random()``
This is the default version of the px::random function

#### ``px::random(inputType min, inputType max,std::list<inputType>* exclude = nullptr)``
This is version of the function takes a mininum, a maximum and a list of numbers to exclude, it then generates a number in between min and max that is also not on the exclude list.
please note that this overload is not realtime safe

<hr>
<a name="vector"></a>

## ``Vector``
The vector class is intended to be used to store an n-dimensional set of data, such as coordinates.
For example this could be used to represent a location in a 2 dimensional coordinate system
This class only exists in case we decide to implement more functionality into it, at the time of writing this we could use std::vector without any issues, in fact this class actually stores it's data as an std::vector object
#### ``px::vector::vector(std::vector<dataType> data)``
This overload of the constructor takes an std::vector object holding the type that is specified in the dataType template argument.
#### ``dataType px::vector::get(__int__ index)``
This function will return the value stored at the specified index
#### ``void px::vector::set(__int__ index,dataType value)``
This function will store the value specified at the specified index

<hr>
<a name="range"></a>

## ``Range``
The range class stores information on a range of integers
#### ``px::range::range(numType min, numType max)``
This overload of the constructor takes a minimum and a maximum for the range
#### ``bool isInRange(numType n)``
This member function checks if the specified number is within the range
#### ``bool isInRange(range<numType> r)``
This function checkes if this range is within the specified range r
