/*===============================

# 此檔案為ANSI檔案

# 我們可以利用**gcc -E**來觀看程式碼被展開之後的樣子
gcc -E test.c

# 新增編譯和執行步驟 :

gcc test.c -o test
./test

或

1) gcc -c hello.c                   // 產生目標檔(object file) hello.o
2) gcc -o hello hello.o          // 產生執行檔(execute file) hello
3) ./hello                           // 執行 execute file "hello"

或

gcc -o hello hello.c

===============================
# 此範例可以看到 : 「習」


# 參考文件 :
資料結構初學指引 ─ 入門精要版, 3/e，陳錦輝


# Node = Data field + link field

# 有四種形式 :

    - 單向鏈結串列 (Singly Linked List)

    - 環狀鏈結串列 (Circular Linked List)

    - 雙向鏈結串列 (Doubly Linked List)

    - 雙向環狀鏈結串列 (Circular Doubly Linked List)


# Linked List 特性 : 可充分而有效的利用可用記憶體空間。我們不該限制使用者在程式執行過程中使用的節點數量，也不該配置過多不會用到的記憶體。我們必須藉由C語言的動態記憶體配置函式「malloc()」來產生新節點。

===============================

#if 0
    //================================================
    printf("arguments numbers : %d\n", argc);   // argc : 所帶參數的數目

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : 一個陣列，它會分拆所帶的參數放到陣列內
    }
    printf("\n");
    //================================================
#endif

# 螢幕輸出結果


cc@myfirst$gcc Temp_C_Code.c -o test
cc@myfirst$./test

arguments numbers : 1
[0] ./test



cc@myfirst$./test walter

arguments numbers : 2
[0] ./test
[1] walter



cc@myfirst$./test w a l t e r

arguments numbers : 7
[0] ./test
[1] w
[2] a
[3] l
[4] t
[5] e
[6] r



cc@myfirst$./test 1 2 3 4

arguments numbers : 5
[0] ./test
[1] 1
[2] 2
[3] 3
[4] 4


===============================
# 參考文件 :

C/C++ 程式設計教學：main 函數讀取命令列參數，argc 與 argv 用法
https://blog.gtwang.org/programming/c-cpp-tutorial-argc-argv-read-command-line-arguments/


MAIN(int argc, char *argv[ ]) 之用法
https://blog.xuite.net/tzeng015/twblog/113273095

===============================

printf("\n\033[1;35m[walter]+++++++++++++++++++++++++[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
printf("\n\033[1;35m[walter]-------------------------[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);


===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'
#include <stdlib.h>     // for malloc(), free() functions


#define EXAMPLE 2
/*
1 : e.g. > 簡易單向鏈結串列 (Singly Linked List)
2 : e.g. > 單向鏈結串列 (Singly Linked List) 完整sample code
3 : e.g. > 雙向鏈結串列 (Doubly Linked List) 完整sample code
*/

#define false   0
#define true    1

#if (EXAMPLE == 1)  // 1 : e.g. > 簡易單向鏈結串列 (Singly Linked List)

struct sr {
    int i ;         // Data field
    struct sr *p;   // link field。「自我參考機制」，完成linked list資料結構的重要機制。
};

#endif


#if (EXAMPLE == 2)  // 2 : e.g. > 單向鏈結串列 (Singly Linked List) 完整sample code

struct Node {           // 單向鏈結串列 (Singly Linked List)
    int data;           // Data field
    struct Node *link;  // link field。「自我參考機制」，完成linked list資料結構的重要機制。
};

typedef struct Node node;
typedef node *nodePointer;  // 指向「node」的 pointer

// 配置一個單向鏈結串列(Singly Linked List) 節點(Node)
nodePointer GetNode()
{
    nodePointer NewNode;        // nodePointer :  指向「node」的 pointer

    NewNode = (nodePointer) malloc(sizeof(node));   // sizeof(node) : 配置一個節點所需要的記憶體
                                                    // NewNode : 指向新的空間
    if(NewNode == NULL)
        printf("memory is not enough\n");

    return NewNode;         // 回傳一個指向「新的node」的 pointer
}

