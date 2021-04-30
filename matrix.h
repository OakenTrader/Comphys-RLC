#include <stdio.h>
#include <math.h>
#define N 10
#define N2 100

#ifndef MATRIX_H
#define MATRIX_H

void M3Display(double A[N][N][N],int mat, int row, int col);
void MDisplay(double A[N][N], int n);
void MDisplay2(double A[N2][N2], int n, int sig, int dec);
void MDisplay21(double A[N2][N], int row, int col, int sig, int dec);
void MDisplayI(int A[N][N], int row, int col);
void MDisplayI2(int A[N2][N2], int row, int col);
void MDisplayI21(int A[N2][N], int row, int col);
void MMDisplay(double A[N][N], double B[N][N], int n, int sig, int dec);
void MMDisplay2(double A[N2][N2], double B[N2][N2], int n, int sig, int dec);
void MVDisplay(double V[N], int n, int sig, int dec);
void MVDisplay2(double V[N2], int n, int sig, int dec);
void MCopy(double in[N][N], double out[N][N], int row, int col);
void MCopy2(double in[N2][N2], double out[N2][N2], int row, int col);
void VClean(double A[N], int row);
void VCleanI(int A[N], int row);
void VClean2(double A[N2], int row);
void M3Clean(double A[N][N][N], int mat, int row, int col);
void MClean(double A[N][N], int row, int col);
void MClean2(double A[N2][N2], int row, int col);
void MClean21(double A[N2][N], int row, int col);
void MCleanI(int A[N][N], int row, int col);
void MCleanI2(int A[N2][N2], int row, int col);
void MCleanI21(int A[N2][N], int row, int col);
void MCompose(int p, int num[N], int dim[N], double set[N][N][N], double *ptr[N]);
void VPush(double A[N], int n);
void MPush21(double A[N2][N], int row, int n);
void MAbs(double A[N2][N2], int n);
void MIdentity(double A[N][N], int n);
void MIdentity2(double A[N2][N2], int n);
void MMultiplication(double A[N][N], double B[N][N], double out[N2][N2], int n);
void MMultiplication2(double A[N2][N2], double B[N2][N2], double out[N2][N2], int n);
void MVTransform(double A[N2][N2], double V[N2], double out[N2], int n);
void MPivot(double A[N2][N2], double B[N2][N2], int j, int n, double *f);
void MScaling(double A[N2][N2], double B[N2][N2],int i, int n, double *f, int *c);
void MElimination(double A[N2][N2], double B[N2][N2],int x, int n);
void MInvert(double A[N2][N2], double IA[N2][N2],int n,int play);
double MGDet(double X[N2][N2], int n);

void M3Display(double A[N][N][N],int mat, int row, int col){ // Display 3D matrix
	int i,j,k;
	for (i = 0; i < mat; i ++){
		for(j = 0; j < row; j ++){
			for(k = 0; k < col; k ++){
				printf("%10.5lf  ",A[i][j][k]);
			}
			printf("\n");
		}
		printf("-------------------------\n");
	}
}

