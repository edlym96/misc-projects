#include <iostream>
#include <fstream>
#include <cstring>
#include "spell.h"

using namespace std;

/* insert your function definitions here */
int frequency(const char* target){
  ifstream in_stream;
  int freq;
  char word[512];
  in_stream.open("words.dat");
  in_stream >> freq;
  bool is_freq = false;
  while(!in_stream.eof()){
    if(!is_freq){
      in_stream >> word;
    }else{
      in_stream >> freq;
    }
    if(!strcmp(word, target)){
      in_stream.close();
      return freq;
    }
    is_freq = !is_freq;
  }
  in_stream.close();
  return -1;
}

int edit_distance(const char* a, const char* b){
  int i,j;

  i = strlen(a);
  j = strlen(b);
  return get_distance(a, b, i, j);
}

int get_distance(const char* a, const char* b, int m, int n){
  int matrix[m+1][n+1];
  matrix[0][0] = 0;

  for(int i=1; i<m+1; ++i){
    matrix[i][0] = i+1;
  }
  for(int j=1; j<n+1; ++j){
    matrix[0][j] = j+1;
  }
  for(int j=1; j<n+1; ++j){
    for(int i=1; i<m+1; ++i){
      matrix[i][j] = min(matrix[i-1][j]+1, matrix[i][j-1]+1);
      matrix[i][j] = min(matrix[i][j], matrix[i-1][j-1] + indicator(a[i-1], b[j-1]));
      if(i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){
	matrix[i][j] = min(matrix[i][j], matrix[i-2][j-2]+1);
      }
    }
  }
  return matrix[m][n];
  /* int answer;
  if(min(i,j) == 0){
    return max(i,j);
  }else if(i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){
    answer = min(get_distance(a,b,i-1,j)+1,get_distance(a,b,i,j-1)+1);
    answer = min(answer, get_distance(a,b,i-1,j-1)+indicator(a[i-1], b[j-1]));
    answer = min(answer, get_distance(a,b,i-2,j-2)+1);
    return answer;
  }else{
    answer = min(get_distance(a,b,i-1,j)+1, get_distance(a,b,i,j-1)+1);
    answer = min(answer, get_distance(a,b,i-1,j-1)+indicator(a[i-1], b[j-1]));
    return answer;
  }
  */
}

int max(int i, int j){
  if(i > j){
    return i;
  }else{
    return j;
  }
}

int min(int i, int j){
  if(j > i){
    return i;
  }else{
    return j;
  }
}

int indicator(const char a, const char b){
  if(a != b){
    return 1;
  }else{
    return 0;
  }
}

bool spell_correct(const char* word, char* fixed){
  ifstream in_stream;
  int freq;
  int current_min = 9999;
  int dist;
  char suggested[512];
  in_stream.open("words.dat");
  in_stream >> freq;
  while(!in_stream.eof()){
    in_stream >> suggested;
    dist = edit_distance(word, suggested);
    if(current_min > dist){
      strcpy(fixed, suggested);
      current_min = dist;
    }
    in_stream >> freq;
  }
  in_stream.close();
  if(current_min > 0){
    return true;
  }else{
    strcpy(fixed, "");
    return false;
  }
}
