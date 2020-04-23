/*
# 編譯和執行步驟 :
1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello
# 此範例執行步驟
$ gcc 7_mutex_Condition_Variable.c -lpthread -o main        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main
===============================
# 執行結果 :

[mtk18157@mtkslt207 pthread_sample]$gcc 7_mutex_Condition_Variable.c -lpthread -o main
[mtk18157@mtkslt207 pthread_sample]$./main

++++ [main thread], work 3 runs per thread ++++

[thread 0] working (1/3)
[thread 2] working (1/3)
[thread 1] working (1/3)
[thread 3] working (1/3)

[main thread] done < 5, so waiting on cond
[thread 4] working (1/3)
[thread 0] working (2/3)
[thread 2] working (2/3)
[thread 1] working (2/3)
[thread 4] working (2/3)
[thread 3] working (2/3)
[thread 0] working (3/3)
[thread 1] working (3/3)
[thread 4] working (3/3)
[thread 3] working (3/3)
[thread 2] working (3/3)

[thread 0] threads done = 1. Signalling cond.

[thread 1] threads done = 2. Signalling cond.

[thread 4] threads done = 3. Signalling cond.

[thread 3] threads done = 4. Signalling cond.

[thread 2] threads done = 5. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done == 5, so everyone is done
[mtk18157@mtkslt207 pthread_sample]$


--------------------
# 若單把"done++;"這行註解掉的話
--------------------
# 執行結果 :

[mtk18157@mtkslt207 pthread_sample]$gcc 7_mutex_Condition_Variable.c -lpthread -o main
[mtk18157@mtkslt207 pthread_sample]$./main

++++ [main thread], work 3 runs per thread ++++

[thread 0] working (1/3)
[thread 1] working (1/3)
[thread 2] working (1/3)
[thread 3] working (1/3)

[main thread] done < 5, so waiting on cond
[thread 4] working (1/3)
[thread 1] working (2/3)
[thread 3] working (2/3)
[thread 0] working (2/3)
[thread 2] working (2/3)
[thread 4] working (2/3)
[thread 1] working (3/3)
[thread 3] working (3/3)
[thread 0] working (3/3)
[thread 2] working (3/3)
[thread 4] working (3/3)

[thread 1] threads done = 0. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[thread 3] threads done = 0. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[thread 0] threads done = 0. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[thread 2] threads done = 0. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[thread 4] threads done = 0. Signalling cond.

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

(在這邊停住不會動了)

--------------------
# 若單把"pthread_cond_wait(&cond, &mutex);"這行註解掉的話
--------------------
# 執行結果 :

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

[main thread] wake - cond was signalled.

[main thread] done < 5, so waiting on cond

...............(無限循環)


===============================
# 加入一個互斥鎖（mutex），將那些不可以被多個執行緒同時執行的程式碼片段，用互斥鎖包起來，當一個執行緒執行到該處時，就會先上鎖，
  避免其他的執行緒進入，若其他的執行緒同時也要執行該處的程式碼時，就必須等待先前的執行緒執行完之後，才能接著進入（也就是排隊輪流使用的概念），
  這樣就可以避免多個執行緒混雜執行，讓結果出錯的問題。

# 在多執行緒程式中部分程式片段的執行可能會有 race conditions 問題，這片段的程式稱為臨界區，
  針對這個臨界區我們可以用 Mutex 互斥鎖來保護，確保同一個時間點只有一隻執行緒進入這個程式片段

# 在 pthread_mutex_lock 與 pthread_mutex_unlock 之間的程式碼就是一次只容許一個執行緒執行的部份，也就是說雖然是平行化的程式，
  但是被包住的這部份只能以單一執行緒來執行，所以在設計程式時，要盡可能減少被互斥鎖包住的程式碼，才能讓程式執行效能更好。

# 有兩種方法創建互斥鎖，靜態方式和動態方式。

  1. 靜態初始化互斥鎖 :

     pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  2. 動態初始化互斥鎖 :

     int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)
     // 其中 mutexattr 用於指定互斥鎖屬性，如果為NULL則使用缺省屬性。

     e.g. :
     pthread_mutex_t mutex;
     pthread_mutex_init(&mutex, NULL);

# Mutex實現了threads之間數據的共享和溝通，但有一個明顯的缺點，就是它指有兩種狀態 : 鎖定和非鎖定，所以出現了Condition Variable

# Condition Variable 的目標是處理執行緒的進度同步。

  這不是兩個執行緒做一樣的事，然後進度要一樣的意思

  是指在多個執行緒間若有合作先後的關係存在，則 Thread A 執行完某段程式碼後，
  必須等待 Thread B 處理完另一段程式碼再繼續執行下去，這時我們便可以用 Condition Variable 確保兩個執行緒的進度，
  不讓 Thread A 在 Thread B 尚未完成工作前就偷跑

# 條件變量(Condition Variable)只是發起阻塞和喚醒thread的作用，具體的「判斷條件」還是需要user自己設定。

# 條件變量(Condition Variable) 和互斥鎖一樣，都有靜態動態兩種創建方式

  1. 靜態初始化 Condition Variable :

     pthread_cond_t cond = PTHREAD_COND_INITIALIZER ;

  2. 動態初始化 Condition Variable :

     int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr)
     // 儘管POSIX標準中為條件變量定義了屬性，但在LinuxThreads中沒有實現，因此cond_attr值通常為NULL，且被忽略。

     e.g. :
     pthread_cond_t cond;
     pthread_cond_init(&cond, NULL);

===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
  # Pthread and Semaphor
  https://www.kshuang.xyz/doku.php/programming:c:pthread_and_semaphore
  # [C] 互斥鎖 pthread_mutex_lock sample
  http://work.oknow.org/2016/09/c-pthreadmutexlock-sample.html
  # Posix線程編程指南(3)
  https://blog.xuite.net/mb1016.flying/linux/26293042-%E8%BD%89%E8%B2%BC%3A+pthread+%E8%A7%A3%E8%AE%80%28%E4%B8%89%29
  # Linux Multi-Thread Programming
  https://sites.google.com/site/myembededlife/Home/applications--development/linux-multi-thread-programming
*/


