#include <iostream>
#include <cstring>

using namespace std;

const int M = 2;
const int N = 2;
const int R = 2;

void mat_mul(int mat_1[][N], int mat_2[][R], int mat_ans[][R], int rows_1, int rows_2, int rows_3);

int main(){
  int matrix_1[M][N];
  int matrix_2[N][R];
  int matrix_answer[M][R];

  cout << "INPUT FIRST (2 X 2) MATRIC: " << endl;
  for(int i=0;i<M;++i){
    cout << "Type in " << N << " values for row " << i << " separated by spaces";
    for(int j=0;j<N;j++){
      cin >> matrix_1[i][j];
    }
  }// TRY USING (WHILE(CIN>>X))

  cout << "INPUTS SECOND (2 X 2) MATRIC: " << endl;
  for(int i=0;i<N;++i){
    cout << "Type in " << R << " values for row " << i << " separated by spaces";
    for(int j=0;j<R;j++){
      cin >> matrix_2[i][j];
    } 
  }
  
  cout << matrix_1[0][0] << "  " << matrix_1[0][1] << endl;
  cout << matrix_1[1][0] << "  " << matrix_1[1][1] << endl;

  cout << matrix_2[0][0] << "  " << matrix_2[0][1] << endl;
  cout << matrix_2[1][0] << "  " << matrix_2[1][1] << endl;

  mat_mul(matrix_1, matrix_2,matrix_answer,M,N,M);

  cout << matrix_answer[0][0] << "  " << matrix_answer[0][1] << endl;
  cout << matrix_answer[1][0] << "  " << matrix_answer[1][1] << endl;

  
  return 0;
}

void mat_mul(int mat_1[][N], int mat_2[][R], int mat_ans[][R], int rows_1, int rows_2, int rows_3){
  for(int i=0; i<rows_3;++i){
    for(int j=0;j<R;++j){
      int ans=0;
      for(int k=0;k<N;++k){
	ans += mat_1[i][k]*mat_2[k][j];
      }
      mat_ans[i][j] = ans;
    }
  }
}
