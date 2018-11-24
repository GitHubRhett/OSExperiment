#include <iostream>
#include <algorithm>
#include <vector>
#define BAD -1
#define EMPTY 0
#define MAXSPACE 1024
#define THRESHOLDVALUE 2
using namespace std;

struct MCB
{
    int StartAddress;//存储块起始地址
    int Length;//存储块长度
    int symbol;//存储块标记
};

bool operator < (MCB m1,MCB m2)
{
    if(m1.StartAddress<m2.StartAddress)
        return 1;
    else
        return 0;
}

class MemoryManagement
{
private:
    vector<MCB> Memory_Free;//空闲内存
    vector<MCB> Memory_Busy;//使用内存
public:
    MemoryManagement()//初始化内存
    {
        MCB mcb1;
        mcb1.StartAddress=0;
        mcb1.Length=MAXSPACE;
        mcb1.symbol=EMPTY;
        this->Memory_Free.push_back(mcb1);
    }

    void FF(int ID,int length)//首次适应策略
    {
         vector<MCB>::iterator it;

        int flag=0;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length>=length)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            MCB mcb2;
            mcb2.symbol=BAD;
            Memory_Busy.push_back(mcb2);
            cout<<"No enough space for "<<ID<<" ! "<<endl;
            return;
        }//检查空闲内存中是否有足够大的存储空间块


        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length>=length)
            {
                if(((*it).Length-length)<=THRESHOLDVALUE)//当分配后的剩余地址小于门限值
                {
                    MCB mcb3 = *it;
                    this->Memory_Free.erase(it);
                    mcb3.symbol=ID;
                    this->Memory_Busy.push_back(mcb3);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                }
                else
                {
                    MCB mcb4 ;
                    mcb4.StartAddress=(*it).StartAddress;
                    mcb4.Length=length;
                    mcb4.symbol=ID;
                    this->Memory_Busy.push_back(mcb4);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                    (*it).StartAddress=(*it).StartAddress+length;
                    (*it).Length=(*it).Length-length;
                }
            }
            break;
        }
    }

    void BF(int ID,int length)
    {
        vector<MCB>::iterator it;

        int flag=0;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length>=length)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            MCB mcb2;
            mcb2.symbol=BAD;
            Memory_Busy.push_back(mcb2);
            cout<<"No enough space for "<<ID<<" ! "<<endl;
            return;
        }//检查空闲内存中是否有足够大的存储空间块


        int MAX=-1;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
           if((*it).Length>=length&&(*it).Length>MAX)
           {
               MAX=(*it).Length;
           }
        }
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length==MAX)
            {
                if(((*it).Length-length)<=THRESHOLDVALUE)//当分配后的剩余地址小于门限值
                {
                    MCB mcb3 = *it;
                    this->Memory_Free.erase(it);
                    mcb3.symbol=ID;
                    this->Memory_Busy.push_back(mcb3);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                }
                else
                {
                    MCB mcb4 ;
                    mcb4.StartAddress=(*it).StartAddress;
                    mcb4.Length=length;
                    mcb4.symbol=ID;
                    this->Memory_Busy.push_back(mcb4);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                    (*it).StartAddress=(*it).StartAddress+length;
                    (*it).Length=(*it).Length-length;
                }
            }
        }

    }

    void WF(int ID,int length)
    {
        vector<MCB>::iterator it;

        int flag=0;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length>=length)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            MCB mcb2;
            mcb2.symbol=BAD;
            Memory_Busy.push_back(mcb2);
            cout<<"No enough space for "<<ID<<" ! "<<endl;
            return;
        }//检查空闲内存中是否有足够大的存储空间块


        int MIN=1025;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length>=length&&(*it).Length<MIN)
            {
                MIN=(*it).Length;
            }
        }
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if((*it).Length==MIN)
            {
                if(((*it).Length-length)<=THRESHOLDVALUE)//当分配后的剩余地址小于门限值
                {
                    MCB mcb3 = *it;
                    this->Memory_Free.erase(it);
                    mcb3.symbol=ID;
                    this->Memory_Busy.push_back(mcb3);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                }
                else
                {
                    MCB mcb4 ;
                    mcb4.StartAddress=(*it).StartAddress;
                    mcb4.Length=length;
                    mcb4.symbol=ID;
                    this->Memory_Busy.push_back(mcb4);
                    sort(this->Memory_Busy.begin(),this->Memory_Busy.end());
                    (*it).StartAddress=(*it).StartAddress+length;
                    (*it).Length=(*it).Length-length;
                }
            }
        }

    }

    void Memory_Recovery(int ID)
    {
        vector<MCB>::iterator it;
        int flag=0;
        for(it=this->Memory_Busy.begin();it!=this->Memory_Busy.end();it++)
        {
            if((*it).symbol==ID) {
                flag = 1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"Recovery failed in can not find "<<ID<<endl;
            return;
        }

        MCB mcb5 = *it;
        this->Memory_Busy.erase(it);

        int flag2=0;//判断是否上邻
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if(((*it).StartAddress+(*it).Length)==mcb5.StartAddress)
            {
                (*it).Length+=mcb5.Length;
                flag2=1;
                break;
            }
        }

        if(flag2==0)
        {
            this->Memory_Free.push_back(mcb5);
            sort(this->Memory_Free.begin(),this->Memory_Free.end());
        }

        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {
            if(((*it).StartAddress+(*it).Length)==(*(it+1)).StartAddress)
            {
                (*it).Length+=(*(it+1)).Length;
                this->Memory_Free.erase((it+1));
            }
        }
    }

    void showmemory()
    {
        vector<MCB>::iterator it;
        cout<<"---------------FREESPACE---------------"<<endl;
        for(it=this->Memory_Free.begin();it!=this->Memory_Free.end();it++)
        {

            cout<<"ADDRESS:"<<(*it).StartAddress<<endl;
            cout<<"LENGTH:"<<(*it).Length<<endl;

        }
        cout<<"---------------------------------------"<<endl;
        cout<<"---------------USEDSPACE---------------"<<endl;
        for(it=this->Memory_Busy.begin();it!=this->Memory_Busy.end();it++)
        {

            cout<<"SYMBOL:"<<(*it).symbol<<endl;
            cout<<"ADDRESS:"<<(*it).StartAddress<<endl;
            cout<<"LENGTH:"<<(*it).Length<<endl;

        }
        cout<<"---------------------------------------"<<endl;
    }
};