#include <stdio.h>
#include <pthread.h>        // 這是ptrhead程式庫的標頭檔..
#include <unistd.h>

const size_t NUMTHREADS = 5;
int done = 0;

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    // 加入 Mutex，靜態初始化互斥鎖
pthread_mutex_t mutex;  // 加入 Mutex，動態初始化互斥鎖
pthread_cond_t cond;    // 動態初始化 Condition Variable

// 子執行緒函數
void *child(void *id)
{
    const int myid = (long)id; // force the pointer to be a 64bit integer
    const int workloops = 3;
    int i;

    for (i = 0; i < workloops; i++)
    {
        printf("[thread %d] working (%d/%d)\n", myid, (i + 1), workloops);
        sleep(1); // simulate doing some costly work
    }

    // we're going to manipulate done and use the cond, so we need the mutex
    pthread_mutex_lock(&mutex);

    /*
    - increase the count of threads that have finished their work.
    - done 這個變數的修改是需要在臨界區處理的 (單一變數可能較難感覺有沒有 metux 的差別，但考慮成寫入檔案就有差了)
    */
    done++;     // 若單把這行註解掉的話，則雖然main thread會被喚醒，但因為while (done < NUMTHREADS)條件不滿足，所以會卡在 "pthread_cond_wait()"。

    // wait up the main thread (if it is sleeping) to test the value of done
    // 每條 Thread 完成工作後會發出 condition signal 通知 Main Thread
    printf("\n[thread %d] threads done = %d. Signalling cond.\n", myid, done);
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);
}

// 主程式(主執行緒)
int main() {    // 建立了 5 條執行緒，每條執行緒會做 3 輪來完成工作

    int i;
    pthread_t threads[NUMTHREADS];      // 宣告 pthread 變數，"pthread_t"資料結構可儲存 pthead的資訊

    printf("\n++++ [main thread], work 3 runs per thread ++++\n\n");

    pthread_mutex_init(&mutex, NULL);       // 動態初始化互斥鎖
    pthread_cond_init(&cond, NULL);         // 動態初始化 Condition Variable

    for (i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, child, (void *)(long)i);    // 建立新的子執行緒，"child"為執行緒要執行的函式名稱

    pthread_mutex_lock(&mutex);            // 上鎖

    // Main Thread 會在一個迴圈中檢查是否 5 條執行緒都完成工作，如果都完成才能結束程式
    while (done < NUMTHREADS){
        printf("\n[main thread] done < %d, so waiting on cond\n", (int)NUMTHREADS);
        /*
        - block this thread until another thread signals cond.
          While blocked, the mutex is released, then re-acquired before this thread is woken up and the call returns.

        - Main Thread 會等待 condition，這邊會釋放 metux 鎖，讓其他 thread 可取得

        - Main Thread被喚醒後，它會重新檢查判斷條件是否滿足，若還不滿足，則thread會被阻塞在這裡，等待下次被喚醒。這個判斷過程一般都是用while來實現。
        */
        pthread_cond_wait(&cond, &mutex);     // 若單把這行註解掉的話會因為其他 thread 拿不到鎖，而無法完成工作，Main 則進入無窮迴圈

        printf("\n[main thread] wake - cond was signalled.\n");
    }

    printf("\n[main thread] done == %d, so everyone is done\n", (int)NUMTHREADS);

    pthread_mutex_unlock(&mutex);           // 解鎖

    return 0;
}

