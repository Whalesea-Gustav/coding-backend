#include <iostream>

int g_var;
int *g_pointer;
static int g_static;

int main() {
    uint32_t l_var;
    int *l_pointer;
    static int l_static;
    uint32_t * l_pointer2 = new uint32_t;

    std::cout << g_var << std::endl;
    std::cout << g_pointer << std::endl;
    std::cout << g_static << std::endl;
    //std::cout << l_var << std::endl;
    //std::cout << l_pointer << std::endl;
    std::cout << l_static << std::endl;
};