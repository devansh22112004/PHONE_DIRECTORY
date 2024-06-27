#include <bits/stdc++.h>
using namespace std;
struct Data{
    string phone_number,name,ID,start_date;
};
struct Node{
    Node* link[37];
    vector<Data> v;
    Node(){
        for(int i=0;i<37;i++){
            link[i]=NULL;
            v.clear();
        }
    }
};
bool isEqual(Data first,Data second){

    if(first.phone_number!=second.phone_number){
        return false;
    }
    if(first.name!=second.name){
        return false;
    }
    if(first.ID!=second.ID){
        return false;
    }
    if(first.start_date!=second.start_date){
        return false;
    }
    return true;
}
int get_index(char a){
    if(a==' '){
        return 36;
    }
    if(a<='9'){
        return a-'0';
    }
    else{
        return a-'A'+10;
    }
}
class Trie{
    public:
    Node* root;
    void insert_data(string name,string phone_number,Data add){
        Node* cur=root;
        int l1=name.length();
        for(int i=0;i<l1;i++){
            int idx=get_index(name[i]);
            if(cur->link[idx]==NULL){
                cur->link[idx]=new Node();
            }
            cur=cur->link[idx];
        }
        cur->v.push_back(add);
        cur=root;
        int l2=phone_number.length();
        for(int i=0;i<l2;i++){
            int idx=get_index(phone_number[i]);
            if(cur->link[idx]==NULL){
                cur->link[idx]=new Node();
            }
            cur=cur->link[idx];
        }
        cur->v.push_back(add);
        cout<<"DETAILS SUCCESFULLY ADDED!\n";
    }
    void add_required_details(Node* cur,vector<Data>& answer){
        for(auto x:cur->v){
            answer.push_back(x);
        }
        for(int i=0;i<37;i++){
            if(cur->link[i]!=NULL){
                add_required_details(cur->link[i],answer);
            }
        }
    }
    void get_details(string info, vector<Data>& answer){
        Node* cur=root;
        int length=info.length();
        for(int i=0;i<length;i++){
            cur=cur->link[get_index(info[i])];
            if(cur==NULL){
                return;
            }
        }
        add_required_details(cur,answer);
    }
    void erase_details(string phone_number){
        Node* cur=root;
        bool flag=true;
        int length=phone_number.length();
        for(int i=0;i<length;i++){
            if(cur->link[get_index(phone_number[i])]==NULL){
                flag=false;
                break;
            }
            cur=cur->link[get_index(phone_number[i])];
        }
        if(flag==false){
            cout<<"NO DATA FOUND!\n";
            return;
        }
        if(cur->v.empty()){
            cout<<"NO DATA FOUND!\n";
            return;
        }
        string name=cur->v.front().name;
        cur->v.clear();
        cur=root;
        length=name.length();
        for(int i=0;i<length;i++){
            cur=cur->link[get_index(name[i])];
        }
        vector<Data> temp;
        for(auto x:cur->v){
            if(phone_number==x.phone_number){
                flag=false;
                continue;
            }
            else{
                temp.push_back(x);
            }
        }
        cur->v.clear();
        for(auto x:temp){
            cur->v.push_back(x);
        }
        cout<<"DATA DELETED SUCCESSFULLY!\n";
    }
};
class User{
    public:
    Trie *t=new Trie();
    void do_the_work(){
        t->root=new Node();
        cout<<"                        WELCOME TO THE DIRECTORY!!!!"<<endl;
        cout<<"FOR ADDING DATA: TYPE 1"<<endl;
        cout<<"FOR ACCESSING INFORMATION: TYPE 2"<<endl;
        cout<<"FOR ERASING DATA: TYPE 3"<<endl;
        cout<<"FOR AN EXIT: TYPE 4"<<endl;
        while(1){
            int input;
            cout<<"ENTER YOUR CHOICE: "<<endl;
            cin>>input;
            if(input==1){
                take_input();
            }
            else if(input==2){
                get_the_data();
            }
            else if(input==3){
                erase_data();
            }
            else{
                break;
            }
        }
        cout<<endl;
        cout<<"THANK YOU FOR USING THE DIRECTORY!!"<<endl;
        cout<<"                                                MADE BY:- DEVANSH LADHA"<<endl;
    }
    void display_data(Data v){
        cout<<"NAME: "<<v.name<<endl;
        cout<<"PHONE NUMBER: "<<v.phone_number<<endl;
        cout<<"ID: "<<v.ID<<endl;
        cout<<"START DATE: "<<v.start_date<<endl;
    }
    void get_the_data(){
        vector<Data> answer=find_data();
        int count=1;
        cout<<endl;
        for(auto x:answer){
            cout<<count++<<"."<<endl;
            display_data(x);
            cout<<endl;
        }
        if(count==1){
            cout<<endl;
            cout<<"NO DATA TO BE DISPLAYED!"<<endl;
        }
        cout<<endl;
    }
    void take_input(){
        Data input;
        cout<<"ENTER THE NAME: ";
        getline(cin>>ws,input.name);
        for(auto &x: input.name){
            if(x!=' ')
            x=toupper(x);
        }
        cout<<"ENTER THE PHONE NUMBER: ";
        cin>>input.phone_number;
        cout<<"ENTER THE ID: ";
        cin>>input.ID;
        cout<<"ENTER THE START DATE: ";
        cin>>input.start_date;
        add_input(input);
    }
    void add_input(Data input){
        t->insert_data(input.name,input.phone_number,input);
    }
    vector<Data> find_data(){
        vector<Data> answer;
        string info;
        cout<<"ENTER THE INFORMATION: ";
        getline(cin>>ws,info);
        for(auto &x: info){
            if(x!=' '&&x>'9')
            x=toupper(x);
        }
        //cout<<info<<endl;
        t->get_details(info,answer);
        return answer;
    }
    void erase_data(){
        string info;
        cout<<"ENTER THE PHONE NUMBER TO BE DELETED: ";
        cin>>info;
        t->erase_details(info);
    }
};
int main(){
    User* u1=new User();
    u1->do_the_work();
}