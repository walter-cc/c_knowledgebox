/*
# 編譯和執行步驟 :
1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello
# 此範例執行步驟
$ gcc 5_mutex.c -lpthread -o main        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main
===============================
# 執行結果 :
[mtk18157@mtkslt207 pthread_sample]$gcc 5_mutex.c -lpthread -o main
[mtk18157@mtkslt207 pthread_sample]$./main
main thread, 1
child thread
child thread
main thread, 2
Counter = 1
Counter = 2
Counter = 3
main thread, 3
Counter = 4
Counter = 5
Counter = 6
main thread, 4
===============================
# 加入一個互斥鎖（mutex），將那些不可以被多個執行緒同時執行的程式碼片段，用互斥鎖包起來，當一個執行緒執行到該處時，就會先上鎖，
  避免其他的執行緒進入，若其他的執行緒同時也要執行該處的程式碼時，就必須等待先前的執行緒執行完之後，才能接著進入（也就是排隊輪流使用的概念），
  這樣就可以避免多個執行緒混雜執行，讓結果出錯的問題。

# 在多執行緒程式中部分程式片段的執行可能會有 race conditions 問題，這片段的程式稱為臨界區，
  針對這個臨界區我們可以用 Mutex 互斥鎖來保護，確保同一個時間點只有一隻執行緒進入這個程式片段

# 在 pthread_mutex_lock 與 pthread_mutex_unlock 之間的程式碼就是一次只容許一個執行緒執行的部份，也就是說雖然是平行化的程式，
  但是被包住的這部份只能以單一執行緒來執行，所以在設計程式時，要盡可能減少被互斥鎖包住的程式碼，才能讓程式執行效能更好。
===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
  # Pthread and Semaphor
  https://www.kshuang.xyz/doku.php/programming:c:pthread_and_semaphore
*/


#include <stdio.h>
#include <pthread.h>        // 這是ptrhead程式庫的標頭檔..
#include <unistd.h>

// 計數器
int counter = 0;

// 加入 Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// 子執行緒函數
void* child() {
    int i;
    printf("child thread\n");

    for(i = 0; i < 3; i++) {
        pthread_mutex_lock(&mutex1);          // 上鎖
        int tmp = counter;
        sleep(1);

        counter = tmp + 1;
        pthread_mutex_unlock(&mutex1);    // 解鎖
        printf("Counter = %d\n", counter);
    }

    pthread_exit(NULL);     // thread自己結束
}

// 主程式(主執行緒)
int main() {

    int i;
    pthread_t t1, t2;   // 宣告 pthread 變數，"pthread_t"資料結構可儲存 pthead的資訊..

    printf("main thread, 1\n");
    pthread_create(&t1, NULL, child, NULL); // 建立新的子執行緒，"child"為執行緒要執行的函式名稱
    pthread_create(&t2, NULL, child, NULL); // 建立新的子執行緒，"child"為執行緒要執行的函式名稱

    printf("main thread, 2\n");
    pthread_join(t1, NULL);                 // 等待子執行緒執行完成

    printf("main thread, 3\n");
    pthread_join(t2, NULL);                 // 等待子執行緒執行完成

    printf("main thread, 4\n");
    return 0;
}
