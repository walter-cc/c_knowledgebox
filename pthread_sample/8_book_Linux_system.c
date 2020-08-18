/*===============================
# 編譯和執行步驟 :
1. gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2. gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3. ./hello                                          // 執行 execute file "hello"
or
1. gcc hello.c -o hello
2. ./hello

# 此範例執行步驟
$ gcc 8_book_Linux_system.c -lpthread -o main    // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main

===============================
# 此範例可以看到 :

# 此程式會建立2個執行緒(總共有3個)，在同一個起始常式start_thread()裡起始這2個執行緒，
  而且會透過提供不同的引數來區分這2個執行緒在起始常式裡的行為。

===============================
# 執行結果 :

cc@pthread_sample$gcc 8_book_Linux_system.c -lpthread -o main
cc@pthread_sample$./main
Thing 1
Thing 2

or
cc@pthread_sample$./main
Thing 2
Thing 1


===============================
# 參考文件 :

Linux 系統程式設計, 2/e(Linux System Programming: Talking Directly to the Kernel and C Library)
Robert Love 著、蔣大偉 譯
===============================*/



#include <stdio.h>
#include <pthread.h>        // 這是ptrhead程式庫的標頭檔..
#include <stdlib.h>

// 子執行緒函數
void *start_thread(void *message) {

    printf("%s\n", (const char *)message);

    return message;
}

// 主程式(主執行緒)
int main() {    // 建立了 2條執行緒

    pthread_t thread1, thread2;         // 宣告 pthread 變數
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";

    // 以不同的訊息來建立2個子執行緒，"start_thread"為執行緒要執行的函式名稱
    pthread_create(&thread1, NULL, start_thread, (void *)message1);
    pthread_create(&thread2, NULL, start_thread, (void *)message2);

    // 等待執行緒結束。如果我們不在此處連接，在這兩個執行緒完成工作之前，我們會有主要執行緒先終止的風險。
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

