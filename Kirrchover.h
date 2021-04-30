#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "functions.h"
#define N 10
#define N2 100
#define NI 3

#ifndef KIRRCHOVER_H
#define KIRRCHOVER_H

void KConnect(int pset[N2][N], int Node[N2][N2], int nV, int nP);
void Kirchhoff(int it, double dt, double t, double I[N2][N], int pset[N2][N], int Node[N2][N2], int nV, int nP, double MKirr[N2][N2], double CKirr[N2], double set[N][N][N]);
void KInvert(double MKirr[N2][N2], double Kirr[N2], double IMKirr[N2][N2], int nP, int nV, int nT);
void KTransform(double Kirr[N2], double IMKirr[N2][N2], double CKirr[N2], int nT);
void KRetrieve(double I[N2][N], double dI[N2][N], double Kirr[N2], double VNode[N2], int pset[N2][N], int nI, int nT);
void KIL(double dt, int pset[N2][N], double I[N2][N], double dI[N2][N], int nT);
void KQ(double dt, int pset[N2][N], double I[N2][N], double set[N][N][N], int nT);
void KAdvance(int *it, double *t, double dt, double I[N2][N], double dI[N2][N], int nP);
void KColumn(int it, double dt, double t, double I[N2][N], int pset[N2][N], int Node[N2][N2], int nV, int nP, double CKirr[N2], double set[N][N][N]);
void KWriteK(FILE *fp, double t, double Kirr[N2], int nset[N], int pset[N2][N], double set[N][N][N], int nT, int sig, int dec);
void KWrite(FILE *fR, FILE *fL, FILE *fC, FILE *fV, FILE *fN, double t, double dt, int nset[N], int pset[N2][N], double I[N2][N], double dI[N2][N], double VNode[N2], double set[N][N][N], int sig, int dec, int pe);

void KEnergy(double dt, int nset[N], int pset[N2][N], double I[N2][N], double set[N][N][N]){
	int i;
	int ptype, pnum;
	for(i = 1; i <= nset[0]; i ++){
		ptype = pset[i][0];
		pnum = pset[i][1];
		switch(ptype){
			case 0:
				set[0][pnum][1] = RPower(I[i][0],set[0][pnum][0]);
				set[0][pnum][2] = RPower(I[i][1],set[0][pnum][0]);
				set[0][pnum][3] += REnergy(dt,set[0][pnum][2],set[0][pnum][1]);
				break;
			case 1:
				set[1][pnum][1] = LEnergy(set[1][pnum][0],I[i][0]);
				break;
			case 2:
				set[2][pnum][2] = CEnergy(set[2][pnum][0],set[2][pnum][1]);
				break;
			case 3:
				break;
			default:
				printf("bruh Energy\n");
				break;
		}
	}
}

void KWriteK(FILE *fp, double t, double Kirr[N2], int nset[N], int pset[N2][N], double set[N][N][N], int nT, int sig, int dec){ // Record the Kirchoff column vector
	int i;
	double TE,DE;
	TE = TEnergy(nset,pset,set);
	DE = DEnergy(nset,pset,set);
	fprintf(fp,"%*.*lf  |  %*.*lf  |   %*.*lf  |  ",sig,dec,t,sig,dec,TE,sig,dec,DE); //t TE DE
	for(i = 0; i < nT; i ++){
		fprintf(fp,"%*.*lf   ",sig,dec,Kirr[i]);
	}
	fprintf(fp,"\n");
}

