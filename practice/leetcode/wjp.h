#include <stack>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <climits>
#include<cstring>
#include<cstdio>

using namespace std;

void test();

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class TreeNode {
 public:
     int val;
     TreeNode *left, *right;
     TreeNode(int val) {
         this->val = val;
         this->left = this->right = NULL;
     }
};
