/*
# 編譯和執行步驟 :

1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello

# 此範例執行步驟
$ gcc 6_Semaphore.c -lpthread -o main        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main

===============================
# 執行結果 : 

cc@pthread_sample$./main 
Post 2 jobs.
Counter = 1
Counter = 2
Post 3 jobs.
Counter = 3
Counter = 4
Counter = 5

===============================

# 旗標（Semaphore）
  如果我們現在有兩個執行緒，分別負責一份工作的前半段與後半段，
  也就是說第一個執行緒會把它處理好的資料，發包給第二個執行緒繼續處理，
  而兩個執行緒的處理速度有可能不同，這種狀況我們就可以使用旗標（Semaphore）的方式來串接。
  
# 旗標本身就是一個計數器，也就是紀錄目前尚未處理的工作數量，
  我們可以使用 sem_wait 來判斷是否有尚未處理的工作，
  當工作數量大於 0 時，sem_wait 就會讓執行緒進入處理，並且把工作數量遞減 1，
  而如果工作數量為 0 的時候，則會讓執行緒等待，直到有新的工作來臨時，才讓執行緒進入。

# 另外在產生工作的執行緒中，可以使用 sem_post 放入新的工作（也就讓將計數器遞增 1），這樣就可以將多個執行緒串接起來處理大型的工作流程

# 旗標本身只是紀錄工作的數量，並且控制執行緒的執行，並沒有負責資料的配送，
  通常我們可以自己實做一個資料佇列（queue），配合旗標來計算索引，讓子執行緒從佇列中取得資料進行處理。

===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;    // 旗標，本身就是一個計數器，紀錄目前尚未處理的工作數量
int counter = 0;

// 子執行緒函數
void* child() {
    
    for(int i = 0;i < 5;i++) {
        
        sem_wait(&semaphore);   // 等待工作，判斷是否有尚未處理的工作
        /*
          當工作數量大於 0 時，sem_wait 就會讓執行緒進入處理，並且把工作數量遞減 1，
          而如果工作數量為 0 的時候，則會讓執行緒等待，直到有新的工作來臨時，才讓執行緒進入。
        */
        
        printf("Counter = %d\n", ++counter);    // 執行工作
        
        sleep(1);               // 子執行緒則是以每秒處理一個工作的速度，消化接收到的工作。
        
    }
    
    pthread_exit(NULL);
}

// 主程式(主執行緒)
// 主執行緒負責派送工作，工作有時候多、有時候少，而子執行緒則是以每秒處理一個工作的速度，消化接收到的工作。
int main(void) {

    // 初始化旗標，僅用於本行程，初始值為 0
    sem_init(&semaphore, 0, 0);
    /*
        旗標在使用前要先以 sem_init 初始化，其第二個參數是指定是否要讓其他的行程（process）共用旗標，
        這裡我們是單一行程、多執行緒的程式，所以第二個參數設定為 0 即可；第三個參數則是設定旗標的初始值。
    */
    
    pthread_t t;
    pthread_create(&t, NULL, child, NULL);

    // 送出兩個工作，工作有時候少
    printf("Post 2 jobs.\n");
    
    sem_post(&semaphore);   // 放入新的工作（也就讓將計數器遞增 1）
    sem_post(&semaphore);   // 放入新的工作（也就讓將計數器遞增 1）
    sleep(4);

    // 送出三個工作，工作有時候多
    printf("Post 3 jobs.\n");
    sem_post(&semaphore);
    sem_post(&semaphore);
    sem_post(&semaphore);

    pthread_join(t, NULL);

    return 0;
}


