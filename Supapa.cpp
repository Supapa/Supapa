#include "supapa.h"

Supapa::Supapa()
{
    init();
}

Supapa::~Supapa()
{
    delete []Go;
    delete []Prt;
    delete []Rel;
    delete []Needs_List;
    delete []IRL;
    delete []IRLlist;
    delete []IRLlistPrt;
}

void Supapa::init()
{
    PI=3.1415926;
    RATE=100;
    level=0;
    isShowinfo=false;
    isCheckRepeat=true;
    unUsedGo=0;

    Go_Size=10000;
    Go_i=-1;
    Go_2=16;
    Go=new int[Go_2*Go_Size];

    Prt_Size=100000;
    Prt_i=-1;
    Prt_2=4;
    Prt=new float[Prt_2*Prt_Size];

    Rel_Size=100000;
    Rel_i=-1;
    Rel_2=4;
    Rel=new int[Rel_2*Rel_Size];

    Needs_List_2=2;
    Needs_List_i=-1;
    Needs_List_Size=Go_Size;
    Needs_List=new int[Needs_List_Size*Needs_List_2];


    IRL_i=-1; // 0
    IRL_2=8; // 6
    IRL_Size=400; // 9000
    IRL=new int[IRL_2*IRL_Size];
    for(int i=0;i<IRL_Size;i++){
        IRL[i*IRL_2+0]=0;
        IRL[i*IRL_2+1]=0;
        IRL[i*IRL_2+2]=-1;
        IRL[i*IRL_2+3]=-1;
        IRL[i*IRL_2+4]=0;
        IRL[i*IRL_2+5]=0;
    }


    IRLlist_i=-1; // 0
    IRLlist_2=9; // 10
    IRLlist_Size=40000; // 500 pre IRL
    IRLlist=new int[IRLlist_2*IRLlist_Size];

    for(int i=0;i<IRLlist_Size;i++){
        IRLlist[i*IRLlist_2+0]=0;
        IRLlist[i*IRLlist_2+1]=-1;
        IRLlist[i*IRLlist_2+2]=0;
        IRLlist[i*IRLlist_2+3]=-1;
        IRLlist[i*IRLlist_2+4]=-1;
        IRLlist[i*IRLlist_2+5]=0;
        IRLlist[i*IRLlist_2+6]=0;
        IRLlist[i*IRLlist_2+7]=0;
        IRLlist[i*IRLlist_2+8]=0;
    }


    IRLlistPrt_Size=80000;
    IRLlistPrt_i=-1;
    IRLlistPrt_2=4;
    IRLlistPrt=new float[IRLlistPrt_2*IRLlistPrt_Size];
    for(int i=0;i<IRLlistPrt_Size;i++){
        IRLlistPrt[i*IRLlistPrt_2+0]=-1;
        IRLlistPrt[i*IRLlistPrt_2+1]=-1;
        IRLlistPrt[i*IRLlistPrt_2+2]=-1;
        IRLlistPrt[i*IRLlistPrt_2+3]=-1;
    }
}

int Supapa::addGo(int state, int type)
{
    Go_i++;
    if(Go_i>=Go_Size){
        Go_i--;
        return -1 ;
    }
    Go[Go_i*Go_2+0]=state;
    Go[Go_i*Go_2+1]=type;
    Go[Go_i*Go_2+2]=-1;
    Go[Go_i*Go_2+3]=-1;
    Go[Go_i*Go_2+4]=-1;
    Go[Go_i*Go_2+5]=-1;
    Go[Go_i*Go_2+6]=0;
    Go[Go_i*Go_2+7]=-1;
    Go[Go_i*Go_2+8]=0;
    Go[Go_i*Go_2+9]=0;
    Go[Go_i*Go_2+10]=-1;
    Go[Go_i*Go_2+11]=-1;
    Go[Go_i*Go_2+12]=0;
    Go[Go_i*Go_2+13]=-1;
    Go[Go_i*Go_2+14]=level;
    showInfo("添加Go_i："+QString::number(Go_i));
    unUsedGo++;
    return Go_i;
}

