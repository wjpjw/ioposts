#include "wjp.h"


// int a[]={3,8,5,1,7,8};
// no transactions overlap;
// transaction nr=2

// Reuse stock1, divide and conqure.
// Straight forward, yet compromised. Divede is often avoidable.
int stock3_naive(vector<int> prices){
  // transaction nr=1 situation
  auto find_max_increment=[&](int start,int end){
    int min_price=prices[0];
    int max_profit=0;
    for(int k=start;k<=end;k++){
      min_price=min(prices[k],min_price);
      max_profit=max(max_profit, prices[k]-min_price);
    }
    return max_profit;
  };
  int max=0;
  for(int i=0,transaction1,transaction2;i<prices.size();i++){
    int profit=find_max_increment(0,i)+find_max_increment(i+1,prices.size()-1);
    if(max<profit){
      max=profit;
    }
  }
  return max;
}



// int a[]={3,8,5,1,7,8};
// transaction nr=1
int stock1(vector<int> prices){
  int min_price=prices[0];
  int max_profit=0;
  for(auto i:prices){
    min_price=min(i,min_price);
    max_profit=max(i-min_price,max_profit);
  }
  return max_profit;
}
// int a[]={3,8,5,1,7,8};
// no transactions overlap;
// transaction nr=2
int stock3(vector<int> prices){
  int min_price1=INT_MAX;
  int min_price2=INT_MAX;
  int max_profit1=0;
  int max_profit2=0;
  for(auto i: prices){
    min_price1=min(min_price1, i);
    max_profit1=max(max_profit1, i-min_price1); //1st transaction's profit equals to reduction of min_price2
    min_price2= min(min_price2, i-max_profit1);
    max_profit2=max(max_profit2, i-min_price2);
  }
  return max_profit2;
}



void test(){
  vector<int> x{3,8,5,1,7,8};
  cout<<stock3(x);
}