void KWrite(FILE *fR, FILE *fL, FILE *fC, FILE *fV, FILE *fN, double t, double dt, int nset[N], int pset[N2][N], double I[N2][N], double dI[N2][N], double VNode[N2], double set[N][N][N], int sig, int dec, int pe){ // Record the objects and nodes properties
	int i;
	int nP = nset[0], nV = nset[1];
	int ptype, pnum;
	fprintf(fR,"%*.*lf    ",sig,dec,t);
	fprintf(fL,"%*.*lf    ",sig,dec,t);
	fprintf(fC,"%*.*lf    ",sig,dec,t);
	fprintf(fV,"%*.*lf    ",sig,dec,t);
	fprintf(fN,"%*.*lf    ",sig,dec,t);
	for (i = 1; i <= nP; i++){
		ptype = pset[i][0];
		pnum = pset[i][1];
		switch(ptype){
			case 0:
				fprintf(fR,"|  %*.*lf   ",sig,dec,I[i][0]);
				if(pe == 1){
					fprintf(fR,"%*.*lf     %*.*lf   ",sig,dec,set[0][pnum][1],sig,dec,set[0][pnum][3]);
				}
				break;
			case 1:
				fprintf(fL,"| %*.*lf    %*.*lf    ",sig,dec,I[i][0],sig,dec,dI[i][0]);
				if(pe == 1){
					fprintf(fL,"%*.*lf   ",sig,dec,set[1][pnum][1]);
				}
				break;
			case 2:
				fprintf(fC,"|  %*.*lf    %*.*lf  ",sig,dec,I[i][0],sig,dec,set[2][pnum][1]);
				if(pe == 1){
					fprintf(fC,"%*.*lf    ",sig,dec,set[2][pnum][2]);
				}
				break;
			case 3:
				fprintf(fV,"|  %*.*lf    %*.*lf  ",sig,dec,I[i][0],sig,dec,FE(t,pnum,dt,I,set));
				break;
			default:
				printf("bruh Kwrite\n");
		}
	}
	for (i = 0; i < nV; i++){
		fprintf(fN,"%*.*lf    ",sig,dec,VNode[i]);
	}
	fprintf(fR,"\n");
	fprintf(fL,"\n");
	fprintf(fC,"\n");
	fprintf(fV,"\n");
	fprintf(fN,"\n");
}


void KConnect(int pset[N2][N], int Node[N2][N2], int nV, int nP){ // Assign relationships between objects and nodes to node matrix
	//Stuff connection infos into Node
	int i,j;
	int place;
	for(i = 0; i < nV; i ++){ // For each Node i
		for(j = 1; j <= nP; j ++){ // Inspecting each object of pset
			if (i == pset[j][2]){ // Found the object that connect to node i at POSITIVE side
				place = Node[i][0];
				Node[i][1+place] = j; // Obj number j is marked as connect to this node by the node
				Node[i][0] ++; // V  ,  Num  ,  *occupied*  ,  *occupied*  ,  *Vacant* <- This place = 2
			}
			if (i == pset[j][3]){ // Found the object that connect to node i at NEGATIVE side
				place = Node[i][0];
				Node[i][1+place] = -j; // V  ,  Num  ,  *occupied*  ,  *occupied*  ,  *Vacant* <- This place = 2
				Node[i][0] ++;
			}
		}	
	}
}

void Kirchhoff(int it, double dt, double t, double I[N2][N], int pset[N2][N], int Node[N2][N2], int nV, int nP, double MKirr[N2][N2], double CKirr[N2], double set[N][N][N]){
	//			 -	      +	-->    --> -       +  bruh shit visualization
	//KCL        |----R---|-----N-----|----R---|                               
	int nodeP, nodeN, Ptype, Pnum, iP; 
	int i,j,Idir;
	for(i = 1; i <= nV-1; i ++){ // Inspecting each Node from Node V1 to Node VN
		CKirr[i-1] = 0;
		for(j = 1; j <= Node[i][0]; j ++){ // Inspecting connected object in a node
			Pnum = Node[i][j];             // Take the object number, positive or negative
			Ptype = pset[abs(Pnum)][0];    // Identify the object type
			Idir = Pnum/abs(Pnum);         // Obtain +1 or -1 depending on current direction
			if(Ptype == 1){                // Check if the object is L
				CKirr[i-1] += -Idir*FIL(t,abs(Pnum),dt,I,set);  // put I on the right side instead because the vector now contain dI/dt instead of I
			} else {
				MKirr[i-1][abs(Pnum)-1] = Idir;
			}			
		}
	}
	//				             - + --> I
	//KVL             Node(-) ----R---- Node(+)
	for(i = 1; i <= nP; i ++){ // Inspecting each object from object 1 to object N
		Ptype = pset[i][0];
		Pnum = pset[i][1];  // Improved readability
		nodeP = pset[i][2]; // The node the obj's plus side is connected to
		nodeN = pset[i][3]; // The node the obj's minus side is connected to
		iP = i+nV-2; // New index to complement KCL, -1 for ground node
		
		if(nodeP > 0){ // Prevent ground node
			MKirr[iP][nP+nodeP-1] = 1; // assign V into the matrix
		}
		if(nodeN > 0){
			MKirr[iP][nP+nodeN-1] = -1;
		}
		
		if(Ptype == 0){ // R
			MKirr[iP][i-1] = KR(Pnum,dt,set);
		} else if(Ptype == 1){ // L
			MKirr[iP][i-1] = KL(Pnum,dt,set);
		} else if(Ptype == 2){ // C
			CKirr[iP] = FC(t,Pnum,dt,I,set);
			MKirr[iP][i-1] = KC(Pnum,dt,set);
		} else if(Ptype == 3){ // E
			CKirr[iP] = FE(t,Pnum,dt,I,set);
		}

	}
}

