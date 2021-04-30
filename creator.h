#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define N 10
#define N2 100
#define N10 10

#ifndef CREATOR_H
#define CREATOR_H

// Functions declared beforehand
int CSeries(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]); // Main series maker
int CParallel(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]); // Main parallel maker
int CCustom(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]);
int CSample(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]);
int CTemp(void);
void CRead(char Ctype[N2], double tset[N], int nset[N], int inum[N], int pset[N2][N], double set[N][N][N], char path[N2]);
void CWrite(char Ctype[N2], double tset[N], int nset[N], int inum[N], int pset[N2][N], double set[N][N][N]); // Write setting file
void CR(int inum[N], int id[N2], double set[N][N][N]); // Add Resistor
void CL(int inum[N], int id[N2], double set[N][N][N]); // Add Inductor
void CC(int inum[N], int id[N2], double set[N][N][N]); // Add Capacitor
void CV(int inum[N], int id[N2], double set[N][N][N]); // Add Voltage Source
void CU(int inum[N], int id[N2]); // Remove the last object
void CP(int inum[N], double set[N][N][N], int sig, int dec); // Print all added objects
void CTime(double tset[N]); // Add Time

int CCustom(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]){
	char path[N2] = "punchcards\\input.txt";
	char Ctype[N2];
	int inum[N] = {0,0,0,0,0};
	CRead(Ctype,tset,nset,inum,pset,set,path);
	CWrite(Ctype,tset,nset,inum,pset,set);
	return 1;
}

void CRead(char Ctype[N2], double tset[N], int nset[N], int inum[N], int pset[N2][N], double set[N][N][N], char path[N2]){
	FILE *fp;
	char A[N2];
	int i = 0,j = 1;
//	printf("%s",path);
	fp = fopen(path,"r");

	double ti,tf,dt;
	int nP = 0, nV = 0;
	int n1,n2,n3,n4;
	int num;
	double R,L,C,q,V,w,phi;
	
	while(fgets(A,N2,fp) != NULL){
		switch(i) {
		case 1: // Circuit types
			fscanf(fp,"%s",Ctype);
			break;
		case 3: // time
			fscanf(fp,"%lf %lf %lf",&ti,&tf,&dt);
			break;
		case 5: // total object
			fscanf(fp,"%d %d",&nP,&nV);
			break;
		case 8: // get pset
			while(j <= nP){
//				fscanf(fp,"%d %d %d %d",&n1,&n2,&n3,&n4);
//				pset[j][0] = n1;
//				pset[j][1] = n2;
//				pset[j][2] = n3;
//				pset[j][3] = n4;
				fscanf(fp,"%d %d %d",&n1,&n3,&n4);
				pset[j][0] = n1;
				pset[j][1] = inum[n1];
				inum[n1] ++;
				pset[j][2] = n3;
				pset[j][3] = n4;
				i++;
				j++;
			}
			i--;
			break;
		}
		if(i == 10+nP){ // get set
			j = 1;
			while(j<=nP){
				num = pset[j][1];
				switch(pset[j][0]){
					case 0:
						fscanf(fp,"%lf",&R);
						set[0][num][0] = R;
						break;
					case 1:
						fscanf(fp,"%lf",&L);
						set[1][num][0] = L;
						break;
					case 2:
						fscanf(fp,"%lf %lf",&C,&q);
						set[2][num][0] = C;
						set[2][num][1] = q;
						break;
					case 3:
						fscanf(fp,"%lf %lf %lf",&V,&w,&phi);
						set[3][num][0] = V;
						set[3][num][1] = w;
						set[3][num][2] = phi;
						break;
				}
				i ++;
				j ++;
			}
		}
		i ++;
	}
	tset[0] = ti;
	tset[1] = tf;
	tset[2] = dt;
	nset[0] = nP;
	nset[1] = nV;
	nset[2] = nP; // nI
	nset[3] = nP+nV-1; // nT
//	MDisplayI21(pset,nP+1,4);
//	M3Display(set,4,3,4);
//	printf("%s",A);
//	printf("ti = %lf tf = %lf dt = %lf\n",ti,tf,dt);
//	printf("nP = %d nV = %d\n",nP,nV);
//	printf("read inum = %d %d %d %d",inum[0],inum[1],inum[2],inum[3]);
	inum[4] = nP;
}