void MDisplay(double A[N][N], int n){ // Display 1 matrix
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%5.4lf ",A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MDisplay2(double A[N2][N2], int n, int sig, int dec){ // Display 1 matrix with N2*N2 dimensions
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%*.*lf ",sig,dec,A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MDisplay21(double A[N2][N], int row, int col, int sig, int dec){ // Display 1 matrix with N2*N dimensions
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%*.*lf ",sig,dec,A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MDisplayI(int A[N][N], int row, int col){ // Display 1 matrix - Integer form
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MDisplayI2(int A[N2][N2], int row, int col){ // Display 1 matrix - Integer form - N2*N2
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MDisplayI21(int A[N2][N], int row, int col){ // Display 1 matrix - Integer form - N2*N
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MMDisplay(double A[N][N], double B[N][N], int n, int sig, int dec){ // Display 2 matrices
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%*.*lf ",sig,dec,A[i][j]);
		}
		printf(" | ");
		for (j = 0; j < n; j++){
			printf("%*.*lf ",sig,dec,B[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MMDisplay2(double A[N2][N2], double B[N2][N2], int n, int sig, int dec){ // Display 2 matrices - N2*N2
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%*.*lf ",sig,dec,A[i][j]);
		}
		printf(" | ");
		for (j = 0; j < n; j++){
			printf("%*.*lf ",sig,dec,B[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n");	
}

void MVDisplay(double V[N], int n, int sig, int dec){
	int i;
	for(i = 0; i < n; i++){
		printf("|%*.*lf|\n",sig,dec,V[i]);
	}
	printf("--------\n");
}
void MVDisplay2(double V[N2], int n, int sig, int dec){
	int i;
	for(i = 0; i < n; i++){
		printf("|%*.*lf|\n",sig,dec,V[i]);
	}
	printf("--------\n");
}

void MCopy(double in[N][N], double out[N][N], int row, int col){ // Copy a matrix to another
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			out[i][j] = in[i][j];
		}
	}
}
void MCopy2(double in[N2][N2], double out[N2][N2], int row, int col){ // Copy a matrix to another
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			out[i][j] = in[i][j];
		}
	}
}

void VClean(double A[N], int row){
	int i;
	for (i = 0; i < row; i++){
		A[i] = 0;
	}
}
void VCleanI(int A[N], int row){
	int i;
	for (i = 0; i < row; i++){
		A[i] = 0;
	}
}

void VClean2(double A[N2], int row){
	int i;
	for (i = 0; i < row; i++){
		A[i] = 0;
	}
}

void M3Clean(double A[N][N][N], int mat, int row, int col){
	int i,j,k;
	for (i = 0; i < mat; i++){
		for (j = 0; j < row; j++){
			for (k = 0; k < col; k++){
				A[i][j][k] = 0;
			}
		}
	}
}

void MClean(double A[N][N], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}
void MClean2(double A[N2][N2], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}
void MClean21(double A[N2][N], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}
void MCleanI(int A[N][N], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}
void MCleanI2(int A[N2][N2], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}
void MCleanI21(int A[N2][N], int row, int col){
	int i,j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			A[i][j] = 0;
		}
	}
}

void VPush(double A[N], int n){
	int i;
	for(i = n - 1; i > 0; i--){
		A[i] = A[i-1];
	}
}

void MPush21(double A[N2][N], int row, int n){
	int i,j;
	for(i = 0; i <= row; i ++){
		for(j = n - 1; j > 0; j--){
			A[i][j] = A[i][j-1];
		}	
	}
}

void MAbs(double A[N2][N2], int n){ // Remove all negative signs
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			A[i][j] = fabs(A[i][j]);
		}
	}
}

void MIdentity(double A[N][N], int n){ // Identity matrix maker
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if(i == j){
				A[i][j] = 1;
			} else {
				A[i][j] = 0;
			}
		}
	}
}

void MIdentity2(double A[N2][N2], int n){ // Identity matrix maker
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if(i == j){
				A[i][j] = 1;
			} else {
				A[i][j] = 0;
			}
		}
	}
}