// 插入新節點在m節點之後，原串列 = L -> m -> a -> NULL
int insertAfter(nodePointer L, nodePointer m, int d)    // L : List Head(第一個節點), m : 被指定的節點, d : 新節點的值
{
    nodePointer n = GetNode();  // 取得一個新節點的address, n

    if(n == NULL)
        return false;

    // 新節點 n->NULL
    n->data = d;
    n->link = NULL;

    // 26->18->15->29->32->12->NULL
    // m節點 = 18, d節點 = 99

    if(m != NULL)
    {
        // 下面兩行順序不可對調
        n->link = m->link;      // L -> m -> a -> NULL  變成  L -> m,   n -> a -> NULL。 說明 : 原本的2級主管(m)因為升官，所以把原本的手下(m->link)交給新的2級主管(n)
        m->link = n;            // L -> m,   n -> a -> NULL  變成  L -> m -> n -> a -> NULL。 說明 : 新的2級主管(n)就變成1級主管(m)的手下
    }
    else    // 串列原本是空串列
        L = n;                  // L -> n

    return true;
}

// 循序拜訪整個串列
void LinkListTraverse(nodePointer L)        // L : List Head(第一個節點)
{
    nodePointer w = L;      // 工作指標w指向第一個節點， 工作指標可移動，概念類似於 for(i = 0;i < x;i++) 的 i

    while(w != NULL)        // 在還沒到達最後一個節點時
    {
        printf("%d->", w->data);    // 打印所指的節點值
        w = w->link;                // 移動到下一個節點
    }
    printf("NULL\n");
}

// 建立一個單向鏈結串列 (Singly Linked List)，由陣列提供節點data值
// data : 陣列，n : 陣列元素數目
nodePointer CreateAll(int *data, int x)  /* 小試身手  4-2 */
{
    nodePointer L = NULL;           // nodePointer :  指向「node」的 pointer
    int i;

    for(i = x - 1; i >= 0; i--)     // 從陣列的最後一個元素開始
    {
        nodePointer n = GetNode();   // 取得一個新節點的address, n

        if(n == NULL)
            exit(1);

        // data[6] = 26, 18, 15, 29, 32, 12,

        n->data = data[i];   // 將陣列第i個值塞入節點
        n->link = L;         // 將該節點指向NULL
        L = n;               // 將該新節點的address給L，等同於該節點變在最後一個
        printf("在串列開頭處插入一個節點%d.....OK!\n",data[i]);
    }
/*
// 螢幕輸出 >
===============================

在串列開頭處插入一個節點12.....OK!
在串列開頭處插入一個節點32.....OK!
在串列開頭處插入一個節點29.....OK!
在串列開頭處插入一個節點15.....OK!
在串列開頭處插入一個節點18.....OK!
在串列開頭處插入一個節點26.....OK!

====================================
*/
    return L;   // 將第一個節點的address回傳

}

