Glut3D
======

Glut3D is a Visual Studio 2017 project intended as a sample reference and guide for OpenGL/GLUT setup and getting started with writing 3D graphics programs.

Features
--------

Glut3D provides a console interface where the user can specify a current object and a rotation.

Note: The controls are handled using glutKeyboardFunc, which listens for keyboard presses and issues a callback. Since this does not involve standard input, your control will not be read if you try to enter it in the console window. The controls must be entered while the display window is selected. Once you have entered a control, then you will be asked to enter input to the console.

Installation
------------

Clone/download this repository:

- You can clone by opening a Git shell, cd'ing into your prefered directory, and typing the command `git clone https://github.com/sappqa/Glut3D-VS2017.git`
- You can download a zip file by clicking the green "Clone or download" button.

Once you have cloned the repository, open it in Visual Studio by double clicking on `Glut3D.sln`.

GLUT Setup
----------

Everything you will need to run this program can be found in the dependencies directory. Please follow these steps to set everything up:
1. Right click on the Glut3D project (or click on `Project` in the bar at the top of the window). Then go to `Properties`.
2. Resolve `#include <GL/Glut.h>` by navigating to `C/C++ -> General -> Additional Include Directories` and typing in `$(SolutionDir)/dependencies/freeglut/include`
