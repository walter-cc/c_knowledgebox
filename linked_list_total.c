/*===============================
# 新增編譯和執行步驟 :
gcc pointer_total.c -o test
./test

# 我們可以利用**gcc -E**來觀看程式碼被展開之後的樣子
gcc -E test.c
===============================

# Linked List 可充分而有效的利用可用記憶體空間。我們不該限制使用者在程式執行過程中使用的節點數量，也不該配置過多不會用到的記憶體。我們必須藉由C語言的動態記憶體配置函式「malloc()」來產生新節點。


===============================


===============================*/

#include <stdio.h>
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'
#include <stdlib.h>     // for malloc(), free() functions

#define EXAMPLE 2
/*
1 : e.g. > 簡易單向鏈結串列 (Singly Linked List)
2 : e.g. > 單向鏈結串列 (Singly Linked List) 完整sample code
*/

#define false   0
#define true    1

#if (EXAMPLE == 1)

struct sr
{
    int i ;
    struct sr *p;   // 「自我參考機制」，完成linked list資料結構的重要機制。
};

#endif

#if (EXAMPLE == 2)  // 單向鏈結串列 (Singly Linked List)

struct Node     // 單向鏈結串列 (Singly Linked List)
{
    int data;
    struct Node *link;   // 「自我參考機制」，完成linked list資料結構的重要機制。
};

typedef struct Node node;
typedef node *nodePointer;  // 指向node的pointer

// 配置一個單向鏈結串列(Singly Linked List) 節點(Node)
nodePointer GetNode()
{
    nodePointer NewNode;

    NewNode = (nodePointer) malloc(sizeof(node));   // sizeof(node) : 配置一個節點所需要的記憶體

    if(NewNode == NULL)
        printf("memory is not enough\n");

    return NewNode; // 回傳一個指向node的pointer
}

// 插入新節點在m節點之後，原串列 = L -> m -> a -> NULL
int insertAfter(nodePointer L, nodePointer m, int d)    // L : List Head(第一個節點), m : 被指定的節點, d : 新節點的值
{
    nodePointer n = GetNode();  // 取得一個新節點的address

    if(n == NULL)
        return false;

    // 新節點 n->NULL
    n->data = d;
    n->link = NULL;

    if(m != NULL)
    {
        // 下面兩行順序不可對調
        n->link = m->link;  // L -> m -> a -> NULL 變成 L -> m,  n -> a -> NULL
        m->link = n;        // L -> m,  n -> a -> NULL 變成 L -> m -> n -> a -> NULL
    }
    else    // 串列原本是空串列
        L = n;              // L -> n

    return true;
}

// 循序拜訪整個串列
void LinkListTraverse(nodePointer L)    // L : List Head(第一個節點)
{
    nodePointer w = L;  // 工作指標w指向第一個節點， 工作指標可移動，概念類似於 for(i = 0;i < x;i++) 的 i

    while(w != NULL)    // 在還沒到達最後一個節點時
    {
        printf("%d \t", w->data);   // 打印所指的節點值
        w = w->link;                // 移動到下一個節點
    }
}

/*
- 刪除m節點，原串列 = L -> m -> a -> NULL
- 刪除m節點錢，必須要先知道m節點的前一個和後一個節點
- m->link : 找m節點的後一個節點
- PreNode : 找m節點的前一個節點，透過迴圈來找。
*/
nodePointer PreNode(nodePointer L, nodePointer m)   // L : List Head(第一個節點), m : 被指定的節點
{
    nodePointer B = L;

    while((B != NULL) && (B->link != m)) // 當還沒到最後一個節點，以及還沒找到m節點的前一個節點時
    {
        B = B->link;        // 移動到下一個節點
    }

    return B;   // 當B為NULL時，表示沒找到m節點，因為 當B為NULL時 = 已經找到最後一個節點了
}

int DeleteNode(nodePointer L, nodePointer m)    // L : List Head(第一個節點), m : 被指定的節點
{
    nodePointer B;

    if(L == m)          // 只有一個節點
        return false;

    B = PreNode(L,m);   //找m節點的前一個節點

    if(B == NULL)       // 當B為NULL時，表示沒找到m節點，因為 當B為NULL時 = 已經找到最後一個節點了
        return false;

    B->link = m->link;  // 把「m的後一個節點」讓給「m的前一個節點的link」
    free(m);            // 然後釋放m節點的記憶體空間

    return true;
}

// 連結兩個單向鏈結串列 (Singly Linked List) L1, L2
nodePointer Concatenate(nodePointer L1, nodePointer L2)
{
    nodePointer w = L1;

    if(w != NULL)   // L1不為空串列
    {
        while(w->link != NULL)  // 當還沒到最後一個節點
            w = w->link;        // 變成 L -> ... -> w -> NULL，將w移動到L1的最後一個節點

        w->link = L2;           // 將L2的頭節點(List Head)連到L1的最後一個節點
    }
    else    // L1原本是空串列
        L1 = L2;

    return L1;
}
#endif

#if (EXAMPLE == 3)
struct DNode    // 雙向鏈結串列 (Doubly Linked List)
{
    int data;
    struct DNode *llink;
    struct DNode *rlink;
}

typedef struct DNode Dnode;
typedef Dnode *DnodePointer;  // 指向Dnode的pointer
#endif


int main(void) {

#if (EXAMPLE == 1)      // first -> sr1 -> sr2 -> NULL

    struct sr *first;      // List Head。一般會使用一個「串列頭(List Head)」來指向頭節點(sr1)。first = &sr1;
    struct sr sr1, sr2;

    first = &sr1;       // 圖示 : first -> sr1
    sr1.i = 10;
    sr1.p = &sr2;       // 圖示 : sr1 -> sr2
    sr2.i = 30;
    sr2.p = NULL;       // 必須指向相同結構體的變數，或是NULL。 sr2 -> NULL
    (*(sr1.p)).i = 40;  // 改變sr2.i的值，*(sr1.p) = sr2

    printf("sr2.i = %d, (*(sr1.p)).i = %d\n", sr2.i, (*(sr1.p)).i);

// 螢幕輸出 >
/*
sr2.i = 40, (*(sr1.p)).i = 40
*/
#endif

    return 0;
}