int Supapa::addGoPrt(int Go_id, int type, int value)
{
    Prt_i++;
    if(Prt_i<Prt_Size){
        int firsttone;
        firsttone=Go[Go_id*Go_2+2];
        int lastone;
        lastone=Go[Go_id*Go_2+3];
        Prt[Prt_i*Prt_2+0]=Go_id;
        Prt[Prt_i*Prt_2+1]=type;
        Prt[Prt_i*Prt_2+2]=value;
        if(firsttone<0){
            Go[Go_id*Go_2+2]=Prt_i;
        }else{
            Prt[lastone*Prt_2+3]=Prt_i;
        }
        Go[Go_id*Go_2+3]=Prt_i;
        Prt[Prt_i*Prt_2+3]=-1;

        showInfo("添加Prt_i："+QString::number(Prt_i));
        return Prt_i;
    }else{
       Prt_i--;
        return -2;
    }
    return -1;

}

int Supapa::addGoRel(int Go_id, int type, int value)
{

    Rel_i++;
    if(Rel_i<Rel_Size){
        int firsttone;
        firsttone=Go[Go_id*Go_2+4];
        int lastone;
        lastone=Go[Go_id*Go_2+5];
        Rel[Rel_i*Rel_2+0]=Go_id;
        Rel[Rel_i*Rel_2+1]=type;
        Rel[Rel_i*Rel_2+2]=value;
        if(firsttone<0){
            Go[Go_id*Go_2+4]=Rel_i;
        }else{
            Rel[lastone*Rel_2+3]=Rel_i;
        }
        Go[Go_id*Go_2+5]=Rel_i;
        Rel[Rel_i*Rel_2+3]=-1;
        showInfo("添加Rel_i："+QString::number(Rel_i));
        return Rel_i;
    }else{
       Rel_i--;
        return -2;
    }
    return -1;

}

int Supapa::addIRLlistPrt(int IRLlist_id, int type, int value)
{

    IRLlistPrt_i++;
    if(IRLlistPrt_i< IRLlistPrt_Size){
        int firsttone;
        firsttone=IRLlist[IRLlist_id*IRLlist_2+7];
        int lastone;
        lastone=IRLlist[IRLlist_id*IRLlist_2+8];

         IRLlistPrt[IRLlistPrt_i*IRLlistPrt_2+0]=IRLlist_id;
         IRLlistPrt[IRLlistPrt_i*IRLlistPrt_2+1]=type;
         IRLlistPrt[IRLlistPrt_i*IRLlistPrt_2+2]=value;

        if(firsttone<0){
            IRLlist[IRLlist_id*IRLlist_2+7]=IRLlistPrt_i;
        }else{
            IRLlistPrt[lastone*IRLlistPrt_2+3]=IRLlistPrt_i;
        }
        IRLlist[IRLlist_id*IRLlist_2+8]=IRLlistPrt_i;
        IRLlistPrt[IRLlistPrt_i*IRLlistPrt_2+3]=-1;

        showInfo("添加IRLlistPrt_i："+QString::number(IRLlistPrt_i));
        return IRLlistPrt_i;

    }else{
       IRLlistPrt_i--;
        return -2;
    }
    return -1;
}

int Supapa::addToIRL_List(int IRLi, int Go_id)
{
    //
    IRLlist_i++;
    if(IRLlist_i>=IRLlist_Size)
    {
        IRLlist_i=IRLlist_Size-1;
        return -1;
    }
    int firsttone;
    firsttone=IRL[IRLi*IRL_2+2];
    int lastone;
    lastone=IRL[IRLi*IRL_2+3];

    //COPY 属性 ~
    bool isEnd=true;
    int k;
    if(Go[Go_id*Go_2+2]>-1){
        isEnd=false;
    }
    k=Go[Go_id*Go_2+2];
    while(!isEnd){
        addIRLlistPrt(IRLlist_i,Prt[k*Prt_2+1],Prt[k*Prt_2+2]);
        k=Prt[k*Prt_2+3];
        if(k<0) isEnd=true;
    }

    IRLlist[IRLlist_i*IRLlist_2+0]=Go[Go_id*Go_2+6];
    IRLlist[IRLlist_i*IRLlist_2+1]=Go[Go_id*Go_2+7];
    IRLlist[IRLlist_i*IRLlist_2+2]=Go[Go_id*Go_2+8];

    IRLlist[IRLlist_i*IRLlist_2+3]=-1;
    IRLlist[IRLlist_i*IRLlist_2+4]=Go[Go_id*Go_2+1];
    IRLlist[IRLlist_i*IRLlist_2+5]=-1;
    IRLlist[IRLlist_i*IRLlist_2+6]=-1;


    if(firsttone<0){
        IRL[IRLi*IRL_2+2]=IRLlist_i;
    }else{
        IRLlist[lastone*IRLlist_2+3]=IRLlist_i;
    }
    IRL[IRLi*IRL_2+3]=IRLlist_i;

    //更新总相似度值
    IRL[IRLi*IRL_2+4]= IRL[IRLi*IRL_2+4]+IRLlist[IRLlist_i*IRLlist_2+0];

    return IRLlist_i ;

}

