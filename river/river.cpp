#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

#include "river.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
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

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++) 
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else 
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}


/* insert your functions here */

char** make_river_scene(const char* left, const char* boat){
  char** scene = create_scene();
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");
  int missionary_count = 0;
  int cannibal_count = 0;
  bool boat_on_left = false;
  while(*left!='\0'){
    if(*left == 'M'){
      add_to_scene(scene, 2, 1+missionary_count*6, "missionary.txt");
      missionary_count++;
    }else if(*left == 'C'){
      add_to_scene(scene, 11, 1+cannibal_count*6, "cannibal.txt");
      cannibal_count++;
    }else if(*left == 'B'){
      add_to_scene(scene, 17, 19, "boat.txt");
      boat_on_left = true;
    }
    ++left;
  }
  if(!boat_on_left){
    add_to_scene(scene, 17, 36, "boat.txt");
  }
  int spot = 0;
  while(*boat != '\0'){
    if(boat_on_left){
      if(*boat == 'M'){
	add_to_scene(scene, 11, 20+spot*6, "missionary.txt");
	missionary_count++;
	++spot;
      }else if(*left == 'C'){
	add_to_scene(scene, 11, 20+spot*6, "cannibal.txt");
	cannibal_count++;
	++spot;
      }
    }else{
      if(*boat == 'M'){
	add_to_scene(scene, 11, 39+spot*6, "missionary.txt");
	missionary_count++;
	++spot;
      }else if(*left == 'C'){
	add_to_scene(scene, 11, 39+spot*6, "cannibal.txt");
	cannibal_count++;
	++spot;
      }
    }
    ++boat;
  }
  for(int i=0; i<3-missionary_count; ++i){
    add_to_scene(scene, 2, 54+i*6, "missionary.txt");
  }
  for(int i=0; i<3-cannibal_count; ++i){
    add_to_scene(scene, 11, 54+i*6, "cannibal.txt");
  }
  return scene;
}

int perform_crossing(char* left, const char* target){
  int boat_on_left = false;
  int missionary_bank = 0;
  int cannibal_bank = 0;
  char* left_cpy = left;
  if(strlen(target)>2 || strlen(target)<1){
    return ERROR_INVALID_MOVE;
  }
  while(*left_cpy!='\0'){
    if(*left_cpy == 'M'){
      missionary_bank++;
    }else if(*left_cpy == 'C'){
      cannibal_bank++;
    }else if(*left_cpy == 'B'){
      boat_on_left = true;
    }else{
      return ERROR_INVALID_MOVE;
    }
    ++left_cpy;
  }
  if(!boat_on_left){
    missionary_bank = 3-missionary_bank;
    cannibal_bank = 3-cannibal_bank;
  }
  int missionary_count = 0;
  int cannibal_count = 0;
  while(*target!='\0'){
    if(*target == 'M'){
      missionary_count++;
    }else if(*target == 'C'){
      cannibal_count++;
    }else{
      return ERROR_INVALID_MOVE;
    }
    target++;
  }

  missionary_bank-=missionary_count;
  cannibal_bank-=cannibal_count;
  if(missionary_bank <0 || cannibal_bank < 0){
    return ERROR_INVALID_MOVE;
  }
  if(missionary_bank>0 && cannibal_bank>missionary_bank){
    return ERROR_MISSIONARIES_EATEN;
  }

  if(!boat_on_left){
    missionary_bank = 3-missionary_bank;
    cannibal_bank = 3-cannibal_bank;
  }
  
  int i=0;
  for(; i<cannibal_bank; ++i){
    left[i] = 'C';
  }
  for(; i<cannibal_bank+missionary_bank; ++i){
    left[i] = 'M';
  }
  if(!boat_on_left){
    left[i] = 'B';
    ++i;
  }
  left[i] = '\0';
  if(left[0] == '\0'){
    return VALID_GOAL_STATE;
  }else{
    return VALID_NONGOAL_STATE;
  }
}

int play_game(){
  char move[16];
  char left[16] = "CCCMMMB";
  int code = VALID_NONGOAL_STATE;
  while(code != VALID_GOAL_STATE && code != ERROR_MISSIONARIES_EATEN){
    char** scene = make_river_scene(left, "");
    print_scene(scene);
    cin >> move;
    code = perform_crossing(left, move);
    cout << status_description(code)<< endl;
  }
  return code;
}
