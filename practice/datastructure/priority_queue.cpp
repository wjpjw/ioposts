#include <queue>
#include <iostream>

using namespace std;


typedef vector<int>                                     seq;
struct seq_comp{
  bool operator(const seq& a, const seq& b){a.size()>b.size();}
};
typedef priority_queue<seq,vector<seq>,seq_comp>        min_heap;




int                                                     main()
{

  return 0;
}
