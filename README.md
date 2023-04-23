***

# AI Library [![Build (Windows)](https://github.com/RyanWestwood/AI-Library/actions/workflows/build-windows.yml/badge.svg?branch=main)](https://github.com/RyanWestwood/AI-Library/actions/workflows/build-windows.yml) [![Build (Linux)](https://github.com/RyanWestwood/AI-Library/actions/workflows/build-linux.yml/badge.svg?branch=main)](https://github.com/RyanWestwood/AI-Library/actions/workflows/build-linux.yml)

<p align="center">
    <img src="https://user-images.githubusercontent.com/55410510/233758470-3593449f-cf70-4ae0-9bbc-1b3e111ccf71.png" alt="AI Library">
</p>  
AI Library is a powerful and versatile C++ project designed to provide efficient implementations of pathfinding algorithms, finite state machines, and behavior trees. This library aims to assist developers in creating intelligent and high-performance applications, including games, simulations, and robotics. AI Library offers a user-friendly interface, comprehensive documentation, and examples to ensure seamless integration into your projects.

***  

# Table of Contents
- [Features](#features)
- [Getting Started](#gettingstarted)  
    - [Prerequisites](#prerequisites)  
    - [Installation](#installation)  
- [Usage](#usage)
    - [Pathfinding Algorithms](#pathfinding-algorithms)
    - [Finite State Machines](#finite-state-machines)
    - [Behavior Trees](#behavior-trees)
- [Running Tests](#runningtests)
- [Examples](#examples)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

***

# Features
* A wide range of pathfinding algorithms, including A*, Greed Best First, Bi Directonal, and more
* Support for Finite State Machines and Behavior Trees to model complex AI behaviors
* Modular and extensible design to facilitate customization and new algorithm implementations
* Comprehensive documentation, test suite, and practical examples
* Build scripts for easy compilation and integration into your projects

***

# Getting Started  
## Prerequisites  
* C++ compiler supporting C++20 or later
* CMake 3.8 or higher  
## Installation  
1. Clone the repository:
``` sh
git clone https://github.com/your_username/AI-Library.git
```  
2. Create a build directory:
``` sh
cd AI-Library
mkdir build
cd build
```
3. Run CMake to generate build files:
``` sh
cmake -S ../ -B .
```
4. Build the library:
``` sh
cmake --build .
```
5. Install the library:
``` sh
cmake --install . --prefix ../lib
```  

***

# Usage  
## Pathfinding Algorithms
``` cpp
#include <ai/pf/Algorithms.h>

// Add impl here
```
## Finite State Machines
``` cpp
#include <ai/fsm/StateManager.h>
// Add impl here
```
## Behavior Trees
``` cpp
#include <ai/Blackboard.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/composite/Sequence.h>
// Add impl here
```

***

# Running Tests  
placeholder

***

# Examples  
Check out the examples directory to find various practical examples that demonstrate the usage of the AI Library. These examples cover various aspects of the library, such as pathfinding, finite state machines, and behavior trees.

# Documentation 
Detailed documentation for the AI Library can be found in the docs directory. You can also generate the latest documentation using Doxygen:
``` sh
doxygen Doxyfile
```
This will generate the HTML documentation in the docs/html directory.

# Contributing  
Contributions are welcome! Please read our [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute and submit pull requests.

# License
AI Library is released under the [MIT License](LICENSE).
