#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {

        vector<pair<int,int>> scores;

        unordered_set<string> pmap = {positive_feedback.begin(), positive_feedback.end()};
        unordered_set<string> nmap = {negative_feedback.begin(), negative_feedback.end()};

        int n = report.size();

        for (int i = 0; i < n; ++i)
        {
            string& cur_report = report[i];
            int cur_id = student_id[i];

            int score = 0;

            istringstream ss(cur_report);

            string token;

            while(std::getline(ss, token, ' '))
            {
                if(pmap.count(token) > 0)
                {
                    score += 3;
                }
                else if (nmap.count(token) > 0)
                {
                    score -= 1;
                }
            }

            scores.emplace_back(score, cur_id);
        }

        sort(scores.begin(), scores.end(), [](pair<int,int>& a, pair<int,int>& b) -> bool
        {
            if(a.first == b.first)
            {
                return a.second < b.second;
            }
            return a.first > b.first;
        });

        vector<int> res;

        for (int i = 0; i < k; ++i)
        {
            res.push_back(scores[i].first);
        }

        return res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-2512.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(topStudents)

    exc.run();
}