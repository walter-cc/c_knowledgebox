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


# typeof(x) : 獲取「括號內x 的變量類型」。


typeof(int *)

int *x;
typeof(x)  y;       // 相當於 int *y
typeof(*x) y;       // 相當於 int y
typeof(&x) y;       // 相當於 int **x;


===============================
# 螢幕輸出結果



===============================
# 參考文件 :

C語言的gcc擴展語法(6)-typeof類型引用
https://kknews.cc/code/6e44g3p.html

===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'
#include <stdlib.h>     // for malloc(), free() functions

struct MY_DATA {

    int Data_A;
    int Data_B;
    int Data_C;

};



/*
- argc : argument count(參數總和)的縮寫，代表包括指令本身的參數個數。
- argv :argument value 的縮寫。 一個陣列，它會分拆所帶的參數放到陣列內
*/
int main(int argc, char *argv[]) {

    int x;
    char y;
    struct MY_DATA z;

    typeof(x) x1;       // 相當於 int x1
    typeof(y) y1;       // 相當於 char y1
    typeof(z) z1;       // 相當於 struct MY_DATA z1

    printf("sizeof(x) = %ld, sizeof(x1) = %ld\n", sizeof(x), sizeof(x1));
    printf("sizeof(y) = %ld, sizeof(y1) = %ld\n", sizeof(y), sizeof(y1));
    printf("sizeof(z) = %ld, sizeof(z1) = %ld\n", sizeof(z), sizeof(z1));
/*
===============================
# 螢幕輸出結果

sizeof(x) = 4, sizeof(x1) = 4
sizeof(y) = 1, sizeof(y1) = 1
sizeof(z) = 12, sizeof(z1) = 12

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

