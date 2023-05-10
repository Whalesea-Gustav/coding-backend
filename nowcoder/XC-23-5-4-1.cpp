#include <GP/GP_macro.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG

#if defined(DEBUG) && defined(GJY_SYSTEM)
#define MY_LOG(x) x
#else
#define MY_LOG(x)
#endif

int main() {
    int n, r;
    cin >> n >> r;

    vector<vector<float>> data(n, vector<float>());

    for (int i = 0; i < n; ++i)
    {
        float x, y, z;
        cin >> x >> y >> z;
        data[i] = {x, y, z};
    }

    float x, y, z;
    cin >> x >> y >> z;
    vector<float> pos = {x, y, z};

    int count = 0;

    auto dis = [](vector<float>& a, vector<float>&b) -> float
    {
        float dx = a[0] - b[0];
        float dy = a[1] - b[1];
        float dz = a[2] - b[2];

        return sqrt(dx * dx + dy * dy + dz * dz);
    };

    for (int i = 0; i < n; ++i)
    {
        if (dis(pos, data[i]) < r)
        {
            count++;
        }
    }

    cout << count << endl;
}
