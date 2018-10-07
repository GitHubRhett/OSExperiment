#include<iostream>
#include <iomanip>
#include <string>
using namespace std;



//***********************函数定义区************************//

int &  operator -( const  string & time1, const  string &time2)//两个标准时间相减，返回相差分钟数
{
    int r_time;
    int hour_time1,hour_time2,hour;
    int minute_time1,minute_time2,minute;
    int carry;
    unsigned int colon;

    for (colon = 0;colon<time1.length();colon++)
    {
        if(time1[colon]==':')break;
    }
    hour_time1=stoi(time1.substr(0,colon));
    minute_time1=stoi(time1.substr(colon+1,time1.length()-1));
    for (colon = 0;colon<time2.length();colon++)
    {
        if(time2[colon]==':')break;
    }
    hour_time2=stoi(time2.substr(0,colon));
    minute_time2=stoi(time2.substr(colon+1,time2.length()-1));


    if(hour_time1>=hour_time2) {
        minute=minute_time1-minute_time2;
        if(minute<0)
        {
            minute=minute+60;
            carry=-1;
            hour=hour_time1-hour_time2-1;
        }
        else{
            hour = hour_time1 - hour_time2;
        }
    }
    else
    { minute=minute_time2-minute_time1;
        if(minute<0)
        {
            minute=minute+60;
            carry=-1;
            hour=hour_time2-hour_time1-1;
        }
        else{
            hour = hour_time2 - hour_time1;
        }
    }


    r_time=hour*60+minute;
    //cout<<"r_time="<<r_time;
    return  r_time;
}

bool operator < (const  string & time1, const  string &time2)//判断time1和time2的时间先后
{
    int hour_time1,hour_time2;
    int minute_time1,minute_time2;
    unsigned int colon;
    for (colon = 0;colon<time1.length();colon++)
    {
        if(time1[colon]==':')break;
    }
    hour_time1=stoi(time1.substr(0,colon));
    minute_time1=stoi(time1.substr(colon+1,time1.length()-1));
    for (colon = 0;colon<time2.length();colon++)
    {
        if(time2[colon]==':')break;
    }
    hour_time2=stoi(time2.substr(0,colon));
    minute_time2=stoi(time2.substr(colon+1,time2.length()-1));

    if(hour_time1<hour_time2)
        return 1;
    else if(hour_time1==hour_time2&&minute_time1<minute_time2)
        return 1;
    else
        return 0;
}


string & operator + ( const  string & time1, int Etime)//标准时间格式time1与整数分钟数Etime相加，返回time1过了Etime分钟后的标准时间格式
{
    string r_time;
    int hour_time1,hour_time2,hour;
    int minute_time1,minute_time2,minute;
    int carry;//进位标记
    unsigned int colon;//冒号的位置

    for (colon = 0;colon<time1.length();colon++)
    {
        if(time1[colon]==':')break;
    }//time1冒号的定位
    hour_time1=stoi(time1.substr(0,colon));//time1时针值的提取
    minute_time1=stoi(time1.substr(colon+1,time1.length()-1));//time1分针值的提取

    hour_time2=(int)(Etime/60);
    minute_time2=(int)(Etime%60);//将分钟转化为标准时间格式对齐数据

    carry=(minute_time1+minute_time2)/60;
    minute=(minute_time1+minute_time2)%60;
    hour=(hour_time1+hour_time2+carry)%24;

    if(hour==0&&minute!=0)
        r_time="00:"+to_string(minute);
    else if(hour!=0&&minute==0)
        r_time=to_string(hour)+":00";
    else if(hour==0&&minute==0)
        r_time="00:00";
    else
        r_time=to_string(hour)+":"+to_string(minute);

    return  r_time;


}



//***********************类定义区*************************//
class JOB
{
public:
    int JOBDone;//是否完成标记
    int JobID;//作业标记
    string EntryTime;//进入时间
    int E_RunningTime;//估计运行时间
    string StartTime;//开始时间
    string EndTime;//结束时间
    int TurnaroundTime;//周转时间
    double R_TurnaroundTime;//带权周转时间
    JOB *Next_Job;//指向下一个工作

    JOB()
    {
        cout<<"JobID:";
        cin>>JobID;
        cout<<endl;
        cout<<"EntryTime";
        cin>>EntryTime;
        cout<<endl;
        cout<<"E_RunningTime";
        cin>>E_RunningTime;
        cout<<endl;
        JOBDone=0;
        Next_Job=NULL;
    }
    JOB(int I_JobID)
    {
        this->JobID=I_JobID;
        cout<<endl;
        cout<<"EntryTime";
        cin>>EntryTime;
        cout<<endl;
        cout<<"E_RunningTime";
        cin>>E_RunningTime;
        cout<<endl;
        Next_Job=NULL;
    }

