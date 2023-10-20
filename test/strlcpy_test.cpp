 #include <bits/stdc++.h>

using namespace std;

size_t strlcpy(char *dst, const char *src, size_t siz) {
    char *d = dst;
    const char *s = src;
    size_t n = siz;
    if (n != 0 && n-1 != 0)
    {
        do {
            if((*d++ = *s++) == '\0')
                break;
        } while (--n != 0);
    }

    if(n == 0)
    {
        *d = '\0';
        while(*s++ == '\0')
            ;
    }

    return (s-src-1);
}

int main()
{
    char dst[100];
    //21
    const char * src1 = "dasjflkdsjldsfjlkdsfj";
    //13
    const char * src2 = "skafdkl\0fsdfd";

    cout << strlcpy(dst, src2, 13) << endl;

    return 0;
}