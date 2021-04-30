#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N2 100
#ifndef SCRIPTS_H
#define SCRIPTS_H

void CHelp(void); // Main Menu help
void CHelp2(void); // Circuit help
void CHelpS(void); // Sample help
void CHelpS1(void); // Sample help - DC
void CHelpS2(void); // Sample help - RLC
void CHelpS3(void); // Sample help - AC
void CHelpS4(void); // Sample help - complex
int CSample1(char path[N2]);
int CSample2(char path[N2]);
int CSample3(char path[N2]);
int CSample4(char path[N2]);

int CSample1(char path[N2]){
	CHelpS1();
	char i;
	int p = 0;
	while(p == 0){
		printf("DC circuits\n");
		printf("Enter a command ");
		scanf("%s",&i);
		p = 1;
		switch (i){
			case '1':
				strcpy(path,"punchcards//dc//1serdc1r.txt");
				break;
			case '2':
				strcpy(path,"punchcards//dc//2serdc2r.txt");
				break;
			case '3':
				strcpy(path,"punchcards//dc//3pardc2r.txt");
				break;
			case '4':
				strcpy(path,"punchcards//dc//4par2v2r.txt");
				break;
//			case '5':
//				strcpy(path,"punchcards//dc//1serdc1r.txt");
//				break;
			case '8':
				strcpy(path,"punchcards//dc//8wheat.txt");
				break;
			case '9':
				return 0;
				break;
			default:
				printf("Invalid command\n");
				p = 0;
				break;
		}
	}
	return 1;
}

int CSample2(char path[N2]){
	CHelpS2();
	char i;
	int p = 0;
	while(p == 0){
		printf("RLC circuits\n");
		printf("Enter a command ");
		scanf("%s",&i);
		p = 1;
		switch (i){
			case '1':
				strcpy(path,"punchcards//rlc//1serrl.txt");
				break;
			case '2':
				strcpy(path,"punchcards//rlc//2serrc.txt");
				break;
			case '3':
				strcpy(path,"punchcards//rlc//3lc.txt");
				break;
//			case '4':
//				strcpy(path,"punchcards//rlc//4rlc.txt");
//				break;
			case '5':
				strcpy(path,"punchcards//rlc//5lcparrser.txt");
				break;
			case '7':
				strcpy(path,"punchcards//rlc//7serrlc.txt");
				break;
			case '8':
				strcpy(path,"punchcards//rlc//8parrlc.txt");
				break;
			case '9':
				return 0;
				break;
			default:
				printf("Invalid command\n");
				p = 0;
				break;
		}
	}
	return 1;
}

int CSample3(char path[N2]){
	CHelpS3();
	char i;
	int p = 0;
	while(p == 0){
		printf("AC circuits\n");
		printf("Enter a command ");
		scanf("%s",&i);
		p = 1;
		switch (i){
//			case '1':
//				strcpy(path,"punchcards//ac//.txt");
//				break;
//			case '2':
//				strcpy(path,"punchcards//ac//.txt");
//				break;
//			case '3':
//				strcpy(path,"punchcards//ac//.txt");
//				break;
//			case '4':
//				strcpy(path,"punchcards//ac//.txt");
//				break;
			case '9':
				return 0;
				break;
			default:
				printf("Invalid command\n");
				p = 0;
				break;
		}
	}
	return 1;
}

int CSample4(char path[N2]){
	CHelpS4();
	char i;
	int p = 0;
	while(p == 0){
		printf("Complex circuits\n");
		printf("Enter a command ");
		scanf("%s",&i);
		p = 1;
		switch (i){
			case '1':
				strcpy(path,"punchcards//cplx//1dccplx.txt");
				break;
			case '2':
				strcpy(path,"punchcards//cplx//2dccplxr.txt");
				break;
//			case '3':
//				strcpy(path,"punchcards//cplx//.txt");
//				break;
			case '8':
				strcpy(path,"punchcards//cplx//8-god.txt");
				break;
			case '9':
				return 0;
				break;
			default:
				printf("Invalid command\n");
				p = 0;
				break;
		}
	}
	return 1;
}

void CHelpS(void){
	printf("Enter a number available below to select sample circuits.\n");
	printf("1 - DC circuits\n");
	printf("2 - RLC models\n");
	printf("3 - AC circuits\n");
	printf("4 - More complex circuits\n");
	printf("9 - back to main menu\n");
}
void CHelp(void){
	printf("Please enter a number command available below.\n");
	printf("1 - Pure Series Circuit\n");
	printf("2 - Pure Parallel Circuit\n");
	printf("3 - Custom Circuit\n");
	printf("4 - Use pre-existing samples circuits\n");
	printf("5 - Create template input file\n");
	printf("9 - exit\n");
}
void CHelp2(void){
	printf("Enter a letter as a command as available below\n");
	printf("R - Resistor\n");
	printf("L - Inductor\n");
	printf("C - Capacitor\n");
	printf("V - Voltage Source\n");
	printf("P - List all objects added\n");
	printf("U - Undo the last object\n");
	printf("S - Reset\n");
	printf("F - Finish\n");
}

void CHelpS1(void){
	printf("Enter a number available below to select sample circuits.\n");
	printf("1 - Series 1 V 1 R\n");
	printf("2 - Series 1 V 2 R\n");
	printf("3 - Parallel 1 V 2 R\n");
	printf("4 - Parallel 2 V 4 R\n");
	printf("5 - Coming soon\n");
	printf("6 - Coming soon\n");
	printf("7 - Coming soon\n");
	printf("8 - Wheatstone bridge\n");
	printf("9 - back to sample menu\n");
}
void CHelpS2(void){
	printf("Enter a number available below to select sample circuits.\n");
	printf("1 - RL charging\n");
	printf("2 - RC charging\n");
	printf("3 - LC Free\n");
	printf("4 - Coming soon\n");
	printf("5 - LC parallel with R series\n");
	printf("6 - Coming soon\n");
	printf("7 - RLC-Series discharging\n");
	printf("8 - RLC-Parallel discharging\n");
	printf("9 - back to sample menu\n");
}
void CHelpS3(void){
	printf("Enter a number available below to select sample circuits.\n");
	printf("1 - Coming soon\n");
	printf("2 - Coming soon\n");
	printf("3 - Coming soon\n");
	printf("4 - Coming soon\n");
	printf("5 - Coming soon\n");
	printf("6 - Coming soon\n");
	printf("7 - Coming soon\n");
	printf("9 - back to sample menu\n");
}
void CHelpS4(void){
	printf("Enter a number available below to select sample circuits.\n");
	printf("1 - Complex DC RLC\n");
	printf("2 - Coming soon\n");
	printf("3 - Coming soon\n");
	printf("4 - Coming soon\n");
	printf("5 - Coming soon\n");
	printf("6 - Coming soon\n");
	printf("7 - Coming soon\n");
	printf("8 - Ultimate circuit\n");
	printf("9 - back to sample menu\n");
}

#endif
