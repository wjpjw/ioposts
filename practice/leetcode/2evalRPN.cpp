#include "wjp.h"
/*
Evaluate reverse polish notation.
["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/



void              test2(){
  vector<string> a{"2","1","+","3","*"};
  evalRPN(a)
}

int evalRPN(vector<string>& tokens) {
    unordered_map<string, function<int (int, int) > > map = {
        { "+" , [] (int a, int b) { return a + b; } },
        { "-" , [] (int a, int b) { return a - b; } },
        { "*" , [] (int a, int b) { return a * b; } },
        { "/" , [] (int a, int b) { return a / b; } }
    };
    std::stack<int> stack;
    for (string& s : tokens) {
        if (!map.count(s)) {
            stack.push(stoi(s));
        } else {
            int op1 = stack.top();
            stack.pop();
            int op2 = stack.top();
            stack.pop();
            stack.push(map[s](op2, op1));
        }
    }
    return stack.top();
}
