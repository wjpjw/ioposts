#include "wjp.h"
/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
For example, Given: s1 = ”aabcc”, s2 = ”dbbca”,
When s3 = ”aadbbcbcac”, return true.
When s3 = ”aadbbbaccc”, return false.
*/

bool              isInterleave(string s1, string s2, string s3) {
  //[0]
  if(s1.size()+s2.size()!=s3.size()){
    return false;
  }
  // f(p1,p2) first p1/p2 elements of s1/s2 forms the first p1+p2-1 elements of s3
  bool f[s1.size()+1][s2.size()+1];

  for(int i=0;i<=s1.size();i++){
    for(int j=0;j<=s2.size();j++){
      auto p1=[&](int i,int j)->bool{
        if(i<0)return true;
        return f[i][j]&&s1[i]==s3[i+j];
      };
      auto p2=[&](int i, int j)->bool{
        if(j<0)return true;
        return f[i][j]&&s2[j]==s3[i+j];
      };

      f[i][j]=  p1(i-1,j)||p2(i,j-1);
      cout<<i<<","<<j<<":"<<f[i][j]<<"\n";
    }
  }
  return f[s1.size()][s2.size()];
}


void              test1(){
  cout<<"aabcc"<<" interleave "<<"dbbca\n";
  cout<<isInterleave("aabcc", "dbbca", "aadbbcbcac")<<"---aadbbcbcac\n";
  cout<<isInterleave("aabcc", "dbbca", "aadbbbaccc")<<"---aadbbbaccc\n";
}