void MMultiplication(double A[N][N], double B[N][N], double out[N2][N2], int n){
	int i,j,k;
	for (i=0;i<n;i++){
		for(j=0;j<n;j++){
			out[i][j] = 0;
			for(k=0;k<n;k++){
				out[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	printf("Multiplication complete.\n");
	MDisplay2(out,n,6,6);
}

void MMultiplication2(double A[N2][N2], double B[N2][N2], double out[N2][N2], int n){
	int i,j,k;
	for (i=0;i<n;i++){
		for(j=0;j<n;j++){
			out[i][j] = 0;
			for(k=0;k<n;k++){
				out[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	printf("Multiplication complete.\n");
	MDisplay2(out,n,6,6);
}

void MVTransform(double A[N2][N2], double V[N2], double out[N2], int n){
	int i,j;
//	MVDisplay(V0,n,6,6);	
	for (i = 0; i < n; i ++){
		out[i] = 0;
		for(j = 0; j < n; j++){
			out[i] += A[i][j]*V[j];
		}
	}
}

void MPivot(double A[N2][N2], double B[N2][N2], int j, int n, double *f){ // Matrix-Matrix Pivoting
	int i;
	int max = j;
	double temp, tempB;
	for(i=j;i<n;i++){
		if (fabs(A[i][j]) > fabs(A[max][j])){
			max = i;
		}
	}
	if(max != j){
		for(i=0;i<n;i++){
			temp = A[j][i];
			A[j][i] = A[max][i];
			A[max][i] = temp;	
			
			tempB = B[j][i];
			B[j][i] = B[max][i];
			B[max][i] = tempB;			
		}
		*f *= -1.0;
	}
	
}

void MScaling(double A[N2][N2], double B[N2][N2],int i, int n, double *f, int *c){ // Scaling components row-wise
	int j;
	double scale = A[i][i];
	if (fabs(A[i][i]) > 0.0000000001){
		for(j = 0; j < n; j ++){
			A[i][j] /= scale;
			B[i][j] /= scale;
		}
	} else {
		*c = 0;
		printf("Division by zero found. Scaling failed.\n");
	}
	*f *= scale;
}

void MElimination(double A[N2][N2], double B[N2][N2],int x, int n){ // Zeroing components column-wise
	int i,j;
	double scale;
	for(i = 0; i < n; i ++){ 
		if(i != x){
			scale = A[i][x];
			for(j = 0; j < n; j++){
				A[i][j] -= A[x][j]*scale;
				B[i][j] -= B[x][j]*scale;
			}
		}
	}
}

void MInvert(double A[N2][N2], double IA[N2][N2],int n,int play){
	// Gauss-Jordan method for finding an inverse of a matrix
	int j;
	int sig = 6, dec = 6;
	double factor = 1;
	int unicheck = 1; // Check unitary matrix
	MIdentity2(IA,n);
	if(play != 0){
		printf("Initial matrices: \n");
		MMDisplay2(A,IA,n,sig,dec);
	}
	for(j = 0; j < n; j ++){ // j = Column index
		MPivot(A,IA,j,n,&factor);
		if(play != 0){
			printf("Pivoting completed.\n");
			MMDisplay2(A,IA,n,sig,dec);
		}
		
		MScaling(A,IA,j,n,&factor,&unicheck);
		if(unicheck == 0){
			break;
		}
		
		if(play != 0){
			printf("Scaling completed.\n");
			MMDisplay2(A,IA,n,sig,dec);
		}
		
		MElimination(A,IA,j,n);
		
		if(play != 0){
			printf("Elimination completed.\n");
			MMDisplay2(A,IA,n,sig,dec);
		}
		
	}
	if (unicheck == 1){
		if(play != 0){
			printf("Final result.\n");
			printf("Former matrix determinant : %lf\n",factor);
			printf("Inverse matrix determinant : %lf\n",1.0/factor);
			MAbs(A,n);
			MMDisplay2(A,IA,n,sig,dec);
		}
	} else {
		printf("This matrix is unitary, there is no inverse.\n");
	}
	
}

double MGDet(double X[N2][N2], int n){ // Determinant by the much faster Gaussian Elimination
	int j;
	double factor = 1;
	double A[N2][N2],IA[N2][N2];
	int unicheck = 1; // Check unitary matrix
	MCopy2(X,A,n,n);
	MIdentity2(IA,n);
	printf("Initial matrices: \n");
	MMDisplay2(A,IA,n,6,6);
	for(j = 0; j < n; j ++){ // j = Column index
		MPivot(A,IA,j,n,&factor);
		MScaling(A,IA,j,n,&factor,&unicheck);
		MElimination(A,IA,j,n);
		if(unicheck == 0){
			break;
		}
	}
	if (unicheck == 1){
		return factor;
	} else {
		return 0;
	}
}

void Minor(double A[N2][N2], double M[N2][N2], int n, int j){
	int im,jm;
	for (jm=0;jm<n;jm++){
		for (im=0;im<n;im++){
			if (jm<j){
				M[im][jm] = A[im+1][jm];
			} else if (jm>j){
				M[im][jm-1] = A[im+1][jm];
			}
		}
	}
//	MDisplay(M,n-1);
}

double MDet(double A[N2][N2], int n){ // Determine the matrix's determinant
	int j;
	double Det = 0;
	double M[N2][N2];
	for (j=0;j<n;j++){
		if(n>1){
			Minor(A,M,n,j);
			Det += pow(-1.0,j)*A[0][j]*MDet(M,n-1);
//			printf("det = %lf\n",Det);
		} else {
			Det = A[0][0];
//			printf("det is now %lf\n",A[0][0]);
		}
	}
	return Det;
}
#endif