    JOB(JOB &c_JOB)
    {
        this->JOBDone=c_JOB.JOBDone;
        this->JobID=c_JOB.JobID;
        this->EntryTime=c_JOB.EntryTime;
        this->E_RunningTime=c_JOB.E_RunningTime;
        this->StartTime=c_JOB.StartTime;
        this->EndTime=c_JOB.EndTime;
        this->TurnaroundTime=c_JOB.TurnaroundTime;
        this->R_TurnaroundTime=c_JOB.R_TurnaroundTime;
        Next_Job=NULL;
    }


};

class InputWell
{
public:
    JOB *P_FirstJob;
    JOB *P_LastJob;
    int num_job;

    InputWell()//输入井的初始化
    {
        int I_JobID=0;//存储作业ID的过程变量
        JOB* p;//过程指针
        this->num_job=0;
        while(I_JobID!=-1)
        {

            cout<<"input JobID putting in well:";
            cin>>I_JobID;
            cout<<endl;
            if(P_FirstJob==NULL&&I_JobID!=-1)
            {
                P_FirstJob=new JOB(I_JobID);
                p=P_FirstJob;
                this->num_job++;
            }
            else if(P_FirstJob!=NULL&&I_JobID!=-1)
            {
                p->Next_Job=new JOB(I_JobID);
                p=p->Next_Job;
                this->num_job++;
            }
            else if(P_FirstJob!=NULL&&I_JobID==-1)
            {
                P_LastJob=p;
                p=NULL;
            }
            else
            {
                P_FirstJob=NULL;
                P_LastJob=NULL;
                p=NULL;
            }

        }
        //this->test_Show();
    }

    void test_Show()//测试用过程函数
    {
        JOB *display=this->P_FirstJob;

        cout<<"作业  "<<"进入时间  "<<"估计运行时间（分钟）  "<<endl;
        do
        {
            cout<<display->JobID<<" "<<display->EntryTime<<" "<<display->E_RunningTime<<endl;
            display=display->Next_Job;
        }
        while(display!=NULL);
        cout<<this->num_job;
    }
};

class Processor
{
public:
    InputWell *P_InputWell;
    JOB *P_QFront;
    JOB *P_QRear;
    JOB *PJOBCHOOSE;//CPU选择指针
    JOB *P_JOB1;//第一道作业
    JOB *P_JOB2;//第二道作业
    string PresentTime;
    Processor()//处理器初始化
    {
        P_InputWell=NULL;
        P_QFront=NULL;
        P_QRear=NULL;
        P_JOB1=NULL;
        P_JOB2=NULL;
        PJOBCHOOSE=NULL;
        cout<<"PresentTime:";
        cin>>PresentTime;
        cout<<endl;
    }




