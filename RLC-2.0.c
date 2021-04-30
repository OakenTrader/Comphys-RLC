#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Scripts.h"
#include "matrix.h"
#include "functions.h"
#include "Kirrchover.h"
#include "creator.h"
#define N 10
#define N2 100
#define NI 3

void run2(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]);
void welcome(void);

void welcome(void){
	
	int status = 0;
	
	int nset[N] = {0,0,0,0}; // nP nV nI nT
	double tset[N] = {}; // ti tf dt
	
	int pset[N2][N] = {};
	double set[N][N][N] = {};
	
	char input;
	printf("Welcome to RLC 2.0, the world-class RLC simulator\n");
	CHelp();
	
	while(status == 0){
		VCleanI(nset,N);
		VClean(tset,N);
		MCleanI21(pset,N2-80,N);
		M3Clean(set,N,N,N);
		printf("Enter a command (8 for help): ");
		scanf("%s",&input);
		if(input == '1'){
			status = CSeries(tset,nset,pset,set);	
		} else if(input == '2'){
			status = CParallel(tset,nset,pset,set);
		} else if(input == '3'){
			status = CCustom(tset,nset,pset,set);
		} else if(input == '4'){
			status = CSample(tset,nset,pset,set);
		} else if(input == '5'){
			status = CTemp();
			printf("Template file created in punchcards\n");
		} else if(input == '8'){
			CHelp();
		} else if(input == '9'){
			printf("Thank you for using our service.\n");
			printf("Press any key to exit.\n");
			getch();
			exit(0);
		} else {
			printf("Invalid command.\n");
		}
		
	}
	run2(tset,nset,pset,set);
	
	printf("Calculation completed, data is in dataset folder.\n");
	printf("Thank you for using our service.\n");
	printf("Press any key to exit.\n");
	getch();
	exit(0);
}

void run2(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]){
	
	FILE *fp, *fR, *fL, *fC, *fV, *fN;
	fp = fopen("dataset\\KirrData.txt","w+");
	fR = fopen("dataset\\RData.txt","w+");
	fL = fopen("dataset\\LData.txt","w+");
	fC = fopen("dataset\\CData.txt","w+");
	fV = fopen("dataset\\VData.txt","w+");
	fN = fopen("dataset\\NodeData.txt","w+");
	
	printf("Initializing...\n");
	
	double ti = tset[0];
	double tf = tset[1];
	double dt = tset[2];
	double t = ti;
	int it = 0; // Iteration
	int nP = nset[0];
	int nV = nset[1];
	int nI = nset[2];
	int nT = nset[3];
	int h = (tf-ti)/dt;
	int c = setc(h);
	double step = 0;
	
	int Node[N2][N2] = {}; // Node i [N] = {Number of connected objects, connected objects, ...} 
	double VNode[N2] = {0}; // Vi  V[0] = 0 (Ground)
	MCleanI2(Node,N2,N2); // Assign zero to all the matrix to prevent bugs
	
	
	
	double I[N2][N] = {{},{},{},{}}; // Store the past 3 currents that pass through each object, I[0][N] is empty
	double dI[N2][N] = {}; // Store dI/dt for L
	double Kirr[N2] = {}; // Kirrchoff Vector on the left side	
	double MKirr[N2][N2] = {}; // The left side matrix
	double CKirr[N2] = {}; // The right side column vector
	double IMKirr[N2][N2]; // Inverted MKirr
	double bMKirr[N2][N2]; // Pre-inverted MKirr
	MCopy2(MKirr,bMKirr,nT,nT);
	
	KConnect(pset,Node,nV,nP);
	Kirchhoff(it,dt,t,I,pset,Node,nV,nP,MKirr,CKirr,set); // Initialization
	KInvert(MKirr,Kirr,IMKirr,nP,nV,nT); // Get IMKirr
	KTransform(Kirr,IMKirr,CKirr,nT); // Transform CKirr into Kirr
	KRetrieve(I,dI,Kirr,VNode,pset,nI,nT); // Store all variables
	KEnergy(dt,nset,pset,I,set);
	KIL(dt,pset,I,dI,nT);
	KQ(dt,pset,I,set,nT);

//	MDisplay21(dI,nP+1,8,6);
//	MDisplay21(I,nP+1,8,6);
//	M3Display(set,4,3,5);
//	MVDisplay(CKirr,nT,8,6);
//	MVDisplay(Kirr,nT,8,6);

	char e;
	int pe;
	printf("Display energy for individual objects? (y/n) ");
	scanf("%s",&e);
	switch(e){
		case 'y':
			pe = 1;
			break;
		case 'n':
			pe = 0;
			break;
		default:
			printf("Invalid command. No, i guess...\n");
			pe = 0;
			break;
	}

	KWriteK(fp,t,Kirr,nset,pset,set,nT,8,6);
	KWrite(fR,fL,fC,fV,fN,t,dt,nset,pset,I,dI,VNode,set,8,6,pe);
	KAdvance(&it,&t,dt,I,dI,nP);
	
	while(t<tf){
		KColumn(it,dt,t,I,pset,Node,nV,nP,CKirr,set);
		KTransform(Kirr,IMKirr,CKirr,nT);
		KRetrieve(I,dI,Kirr,VNode,pset,nI,nT);
		KEnergy(dt,nset,pset,I,set);
		KIL(dt,pset,I,dI,nT);
		KQ(dt,pset,I,set,nT);
		if(it % c < 1){
			KWriteK(fp,t,Kirr,nset,pset,set,nT,8,6);
			KWrite(fR,fL,fC,fV,fN,t,dt,nset,pset,I,dI,VNode,set,8,6,pe);
		}
		KAdvance(&it,&t,dt,I,dI,nP);
		if(t - step > 0){
			printf("Progression: %2.0lf%\n",t/tf*100);
			printf("t: %lf%\n",t);
			step += 0.1*(tf-ti);
			printf("Current input vector:\n");
			MVDisplay(CKirr,nT,8,6);
			printf("Current output vector:\n");
			MVDisplay(Kirr,nT,8,6);
			printf("Current current:\n");
			MDisplay21(I,nP+1,1,8,6);
		}
	}
//	MDisplay21(I,nP+1,8,6);
//	MDisplay21(dI,nP+1,8,6);
//	MVDisplay(CKirr,nT+1,8,6);
//	MVDisplay(Kirr,nT+1,8,6);
	fclose(fp);
	fclose(fR);
	fclose(fL);
	fclose(fC);
	fclose(fV);
	fclose(fN);
}

void main(void){
	welcome();
}


