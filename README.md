# Flappy Bird Console Game

**Author:** TomLifey
**Date:** 12 January 2026  

---

## Description
This is a **console-based Flappy Bird game** implemented in C++.  
The game is designed to run on both **Linux/macOS and Windows** consoles.  
It uses basic programming concepts learned in the course, such as:

- **Functions** for modular code.  
- **Loops** (`while`) for repeated actions.  
- **Conditional statements** (`if`, `else`, `switch`) for decision making.  
- **User input handling** with `w` or `space` to make the bird jump.  

---

## How to Play
1. Run the program in a terminal/console.  
2. Select **Start Game** from the menu.  
3. Press `w` or `space` to make the bird jump.  
4. Avoid the pipes (`|`). Each successfully passed pipe gives +1 score.  
5. The game ends when the bird collides with a pipe.  

---

## Features
- Adjustable **difficulty levels**: Easy, Medium, Hard.  
- **High score tracking** within the session.  
- Works on **Linux, macOS, and Windows**.  
- **Portable and simple console graphics**.  

---

## Files Included
- `FlappyBird.cpp` – Main game code.  
- `FlappyBirdFlowchart.png` – Flowchart illustrating game logic.  
- `FlappyBirdDocumentation.pdf` – Detailed explanation of the code.  

---

## Technical Details
- **Bird mechanics**: Gravity pulls the bird down; user input makes it jump.  
- **Pipe mechanics**: Pipes move from right to left; gap position is randomized.  
- **Collision detection**: Checks if bird overlaps with pipe positions.  
- **Screen clearing**: Uses ANSI escape codes for Linux/macOS and `cls` for Windows.  

---

## Requirements
- **C++ compiler** (g++, clang++)  
- **Linux/macOS or Windows console**  

---

## How to Compile and Run
### Linux/macOS:
```bash
g++ FlappyBird.cpp -o FlappyBird
./FlappyBird
### **Windows**

Windows (Command Prompt / PowerShell):
g++ FlappyBird.cpp -o FlappyBird.exe
FlappyBird.exe
