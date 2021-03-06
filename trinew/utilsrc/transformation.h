#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string.h>
#include "TriMesh.h"
#include "XForm.h"
#include "GLCamera.h"
#include "ICP.h"`
#include "strutil.h"
#include <GL/glut.h>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
typedef vector < float >vectf;
class Transformation
{
public:
	double s;
	double *r;
	double *t;
	double Q[3][3];
/*	static double max_s;
	static double *max_r;
	static double *max_t;
	static double min_s;
	static double *min_r;
	static double *min_t;
	static double sum_s;
	static double *sum_r;
	static double *sum_t;
	static double sumsq_s;
	static double *sumsq_r;
	static double *sumsq_t;*/
	static int count;
	pair < int, int >*points;
  	static void initialize()
  	{
  		
  	}
	public:Transformation (TriMesh * mesh, int i, int j) 
	{
			points = new pair < int, int >(i, j);
			s = ((mesh->curv2[i] / mesh->curv2[j]) +(mesh->curv1[i] / mesh->curv1[j])) / 2;
			vec * system1 = new vec[3];
    		system1[0] = mesh->pdir1[i];
    		system1[1] = mesh->pdir2[i];
    		system1[2] = mesh->normals[i];
    		vec * system2 = new vec[3];
    		system2[0] = mesh->pdir1[j];
    		system2[1] = mesh->pdir2[j];
    		system2[2] = mesh->normals[j];
			eulerian_angles (system1, system2, mesh);
			translation (mesh->vertices[i], mesh->vertices[j], Q, s);
	} 
	public:Transformation (int x) 
	{
    		s = x;
    		r = new double[3];
    		t = new double[3];
    		r[0] = x;
    		r[1] = x;
    		r[2] = x;
    		t[0] = x;
    		t[1] = x;
    		t[2] = x;
	} 
	public:Transformation (double s0, double r0, double r1, double r2, double t0,double t1, double t2) 
	{
    	s = s0;
    	r = new double[3];
    	t = new double[3];
    	r[0] = r0;
    	r[1] = r1;
    	r[2] = r2;
    	t[0] = t0;
    	t[1] = t1;
    	t[2] = t2;
	} 
	double normSq () 
	{
		return (pow (s, 2) + pow (r[0], 2) + pow (r[1], 2) + pow (r[2], 2) + pow (t[0], 2) + pow (t[1], 2) + pow (t[2], 2));  
	}
  
	double norm () 
	{
		return sqrt (pow (s, 2) + pow (r[0], 2) + pow (r[1], 2) + pow (r[2], 2) + pow (t[0], 2) + pow (t[1], 2) + pow (t[2], 2));
  
	}
  
	Transformation operator- (const Transformation a) 
	{
		Transformation temp (s - a.s, r[0] - a.r[0], r[1] - a.r[1], r[2] - a.r[2], t[0] - a.t[0], t[1] - a.t[1],t[2] - a.t[2]);
		return temp;
	}
	Transformation operator+ (const Transformation a) 
	{
		Transformation temp (s + a.s, r[0] + a.r[0], r[1] + a.r[1],r[2] + a.r[2], t[0] + a.t[0], t[1] + a.t[1],t[2] + a.t[2]);
		return temp;
	}
	
	void operator+= (const Transformation a) 
	{
		s += a.s;
		r[0] += a.r[0];
		r[1] += a.r[1];
		r[2] += a.r[2];
		t[0] += a.t[0];
		t[1] += a.t[1];
    		t[2] += a.t[2];
	} 
	Transformation operator* (double a) 
	{
		Transformation temp (s * a, r[0] * a, r[1] * a, r[2] * a, t[0] * a, t[1] * a, t[2] * a);    
		return temp;
	}
  
	void printTrans () 
	{
		printf ("s=%.3f r0=%.3f r0=%.3f r0=%.3f t0=%.3f t0=%.3f t0=%.3f\n", s,r[0], r[1], r[2], t[0], t[1], t[2]);
	} 
	void eulerian_angles (vec * system1, vec * system2, TriMesh * mesh) 
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)		
			{	  
				Q[i][j] = system2[0][i]*system1[0][j] + system2[1][i]*system1[1][j] + system2[2][i]*system1[2][j];
			}
		} 
		double theta, psi, phi;
		if (fabs (Q[2][0]) != 1)
      		{
			theta = -asin (Q[2][0]);	
			psi = atan2 (Q[2][1] / cos (theta), Q[2][2] / cos (theta));	
			phi = atan2 (Q[1][0] / cos (theta), Q[0][0] / cos (theta));	
		}
		else
		{
			phi = 0;	
			double delta = atan2 (Q[0][1], Q[0][2]);
			if (Q[2][0] == -1)
			{
				theta = M_PI / 2;
	    			psi = phi + delta;
	  		}
	  		else
	  		{
	  			theta = -M_PI / 2;
	    			psi = -phi + delta;
	  		}
	  	}
		r = new double[3];
		r[0] = psi;
		r[1] = theta;
		r[2] = phi;
	}
  
	void translation (const point & pt1, const point & pt2, double Q[][3] ,double st)
	{
		t = new double[3];
		t[0] = pt2[0] - st * (Q[0][0] * pt1[0] + Q[0][1] * pt1[1] + Q[0][2] * pt1[2]);
		t[1] = pt2[1] - st * (Q[1][0] * pt1[0] + Q[1][1] * pt1[1] + Q[1][2] * pt1[2]);
		t[2] = pt2[2] - st * (Q[2][0] * pt1[0] + Q[2][1] * pt1[1] + Q[2][2] * pt1[2]);

	} 
};




point applyTransformation(Transformation *trans,point *pt)
{
	float rm[3][3];
	float ca = cos(trans->r[0]);
	float cb = cos(trans->r[1]);
	float cg = cos(trans->r[2]);
	float sa = sin(trans->r[0]);
	float sb = sin(trans->r[1]);
	float sg = sin(trans->r[2]);
	rm[0][0] = cg*cb;			
	rm[0][1] = cg*sb*sa - sg*ca;
	rm[0][2] = cg*sb*ca + sg*sa;
	rm[1][0] = sg*cb;
	rm[1][1] = sg*sb*sa + cg*ca;
	rm[1][2] = sg*sb*ca - cg*sa;
	rm[2][0] = -sb;
	rm[2][1] = cb*sa;
	rm[2][2] = cb*ca;
	float pt0 = trans->t[0] + trans->s * (rm[0][0] * (*pt)[0] + rm[0][1] * (*pt)[1] + rm[0][2] * (*pt)[2]);
	float pt1 = trans->t[1] + trans->s * (rm[1][0] * (*pt)[0] + rm[1][1] * (*pt)[1] + rm[1][2] * (*pt)[2]);
	float pt2 = trans->t[2] + trans->s * (rm[2][0] * (*pt)[0] + rm[2][1] * (*pt)[1] + rm[2][2] * (*pt)[2]);
	point ptn(pt0, pt1, pt2);
	return ptn;
}

 
