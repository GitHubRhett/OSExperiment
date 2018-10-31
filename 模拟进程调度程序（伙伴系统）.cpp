#include<iostream>
#include <list>
using namespace std;

#define STATE_NEW 1
#define STATE_READY 2
#define STATE_RUNNING 3
#define STATE_WAITING 4
#define STATE_TERMINATE 5
#define PCB_LIMIT_AMOUNT 10

class PCB {
public:
    int  Identifier;
    int  State;
    int  Priority;
    int  I_O_Status_Info;

    PCB()
    {
        this->Identifier=-1;
        this->I_O_Status_Info=0;
        this->Priority=-1;
        this->State=-1;

    }
    PCB(int  ID)
    {
        this->Identifier=ID;
        this->State=STATE_NEW;
        this->I_O_Status_Info=0;
        std::cout<<"PRIORITY:";
        std::cin>>this->Priority;
        std::cout<<std::endl;
    }
};


 list <PCB *> PCB_Pool(PCB_LIMIT_AMOUNT);
 list <PCB *> PCB_Queue;
 list <PCB *> PCB_Waiting_Queue;
 list <PCB *> PCB_Ready_Queue;


class Process_Scheduling
{
public:
    list <PCB *>  SPCB_Pool;
    list <PCB *>  SPCB_Queue;
    list <PCB *>  SPCB_Ready_Queue;
    list <PCB *>  SPCB_Wating_Queue;
    PCB *PCB_On_Runing;
    int Flag_Is_Running;
    int Amount_Of_PCB;

    Process_Scheduling()
    {
        this->SPCB_Pool =  PCB_Pool;
        this->SPCB_Queue=  PCB_Queue;
        this->SPCB_Ready_Queue = PCB_Ready_Queue;
        this->SPCB_Wating_Queue = PCB_Waiting_Queue;
        this->PCB_On_Runing=NULL;
        this->Flag_Is_Running=0;
        this->Amount_Of_PCB=PCB_LIMIT_AMOUNT;
    }

    void Init_Process()
    {
            PCB * use1 = this->SPCB_Pool.front();
            this->SPCB_Pool.pop_front();
            int Identifier;
            std::cout<<"IDENTIFIER OF CREATE:";
            cin>>Identifier;
            use1 = new PCB (Identifier);
            use1->State=STATE_NEW;
            this->SPCB_Queue.push_back(use1);
            use1->State=STATE_READY;
            this->SPCB_Ready_Queue.push_back(use1);

    }

    void Term_Process()
    {
        PCB *use2;
        int useid = this->PCB_On_Runing->Identifier;
        this->PCB_On_Runing = NULL;
        this->Flag_Is_Running = 0;
        list<PCB *>::iterator it;
        for (it = this->SPCB_Queue.begin(); it != this->SPCB_Queue.end(); it++)
        {
            PCB *use3 = *it;
            if (use3->Identifier == useid)
            {
                this->SPCB_Queue.erase(it);
                use2 = use3;
                break;
            }
        }
        use2->State=STATE_TERMINATE;
        use2->Identifier=-1;
        this->SPCB_Pool.push_back(use2);
    }


    void End_TimeSlice()
    {
        PCB * use4;
        use4=this->PCB_On_Runing;
        this->PCB_On_Runing=NULL;
        this->Flag_Is_Running=0;
        use4->State=STATE_READY;
        this->SPCB_Ready_Queue.push_back(use4);
    }

    void Kill_Process(int ID)
    {

        PCB *use5;
        list<PCB *>::iterator it;
        for (it = this->SPCB_Queue.begin(); it != this->SPCB_Queue.end(); it++)
        {
            PCB *use6 = *it;
            if (use6->Identifier == ID)
            {
                this->SPCB_Queue.erase(it);
                use5 = use6;
                break;
            }
        }
        if(use5->State==STATE_READY) {
            for (it = this->SPCB_Ready_Queue.begin(); it != this->SPCB_Ready_Queue.end(); it++) {
                PCB *use6 = *it;
                if (use6->Identifier == ID) {
                    this->SPCB_Queue.erase(it);
                    break;
                }
            }
        }
        else if(use5->State==STATE_WAITING)
        {
            for (it = this->SPCB_Wating_Queue.begin(); it != this->SPCB_Wating_Queue.end(); it++) {
                PCB *use6 = *it;
                if (use6->Identifier == ID) {
                    this->SPCB_Queue.erase(it);
                    break;
                }
            }
        }
        this->SPCB_Pool.push_back(use5);
    }


