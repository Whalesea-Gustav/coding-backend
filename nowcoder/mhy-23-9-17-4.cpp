#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

set<char> prims = {'a', 'e', 'i', 'o', 'u'};

int main() {
    int n = 0;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string name;
        cin >> name;

        vector<string> sound;

        for (int j = 0; j < name.size();)
        {
            if(j == name.size()-1)
            {
                sound.push_back(name.substr(j));
            }
            else
            {
                bool c_is_prim = prims.count(name[j]);
                bool n_is_prim = prims.count(name[j+1]);

                if(c_is_prim && n_is_prim && name[j] != name[j+1])
                {
                    sound.push_back(name.substr(j, 2));
                    j = j + 2;
                }
                else if (!c_is_prim && n_is_prim)
                {
                    sound.push_back(name.substr(j, 2));
                    j = j + 2;
                }
                else {
                    sound.push_back(name.substr(j, 1));
                    j = j + 1;
                }
            }
        }

        //判断sound是否回文
        if(sound.size() == 0 || sound.size() == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            int l = 0, r = sound.size() - 1;
            bool bP = true;
            while(l < r)
            {
                if(sound[l] != sound[r])
                {
                    bP = false;
                    break;
                }
                ++l;
                --r;
            }
            if (bP)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        };

    }
}