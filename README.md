C++ Coding Standards - Jason Gardella
=====================================

This file details the C++ coding standards which will be adhered to by Jason Gardella throughout CS585 Introduction to Game Development.

File Types
----------
All header files will be of type `.hh`, and all CPP files will be of type `.cpp`.

Structure
---------
A clear, sensible, rigorously followed code structure is paramount to understandable code. A good code structure is one in which everything is where the reader would expect it to be; as such, the reader can navigate the code with ease.

Header files will contain *only* variable declarations and method signatures within their classes. A method should *never* have its body implemented in the header file. All methods should be implemented in separate `.cpp` files. Header files should follow this pattern:

- Header Guard 
- Includes
- Namespace
- Structure and Unions
- Class Comment Block (described in further detail in comments section)
- Class Declaration
- Public Members and Methods
- Protected Members and Methods
- Private Members and Methods

Header files may contain multiple classes.

All body implementation will be done in separate `.cpp` files. Similar methods should be grouped together in their own `.cpp` file, which should be named to indicate its contents (e.g. all getters and setters could be grouped together
in a `.cpp` file called `gettersAndSetters.cpp`). `.cpp` files should follow this pattern:

- Comment Block (describing what type of methods are in the file)
- Includes (the associated header file should be first)
- Method Implementations

Method implementations within the `.cpp` files should follow this pattern:

- Method Comment Block (described in further detail in comments section)
- Template Signature (if applicable)
- Method Signature
- Method Body

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
