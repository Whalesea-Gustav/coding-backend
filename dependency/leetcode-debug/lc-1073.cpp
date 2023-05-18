#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> addNegabinary(vector<int> &arr1, vector<int> &arr2) {
        int m = arr1.size(), n = arr2.size();

        vector<int> res(max(m, n) + 2, 0);

        int res_sz = res.size();

        int index = 0;
        while (index < max(m, n) + 2) {
            int index1 = m - 1 - index;
            int index2 = n - 1 - index;
            int indexRes = res_sz - 1 - index;

            int arr1_ele = index1 >= 0 ? arr1[index1] : 0;
            int arr2_ele = index2 >= 0 ? arr2[index2] : 0;

            if (index % 2 == 0) {
                int tmp = arr1_ele + arr2_ele + res[indexRes];
                while (tmp >= 2) {
                    tmp -= 2;
                    res[indexRes - 1]++;
                }

                if (tmp < 0) {
                    res[indexRes - 1]--;
                    tmp = 1;
                }

                res[indexRes] = tmp;
            } else {
                int tmp = -1 * (arr1_ele + arr2_ele) + res[indexRes];

                if (tmp == 0) {
                    res[indexRes] = 0;
                } else if (tmp < 0) {
                    while (tmp <= -2) {
                        tmp += 2;
                        res[indexRes - 1]--;
                    }

                    res[indexRes] = -tmp;
                } else {
                    while (tmp >= 2) {
                        tmp -= 2;
                        res[indexRes - 1]++;
                    }

                    res[indexRes - 1]++;
                    res[indexRes] = 1;
                }
            }

            index++;
        };

        while (res[0] == 0 && res.size() >= 2) {
            res = {res.begin() + 1, res.end()};
        }

        return res;
    }

    //分析领悟进位规则
    vector<int> addNegabinary_pro(vector<int> &arr1, vector<int> &arr2) {
        int i = arr1.size() - 1, j = arr2.size() - 1;
        vector<int> ans;
        for (int c = 0; i >= 0 || j >= 0 || c; --i, --j) {
            int a = i < 0 ? 0 : arr1[i];
            int b = j < 0 ? 0 : arr2[j];
            int x = a + b + c;
            c = 0;
            if (x >= 2) {
                x -= 2;
                c -= 1;
            } else if (x == -1) {
                x = 1;
                c += 1;
            }
            ans.push_back(x);
        }
        while (ans.size() > 1 && ans.back() == 0) {
            ans.pop_back();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-1073.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(addNegabinary)

    exc.run();
}