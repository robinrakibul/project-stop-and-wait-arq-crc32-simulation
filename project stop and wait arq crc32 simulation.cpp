using namespace std;
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#define TIME 500

string errortry(string str);
void opening();
void display();

//Sender work
class sending{
    string data;
    string divisor = "10001111001100110010101011111110";
    string frame;
    int st = 0;
public:
    void generate_data(){
        for(int i=0;i<1000;i++){
            int random=rand()%2;
            int f=random;
            char c=f+'0';
            this->data =data+c;
        }
    }

    void CRCcheck(){
        string temp;
        int k = this->st;
        while(this->st<(k+100)){
            temp=temp+(this->data[st]);
            this->st++;
        }
        frame=temp;
        int d=this->divisor.size();
        for(int i=0;i<d-1;i++){
            temp=temp+'0';
        }
        for(int i=0; i<=temp.size()-d; i++){
            for(int j=0; j<d; j++){
                if(temp[i+j] == divisor[j])
                    temp[i+j] = '0';
                else
                    temp[i+j] = '1';
            }
            while(i==temp.size() && temp[i]==1)
                i++;
        }
        for(int i=temp.size()-d+1; i<temp.size(); i++)
            frame += temp[i];
    }
    string getframe(){
        return this->frame;
    }
    string getdata(){
        return this->data;
    }
    void showdata(){
        cout<<this->data<<endl<<endl;
    }
};

//Receiver work
class receiving{
    string data;
    string divisor = "10001111001100110010101011111110";
    string frame;
    int ACK=0;
public:
    int receive_frame(int i, string f){
        string temp;
        if(i < ACK){
            cout<<"\t\t\t\t\t\tDuplicate Data Received... ";
  cout<<"Ignoring One..."<<endl;
            Sleep(TIME);
          cout<<"\t\t\t\t\t\tAcknowledgment sent for Frame: ";
  cout<<ACK<<endl<<endl;
            return ACK;
        }
        else{
            this->frame = f;
            temp = f;
        }
        int d = this->divisor.size();
        for(int i=0; i<=temp.size()-d; i++){
            for(int j=0; j<d; j++){
                if(temp[i+j] == divisor[j])
                    temp[i+j] = '0';
                else
                    temp[i+j] = '1';
            }
            while(i==temp.size() && temp[i]==1)
                i++;
        }
        string t;
        for(int i=temp.size()-d+1; i<temp.size(); i++)
            t += temp[i];
        for(int i=0;i<t.size();i++){
            if(t[i]=='1'){
                frame.empty();
                cout<<"\t\t\t\t\t\tFrame: "<<ACK+1;
 cout<<" is lost..."<<endl;
                Sleep(TIME);
                cout<<"\t\t\t\t\t\tResend the Data..."<<endl;
                Sleep(TIME);
                return -1;
            }
        }
        int U=100,L=1;
        int random = (rand() % (U-L+1))+L;
        if(random<20){
            ACK++;
            cout<<"\t\t\t\t\t\tReceived..."<<endl;
          cout<<"\t\t\t\t\t\tAcknowledgment sent for Frame: ";
  cout<<ACK<<endl<<endl;
            addData();
            return 0;
        }
        else{
            ACK++;
            cout<<"\t\t\t\t\t\tReceived..."<<endl;
            Sleep(TIME);
          cout<<"\t\t\t\t\t\tAcknowledgment sent for Frame: ";
  cout<<ACK<<endl<<endl;
            addData();
            return ACK;
        }
    }
    void addData(){
        string d;
        for(int i=0;i<100;i++)
            d += this->frame[i];
        this->data += d;
        return;
    }
    string getdata(){
        return this->data;
    }
    void showdata(){
        cout<<this->data<<endl<<endl;
    }
};


//main
sending S;
receiving R;

int main(){
    time_t t;
    srand(time(&t));
    S.generate_data();
    opening();
    cout<<"................................................................................................"<<endl<<endl;
    cout<<"\tSENDING\t\t\t\t\t\t\t\t\t\tRECEIVING"<<endl;
    cout<<"................................................................................................"<<endl;

    for(int i=0;i<10;i++){

    S.CRCcheck();
    cout<<"................................................................................................"<<endl;
RES:    string str = S.getframe();
        cout<<" Sending Frame: "<<i+1<<endl;
        for(int k=0;k<7;k++){
            cout<<" . ";
            Sleep(TIME);
        }
        cout<<endl;
        string str2 = errortry(str);
        int ACK = R.receive_frame(i,str2);

        if(ACK==-1){
            Sleep(TIME);
            cout<<" Trying to Resend..."<<endl<<endl;
            goto RES;
        }
        else if(ACK==0){
            for(int k=0;k<3;k++){
                cout<<" . "<<endl;
                Sleep(4*TIME);
            }
            cout<<" Timeout...!!!"<<endl;
            Sleep(TIME);
            cout<<" No Acknowledgment received for Frame: ";
  cout<<i+1<<endl<<endl;
            Sleep(TIME);
            cout<<" Resending Data..."<<endl<<endl;
            goto RES;
        }
        else{
            Sleep(TIME);
            cout<<" Acknowledgment received for Frame: ";
  cout<<ACK<<endl<<endl;
            cout<<"................................................................................................"<<endl;
        }
            Sleep(TIME);
    }
    cout<<endl<<endl<<" All Data Received Successfully...!!!";
    cout<<endl;

    system("pause");
    system("cls");
    display();
    getch();
    return 0;
}
string errortry(string str){
    int U=115,L=100;
    int random = (rand()%(U-L+1))+L;
    str[random] = '0';
    return str;
}
void opening(){
    cout<<"\t\t\t\t ->Randomly Generated Data<-"<<endl<<endl;
    S.showdata();
    cout<<endl;
    cout<<"Press Any Key to Start Sending the Data..."<<endl;
    getch();
    system("cls");
}
void display(){
    cout<<"SENT DATA:"<<endl<<endl;
    S.showdata();
    cout<<endl;
    cout<<"RECEIVED DATA:"<<endl<<endl;
    R.showdata();
    cout<<endl;

    if(S.getdata()==R.getdata())
        cout<<"No Error Found, Data received without error."<<endl;
    else
        cout<<"Error Found!!"<<endl;
}
