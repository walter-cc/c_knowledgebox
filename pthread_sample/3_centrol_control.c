/*
# 編譯和執行步驟 :

1) gcc -c hello.c                                   // 產生目標檔(object file) hello.o
2) gcc hello.o -o hello / gcc -o hello hello.o      // 產生執行檔(execute file) hello
3) ./hello                                          // 執行 execute file "hello"
or
1) gcc hello.c -o hello
2) ./hello

# 此範例執行步驟
$ gcc 3_centrol_control.c -lpthread -o main        // 使用 gcc 編譯時，要加上 -lpthread 參數
$ ./main

===============================
# 執行結果 : 

cc@pthread_sample$./main 
1 + 2 = 3

===============================

# 多執行緒之間的記憶體管理其實很不方便，也很容易不小心寫錯，造成記憶體流失（memory leak）問題，若想避免這個問題，可以統一由主執行緒來管理記憶體

# 這個例子中，我們使用自己定義的資料結構（struct），將所有的輸入資料與輸出結果欄位都包裝在一個 my_data 中，以指標的方式傳入子執行緒中，讓子執行緒在計算完成後，將結果直接寫入 my_data 的 result 欄位，這樣就不需要另外配置記憶體空間，而主執行緒也可以直接取得計算結果。

===============================
# 參考文件 :
  # C 語言 pthread 多執行緒平行化程式設計入門教學與範例
  https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/amp/
*/


#include <stdio.h>
#include <pthread.h>

// 自己定義的資料結構
typedef struct my_data {
    int a;
    int b;
    int result;
} my_data;

// 子執行緒函數
void *child(void *arg) {
    my_data *data=(my_data *)arg;   // 取得資料

    int a = data->a;
    int b = data->b;
    int result = a + b;             // 進行計算

    data->result = result;          // 將結果放進 data 中
    pthread_exit(NULL);
}

// 主程式(主執行緒)
int main() {
    
    pthread_t t;
    my_data data;

    data.a = 1;
    data.b = 2;

    // 建立子執行緒，傳入 data 進行計算
    pthread_create(&t, NULL, child, (void*) &data);

    // 等待子執行緒計算完畢
    pthread_join(t, NULL);

    // 從 data.result 取回計算結果
    printf("%d + %d = %d\n", data.a, data.b, data.result);

    return 0;
}


