# CppND: Capstone Breakout Game Clone
---

[image1]: ./images/BA_01.png  " "
[image2]: ./images/BA_02.png  " "
[image3]: ./images/BA_03.png  " "
[image4]: ./images/BA_04.png  " "
[image5]: ./images/BA_05.png  " "


**Contents of this README**
- Building and runnning instructions
- Project structure 
- Addressed rubric points
 - Loops, Functions, I/O
 - Object oriented programming
---

This is a Breakout game clone implemented in C++ with SDL2. It is based on the [starter repo](https://github.com/udacity/CppND-Capstone-Snake-Game) for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

![][image2]

## Dependencies for Running Locally
* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* Eigen3 >= 3.3
  * All installation instructions can be found [here](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-eigen.md)
  * Ubuntu: sudo apt install libeigen3-dev
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./BreakoutGame`.
5. Use the mouse to move the racket. The left mouse button releases the ball.

## Project Structure

![][image3]

1. **main** creates a Racket, Ball, BrickWall object which are passed to the Game constructor by value. It also creates a Controller, Game and Renderer object. 
2. **main** calls Game::Run to start the game loop.

### Class Structure

![][image4]

The classes Ball, Brick and Racket inherit from Block since they share all of its properties.

![][image5]

The BrickWall class represents a collection of bricks and is created by composition. The Game class holds all the objects which define the game state.     

### Repo Structure

```
CppND-Capstone-BreakoutGame
│   CMakeLists.txt
│   README.md  
│
└───build
│   │   [build files]
│   │   BreakoutGame
│   │   ...
│
└───images
│   │   [images for the README.md]
│   │   ...
│  
└───include
│   │   [include files]
|   |   ball.h
│   │   ...
|
└───src
    │   [source files]
    │   ball.cpp
    |   ...
    |   main.cpp
```

The source files are mostly self-explanatory. **constants.h** holds parameters such as game geometry and colors. **misc.h** defines a class that holds color values.



## Rubric points

The project addresses the following rubric points:

### Loops, Functions, I/O

|     |     |     |
| --- | --- | --- |
| Criterium | Rubric Point | Description |
|#1|*The project demonstrates an understanding of C++ functions and control structures.* |As an example for C++ functions see Block::DetectCollision in block.cpp line 7ff. For control structues see Game::DetectCollision in game.cpp line 91ff.| 
|#2|*The project accepts user input and processes the input.*|The program accepts mouse input from the user. See Controler::HandleInput in controller.cpp line 62ff. |

### Object Oriented Programming

|     |     |     |
| --- | --- | --- |
| Criterium | Rubric Point | Description |
|#3|*The project uses Object Oriented Programming techniques.*|The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks. E.g. see class Block in block.h.|
|#4|*Classes use appropriate access specifiers for class members.*|All class data members are explicitly specified as public, protected, or private. E.g. see class Block in block.h.|
|#5|*Class constructors utilize member initialization lists.*|All class members that are set to argument values are initialized through member initialization lists. E.g. see class brick in Brick.h.|
|#6|*Classes follow an appropriate inheritance hierarchy.*|Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. The classes Ball, Brick and Racket inherit from Block since they share all its properties. The class BrickWall represents a collection of bricks and is created by composition.|













