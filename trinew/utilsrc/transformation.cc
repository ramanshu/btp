#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include "TriMesh.h"
#include "XForm.h"
#include "GLCamera.h"
#include "ICP.h"
#include "strutil.h"
#include <GL/glut.h>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
class transformation{
    double s;
    double r[3];
    double t[3];     
    pair<int,int> *points;
    transformation(TriMesh *mesh,int i, int j)   
    {
           points=new pair<int,int>(i,j);
           s=(mesh->curv2[i]/mesh->curv2[j])+(mesh->curv1[i]/mesh->curv1[j]);
    }
    transformation(double s0,double r0,double r1,double r2,double t0,double t1,double t2)   
    {
           s=s0;
           r[0]=r0;
           r[1]=r1;
           r[2]=r2;
           t[0]=t0;
           t[1]=t1;
           t[2]=t2;    
    }
    transformation operator- (const transformation a)
    {
    transformation temp(s-a.s,r[0]-a.r[0],r[1]-a.r[1],r[2]-a.r[2],t[0]-a.t[0],t[1]-a.t[1],t[2]-a.t[2]);
    return temp;    
    }
    transformation operator+ (const transformation a)
    {
    transformation temp(s+a.s,r[0]+a.r[0],r[1]+a.r[1],r[2]+a.r[2],t[0]+a.t[0],t[1]+a.t[1],t[2]+a.t[2]);
    return temp;    
    }
    
};
/*

void normalize(double *vector) {
	double magnitude = pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2);
	vector[0] = vector[0]/magnitude;
	vector[1] = vector[1]/magnitude;
	vector[2] = vector[2]/magnitude;
}
	
double dot_product(double *vector1, double *vector2, int dimension) {

	double dproduct;
	for(int i = 0; i < dimension; dimension++)
		dproduct += vector1[i]*vector2[i];
	return(dproduct);
}
	
double* find_normal(double *vector1, double *vector2) {

	double normal[3];	
	normal[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
	normal[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2];
	normal[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];
	normalize(normal);
	
	return(normal);
}

double* compute_eulerangles(double *dcurv11, double *dcurv12, double *normal1, double *dcurv21, double *dcurv22, double *normal2) {

	double eulerangles[3];
	double* line_of_nodes = find_normal(normal1, normal2);
	
	eulerangles[0] = fabs(acos(dot_product(dcurv11, line_of_nodes, 3)));
	eulerangles[1] = fabs(acos(dot_product(normal1, normal2, 3)));
	eulerangles[2] = fabs(acos(dot_product(dcurv21, line_of_nodes, 3)));	
	return eulerangles;
}

void euleranglesto_RotationMatrix(double* eulerangles, double rotation_matrix[][3]) {

	double ca = cos(eulerangles[0]);
	double cb = cos(eulerangles[1]);
	double cg = cos(eulerangles[2]);
	double sa = sin(eulerangles[0]);
	double sb = sin(eulerangles[1]);
	double sg = sin(eulerangles[2]);
	
	rotation_matrix[0][0] = cg*cb;			
	rotation_matrix[0][1] = cg*sb*sa - sg*ca;
	rotation_matrix[0][2] = cg*sb*ca + sg*sa;
	rotation_matrix[1][0] = sg*cb;
	rotation_matrix[1][1] = sg*sb*sa + cg*ca;
	rotation_matrix[1][2] = sg*sb*ca - cg*sa;
	rotation_matrix[2][0] = -sb;
	rotation_matrix[2][1] = cb*sa;
	rotation_matrix[2][2] = cb*ca;
	
}

double** matrix_multiplication(double matrix1[][3], double matrix2[][1], int p, int q, int r) {
	
	double** pmatrix = 0;
	pmatrix = new double*[p];
	for(int i = 0; i < p; i++) {
		pmatrix[p] = new double[r];
		for(int j = 0; j < r; j++) {
			pmatrix[i][j] = 0;
			for(int k = 0; k < q; k++) {
				pmatrix[i][j] += matrix1[i][k]*matrix2[k][j];
			}
		}
	}
	return pmatrix;
	
}

double* compute_translate(double* pt1, double* pt2, double rotation_matrix[][3], double scale_transformation) {
	
	double** inter;
	double translate[3];
	double ptn1[3][1];
	ptn1[0][0] = pt1[0];
	ptn1[1][0] = pt1[1];
	ptn1[2][0] = pt1[2];
	inter = matrix_multiplication(rotation_matrix, ptn1, 3, 3, 1);
	translate[0] = pt2[0] - scale_transformation*inter[0][0];
	translate[1] = pt2[1] - scale_transformation*inter[1][0];
	translate[2] = pt2[2] - scale_transformation*inter[2][0];
	
	return translate;
	
}
double* transformation(double *pt1, double *pt2, double *dcurv11, double *dcurv12, double *dcurv21, double *dcurv22, double mcurv11, double mcurv12, double mcurv21, double mcurv22) {

	double scale_transformation;
	double* translate_transformation;
	double* rotate_transformation;
	double* normal1;
	double* normal2;
	double rotation_matrix[3][3];
	
	normal1 = find_normal(dcurv11, dcurv12);
	normal2 = find_normal(dcurv21, dcurv22);
	
	scale_transformation = (mcurv11/mcurv21 + mcurv12/mcurv22)/2;
	rotate_transformation = compute_eulerangles(dcurv11, dcurv12, normal1, dcurv21, dcurv22, normal2);
	euleranglesto_RotationMatrix(rotate_transformation, rotation_matrix);
	translate_transformation = compute_translate(pt1, pt2, rotation_matrix, scale_transformation);
	
	return rotate_transformation;
}
*/
int main() {
	return 0;
}
