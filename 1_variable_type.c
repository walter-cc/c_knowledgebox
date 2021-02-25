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


#if 0
    //================================================
    printf("arguments numbers : %d\n", argc);   // argc : 所帶參數的數目

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : 一個陣列，它會分拆所帶的參數放到陣列內
    }
    printf("\n");
    //================================================
#endif

===============================
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


#include <stdio.h>          // standard I/O

void a(void);
void b(void);
void c(void);

int x = 1;  // global variable

/*
- argc : argument count(參數總和)的縮寫，代表包括指令本身的參數個數。
- argv :argument value 的縮寫。 一個陣列，它會分拆所帶的參數放到陣列內
*/
int main(int argc, char *argv[]) {

    int i;

    int x = 5;

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5, 會先顯示離自己最近的變數型態

    {
        int x = 7;
        printf("[%d]x = %d\n",__LINE__ , x);  //  = 7
    }

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5

    a();
    b();
    c();

    a();
    b();
    c();

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5

    return 0;
}

void a(void)
{
    int x = 25;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 25, x = 25

    ++x;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 26, x = 26
}

void b(void)
{
    static int x = 50;
    printf("[%d]x = %d\n",__LINE__ , x);  //x = 50, x = 51      // static variable

    ++x;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 51, x = 52     // static variable
}

void c(void)
{
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 1, x = 10      // global variable

    x *= 10;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 10, x = 100    // global variable
}