int main() {
    MemoryManagement test1,test2,test3;
    int ID1,ID2,ID3,ID4;
    int l1,l2,l3,l4;
    cout<<"ID1"<<endl;
    cin>>ID1;
    cout<<"l1"<<endl;
    cin>>l1;
    cout<<"ID2"<<endl;
    cin>>ID2;
    cout<<"l2"<<endl;
    cin>>l2;
    cout<<"ID3"<<endl;
    cin>>ID3;
    cout<<"l3"<<endl;
    cin>>l3;
    cout<<"ID4"<<endl;
    cin>>ID4;
    cout<<"l4"<<endl;
    cin>>l4;


    cout<<"~~~~~~~~~~~~~~FF~~~~~~~~~~~~~~"<<endl;
    test1.FF(ID1,l1);
    test1.FF(ID2,l2);
    test1.FF(ID3,l3);
    test1.Memory_Recovery(ID2);
    test1.FF(ID4,l4);
    test1.showmemory();
    test1.Memory_Recovery(ID4);
    test1.showmemory();
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

    cout<<"~~~~~~~~~~~~~~BF~~~~~~~~~~~~~~"<<endl;
    test2.BF(ID1,l1);
    test2.BF(ID2,l2);
    test2.BF(ID3,l3);
    test2.Memory_Recovery(ID2);
    test2.BF(ID4,l4);
    test2.showmemory();
    test2.Memory_Recovery(ID4);
    test2.showmemory();
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

    cout<<"~~~~~~~~~~~~~~WF~~~~~~~~~~~~~~"<<endl;
    test3.WF(ID1,l1);
    test3.WF(ID2,l2);
    test3.WF(ID3,l3);
    test3.Memory_Recovery(ID2);
    test3.WF(ID4,l4);
    test3.showmemory();
    test3.Memory_Recovery(ID4);
    test3.showmemory();
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;


    return 0;
}