#include <GP/GP_macro.h>
#include "header.h"
#include <algorithm>

using namespace std;

class LRUCache {
public:
    /** initialize your data structure here. */
    using pair_list = list<pair<int,int>>;
    pair_list m_list;
    unordered_map<int, pair_list::iterator> m_map;
    int m_capacity = 0;


    explicit LRUCache() {
    }

    void set_capacity(int capacity)
    {
        m_capacity = capacity;
    }

    int get(int key) {
        if(m_map.count(key) == 0) return -1;

        auto pre_iter = m_map[key];
        auto value = pre_iter->second;

        m_list.erase(pre_iter);
        m_list.emplace_back(key, value);
        m_map[key] = --m_list.end();

        return value;
    }

    void put(int key, int value) {
        if(m_map.count(key) == 0)
        {
            if(m_list.size() >= m_capacity)
            {
                m_map.erase(m_list.begin()->first);
                m_list.erase(m_list.begin());
            }

            m_list.emplace_back(key, value);
            m_map[key] = --m_list.end();
        }
        else
        {
            auto pre_iter = m_map[key];
            m_list.erase(pre_iter);
            m_list.emplace_back(key, value);
            m_map[key] = --m_list.end();
        }
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &LRUCache::func);

int main() {
    string input_path = STRINGIFY(INPUT_DIR) "lc-146.txt";
    Excecutor<LRUCache, false> exc(input_path);
    exc.instance = exc.createInstance<void>();
    REGISTER(set_capacity)
    REGISTER(get)
    REGISTER(put)

    exc.run();

    // inputs
    // ["MyCircularDeque","insertLast","insertLast","insertFront","insertFront","getRear","isFull","deleteLast","insertFront","getFront"]
    // [[3],[1],[2],[3],[4],[],[],[],[4],[]]
}