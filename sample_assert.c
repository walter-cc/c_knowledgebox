/*

1. 我們可以利用**gcc -E**來觀看程式碼被展開之後的樣子
gcc -E test2.c

2. 執行結果

cc@c_knowledgebox$gcc sample_assert.c -o test
cc@c_knowledgebox$./test 
enter number：12
the number you enter：12
**********
cc@c_knowledgebox$./test 
enter number：8
the number you enter：8
test: sample_assert.c:45: main: Assertion `input >= 10' failed.
Aborted (core dumped)


===============================
# 參考文件 :
C函數庫宏 assert()
http://tw.gitbook.net/c_standard_library/c_macro_assert.html

C library macro - assert()
https://www.tutorialspoint.com/c_standard_library/c_macro_assert.htm
===============================*/

#include <stdio.h>
#include <assert.h>     //assert 所在 header

int main() {

    int input;

    printf("enter number：");
    scanf("%d", &input);

    printf("the number you enter：%d\n", input);

    assert(input >= 10);    // 如果計算結果為TRUE，assert()什麼都不做。等於false，就直接在這邊跳出程式

    printf("**********\n");

    return 0;
}


