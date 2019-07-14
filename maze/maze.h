#include <string>
/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

bool find_marker(char ch, char** maze, int height, int width, int& row, int& col);

bool valid_solution(const char* path, char** maze, int height, int width);
std::string find_path(char** maze, int height, int width, char start, char end);
bool recursive_find(char** maze, char previous_move, int height, int width, int row, int col, std::string& path, char end);
bool attempt_move(char move, char** maze, int height, int width, int& row, int& col, std::string& path);
