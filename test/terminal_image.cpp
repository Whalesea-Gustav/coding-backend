#include <stdio.h>

int main()
{
    printf("\033[2J"); //清屏
    printf("\033[0;0H"); //定位光标到0行0列
    printf("\033[32m"); //设置颜色为绿色
    printf("  *  \n");
    printf(" *** \n");
    printf("*****\n");
    printf(" *** \n");
    printf("  *  \n");
    printf("\033[0m"); //恢复默认颜色


    return 0;
}