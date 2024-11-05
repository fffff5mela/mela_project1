#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>
#include "struct.h"

//===============================医生端===============================
void diagnose(char doc_id[]);                 //医生办理就诊
void doc_ModiFile(char doc_id[]);             //医生查看与修改个人信息
void doc_menu(char doc_id[]);                 //医生菜单
void doc_pla();                               //医生端入口
void find_pat();                              //医生查找患者信息
void login_doc();                             //医生端登录
void register_doc();                          //医生注册
void modify_rec(char pat_id[], char doc_id[]);//医生修改就诊记录

//===============================患者端===============================
void login_pat();                             //患者端登录
void pat_ModiFile(char pat_id[]);             //患者查看与修改个人信息
void pat_appo();                              //患者办理挂号
void pat_menu(char pat_id[]);                 //患者菜单
void pat_outpat_menu(char pat_id[]);          //患者就诊菜单
void pat_pla();                               //患者端入口
void pay(char pat_id[]);                      //患者办理缴费
void payment_mag(char pat_id[]);              //患者缴费管理
void register_pat();                          //患者注册

//===============================管理员端===============================
void login_man();                             //管理员端登录
void man_menu(char doc_id[]);                 //管理员端菜单与功能
void man_pla();                               //管理员端入口
void register_man();                          //管理员注册

//===============================其他功能===============================
void loading();
void menu();
int* strToArr(const char* str, int* len);     //将字符串数组转换为整数数组
char* arrToStr(int* arr, int len);            //整数数组转换为字符串数组
bool check_date(int y, int m, int d);         //判断日期的合法性
int check_year(int y);                        //判断是否是闰年
void reverse(char* str);                      //反转字符串


int month[] = {0,31,30,28,31,30,31,30,31,31,30,31,30,31};
int check_year(int y)
{
    return (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0));
}
bool check_date(int y, int m, int d) {
    int real_day = month[m] + check_year(y);
    return (d > 0 && d <= real_day);
}

