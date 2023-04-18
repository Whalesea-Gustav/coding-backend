#include <GP/GP_macro.h>
#include "header.h"

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        stack<int> stk;
        int i = 0, j = 0;
        while (i < pushed.size() && j < popped.size()) {
            stk.push(pushed[i++]);
            while (!stk.empty() && popped[j] == stk.top()) {
                stk.pop();
                j++;
            }
        }
        return stk.empty();
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "testcases.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(validateStackSequences)

    exc.run();
}