    JOB* FRP_ShortestJob(string ptime)//找到运行时间最短井且未完成的作业
    {
        cout<<"shortest"<<endl;
        int flag=1;
        JOB *tfind=(*P_InputWell).P_FirstJob;

        do{
            if((tfind->JOBDone)==0)
            {
                flag=0;
                break;
            }
            tfind=tfind->Next_Job;
        }
        while(tfind!=(*P_InputWell).P_LastJob);
        //cout<<"still OK"<<endl;
        if((tfind->JOBDone)==0)flag=0;
        if(flag==1)
            return NULL;
        cout<<"still OK"<<endl;
        int ShortestJob=1500;
        JOB *find=P_InputWell->P_FirstJob;
        JOB *P_ShortestJob=NULL;
        do{
            if (find->E_RunningTime<ShortestJob&&find->JOBDone!=1&&!(ptime<find->EntryTime)&&find!=P_JOB1&&find!=P_JOB2)
            {
                ShortestJob=find->E_RunningTime;
                P_ShortestJob=find;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        if (find->E_RunningTime<ShortestJob&&find->JOBDone!=1&&!(ptime<find->EntryTime)&&find!=P_JOB1&&find!=P_JOB2) P_ShortestJob=find;
        return P_ShortestJob;
    }




    int Is_AllDone()//判断工作是否全被做完
    {
        cout<<"Is_AllDone was called"<<endl;
        int flag=1;
        JOB *find=(*P_InputWell).P_FirstJob;

        do{
            if((find->JOBDone)!=1)
            {
                flag=0;
                break;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        //cout<<"still OK"<<endl;
        if((find->JOBDone)!=1)flag=0;

        return flag;
    }

    void QueneEntry(JOB * EntryJOB)//将处理好的队列入队准备显示
    {
        JOB *CEntryJOB=new JOB(*EntryJOB);
        if(this->P_QFront==NULL&&this->P_QRear==NULL)
        {
            this->P_QFront=CEntryJOB;
            this->P_QRear=CEntryJOB;
        }
        else
        {
            (this->P_QRear)->Next_Job=CEntryJOB;
            this->P_QRear=CEntryJOB;
            this->P_QRear->Next_Job=NULL;
        }

    }


    bool  compare ( JOB * JOB1,  JOB * JOB2)//JOB1与JOB2相比较，得出谁的剩余工作时间最短
    {
        cout<<"compare was called"<<endl;
        if(JOB1->JOBDone==2)
        {
            cout<<"computer1   "<<(JOB1->E_RunningTime-(JOB1->EndTime-JOB1->StartTime))<<endl;
            cout<<"computer1 .1   "<<(JOB1->EndTime-JOB1->StartTime)<<endl;
            cout<<"computer1  .2 "<<JOB1->E_RunningTime<<endl;

            if ((JOB1->E_RunningTime-(JOB1->EndTime-JOB1->StartTime))>JOB2->E_RunningTime)return 1;
            else return 0;
        }
        if(JOB2->JOBDone==2)
        {
            cout<<"computer2"<<(JOB1->E_RunningTime-(JOB1->EndTime-JOB1->StartTime))<<endl;
            if ((JOB2->E_RunningTime-(JOB2->EndTime-JOB2->StartTime))>JOB1->E_RunningTime)return 0;
            else return 1;
        }

    }

    JOB* FindNextJOB()//找出下一个要从输入井进入内存的JOB（常用于最开始第二个作业进入时）
    {

        int minTSpace=10000;//最短时间间隔
        JOB *find=P_InputWell->P_FirstJob;
        JOB *P_NextJOB=NULL;
        do{
            if ((find->EntryTime-this->PresentTime)<minTSpace&&find->JOBDone!=1&&find!=this->PJOBCHOOSE)
            {
               minTSpace=find->EntryTime-this->PresentTime;
                P_NextJOB=find;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        if ((find->EntryTime-this->PresentTime)<minTSpace&&find->JOBDone!=1&&find!=this->PJOBCHOOSE) P_NextJOB=find;;
        return P_NextJOB;
    }

    void JobDeal(string ntime)//作业不完全处理，只处理至ntime处，作业标志位置为2（半处理状态）
    {
        JOB *deal=this->PJOBCHOOSE;
        deal->StartTime=this->PresentTime;
        deal->EndTime=ntime;
        this->PresentTime=ntime;
        deal->JOBDone=2;
        cout<<"deal->JobID"<<deal->JobID<<endl;
        cout<<"start"<<deal->StartTime<<endl;
        cout<<"end"<<deal->EndTime<<endl;

    }

    void JobDeal()//作业完全处理，作业标志位置为1
    {
        cout<<"JOb deal was called"<<endl;
        if(this->PJOBCHOOSE->JOBDone==2)
        {
            JOB *deal=this->PJOBCHOOSE;
            deal->EndTime=this->PresentTime+(deal->E_RunningTime-(deal->EndTime-deal->StartTime));
            PresentTime=PresentTime+(deal->E_RunningTime-(deal->EndTime-deal->StartTime));
            deal->TurnaroundTime=(deal->EndTime)-(deal->EntryTime);
            deal->R_TurnaroundTime=(double)(deal->TurnaroundTime)/(double)(deal->E_RunningTime);
            deal->JOBDone=1;
            QueneEntry(deal);
            if(this->PJOBCHOOSE==this->P_JOB1)this->P_JOB1=NULL;
            else if(this->PJOBCHOOSE==this->P_JOB2) this->P_JOB2=NULL;
        } else
        {
            JOB *deal=this->PJOBCHOOSE;
            deal->StartTime=PresentTime;
            deal->EndTime=(deal->StartTime)+(deal->E_RunningTime);
            PresentTime=PresentTime+(deal->E_RunningTime);
            deal->TurnaroundTime=(deal->EndTime)-(deal->EntryTime);
            deal->R_TurnaroundTime=(double)(deal->TurnaroundTime)/(double)(deal->E_RunningTime);
            deal->JOBDone=1;
            QueneEntry(deal);
            if(this->PJOBCHOOSE==this->P_JOB1)this->P_JOB1=NULL;
            else if(this->PJOBCHOOSE==this->P_JOB2) this->P_JOB2=NULL;
        }

    }

    void CompareInterrupt()//比较中断，每当一个作业进入内存后，触发中断，对cpu的选择作出判断
    {
        cout<<"zhongduan was called"<<endl;
        if(this->P_JOB1==NULL||this->P_JOB2==NULL)
        {
                if (this->P_JOB1==NULL)
                    this->PJOBCHOOSE=this->P_JOB2;
                else if(this->P_JOB2==NULL)
                    this->PJOBCHOOSE=this->P_JOB1;
                string nexttime=this->FindNextJOB()->EntryTime;
                this->JobDeal(nexttime);
        }
        else
        {
            if(compare(this->P_JOB1,this->P_JOB2))
            {
                cout<<"in #1"<<endl;
                this->PJOBCHOOSE=this->P_JOB2;
                this->JobDeal();
                }
            else
            {
                cout<<"in #2"<<endl;
                this->PJOBCHOOSE=this->P_JOB1;
                this->JobDeal();
            }
        }
    }


    void Dprog_BatchProcessing()//二道作业批处理
    {   JOB *deal=NULL;
        while(!this->Is_AllDone())
        {
            if(this->P_JOB1==NULL||this->P_JOB2==NULL){

                deal = this->FRP_ShortestJob(this->PresentTime);
                if(this->P_JOB1==NULL&&deal!=NULL)//当第一道作业位为空
                {
                    cout<<"@@@@@@@@@@@@1"<<endl;
                    this->P_JOB1 = deal;
                    this->CompareInterrupt();
                    cout<<"nowtime"<<this->PresentTime<<endl;
                }
                else if(this->P_JOB2==NULL&&deal!=NULL)//当第二道作业位为空
                {
                    cout<<"@@@@@@@@@@@@2"<<endl;
                    this->P_JOB2=deal;
                    this->CompareInterrupt();
                    cout<<"nowtime"<<this->PresentTime<<endl;
                }
                else if(this->P_JOB1==NULL)//当只剩下一道作业未处理，且为作业2时
                {
                    cout<<"win"<<endl;
                    this->PJOBCHOOSE=this->P_JOB2;
                    this->JobDeal();
                    break;
                }
                else if(this->P_JOB2==NULL)//当只剩下一道作业未处理，且为作业1时
                {
                    cout<<"win too"<<endl;
                    this->PJOBCHOOSE=this->P_JOB1;
                    this->JobDeal();
                    break;
                }

            }
        }

    }

    void R_Show()//显示处理结果
    {
        JOB *display=this->P_QFront;
        int TTREM[P_InputWell->num_job];//周转时间记录
        float RTREM[P_InputWell->num_job];//带权周转时间记录

        //cout<<"@"<<P_InputWell->num_job<<endl;
        int count=0;
        cout<<"作业          "<<"进入时间        "<<"估计运行时间（分钟)  "<<"开始时间        "<<"结束时间        "<<"周转时间        "<<"带权周转时间        "<<endl;
        do
        {
            TTREM[count]=display->TurnaroundTime;
            //cout<<"TTREM"<<count<<"="<<TTREM[count]<<endl;
            RTREM[count]=display->R_TurnaroundTime;
            //cout<<"RTREM"<<count<<"="<<RTREM[count]<<endl;
            count++;
            cout<<display->JobID<<"             "<<display->EntryTime<<"            "<<display->E_RunningTime<<"               "<<display->StartTime<<"           "<<display->EndTime<<"           "<<display->TurnaroundTime<<"             "<<display->R_TurnaroundTime<<"              "<<endl;
            display=display->Next_Job;
        }
        while(display!=NULL);

        int aver_T=0;//平均周转时间
        float aver_R=0;//平均带权周转时间
        for (int i = 0; i <P_InputWell->num_job ; ++i) {
            aver_T=aver_T+TTREM[i];
            //cout<<"TTREM"<<i<<"="<<TTREM[i]<<endl;
        }

        //cout<<"@"<<P_InputWell->num_job<<endl;
        aver_T=aver_T/P_InputWell->num_job;
        for (int i = 0; i <P_InputWell->num_job; ++i) {
            aver_R=aver_R+RTREM[i];
            //cout<<"RTREM"<<i<<"="<<RTREM[i]<<endl;
        }
        //cout<<"@"<<P_InputWell->num_job<<endl;
        aver_R=aver_R/P_InputWell->num_job;
        //cout<<count+1;

        cout<<"作业平均周转时间 T="<<aver_T<<" 分钟"<<endl;
        cout<<"作业带权平均周转时间 W="<<aver_R<<" 分钟"<<endl;


    }

};
//********************主函数*********************//
int main()
{
    Processor test1;
    test1.P_InputWell=new InputWell();
    test1.Dprog_BatchProcessing();
    test1.R_Show();

    return 0;
}

