/*******************************************************************************
 * Name        : mazesolver.cpp
 * Author      : Nicholas Cali
 * Date        : May 16, 2021
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Description : Uses recursive backtracking to solve a maze.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <stack>

using namespace std;

enum direction_t {
    NORTH, EAST, SOUTH, WEST
};

direction_t directions[] = {NORTH, EAST, SOUTH, WEST};

/**
 * Simple struct that represents a cell within the text-based maze.
 */
struct Cell {
    int row, col;

    /**
     * No-args constructor.
     */
    Cell() : row{0}, col{0} { }

    /**
     * Constructor that takes in (row, col) coordinates.
     */
    Cell(int _row, int _col) : row{_row}, col{_col} { }

    /**
     * Checks if two cells are equal.
     */
    bool operator==(const Cell &other) const {
        return row == other.row && col == other.col;
    }

    /**
     * Returns that cell reached from the current cell when moving in the
     * specified direction.
     */
    Cell adjacent_cell(const direction_t direction) const {
        switch (direction) {
            case NORTH:
                return Cell(row - 1, col);
            case EAST:
                return Cell(row, col + 1);
            case SOUTH:
                return Cell(row + 1, col);
            case WEST:
                return Cell(row, col - 1);
            default:
            	// Unknown direction -- just return a cell with the
            	// coordinates of the current cell.
                return Cell(row, col);
        }
    }

    /**
     * Allows for printing a cell from a cout statement.
     */
    friend std::ostream& operator<<(std::ostream& os, const Cell &cell) {
        os << "(" << cell.row << ", " << cell.col << ")";
        os.flush();
        return os;
    }
};

class MazeSolver {
public:
	/**
	 * Constructor for creating a MazeSolver. Takes as argument a string
	 * representing the filename of the text file containing the maze.
	 */
    explicit MazeSolver(const string &filename) :
        filename_{filename}, input_file_{filename.c_str()} {
        if (!input_file_) {
            throw runtime_error("File '" + filename + "' not found.");
        }
        input_file_.exceptions(std::ifstream::badbit);
        parse_file();
    }


    /**
     * Destructor. Used to free up memory allocated inside a MazeSolver.
     */
    ~MazeSolver() {
        //todo
        delete [] filename_.c_str();
    }

    /**
     * Returns the path length of the solution.
     */
    int path_length() const {
        // todo
        int row, col, i, j;
        row = i;
        col = j;
        int MazeSolver[1][1];
        if (row > 0 && MazeSolver[i-1][j] == ' '){
            return path_length(NORTH);
        }else if (row < num_cols_ && MazeSolver[i+1][j] == ' ') {
            return path_length(SOUTH);
        }else if (col > 0  && MazeSolver[i][j-1] == ' ' ){
            return path_length(EAST);
        }else if (col < num_rows_ && MazeSolver[i][j+1] == ' '){
            return path_length(WEST);
        }else{
            return path_length(Cell(row, col));
        }
 
    }

    /**
     * Attempts to solve the maze and returns whether or not a solution exists.
     */
    bool solve() {
        return solve(start_);
    }

    /**
     * Prints the ASCII maze on the screen with cout statements.
     */
    void display_maze() const {
        //todo
       int row, col; 
       int MazeSolver[1][1]; 
       for (int i = 0; i < col; i++){
           for(int j = 0; j < row;j++){
               cout <<  MazeSolver[i][j] << endl;
           }
           cout << endl;
        }
    }

    static const int
		WALL_CHARACTER = '#',
		MARK_CHARACTER = '.',
		SPACE_CHARACTER = ' ';

private:
    string filename_;
    ifstream input_file_;
    char **maze_;
    int num_rows_, num_cols_, path_length_;
    Cell start_, end_;

    /**
     * Parses the text file so that upon successful completion of this method,
     * maze_ is a 2D array of characters, start_ and end_ represent the two
     * open cells in the exterior of the maze, and path_length_ is initialized
     * to 0.
     */
    void parse_file() {
        vector<string> v;
        string line;
        while (getline(input_file_, line)) {
            v.push_back(line);
        }

        num_rows_ = v.size();
        if (num_rows_ == 0) {
            throw runtime_error("File '" + filename_ + "' is empty.");
        }
        num_cols_ = v[0].length();
        if (num_cols_ == 0) {
            throw runtime_error("File '" + filename_ + "' is empty.");
        }

        vector<Cell> points = start_and_end_points(v);

        maze_ = new char*[num_rows_];
        for (int row = 0; row < num_rows_; row++) {
            maze_[row] = new char[num_cols_];
            for (int col = 0; col < num_cols_; col++) {
                maze_[row][col] = v[row][col];
            }
        }
        start_ = points[0];
        end_ = points[1];
        path_length_ = 0;
    }

    /**
     * Takes as input a vector of strings and returns a vector of exactly two
     * cells, representing the starting and ending points in the exterior walls
     * in the maze.
     */
    vector<Cell> start_and_end_points(const vector<string> &v) const {
        vector<Cell> points;
        stack<Cell> st;
        unsigned int last_row = num_rows_ - 1, last_col = num_cols_ - 1;

        // TODO - missing section
        for (unsigned int i = 1; i < last_col;i++){
            for (unsigned int j = 1; j < last_row; j++){
                if (last_row == ' ' || last_col == ' ' ){
                    st.push(MazeSolver[i-1][j-1]);
                    points.push_back(st.top());
                    st.pop();
                }
            }
        }

        size_t num_openings = points.size();
        if (num_openings == 0) {
            throw runtime_error("Maze has no openings.");
        } else if (num_openings == 1) {
            throw runtime_error("Maze has only 1 opening.");
        } else if (num_openings > 2) {
            throw runtime_error(
                    "Ambiguous path. Maze has more than 2 openings.");
        }
        return points;
    }

    /**
     * Attempts to solve the maze and mark the path from the starting cell to
     * the ending cell. Uses recursive backtracking to mark the path.
     */
    bool solve(Cell cell) {
        //todo
        MazeSolver[row][col] = '#';
        if (row == cell.row && col == cell.col){
            return true;
        }else if (row > 0 && MazeSolver[row-1][col] == ' ' && solve(NORTH)){
            return true;
        }else if (row < num_cols_ && MazeSolver[row+1][col] == ' ' && solve(SOUTH)){
            return true;
        }else if (col > 0  && MazeSolver[row][col-1] == ' ' && solve(EAST)){
            return true;
        }else if (col < num_rows_ && MazeSolver[row][col+1] == ' ' && solve(WEST)){
            return true;
        }else{
            MazeSolver[row][col] = ' ';
            return false; 
        }
    }
};

// /**
//  * Main function for reading the command line arguments and producing output.
//  */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <maze file>" << endl;
        return 1;
    }
    MazeSolver *maze_solver = NULL;
    try {
        maze_solver = new MazeSolver(argv[1]);
        if (maze_solver->solve()) {
            cout << "Solution exists: YES" << endl
                 << "Total moves:     " << maze_solver->path_length()
                 << endl << endl;
            maze_solver->display_maze();
        } else {
            cout << "Solution exists: NO" << endl;
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Don't forget to delete the pointer to the maze solver.
    delete maze_solver;
    return 0;
}
