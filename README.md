Glut3D
======

Glut3D is a Visual Studio 2017 project intended as a sample reference and guide for OpenGL/GLUT setup and getting started with writing 3D graphics programs.

Features
--------

Glut3D provides a console interface where the user can specify a current object and a rotation.

Note: The controls are handled using `glutKeyboardFunc`, which listens for keyboard presses and issues a callback. Since this does not involve standard input, your control will not be read if you try to enter it in the console window. The controls must be entered while the display window is selected. Once you have entered a control, then you will be asked to enter input to the console.

Installation
------------

Clone this repository with the command `git clone https://github.com/sappqa/Glut3D-VS2017.git`.

Once you have cloned the repository, open it in Visual Studio by double clicking on `Glut3D.sln`.

GLUT Setup
----------

Everything you will need to run this program can be found in the dependencies directory. Please follow this guide for setting everything up:

We will be using a 32-bit binary, so first, we need to make sure Visual Studio is building for 32-bits. To do this:

- To the left of the green run button, make sure the build platform is `x86`.
- Right click on the Glut3D project (or click on `Project` in the bar at the top of the window). Then go to `Properties`.
- At the top of the properties window, make sure that the `Platform` is set to `Win32`.

If we try compiling the code as is (`ctrl+F7`), we will get the following compilation error: `cannot open source file "GL/glut.h"`. To resolve `#include <GL/glut.h>`:

- Go to `Project -> Properties` again.
- Navigate to `C/C++ -> General -> Additional Include Directories` and type in `$(SolutionDir)/dependencies/freeglut/include`.

Now that the header file has been found, we can compile without any problems! But remember, the header file does not actually contain the function definitions, so we will get a linker error, `cannot open file freeglut.lib` if we try to build the project. So now, we need to link the library `freeglut.lib`.

- Go back to `Project -> Properties`.
- Navigate to `Linker -> General -> Additional Library Directories` and type in `$(SolutionDir)/dependencies/freeglut/lib`.
- Navigate to `Linker -> Input -> Additional Dependencies` and type in `freeglut.lib`

If `freeglut.lib` was a <strong>static library</strong>, then we would be done now. However, since it is a <strong>dynamic library</strong>, this means that it is used to reference the contents of `freeglut.dll`, which contains the actual binary code of everything. The final step is simple:

- Move `dependencies/freeglut/bin/freeglut.dll` to the `Glut3D` directory.

And that should do it! Try building and running the program!

Support
-------

If you get stuck, here are some links that might help.

Contribute
----------

If you want to contribute, here is how.

License
-------