int Supapa::addToNeedsList(int Go_id)
{
    Needs_List_i++;
    if(Needs_List_i<Needs_List_Size){
        Needs_List[Needs_List_i*Needs_List_2+0]=Go_id;
    }else{
        Needs_List_i--;
    }

    return Needs_List_i;
}

int Supapa::copyIRLlistToGoRel(int Go_id,int j)
{
    return addGoRel(Go_id,-1,j);
}

double Supapa::getGoPrtValue(int Go_id, int type)
{
    double value=-1;

    bool isEnd=true;
    int k;
    k=Go[Go_id*Go_2+2];  //属性列表
    if(k>=0 ){
        isEnd=false;
    }
    while(!isEnd){
         if(Prt[k*Prt_2+1]==type){
            value=Prt[k*Prt_2+2];
        }
        k=Prt[k*Prt_2+3];
        if(k<0){
            isEnd=true;
        }
    }

    return value;

}

double Supapa::getIRLlistPrtValue(int IRLlist_id, int type)
{

    double value=-1;

    bool isEnd=true;
    int k;
    k=IRLlist[IRLlist_id*IRLlist_2+7];  //属性列表
    if(k>=0 ){
        isEnd=false;
    }
    while(!isEnd){
         if(IRLlistPrt[k*IRLlistPrt_2+1]==type){
            value=IRLlistPrt[k*IRLlistPrt_2+2];
        }
        k=IRLlistPrt[k*IRLlistPrt_2+3];
        if(k<0){
            isEnd=true;
        }
    }
    return value;
}

int Supapa::createGo(int IRL_id,int type)
{
    bool isEnd;
    int i,k;
    int Go_id=-1;
    Go_id=addGo(1,type);

/*
Supapa的对象不具备真正意义上的“反向逻辑”能力，
如果对象自身具备推动力则可能会产生对全局整体设计的挑战，
所谓“反向逻辑”能力源自于某cc对IRLlist内容类型的捕捉，而后push某个具体对象。
*/
    //添加Prt ，


    //
    //重复性检测
    if(isCheckRepeat){

        //
        for(i=0;i<=Go_i;i++){

            //

        }

    }

    //添加Rel
    isEnd=true;
    k=IRL[IRL_id*IRL_2+2];
    if(k>=0) isEnd=false;
    while(!isEnd){
        copyIRLlistToGoRel(Go_id,k);
        k= k+IRLlist[k*IRLlist_2+2]-1; //只记录头  // 直接跳跃  //储存是连续序列
        k=IRLlist[k*IRLlist_2+3];
        if(k<0) isEnd=true;
    }

    //


    return Go_id;

}

bool Supapa::saveData()
{

    QFile file("data101.sup");
    if(!file.open(QIODevice::ReadWrite)){
        return false;
    }
    file.write((char*)IRL,IRL_2*IRL_Size*4);
    file.close();


    QFile file2("data102.sup");
    if(!file2.open(QIODevice::ReadWrite)){
        return false;
    }
    file2.write((char*)IRLlist,IRLlist_2*IRLlist_Size*4);
    file2.close();


    QFile file3("data103.sup");
    if(!file3.open(QIODevice::ReadWrite)){
        return false;
    }
    file3.write((char*)IRLlistPrt,IRLlistPrt_2*IRLlistPrt_Size*4);
    file3.close();

    showInfo("数据已经保存");

    return true;
}

bool Supapa::loadData()
{

    QFile file("data101.sup");
    if(!file.open(QIODevice::ReadWrite)){
        return false;
    }
    file.read((char*)IRL,IRL_2*IRL_Size*4);
    file.close();

    QFile file2("data102.sup");
    if(!file2.open(QIODevice::ReadWrite)){
        return false;
    }
    file2.read((char*)IRLlist,IRLlist_2*IRLlist_Size*4);
    file2.close();

    QFile file3("data103.sup");
    if(!file3.open(QIODevice::ReadWrite)){
         return false;
    }
    file3.read((char*)IRLlistPrt,IRLlistPrt_2*IRLlistPrt_Size*4);
    file3.close();

    //数据发现

    int i;
    for(i=0;i<IRL_Size;i++){
        if(IRL[i*IRL_2+1]==1){
            IRL_i=i;
        }
    }
    for(i=0;i<IRLlist_Size;i++){
        if(IRLlist[i*IRLlist_2+1]==1){
            IRLlist_i=i;
        }
    }

    for(i=0;i<IRLlistPrt_Size;i++){
        if(IRLlistPrt[i*IRLlistPrt_2+0]>=0){
            IRLlistPrt_i=i;
        }
    }

    showInfo("IRL_i："+QString::number(IRL_i));
    showInfo("IRLlist_i："+QString::number(IRLlist_i));
    showInfo("IRLlistPrt_i："+QString::number(IRLlistPrt_i));
    showInfo("数据已加载，且完成发现");

    return true;
}

