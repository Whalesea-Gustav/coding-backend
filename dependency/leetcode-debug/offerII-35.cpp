#include <GP/GP_macro.h>
#include "header.h"

#include <bits/stdc++.h>

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        size_t operator()(pair<int, int> const & t) const
        {
            size_t h1 = hash<int>()(t.first);
            size_t h2 = hash<int>{}(t.second);
            return h1 ^ (h2 << 1);
        }
    };
}

using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:

    Node* copyRandomList(Node* head) {

        if(head == nullptr) return nullptr;

        unordered_map<Node*, Node*> new_map;

        Node* cur = head;

        while(cur)
        {
            Node* cur_new = new Node(cur->val);
            new_map[cur] = cur_new;

            cur = cur->next;
        }

        cur = head;
        while(cur)
        {
            Node* cur_new = new_map[cur];
            if(cur->next != nullptr)
            {
                cur_new->next = new_map[cur->next];
            }
            else
            {
                cur_new->next = nullptr;
            }

            if(cur->random != nullptr)
            {
                cur_new->random = new_map[cur->random];
            }
            else
            {
                cur_new->random == nullptr;
            }

            cur = cur->next;
        }

        return new_map[head];
    }

    Node* copyRandomListInPlace(Node* head) {

        if(head == nullptr) return nullptr;

        Node* head_new;

        Node* cur = head;
        Node* next;

        bool first = true;

        Node* pre_new;

        while(cur)
        {
            Node* cur_new = new Node(cur->val);

            cur_new->random = cur->random;

            if(first)
            {
                head_new = cur_new;
                first = false;
            }
            else
            {
                pre_new->next = cur_new;
            }

            next = cur->next;

            cur->next = cur_new;

            cur = next;
            pre_new = cur_new;
        }

        cur = head_new;

        while(cur)
        {
            if(cur->random != nullptr)
            {
                cur->random = cur->random->next;
            }

            cur = cur->next;
        }

        return head_new;
    }

    Node* copyRandomListInPlaceRecovery(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        Node* headNew = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* nodeNew = node->next;
            node->next = node->next->next;
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
        }
        return headNew;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    Node* n1 = new Node(7);
    Node* n2 = new Node(13);
    Node* n3 = new Node(11);
    Node* n4 = new Node(10);
    Node* n5 = new Node(1);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n1->random = nullptr;
    n2->random = n1;
    n3->random = n5;
    n4->random = n3;
    n5->random = n1;

    Solution sol;

    auto test = sol.copyRandomListInPlace(n1);
}