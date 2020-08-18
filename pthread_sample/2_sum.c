/*===============================
# 編譯和執行步驟 :
1. gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2. gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3. ./hello                                          // 執行 execute file "hello"
or
1. gcc hello.c -o hello
2. ./hello

# 此範例執行步驟
$ gcc 2_sum.c -lpthread -o sum                  // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./sum

===============================
# 此範例可以看到 :

# 在許多的平行化應用程式中，我們都會需要傳遞一些資料給子執行緒進行計算，而在計算完之後再將結果傳回來，而子執行緒在傳回資料時通常都會以 malloc 配置記憶體空間來存放傳回的資料

# 這個程式中，子執行緒呼叫 malloc 配置了記憶體空間，而主執行緒在使用完該記憶體空間之後，負責釋放掉不再使用的記憶體。

===============================
# 執行結果 :

cc@pthread_sample$./sum
1 + 2 = 3


===============================
# 參考文件 :

C 語言 pthread 多執行緒平行化程式設計入門教學與範例
https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/

===============================*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 子執行緒函數
void *child(void *arg) {

    int *input = (int *) arg;               // 取得資料
    int *result = malloc(sizeof(int) * 1);  // 配置記憶體
    result[0] = input[0] + input[1];        // 進行計算
    pthread_exit((void *) result);          // 傳回結果

}

// 主程式(主執行緒)
int main() {

    pthread_t t;
    void *ret;                  // 子執行緒傳回值
    int input[2] = {1, 2};      // 輸入的資料

    // 建立子執行緒，傳入 input 進行計算
    pthread_create(&t, NULL, child, (void*) input);

    // 等待執行到子執行緒內的"pthread_exit"時退出，然後返回一個值直接送到"pthread_join"
    pthread_join(t, &ret);

    // 取得計算結果
    int *result = (int *) ret;

    // 輸出計算結果
    printf("%d + %d = %d\n", input[0], input[1], result[0]);

    // 釋放記憶體
    free(result);

    return 0;
}


