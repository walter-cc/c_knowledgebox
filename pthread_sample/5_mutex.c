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

cc@pthread_sample$./main 
Counter = 1
Counter = 2
Counter = 3
Counter = 4
Counter = 5
Counter = 6

===============================

# 加入一個互斥鎖（mutex），將那些不可以被多個執行緒同時執行的程式碼片段，用互斥鎖包起來，當一個執行緒執行到該處時，就會先上鎖，避免其他的執行緒進入，若其他的執行緒同時也要執行該處的程式碼時，就必須等待先前的執行緒執行完之後，才能接著進入（也就是排隊輪流使用的概念），這樣就可以避免多個執行緒混雜執行，讓結果出錯的問題。

# 在 pthread_mutex_lock 與 pthread_mutex_unlock 之間的程式碼就是一次只容許一個執行緒執行的部份，也就是說雖然是平行化的程式，但是被包住的這部份只能以單一執行緒來執行，所以在設計程式時，要盡可能減少被互斥鎖包住的程式碼，才能讓程式執行效能更好。

===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 計數器
int counter = 0;

// 加入 Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// 子執行緒函數
void* child() {
    
    for(int i = 0;i < 3;++i) {
        
        pthread_mutex_lock( &mutex1 );          // 上鎖
    
        int tmp = counter;
        sleep(1);
        counter = tmp + 1;
        
        pthread_mutex_unlock( &mutex1 );    // 解鎖
        
        printf("Counter = %d\n", counter);
        
    }
    
    pthread_exit(NULL);
  
}

// 主程式(主執行緒)
int main() {
    
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, child, NULL);
    pthread_create(&t2, NULL, child, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}


