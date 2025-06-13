cmake_minimum_required(VERSION 3.8)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")

add_compile_options(-Wall -Wextra -pedantic)

add_executable(MazeSolver 
  main.cpp
  Maze.cpp
  MazeDFSGenerate.cpp
  MazeKruskalGenerate.cpp
  MazeDFSSolve.cpp
  MazeBFSSolve.cpp
  MazeUtilities.cpp
  MazeNeighbors.cpp
  DisjointSetUnion.cpp
  MazeDraw.cpp
  MainMenu.cpp
  WindowSettings.cpp
  ConfigureMenu.cpp
  App.cpp
  EndScreen.cpp
  MazeWilsonGenerate.cpp
  MazeAStarSolve.cpp
  ConfigureMenuUtilities.cpp
)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(MazeSolver sfml-graphics sfml-window sfml-system)