/*
- 刪除m節點，原串列 = L -> m -> a -> NULL
- 刪除m節點前，必須要先知道m節點的前一個和後一個節點
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
    else            // L1原本是空串列
        L1 = L2;

    return L1;
}
#endif




/*
- argc : argument count(參數總和)的縮寫，代表包括指令本身的參數個數。
- argv :argument value 的縮寫。 一個陣列，它會分拆所帶的參數放到陣列內
*/
int main(int argc, char *argv[]) {

#if (EXAMPLE == 1)  // 1 : e.g. > 簡易單向鏈結串列 (Singly Linked List)

                    // first -> sr1 -> sr2 -> NULL

    struct sr *first;       // List Head。一般會使用一個「串列頭」(List Head)來指向頭節點(sr1)。first = &sr1;
    struct sr sr1, sr2;     // 宣告2個節點

    first = &sr1;           // 圖示 : first -> sr1
    sr1.i = 10;

    sr1.p = &sr2;           // 圖示 : sr1 -> sr2
    sr2.i = 30;

    sr2.p = NULL;           // 必須指向相同結構體的變數，或是NULL。 sr2 -> NULL
    (*(sr1.p)).i = 40;      // 改變sr2.i的值，*(sr1.p) = sr2

    printf("sr2.i = %d, (*(sr1.p)).i = %d\n", sr2.i, (*(sr1.p)).i);

/*
// 螢幕輸出 >
===============================
// first -> sr1 -> sr2 -> NULL
===============================
*/

#endif


#if (EXAMPLE == 2)  // 2 : e.g. > 單向鏈結串列 (Singly Linked List) 完整sample code

                    // first -> sr1 -> sr2 -> NULL

    // 圖示 : first ->
    nodePointer first = NULL;           // 宣告指向「node」的 pointer，List Head

    int data[6] = {26, 18, 15, 29, 32, 12};
    int i;

    printf("matrix data[%d] = ", (int)(sizeof(data)/sizeof(*data))); // (sizeof(data)/sizeof(*data)) : 算出幾個元素
    // 螢幕輸出 >  matrix data[6] =

    for(i = 0; i < (int)(sizeof(data)/sizeof(*data)); i++)
        printf("%d, ", data[i]);
        // 螢幕輸出 >  26, 18, 15, 29, 32, 12,

    printf("\n\n");


    /*================= 小試身手  4-2 =================*/
    // 建立一個單向鏈結串列 (Singly Linked List)，由陣列提供節點data值
    printf("建立一個單向鏈結串列 (Singly Linked List)，由陣列提供節點data值\n");

    // first = CreateAll(data, 6);
    first = CreateAll(data, (int)(sizeof(data)/sizeof(*data)));     // 圖示 : first -> data[i] -> ...
    LinkListTraverse(first);    // 循序拜訪整個串列

/*
// 螢幕輸出 >
===============================

26->18->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("插入新節點在m節點之後\n");
    {
        int d = 99;   // 新節點的值

        // 插入新節點在m節點之後
        printf("m節點 = %d, 新節點 = %d\n", first->link->data, d);

        insertAfter(first, first->link, d);     // L : List Head(第一個節點), m : 被指定的節點, d : 新節點的值
        LinkListTraverse(first);                // 循序拜訪整個串列
    }
/*
// 螢幕輸出 >
===============================

插入新節點在m節點之後
m節點 = 18, 新節點 = 99
26->18->99->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("刪除m節點\n");
    {
        // 插入新節點在m節點之後
        printf("刪除m節點 = %d\n", first->link->link->data);

        DeleteNode(first, first->link->link);    // L : List Head(第一個節點), m : 被指定的節點
        LinkListTraverse(first);                    // 循序拜訪整個串列
    }
/*
// 螢幕輸出 >
===============================

刪除m節點
刪除m節點 = 99
26->18->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("連結兩個單向鏈結串列 (Singly Linked List) L1, L2\n");
    {
        nodePointer L1 = NULL, L2 = NULL;   // 宣告2個 List Head
        int d1[3] = {26,18,15};
        int d2[3] = {26,18,15};

        L1 = CreateAll(d1, (int)(sizeof(d1)/sizeof(*d1)));
        LinkListTraverse(L1);
        printf("\n");

        L2 = CreateAll(d2, (int)(sizeof(d2)/sizeof(*d2)));
        LinkListTraverse(L2);
        printf("\n");

        L1 = Concatenate(L1,L2);    // 連結兩個單向鏈結串列 (Singly Linked List) L1, L2

        printf("L1 + L2\n");
        LinkListTraverse(L1);
    }

/*
// 螢幕輸出 >
===============================


matrix data[6] = 26, 18, 15, 29, 32, 12,

建立一個單向鏈結串列 (Singly Linked List)，由陣列提供節點data值
在串列開頭處插入一個節點12.....OK!
在串列開頭處插入一個節點32.....OK!
在串列開頭處插入一個節點29.....OK!
在串列開頭處插入一個節點15.....OK!
在串列開頭處插入一個節點18.....OK!
在串列開頭處插入一個節點26.....OK!
26->18->15->29->32->12->NULL
====================================

插入新節點在m節點之後
m節點 = 18, 新節點 = 99
26->18->99->15->29->32->12->NULL
====================================

刪除m節點
刪除m節點 = 99
26->18->15->29->32->12->NULL
====================================

連結兩個單向鏈結串列 (Singly Linked List) L1, L2
在串列開頭處插入一個節點15.....OK!
在串列開頭處插入一個節點18.....OK!
在串列開頭處插入一個節點26.....OK!
26->18->15->NULL

在串列開頭處插入一個節點15.....OK!
在串列開頭處插入一個節點18.....OK!
在串列開頭處插入一個節點26.....OK!
26->18->15->NULL

L1 + L2
26->18->15->26->18->15->NULL


===============================
*/

#endif


    return 0;
}




