Collision Simulation

A 2D physics simulation built from scratch in C++ using Raylib. This project demonstrates custom vector math, collision detection, and positional/velocity resolution without relying on built-in physics engines (like Box2D).

Overview

The simulation features a ball bouncing perfectly inside a rotated square (diamond). It handles edge cases like boundary sticking, tunneling, and corner collisions by implementing manual position resolution and standard mathematical vector reflections.

Features

Custom Vector Math: Implements manual dot products for physics resolution.

Anti-Tunneling (Positional Resolution): Calculates penetration depth to push the ball out of walls before rendering the next frame, completely eliminating boundary sticking.

Perfect Corner Resolution: Ensures velocity is locked and only mathematically reflected once per frame to prevent vector corruption when wedged in corners.

Floating-Point Precision: Casts mathematical constants accurately to prevent velocity magnitude truncation over time.

🛠️ Prerequisites & Installation

This project uses a cross-platform Makefile. To build and run this project, you need a C++ Compiler, make, and Raylib. Follow the instructions for your operating system below:

🍎 macOS

Install Homebrew if you haven't already.

Open your terminal and install the compiler tools and raylib:

xcode-select --install
brew install raylib


(Note: The Makefile automatically supports both Apple Silicon M1/M2/M3 and Intel Macs).

🐧 Linux (Ubuntu/Debian)

Open your terminal and install the required build tools and dependencies:

sudo apt update
sudo apt install build-essential git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev


Install Raylib:

sudo apt install libraylib-dev


(If your distro does not have libraylib-dev, you may need to build Raylib from source using make install).

🪟 Windows

Install MSYS2.

Open the MSYS2 UCRT64 terminal and install the MinGW toolchain, Make, and Raylib:

pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-make
pacman -S mingw-w64-ucrt-x86_64-raylib


Add C:\msys64\ucrt64\bin to your Windows System Environment Variables PATH.

🚀 Building and Running

Clone the repository or download the source files.

Open a terminal (or Command Prompt/Git Bash) in the project directory.

Compile the project using Make:

make


Run the generated executable:

Linux & macOS: ./game

Windows: game.exe (or simply game)

To clean up the compiled binary, run:

make clean


🎮 Controls & Parameters

Currently, the simulation runs automatically upon launch. The initial velocity, position, and physics properties are hardcoded in main.cpp.

To alter the simulation, modify the following variables inside the main() function:

ball.speed_x and ball.speed_y: Adjusts the starting trajectory and speed.

ball.radius: Changes the size of the bouncing ball.

Change speed_x and speed_y to asymmetrical numbers (e.g., -7 and 4) to watch the ball bounce chaotically instead of in a straight repeating line!