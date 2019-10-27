/*                                                                          
# 編譯和執行步驟 : 

1) g++ hello.cpp -o hello
2) ./hello

===============================
# 執行結果 : 

cc@pthread_sample$./hello

===============================
參考文件 : 191027，可以執行
Doubly LinkedList(雙向鏈結串列)
https://sites.google.com/site/paothsungchen/learning/code/doubly-linkedlist

*/  

#include <iostream>
using namespace std;

struct node{
    int data;
    node *next;
    node *before;
};

node *NewNode(){
    node *pt;
    pt = new node ;
    if(pt == NULL){
    cout<<"FULL !"<<endl;
//    exit(1);
}
return pt;
}

void content(node *head, node *tail){
    node *pt=head;
    while(pt!=tail){
        cout<<pt->data<<" ";
        pt = pt->next;
    }
    cout<<endl;
}

void show_all(node *head, node *tail){
    node *pt=head;
    int count=0;
    while(pt!=tail){
        pt = pt->next;
        count++;
    }
    cout<<"目前在第"<<count<<"個節點，"<<"資料內容是"<<pt->before->data<<endl; 
}


int main(){
    
    bool flag=true;
    int choose;
    int data;
    node *head,*temp,*tail,*newtemp;

    head=NewNode();
    head->before = NULL;
    temp = head;
    temp->next=NULL;
    while(flag){
        
        cout<<"選擇動作 [1]插入資料 [2]刪除資料 [3]顯示串列內容 [4]顯示串列節點及資料內容 [5] 往上一個節點 [6]離開 :" <<endl; 
        
        cin>>choose;
        
        switch (choose){
            
            case 1 :
            
            cout<<"請輸入資料 :";
            cin>>data; 
            
            if(temp->next!=NULL){
                //按順序插入 
                if(temp==tail){
                    temp->data = data ;
                    temp->next=NewNode();
                    tail=temp->next;
                    tail->before =temp;
                    temp->next=tail;
                    temp = temp->next;
                    } 
                //中途插入 
                else{
                    newtemp=NewNode();
                    newtemp->data = data;
                    temp->next->before=newtemp;
                    newtemp->next=temp->next;
                    temp->next=newtemp;
                    newtemp->before=temp;
                }

                break;
            }
            else{
                temp->data = data ;
                temp->next=NewNode();
                tail=temp->next;
                tail->before =temp;
                temp->next=tail;
                temp = temp->next;
                break;
            }

            //break;
            // temp->before = 
            case 2 :
            
            cout<<"刪除目前資料 "<<endl;
            if(temp==tail){
                temp=temp->before;
                temp->next=NULL;
                tail=temp;
            }
            else if(temp==head){
                if(head->next==NULL){
                    head=NULL;
                    cout<<"節點已清空。"<<endl; 
                }
            else {
                temp=temp->next;
                temp->before=NULL;
                head=temp;
                }
            }
            else{
                temp=temp->before;
                temp->next=temp->next->next;
                temp->next->next->before=temp;
            }
            break;
            
            case 3 :
            
            cout<<"目前串列內容包括 : ";
            content(head,tail);
            break;
            
            case 4 :
            show_all(head,temp);
            break;
            
            case 5 :
            temp =tail->before;
            break;
            
            case 6 :
            flag = false;
            break;
            
            defaut :
            flag = false ;
            break ;
            
        } 

    }

}
