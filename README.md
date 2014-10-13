C++ Coding Standards - Jason Gardella
=====================================

This file details the C++ coding standards which will be adhered to by Jason Gardella throughout CS585 Introduction to Game Development.

File Types
----------
All header files will be of type `.hh`, and all CPP files will be of type `.cpp`.

Structure
---------
A clear, sensible, rigorously followed code structure is paramount to understandable code. A good code structure is one in which everything is where the reader would expect it to be; as such, the reader can navigate the code with ease.

When possible, header files should *only* contain method and member declarations. All implementation should be placed in separate `.cpp` files. A noteable exception to this is when dealing with templates,
as for the template to accept all types, all implementation must be in the header file. Header files should follow this pattern:

- Header Guard 
- Includes
- Macros
- Namespace
- Structures and Unions
- Class Comment Block (described in further detail in comments section)
- Template
- Class Declaration
- Public Members and Methods
- Protected Members and Methods
- Private Members and Methods

Header files may contain multiple classes.

Similar methods should be grouped together in their own `.cpp` file, which should be named to indicate its contents and its associated headerfile.
For example, a file which contains getters and setters for a car class, which has the header file `car.hh` should be called `car_gettersandsetters.cpp`.

Internally, `.cpp` files should follow this pattern:

- Comment Block (describing what type of methods are in the file)
- Includes (the associated header file should be first)
- Method Implementations

Method implementations within the `.cpp` files should follow this pattern:

- Method Comment Block (described in further detail in comments section)
- Template Signature (if applicable)
- Method Signature
- Local Variables
- Rest of Method Body

Comments
--------
Ideally, code should be written such that it is self-explanatory to the reader. In cases in which this does not hold, or cases in which it is anticipated that the reader could have difficulty comprehending the code,
supplementary comments should be provided.

This concept also carries over into method comment blocks. Methods which have a clearly obvious function (e.g. getters and setters) should not have comment blocks. Methods which do necessitate comments will follow this pattern:

- General Description
- Parameter Explanation (each parameter on its own line)
- Return Explanation (if applicable, describe the different values which could possibly be returned)

Class comment blocks should simply be a short description of the class and its functionality.

Each `.cpp` file should have a comment block at the top with a short description of the methods it contains.

Always air on the side of caution. If you are not sure whether or not to add a comment, just add it. Too few comments inconveniences the reader more than too many comments. This is not to say that every line needs a comment, nor that over-commenting
is a trivial mistake; over-commenting can disrupt the flow of code and even make it more difficult to understand. In most situations, though, if you are unsure if a certain line requires a comment, just play it safe and add it.

Indentation
-----------
All indentation should be done using tabs. There should be an indentation used at every scope change.

Brace Placement
---------------
Braces for methods, classes, statements, etc. should always be placed on the next line, as this way the starting and ending brace for the block will line up horizontally.
All statements should use braces, even if their contents are only one line, for the sake of consistency and readability.

Naming
------
- Classes should be in PascalCase.
- Methods and variables should be in camelCase.
- Single letter variables should not be used except as an iterator in a for loop.
- Variable names should be indicative of what they hold.
- Boolean variables and methods which return a boolean should ask a true/false question (e.g. `bool isEnabled` or `bool isPositive(int num)`).

Spacing
-------
- On both sides of an operator, there should be one space.
- On the inside of parenthetical statements, there should be no space between the contents and the parenthesees.
