# Maze generator and solver
A C++23 SFML application that lets you **generate and solve mazes** using classic algorithms like DFS, BFS, A*, Wilson’s, and Kruskal’s – all with real-time animation and a minimalistic GUI.

## Maze internals

- The maze grid is stored as `std::vector<std::vector<int>> maze;`  
  - `0` = **PATH**  White color
  - `1` = **WALL** Black color
  - `2` = **SOLUTION** Green color
  _Grey color is used in solving algs. to show which path they visited._

- Coordinates are `(col, row)` where  
  - `col` -> x (0 … width−1)  
  - `row` -> y (0 … height−1)  
- **Start** cell = `(1,1)`
- **Goal** = `(width−2, height−2)`  
- **Dimensions** are always **odd** to ensure a proper wall‐path alternation.

-----

## Features
Between generating / adding cycles / solving there is *2 second* pause

#### 1. Menu & UI  
- **Main menu** (`MainMenu.cpp`) base menu of the program 
- **Configure menu** (`ConfigureMenu.cpp`) to set width, height, cycles, algorithms, etc.
- **End screen** (`EndScreen.cpp`) showing “Success!” if everything went smoothly 
- **VertexArray renderer** (`MazeDraw.cpp`) to put all cells into one draw call 
_The window is resizable – even during generation or solving._ 

#### 2. Maze generation  
- **DFS** (`MazeDFSGenerate.cpp`) – randomized depth-first carving  
- **Kruskal** (`MazeKruskalGenerate.cpp`) – randomized walls removal via DSU  
- **Wilson** (`MazeWilsonGenerate.cpp`) – loop-erased random walks 

### 3. Maze solving  
- **DFS solver** (`MazeDFSSolve.cpp`)  
- **BFS solver** (`MazeBFSSolve.cpp`)  
- **AStar solver** (`MazeAStarSolve.cpp`) with Manhattan distance heuristic  

_All solvers animate tracking and final path in distinct colors._

### 4. Utilities  
- **Random cycles** (`MazeUtilities.cpp::addRandomCycles`) for removing random walls within the given probability
- **EnumUtilities** for clean `CellType` int conversions
- **MazeUtilities** (`MazeUtilities.cpp`) - overall utilities for maze
- **Configuring Menu Utilities** (`ConfiguringMenuUtilities.cpp`) - overall utilities for menu configuration

### Support classes
- `DisjointSetUnion` – used in Kruskal’s algorithm
- `MazeDraw.cpp` – drawing logic and viewport handling

The main logic and maze structure is defined in `Maze.h`.
-----

## Building

**Requirements**  
- C++23
- [SFML 2.5.1](https://www.sfml-dev.org/)  
- CMake 3.8+

```bash
mkdir build && cd build
cmake ..
make
cd ..
./build/MazeSolver  # Run it like this because assets are located outside the build folder
```
-----

## Usage
Run the program:
```bash
./build/MazeSolver
```
- Configure -> move to the configuration menu
- Exit -> quit application

Maze size
- choose size of cols and rows from 5 to 999
_Sizes above 101x101 will not be generated/solved via *live animation* since it takes too long._  

Maze Generation
- Choose one of DFS, Kruskal or Wilson

Maze Solving
- Choose one of DFS, BFS or A*

End Screen
- you can choose to Exit or Re-configure which will take you back to the configuring menu

Keyboard controls:
- ↑/↓ to navigate menus
- ←/→ to choose values in configure menu
- Enter to select