void CWrite(char Ctype[N2] ,double tset[N], int nset[N], int inum[N], int pset[N2][N], double set[N][N][N]){
	int i;
	FILE *fp;
	fp = fopen("dataset\\setting.txt","w+");
	fprintf(fp,"Circuit type: %s\n",Ctype);
	double logdt = log10(tset[2]);
	int expo = floor(logdt);
	double a = pow(10,logdt-expo);
	fprintf(fp,"Initial time = %lf\n",tset[0]);
	fprintf(fp,"Final time = %lf\n",tset[1]);
	fprintf(fp,"Time increment = %.2lf*10^%d\n",a,expo);
	fprintf(fp,"Total objects = %d, Total nodes = %d\n",nset[0],nset[1]);
	if(inum[3] > 0){
		fprintf(fp,"-----------Voltage Source-----------\n");
	}
	for(i = 0; i < inum[3]; i ++){
		fprintf(fp,"V%d = %10.6lf  VOLT  Omega = %10.6lf  RAD/S  Phase Angle = %10.6lf RAD\n",i+1,set[3][i][0],set[3][i][1],set[3][i][2]);
	}
	if(inum[0] > 0){
		fprintf(fp,"--------------Resistor--------------\n");
	}
	for(i = 0; i < inum[0]; i ++){
		fprintf(fp,"R%d = %10.6lf  OHM\n",i+1,set[0][i][0]);
	}
	if(inum[1] > 0){
		fprintf(fp,"--------------Inductor--------------\n");
	}
	for(i = 0; i < inum[1]; i ++){
		fprintf(fp,"L%d = %10.6lf  HENRY\n",i+1,set[1][i][0]);
	}
	if(inum[2] > 0){
		fprintf(fp,"--------------Capacitor--------------\n");
	}
	for(i = 0; i < inum[2]; i ++){
		fprintf(fp,"C%d = %10.6lf  FARAD  Charges = %10.6lf  COULOMB\n",i+1,set[2][i][0],set[2][i][1],set[2][i][2]);
	}
	fprintf(fp,"---------Object Connection--------\n");
	fprintf(fp,"Type       Number     Pos.Node     Neg.Node\n");
	char type[N][N2] = {"Dogs       ","Resistor       ","Inductor      ","Capacitor     ","Source         "};
	for(i = 1; i <= nset[0]; i ++){
		fputs(type[pset[i][0]+1],fp);
		fprintf(fp,"%d                %d                 %d\n",pset[i][1],pset[i][2],pset[i][3]);
	}
	fprintf(fp,"-------Obtained data columns-------\n");
	fprintf(fp,"Kirchhoff column vector : time    total-energy    dissipated-energy    ");
	for(i = 1; i <= nset[0]; i ++){
		if(pset[i][0] == 1){ // Check L
			fprintf(fp,"dI%d/dt    ",i);
		} else {
			fprintf(fp,"I%d    ",i);
		}
	}
	for(i = 1; i <= nset[1] - 1; i ++){
		fprintf(fp,"V%d    ",i);
	}
	fprintf(fp,"\nRData : time    ");
	for(i = 0; i < inum[0]; i ++){
		fprintf(fp,"I%d    P%d    E%d   ",i,i,i);
	}
	fprintf(fp,"\nLData : time    ");
	for(i = 0; i < inum[1]; i ++){
		fprintf(fp,"I%d    dI%d/dt    UL%d    ",i,i,i);
	}
	fprintf(fp,"\nCData : time    ");
	for(i = 0; i < inum[2]; i ++){
		fprintf(fp,"I%d    q%d    U%d   ",i,i,i);
	}
	fprintf(fp,"\nVData : time    ");
	for(i = 0; i < inum[3]; i ++){
		fprintf(fp,"I%d    V%d   ",i,i);
	}
	fprintf(fp,"\nNodeData : time    V(ground)   ");
	for(i = 1; i < nset[1]; i ++){
		fprintf(fp,"V%d    ",i);
	}
	fprintf(fp,"\n");
	fclose(fp);
}

