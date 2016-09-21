#include "wjp.h"
/*

Given two arrays of length m and n with digits 0-9 representing two numbers.
Create the maximum number of length k <= m + n from digits of the two.
The relative order of the digits from the same array must be preserved.
Return an array of the k digits. You should try to optimize your time and space complexity.

Example
Given nums1 = [3, 4, 6, 5], nums2 = [9, 1, 2, 5, 8, 3], k = 5
return [9, 8, 6, 5, 3]

Given nums1 = [6, 7], nums2 = [6, 0, 4], k = 5
return [6, 7, 6, 0, 4]

Given nums1 = [3, 9], nums2 = [8, 9], k = 3
return [9, 8, 9]
*/

namespace createmaxnr{
  // rrrrrbbbb
  struct RedBlueArray{
    RedBlueArray(int*arr,int size):arr(arr),size(size),red_nr(0){}
    int* arr;
    int  size;
    int  red_nr; //the index of 1st blue cell
    void append(int x){
      arr[red_nr]=x;
      red_nr++;
    }
    int  blue_nr(){return size-pos;}
    int  at(int x){return arr[x];}
  };
}
using namespace createmaxnr;

//Cost of data abstraction is low. Yet it will improve readability.
int[] maxNumber(int[] nums1, int[] nums2, int m, int n, int k) {
  int res[k];
  RedBlueArray a1(nums1,m);
  RedBlueArray a2(nums2,n);
  RedBlueArray a3(res,k);
  auto deserted_nr=[&]()->int{return a1.red_nr+a2.red_nr-a3.red_nr;}
  auto desertable_nr=[&]()->int{return a1.size+a2.size-a3.size-deserted_nr();}
  //return the index of largest blue cell
  auto find_largest_blue_cell_in=[&](RedBlueArray*target)->int{
    int largest_index=target->red_nr;
    for(int i=0,cur_desertable_nr=desertable_nr();i<cur_desertable_nr;i++){
      if(target->at(i)>target->at(largest_index)){
        largest_index=i;
      }
    }
  }
  auto get_largest_and_paint_red=[&]()->int{
    int l1=find_largest_blue_cell_in(&a1);
    int l2=find_largest_blue_cell_in(&a2);
    int d1=a1.at(l1);
    int d2=a2.at(l2);
    int largest;
    if(d1>d2){
      largest=d1;
      a1.red_nr=l1+1;
    }
    else{
      largest=d2;
      a2.red_nr=l2+1;
    }
    return largest;
  }
  while(a3.red_nr<=a3.size){
    a3.append(get_largest_and_paint_red());
  }
  return res;
}



void test3(){

}
