/*
    Example : Linked List (2), Singly linked list 單向鏈結串列，兩個或以上的節點
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
void PrintLists(NODE*); // 宣告列印兩個或兩個以上串列的內容

int main(void) {
    puts("Hello World!");

    printf("===============程式描述====================\n");
    printf("= 程式名稱：ch5-5.2.c =\n");
    printf("= 程式目的：兩個或兩個以上節點的鏈結串列 =\n");
    printf("===========================================\n");

    int i;
    NODE *head,*temp;   // 宣告 head,temp 為指向結構 NODE 的指標
    head = NewNode( );  // 1) 建立一個新節點，並將 NewNode 回傳的記憶體位置指定給 head

    temp = head;        // 兩個指標指向同一個節點
#if 1
	head->data = 10;			// 2) 加入資料欄位A
	head->link = NULL;

	printf("i = 0, head = %p, head->link = %p, temp = %p, temp->link = %p\n", head, head->link, temp, temp->link);

    for(i = 1; i <= 4; i++)
    {
        temp->link = NewNode( );	// 3) 呼叫建立新節點，並將其連在前一個後面
        temp->link->data = 10+i;	// 4) 加入資料欄位A

		printf("i = %d, temp = %p, temp->link = %p\n", i, temp, temp->link);

        temp = temp->link;			// 5) 將新節點的尾巴變成temp指標，這樣才可以往後長新結點

    }
    temp->link = NULL;

	printf("i = %d, temp = %p, temp->link = %p\n", i, temp, temp->link);
#else
	printf("=================輸入======================\n");
    printf("請輸入串列第1 個資料欄位值：");
    scanf("%d",&head->data);	// 2) 加入資料欄位A
	head->link = NULL;

	printf("i = 0, head = %p, head->link = %p, temp = %p, temp->link = %p\n", head, head->link, temp, temp->link);

    for(i = 1; i <= 4; i++)
    {
        printf("請輸入串列第%d 個資料欄位值：",i+1);
        temp->link = NewNode( );	// 呼叫建立新節點
        scanf("%d",&temp->link->data);
        temp = temp->link;

		printf("i = %d, temp = %p, temp->link = %p\n", i, temp, temp->link);
    }
    temp->link = NULL;
#endif


    printf("=================輸出======================\n");
    PrintLists(head); //呼叫列印兩個或兩個以上串列的內容

    while(head != NULL) {
        NODE *temp;
        temp = head;
        head = head->link;
        free(temp);
    }

//    system("pause");    // 使程式暫停在執行畫面

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

void PrintLists(NODE* head) //列印兩個或兩個以上串列的內容之副程式
{
    NODE *temp=head;
    printf("鏈結串列為："); //印出串列的資料欄之內容

    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->link;
    }

    printf("\n");
}