int CSeries(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]){
	
	int inum[N] = {0,0,0,0,0}; // iR iL iC iV iT
	int id[N2] = {-1};
	printf("You are about to simulate a series circuit.\n");
	CHelp2();
	
	int status = 0;

	char in;
	while(1){
//		M3Display(set,3,3,5);
//		printf("%d %d %d %d\n",id[0],id[1],id[2],id[3]);
//		printf("%d %d %d %d %d\n",inum[0],inum[1],inum[2],inum[3],inum[4]);
		printf("Enter a letter as a command ");
		scanf("%s",&in);
		if(in == 'R'){
			CR(inum,id,set);
		} else if(in == 'L'){
			CL(inum,id,set);
		} else if(in == 'C'){
			CC(inum,id,set);
		} else if(in == 'V'){
			CV(inum,id,set);
		} else if(in == 'U'){
			CU(inum,id);
		} else if(in == 'S'){
			printf("Returning to the main menu...\n");
			return 0;
		} else if(in == 'P'){
			CP(inum,set,8,6);
		} else if(in == 'F'){
			printf("Finished building circuit...\n");
			break;
		} else {
			printf("Invalid command.\n");
		}
	}
	
	int nP = inum[4], nV = nP, nI = nP, nT = nI+nV-1;
	nset[0] = nP;
	nset[1] = nV;
	nset[2] = nI;
	nset[3] = nT;
	int iR = inum[0], iL = inum[1], iC = inum[2], iV = inum[3];
	
	int i;
	for(i = 0; i < iR; i ++){
		pset[i+1][0] = 0;
		pset[i+1][1] = i;
	}
	for(i = 0; i < iL; i ++){
		pset[i+1+iR][0] = 1;
		pset[i+1+iR][1] = i;
	}
	for(i = 0; i < iC; i ++){
		pset[i+1+iR+iL][0] = 2;
		pset[i+1+iR+iL][1] = i;
	}
	for(i = 0; i < iV; i ++){
		pset[i+1+iR+iL+iC][0] = 3;
		pset[i+1+iR+iL+iC][1] = i;
	}
	for(i = 1; i <= nP; i ++){
		if(i == nP){
			pset[i][2] = 0;
		} else {
			pset[i][2] = i;	
		}
		pset[i][3] = i-1;
	}
	
	char Ctype[N2] = "Series";
	CTime(tset);
	CWrite(Ctype,tset,nset,inum,pset,set);
	return 1;
}

int CParallel(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]){
	int inum[N] = {0,0,0,0,0}; // iR iL iC iV iT
	int id[N2] = {-1};
	printf("You are about to simulate a parallel circuit.\n");
	CHelp2();
	
	int status = 0;

	char in;
	while(1){
		printf("Enter a letter as a command ");
		scanf("%s",&in);
		if(in == 'R'){
			CR(inum,id,set);
		} else if(in == 'L'){
			CL(inum,id,set);
		} else if(in == 'C'){
			CC(inum,id,set);
		} else if(in == 'V'){
			CV(inum,id,set);
		} else if(in == 'U'){
			CU(inum,id);
		} else if(in == 'S'){
			printf("Returning to the main menu...\n");
			return 0;
		} else if(in == 'P'){
			CP(inum,set,8,6);
		} else if(in == 'F'){
			printf("Finished building circuit...\n");
			break;
		} else {
			printf("Invalid command.\n");
		}
	}
	
	int nP = inum[4], nV = 2, nI = nP, nT = nI+nV-1;
	nset[0] = nP;
	nset[1] = nV;
	nset[2] = nI;
	nset[3] = nT;
	int iR = inum[0], iL = inum[1], iC = inum[2], iV = inum[3];
	
	int i;
	for(i = 0; i < iR; i ++){
		pset[i+1][0] = 0;
		pset[i+1][1] = i;
	}
	for(i = 0; i < iL; i ++){
		pset[i+1+iR][0] = 1;
		pset[i+1+iR][1] = i;
	}
	for(i = 0; i < iC; i ++){
		pset[i+1+iR+iL][0] = 2;
		pset[i+1+iR+iL][1] = i;
	}
	for(i = 0; i < iV; i ++){
		pset[i+1+iR+iL+iC][0] = 3;
		pset[i+1+iR+iL+iC][1] = i;
	}
	for(i = 1; i <= nP; i ++){
		pset[i][2] = 1;
		pset[i][3] = 0;
	}

	char Ctype[N2] = "Parallel";
	CTime(tset);
	CWrite(Ctype,tset,nset,inum,pset,set);
	return 1;
}

int CSample(double tset[N], int nset[N], int pset[N2][N], double set[N][N][N]){
	CHelpS();
	char i;
	char path[N2] = "";
	char Ctype[N2];
	int p = 0;
	while(p == 0){
		printf("Enter a command ");
		scanf("%s",&i);
		switch (i){
			case '1':
				p = CSample1(path);
				break;
			case '2':
				p = CSample2(path);
				break;
			case '3':
				p = CSample3(path);
				break;
			case '4':
				p = CSample4(path);
				break;
			case '9':
				return 0;
			default:
				printf("Invalid command\n");
				break;
		}
	}
	int inum[N] = {0,0,0,0,0};
	CRead(Ctype,tset,nset,inum,pset,set,path);
	CWrite(Ctype,tset,nset,inum,pset,set); // must edit SP
	return 1;
}

