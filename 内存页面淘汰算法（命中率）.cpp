#include <iostream>
#include <vector>

using namespace std;





struct Page
{
    int Flag;//标志位
    int No_Page;//页号
};

class Page_Schedule
{
private:
    vector<Page>pages;//页框内容队列
    vector<int>Request_Queue;//请求队列
    int LimitNum;//cache页框总数
    int **Table;//结果数组指针
    int TotalNum_Request;//请求数

public:
    Page_Schedule(int n)
    {
        this->LimitNum=n;
        cout<<"Please Input the Request Queue of the Page:"<<endl;
        int m=0;
       do
        {
            cin>>m;
            if(m!=-1) {
                this->Request_Queue.push_back(m);
            }
        }
       while (m!=-1);

       /* vector<int>::iterator itt;
        for (itt = this->Request_Queue.begin();  itt!=this->Request_Queue.end() ; itt++)
        {
           cout<<(*itt)<<endl;
        }
        cout<<"hhh1"<<endl;*/



        this->Table = new int* [this->LimitNum+2];
        for (int i = 0; i <n+2; ++i) {
            this->Table[i] = new int [this->Request_Queue.size()];
        }


        for (int j = 0; j <LimitNum+2 ; ++j) {
            for (int i = 0; i <this->Request_Queue.size() ; ++i) {
                //cout<<"!"<<endl;
                this->Table[j][i]=0;
            }
        }//结果数组置零

//        for(int i=0;i<this->LimitNum+2;i++)
//            for(int j=0;j<this->Request_Queue.size();j++)
//            {
//                if(j==this->Request_Queue.size()-1)
//                    cout<<" "<<Table[i][j]<<endl;
//                else
//                    cout<<" "<<Table[i][j];
//            }

        this->TotalNum_Request=this->Request_Queue.size();
    }



    Page_Schedule(Page_Schedule &p1)
    {
        this->LimitNum=p1.LimitNum;

       this->Request_Queue=p1.Request_Queue;

        this->Table = new int* [this->LimitNum+2];
        for (int i = 0; i <this->LimitNum+2; ++i) {
            this->Table[i] = new int [this->Request_Queue.size()];
        }


        for (int j = 0; j <LimitNum+2 ; ++j) {
            for (int i = 0; i <this->Request_Queue.size() ; ++i) {
                //cout<<"!"<<endl;
                this->Table[j][i]=0;
            }
        }//结果数组置零

        this->TotalNum_Request=this->Request_Queue.size();
    }


