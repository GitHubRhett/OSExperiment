#include <iostream>
#include <vector>
#define USERNUM 10//用户数
#define FILENUM 10//文件数
#define OPENNUM 5 //打开文件上限
using namespace std;
using std::string;

struct FCB
{
    std::string Filename;//文件名
    string Authority;//存取权限
    string Content;//文件内容
    bool Is_Open;//文件是否被打开
};


class User
{
private:
    string User_Name;//用户命
    string Psw;//用户密码
    bool Is_Log;//是否登陆
    vector<FCB>UFD;//用户文件目录
    int Open_Num;//打开文件数
public:
    User(string Name,string Psw1)
    {
        this->User_Name=Name;
        this->Psw=Psw1;
        this->Is_Log=0;
        this->Open_Num=0;
    }

    bool CREATE()//创建文件
    {
        if(this->UFD.size()<FILENUM)
        {
            FCB f;
            cout<<"Please Name The New Film:";
            string name;
            cin>>name;
            f.Filename=name;
            cout<<endl;
            cout<<"Set The Authority Of The New Film"<<endl;
            cout<<"form as 'rwx' (1-Yes/0-No):";
            string authority;
            cin>>authority;
            f.Authority=authority;
            cout<<endl;
            f.Is_Open=0;
            this->UFD.push_back(f);
            return 1;
        }
        else
        {
            cout<<"No File Space!!!"<<endl;
            return 0;
        }
    }


    bool Open()
    {
        if(this->Open_Num< OPENNUM)
        {
            cout << "Please Enter The Filename You Want To Open:";
            string filename;
            cin >> filename;
            cout << endl;

            bool flag = 0;
            vector<FCB>::iterator it;
            for (it = this->UFD.begin(); it != UFD.end(); ++it) {
                if ((*it).Filename.compare(filename) == 0) {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0) {
                cout << "File did not exist!!!" << endl;
                return 0;
            } else {
                (*it).Is_Open = 1;
                //cout << "File Open Success~" << endl;
                this->Open_Num++;
                return 1;
            }
        }
        else
        {
            cout<<"Open File Overflow!!!"<<endl;
            return 0;
        }
        return 0;

    }

    bool Read()
    {
        cout<<"Please Enter The Filename You Want To Read:";
        string filename;
        cin>>filename;
        cout<<endl;

        bool flag = 0;
        vector<FCB>::iterator it;
        for (it=this->UFD.begin(); it!=UFD.end() ; ++it)
        {
            if((*it).Filename.compare(filename)==0)
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            cout<<"File did not exist!!!"<<endl;
            return 0;
        }
        else
        {
            if((*it).Is_Open==1)
            {
                if ((*it).Authority[0] == '1') {
                    cout<<"CONTENCE : "<<endl;
                    cout << "File " << (*it).Filename << " : " << (*it).Content << endl;
                    return 1;
                } else {
                    cout << "No Permission To Read The File!!!" << endl;
                    return 0;
                }
            }
            else
            {
                cout<<"File Not Open!!!"<<endl;
                return 0;
            }
        }
    }

    bool Write()
    {
        cout<<"Please Enter The Filename You Want To Write:";
        string filename;
        cin>>filename;
        cout<<endl;

        bool flag = 0;
        vector<FCB>::iterator it;
        for (it=this->UFD.begin(); it!=UFD.end() ; ++it)
        {
            if((*it).Filename.compare(filename)==0)
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            cout<<"File did not exist!!!"<<endl;
            return 0;
        }
        else
        {
            if((*it).Is_Open==1)
            {
                if ((*it).Authority[1] == '1') {
                    cout<<"Please Edit Your Passage : "<<endl;
                      cin>> (*it).Content;
                    cout<<"Write finished~"<<endl;
                    return 1;
                } else {
                    cout << "No Permission To Write The File!!!" << endl;
                    return 0;
                }
            }
            else
            {
                cout<<"File Not Open!!!"<<endl;
                return 0;
            }
        }
    }

    bool Close()
    {
        cout<<"Please Enter The Filename You Want To Close:";
        string filename;
        cin>>filename;
        cout<<endl;

        bool flag = 0;
        vector<FCB>::iterator it;
        for (it=this->UFD.begin(); it!=UFD.end() ; ++it)
        {
            if((*it).Filename.compare(filename)==0)
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            cout<<"File did not exist!!!"<<endl;
            return 0;
        }
        else
        {
            (*it).Is_Open=0;
            cout<<filename<<" has been close~"<<endl;
            this->Open_Num--;
            return 1;
        }
        return 0;

    }


    bool Delete()
    {
        cout<<"Please Enter The Filename You Want To Delete:";
        string filename;
        cin>>filename;
        cout<<endl;

        bool flag = 0;
        vector<FCB>::iterator it;
        for (it=this->UFD.begin(); it!=UFD.end() ; ++it)
        {
            if((*it).Filename.compare(filename)==0)
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            cout<<"File did not exist!!!"<<endl;
            return 0;
        }
        else
        {
            if((*it).Is_Open==1)
            {
                this->Open_Num--;
            }
            this->UFD.erase(it);
            cout<<filename<<" has been delete~"<<endl;
            return 1;
        }
        return 0;

    }

    bool list()
    {
        vector<FCB>::iterator it;
        cout<<"^^^^^^^^^^^^^^File-List^^^^^^^^^^^^^^"<<endl;
        for(it=this->UFD.begin();it!=this->UFD.end();it++)
        {
            cout<<" Filename "<<(*it).Filename<<endl;
        }
        cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    }

    friend class MFD;
};

class MFD
{
private:
    vector<User>MFD_Users;//主文件目录
    string Pre_User;
public:
    MFD()
    {
        this->Pre_User="";
    }//MDF初始化

