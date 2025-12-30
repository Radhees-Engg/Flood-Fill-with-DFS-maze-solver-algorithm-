# Flood-Fill-with-DFS-maze-solver-algorithm-
Maze solver using DFS exploration + Flood Fill (BFS) shortest path extraction with real-time visualization in Raylib.

This project implements a two-phase maze solving system with real-time visualization using Raylib.
The solver does not blindly search for the shortest path.
Instead, it first fully explores the maze once using DFS, records structural knowledge (visited paths and dead ends), and then computes the shortest path using Flood Fill (BFS) without re-exploration.

This mirrors how intelligent maze solvers (e.g., micromouse-style logic) separate exploration from optimization.

## Core Idea

### DFS Phase (Exploration)

Explores the maze from the start cell
Marks:

- VISITED cells
- DEAD_END cells when no unexplored neighbors remain
Uses an explicit stack for backtracking
Terminates once the entire reachable maze is explored

### Flood Fill Phase (Shortest Path Computation)

Starts from the end cell
Propagates distance values to all reachable cells using BFS
-Walls are treated as blocked (-1)
-The result is a distance gradient across the maze

### Path Extraction

- The bot moves from the start cell
- Always selects the neighboring cell with a lower flood-fill value
- This guarantees the shortest path
- The final path is rendered as a golden path

## Visualization
- Maze: 0 → PATH, 1 → BOT, 9 → END, 8 → WALL, 3 → DEAD_END, 2 → VISITED
- Raylib: Blue → Walls, Green → Visited cells, Pink → End cell, Red → Dead ends, Gold → Final shortest path, Gray circle → Bot

## Dependencies
- Language: C++
- Graphics: Raylib *(Make sure Raylib is properly installed and linked before building.)*

## Conclusion 
This project is inspired by maze-solving techniques used in autonomous robots, where the system first explores the environment 
to understand the maze layout and then determines an efficient path to the goal

**Soon I'll Implement this in my MazeMouse Robot**


**VIDEO:** https://www.linkedin.com/posts/radhees-bala-2a08652b4_autonomous-maze-solving-algorithm-developed-activity-7410948426101665792-UD0w?utm_source=share&utm_medium=member_android&rcm=ACoAAEuW6VgBPYjPBeU6XmIGHNi1sBbR9MCAjSo
