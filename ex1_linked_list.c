/*
    Example : Linked List (1), Singly linked list 單向鏈結串列
    Reference : 動畫圖解資料結構
    步驟 :
    1) 必須先建立一個新的節點，並且[Head指標]指向新節點
    2) 存放資料10到資料欄位中
    3) 讓新節點的指標欄位指向空節點
*/

#include<stdio.h>
#include<stdlib.h>

//#define NULL 0

typedef struct node{
    int data;           // 資料欄位
    struct node *link;  // 指標欄位
}NODE;

NODE *NewNode(void);    // 宣告一個回傳指標(指向NODE)的函數，功能為建立一個新節點

int main(void) {
    puts("Hello World!");

    printf("===============程式描述====================\n");
    printf("= 程式名稱：ch5-5.1.c =\n");
    printf("= 程式目的：動態配置單向鏈結串列一個節點 =\n");
    printf("===========================================\n");

    int Nodedata;
    NODE *list;             // 指向struct NODE的指標
    list = NewNode();       // 建立一個新節點，並將 NewNode 回傳的記憶體位置指定給 list
                            // 1) 執行完上述的程式碼，記憶體中就會自動產生一個新節點

    printf("=================輸入======================\n");
    printf("請輸入單一節點內容：");
    scanf("%d",&Nodedata);
    list->data = Nodedata;       // 2) 存放資料 10 到資料欄上面

    list->link = NULL;            // 3) 讓新節點的指標欄位指向空節點

    printf("=================輸出======================\n");
    printf("節點內容為：%d\n",list->data);    // 印出串列的資料欄之內容
    // system("PAUSE"); //用來表示暫停

    return 0;
}

NODE *NewNode(void){    // 建立一個新節點
    NODE *pt;

    // 指標變數 = (資料型態*)malloc(sizeof(資料型態))
    pt = (NODE*)malloc(sizeof(NODE));   // 動態記憶體配置

    if(pt == NULL){
        printf("記憶體空間不足!");
        exit(1);
    }
    return pt; /* 回傳記憶體位置給 list */
}

