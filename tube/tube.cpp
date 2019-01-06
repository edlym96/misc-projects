#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char** map, int height, int width, const char target, int &r, int &c){
  if(!isalnum(target)){
    r = -1;
    c = -1;
    return false;
  }
  for(int i=0; i<height; ++i){
    for(int j=0; j<width; ++j){
      if(map[i][j] == target){
	r = i;
	c = j;
	return true;
      }
    }
  }
  r = -1;
  c = -1;
  return false;
}

char get_symbol_for_station_or_line(const char* name){
  char line[512];
  char symbol;
  char place[256];
  ifstream in_stream;
  in_stream.open("stations.txt");
  in_stream.getline(line, 512);
  if(in_stream.fail()){
    in_stream.close();
    return ' ';
  }
  while(!in_stream.eof()){
    int i=2;
    for(; i<strlen(line); ++i){
      place[i-2] = line[i];
    }
    place[i-2] = '\0';
    if(!strcmp(place, name)){
      symbol = line[0];
      return symbol;
    }
    in_stream.getline(line, 512);
  }
  in_stream.close();
  in_stream.open("lines.txt");
  in_stream.getline(line, 512);
  if(in_stream.fail()){
    in_stream.close();
    return ' ';
  }
  while(!in_stream.eof()){
    int i=2;
    for(; i<strlen(line); ++i){
      place[i-2] = line[i];
    }
    place[i-2] = '\0';
    if(!strcmp(place, name)){
      symbol = line[0];
      return symbol;
    }
    in_stream.getline(line, 512);
  }
  in_stream.close();
  return ' ';
}

int validate_route(char** map, int height, int width, const char* start_station, const char* route, char* destination){
  int row;
  int col;
  char input[4];
  Direction previous_dir;
  int changes = 0;
  char symbol = get_symbol_for_station_or_line(start_station);
  if(symbol == ' '){
    return ERROR_START_STATION_INVALID;
  }
  if(!get_symbol_position(map, height, width, symbol, row, col)){
    return ERROR_START_STATION_INVALID;
  }  
  while(*route != '\0'){
    int count = 0;
    while(*route != ',' && *route != '\0'){
      input[count] = *route; 
      ++route;
      ++count;
    }
    input[count] = '\0';
    cout << input << endl;
    Direction dir = string_to_direction(input);
    char temp = map[row][col];
    if(dir == N){
      --row;
    }else if(dir == S){
      ++row;
    }else if(dir == W){
      --col;
    }else if(dir == E){
      ++col;
    }else if(dir == NE){
      ++col;
      --row;
    }else if(dir == NW){
      --col;
      --row;
    }else if(dir == SE){
      ++col;
      ++row;
    }else if(dir == SW){
      --col;
      ++row;
    }else if(dir == INVALID_DIRECTION){
      return ERROR_INVALID_DIRECTION;
    }
    
    if(row > height-1 || col > width-1 || row < 0 || col < 0){
      return ERROR_OUT_OF_BOUNDS;
    }
    if(map[row][col] == ' '){
      return ERROR_OFF_TRACK;
    }
    if(temp != map[row][col] && !is_station(temp) && !is_station(map[row][col])){
      return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
    }
    if(get_opposite_direction(dir) == previous_dir){
      return ERROR_BACKTRACKING_BETWEEN_STATIONS;
    }
    if(is_station(temp) && !is_station(map[row][col])){
      ++changes;
    }
    previous_dir = dir;
    ++route;
  }
  if(!is_station(map[row][col])){
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  }
  if(symbol_to_station(map[row][col], destination)){
    return changes;
  }else{
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  }
}

bool is_station(const char symbol){
  char line [512];
  ifstream in_stream;
  in_stream.open("stations.txt");
  in_stream.getline(line, 512);
  if(in_stream.fail()){
    in_stream.close();
    return false;
  }
  while(!in_stream.eof()){
    if(line[0] == symbol){
      return true;
    }
    in_stream.getline(line, 512);
  }
  return false;
}

Direction get_opposite_direction(Direction dir){
  if(dir == N){
    return S;
  }else if(dir == S){
    return N;
  }else if(dir == W){
    return E;
  }
  else if(dir == E){
    return W;
  }
  else if(dir == NE){
    return SW;
  }
  else if(dir == NW){
    return SE;
  }
  else if(dir == SE){
    return NW;
  }else if(dir == SW){
    return NE;
  }else{
    return INVALID_DIRECTION;
  }
}

bool symbol_to_station(const char symbol, char* station){
  char line [512];
  ifstream in_stream;
  in_stream.open("stations.txt");
  in_stream.getline(line, 512);
  if(in_stream.fail()){
    in_stream.close();
    return false;
  }
  while(!in_stream.eof()){
    if(line[0] == symbol){
      int i=2;
      for(; i<strlen(line); ++i){
	station[i-2] = station[i];
      }
      station[i-2] = '\0';
      return true;
    }
    in_stream.getline(line, 512);
  }
  in_stream.close();
  return false;
}
