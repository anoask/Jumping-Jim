# Jumping-Jim

Solving the "Jumping Jim" Maze Problem


Problem Overview
The "Jumping Jim" maze problem is a pathfinding problem where each cell in a grid represents a trampoline with a number that tells the distance Jim can move horizontally or vertically. The challenge is to find a path from the top-left corner of the grid to the 'Goal' at the bottom-right.


Graph Model
To model the maze, I used a Directed Graph, where each vertex corresponds to a cell in the grid and each directed edge represents a possible move from one cell to another.

Vertices: Each vertex V(i,j) in the graph corresponds to the cell at row i and column j in the grid.

Edges: For each vertex V(i,j), I added directed edges to vertices that represent cells that Jim can reach from V(i,j) according to the number on the current cell's trampoline. Jim can move the exact number of cells either up, down, left, or right but not diagonally.
An edge from V(i,j) to V(k,l) exists if and only if: k=i and l=j±X, where X is the number on trampoline V(i,j), representing a horizontal move, or k=i±X and l=j, where X is the number on trampoline V(i,j), representing a vertical move. There will be no edge if moving X cells would go outside the grid's bounds.


Algorithm
The algorithm I used to solve this problem is the Depth-First Search (DFS) algorithm with backtracking.

Steps:
Begin at the starting vertex V(0,0).
Explore each edge from the current vertex to vertices that have not been visited yet, sticking to the rules dictated by the trampoline numbers.
If a move leads to the 'Goal' vertex V(goal), save this path as a potential solution.
If a dead-end is reached, backtrack to the previous vertex and explore other edges.
Continue this process til all possible paths have been explored, or the Goal vertex is reached.

The sequence of moves is identified in the following way:
Each time we move to a new vertex, we record the direction of the move (NORTH, EAST, SOUTH, WEST).
As we backtrack, we discard the last recorded move.
Once the Goal vertex is reached, the sequence of recorded moves represents the path Jim must take to reach the goal.

Pseudocode:
function DFS(Vertex current, Vertex goal, Graph G, Path moves) 
  if current is goal
    print "Path found!" and the sequence of moves 
    return true
  for each Vertex next in G.adjacentVertices(current) 
    if next is not visited
      mark next as visited
      direction = get_direction(current, next) 
      append direction to moves
      if DFS(next, goal, G, moves)
        return true
      remove last direction from moves 
      mark next as unvisited
  return false

main()
  Graph G = construct_graph_from_maze(maze_grid) 
  Path moves = empty list
  DFS(start_vertex, goal_vertex, G, moves)

Conclusion
By representing the "Jumping Jim" maze as a directed graph and utilizing a DFS algorithm with backtracking, we can effectively find a path for Jim to reach the goal. This approach combines the structural representation of the maze with an algorithm that makes sure all potential paths can be evaluated to identify the right sequence of moves for Jim.
