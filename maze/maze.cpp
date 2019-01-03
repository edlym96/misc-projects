#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <cstring>
#include "maze.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char** maze, int height, int width, int& row, int& col){
  for(int i=0; i<height; ++i){
    for(int j=0; j<width; ++j){
      if(maze[i][j] == ch){
	row = i;
	col = j;
	return true;
      } 
    }
  }
  row = -1;
  col = -1;
  return false;
}

bool valid_solution(const char* path, char** maze, int height, int width){
  int pos_x, pos_y;
  if(!find_marker('>', maze, height, width, pos_y, pos_x)){
    return false;
  }
  while((maze[pos_y][pos_x] == '>' || maze[pos_y][pos_x] == ' ') && *path != '\0'){
    if(*path == 'N'){
      --pos_y;
    }else if(*path == 'E'){
      ++pos_x;
    }else if(*path == 'S'){
      ++pos_y;
    }else if(*path == 'W'){
      --pos_x;
    }
    ++path;
  }
  if(maze[pos_y][pos_x] == 'X'){
    return true;
  }else{
    return false;
  }
}

string find_path(char** maze, int height, int width, char start, char end){
  int row, col;
  string path;
  char fake = ' ';
  if(!find_marker(start, maze, height, width, row, col)){
    return "NO SOLUTION";
  }
  maze[row][col] = '#';
  if(recursive_find(maze, fake, height, width, row, col, path, end)){
    return path; 
  }else{
    return "NO SOLUTION";
  }
}

bool recursive_find(char** maze, char previous_move, int height, int width, int row, int col, string& path, char end){

  const char moveset[] = "NESW";
  int counter = 0;
  while((!attempt_move(moveset[counter], maze, height, width, row, col, path) || !recursive_find(maze, moveset[counter], height, width, row, col, path, end))){
    if(counter > 3){
      //Return position if recursive find is false
      return false;
    }
  }
  return true;
}

bool attempt_move(char move, char** maze, int height, int width, int& row, int& col, string &path){
  std:: cout << "location " << row << col << " move " << move << endl;
  if(move == 'N'){
    --row;
  }else if(move == 'E'){
    ++col;
  }else if(move == 'S'){
    ++row;
  }else if(move == 'W'){
    --col;
  }
  if(row >= height || row < 0 || col >= width || col <0){
    if(move == 'N'){
      ++row;
    }else if(move == 'E'){
      --col;
    }else if(move == 'S'){
      --row;
    }else if(move == 'W'){
      ++col;
    } 
    return false;
  }
  if(maze[row][col] != '+' && maze[row][col] != '-' && maze[row][col] != '|' && maze[row][col] != '#'){
    path+=move;
    if(maze[row][col] == ' '){
      maze[row][col] = '#';
    }
    return true;
  }else{
    if(move == 'N'){
      ++row;
    }else if(move == 'E'){
      --col;
    }else if(move == 'S'){
      --row;
    }else if(move == 'W'){
      ++col;
    } 
    return false;
  }
}
