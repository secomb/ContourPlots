/************************************************************************
Main program to call subroutines to plot contours of a function specified
by numerical data on a rectangular grid
contr_lines - generates contour lines and labels with contour heights
contr_shade - generates contour lines with colored shading between contours
Each generates a postscript file.  T.W. Secomb, February 2009.  Updated August 2011. 
This code is free to use at your own risk.  Feedback and/or acknowledgement
are appreciated.  Email secomb@u.arizona.edu.
Note: uses nrutil.h and nrutil.cpp as placed in the public domain
by Numerical Recipes at http://www.nrbook.com/a/bookcpdf/c21-1.pdf.
***********************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nrutil.h"

void contr_lines(FILE *ofp, int m, int n, float scalefac, int nl,float xmin,
		   float xmax, float ymin, float ymax, float *cl, float **zv);
void contr_shade(FILE *ofp, int m, int n, float scalefac, int nl,float xmin,
		   float xmax, float ymin, float ymax, float *cl, float **zv,
		   int showscale, int lowcolor, int hatch, int plotcontour);


int main(int argc, char *argv[])
{
	int i,j,m,n,nl,ifun;
	float clmin,clint,xmin,xmax,ymin,ymax,scalefac,x,y;
	float **zv,*cl;
	FILE *ofp;
	nl = 11;
	m = 51;
	n = 41;
	ifun = 4;//change this to use different test functions

	cl = vector(1,nl);
	zv = matrix(1,m,1,n);

	for(i=1; i<=m; i++) for(j=1; j<=n; j++){
		if(ifun == 1){
//test function to give rings above a certain level
			x = 4.*float(i-1)/float(m-1) - 2.;
			y = 4.*float(j-1)/float(n-1) - 2.;
			zv[i][j] = 4./(1+x*x + y*y) - 3./(1+(x*x + y*y)*(x*x + y*y));
		}
		else if(ifun == 2){
//test function to give an apparent convecting and diffusing source
			x = 4.*float(i-1)/float(m-1);
			y = 2.*float(j-1)/float(n-1) - 1.;
			if(fabs(y) < 0.125) zv[i][j] = exp(-x) + 0.05*(4.-x);
			else zv[i][j] = exp(-x)*(1. - log(8.*fabs(y))/log(8.)) + 0.05*(4.-x);
		}
		else if(ifun == 3){
//test function to give modulated sinusoidal dependence
			x = 2.*float(i-1)/float(m-1) - 1.;
			y = 2.*float(j-1)/float(n-1) - 1.;
			zv[i][j] = (cos(4.*x)/(1. + x*x) + sin(4.*y)/(1 + y*y))/2.;
		}
	}



	xmin = -2.;
	ymin = -2.;
	xmax = 2.;
	ymax = 2.;

	clmin = 0.0;
	clint = 0.1;

	scalefac = 500./FMAX(xmax-xmin,ymax-ymin);
	if(ifun == 4){
		clint = 0.4;
		m = 4;
		n = 4;
		for(i=1; i<=m; i++) for(j=1; j<=n; j++){
			if(i == 1 || i == 3) zv[i][j] = j;
			else zv[i][j] = 5 - j;
		}
		zv[1][1] = 0;
		zv[1][2] = 1;
		zv[1][3] = 1;
		zv[1][4] = 0;
		zv[2][1] = 1;
		zv[2][2] = 2;
		zv[2][3] = 2;
		zv[2][4] = 1;
		zv[3][1] = 2;
		zv[3][2] = 3;
		zv[3][3] = 3;
		zv[3][4] = 2;
		zv[4][1] = 1;
		zv[4][2] = 2;
		zv[4][3] = 2;
		zv[4][4] = 1;
	}
	for(i=1; i<=nl; i++) cl[i] = clmin + (i-1)*clint;
	
	//Simple line contour plot, with contour labels
	ofp = fopen("Contour_lines.ps", "w");
	contr_lines(ofp, m, n, scalefac, nl, xmin, xmax, ymin, ymax, cl, zv);
//These commands are in the main program to allow further additions to page.
	fprintf(ofp, "showpage\n");
	fclose(ofp);

//Color shaded contour plot, with color bar
	ofp = fopen("Contour_shade.ps", "w");
	contr_shade(ofp, m, n, scalefac, nl, xmin, xmax, ymin, ymax, cl, zv,1,1,0,0);
	fprintf(ofp, "showpage\n");
	fclose(ofp);

//Color shaded contour plot, with line contours and color bar
	ofp = fopen("Contour_shade_lines.ps", "w");
	contr_shade(ofp, m, n, scalefac, nl, xmin, xmax, ymin, ymax, cl, zv,1,1,0,1);
	fprintf(ofp, "showpage\n");
	fclose(ofp);

//Contour plot using diagonal hatching
	cl[1] = 0.5;
	ofp = fopen("Contour_hatch.ps", "w");
	contr_shade(ofp, m, n, scalefac, 1, xmin, xmax, ymin, ymax, cl, zv,0,0,1,1);
	fprintf(ofp, "showpage\n");
	fclose(ofp);
	
	return 0;
}