    bool Create_User()//创建新用户
    {
        if(this->MFD_Users.size()<USERNUM)
        {

            cout<<"Please Enter Your User Name:";
            string New_Name;
            cin>>New_Name;
            cout<<endl;
            cout<<"Please Set Your Password"<<endl;
            cout<<"(If you don't want to set,just use '0'):";
            string NewPsw;
            cin>>NewPsw;
            cout<<endl;
            User user1(New_Name,NewPsw);
            this->MFD_Users.push_back(user1);
            cout<<New_Name<<"Create Successful~"<<endl;
            return Login(New_Name);
        }
        else
        {
            cout<<"No User Space!!!"<<endl;
            return 0;
        }

    }

    bool Login(string Username_log)//用户登陆
    {
        vector<User>::iterator it;
        bool flag=0;
        for (it=this->MFD_Users.begin(); it!=this->MFD_Users.end() ; ++it)
        {
         if((*it).User_Name.compare(Username_log)==0)
         {
             flag=1;
             break;
         }
        }


        if(flag==0)
        {
            cout<<"No User Name "<<Username_log<<" In System !"<<endl;
            cout<<"Would You Like To Create A New User In System?"<<endl;
            cout<<"(1-Yes/0-No:)";
            bool choose;
            cin>>choose;
            cout<<endl;
            if(choose)
            {
                return this->Create_User();
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if((*it).Is_Log==1)
            {
                cout<<"User Had Already OnLine"<<endl;
                return 1;
            }
            else
            {
                if((*it).Psw.compare("0")==0)
                {
                    (*it).Is_Log=1;
                    this->Pre_User=Username_log;
                    return 1;
                }
                cout<<"Please Input Your Password:";
                string pswcheck;
                cin>>pswcheck;
                cout<<endl;
                int check = (*it).Psw.compare(pswcheck);
                if(check==0)
                {
                    (*it).Is_Log=1;
                    this->Pre_User=Username_log;
                    return 1;
                }
                else
                {
                    cout<<"Password Error!!!"<<endl;
                    return 0;
                }
            }
        }
        return 0;
    }


    bool Quit()//退出当前用户
    {
          if(this->Pre_User.compare("")==0)
          {
              cout<<"No User Online!!!"<<endl;
              return 0;
          }
          else
          {
              vector<User>::iterator it;
              bool flag=0;
              for (it=this->MFD_Users.begin(); it!=this->MFD_Users.end() ; ++it)
              {
                  if((*it).User_Name.compare(Pre_User)==0)
                  {
                      (*it).Is_Log=0;
                      break;
                  }
              }
              this->Pre_User="";
              return 1;
          }
    }



    void Ope()
    {


        vector<User>::iterator global_it;
        bool flag=0;
        if(this->Pre_User.compare("")==0)
        {
            cout<<"No User Online!!!"<<endl;
            return;
        }
        else
        {
            vector<User>::iterator it;

            for (it=this->MFD_Users.begin(); it!=this->MFD_Users.end() ; ++it)
            {
                if((*it).User_Name.compare(Pre_User)==0)
                {
                    flag=1;
                    global_it=it;
                    break;
                }
            }
        }

        if(flag==0)
        {
            cout<<"User Error!!!"<<endl;
            return;
        }

        cout<<"------------File Operater List:------------"<<endl;
        cout<<"------------1-Create()---------------------"<<endl;
        cout<<"------------2-Open()-----------------------"<<endl;
        cout<<"------------3-Read()-----------------------"<<endl;
        cout<<"------------4-Write()----------------------"<<endl;
        cout<<"------------5-Close()----------------------"<<endl;
        cout<<"------------6-Delete()---------------------"<<endl;
        cout<<"------------7-List()-----------------------"<<endl;
        cout<<"------------(-1)-EXIT----------------------"<<endl;
        int choose = 0;
        while(1)
        {
            cout<<"Enter File Operater choose NO.:";
            cin>>choose;
            cout<<endl;
            if(choose==1)
            {
                (*global_it).CREATE();
            }
            else if(choose==2)
            {
                (*global_it).Open();
            }
            else if(choose==3)
            {
                (*global_it).Read();
            }
            else if(choose==4)
            {
                (*global_it).Write();
            }
            else if(choose==5)
            {
                (*global_it).Close();
            }
            else if(choose==6)
            {
                (*global_it).Delete();
            }
            else if(choose==7)
            {
                (*global_it).list();
            }
            else
            {
                return;
            }

        }
    }


    string Show_PreUser()
    {
        return this->Pre_User;
    }


};


int main()
{
    MFD System_1;
    cout<<"------------User Operater List:------------"<<endl;
    cout<<"------------1-Create()---------------------"<<endl;
    cout<<"------------2-Login()----------------------"<<endl;
    cout<<"------------3-Quit()-----------------------"<<endl;
    cout<<"------------4-Ope()------------------------"<<endl;
    cout<<"------------5-Show_PreUser()---------------"<<endl;
    cout<<"------------(-1)-EXIT----------------------"<<endl;
    int choose = 0;
    while(1)
    {
        cout<<"Enter User Operater choose NO.:";
        cin>>choose;
        cout<<endl;
        if(choose==1)
        {
           System_1.Create_User();
        }
        else if(choose==2)
        {
            if(System_1.Show_PreUser().compare("")!=0)
            {
                cout<<"Aready User Online!!!"<<endl;
                cout<<"Must Quit First"<<endl;
                continue;
            } else
            {
                cout<<"Enter Your Username";
                string username;
                cin>>username;
                cout<<endl;
                System_1.Login(username);
            }
        }
        else if(choose==3)
        {
            System_1.Quit();
        }
        else if(choose==4)
        {
            System_1.Ope();
        }
        else if(choose==5)
        {
           cout<<"Present-User : "<<System_1.Show_PreUser()<<endl;
        }
        else
        {
            exit(0);
        }

    }
    return 0;
}