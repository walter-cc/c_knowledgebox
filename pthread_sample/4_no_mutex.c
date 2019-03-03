/*
# 編譯和執行步驟 :

1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello

# 此範例執行步驟
$ gcc 4_no_mutex.c -lpthread -o main        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main

===============================
# 執行結果 : 

cc@pthread_sample$./main 
Counter = 1
Counter = 1
Counter = 2
Counter = 2
Counter = 3
Counter = 3

===============================

# 互斥鎖（Mutex）:
  在平行化的程式中，如果發生多個執行緒需要同時存取同一個位置的資料時，就有可能會因為同時存取而產生錯誤，在下面這個例子中，我們定義一個全域變數 counter，用來紀錄某個量的總和，而我們希望在多個執行緒中同時計算，然後統一將加總的結果放在其中。

# 在這段程式碼中，我們放了兩個子執行緒，每個子執行緒用迴圈跑了三次計算，所以最後的 counter 預期應該是 6，但由於我們將 counter 的值取出來，計算出新的值之後在放回去，兩個子執行緒同時都這樣做的話，計算結果就會不如預期

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

// 子執行緒函數
void* child() {
    
    for(int i = 0;i < 3;i++) {
        
        int tmp = counter;
        sleep(1);           // 故意讓它延遲一下
        counter = tmp + 1;
        
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


