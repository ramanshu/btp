/*
Szymon Rusinkiewicz
Princeton University

mesh_cat.cc
Concatenate meshes together
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriMesh.h"
#include <vector>
using namespace std;
TriMesh* combine_models(vector< TriMesh* >* mesh_list)
{
	TriMesh *outmesh = new TriMesh;
	for (int i = 0; i < mesh_list->size(); i++) {
		TriMesh *m = mesh_list->at(i);
		int onv = outmesh->vertices.size();
		outmesh->vertices.insert(outmesh->vertices.end(),
				         m->vertices.begin(),
					 m->vertices.end());

		if (outmesh->colors.empty() && !m->colors.empty())
			outmesh->colors.resize(onv, Color(1,1,1));
		else if (m->colors.empty() && !outmesh->colors.empty())
			m->colors.resize(m->vertices.size(), Color(1,1,1));
		outmesh->colors.insert(outmesh->colors.end(),
				       m->colors.begin(),
				       m->colors.end());

		if (outmesh->confidences.empty() && !m->confidences.empty())
			outmesh->confidences.resize(onv);
		else if (m->confidences.empty() && !outmesh->confidences.empty())
			m->confidences.resize(m->vertices.size());
		outmesh->confidences.insert(outmesh->confidences.end(),
					    m->confidences.begin(),
					    m->confidences.end());

		if (outmesh->normals.empty() && !m->normals.empty()) {
			outmesh->need_normals();
			outmesh->normals.resize(onv);
		} else if (m->normals.empty() && !outmesh->normals.empty())
			m->need_normals();
		outmesh->normals.insert(outmesh->normals.end(),
					m->normals.begin(),
					m->normals.end());

		m->need_faces();
		for (int i = 0; i < m->faces.size(); i++) {
			m->faces[i][0] += onv;
			m->faces[i][1] += onv;
			m->faces[i][2] += onv;
		}
		outmesh->faces.insert(outmesh->faces.end(),
				      m->faces.begin(),
				      m->faces.end());
		delete m;
	}
		return outmesh;//->write(outfile);
}