void Supapa::showInfo(QString str)
{
    if(isShowinfo){
        mwd->showinfoQString(str);
    }
}

void Supapa::showInfoH(QString str)
{
    mwd->showinfoQString(str);
}


int Supapa::Learn()
{

    Check(); // 首先进行一番推进

    //showInfo(QString::number(""));

    int groupSize=5; // 创建对象集合组的对象数量
    int groupedCount;
    int focusLevel; //目标层
    int while1count; //首层循环已经进行的
    int banjing=50;

    int i,k,x,y;

    bool isEnd=true;
    bool isEnd2=true;
    bool isEnd3=true;
    while1count=0;

    if(unUsedGo>1){
        isEnd=false;
    }
    while(!isEnd){

        while1count++;
        if(Go_i>=0) isEnd2=false;
        i=0;

        Needs_List_i=-1;

        if(while1count>3){
            //如果已经推进三层，剩余内容将集中合并
            groupSize=Go_i+100;
            banjing=50000; //巨型数
        }

        while(!isEnd2){
            if(Go[i*Go_2+0]==1 && Go[i*Go_2+1]==3 ){   //检测线段类型 //支持跨层

                x=getGoPrtValue(i,1); //获取1类型属性
                y=getGoPrtValue(i,2); //获取2类型属性

                k=0;groupedCount=0;
                isEnd3=false;
                k=i;

                while(!isEnd3){
                    if(Go[k*Go_2+0]==1 && Go[k*Go_2+1]==3 ){
                        if(check1and2(x,y,banjing,k)){
                            addToNeedsList(k);
                            Go[k*Go_2+0]=3;
                            groupedCount++;
                        }
                    }
                    k++;
                    if(groupedCount=groupSize){
                        //进行封装处理
                        Learn_cerate();
                        groupedCount=0;
                        isEnd3=true;
                    }

                    if(k>Go_i){
                        isEnd3=true;
                        if(groupedCount>=2){
                            //进行封装处理
                            Learn_cerate();
                        }
                    }

                }

            }
            i++;
            if(i>Go_i){
                isEnd2=true;
            }
        }

        if(unUsedGo<=1){
            isEnd=true;
        }
    }

    showInfo("Learn结束");

}

int Supapa::Learn_cerate()
{
    int i,Go_id;
    IRL_i++;
    if(IRL_i>=IRL_Size)
    {
        IRL_i=IRL_Size-1;
        return -1;
    }
    IRL[IRL_i*IRL_2+1]=1;
    IRL[IRL_i*IRL_2+2]=-1;
    IRL[IRL_i*IRL_2+3]=-1;
    IRL[IRL_i*IRL_2+4]=0;
    IRL[IRL_i*IRL_2+5]=0;
    IRL[IRL_i*IRL_2+6]=-1;

    Go_id=addGo(1,2);
    // 产生全局信息
    cc_2();
    //产生对象与全局之关系
    cc_3();
    //
    for(i=0;i<=Go_i;i++){
        if(Go[i*Go_2+1]==2){
            addToIRL_List(IRL_i,i);
            Go[i*Go_2+1]=0;
        }
    }

    showInfo("创建IRL："+QString::number(IRL_i));
    return IRL_i ;
}