//患者修改自己的个人信息
void pat_ModiFile(char pat_id[]) {      // 修改文件中的记录
    char xz[8];
    system("cls");
    printf("\n\n                    0--返回上一级");
    printf("\n\n                    1--编辑个人信息");

    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    switch (xz[0]) {
    case '0': return;
    case '1': {      // 按学号修改学生基本信息
        int find, repeat;    long pos;    char xz[8], ch[30], num[10];    FILE* fp;
        Patient t, x;      // 定义学生表的结构体变量t, x
        if ((fp = fopen("patient_use.dat", "r+b")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Patient data file!\n");
            system("pause"); break;
        }
        system("cls");
        find = 0;
        rewind(fp);    // 复位到学生文件头
        pos = ftell(fp);  // 保留要读取的学生记录在学生文件中的位移量，以便重新定位该记录进行更新
        fread(&t, sizeof(Patient), 1, fp);   // 从学生文件中读取一个学生记录

        while (!feof(fp)) {  // 需要在学生文件中找到学号num的学生记录，找到后再进行修改
            if (!feof(fp) && strcmp(t.pat_id, pat_id) == 0) {
                // 如果读取的学生记录是给定学号num的学生记录，即找到了需要修改的学生记录
                find = 1;    break;    // 结束查找
            }
            pos = ftell(fp);  // 保留要读取的学生记录在学生文件中的位移量，以便重新定位该记录进行更新
            fread(&t, sizeof(Patient), 1, fp);   // 从学生文件中读取一个学生记录
        }

        if (find) {    // 如果找到了给定学号num的学生记录，则进行修改
        F11: system("cls");
            // 在屏幕上显示该学生记录的原来值
            printf("\n\n==================================================");
            printf("\n 患者就诊卡号 : %-s", t.pat_id);
            printf("\n 密码 : %-s", t.pwd);
            printf("\n 姓名 : %-s", t.name);
            printf("\n 性别 : %-c", t.sex);
            printf("\n 电话号码 : %-s", t.phone);
            printf("\n 年龄 : %-s", t.age);
            printf("\n 余额 : %-s", t.balance);
            
            printf("\n===================================================");

            do {
                printf("\n\n 请问是否需要修改你的个人信息？（y/n）");
                gets_s(ch);
            } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
            if (ch[0] != 'y' && ch[0] != 'Y') {
                system("cls");
                fclose(fp);
                break;
            }

        F1:    printf("\n\n 请输入以下需要修改的信息：\n");
            printf(" 密码 : ");    gets_s(ch);    // 继续修改学生的其他成员
            if (strlen(ch) > 0) strcpy(t.pwd, ch);  // 如果输入了新的值，则更新学生结构体变量t的相应成员值
            printf(" 姓名 : ");    gets_s(ch);    // 继续修改学生的其他成员
            if (strlen(ch) > 0) strcpy(t.name, ch);  // 如果输入了新的值，则更新学生结构体变量t的相应成员值
            printf(" 性别 : ");    gets_s(ch);
            while (ch[0] != 'f' && ch[0] != 'm')
            {
                printf(" 性别输入错误！请重新输入:");
                gets_s(ch);
            }
            t.sex = ch[0];
            printf(" 电话号码 :");    gets_s(ch);
            while (strlen(ch) != 11)
            {
                printf(" 电话号码格式输入错误！请重新输入:");
                gets_s(ch);
            }
            strcpy(t.phone, ch);
            printf(" 年龄 :");    gets_s(ch);
            if (strlen(ch) > 0) strcpy(t.age, ch);
            //病人不能修改自己的余额和病名
            printf("               操作成功！              ");
            Sleep(500);
            
            fseek(fp, pos, SEEK_SET);    // 在学生文件中定位正在修改的学生记录
            fwrite(&t, sizeof(Patient), 1, fp);  // 用学生结构体变量t更新学生文件中已定位的学生记录内容
        }
        else printf("\n\n\n\t\tNo find record.\n");
        system("cls");
        fclose(fp);
        break;
    }
    }
}

void pat_find_appo(char pat_id[])
{
    char xz[8];
    system("cls");
    printf("\n\n================挂号记录查找================");
    printf("\n\n 0--返回上一级");
    printf("\n\n 1--查找挂号记录");

    printf("\n\n 请选择下一步操作： (0, 1):  ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    system("cls");
    switch (xz[0]) {
    case '0': return;
        int find;    char ch[30], num[10];    FILE* fp, * fpIdx;
    case '1':
    {
        Medical_record t;      // 定义学生表的结构体变量t

        if ((fp = fopen("Medical_record.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Medical_record data file!\n");
            system("pause");
            break;
        }

        find = 0;
        rewind(fp);    // 复位到学生文件头
        fread(&t, sizeof(Medical_record), 1, fp);   // 从学生文件中读取一个学生记录
        while (!feof(fp)) {    // 在学生文件中顺序查找学号num的学生记录，找到后再显示
            if (strcmp(t.pat_id, pat_id) == 0) {   // 如果在学生文件中找到了给定学号num的学生记录
                find = 1;   
                // 在屏幕上显示该学生记录
                printf("\n\n===================================================");
                printf("\n 患者就诊卡号 : %-s", t.pat_id);
                printf("\n 患者姓名 : %-s", t.pat_name);
                printf("\n 患病名称 : %-s", t.disease);
                printf("\n 医生姓名 : %-s", t.doc_name);
                printf("\n 所属科室 : %-s", t.department);
                printf("\n 用药名称 : %-s", t.medicine);
                printf("\n 消费金额 : %-s", t.spend);
                printf("\n 就诊日期 ：%4d-%2d-%2d  ", t.time.year, t.time.month, t.time.day);
                printf("\n 就诊状态 : %-s ", t.state);
                printf("\n====================================================");

                do {
                    printf("\n\n请选择是否继续查找：(y/n): ");//考虑到一个患者可能挂多个医生的号
                    gets_s(ch);
                } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
                if (ch[0] == 'y' || ch[0] == 'Y') continue;    // 实际上是构成循环
                else {
                    system("cls");
                    fclose(fp);
                    break;
                }
            }
            fread(&t, sizeof(Medical_record), 1, fp);   // 从学生文件中读取一个学生记录
        }

        system("cls");
        if (find==0) {    // 如果没找到
            system("cls");    
            printf("\n\n\t\tNot find record");
        }
       
        break;
    }
        
    system("pause");
    break;
    }
}

void pat_appo()
{     /*记录方式查找*/
    system("cls");
    char xz[8];
    system("cls");
    printf("\n*******************挂号管理**************************");
    printf("\n====================================================");
    printf("\n\n  0.返回上一级");
    printf("\n\n  1.查找科室医生");
    printf("\n\n  2.直接办理挂号");
    printf("\n\n  请选择下一步操作：(0, 1, 2) ");

    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1' && xz[0] != '2');
    system("cls");
    switch (xz[0]) {
    case '0': return;
    case '1':
    {
        // 按科室查找医生基本信息
        int find, flag = 0, len = 0, start, end, mid;    char ch[30], num[10];    FILE* fp, * fpIdx;
        Doctor t;      // 定义学生表的结构体变量t

        if ((fp = fopen("doctor_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open STUDENT data file!\n");
            system("pause");
            break;
        }

        printf("\n\n请输入就诊科室名称：  ");
        gets_s(num);    // 输入需修改学生记录的学号到字符数组num
        find = 0;
        printf("\n\n=======================================================");
        printf("\n\n 姓名            性别          所属科室");
        rewind(fp);    // 复位到学生文件头
        fread(&t, sizeof(Doctor), 1, fp);   // 从学生文件中读取一个学生记录
        while (!feof(fp)) {    // 在学生文件中顺序查找学号num的学生记录，找到后再显示
            if (strcmp(t.department, num) == 0) {   // 如果在学生文件中找到了给定学号num的学生记录
                printf("\n %-s         %-c           %-s    ", t.name, t.sex, t.department);
                find = 1;
            }
            fread(&t, sizeof(Doctor), 1, fp);   // 从学生文件中读取一个学生记录
        }
        printf("\n\n=======================================================\n");
        system("pause");
        system("cls");
        if (find == 0) {
            printf(" 没有找到相关科室的记录！");
        }

        do {
            printf("\n\n请选择是否办理挂号：(y/n): ");
            gets_s(ch);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // 实际上是构成循环
        else {
            system("cls");
            fclose(fp);
        }
        break;
    }

    case '2':
    {
        printf("\n*******************办理挂号**************************");
        printf("\n====================================================");
        printf("\n\n 0.返回上一级");
        printf("\n\n 1.办理挂号");
        printf("\n\n 请选择下一步操作： (0, 1) ");
        do {
            gets_s(xz);
        } while (xz[0] != '0' && xz[0] != '1');

        system("cls");
        switch (xz[0]) {
        case '0': return;
        F1: case '1': {
            char ch[30], tem[30];
            int find1,find2;
            FILE* fp, * fp_r,* fp_d;
            Patient x; // 定义学生表的结构体变量t, x
            Doctor d;
            Medical_record t;

            if ((fp = fopen("patient_use.dat", "a+b")) == 0)
            {
                printf("\n\nCannot open Patient data file!\n");
                system("pause");
                break;
            }

            if ((fp_r = fopen("Medical_record.dat", "a+b")) == 0)
            {
                printf("\n\nCannot open Medical_record data file!\n");
                system("pause");
                break;
            }

            if ((fp_d = fopen("doctor_use.dat", "a+b")) == 0)
            {
                printf("\n\nCannot open Doctor data file!\n");
                system("pause");
                break;
            }

        F2:
            printf("\n 请输入病人就诊卡号: ");
            gets_s(ch); // 输入一个学号到字符数组ch
            find1 = 0;
            rewind(fp);                       // 复位到文件头
            fread(&x, sizeof(Patient), 1, fp); // 从医生文件中读取一个医生记录，并把它放到结构体x内
            while (!feof(fp))
            { // 判断学号ch的医生记录是否已经输入过，输入过则不能再输入
                if (strcmp(x.pat_id, ch) == 0)
                { // 如果在医生文件中找到了工号ch的学生记录，则结束查找
                    find1 = 1;
                    break; // 结束查找
                }
                fread(&x, sizeof(Patient), 1, fp); // 从医生文件中读取一个医生记录，并把它放到结构体x内
            }
            if (find1 == 0)
            { // 在医生文件中已经存在该学号的学生记录，选择是否输入下一个医生
                printf("\n\n\n\t 账号 %s 不存在! 请问是否重新输入? (y/n)  ", ch);
                do
                {
                    gets_s(ch);
                } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
                if (ch[0] == 'y' || ch[0] == 'Y')
                    goto F2; // 实际上是构成循环
                else
                {
                    fclose(fp);
                    system("cls");
                    break;
                }
            }
            strcpy(t.pat_id, ch);

            printf("\n 患者姓名 : ");
            gets_s(t.pat_name);

         F3:printf("\n 就诊医生姓名 : ");
            gets_s(ch);

            find2 = 0;
            rewind(fp_d);                       // 复位到文件头
            fread(&d, sizeof(Doctor), 1, fp_d); // 从医生文件中读取一个医生记录，并把它放到结构体x内
            while (!feof(fp_d))
            { // 判断学号ch的医生记录是否已经输入过，输入过则不能再输入
                if (strcmp(d.name, ch) == 0)
                { // 如果在医生文件中找到了工号ch的学生记录，则结束查找
                    find2 = 1;
                    strcpy(t.doc_id, d.doc_id);
                    break; // 结束查找
                }
                fread(&d, sizeof(Doctor), 1, fp_d); // 从医生文件中读取一个医生记录，并把它放到结构体x内
            }
            if (find2 == 0)
            { // 在医生文件中已经存在该学号的学生记录，选择是否输入下一个医生
                printf("\n\n\n\t  %s 医生不存在! 请问是否重新输入? (y/n)  ", ch);
                do
                {
                    gets_s(ch);
                } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
                if (ch[0] == 'y' || ch[0] == 'Y')
                    goto F3; // 实际上是构成循环
                else
                {
                    fclose(fp);
                    system("cls");
                    break;
                }
            }
            strcpy(t.doc_name, ch);


            printf("\n 就诊科室 : ");
            gets_s(t.department);

            printf("\n 就诊时间 : 年份:  ");
            gets_s(ch);
            while (atoi(ch) != 2024)
            {
                printf(" 就诊年份输入错误！请重新输入:");
                gets_s(ch);
            }
            t.time.year = atoi(ch);

            printf("            月份: ");
            gets_s(ch);
            while (atoi(ch) > 12 || atoi(ch) < 1)
            {
                printf(" 就诊月份输入错误！请重新输入:");
                gets_s(ch);
            }
            t.time.month = atoi(ch);

            printf("            日期: ");    gets_s(ch);
            while (!check_date(t.time.year, t.time.month,atoi(ch)))
            {
                printf(" 就诊日期输入错误！请重新输入:");
                gets_s(ch);
            }
            t.time.day = atoi(ch);

            strcpy(t.medicine, "暂无详情");
            strcpy(t.spend, "0");
            strcpy(t.state, "待就诊");
            strcpy(t.disease, "暂无详情");
            t.has_paied = false;
            fwrite(&t, sizeof(Medical_record), 1, fp_r);
            printf("==================================================\n");
            system("pause");
            fclose(fp);
            fclose(fp_r);
            system("cls");
            break;
        }
        }
    }
    }
}

void pat_outpat_menu(char pat_id[])
{
    system("cls");
    while (1) {
        char xz[8];
        printf("\n*******************就诊管理**************************");
        printf("\n====================================================\n");
        printf("\n 0. 退出页面\n");
        printf("\n 1. 查看就诊信息\n");
        printf("\n 2. 办理挂号\n");
        
        printf("\n 请选择输入选择操作：（0，1，2）\n");
        gets_s(xz);
        //getchar();  // 捕捉换行符
        switch (xz[0]) {
        case '0':
            return;
            break;
        case '1':
            pat_find_appo(pat_id);
            break;
        case '2':
            pat_appo();
            break;
        
        default:
            printf("输入非法请重新输入！\n");
            Sleep(500);
            system("cls");
        }
    }

}

void pat_find_bal(char pat_id[])
{
    char xz[8];
    system("cls");
    printf("\n\n================余额查询================");
    printf("\n\n 0--返回上一级");
    printf("\n\n 1--查找余额");

    printf("\n\n 请选择下一步操作： (0, 1):  ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    system("cls");
    switch (xz[0]) {
    case '0': return;
        int find;    char ch[30], num[10];    FILE* fp, * fpIdx;
    case '1':
    {
        Patient t;    

        if ((fp = fopen("patient_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Patient data file!\n");
            system("pause");
            break;
        }
     
    F1:
        find = 0;
        rewind(fp);    
        fread(&t, sizeof(Patient), 1, fp); 
        while (!feof(fp)) {   
            if (strcmp(t.pat_id, pat_id) == 0) {   
                find = 1;    break;    
            }
            fread(&t, sizeof(Patient), 1, fp);   
        }

        system("cls");
        if (find) {    // 如果找到了，
            // 在屏幕上显示
            printf("\n===================================================");
            
            printf("\n 账户余额 : %-s", t.balance);
            
            printf("\n====================================================\n");
        }
        else { system("cls");    printf("\n\n\t\tNot find record"); }
        break;
    }
    do {
        printf("\n\n请选择是否继续操作：(y/n): ");
        gets_s(ch);
    } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
    if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // 实际上是构成循环
    else {
        system("cls");
        fclose(fp);
    }
    system("pause");
    break;
    }
}

// 反转字符串
void reverse(char* str) 
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// 字符串数字转换为整数数组
int* strToArr(const char* str, int* len) {
    *len = strlen(str);
    int* arr = (int*)malloc((*len) * sizeof(int));
    for (int i = 0; i < *len; i++) {
        arr[i] = str[str[i] == '-' ? i + 1 : i] - '0';
    }
    return arr;
}

// 整数数组转换为字符串数字
char* arrToStr(int* arr, int len) {
    char* str = (char*)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) {
        str[i] = (arr[i] < 0) ? '-' : (arr[i] + '0');
    }
    str[len] = '\0';
    return str;
}

// 两个字符串数字相减
char* substract(char* num1, char* num2) {
    int len1, len2;
    int* arr1 = strToArr(num1, &len1);
    int* arr2 = strToArr(num2, &len2);

    // 反转数组，方便从最低位开始计算
    reverse(num1);
    reverse(num2);

    int borrow = 0;
    for (int i = 0; i < len1; i++) {
        if (i < len2) {
            arr1[i] -= borrow + arr2[i];
            if (arr1[i] < 0) {
                arr1[i] += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
        }
        else {
            arr1[i] -= borrow;
            if (arr1[i] < 0) {
                arr1[i] += 10;
            }
        }
    }

    // 处理最高位的负数
    if (arr1[0] < 0) {
        arr1[0] = -arr1[0];
    }

    char* result = arrToStr(arr1, len1);
    free(arr1);
    free(arr2);

    return result;
}


void pay(char pat_id[]) {
    char xz[8];
    system("cls");
    printf("\n\n================办理缴费================");
    printf("\n\n 0--返回上一级");
    printf("\n\n 1--查看消费记录");
    printf("\n\n 2--缴费");
    printf("\n\n 请选择下一步操作： (0, 1, 2):  ");

    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1' && xz[0]!='2');

    system("cls");
    switch (xz[0]) {
    case '0': return;
    int find;    char ch[30], num[10];    FILE* fp, * fp2;
    char needspend[10];
    Medical_record t;      
    case '1':
    {
        if ((fp = fopen("Medical_record.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Medical_record data file!\n");
            system("pause");
            break;
        }

        find = 0;
        rewind(fp);    
        fread(&t, sizeof(Medical_record), 1, fp);  
        while (!feof(fp)) {    
            if (strcmp(t.pat_id, pat_id) == 0 && !t.has_paied) {   
                find = 1;    break;     // 找到了，则结束顺序查找
            }
            fread(&t, sizeof(Medical_record), 1, fp);  
        }

        system("cls");
        if (find) {    // 如果找到了，则显示
            
            printf("\n===================================================");
            printf("\n 本次就诊消费 : %-s", t.spend);
            strcpy(needspend, t.spend);
            printf("\n====================================================");
        }
        else { system("cls");    printf("\n\t\t已缴费！\n"); }
        break;
    }

    do {
        printf("\n\n请选择是否进行缴费：(y/n): ");
        gets_s(ch);
    } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N') );
    if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // 实际上是构成循环
    else {
        system("cls");
        fclose(fp);
    }

 F1:case '2'://缴费
    {
        Patient p;     

        if ((fp2 = fopen("patient_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Patient data file!\n");
            system("pause");
            break;
        }

        find = 0;
        rewind(fp2); 
        fread(&p, sizeof(Patient), 1, fp2);  
        while (!feof(fp2)) {   
            if (strcmp(p.pat_id, pat_id) == 0 ) {  
                find = 1;    
                break;    
            }
            fread(&p, sizeof(Patient), 1, fp2);  
        }

        system("cls");
        if (find) {    
           
            if (atoi(needspend) < atoi(p.balance))
            { 
                strcpy(p.balance, substract( p.balance , needspend));
               
                printf("缴费成功！\n");
                t.has_paied = true;
            }
            else
            {
                printf(" 余额不足无法缴费！\n");
            }
        }
        else { system("cls");    printf("\n\n\t\t没找到该患者的信息！"); }
        fwrite(&p, sizeof(Patient), 1, fp2);  
        
        break;
    }
    fwrite(&t, sizeof(Medical_record), 1, fp);  
    system("pause");
    break;
    }
}

void payment_mag(char pat_id[])
{
    system("cls");
    while (1) {
        char xz[8];
        printf("\n*******************缴费管理************************");
        printf("\n===================================================\n");
        printf("0. 退出页面\n");
        printf("1. 余额查询\n");
        printf("2. 办理缴费\n");
       
        printf("请选择输入选择操作：（0，1，2）\n");
        gets_s(xz);
        //getchar();  // 捕捉换行符
        switch (xz[0]) {
        case '0':
            return;
            break;
        case '1':
            Patient t;      
            int find;    
            char ch[30], num[10];    
            FILE* fp, * fpIdx;

            if ((fp = fopen("patient_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
                printf("\n\nCannot open Patient data file!\n");
                system("pause");
                break;
            }

        F1:
            find = 0;
            rewind(fp);    
            fread(&t, sizeof(Patient), 1, fp);  
            while (!feof(fp)) {    // 在患者文件中顺序查找学号num的患者记录，找到后再显示
                if (strcmp(t.pat_id, pat_id) == 0) {   // 如果在患者文件中找到了给定学号num的患者记录
                    find = 1;    break;     // 找到了，则结束顺序查找
                }
                fread(&t, sizeof(Patient), 1, fp);   // 从患者文件中读取一个患者记录
            }

            system("cls");
            if (find) {    // 如果找到了，则显示该患者信息
                // 在屏幕上显示患者记录
                printf("\n===================================================");
                printf("\n 账户余额 : %-s", t.balance);
                printf("\n====================================================");
            }
            else { system("cls");    printf("\n\n\t\tNot find record"); }
            break;
            
        case '2':
            pay(pat_id);
            break;
        
        default:
            printf("输入非法请重新输入！\n");
            Sleep(500);
            system("cls");
        }
    }
}

void pat_menu(char pat_id[]) 
{
    system("cls");
    while (1) {
        char xz[8];
        printf("患者操作菜单:\n");
        printf("==============================\n");
        printf("0. 退出页面\n");
        printf("1. 个人信息管理\n");
        printf("2. 就诊管理\n");
        printf("3. 缴费管理\n");
        printf("请选择输入选择操作：（0，1，2，3）\n");
        gets_s(xz);
        //getchar();  // 捕捉换行符
        switch (xz[0]) {
        case '0':
            return;
            break;
        case '1':
            pat_ModiFile(pat_id);
            break;
        case '2':
            pat_outpat_menu(pat_id);
            break;
        case '3':
            payment_mag(pat_id);
            break;
        default:
            printf("输入非法请重新输入！\n");
            Sleep(500);
            system("cls");
        }
    }

}

void register_pat()
{
    system("cls");
    printf("\n\t 欢迎来到患者注册界面！");
    //Sleep(1000);

    char ch[30], tem[30];
    int find;
    FILE* fp;
    Patient t, x; // 定义病人表的结构体变量t, x
    if ((fp = fopen("patient_use.dat", "a+b")) == 0)
    {
        printf("\n\nCannot open Patient data file!\n");
        system("pause");
        return;
    }

F1:
    system("cls");
    printf("*******************患者注册**************************");
    printf("\n==================================================");
    printf("\n 请输入患者就诊卡号 : ");
    getchar();
    gets_s(ch); // 输入一个卡号到字符数组ch
    find = 0;
    rewind(fp);                       // 复位到文件头
    fread(&x, sizeof(Patient), 1, fp); // 从病人文件中读取一个病人记录，并把它放到结构体x内
    while (!feof(fp))
    { // 判断学号ch的病人记录是否已经输入过，输入过则不能再输入
        if (strcmp(x.pat_id, ch) == 0)
        { // 如果在病人文件中找到了卡号ch的病人记录，则结束查找
            find = 1;
            break; // 结束查找
        }
        fread(&x, sizeof(Patient), 1, fp); // 从医生文件中读取一个医生记录，并把它放到结构体x内
    }
    if (find)
    { // 在病人文件中已经存在该卡号的病人记录，选择是否输入下一个病人
        printf("\n\n\n\t 账号 %s 已存在! 请问是否重新输入? (y/n)  ", ch);
        do
        {
            gets_s(ch);
        } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
        if (ch[0] == 'y' || ch[0] == 'Y')
            goto F1; // 实际上是构成循环
        else
        {
            fclose(fp);
            system("cls");
            menu();
            return;
        }
    }

    strcpy(t.pat_id, ch); // 将学号ch字符串拷贝给病人结构体变量t的病人卡号num
    printf("\n 请输入密码 : ");
    gets_s(t.pwd); // 继续输入该病人的其他成员值
    printf("\n 请确认密码 :");
    gets_s(tem);
    while (strcmp(t.pwd, tem) != 0) {
        printf(" 密码确认错误！请重新输入:");
        gets_s(tem);
    }

    printf("\n 姓名 : ");
    gets_s(t.name);
    printf("\n 性别 : ");
    gets_s(ch);

    while (ch[0] != 'f' && ch[0] != 'm' && ch[0] !='F' &&ch[0]!='M')
    {
        printf(" 性别输入错误！请重新输入:");
        gets_s(ch);
    }
    t.sex = ch[0];

    printf("\n 电话 :");
    gets_s(ch);
    while (strlen(ch) != 11)
    {
        printf(" 电话号码格式输入错误！请重新输入:");
        gets_s(ch);
    }

    strcpy(t.phone, ch);
    printf("\n 年龄 :");
    gets_s(t.age);

    printf("\n 账户余额 : ");
    gets_s(t.balance);

    
    fwrite(&t, sizeof(Patient), 1, fp); // 向病人文件中追加一个学生记录
    printf("==================================================");
    printf("\n\n\n\t\t 注册成功！");
    system("pause");
    fclose(fp);
    system("cls");
    menu();
    return;
}

void login_pat()
{
    Patient a, b;//定义结构体The_users别名
    char ch[3];
    FILE* fp;
    system("cls");
    printf(" \n欢迎来到登录界面！\n\n");
    char xz[8];
    system("cls");
    printf("\n\n                    0--返回上一级");
    printf("\n\n                    1--病人登录");
    printf("\n\n                    请选择下一步操作： (0, 1):  ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    system("cls");
    switch (xz[0]) {
    case '0': return;
    case '1': {
        if ((fp = fopen("patient_use.dat", "r")) == 0)
        {
            printf("\n\nCannot open Patient data file!\n");
            system("pause");
            return;
        }

        fread(&b, sizeof(Patient), 1, fp); //读入一个结构体字符块 写入b

    F2: system("cls");
        printf(" \n欢迎来到登录界面！\n\n");
        printf(" 请输入账号：");
        scanf("%s", &a.pat_id);

        while (1)
        {
            if (strcmp(a.pat_id, b.pat_id) == 0)         //如果有此用户名
            {
                break;
            }
            else
            {
                if (!feof(fp))  //如果文件没有读完                            
                {
                    fread(&b, sizeof(Patient), 1, fp);
                }
                else
                {
                    printf("\n\n\n\t 账号不存在! 请问是否重新输入? (y/n)  ");
                    do
                    {
                        gets_s(ch);
                    } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
                    if (ch[0] == 'y' || ch[0] == 'Y')
                        goto F2; // 实际上是构成循环
                    else
                    {
                        fclose(fp);
                        system("pause");
                        system("cls");
                        menu();
                        break;
                    }
                }
            }
        }
        printf(" 请输入密码：");
        scanf("%s", &a.pwd);
        do {

            if (strcmp(a.pwd, b.pwd) == 0)            /*如果密码匹配*/
            {
                fclose(fp);
                printf("\n 登录成功,欢迎使用!\n");
                Sleep(500);
                system("cls");
                pat_menu(a.pat_id);
                return;
            }
            else
            {
                printf("     密码不正确!请重新输入密码\n");
                scanf("%s", &a.pwd);
            }
        } while (strcmp(a.pwd, b.pwd) == 0);
    }
    }
}

void pat_pla()
   {
        system("cls");
    F2: printf("\n 请选择病人进入方式：\n");
        printf("=========================================\n");
        printf(" 1.病人注册            \n 2.病人登录\n\n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            register_pat();
            break;
        case 2:
            login_pat();
            break;

        default:
            printf("   输入格式错误，请重新输入！\n");
            goto F2;
            break;
        }
    }


//======================================医生操作===========================================
void doc_ModiFile(char doc_id[]) {      // 修改文件中的记录
    char xz[8];
    system("cls");
    printf("\n\n                    0--返回上一级");
    printf("\n\n                    1--编辑个人信息\n");

    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');

    switch (xz[0]) {
    case '0': return;
    case '1': {      
        //printf("进入....");
        int find, repeat;    long pos;    char xz[8], ch[30], num[10];    FILE* fp;
        Doctor t, x;      // 定义学生表的结构体变量t, x
        if ((fp = fopen("doctor_use.dat", "r+b")) == 0) {    // 由于\用于转义字符，因此\\才表示\                                                                                                  printf("\n\nCannot open STUDENT data file!\n");
            system("pause"); 
            break;
        }
        system("cls");

        find = 0;
        rewind(fp);    // 复位到医生文件头
        pos = ftell(fp);  // 保留要读取的医生记录在医生文件中的位移量，以便重新定位该记录进行更新

        fread(&t, sizeof(Doctor), 1, fp);   // 从医生文件中读取一个医生记录
        while (!feof(fp)) {  // 需要在医生文件中找到学号num的医生记录，找到后再进行修改
            if ( strcmp(t.doc_id, doc_id) == 0) {
                // 如果读取的医生记录是给定学号num的医生记录，即找到了需要修改的医生记录
                find = 1;    break;    // 结束查找
            }
            pos = ftell(fp);  // 保留要读取的医生记录在医生文件中的位移量，以便重新定位该记录进行更新
            fread(&t, sizeof(Doctor), 1, fp);   // 从医生文件中读取一个医生记录
        }

        if (find) {    // 如果找到了给定医生记录，则进行修改
        F11: system("cls");
            // 在屏幕上显示该医生记录的原来值
            printf("\n\n==================================================");
            printf("\n 医生工号 :      %-s", t.doc_id);
            printf("\n 密码 :     %-s", t.pwd);
            printf("\n 姓名 :     %-s", t.name);
            printf("\n 性别 :      %-c", t.sex);
            printf("\n 电话号码 :    %-s", t.phone);
            printf("\n 年龄 :    %-s", t.age);
            printf("\n 所属科室 :    %-s", t.department);
            printf("\n==================================================");

            do {
                printf("\n\n 请问是否需要修改你的个人信息？（y/n）");
                gets_s(ch);
            } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));

            if (ch[0] != 'y' && ch[0] != 'Y') {
                system("cls");
                fclose(fp);
                break;
            }
            
        F1: printf("\n 请输入以下需要修改的信息：\n");
            printf(" 密码 : ");    gets_s(ch);    // 继续修改医生的其他成员
            if (strlen(ch) > 0) strcpy(t.pwd, ch);  // 如果输入了新的值，则更新医生结构体变量t的相应成员值
            printf(" 姓名 : ");    gets_s(ch);    // 继续修改医生的其他成员
            if (strlen(ch) > 0) strcpy(t.name, ch);  // 如果输入了新的值，则更新医生结构体变量t的相应成员值
            printf(" 性别 (f/F,m/M) :");    gets_s(ch);
            while (ch[0] != 'f' && ch[0] != 'm' && ch[0] != 'F' && ch[0] != 'M')
            {
                printf(" 性别输入错误！请重新输入:");
                gets_s(ch);
            }
            t.sex = ch[0];
            printf(" 电话号码 (11位）:");    gets_s(ch);
            while (strlen(ch) != 11)
            {
                printf(" 电话号码格式输入错误！请重新输入:");
                gets_s(ch);
            }
            strcpy(t.phone, ch);
            printf(" 年龄 : ");    gets_s(ch);
            if (strlen(ch) > 0) strcpy(t.age, ch);
            printf(" 所属科室 : ");    gets_s(ch);
            if (strlen(ch) > 0) strcpy(t.department, ch);

            printf("               操作成功！              ");
            Sleep(1000);
            fseek(fp, pos, SEEK_SET);    // 在医生文件中定位正在修改的医生记录
            fwrite(&t, sizeof(Doctor), 1, fp);  // 用医生结构体变量t更新医生文件中已定位的医生记录内容
        }
        else printf("\n\n\n\t\tNo find record.\n");
        fclose(fp);
        break;
    }
    }
}

void find_pat()
{     /*记录方式查找*/
    char xz[8];
    system("cls");
    printf("\n\n================患者信息查找================");
    printf("\n\n 0--返回上一级");
    printf("\n\n 1--查找患者信息");

    printf("\n\n 请选择下一步操作： (0, 1):  ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1' );
    system("cls");
    switch (xz[0]) {
    case '0': return;
    case '1':
    {
       
        int find, flag = 0, len = 0, start, end, mid;    char ch[30], num[10];    FILE* fp, * fpIdx;
        Patient t;      

        if ((fp = fopen("patient_use.dat", "rb")) == 0) {  
            printf("\n\nCannot open STUDENT data file!\n");
            system("pause"); 
            break;
        }

    F1: int choice;
        printf("请选择使用 :1.病人就诊卡号查找 or 2.姓名查找  ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1: 
        {
            printf("\n\n请输入病人就诊卡号：  ");
            gets_s(num);    // 输入需修改患者记录的学号到字符数组num
            find = 0;
            // 不存在患者索引文件时，则在患者文件中进行顺序扫描查找
            rewind(fp);    // 复位到患者文件头
            fread(&t, sizeof(Patient), 1, fp);   // 从患者文件中读取一个患者记录
            while (!feof(fp)) {    // 在患者文件中顺序查找学号num的患者记录，找到后再显示
                if (strcmp(t.pat_id, num) == 0) {   // 如果在患者文件中找到了给定学号num的患者记录
                    find = 1;    break;     // 找到了，则结束顺序查找
                }
                fread(&t, sizeof(Patient), 1, fp);   // 从患者文件中读取一个患者记录
            }
            system("cls");
            if (find) {    // 如果找到了，则显示该患者信息
                // 在屏幕上显示该患者记录
                printf("\n\n===================================================");
                printf("\n 就诊卡号 : %-s", t.pat_id);
                printf("\n 姓名 : %-s", t.name);
                printf("\n 性别 : %-c", t.sex);
                printf("\n 年龄 ：%-s", t.age);
                printf("\n 手机号码 : %-s", t.phone);
                printf("\n 账户余额 : %-s", t.balance);
                
                printf("\n====================================================");
            }
            else { system("cls");    printf("\n\n\t\tNot find record"); }
            break;
        }

        case 2:
        {
            printf("\n\n请输入病人姓名:  ");

            gets_s(num);    // 输入需修改患者记录的学号到字符数组num
            find = 0;
            // 不存在患者索引文件时，则在患者文件中进行顺序扫描查找
            rewind(fp);    // 复位到患者文件头
            fread(&t, sizeof(Patient), 1, fp);   // 从患者文件中读取一个患者记录
            while (!feof(fp)) {    // 在患者文件中顺序查找学号num的患者记录，找到后再显示
                if (strcmp(t.name, num) == 0) {   // 如果在患者文件中找到了给定学号num的患者记录
                    find = 1;    break;     // 找到了，则结束顺序查找
                }
                fread(&t, sizeof(Patient), 1, fp);   // 从患者文件中读取一个患者记录
            }


            system("cls");
            if (find) {    // 如果找到了，则显示该患者信息
                // 在屏幕上显示该患者记录
                printf("\n\n===================================================");
                printf("\n num :     %-s", t.pat_id);
                printf("\n name :    %-s", t.name);
                printf("\n sex :     %-c", t.sex);
                printf("\n phone :   %-s", t.phone);
                printf("\n balance :  %-s", t.balance);
                
                printf("\n=====================================================");
            }
            else { system("cls");    printf("\n\n\t\tNot find record"); }

            break;
        }
        }
        do {
            printf("\n\n请选择是否继续操作：(y/n): ");
            gets_s(ch);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // 实际上是构成循环
        else {
            system("cls");
            fclose(fp);
        }
        break;
    }
    }
}


void modify_rec(char pat_id[],char doc_id[])
{
    int find, repeat;    long pos;    char xz[8], ch[30], num[10];    FILE* fp;
    Medical_record t, x;     
    if ((fp = fopen("Medical_record.dat", "r+b")) == 0) {    // 由于\用于转义字符，因此\\才表示
        printf("\n\nCannot open Medical_record data file!\n");
        system("pause");
    }
   system("cls");
    
    find = 0;
    rewind(fp);    // 复位到文件头
    pos = ftell(fp); 
    fread(&t, sizeof(Medical_record), 1, fp);   

    while (!feof(fp)) { 
        if (strcmp(t.doc_id, doc_id) && strcmp(t.pat_id, pat_id) == 0) {
            
            find = 1;    break;    // 结束查找
        }
        pos = ftell(fp); 
        fread(&t, sizeof(Medical_record), 1, fp);   
    }

    if (find)
    {   
    F1: 
        printf("\n 就诊明细：");
        printf("\n==================================================");
        printf("\n 患病名称 : ");    gets_s(ch);   
        if (strlen(ch) > 0) strcpy(t.disease, ch); 
        printf("\n 治疗药物名称 : ");    gets_s(ch);
        if (strlen(ch) > 0) strcpy(t.medicine, ch);
        printf("\n 消费金额 : ");    gets_s(ch);
        if (strlen(ch) > 0) strcpy(t.spend, ch);
        strcpy(t.state, "已就诊");
        printf("==================================================");
        fseek(fp, pos, SEEK_SET);
        fwrite(&t, sizeof(Medical_record), 1, fp); 
    }
    else printf("\n\n\n\t\t没有找到记录！\n");
    do {
        printf("\n\n\t\t是否需要重新修改？(y/n) ");
        gets_s(ch);
    } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
    if (ch[0] == 'y' || ch[0] == 'Y') goto F1;   
    else fclose(fp);
    
}
void diagnose(char doc_id[]) {
    system("cls");
    char xz[8];
    system("cls");
    printf("\n\n================就诊管理================");
    printf("\n\n 0--返回上一级");
    printf("\n\n 1--办理就诊");

    printf("\n\n 请选择下一步操作： (0, 1)  ");

    int find;    char ch[30], num[10];    FILE* fp, * fpIdx; long pos;

    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    system("cls");
    switch (xz[0]) {
    case '0': return;
        
    case '1':
    {
        Medical_record t;    

        if ((fp = fopen("Medical_record.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示
            printf("\n\nCannot open Patient data file!\n");
            system("pause");
            break;
        }

    F1:
        find = 0;
        rewind(fp);    
        fread(&t, sizeof(Medical_record), 1, fp);  
        while (!feof(fp)) {   
            if (strcmp(t.doc_id, doc_id) == 0) {   
                find = 1;   
                printf("\n\n===================================================");
                printf("\n 患者就诊卡号 : %-s", t.pat_id);
                printf("\n 患者姓名 : %-s", t.pat_name);
                printf("\n 所属科室 : %-s", t.department);
                printf("\n 就诊日期 ：%4d-%2d-%2d  ", t.time.year, t.time.month, t.time.day);
                printf("\n====================================================");

                do {
                    printf("\n\n 请选择是否填写就诊明细：(y/n): ");
                    gets_s(ch);
                } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
                if (ch[0] == 'y' || ch[0] == 'Y') modify_rec(t.pat_id,t.doc_id);    // 实际上是构成循环
                else {
                    system("cls");
                }
            }
            fread(&t, sizeof(Medical_record), 1, fp);  
        }
        system("cls");
        fclose(fp);
        if (find==0) {   
            system("cls");    printf("\n\n\t\tNot find record");
        }
        break;
    }
    system("pause");
    break;
    }
}

void doc_menu(char doc_id[]) {
    
    system("cls");
    while (1) {
        char xz[8];
        printf("医生操作菜单:\n");
        printf("==============================\n");
        printf("0. 退出页面\n");
        printf("1. 个人信息管理\n");
        printf("2. 患者信息管理\n");
        printf("3. 就诊信息管理\n");

        printf("\n请选择下一步操作：(0,1,2,3)");
        gets_s(xz);
        //getchar();  // 捕捉换行符
        switch (xz[0]) {
        case '0':
            return;
            break;
        case '1':
            doc_ModiFile(doc_id);
            break;
        case '2':
            find_pat();
            break;
        case '3':
            diagnose(doc_id);
            break;
        default:
            printf("选择非法，请重新输入！\n");
            Sleep(500);
            system("cls");
        }
    }
}

void register_doc() 
{
    system("cls");
    printf("\n 欢迎来到医生注册界面！");
    Sleep(500);

    char xz[8];
    //system("cls");
    printf("\n*******************医生注册**************************");
    printf("\n====================================================");
    printf("\n\n 0.返回上一级");
    printf("\n\n 1.注册医生账户");
    printf("\n\n 请选择下一步操作： (0, 1) ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1' );

    system("cls");
    switch (xz[0]) {
    case '0': {
        return;
        break;
    }
    case '1': {
        char ch[30], tem[30];
        int find;
        FILE* fp;
        Doctor t, x; // 定义学生表的结构体变量t, x
        if ((fp = fopen("doctor_use.dat", "a+b")) == 0)
        {
            printf("\n\nCannot open Doctor data file!\n");
            system("pause");
            break;
        }

    F1: system("cls");
        //printf("\n 请输入账号 ");
        printf("*******************医生注册**************************");
        printf("\n==================================================");
        printf("\n 请输入医生工号 : ");
        
        gets_s(ch); 
        find = 0;
        rewind(fp);                     
        fread(&x, sizeof(Doctor), 1, fp); // 从医生文件中读取一个医生记录，并把它放到结构体x内
        while (!feof(fp))
        { // 判断学号ch的医生记录是否已经输入过，输入过则不能再输入
            if (strcmp(x.doc_id, ch) == 0)
            { // 如果在医生文件中找到了工号ch的学生记录，则结束查找
                find = 1;
                break; // 结束查找
            }
            fread(&x, sizeof(Doctor), 1, fp); // 从医生文件中读取一个医生记录，并把它放到结构体x内
        }
        if (find)
        { // 在医生文件中已经存在该学号的学生记录，选择是否输入下一个医生
            printf("\n\n\n\t 账号 %s 已存在! 请问是否重新输入? (y/n)  ", ch);
            do
            {
                gets_s(ch);
            } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
            if (ch[0] == 'y' || ch[0] == 'Y')
                goto F1; // 实际上是构成循环
            else
            {
                fclose(fp);
                system("cls");
                menu();
                break;
            }
        }

        strcpy(t.doc_id, ch);
    F3: printf("\n 请输入密码 : ");
        gets_s(t.pwd); // 继续输入该医生的其他成员值
        printf("\n 请确认密码 :");
        gets_s(tem);

        while (strcmp(t.pwd, tem) != 0) {
            printf("密码确认错误！请重新输入:");
            gets_s(tem);
        }

        printf("\n 姓名 : ");
        gets_s(t.name);
        printf("\n 性别 : ");
        gets_s(ch);

        while (ch[0] != 'f' && ch[0] != 'm' && ch[0] != 'F' && ch[0]!= 'M')
        {
            printf(" 性别输入错误！请重新输入:");
            gets_s(ch);
        }
        t.sex = ch[0];

        printf("\n 电话号码 :");
        gets_s(ch);
        while (strlen(ch) != 11)
        {
            printf(" 电话号码格式输入错误！请重新输入:");
            gets_s(ch);
        }

        strcpy(t.phone, ch);
        printf("\n 年龄  :");
        gets_s(t.age);

        printf("\n 所属科室： ");
        gets_s(t.department);

        fwrite(&t, sizeof(Doctor), 1, fp); 
        printf("==================================================");
        printf("\n\n\n\t 注册成功！");
        system("pause");
        fclose(fp);
        system("cls");
        menu();
        break;
    }
    }
}

void  login_doc()
{
    Doctor a, b;//定义结构体The_users别名
    char ch[3];
    FILE* fp;
    system("cls");
    printf(" \n欢迎来到登录界面！\n\n");
    Sleep(1000);
    if ((fp = fopen("doctor_use.dat", "r")) == 0)
    {
        printf("\n\nCannot open Doctor data file!\n");
        system("pause");
        return;
    }

    fread(&b, sizeof(Doctor), 1, fp); //读入一个结构体字符块 写入b
F2: system("cls");
    printf("\n*******************医生登录**************************\n");
    printf("\n==================================================\n");
    printf(" 请输入账号：");
    scanf("%s", &a.doc_id);

    while (1)
    {
        if (strcmp(a.doc_id, b.doc_id) == 0)         //如果有此用户名
        {
            break;
        }
        else
        {
            if (!feof(fp))  //如果文件没有读完                            
            {
                fread(&b, sizeof(Doctor), 1, fp);
            }
            else
            {
                printf("\n\n\n\t 账号不存在! 请问是否重新输入? (y/n)  ");
                do
                {
                    gets_s(ch);
                } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
                if (ch[0] == 'y' || ch[0] == 'Y')
                    goto F2; // 实际上是构成循环
                else
                {
                    fclose(fp);
                    system("cls");
                    menu();
                    return;
                }
            }
        }
    }
    printf(" 请输入密码：");
    scanf("%s", &a.pwd);
    do {
        if (strcmp(a.pwd, b.pwd) == 0)            /*如果密码匹配*/
        {
            fclose(fp);
            printf("\n 登录成功,欢迎使用!\n");
            system("cls");
            Sleep(500);
            doc_menu(a.doc_id);
        }
        else
        {
            printf("     密码不正确!请重新输入密码\n");
            scanf("%s", &a.pwd);
        }
    } while (strcmp(a.pwd, b.pwd) == 0);
}

void doc_pla()
{
    system("cls");
    int choice;

    while (1) {
        printf("*******************医生入口*************************");
        printf("\n==================================================");
        printf("\n 请选择医生进入方式：\n");
        
        printf("\n 0.返回上一级\n");
        printf(" 1.医生注册            \n 2.医生登录\n\n");

        printf(" 请选择进入方式：（0，1，2）\n");
        scanf("%d", &choice);
        getchar();  // 捕捉换行符

        switch (choice) {
        case 0:
            return;
        case 1:
            register_doc();
            break;
        case 2:
            login_doc();
            break;
        default:
            printf(" 输入格式错误，请重新输入！\n");
        }
    }
}



//=============================================================================

void register_man()
{
    system("cls");
    printf("\n 欢迎来到管理员注册界面！");
    Sleep(500);

    char xz[8];
    //system("cls");
    printf("\n*******************管理员注册**************************");
    printf("\n====================================================");
    printf("\n\n 0.返回上一级");
    printf("\n\n 1.注册管理员账户");
    printf("\n\n 请选择下一步操作： (0, 1) ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');

    system("cls");
    switch (xz[0]) {
    case '0': {
        return;
        break;
    }
    case '1': {
        char ch[30], tem[30];
        int find;
        FILE* fp;
        Manager t, x; 
        if ((fp = fopen("manager_use.dat", "a+b")) == 0)
        {
            printf("\n\nCannot open Manager data file!\n");
            system("pause");
            break;
        }

    F1: system("cls");
        //printf("\n 请输入账号 ");
        printf("*******************管理员注册**************************");
        printf("\n==================================================");
        printf("\n 请输入管理员账号 : ");

        gets_s(ch);
        find = 0;
        rewind(fp);                       // 复位到文件头
        fread(&x, sizeof(Manager), 1, fp); 
        while (!feof(fp))
        { 
            if (strcmp(x.man_id, ch) == 0)
            { 
                find = 1;
                break; // 结束查找
            }
            fread(&x, sizeof(Manager), 1, fp); 
        }
        if (find)
        { 
            printf("\n\n\n\t 账号 %s 已存在! 请问是否重新输入? (y/n)  ", ch);
            do
            {
                gets_s(ch);
            } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
            if (ch[0] == 'y' || ch[0] == 'Y')
                goto F1; // 实际上是构成循环
            else
            {
                fclose(fp);
                system("cls");
                menu();
                break;
            }
        }

        strcpy(t.man_id, ch);
    F3: printf("\n 请输入密码 : ");
        gets_s(t.pwd); 
        printf("\n 请确认密码 :");
        gets_s(tem);

        while (strcmp(t.pwd, tem) != 0) {
            printf("密码确认错误！请重新输入:");
            gets_s(tem);
        }

        fwrite(&t, sizeof(Manager), 1, fp); // 向学生文件中追加一个学生记录
        printf("==================================================");
        printf("\n\n\n\t 注册成功！");
        system("pause");
        fclose(fp);
        system("cls");
        menu();
        break;
    }
    }
}

void man_menu(char doc_id[]) 
{

    system("cls");
    while (1) {
        char xz[8];
        printf("管理员操作菜单:\n");
        printf("==============================\n");
        printf("0. 退出页面\n");
        printf("1. 查看医生信息\n");
        printf("2. 查看患者信息\n");
        printf("3. 查看就诊记录\n");

        printf("\n请选择下一步操作：(0,1,2,3)");
        gets_s(xz);
        //getchar();  // 捕捉换行符
        switch (xz[0]) {
        case '0':
            return;
            break;
        case '1': {  
            int n = 0, flag;
            char ch[30];
            FILE* fp, * fpIdx;
            Doctor t;     

            if ((fp = fopen("doctor_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示\

                printf("\n\nCannot open Doctor data file!\n");
                system("pause");
                break;
            }
            system("cls");
            
            printf("\n工号        姓名          性别    电话      年龄  所属科室\n");
            printf("\n===============================================================================\n\n");

            fread(&t, sizeof(Doctor), 1, fp);  
            while (!feof(fp)) {   
                printf("%-10s  ", t.doc_id);
                printf("%-12s  ", t.name);
                printf("%-2c  ", t.sex);
                printf("%-15s ", t.phone);
                printf("%-s   ", t.age);
                printf("%-s\n", t.department);
                n++;
                fread(&t, sizeof(Doctor), 1, fp);  
                if (n % 20 == 0 || feof(fp)) {   

                    printf("\n===============================================================================\n\n");
                    printf("\t\t 请按任意键继续. ");
                    _getch();    // 停下来，按任意键继续，让用户看清屏幕上的显示内容
                    system("cls");    // 清屏后重新显示表头信息
                    printf("\n工号        姓名          性别    电话      年龄  所属科室\n");
                    printf("\n===============================================================================\n\n");
                }
            }
            break;
        }
        
        case '2': {
            int n = 0, flag;
            char ch[30];
            FILE* fp, * fpIdx;
            Patient t;      

            if ((fp = fopen("patient_use.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示\

                printf("\n\nCannot open Patient data file!\n");
                system("pause");
                break;
            }
            
            
            system("cls");
            
            printf("\n就诊卡号        姓名      性别    电话      年龄   账户余额\n");
            printf("\n===============================================================================\n\n");

            fread(&t, sizeof(Patient), 1, fp);   
            while (!feof(fp)) {    
                printf("%-10s  ", t.pat_id);
                printf("%-12s  ", t.name);
                printf("%-2c  ", t.sex);
                printf("%-15s ", t.phone);
                printf("%-s   ", t.age);
                printf("%-s\n", t.balance);
                n++;
                fread(&t, sizeof(Patient), 1, fp);  
                if (n % 20 == 0 || feof(fp)) {   

                    printf("\n===============================================================================\n\n");
                    printf("\t\t 请按任意键继续. ");
                    _getch();    // 停下来，按任意键继续，让用户看清屏幕上的显示内容
                    system("cls");    // 清屏后重新显示表头信息
                    printf("\n就诊卡号        姓名          性别    电话      年龄   账户余额\n");
                    printf("\n===============================================================================\n\n");
                }
            }
            break;
        }
        
        case '3': {
            int n = 0, flag;
            char ch[30];
            FILE* fp;
            
            Medical_record t;     

            if ((fp = fopen("Medical_record.dat", "rb")) == 0) {    // 由于\用于转义字符，因此\\才表示\

                printf("\n\nCannot open Patient data file!\n");
                system("pause");
                break;
            }
            typedef struct
            {
                char pat_id[11];//病人就诊卡号
                char pat_name[15];   // 病人姓名为字符串
                char disease[10];    //患病名称
                char doc_name[15];   // 治疗医生姓名
                char doc_id[11];  //医生工号（患者挂号后会自动匹配，但不会显示给患者看）
                char department[15]; // 所属科室
                char medicine[10]; //药品名称
                char spend[10]; //消费金额
                struct date time;//诊断时间
                char state[10];//就诊状态
                bool has_paied;//缴费状态

            }Medical_record;//就诊记录
            system("cls");
            // 在屏幕上列表显示学生信息，首先显示表头信息
            printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %10s   %-10s %-10s\n",
                "就诊卡号", "患者姓名", "医生姓名", "医生工号", "患病名称",
                "所属科室", "治疗药物", "消费金额", "诊断时间", "就诊状态");
            printf("\n=========================================================================================================\n\n");

            fread(&t, sizeof(Medical_record), 1, fp);  
            while (!feof(fp)) {   
                printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-13s %-4d-%02d-%02d   %-10s\n",
                    t.pat_id, t.pat_name, t.doc_name, t.doc_id, t.disease, t.department,
                    t.medicine, t.spend, t.time.year, t.time.month, t.time.day, t.state);
                n++;
                fread(&t, sizeof(Medical_record), 1, fp);  
                if (n % 20 == 0 || feof(fp)) {   

                    printf("\n=============================================================================================\n\n");
                    printf("\t\t 请按任意键继续. ");
                    _getch();   
                    system("cls");   
                    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %10s   %-10s %-10s\n",
                        "就诊卡号", "患者姓名", "就诊医生姓名", "就诊医生工号", "患病名称",
                        "所属科室", "治疗药物", "消费金额", "诊断时间", "就诊状态");
                    printf("\n===============================================================================\n\n");
                }
            }
            break;
        }

        default:
            printf("选择非法，请重新输入！\n");
            Sleep(500);
            system("cls");
        
        }
    }
}

void login_man()
{
    Manager a, b;//定义结构体The_users别名
    char ch[3];
    FILE* fp;
    system("cls");
    printf(" \n欢迎来到登录界面！\n\n");
    char xz[8];
    system("cls");
    printf("\n\n  0--返回上一级");
    printf("\n\n  1--管理员登录");
    printf("\n\n  请选择下一步操作： (0, 1):  ");
    do {
        gets_s(xz);
    } while (xz[0] != '0' && xz[0] != '1');
    system("cls");
    switch (xz[0]) {
    case '0': return;
    case '1': {
        if ((fp = fopen("manager_use.dat", "r")) == 0)
        {
            printf("\n\nCannot open Manager data file!\n");
            system("pause");
            return;
        }

        fread(&b, sizeof(Manager), 1, fp); //读入一个结构体字符块 写入b

    F2: system("cls");
        printf(" \n欢迎来到登录界面！\n\n");
        printf(" 请输入账号：");
        scanf("%s", &a.man_id);

        while (1)
        {
            if (strcmp(a.man_id, b.man_id) == 0)         //如果有此用户名
            {
                break;
            }
            else
            {
                if (!feof(fp))  //如果文件没有读完                            
                {
                    fread(&b, sizeof(Manager), 1, fp);
                }
                else
                {
                    printf("\n\n\n\t 账号不存在! 请问是否重新输入? (y/n)  ");
                    do
                    {
                        gets_s(ch);
                    } while (ch[0] != 'y' && ch[0] != 'Y' && ch[0] != 'n' && ch[0] != 'N');
                    if (ch[0] == 'y' || ch[0] == 'Y')
                        goto F2; // 实际上是构成循环
                    else
                    {
                        fclose(fp);
                        system("pause");
                        system("cls");
                        menu();
                        break;
                    }
                }
            }
        }
        printf(" 请输入密码：");
        scanf("%s", &a.pwd);
        do {

            if (strcmp(a.pwd, b.pwd) == 0)            /*如果密码匹配*/
            {
                fclose(fp);
                printf("\n 登录成功,欢迎使用!\n");
                Sleep(500);
                system("cls");
                man_menu(a.man_id);
                return;
            }
            else
            {
                printf("     密码不正确!请重新输入密码\n");
                scanf("%s", &a.pwd);
            }
        } while (strcmp(a.pwd, b.pwd) == 0);
    }
    
    }
}

void man_pla()
{
    system("cls");
    int choice;

    while (1) {
        printf("*******************管理员入口*************************");
        printf("\n==================================================");
        char key[10];
        printf(" \n 请输入管理员密钥：");
        gets_s(key);
        while (strcmp(key,"0235011")!=0)
        {
            printf(" 密钥错误，请重新输入:");
            gets_s(key);
        }

        printf("\n 请选择管理员进入方式：\n");

        printf("\n 0.返回上一级\n");
        printf(" 1.管理员注册            \n 2.管理员登录\n\n");

        printf(" 请选择进入方式：（0，1，2）\n");
        scanf("%d", &choice);
        getchar();  // 捕捉换行符

        switch (choice) {
        case 0:
            return;
        case 1:
            register_man();
            break;
        case 2:
            login_man();
            break;
        default:
            printf(" 输入格式错误，请重新输入！\n");
        }
    }
}

void menu() 
{
    int choice;
    while (1) {
        system("cls");
        printf(" =====================欢迎来到医院信息管理系统！=====================\n\n");
        printf(" 0.退出系统\n\n");
        printf(" 1.医生端进入\n\n");
        printf(" 2.病人端进入\n\n");
        printf(" 3.管理员端进入\n\n");
        printf(" 请选择进入方式：（1，2）\n");
        scanf("%d", &choice);
        getchar();  // 捕捉换行符

        switch (choice) {
        case 0:
            return;
        case 1:
            doc_pla();
            break;
        case 2:
            pat_pla();
            break;
        case 3:
            man_pla();
        default:
            printf(" 输入格式错误，请重新输入！\n");
        }
    }
}

