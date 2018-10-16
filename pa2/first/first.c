#include <stdio.h>
#include <stdlib.h>

double** multiply(double**, double**, int, int, int, int);
double** inverse(double**, int, int);
double** transpose(double**, int, int);
double** subtract(double**, int, int, int, int, double);

double** multiply(double** mat1, double** mat2, int row1, int col1, int row2, int col2){

double** res;

  res = (double**)malloc(row1*sizeof(double*));
  
  int i;
  for(i=0; i<row1;i++){
      res[i]= (double*)malloc(col2*sizeof(double));
   }

  
  int j;
  int k;

 
  
  for(i=0; i<row1; i++){

    for(j = 0; j<col2; j++){
     
      for(k=0; k<row2; k++){

	res[i][j] += (mat1[i][k]*mat2[k][j]);
      }

    }


  }

  //check result once inverse method is made
  
  return res;

}

double** transpose(double** mat, int row, int col){

  double**res;

  res = (double**)malloc(col*sizeof(double*));
  
  int i;
  int j;
  for(i=0; i<col;i++){
      res[i]= (double*)malloc(row*sizeof(double));
   }

  for(i=0; i<col; i++){

    for(j = 0; j<row; j++){    

      res[i][j] = mat[j][i];

    }


  }

  return res;

}

double** inverse(double** mat, int row, int col){

 
  
  double** res;
  
  res = (double**)malloc(row*sizeof(double*));
  
  int i;
  for(i=0; i<row;i++){
      res[i]= (double*)malloc(col*sizeof(double));
   }

  
  int augCol;
  augCol = 2*col;
  
  double** augmented;

   augmented = (double**)malloc(row*sizeof(double*));
  
  for(i=0; i<row;i++){
      augmented[i]= (double*)malloc(augCol*sizeof(double));
   }

  double** identity;

  identity = (double**)malloc(row*sizeof(double*));

  
  for(i=0; i<row;i++){
      identity[i]= (double*)malloc(col*sizeof(double));
   }

  //create identity matrix will use to augment later
  int j;
   for(i=0; i<row; i++){

    for(j = 0; j<col; j++){    

      if(i==j){
	identity[i][j] = 1.0;
      }
      else{
	identity[i][j] = 0;
      }

    }

   }


  //fill first half of augmented matrix

   for(i=0; i<row; i++){

    for(j = 0; j<col; j++){    

      augmented[i][j] = mat[i][j];

    }

   }
  
   //augment with identity matrix

   for(i = 0; i < row; i++){

     for(j = col; j<augCol; j++){
       
       augmented[i][j] = identity[i][j-col];
     }


   }
   
   //find way to check if pivot or not, then create helper method to subtract rows
   //figure out how to find constant to subtract/multply by has to do with whatever target value is and reciprical
   int k;
   for(i=0; i<row; i++){

    for(j = 0; j<col; j++){    

      if(i==j){//pivot column must be 1

	if(augmented[i][j]!=1){
	  double val;
	  val = augmented[i][j];
	  for(k = j; k<augCol; k++){
	    augmented[i][k] = (augmented[i][k]/val);
	   }  
	}
	//make above and below 0
	  double constant;
	  int targRow;
	  //check above pivot
	  k = i;
	  while(k!=0){
	    if(augmented[k-1][j]!=0){
	      constant = augmented[k-1][j];
	      targRow = k-1;
		augmented = subtract(augmented, row, augCol, targRow, i, constant);
	      
	    }
	    k--;
	  }
	   
	

	  //check below pivot
	  k=i;
	   while(k!=row-1){
	    if(augmented[k+1][j]!=0){
	      constant= augmented[k+1][j];
	      targRow = k+1;
		augmented = subtract(augmented, row, augCol, targRow, i, constant);
	      
	    }
	    k++;
	   }
	 
	
      }
	  
    }
   }

  
   //build result using the second half of augmented
  
    for(i=0; i<row; i++){

    for(j = col; j<augCol; j++){    

      res[i][j-col] = augmented[i][j];

    }

   }
  


  return res;
}

double** subtract(double** mat, int row, int col, int targRow, int otherRow, double constant){

   double** res;
  
  res = (double**)malloc(row*sizeof(double*));
  
  int i;
  int j;
  for(i=0; i<row;i++){
      res[i]= (double*)malloc(col*sizeof(double));
   }

  //FILL res with mat data
  
   for(i=0; i<row; i++){

    for(j = 0; j<col; j++){    

      res[i][j] = mat[i][j];

    }

   }
   
   //subtract target row by other row

   for(i = 0; i<col; i++){

     res[targRow][i] = (mat[targRow][i]- (constant*mat[otherRow][i]));

   }



  return res;
}

int main(int argc, char** argv){

  if(argc != 3){
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

  //open file 2
  FILE *fp2;
  
  fp2 = fopen(argv[2], "r");
  
  if(fp2 == NULL){
    printf("Error\n");
    return 0;
  }

  fseek(fp2, 0, SEEK_END);
  
  length = ftell(fp2); //checks how large file is
 
  
  if(length == 0){
    printf("0\n"); //seek didnt move, file is empty
    return 0;
  }

  rewind(fp2);

  double **train;
  double **tPrice;
  
  int K;
  int N;
  
  fscanf(fp, "%d\n%d\n", &K, &N);
  
  K = K+1;

  //allocate mem for training mat and t price mat
  
  train = (double**)malloc(N*sizeof(double*));

  int i;
  for(i = 0; i<N; i++){
    train[i] = (double*)malloc(K*sizeof(double));
  }

  tPrice = (double**)malloc(N*sizeof(double*));

  for(i = 0; i<N; i++){
  tPrice[i] = (double*)malloc(sizeof(double));
  }
  
 
  
  //set train col 1 = 1

  for(i=0; i<N; i++){
    train[i][0] = 1.0;
  }
  
  
  //fill train and tPrice

  int count = 0;
  int j;
  
  for(i = 0; i<N; i++){
    for(j = 0; j<K; j++){
     
       if(count==K-1){
	fscanf(fp, "%lf", &tPrice[i][0]);
	count=0;
	break;
       }
      if(count!=K-1){ 
	fscanf(fp, "%lf%*[,]", &train[i][j+1]);
	count++;
      }
	
       
    }
  }

  K = K-1; //reset to use when building test matrix

  double** test;
  int houseCount;

  fscanf(fp2, "%d\n", &houseCount);
  
   test = (double**)malloc(houseCount*sizeof(double*));

  for(i = 0; i<houseCount; i++){
    test[i] = (double*)malloc(K*sizeof(double));
  }


   for(i = 0; i<houseCount; i++){
    for(j = 0; j<K; j++){
      
	fscanf(fp2, "%lf%*[,]", &test[i][j]);
       
    }
  }
   
   
   
    

   double** tp = transpose(train, N, K+1);

   double** mult = multiply(tp, train, K+1, N, N, K+1);
 
   double** invert = inverse(mult, K+1, K+1);
   
   double** w1 = multiply(invert, tp, K+1, K+1, K+1, N);

   double** W = multiply(w1, tPrice, K+1, N, N, 1);

   //calc price and print
   
   double price;
   for(i=0; i<houseCount; i++){

     price = W[0][0];
     
     for(j = 0; j<K; j++){

       price = price + (test[i][j] * W[j+1][0]);
       
      
     }
       printf("%0.0lf\n", price);

   }


  return 0;
}
