#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *gp;
	
	gp=popen("gnuplot -persist","w");
	fprintf(gp,"plot \"gnuplot.csv\" using 1:2 with linespoints\n");
	
	pclose(gp);
	return 0;
}
