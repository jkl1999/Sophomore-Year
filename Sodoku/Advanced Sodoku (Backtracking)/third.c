#include <stdio.h>
#include <stdlib.h>

int** mat;

int inRow(int, int);
int inCol(int, int);
int inSub(int, int, int);
int recursiveSolve();
int hasEmpty();

int hasEmpty(){
  int i;
  int j;
  
  for(i = 0; i<9; i++){
    for(j = 0; j<9; j++){
      
      if(mat[i][j] == 0){

	return 0;
      }

    }
  }


  return 1; //no zeros
}

int recursiveSolve(){
  // 0 is no solution, 1 is successful
  int i;
  int j;
  int k=1;

  for(i = 0; i<9; i++){
    for(j = 0; j<9; j++){
      
      if(mat[i][j] == 0){ //need to fill value
       
	while(k!=10){
	  //check if number fits constraints
   if((inRow(i, k) == 0) && (inCol(j, k) == 0) && (inSub(i,j,k) == 0)){
	    // printf("%d\n", k);
	   
            mat[i][j] = k;
	    
	    int check = recursiveSolve();
	    if(check == 1){	     
	      return hasEmpty();
	    }
	      //reset to try next num
	    mat[i][j] = 0;	  
	    
	  }
	  k++;
	}

	return hasEmpty(); // tried every value - not succesful 
	
      }
     
     }
  }

  return hasEmpty();
}

int inRow( int row, int target){
  int truthValue=0;
  int i;
  
  for(i=0; i<9; i++){

    if(mat[row][i] == target){
      truthValue = 1;
    }

  }
  

  return truthValue;
}


int inCol(int col, int target){
  int truthValue=0;

  int i;
  
  for(i=0; i<9; i++){

    if(mat[i][col] == target){
      truthValue = 1;
    }

  }

  return truthValue;
}

int inSub(int row, int col, int target){
  int truthValue=0;
  int i;
  int j;

  int rNew = row - row%3;
  int cNew = col - col%3;

  for(i = rNew; i<rNew+3; i++){
    for(j = cNew; j<cNew+3; j++){

      if(mat[i][j] == target){
	truthValue = 1;
      }
 
   }
  }
  

  return truthValue;
}

int main(int argc, char** argv){

  
  if(argc != 2){
    return 0; //not enough args
  }

  FILE *fp;
  
  fp = fopen(argv[1], "r");
  
  if(fp == NULL){
    printf("Error\n");
    return 0;
  }

  fseek(fp, 0, SEEK_END);
  
  int length = ftell(fp); //checks how large file is
 
  
  if(length == 0){
    printf("0\n"); //seek didnt move, file is empty
    return 0;
  }

  rewind(fp);

  //create and fill matrix with test file data

  mat = (int**)malloc(9*sizeof(int*));

  int i;

  for(i = 0; i<9; i++){
    mat[i] = (int*)malloc(9*sizeof(int));
    
  }

  int j;
  
  for(i = 0; i<9; i++){
    for(j = 0; j<9; j++){
      
      fscanf(fp, "%d\t", &mat[i][j]);

    }
  }


  int solved;
  solved = recursiveSolve();

  if(solved == 1){
  for(i = 0; i<9; i++){
    for(j = 0; j<9; j++){
      
      printf("%d\t", mat[i][j]);

    }
    printf("\n");
  }

 }

  if(solved == 0){
    printf("no-solution\n");

  }
  return 0;
}