void CR(int inum[N], int id[N2], double set[N][N][N]){
	double R;
	int num = inum[0], tnum = inum[4];
	printf("Resistor - Enter resistance (OHM): ");
	scanf("%lf",&R);
	set[0][num][0] = R;
	inum[0] = num + 1;
	id[tnum] = 0;
	inum[4] = inum[4] + 1;
	printf("Resistor successfully added.\n");
}
void CL(int inum[N], int id[N2], double set[N][N][N]){
	double L;
	printf("Inductor - Enter Inductance (HENRY): ");
	scanf("%lf",&L);
	set[1][inum[1]][0] = L;
	inum[1]++;
	id[inum[4]] = 1;
	inum[4]++;
	printf("Inductor successfully added.\n");
}
void CC(int inum[N], int id[N2], double set[N][N][N]){
	double C,q;
	printf("Capacitor - Enter Capacitance (FARAD): ");
	scanf("%lf",&C);
	printf("Enter initial stored Charges (COULOMB): ");
	scanf("%lf",&q);
	set[2][inum[2]][0] = C;
	set[2][inum[2]][1] = q;
	inum[2]++;
	id[inum[4]] = 2;
	inum[4]++;
	printf("Capacitor successfully added.\n");
}
void CV(int inum[N], int id[N2], double set[N][N][N]){
	double V0,w,phi;
	printf("Voltage Source - Enter Maximum Voltage (VOLT): ");
	scanf("%lf",&V0);
	printf("Enter Angular Frequency (0 if Direct Current) (RADIAN/SECOND): ");
	scanf("%lf",&w);
	printf("Enter initial Phase Angle (0 if at maximum) (RADIAN) : ");
	scanf("%lf",&phi);
	set[3][inum[3]][0] = V0;
	set[3][inum[3]][1] = w;
	set[3][inum[3]][2] = phi;
	inum[3]++;
	id[inum[4]] = 3;
	inum[4]++;
	printf("Voltage Source successfully added.\n");
}
void CU(int inum[N], int id[N2]){
	if(inum[4] > 0){
		printf("The last object is removed.\n");
		inum[id[inum[4]-1]] --;
		inum[4] --;
	} else {
		printf("No objects have been added.\n");
	}
}
void CP(int inum[N], double set[N][N][N], int sig, int dec){
	int i;
	for(i = 0; i < inum[3]; i ++){
		printf("Source: %*.*lf VOLT  Angular Speed: %*.*lf RAD/S  Initial Phase Angle: %*.*lf RAD\n",sig,dec,set[3][i][0],sig,dec,set[3][i][1],sig,dec,set[3][i][2]);
	} for(i = 0; i < inum[0]; i ++){
		printf("Resistor: %*.*lf  OHM\n",sig,dec,set[0][i][0]);
	} for(i = 0; i < inum[1]; i ++){
		printf("Inductor: %*.*lf  HENRY\n",sig,dec,set[1][i][0]);
	} for(i = 0; i < inum[2]; i ++){
		printf("Capacitor: %*.*lf  FARAD   Charges: %*.*lf  COULOMB\n",sig,dec,set[2][i][0],sig,dec,set[2][i][1]);
	}
}
void CTime(double tset[N]){
	double ti,tf,dt;
	printf("Enter Initial Time (SECOND): ");
	scanf("%lf",&ti);
	printf("Enter Final Time (SECOND): ");
	scanf("%lf",&tf);
	printf("Enter Time Interval (SECOND): ");
	scanf("%lf",&dt);
	tset[0] = ti;
	tset[1] = tf;
	tset[2] = dt;
}


int CTemp(void){ // create template
	FILE *fp;
	fp = fopen("punchcards\\input.txt","w+");
	fprintf(fp,"DO NOT MAKE CHANGE TO ANY TEXT EXCEPT ON ALLOWED FIELDS ELSE THE PROGRAM MIGHT FAIL\n");
	fprintf(fp,"------------- circuit type\n");
	fprintf(fp,"***Insert***\n");
	fprintf(fp,"------------- time set (ti, tf, dt) (seconds)\n");
	fprintf(fp,"***Insert***\n");
	fprintf(fp,"------------- Total Objects, Total Nodes MAKE SURE TO CORRECT IT\n");
	fprintf(fp,"***Insert***\n");
	fprintf(fp,"------------- Object set (type,+ side,- side) type => 0 = R   1 = L    2 = C   3 = VSource\n");
	fprintf(fp,"||  Object of the same type must have a different number\n");
	fprintf(fp,"***Insert***\n");
	fprintf(fp,"------------- Object data (data1, data2, etc as necessary)\n");
	fprintf(fp,"|| Must be in the same order as above\n");
	fprintf(fp,"***Insert***\n");
	fprintf(fp,"------------- Circuit description\n");
	fclose(fp);
	return 0;
};
#endif
