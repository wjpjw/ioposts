/*
对于任意正整数 n, 存在一个长度 m 的正整数序列 S = {a1, a2, a3...., am} , 使得 n = a1^3 + a2^3 + ... am^3,
例如： n = 2, S = {1, 1}, 2 = 1^3 + 1 ^3
            n=2016 S={2,2,10,10},2016=2^3+2^3+10^3+10^3输入 n(n< 100000), 输出最短的序列 S(序列的输出按从小到大排序) 
输入：2，输出：11
输入：2016，输出：2 2 10 10
*/


#include "wjp.h"
//S(i)= shortest(S(i-am^3)U{am}), am=1,2,3,...,cbrt(i)
typedef vector<int> seq;
seq get_shortest_sequence(int n){
  vector<seq> S(n+1);
  auto recursive_fill=[&S](int i){
    int t=cbrt(i);
    if(t*t*t==i){
      S[i].push_back(t);
    }
    else{
      int smallest_i=0;
      for(int am=1,smallest_seqsize=INT_MAX;am<=t;am++){
          int cursize=S[i-am*am*am].size();
          if(cursize<=smallest_seqsize){
            smallest_seqsize=cursize;
            smallest_i=am;
          }
      }
      S[i]=S[i-smallest_i*smallest_i*smallest_i];
      S[i].push_back(smallest_i);
    }
  };
  if(n==0)return S[0];
  S[1].push_back(1);
  if(n==1)return S[1];
  for(int i=2;i<=n;i++){
    recursive_fill(i);
  }
  return S[n];
}



void print_sequence(seq s){
  for(int i:s){
    cout<<i<<", ";
  }
  cout<<endl;
}

void test(){
  seq a=get_shortest_sequence(5000);
  print_sequence(a);
}