    void OPT()
    {
        //cout<<"called OPT"<<endl;
        vector<int>::iterator itt;
        int ll=0;
        for (itt = this->Request_Queue.begin();  itt!=this->Request_Queue.end() ; itt++)
        {
         Table[0][ll]=*itt;
            ll++;
        }

        while(!this->Request_Queue.empty())
        {

            if (this->pages.size() < this->LimitNum && !this->Request_Queue.empty()) {

                vector<Page>::iterator it0;
                int flag = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {

                    Page p1;
                    p1.No_Page = this->Request_Queue.front();
                    this->Request_Queue.erase(this->Request_Queue.begin());
                    this->pages.push_back(p1);
                    vector<Page>::iterator it = this->pages.begin();
                    int count1 = 1;
                    for (; it != this->pages.end(); it++) {
                        this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = (*it).No_Page;
                        count1++;
                    }
                    this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = 0;
                } else {

                    this->Request_Queue.erase(this->Request_Queue.begin());
                    int i;
                    for (i = 0; i < this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
            else if (this->pages.size() == this->LimitNum && !this->Request_Queue.empty())
            {

                vector<Page>::iterator it0;
                int flag1 = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag1 = 1;
                        break;
                    }
                }
                if (flag1 == 0)//匹配失败
                {

                    vector<Page>::iterator it1;
                    vector<int>::iterator it2;

                    for (it1 = this->pages.begin(); it1 != this->pages.end(); it1++)
                    {
                        int count2 = 1;//记录距离
                        int findflag=0;
                        for (it2 = this->Request_Queue.begin() + 1; it2 != this->Request_Queue.end(); it2++)
                        {
                            if (*it2 == (*it1).No_Page) {
                                (*it1).Flag = count2;
                                findflag=1;
                                break;
                            }
                            count2++;
                        }
                        if(findflag==0)
                        {
                            (*it1).Flag = count2 + 1;
                        }
                    }

//                    cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
//                    for (it1 = this->pages.begin(); it1 != this->pages.end(); ++it1) {
//                        cout<<"  NO"<<(*it1).No_Page<<endl;
//                        cout<<"  Flag"<<(*it1).Flag<<endl;
//                    }
//                    cout<<"+++++++++++++++++++++++++++++++++++++++"<<endl;
                    int max = 0;
                    for (it1 = this->pages.begin(); it1 != this->pages.end(); ++it1) {
                        if ((*it1).Flag > max)
                            max = (*it1).Flag;
                    }



                    for (it1 = this->pages.begin(); it1 != this->pages.end(); ++it1) {
                        if ((*it1).Flag == max) {
                            Page p2;
                            p2.No_Page = this->Request_Queue.front();
                            p2.Flag=0;
                            (*it1)=p2;
                            this->Request_Queue.erase(this->Request_Queue.begin());
                            break;
                        }
                    }

                    vector<Page>::iterator it3 = this->pages.begin();
                    int count1 = 1;
                    for (; it3 != this->pages.end(); it3++) {
                        this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = (*it3).No_Page;
                        count1++;
                    }
                    this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = 0;

                }
                else//匹配成功
                {

                    this->Request_Queue.erase(this->Request_Queue.begin());
                    int i;
                    for (i = 0; i <this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
        }
    }

    void FIFO()
    {
        //cout<<"called FIFO"<<endl;
        vector<int>::iterator itt;
        int ll=0;
        for (itt = this->Request_Queue.begin();  itt!=this->Request_Queue.end() ; itt++)
        {
            Table[0][ll]=*itt;
            ll++;
        }

        while(!this->Request_Queue.empty())
        {

            if (this->pages.size() < this->LimitNum && !this->Request_Queue.empty()) {

                vector<Page>::iterator it0;
                int flag = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    Page p1;
                    p1.No_Page = this->Request_Queue.front();
                    p1.Flag=0;
                    this->Request_Queue.erase(this->Request_Queue.begin());
                    this->pages.push_back(p1);

                    vector<Page>::iterator it5;
                    for (it5 = this->pages.begin(); it5 != this->pages.end(); it5++) {
                        (*it5).Flag++;
                    }//计数加一

                    vector<Page>::iterator it = this->pages.begin();
                    int count1 = 1;
                    for (; it != this->pages.end(); it++) {
                        this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = (*it).No_Page;
                        count1++;
                    }
                    this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = 0;
                }
                else
                {

                    this->Request_Queue.erase(this->Request_Queue.begin());

                    vector<Page>::iterator it6;
                    for (it6 = this->pages.begin(); it6!= this->pages.end(); it6++) {
                        (*it6).Flag++;
                    }//计数加一

                    int i;
                    for (i = 0; i <this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
            else if (this->pages.size() == this->LimitNum && !this->Request_Queue.empty())
            {

                vector<Page>::iterator it0;
                int flag1 = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag1 = 1;
                        break;
                    }
                }
                if (flag1 == 0)//匹配失败
                {
                    int max=-1;

                    vector<Page>::iterator it8;
                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++)
                    {
                        if((*it8).Flag>max)
                        {
                            max=(*it8).Flag;
                        }
                    }

                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++)
                    {
                        if((*it8).Flag==max)
                        {
                            Page p3;
                            p3.No_Page = this->Request_Queue.front();
                            p3.Flag=0;
                            (*it8)=p3;
                            this->Request_Queue.erase(this->Request_Queue.begin());
                            break;
                        }
                    }

                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++) {
                        (*it8).Flag++;
                    }//计数加一

                    int count2 = 1;
                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++) {
                        this->Table[count2][TotalNum_Request - this->Request_Queue.size() - 1] = (*it8).No_Page;
                        count2++;
                    }
                    this->Table[count2][TotalNum_Request - this->Request_Queue.size() - 1] = 0;

                }
                else//匹配成功
                {

                    this->Request_Queue.erase(this->Request_Queue.begin());

                    vector<Page>::iterator it7;
                    for (it7 = this->pages.begin(); it7 != this->pages.end(); it7++) {
                        (*it7).Flag++;
                    }//计数加一

                    int i;
                    for (i = 0; i <this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
        }
    }

    void LRU()
    {
        //cout<<"called LRU"<<endl;
        vector<int>::iterator itt;
        int ll=0;
        for (itt = this->Request_Queue.begin();  itt!=this->Request_Queue.end() ; itt++)
        {
            Table[0][ll]=*itt;
            ll++;
        }

        while(!this->Request_Queue.empty())
        {

            if (this->pages.size() < this->LimitNum && !this->Request_Queue.empty()) {

                vector<Page>::iterator it0;
                int flag = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag = 1;
                        (*it0).Flag=0;
                        break;
                    }
                }
                if (flag == 0)
                {
                    Page p1;
                    p1.No_Page = this->Request_Queue.front();
                    p1.Flag=0;
                    this->Request_Queue.erase(this->Request_Queue.begin());
                    this->pages.push_back(p1);

                    vector<Page>::iterator it5;
                    for (it5 = this->pages.begin(); it5 != this->pages.end(); it5++) {
                        (*it5).Flag++;
                    }//计数加一

                    vector<Page>::iterator it = this->pages.begin();
                    int count1 = 1;
                    for (; it != this->pages.end(); it++) {
                        this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = (*it).No_Page;
                        count1++;
                    }
                    this->Table[count1][TotalNum_Request - this->Request_Queue.size() - 1] = 0;
                }
                else
                {

                    this->Request_Queue.erase(this->Request_Queue.begin());

                    vector<Page>::iterator it6;
                    for (it6 = this->pages.begin(); it6!= this->pages.end(); it6++) {
                        (*it6).Flag++;
                    }//计数加一

                    int i;
                    for (i = 0; i <this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
            else if (this->pages.size() == this->LimitNum && !this->Request_Queue.empty())
            {

                vector<Page>::iterator it0;
                int flag1 = 0;
                for (it0 = this->pages.begin(); it0 != this->pages.end(); it0++) {
                    if ((*it0).No_Page == this->Request_Queue.front()) {
                        flag1 = 1;
                        (*it0).Flag=0;
                        break;
                    }
                }
                if (flag1 == 0)//匹配失败
                {
                    int max=-1;

                    vector<Page>::iterator it8;
                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++)
                    {
                        if((*it8).Flag>max)
                        {
                            max=(*it8).Flag;
                        }
                    }

                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++)
                    {
                        if((*it8).Flag==max)
                        {
                            Page p3;
                            p3.No_Page = this->Request_Queue.front();
                            p3.Flag=0;
                            (*it8)=p3;
                            this->Request_Queue.erase(this->Request_Queue.begin());
                            break;
                        }
                    }

                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++) {
                        (*it8).Flag++;
                    }//计数加一

                    int count2 = 1;
                    for (it8 = this->pages.begin(); it8 != this->pages.end(); it8++) {
                        this->Table[count2][TotalNum_Request - this->Request_Queue.size() - 1] = (*it8).No_Page;
                        count2++;
                    }
                    this->Table[count2][TotalNum_Request - this->Request_Queue.size() - 1] = 0;

                }
                else//匹配成功
                {

                    this->Request_Queue.erase(this->Request_Queue.begin());

                    vector<Page>::iterator it7;
                    for (it7 = this->pages.begin(); it7 != this->pages.end(); it7++) {
                        (*it7).Flag++;
                    }//计数加一

                    int i;
                    for (i = 0; i < this->LimitNum; ++i) {
                        this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = this->Table[i + 1][
                                TotalNum_Request - this->Request_Queue.size() - 2];
                    }
                    this->Table[i + 1][TotalNum_Request - this->Request_Queue.size() - 1] = 1;//匹配成功
                }
            }
        }
    }




    void show()
    {
        cout<<"   请求页号队列          :";

        for(int i=0;i<this->LimitNum+2;i++)
            for(int j=0;j<TotalNum_Request;j++)
            {
                if(j==this->TotalNum_Request-1&&i<LimitNum)
                {
                    cout<<" "<<Table[i][j]<<endl;
                    cout<<"      Page"<<i+1<<"            :";
                }
                else if(j==this->TotalNum_Request-1&&i==LimitNum)
                {
                    cout<<" "<<Table[i][j]<<endl;
                    cout<<"是否匹配匹配成功（1Y／0N）:";
                }
                else
                    cout<<" "<<Table[i][j];
            }
        int count=0;
        for(int i=0;i<this->TotalNum_Request;i++)
        {
            if(Table[this->LimitNum+1][i]==0)
                count++;
        }
        cout<<endl;
        cout<<"共产生缺页中断（次）："<<count<<endl;

    }
    
};


int main()
{
    int n=4;
    Page_Schedule test1(n);
    Page_Schedule test2(test1);
    Page_Schedule test3(test1);
    test1.OPT();
    cout<<"**********************OPT**********************"<<endl;
    test1.show();
    cout<<endl;
    cout<<"***********************************************"<<endl;


    test2.FIFO();
    cout<<"**********************FIFO**********************"<<endl;
    test2.show();
    cout<<endl;
    cout<<"***********************************************"<<endl;


    test3.LRU();
    cout<<"**********************LRU**********************"<<endl;
    test3.show();
    cout<<endl;
    cout<<"***********************************************"<<endl;

    return 0;
}

