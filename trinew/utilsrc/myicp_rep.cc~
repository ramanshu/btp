#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "KDtree.h"
using namespace std;


void growMatch(Transformation_list *list,Transformation_list *norm_list, Transformation *matched, TriMesh *mesh, KDtree *kd, vector< pair<int,int> >* match, bool covered[]) {
	if(covered[(matched->points)->first]) 
		return;
	std::list<int> patch;
	bool covered1[mesh->vertices.size()];
	vector< pair<int,int> > *new_match=new vector< pair<int,int> >();
	patch.push_back((matched->points)->first);
	new_match->push_back(*(matched->points));
	int i = (matched->points)->first;
	covered1[i] = true;
	while(!patch.empty()) {
		int temp = patch.front();
		patch.pop_front();
		vector<int> candidates = mesh->neighbors[temp];
		for(vector<int>::iterator it = candidates.begin(); it != candidates.end(); it++) {
			if(covered1[*it]) 
				continue;
			point pt = mesh->vertices[*it];
			point nearpt = applyTransformation(matched, &pt);
			const float *pts = kd->closest_to_pt(nearpt, 0.09);
			if (!pts)
				continue;
			int ind = (pts - (const float *) &(mesh->vertices[0][0])) / 3;
			if (ind < 0 || ind >= mesh->vertices.size())
				continue;
			patch.push_back(*it);
			covered1[*it] = true;
			pair<int,int> ptpair(*it, ind);
			new_match->push_back(ptpair);
		}
	}
	if(new_match->size() > 30) {
		for(vector< pair<int,int> >::iterator it = new_match->begin(); it != new_match->end(); it++) 
			covered[it->first] = true;
		match->insert(match->begin(), new_match->begin(), new_match->end());
		
	}
}


vector< vector< pair<int,int> >* >* growCLuster_ICP(Transformation_list *list,Transformation_list *norm_list,Transformation_list *modes_list, TriMesh *mesh)
{
	float differ;
	int clusterno = 0;
	float diagonal = mesh->need_diagonal_length();
	KDtree *kd = new KDtree(mesh->vertices);
	mesh->need_neighbors();
	vector< vector< pair<int,int> >* >* modesMatch = new vector< vector< pair<int,int> >* >();
	for(Transformation_list::iterator it = modes_list->begin(); it != modes_list->end(); it++) {
		Transformation temp1(0);
		vector< pair<int,int> >*match = new vector< pair<int,int> >();
		bool covered[mesh->vertices.size()];
		Transformation_list::iterator it2 = list->begin();
		Transformation_list::iterator it1 = norm_list->begin();
		for(; it1 != norm_list->end(); it1++,it2++) {
			temp1 = (*(*it)-*(*it1));
			differ = temp1.norm();
			if(differ < 200) {
				growMatch(list, norm_list, *it2, mesh, kd, match, covered);
			}
		}
		if(match->size() > 1) {
			modesMatch->push_back(match);
			clusterno++;
		}
	}
	cout << clusterno << endl;
	return modesMatch;
}
