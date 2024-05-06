#include <fstream>
#include <vector>
#include <stack>
#include <string>

// Define a struct to represent positions on the grid.
struct Position {
    int row, col;
};

// Enumeration for directions to make the code more readable.
enum Direction { NORTH, EAST, SOUTH, WEST };

// Function to determine the direction of a move from one position to another.
Direction get_direction(Position from, Position to) {
    if (to.row < from.row) return NORTH;
    if (to.row > from.row) return SOUTH;
    if (to.col > from.col) return EAST;
    if (to.col < from.col) return WEST;
    return NORTH; // Default return to avoid compilation error
}

// Function to convert a direction enum into a string.
std::string direction_to_string(Direction dir) {
    switch (dir) {
        case NORTH: return "N";
        case EAST: return "E";
        case SOUTH: return "S";
        case WEST: return "W";
        default: return ""; // Added to avoid compilation error
    }
}

// Check if the position is valid within the grid bounds.
bool is_valid_position(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

// Depth-first search algorithm to find a path through the maze.
void dfs(const std::vector<std::vector<int> >& maze, std::vector<std::vector<bool> >& visited,
         Position current, const Position& goal, std::vector<Position>& path, bool& found) {
    if (found) return; // If a path is already found, stop the search.
    if (current.row == goal.row && current.col == goal.col) {
        found = true; // If the current position is the goal, the path is found.
        return;
    }

    // Generate all possible moves from the current position.
    Position moves[4] = {
        {current.row - maze[current.row][current.col], current.col}, // Move North
        {current.row, current.col + maze[current.row][current.col]}, // Move East
        {current.row + maze[current.row][current.col], current.col}, // Move South
        {current.row, current.col - maze[current.row][current.col]}  // Move West
    };

    // Try each possible move.
    for (int i = 0; i < 4; ++i) {
        Position next = moves[i];
        if (is_valid_position(next.row, next.col, maze.size(), maze[0].size()) &&
            !visited[next.row][next.col]) {
            visited[next.row][next.col] = true;
            path.push_back(next);
            dfs(maze, visited, next, goal, path, found); // Continue the search from the new position.
            if (found) return; // If a path has been found, stop the search.
            path.pop_back(); // Backtrack if the path is not found.
            visited[next.row][next.col] = false; // Unmark the position as visited.
        }
    }
}

int main() {
    // Open input and output files.
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");

    // Read the size of the maze.
    int rows, cols;
    infile >> rows >> cols;

    // Read the maze data.
    std::vector<std::vector<int> > maze(rows, std::vector<int>(cols));
    Position goal = {rows - 1, cols - 1};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            infile >> maze[i][j];
        }
    }

    // Initialize the visited matrix and the path vector.
    std::vector<std::vector<bool> > visited(rows, std::vector<bool>(cols, false));
    std::vector<Position> path;
    bool found = false;
    Position start = {0, 0};
    visited[start.row][start.col] = true;
    path.push_back(start);

    // Start the depth-first search from the starting position.
    dfs(maze, visited, start, goal, path, found);

    // Write the path to the output file or output "No path found!".
    if (!found) {
        outfile << "No path found!";
    } else {
        for (size_t i = 1; i < path.size(); ++i) {
            outfile << direction_to_string(get_direction(path[i - 1], path[i])) << " ";
        }
    }

    // Close the input and output files.
    infile.close();
    outfile.close();

    return 0;
}