    void Suspend_Process()
    {
        PCB *use7=this->PCB_On_Runing;
        this->PCB_On_Runing=NULL;
        this->Flag_Is_Running=0;
        use7->State=STATE_WAITING;
        use7->I_O_Status_Info=1;
        this->SPCB_Wating_Queue.push_back(use7);
    }

    void  Active_Process()
    {
        if(this->SPCB_Wating_Queue.size()>0)
        {
            int maxPriority = -1;
            PCB * Maxuse = NULL;
            list<PCB *>::iterator it;
            for (it = this->SPCB_Wating_Queue.begin(); it != this->SPCB_Wating_Queue.end(); it++)
            {
                PCB *use8 = *it;
                if (use8->Priority>maxPriority)
                {
                    maxPriority=use8->Priority;
                    Maxuse=use8;
                }
            }
            for (it = this->SPCB_Wating_Queue.begin(); it != this->SPCB_Wating_Queue.end(); it++)
            {
                PCB *use8 = *it;
                if (use8->Identifier==Maxuse->Identifier)
                {
                    this->SPCB_Wating_Queue.erase(it);
                }
            }
            Maxuse->I_O_Status_Info=0;
            Maxuse->State=STATE_READY;
            this->SPCB_Ready_Queue.push_back(Maxuse);
        }
    }

    int Schedul_Process()
    {
        if(this->Flag_Is_Running==1)
            return 0;
        else
        {
            int maxPriority = -1;
            PCB * Maxuse = NULL;
            list<PCB *>::iterator it;
            for (it = this->SPCB_Ready_Queue.begin(); it != this->SPCB_Ready_Queue.end(); it++)
            {
                PCB *use9 = *it;
                if (use9->Priority>maxPriority)
                {
                    maxPriority=use9->Priority;
                    Maxuse=use9;
                }
            }
            for (it = this->SPCB_Ready_Queue.begin(); it != this->SPCB_Ready_Queue.end(); it++)
            {
                PCB *use9 = *it;
                if (use9->Identifier==Maxuse->Identifier)
                {
                    this->SPCB_Wating_Queue.erase(it);
                }
            }
            Maxuse->State=STATE_RUNNING;
          this->PCB_On_Runing=Maxuse;
            this->Flag_Is_Running=1;
        }
    }

    void Snapshot_CPU()
    {
        {
            std::cout<<"**************************The SnapShot Of CPU**************************"<<std::endl;
            std::cout<<"-----------------------The  PROCESS QUEUE IN CPU-----------------------"<<std::endl;
            std::cout<<"-------------NEW 1 READY 2 RUNNING 3 WAITING 4 TERMINATE 5-------------"<<std::endl;
            list<PCB *>::iterator it;
            for (it = this->SPCB_Queue.begin(); it != this->SPCB_Queue.end(); it++)
            {
                PCB *use10=*it;
                cout<<" $Lis ID."<<use10->Identifier<<" STATE:"<<use10->State<<" PRIORITY:"<<use10->Priority<<" I/O:"<<use10->I_O_Status_Info<<endl;
            }


            std::cout<<"-----------------------------------------------------------------------"<<std::endl;
            std::cout<<"--------------------The  Amount PROCESS POOL IN CPU--------------------"<<std::endl;
            std::cout<<"There are "<<this->SPCB_Pool.size()<<" PCB SPACES Last!"<<std::endl;
            std::cout<<"-----------------------------------------------------------------------"<<std::endl;
            std::cout<<"***********************************************************************"<<std::endl;
        }
    }

};

int main()
{
    Process_Scheduling CPU1;
    char c = '0';
    cout<<"1.创建进程"<<endl;
    cout<<"2.撤销进程"<<endl;
    cout<<"3.时间片到"<<endl;
    cout<<"4.挂起进程"<<endl;
    cout<<"5.激活进程"<<endl;
    cout<<"6.进程结束"<<endl;
    cout<<"-1.退出"<<endl;
   while (1)
   {
       cin>>c;
       if(c=='1')
       {
           CPU1.Init_Process();
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else if(c=='2')
       {
           int ID;
           cout<<"The ID of PCB to kill:";
           cin>>ID;
           cout<<endl;
           CPU1.Kill_Process(ID);
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else if(c=='3')
       {
           CPU1.End_TimeSlice();
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else if(c=='4')
       {
           CPU1.Suspend_Process();
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else if(c=='5')
       {
           CPU1.Active_Process();
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else if(c=='6')
       {
           CPU1.Term_Process();
           CPU1.Schedul_Process();
           CPU1.Snapshot_CPU();
       }
       else
       {
           exit(-1);
       }

   }
    return 0;
}