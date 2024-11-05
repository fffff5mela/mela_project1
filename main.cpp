#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "user.h"

void loading()
{
    printf("\n");
    int i = 0;
    char buf[102];
    memset(buf, '\0', sizeof(buf));
    const char* lable = "|/-\\";
    while (i <= 100)
    {
        printf("[%-101s][%d%%][%c]\r", buf, i, lable[i % 4]);
        fflush(stdout);
        buf[i] = '=';
        i++;
        Sleep(25);
    }
    Sleep(200);
    printf("\n加载完成!\n");
    return;
}

int main()
{
    loading();
    menu();
    
    return 0;
}
