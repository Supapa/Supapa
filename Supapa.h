#ifndef SUPAPA_H
#define SUPAPA_H


//来自Sigarea.com.cn的开源轻量级通用模式识别引擎
//2014-06-13

//纯对象系统

class Supapa
{
public:
    Supapa();
    ~Supapa();


    double PI;
    double RATE; // 目标分辨率  0-无限 ，更具目标视觉面积的不同而不同
    int level; // 计算层
    bool isShowinfo;
    bool isCheckRepeat; //检测重复性开关
    int unUsedGo; //有效Go对象数量

    int *Go; //对象
    //0、状态值(0、无效 1、有效 2、待代入新IRLlist 3、已经被Learn处理过了)
    //1、Type  2、属性list起始 3、属性list终止    4、构成关系REL起始 5、构成关系REL终止
    //6、对比权重 7、序列Id  8、序列总数 9、浮动性 10、临时处理标记 11、临时处理标记2
    //12、构成量  13、所等价的IRL.id 14、Level
    int Go_Size;
    int Go_i;
    int Go_2; //16


    float *Prt; // 属性
    //0、所属Go.id 1、Type 2、Value  3、下一位置
    int Prt_Size;
    int Prt_i;
    int Prt_2; //4

    int *Rel; // 关系数据
    //0、所属Go.id 1、所对应的Go.id 2、Value  3、下一位置
    int Rel_Size;
    int Rel_i;
    int Rel_2; //4

    // imagery_List // 本区域
    int *Needs_List; // 0、Imagery.id
    int Needs_List_2;
    int Needs_List_i;
    int Needs_List_Size;


    // 下面是特征(对象)相关

    int *IRL; // imagery relation  目标数组
    //0、类型(目前用于创建场时) 1,valid 2,IRLlist Start 3,
    //IRLlist End 4、构成量(比对权重总量) 5、临时构成量 6、关联目标(-1)  7、--
    int IRL_i; // 0
    int IRL_2; // 8
    int IRL_Size; // 9000

    int *IRLlist;  // 目标特征关系记录
    //0、对比权重值 1、所在序列id  2、序列项总数
    //3、下一位置 4、TYPE(IRL.id) 5、被处理状态(记录是否被命中)  6、配指IRLlist.id（-1）
    //7、属性IRLlistPrt起点 8、属性IRLlistPrt终点
    int IRLlist_i; // 0
    int IRLlist_2; // 9
    int IRLlist_Size; // 2000

    float *IRLlistPrt;
    //0、所属Go.id 1、Type 2、Value  3、下一位置
    int IRLlistPrt_i; // 0
    int IRLlistPrt_2; // 4
    int IRLlistPrt_Size; // 20000

    int currentSeriesId;

    void init();
    int Learn();
    int Learn_cerate();
    void Check();
    bool CheckSeries(int i, int j);
    bool CheckTrue(int i, int j);



    // 服务

    int addGo(int state,int type);
    int addGoPrt(int Go_id,int type,int value);
    int addGoRel(int Go_id, int type, int value);

    int addIRLlistPrt(int IRLlist_id,int type,int value);
    int addToIRL_List(int IRLi,int Go_id);
    int addToNeedsList(int Go_id);
    int copyIRLlistToGoRel(int Go_id, int j);

    double getGoPrtValue(int Go_id,int type);
    double getIRLlistPrtValue(int IRLlist_id,int type);

    int createGo(int IRL_id,int type);

    bool saveData();
    bool loadData();

    void showInfo(QString str); //根据条件进行输出
    void showInfoH(QString str); // 强制报告输出用


    //Dc
    void C_1();
    void cc_2(); //测量主体信息
    void cc_3();//产生特征与主体之间的信息关系,这些信息关系也可以Go化，如何整合如IRL体系中

    //Others

    void buildNeedsListByXandY(int x,int y, int banjing);
    bool check1and2(int x,int y, int banjing,int Go_id);


};

#endif // SUPAPA_H
