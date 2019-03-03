/*
# 編譯和執行步驟 :

1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello

# 此範例執行步驟
$ gcc 1_hello.c -lpthread -o hello        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./hello

===============================
# 執行結果 : 

cc@pthread_sample$./hello
Master
Child
Master
Child
Master
Child

===============================

# POSIX執行緒（英語：POSIX Threads，常被縮寫為Pthreads）是POSIX的執行緒標準，定義了創建和操縱執行緒的一套API。

# 實現POSIX 執行緒標準的庫常被稱作Pthreads，一般用於Unix-like POSIX 系統，如Linux、 Solaris。

# pthread 的 pthread_create 函數可以用來建立新的執行緒，子執行緒在建立之後，就會以平行的方式執行，在子執行緒的執行期間，主執行緒還是可以正常執行自己的工作，最後主執行緒再以 pthread_join 函數等待子執行緒執行結束。

# int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

  e.g. :
  pthread_t t;                                // 宣告 pthread 變數
  pthread_create(&t, NULL, child, "Child");   // 建立新的子執行緒
    
===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 子執行緒函數
void* child(void* data) {
    
    char *str = (char*) data;   // 取得輸入資料
    
    for(int i = 0;i < 3;++i) {
        printf("%s\n", str);    // 每秒輸出文字
        sleep(1);
    }
    
    pthread_exit(NULL);         // 離開子執行緒
    
}

// 主程式(主執行緒)
int main() {
    
    pthread_t t;                                // 宣告 pthread 變數
    pthread_create(&t, NULL, child, "Child");   // 建立新的子執行緒

    // 主執行緒工作
    for(int i = 0;i < 3;++i) {
        
        printf("Master\n"); // 每秒輸出文字
        sleep(1);
        
    }

    pthread_join(t, NULL);                      // 等待子執行緒執行完成
    return 0;
}


