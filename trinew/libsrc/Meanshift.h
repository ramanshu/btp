#include "pairing.h"
typedef vector<Transformation> ModeList;




class Meanshift{
    ModeList *modelist;
    Transformation_list *input;   
    double bandwidth;
    double kernel(Transformation &a,Transformation &b)
    {
      return exp(bandwidth*((a-b).normSq());
    }
    bool same(Transformation &a,Transformation &b)
    {
    /// code for cheking a, bif they can be merged;
    return true;
    }
    void find_modes()
    { 
      ModeList *temp_modes=new ModeList();
      double k_i_j,k_sum;
      for(i=0;i<modelist->size();i++)
      {
      Transformation temp(0);
      k_sum=0;
      for(int j=0;j<input->size();j++)
      {
      k_i_j=*kernel(modelist->at(i),input->at(j));
      temp+=input[j]*k_i_j;
      k_sum+=k_i_j;
      }
      temp=temp*(1/k_sum);
      temp_modes->push_back(temp);
      }
      modelist->clear();
      modelist=temp_modes;
    }
    void merge_modes()
    {
       ModeList *temp_modes=new ModeList();
       vector<vector<int> > lists;
      for(int i=0;i<mode_list->size();i++)
      {
       int count=0;
       for(int j=0;j<temp_modes->size();j++)
       {
       if(same(mode_list->at(i),temp_modes->at(j)))
       {
       lists[j].push_back(i);
       
        count++;
        break;
       }
       }
       if(count==0)
       {
       temp_modes->push_back(mode_list->at(i));
       list.push_back(vector<int>(i));
       }
      }
       for(int j=0;j<temp_modes->size();j++)
       {
       temp_modes->at(j).points=new vector<pair<int,int> >();
       for(int i=0;i<lists[j].size();j++)
       {
       for(int k=0;k<mode_list->at(j).points->size();k++)
        temp_modes->at(j).points->push_back(mode_list->at(lists[j][i]).points->at(k));
        }
       }
       mode_list->clear();
       mode_list=temp_modes;
    }


    void mean_shift()
    {
    
    
    while(1)    
    {
        find_modes(modelist,Transformation_list)
        merge_modes();
    }
    
    
    
    
    
    
    
    }
 /*   Modelist *modes;
    vecotor<Modelist> temp_modes;
    
    bool isSame(Transformation &a,Transformation &b)
    {
    // Code for Merging transformations.
    }
    void merge_transformations(Modelist *modelist,Transformation *tolerance,float ftolerance)
    {
     for(int i=0;i<modelist.size();i++)
     {
     count=0;
     for(int j=0;j<templist.size();j++)
     {
       if(isSame(templist[j],modelist[i])
       {
       count++;
       }
     }
      if(count==0)
      {
         templist.push_back(modelist[i]);
      }      
     }
    }
*/

};
