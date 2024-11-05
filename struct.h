struct date {   // 定义日期结构体类型
    int year;        // 年      取值范围：正整数
    int month;       // 月      取值范围：1～12之间的整数
    int day;         // 日      取值范围：1～31之间的整数，注意不同月份的取值限制
};

typedef struct
{
    char doc_id[11]; // 账号：医生工号
    char pwd[20];    // 密码
    char name[15];   // 姓名
    char sex;        // 性别为单个字符
    char phone[12];  // 电话号s码，11位
    char age[3];     //年龄
    char department[15]; // 所属科室
}Doctor;

typedef struct
{
    char pat_id[11];//病人就诊卡号
    char pwd[20];
    char name[15];   // 姓名为字符串
    char sex;        // 性别为单个字符
    char phone[12];  // 电话号码，11位
    char age[3];
    char balance[11];
    
}Patient;

typedef struct
{
    char man_id[11];//管理员账户
    char pwd[20];
}Manager;

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




