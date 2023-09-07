#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    list<pair<int,int>> m_list;
    unordered_map<int, list<pair<int,int>>::iterator> m_map;

    int capacity;
public:
    Solution(int capacity) {
        capacity = capacity;
    }

    int get(int key) {
        if(m_map.count(key) == 0)
        {
            return -1;
        }

        auto key_iter = m_map[key];

        if(key_iter == m_list.begin()) return key_iter->second;

        int value = key_iter->second;

        m_list.insert(m_list.begin(), *key_iter);

        m_list.erase(key_iter);

        m_map[key] = m_list.begin();

        return value;
    }

    void put(int key, int value) {
        if(m_map.count(key) == 0)
        {
            if(m_list.size() < capacity)
            {
                auto iter = m_list.insert(m_list.begin(), {key, value});
                m_map[key] = iter;
            }
            else
            {
                auto end = --m_list.end();
                m_map.erase(end->first);
                m_list.erase(end);

                auto iter = m_list.insert(m_list.begin(), {key, value});
                m_map[key] = iter;
            }
        }
        else
        {
            auto iter = m_map[key];
            m_list.erase(iter);
            iter = m_list.insert(m_list.begin(), {key, value});
            m_map[key] = iter;
        }
    }
};


#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-72.txt";
    Excecutor<Solution, true> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(minDistance_DP_space_optimization)

    exc.run();
}