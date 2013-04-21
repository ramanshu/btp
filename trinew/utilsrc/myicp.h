#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "KDtree.h"
using namespace std;

typedef pair<int,int> intpair;
typedef pair<intpair,bool> intbpair;


void growMatch(Transformation_list *list,Transformation_list *norm_list, Transformation *matched, TriMesh *mesh, KDtree *kd, vector< pair<int,int> >* match, bool covered[], bool coveredsec[], float diagonal) {
	if(covered[(matched->points)->first] || coveredsec[(matched->points)->second]) 
		return;
	bool reflect;
	if((matched->points)->second >= mesh->vertices.size()/2) {cout << "reflect" << endl;
		reflect = true;}
	else {cout << "not reflect" << endl;
		reflect = false;}
	std::list<intbpair> patch;
	bool covered1[mesh->vertices.size()];
	bool coveredsec1[mesh->vertices.size()];
	vector<intpair> new_match;
	intpair ptp((matched->points)->first, (matched->points)->second);
	pair<intpair,bool> ptb(ptp, true);
	patch.push_back(ptb);
	int i = (matched->points)->first;
	covered1[i] = true;
	while(!patch.empty()) {
		intbpair temp = patch.front();
		patch.pop_front();
		vector<int> candidates = mesh->neighbors[(temp.first).first];
		bool nmatched = false;
		for(vector<int>::iterator it = candidates.begin(); it != candidates.end(); it++) {
			bool mtchd = false;
			if(covered1[*it] || coveredsec1[*it]) {
				mtchd = true;
				nmatched = true;
				continue;
			}
			point pt = mesh->vertices[*it];
			point nearpt = applyTransformation(matched, &pt);
			vector<const float *> nearpts;
			kd->find_k_closest_to_pt(nearpts, 10, nearpt, 0.001*diagonal);
			int ind;
			for(i = 0; i < nearpts.size(); i++) {
				const float *pts = nearpts[i];
				if(!pts) 
					continue;
				ind = (pts - (const float *) &(mesh->vertices[0][0])) / 3;
				if (ind < 0 || ind >= mesh->vertices.size() || coveredsec1[ind] || *it == ind || reflect && ind < mesh->vertices.size()/2 || !reflect && ind >= mesh->vertices.size()/2) 
					continue;
				else {
					nmatched = true;
					mtchd = true;
					break;
				}
			}
			covered1[*it] = true;
			coveredsec1[ind] = true;
			pair<int,int> ptpair(*it, ind);
			pair<intpair,bool> ptb(ptpair, mtchd);
			patch.push_back(ptb);
		}
		if(temp.second || nmatched) 
			new_match.push_back(temp.first);
	}
	if(new_match.size() > 10) {
		for(vector< pair<int,int> >::iterator it = new_match.begin(); it != new_match.end(); it++) {
			covered[it->first] = true;
			coveredsec[it->second] = true;
		}
		match->insert(match->begin(), new_match.begin(), new_match.end());
		
	}
}


vector< vector< pair<int,int> >* >* growCLuster_ICP(Transformation_list *list,Transformation_list *norm_list,Transformation_list *modes_list, TriMesh *mesh)
{
	float differ;
	int clusterno = 0;
	float diagonal = mesh->need_diagonal_length();
	KDtree *kd = new KDtree(mesh->vertices);
	mesh->need_neighbors();
	vector< vector< pair<int,int> >* >* modesMatch = new vector< vector< pair<int,int> >* >();int clusternum = 0;
	for(Transformation_list::iterator it = modes_list->begin(); it != modes_list->end(); it++) {
		Transformation temp1(0);
		vector< pair<int,int> >*match = new vector< pair<int,int> >();
		bool covered[mesh->vertices.size()];
		bool coveredsec[mesh->vertices.size()];
		Transformation_list::iterator it2 = list->begin();
		Transformation_list::iterator it1 = norm_list->begin();
		int numsatisfy = 0;
		for(; it1 != norm_list->end(); it1++,it2++) {
			temp1 = (*(*it)-*(*it1));
			differ = temp1.norm();
			
			if(differ < .05*((*(*it)).norm())) {
				numsatisfy++;
				growMatch(list, norm_list, *it2, mesh, kd, match, covered, coveredsec, diagonal);
			}
		}
		cout << clusternum++ << " " << numsatisfy << " " << match->size() << endl;
		if(match->size() > 1) {
			modesMatch->push_back(match);
			clusterno++;
		}
	}
	cout << clusterno << endl;
	return modesMatch;
}





