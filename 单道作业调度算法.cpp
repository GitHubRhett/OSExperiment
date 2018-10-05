#include<iostream>
#include <iomanip>
#include <string>
using namespace std;



//***********************函数定义区************************//

int &  operator -( const  string & time1, const  string &time2)
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


    if(hour_time1>hour_time2) {
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

bool operator < (const  string & time1, const  string &time2)
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

string & operator + ( const  string & time1, int Etime)
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

    InputWell(){
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

    void test_Show()
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
    string PresentTime;
    Processor()
    {
        P_InputWell=NULL;
        P_QFront=NULL;
        P_QRear=NULL;
        cout<<"PresentTime:";
        cin>>PresentTime;
        cout<<endl;
    }

    double ResponseRatio(JOB *pjob)
    {
        return (double)(PresentTime-pjob->EntryTime+pjob->E_RunningTime)/(double)(pjob->E_RunningTime);
    }

    JOB* FRP_EarliestJob()//找到最先进入输入井且未完成的作业
    {


        string EarliestJob="25:00";
        JOB *find=(*P_InputWell).P_FirstJob;
        JOB *P_EarliestJob=NULL;

        do{
            if (find->EntryTime<EarliestJob&&find->JOBDone==0)
            {
                EarliestJob=find->EntryTime;
                P_EarliestJob=find;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        if (find->EntryTime<EarliestJob&&find->JOBDone==0) P_EarliestJob=find;

        return P_EarliestJob;
    }

    JOB* FRP_ShortestJob(string ptime)//找到运行时间最短井且未完成的作业
    {


        int ShortestJob=1500;
        JOB *find=P_InputWell->P_FirstJob;
        JOB *P_ShortestJob=NULL;
        do{
            if (find->E_RunningTime<ShortestJob&&find->JOBDone==0&&!(ptime<find->EntryTime))
            {
                ShortestJob=find->E_RunningTime;
                P_ShortestJob=find;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        if (find->E_RunningTime<ShortestJob&&find->JOBDone==0&&!(ptime<find->EntryTime)) P_ShortestJob=find;
        return P_ShortestJob;
    }

    JOB* FRP_HRRatioJob(string ptime)//找到响应比井且未完成的作业
    {


        int HighestRatio=0;
        JOB *find=P_InputWell->P_FirstJob;
        JOB *P_HighestRatio=NULL;
        do{
            if (ResponseRatio(find)>HighestRatio&&find->JOBDone==0&&!(ptime<find->EntryTime))
            {
                HighestRatio=ResponseRatio(find);
                P_HighestRatio=find;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        if (ResponseRatio(find)>HighestRatio&&find->JOBDone==0&&!(ptime<find->EntryTime)) P_HighestRatio=find;
        return P_HighestRatio;
    }



    int Is_AllDone()//判断工作是否全被做完
    {
        //cout<<"Is_AllDone was called"<<endl;
        int flag=1;
        JOB *find=(*P_InputWell).P_FirstJob;

        do{
            if((find->JOBDone)==0)
            {
                flag=0;
                break;
            }
            find=find->Next_Job;
        }
        while(find!=(*P_InputWell).P_LastJob);
        //cout<<"still OK"<<endl;
        if((find->JOBDone)==0)flag=0;

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


    void FCFS()
    {
        while(!this->Is_AllDone())
        {
            JOB *deal=FRP_EarliestJob();
            deal->StartTime=PresentTime;
            deal->EndTime=(deal->StartTime)+(deal->E_RunningTime);
            PresentTime=PresentTime+(deal->E_RunningTime);
            deal->TurnaroundTime=(deal->EndTime)-(deal->EntryTime);
            deal->R_TurnaroundTime=(double)(deal->TurnaroundTime)/(double)(deal->E_RunningTime);
            deal->JOBDone=1;
            QueneEntry(deal);
        }
    }

    void SJF(){

      while(!this->Is_AllDone())
      {
          JOB *deal=FRP_ShortestJob(this->PresentTime);
          deal->StartTime=PresentTime;
          deal->EndTime=(deal->StartTime)+(deal->E_RunningTime);
          PresentTime=PresentTime+(deal->E_RunningTime);
          deal->TurnaroundTime=(deal->EndTime)-(deal->EntryTime);
          deal->R_TurnaroundTime=(double)(deal->TurnaroundTime)/(double)(deal->E_RunningTime);
          deal->JOBDone=1;
          QueneEntry(deal);


      }

    }

    void HRRN() {
        while(!this->Is_AllDone())
        {
            JOB *deal=FRP_HRRatioJob(this->PresentTime);
            deal->StartTime=PresentTime;
            deal->EndTime=(deal->StartTime)+(deal->E_RunningTime);
            PresentTime=PresentTime+(deal->E_RunningTime);
            deal->TurnaroundTime=(deal->EndTime)-(deal->EntryTime);
            deal->R_TurnaroundTime=(double)(deal->TurnaroundTime)/(double)(deal->E_RunningTime);
            deal->JOBDone=1;
            QueneEntry(deal);
        }
    }

    void R_Show()
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
    //test1.FCFS();
    //test1.R_Show();
    //test1.SJF();
    //test1.R_Show();
    test1.HRRN();
    test1.R_Show();
    return 0;
}