void Supapa::Check()
{
    int i,j,k;
    bool isEnd=true;
    int theBigest[2];  // 目标值  // 构成度
    theBigest[0]=-1;theBigest[1]=0;
    int lsIRL_ID;
    int lsIRLlist_ID;
    int unBe; // 没有命中的权重值
    bool isFind;
    int count1,count2;
    count1=0;
    count2=0;

    //不同场次的检测
    for(i=0;i<=Go_i;i++){
        //是场型
        if(Go[i*Go_2+14]>0){
            lsIRL_ID=Go[i*Go_2+14];
            //判断相似度是否达成
            if(Go[i*Go_2+13]<IRL[lsIRL_ID*IRL_2+5]){
                C_1();
                //进行匹配
                isEnd=true;
                //检测未匹配列表
                k=Go[i*Go_2+4];
                if(k>=0) isEnd=false;
                while(!isEnd){
                    if(Rel[k*Rel_2+2]>=0){
                        count2++;
                        lsIRLlist_ID=Rel[k*Rel_2+2];
                         for(j=0;j<=Needs_List_i;j++){
                             if(Needs_List[j*Needs_List_2+0]>=0){
                                 if(CheckSeries(lsIRLlist_ID,Needs_List[j*Needs_List_2+0])){
                                     Go[i*Go_2+13]+=IRLlist[lsIRLlist_ID*IRLlist_2+0];
                                     Rel[k*Rel_2+1]=Needs_List[j*Needs_List_2+0];//记录对应值Go.id
                                     Rel[k*Rel_2+2]=-1;//取消
                                     Needs_List[j*Needs_List_2+0]=-1; //取消
                                     //
                                     count1++;
                                 }
                             }
                         }
                    }
                    k=Rel[k*Rel_2+3];
                    if(k<0) isEnd=true;
                }
                //检测激活度

            }
        }
    }

    C_1();

    //IRL中进行全新
    k=-1;
    count1=0;
    count2=0;
    for(i=0;i<=IRL_i;i++){
        if(IRL[i*IRL_2+2]>-1){
            count1++;
            isEnd=true;
            k=IRL[i*IRL_2+2];
            if(k>=0) isEnd=false;
            unBe=0;
            while(!isEnd){
                count2++;
                isFind=false;
                for(j=0;j<=Go_i;j++){
                    if(IRLlist[k*IRLlist_2+4]==Go[j*Go_2+1] &&Go[j*Go_2+10] !=i){
                        if(IRLlist[k*IRLlist_2+2]>0 &&Go[j*Go_2+8]>0 && IRLlist[k*IRLlist_2+2]==Go[j*Go_2+8]){
                            if(CheckSeries(k,j)){
                                IRL[i*IRL_2+5]=IRL[i*IRL_2+5]+(IRLlist[k*IRLlist_2+0]*IRLlist[k*IRLlist_2+2]); //增加相似度(权重值)
                                Go[j*Go_2+10]=i; // 已经完成了匹配
                                Go[j*Go_2+11]=k; // 已经完成了匹配,记录所匹配上IRL list id
                                j=Go_i;
                                isFind=true;
                            }
                        }
                    }
                    if(j!=Go_i)    j=j+Go[j*Go_2+8]-1 ;  //跳跃连续的序列
                }
                k= k+IRLlist[k*IRLlist_2+2]-1; // 直接跳跃
                k=IRLlist[k*IRLlist_2+3];
                if(k<0) isEnd=true;
            }
            //够成度判断
            if(((double)IRL[i*IRL_2+5]/(double)IRL[i*IRL_2+4])>0.3){
                 createGo(i,1);
            }
            IRL[i*IRL_2+5]=0;
        }
    }

    showInfo("Check结束");
    return  ;

}

bool Supapa::CheckSeries(int i, int j)
{
    if(IRLlist[i*IRLlist_2+2]!=Go[j*Go_2+1]){
        return false;
    }
    if(IRLlist[i*IRLlist_2+4]!=Go[j*Go_2+8]){
        return false;
    }
    int k2,j2;
    int SeriseSize =IRLlist[i*IRLlist_2+2] ;
    for(int ii=0;ii<SeriseSize;ii++){
        k2=i+ii;
        j2=j+ii;
        if(!CheckTrue(k2,j2)){
            return false;
        }
    }
    return true;
}

bool Supapa::CheckTrue(int i, int j)
{
    bool isEnd=true;
    int k,l;
    k=IRLlist[i*IRLlist_2+7];  //属性列表
    l=Go[j*Go_2+2];  //属性列表
    if(k>=0 && l>=0){
        isEnd=false;
    }
    while(!isEnd){
        //
        if(IRLlistPrt[k*IRLlistPrt_2+1]!=Prt[l*Prt_2+1] || IRLlistPrt[k*IRLlistPrt_2+2]!=Prt[l*Prt_2+2]){
            return false;
        }
        k=IRLlistPrt[k*IRLlistPrt_2+3];
        l=Prt[l*Prt_2+3];

        if(k<0 && l<0){
            return true;
        }
        if(k<0 || l<0){
            return false;
        }
    }
    return false;
}

