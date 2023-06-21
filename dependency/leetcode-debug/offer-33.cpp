#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {

        int n = postorder.size();
        if(n <= 1) return true;

        function<bool(int, int)> verify_aux = [&](int start, int end) -> bool
        {
            if(start >= end) return true;

            int root = postorder[end];

            int prev = end;

            for (int i = end-1; i >= start; --i)
            {
                if(root < postorder[i])
                {
                    if(i != prev - 1)
                    {
                        return false;
                    }

                    prev = i;
                }
            }

            return verify_aux(start, prev - 1) && verify_aux(prev, end - 1);
        };

        return verify_aux(0, n-1);
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "offer-33.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(verifyPostorder)

    exc.run();
}