void KInvert(double MKirr[N2][N2], double Kirr[N2], double IMKirr[N2][N2], int nP, int nV, int nT){
	// Invert the Kirchoff matrix
	int sig = 8, dec = 6;
	MIdentity2(IMKirr,nT);
	MInvert(MKirr,IMKirr,nT,0);
//	MVDisplay2(Kirr,nT,sig,dec);
//	MDisplay2(MKirr,nT,sig,dec);
}

void KTransform(double Kirr[N2], double IMKirr[N2][N2], double CKirr[N2], int nT){
	int sig = 8, dec = 6, i;
//	printf("CKirr:\n");
//	MVDisplay(CKirr,nT,sig,dec);
	MVTransform(IMKirr,CKirr,Kirr,nT);
//	printf("Kirr:\n");
//	MVDisplay(Kirr,nT,sig,dec);
}

void KRetrieve(double I[N2][N], double dI[N2][N], double Kirr[N2], double VNode[N2], int pset[N2][N], int nI, int nT){
	// Retrieve values from Kirr and assign them to respective variables
	int i;
	int Ptype;
	for (i = 1; i <= nI; i ++){
		Ptype = pset[i][0];
		if(Ptype == 1){ // In case of L, the entry will be dI/dt instead of I
			dI[i][0] = Kirr[i-1];
		} else {
			I[i][0] = Kirr[i-1]; // Get Current i for Obj i
		}
	}
	for (i = nI + 1; i <= nT; i ++){
		VNode[i-nI] = Kirr[i-1]; // Get Voltage Vi for Node i
	}
}

void KIL(double dt, int pset[N2][N], double I[N2][N], double dI[N2][N], int nT){ // Make changes to stored IL
	int i;
	double dI0,dI1;
	for(i = 1; i <= nT; i ++){
		if (pset[i][0] == 1){
			dI0 = dI[i][1]; //Past dI
			dI1 = dI[i][0]; //Present dI
			I[i][0] += 0.5*(dI0+dI1)*dt; // Trapezoid gang
		} 
	}
}

void KQ(double dt, int pset[N2][N], double I[N2][N], double set[N][N][N], int nT){ // Make changes to stored Q
	int i,pnum;
	double I0,I1;
	for(i = 1; i <= nT; i ++){
		if (pset[i][0] == 2){
			I0 = I[i][1]; //Past I
			I1 = I[i][0]; //Present I
			pnum = pset[i][1];
			set[2][pnum][1] -= 0.5*(I0+I1)*dt; // Trapezoid gang
		} 
	}
}

void KAdvance(int *it, double *t, double dt, double I[N2][N], double dI[N2][N], int nP){ // Advance to the next iteration
	*it += 1;
	*t += dt;
	MPush21(I,nP+1,3); //Push present I into past I
	MPush21(dI,nP+1,3);
}

void KColumn(int it, double dt, double t, double I[N2][N], int pset[N2][N], int Node[N2][N2], int nV, int nP, double CKirr[N2], double set[N][N][N]){ // Modify the column vector for the new iteration
	//			 -	      +	-->    --> -       +  bruh shit visualization
	//KCL        |----R---|-----N-----|----R---|                               
	int nodeP, nodeN, Ptype, Pnum, iP; 
	int i,j,Idir;
	for(i = 1; i <= nV-1; i ++){ // Inspecting each Node from Node V1 to Node VN
		CKirr[i-1] = 0;
		for(j = 1; j <= Node[i][0]; j ++){ // Inspecting connected object in a node
			Pnum = Node[i][j];             // Take the object number, positive or negative
			Ptype = pset[abs(Pnum)][0];    // Identify the object type
			Idir = Pnum/abs(Pnum);         // Obtain +1 or -1 depending on current direction
			if(Ptype == 1){                // Check if the object is L
				CKirr[i-1] += -Idir*FIL(t,abs(Pnum),dt,I,set);  // put I on the right side instead because the vector now contain dI/dt instead of I	
			}
		}
	}
	//				             - + --> I
	//KVL             Node(-) ----R---- Node(+)
	for(i = 1; i <= nP; i ++){ // Inspecting each object from object 1 to object N
		Ptype = pset[i][0];
		Pnum = pset[i][1];
		iP = i+nV-2; // New index to complement KCL, -1 for ground node

		if(Ptype == 2){ // C
			CKirr[iP] = FC(t,Pnum,dt,I,set);
		} else if(Ptype == 3){ // E
			CKirr[iP] = FE(t,Pnum,dt,I,set);
		}

	}
}


#endif
