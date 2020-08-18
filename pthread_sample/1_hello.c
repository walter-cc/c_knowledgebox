/*===============================
# 編譯和執行步驟 :
1. gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2. gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3. ./hello                                          // 執行 execute file "hello"
or
1. gcc hello.c -o hello
2. ./hello

# 此範例執行步驟
$ gcc 1_hello.c -lpthread -o hello                  // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./hello

===============================
# 此範例可以看到 :

最簡易的POSIX thread程式庫(pthread)

# POSIX執行緒（英語：POSIX Threads，常被縮寫為Pthreads）是POSIX的執行緒標準，定義了創建和操縱執行緒的一套API。

# 實現POSIX 執行緒標準的庫常被稱作Pthreads，一般用於Unix-like POSIX 系統，如Linux、 Solaris。

# pthread 的 pthread_create 函數可以用來建立新的執行緒，子執行緒在建立之後，就會以平行的方式執行，
  在子執行緒的執行期間，主執行緒還是可以正常執行自己的工作，最後主執行緒再以 pthread_join 函數等待子執行緒執行結束。

# int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
  e.g. :
  pthread_t t;                                // 宣告 pthread 變數
  pthread_create(&t, NULL, child, "Child");   // 建立新的子執行緒

===============================
# 執行結果 :

//#define PTHREAD_EXIT_TEST	// 測試 "pthread_exit"
//#define PTHREAD_JOIN_TEST	// 測試 "pthread_join"

可以看到，主執行緒執行完畢後，會在"pthread_join"等待子執行緒執行。
當子執行緒執行結束後，返回值會直接送到"pthread_join"。

cc@pthread_sample$gcc 1_hello.c -lpthread -o hello
cc@pthread_sample$./hello
Master_data
Child_data
Master_data
Child_data
Master_data
Child_data
-----1-----
Child_data
Child_data
Child_data
Child_data
Child_data
Child_data
Child_data
-----2-----

-------------------------------------------
 #define PTHREAD_EXIT_TEST	// 測試 "pthread_exit"
// #define PTHREAD_JOIN_TEST	// 測試 "pthread_join"

可以看到子執行緒執行一次後被強制退出，只剩主執行緒在動

cc@pthread_sample$gcc 1_hello.c -lpthread -o hello
cc@pthread_sample$./hello
Master_data
Child_data
Master_data
Master_data
-----1-----
-----2-----

-------------------------------------------
// #define PTHREAD_EXIT_TEST	// 測試 "pthread_exit"
 #define PTHREAD_JOIN_TEST	// 測試 "pthread_join"

可以看到，在不加上"pthread_join"的情況下，主執行緒不等子執行緒做完就結束了。


cc@pthread_sample$gcc 1_hello.c -lpthread -o hello
cc@pthread_sample$./hello
Master_data
Child_data
Master_data
Child_data
Master_data
Child_data
-----1-----
-----2-----



===============================
# 參考文件 :

- C 語言 pthread 多執行緒平行化程式設計入門教學與範例
https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/

- pthread_join/pthread_exit的用法解析
https://blog.csdn.net/modiziri/article/details/41961595

===============================*/


#include <stdio.h>
#include <pthread.h>        // 這是ptrhead程式庫的標頭檔..
#include <unistd.h>         // sleep(1)的標頭檔

// #define PTHREAD_EXIT_TEST	// 測試 "pthread_exit"
// #define PTHREAD_JOIN_TEST	// 測試 "pthread_join"

// 子執行緒函數
void* child(void* data) {

    int i;
    char *str = (char*) data;   // 取得輸入資料 "Child_data"

    for(i = 0;i < 10;++i) {
        printf("%s\n", str);    // 每秒輸出文字
        sleep(1);

#ifdef PTHREAD_EXIT_TEST
        pthread_exit(NULL);     // 強制退出子執行緒（非執行完畢退出），一般用於子執行緒內部
#endif
    }

#ifdef PTHREAD_EXIT_TEST
#else
    pthread_exit(NULL);     // 強制退出子執行緒（非執行完畢退出），一般用於子執行緒內部
#endif
}


// 一般都是等待執行到子執行緒內的"pthread_exit"時退出，
// 然後返回一個值直接送到"pthread_join"，實現了主執行緒與子執行緒的通信

// 主程式(主執行緒)
int main() {

    int i;
    pthread_t t;        // 宣告 pthread 變數，"pthread_t"資料結構可儲存 pthead 的資訊
    pthread_create(&t, NULL, child, "Child_data");  // 建立新的子執行緒，"child"為執行緒要執行的函式名稱， "Child_data"為輸入的資料

    // 主執行緒工作
    for(i = 0;i < 3;++i) {
        printf("Master_data\n"); // 每秒輸出文字
        sleep(1);
    }

    printf("-----1-----\n");
#ifdef PTHREAD_JOIN_TEST
#else
    pthread_join(t, NULL);                      // 在此停住，等待子執行緒執行完成才往下走。
#endif
    printf("-----2-----\n");

    return 0;
}



