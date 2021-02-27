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

# offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

- offsetof 定義在 <linux/stddef.h>
- 用來計算某一個struct結構的成員相對於該結構起始位址的偏移量( offset )。
  (偏移 == 離起始位址有多遠的距離)


# container_of(PTR, TYPE, MEMBER) :
- container_of 定義在 <linux/kernel.h>
- 它需要引用offsetof巨集，它的作用是用來「取得struct結構的起始點」，只要知道該結構的任一個成員的位址，就可以使用container_of巨集來算出該結構的起始位址。



===============================
# 螢幕輸出結果



===============================
# 參考文件 :

Linux的container_of 與 offsetof巨集
https://myao0730.blogspot.com/2016/09/linuxcontainerof-offsetof.html?m=1

===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'
#include <stdlib.h>     // for malloc(), free() functions


// 用來計算某一個struct結構的成員相對於該結構起始位址的偏移量( offset )
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/*
- TYPE : structure name
- MEMBER : structure member

1. ((TYPE *)0) : 轉型成 「TYPE指標」型別
2. &((TYPE *)0)->MEMBER : 0 被當作該TYPE的起始地址，然後再指向某成員
3. &((TYPE *)0)->MEMBER) : 得到MEMBER的位址。因為起始位址等於 0，所以MEMBER的位址也就等於MEMBER與起始位址0的偏移(offset)。
4. offsetof(TYPE, MEMBER) : 用來計算某一個struct結構的成員相對於該結構起始位址的偏移量( offset )
*/


// 用來「取得 struct結構 TYPE的起始點」
#define container_of(PTR, TYPE, MEMBER) ({\
        const typeof( ((TYPE *)0)->MEMBER ) *__mptr = (PTR);\
              (TYPE *)( (char *)__mptr - offsetof(TYPE,MEMBER) );})
/*
- PTR : 指向該結構成員的型別的指標
- TYPE :  structure name
- MEMBER :  structure member

1. typeof( ((TYPE *)0)->MEMBER ) : 取出「MEMBER」的資料型別
2. typeof( ((TYPE *)0)->MEMBER ) *__mptr : 定義一個「指向 MEMBER 型別的指標」 __mptr
3. const typeof( ((TYPE *)0)->MEMBER ) *__mptr = (PTR); : 將指標PTR傳給__mptr
4. (TYPE *)( (char *)__mptr - offsetof(TYPE,MEMBER) ); :
   「__mptr的位址」 - 「MEMBER與結構起始點的偏移(利用offsetof)」 = 該結構的起始點位址。
*/


struct MY_DATA {    // 假設起始 addr = 0x100

    int Data_A;     // 假設 addr = 0x100
    int Data_B;     // 假設 addr = 0x104, offset of Data_B = 4, 0x104 - 4 = 0x100 = 該結構的起始點位址
    int Data_C;
    struct MY_DATA *next;

};



/*
- argc : argument count(參數總和)的縮寫，代表包括指令本身的參數個數。
- argv :argument value 的縮寫。 一個陣列，它會分拆所帶的參數放到陣列內
*/
int main(int argc, char *argv[]) {

    struct MY_DATA data ;
    struct MY_DATA *ptr;

    data.Data_A = 123;
    data.Data_B = 321;
    data.Data_C = 987;


    int *Data_B_ptr = &data.Data_B;     // the address of Data_B in "struct MY_DATA data"

    /*
        # container_of(PTR, TYPE, MEMBER)
        - PTR : 指向該結構成員的型別的指標
        - TYPE :  structure name
        - MEMBER :  structure member
    */
    ptr = container_of( Data_B_ptr, struct MY_DATA , Data_B );

    printf("\n== the example of container_of ==\n");
    printf("(struct MY_DATA data) addr = %p, addr from container_of = %p\n", &data, ptr);

    if( &data == ptr )
        printf("container_of function is ok!\n\n");

    printf("\n== the example of offsetof ==\n");
    printf("ptr->Data_A = %d\nptr->Data_B = %d\nptr->Data_C = %d\n\n",
        ptr->Data_A,
        ptr->Data_B,
        ptr->Data_C);

    printf("Data_A offset = %ld\n", offsetof(struct MY_DATA, Data_A));
    printf("Data_B offset = %ld\n", offsetof(struct MY_DATA, Data_B));
    printf("Data_C offset = %ld\n", offsetof(struct MY_DATA, Data_C));
    printf("ptr next offset = %ld\n\n", offsetof(struct MY_DATA, next));

    printf("sizeof(struct MY_DATA) = %ld\n", sizeof(struct MY_DATA));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(data.Data_A) = %ld\n", sizeof(data.Data_A));
    printf("sizeof(data.next) = %ld\n", sizeof(data.next));
    printf("sizeof(ptr) = %ld\n", sizeof(ptr));
/*
===============================
# 螢幕輸出結果

== the example of container_of ==
(struct MY_DATA data) addr = 0x7ffe855c6410, addr from container_of = 0x7ffe855c6410
container_of function is ok!


== the example of offsetof ==
ptr->Data_A = 123
ptr->Data_B = 321
ptr->Data_C = 987

Data_A offset = 0
Data_B offset = 4
Data_C offset = 8
ptr next offset = 16

sizeof(struct MY_DATA) = 24
sizeof(int) = 4
sizeof(data.Data_A) = 4
sizeof(data.next) = 8
sizeof(ptr) = 8


===============================
*/
    return 0;
}


/*
===============================
printf("\n\033[1;35m[walter]+++++++++++++++++++++++++[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
printf("\n\033[1;35m[walter]-------------------------[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
===============================

int main(int argc, char *argv[]) {

    printf("arguments numbers : %d\n", argc);   // argc : 所帶參數的數目

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : 一個陣列，它會分拆所帶的參數放到陣列內
    }
    printf("\n");
    return 0;
}

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
*/

