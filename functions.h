#include <stdio.h>
#include <math.h>
#define N 10
#define N2 100
#define NI 3
#define F 0.5

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int setc(double h){
	int c = floor(h/1000);
	if(c < 1){
		c = 1;
	}
	return c;
}

// Appear on the right side of the equation
double FC(double t, int pnum, double dt, double I[N2][N], double set[N][N][N]){
	double Ii = I[pnum][1]; // Initial currents
	double qi = set[2][pnum][1]; // Initial charges
	double C = set[2][pnum][0]; // Capacitance
	return 1/C * (qi - 0.5*dt*Ii);
}
double FE(double t, int pnum, double dt, double I[N2][N], double set[N][N][N]){ // Voltage Source
	double V0 = set[3][pnum][0];
	double w = set[3][pnum][1];
	double phi = set[3][pnum][2];
	return V0*cos(w*t);
}
double FIL(double t, int pnum, double dt, double I[N2][N], double set[N][N][N]){
	double Ii = I[pnum][0];
	return Ii;
}

// Appear on the Matrix side
double KR(int pnum, double dt, double set[N][N][N]){
	double R = set[0][pnum][0];
	return R;
}
double KL(int pnum, double dt, double set[N][N][N]){
	double L = set[1][pnum][0];
	return L;
}
double KC(int pnum, double dt, double set[N][N][N]){
	double C = set[2][pnum][0];
	return dt/(C * 2.0);
}

double CEnergy(double C, double q){
	return 0.5*q*q/C;
}
double LEnergy(double L, double I){
	return 0.5*L*I*I;
}
double RPower(double I, double R){
	return I*I*R;
}
double REnergy(double dt, double P0, double P){
	return 0.5*(P0+P)*dt;
}
double TEnergy(int nset[N], int pset[N2][N], double set[N][N][N]){
	double E = 0;
	int i;
	for(i = 1; i <= nset[0]; i ++){
		switch(pset[i][0]){
			case 0:
				break;
			case 1:
				E += set[1][pset[i][1]][1];
				break;
			case 2:
				E += set[2][pset[i][1]][2];
				break;
			case 3:
				break;
			default:
				printf("bruh total energy\n");
		}
	}
	return E;
}
double DEnergy(int nset[N], int pset[N2][N], double set[N][N][N]){
	double E = 0;
	int i;
	for(i = 1; i <= nset[0]; i ++){
		switch(pset[i][0]){
			case 0:
				E += set[0][pset[i][1]][3];
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				printf("bruh diss energy\n");
		}
	}
	return E;
}

double source(double t, double V0, double w, double phi){
	return V0*cos(w*t);
}
double sourcedot(double t, double V0, double w, double phi){
	return -V0*w*sin(w*t);
}


#endif

