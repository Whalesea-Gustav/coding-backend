#include <iostream>
#include <vector>

uint32_t murmurHash(uint32_t idx) {
    uint32_t m = 0x5bd1e995;
    uint32_t r = 24;

    uint32_t h = 64684;
    uint32_t k = idx;

    k *= m;
    k ^= (k >> r);
    k *= m;
    h *= m;
    h ^= k;

    return h;
}

using namespace std;

vector<float> unpackUnorm4x8(uint32_t p)
{
    union
    {
        uint32_t in;
        unsigned char out[4];
    } u;

    u.in = p;
    auto res = vector<float>(4,0);

    res[0] = u.out[0] / 255.f;
    res[1] = u.out[1] / 255.f;
    res[2] = u.out[2] / 255.f;
    res[3] = u.out[3] / 255.f;

    return res;
}



int main()
{
    uint32_t p = murmurHash(0);

    cout << p << endl;

    auto vec4 = unpackUnorm4x8(p);

    cout << vec4[0] << " " << vec4[1] << " " << vec4[2] << " " << vec4[3] << endl;

    return 0;
}