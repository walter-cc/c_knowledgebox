/*===============================

# 此檔案為ANSI檔案

# 我們可以利用**gcc -E**來觀看程式碼被展開之後的樣子
gcc -E test.c

# 新增編譯和執行步驟 :

gcc test.c -o test
./test

或

1) gcc -c hello.c                   // 產生目標檔(object file) hello.o
2) gcc -o hello hello.o          // 產生執行檔(execute file) hello
3) ./hello                           // 執行 execute file "hello"

或

gcc -o hello hello.c

===============================
# 此範例可以看到 : 「習」


# 指標的基本概念很簡單 : 就是個「存放記憶體位址」的變數。

# 函數指標 (Function pointer) :

    - 雖然函數不是變數，但它在記憶中佔有一個位址(函數的起始位址)，
    將此位址指定給某一個指標，之後便「可利用此指標呼叫該函數」。
    
    - 換句話說，這個階段可將指標當成函數A，下個階段指標可當成函數B


# 指標陣列 (pointers of array) :

    - 一種陣列，其元素皆為「指標」。
  

# 常數指標 (constant pointer) :

    - 指向 const 的 pointer，
        
      e.g. : const int *pci

    - 指向 不是const 的 const pointer，
    
      e.g. : int *const cpi


#define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))

    - ARRAYSIZE(arr) : 算出array裡面有幾個element，8個
    - sizeof(arr) : array裡面 Total 幾個bytes
    - sizeof(*arr) : 每單位 element 是 幾個bytes

// <offset, value>
reg_val_t data_raw_main[] =
{
    0x4930, 0x12345678, //FHO.ORIWDMA_FH_SPARE_5
    0x4934, 0x87654321, //FHO.ORIWDMA_FH_SPARE_6
    0x4938, 0xdeadbeef, //FHO.ORIWDMA_FH_SPARE_7
    0x493c, 0xbeefdead, //FHO.ORIWDMA_FH_SPARE_8
};
T.regval_size = ARRAYSIZE(data_raw_main);


===============================
# 螢幕輸出結果



===============================
# 參考文件 :


===============================
*/

#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'

#define EXAMPLE 8
/*
1 : simple example
2 : e.g. > 回傳一個指向char的指標
           int *op(int a, int b)
3 : e.g. > 函數指標 (Function pointer)
            int (*op)(int a, int b)     // 「()」不能省
4 : e.g. > 指標陣列 (pointers of array)
5 : e.g. > size of pointer
6 : e.g. > 指向 const 的 pointer (指向 const 的 pointer)，e.g. : const int *pci
7 : e.g. > 指向不是常數的指標常數 (指向 不是const 的 const pointer)，e.g. : int *const cpi
8 : e.g. > #define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))
*/

#if (EXAMPLE == 2)
/*
2 : e.g. > 回傳一個指向char的指標
           int *op(int a, int b)
*/

char *find(char *st, char ch)   // 回傳一個指向char的指標
{
    int count = 0;

    while(ch != st[count] && st[count] != '\0') // 如果字元不等於字串的第count，並且不等於'\0'結數字元，count++
    count++;

    if(count == strlen(st))
        return ((char *)0);     // 將0強制轉型成char *傳回
    else
        return (&st[count]);    // 將字元位址傳回
}
#endif

#if (EXAMPLE == 3)
/*
3 : e.g. > 函數指標 (Function pointer)
            int (*op)(int a, int b)     // 「()」不能省
*/
int add(int a, int b)
{
    return (a + b);
}

int mult(int a, int b)
{
    return (a * b);
}

typedef int (*OP) (int, int);  // 如果希望定義一個「函數指標」的型態

#endif

/*
- argc : argument count(參數總和)的縮寫，代表包括指令本身的參數個數。
- argv :argument value 的縮寫。 一個陣列，它會分拆所帶的參數放到陣列內
*/
int main(int argc, char *argv[]) {

#if (EXAMPLE == 1)  // 1 : simple example
    //e.g. 1 :
    char ch[]={'g', 'e', 'e', 'k', 's', '\0'};
    printf("Length of string is: %ld\n", strlen(ch));   // strlen : 算出字元總數，不含'\0'
    // 螢幕輸出 > Length of string is: 5


    //e.g. 2 :
    char str1[]= "geeks";   // 字元陣列
    printf("Length of string is: %ld\n", strlen(str1));
    // 螢幕輸出 > Length of string is: 5


    //e.g. 3 :
    char *str2 = "geeks";
    printf("Length of string is: %ld\n", strlen(str2));
    // 螢幕輸出 > Length of string is: 5
#endif

#if (EXAMPLE == 2)
/*
2 : e.g. > 回傳一個指向char的指標
           int *op(int a, int b)
*/
    char *find(char *st, char ch);
    char s[80], *ptr, c;

    printf("Input a string : ");
    fgets(s, sizeof(s), stdin);     // 取得使用者輸入的整個字串，不包括按下 Enter
    // 螢幕輸出 > Input a string : walter is good

    printf("string is : ");
    puts(s);    // 輸出整個字串，會直接進行換行
    // 螢幕輸出 > string is : walter is good


    printf("Input a character : ");
    c = getchar();      // 取得使用者輸入的"字元"
    // 螢幕輸出 > Input a character : g

    putchar(c);         // 只想輸出一個"字元"
    putchar('\n');
    // 螢幕輸出 > g


    ptr = find(s,c);

    if(ptr)
        printf("Address of %c is : %p\n", c, ptr);  // %c : 以字元形式列印char型態的資料
    else
        printf("Not found\n");

/*
// 螢幕輸出 >
===============================
----------
# ans 1:
----------
Input a string :walter is good
string is : walter is good

Input a character : x
x
Not found

----------
# ans 2 :
----------
Input a string :walter is good
string is : walter is good

Input a character : g
g
Address of g is:0x7fff7b38f58a
===============================
*/
#endif

#if (EXAMPLE == 3)
/*
3 : e.g. > 函數指標 (Function pointer)
            int (*op)(int a, int b)     // 「()」不能省
*/

    int (*op1)(int a, int b);   // 宣告一個function pointer，回傳值是int，傳入參數是(int, int)
    
    OP op2 = add;               // 直接用prototype "OP" 來宣告 function pointer
    op1 = add;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

    op1 = mult;
    op2 = mult;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

/*
// 螢幕輸出 >
===============================
op1(3,5) = 8, op2(3,5) = 8
op1(3,5) = 15, op2(3,5) = 15
===============================
*/
#endif

#if (EXAMPLE == 4)  // 4 : e.g. > 指標陣列 (pointers of array)

    // 字串陣列 : 浪費記憶體空間
    static char days[7][10] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    // 指標陣列 (pointers of array)
    static char *DAYS[7] = {    // 一個陣列有7個元素，元素皆為指向char的指標
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    printf("*DAYS[3] = %c\n", *DAYS[3]);            // 第4個元素的第1個字元
    printf("**(DAYS + 3) = %c\n", **(DAYS + 3));    // 第4個元素的第1個字元
    printf("DAYS[3][0] = %c\n", DAYS[3][0]);        // 第4個元素的第1個字元
    printf("DAYS[2] = %s\n", DAYS[2]);              // 第3個元素的字串
    printf("*(DAYS + 2) = %s\n", *(DAYS + 2));      // 第3個元素的字串

/*
// 螢幕輸出 >
===============================
*DAYS[3] = W
**(DAYS + 3) = W
DAYS[3][0] = W
DAYS[2] = Tuesday
*(DAYS + 2) = Tuesday
===============================
*/
#endif

#if (EXAMPLE == 5)  // 5 : e.g. > size of pointer

    char *x;                    // 指向char的pointer
    int *y;                     // 指向int的pointer
    char **a;                   // 指向一個「指向char的pointer」的pointer
    char *b[20];                // 有20個指向char的pointer，叫做「指標陣列」
    char (*c)[20];              // 指向char[20]陣列的pointer
    char (*d)[20][1];           // 指向char[20][1]陣列的pointer
    int (*pt)(int a, int b);    // 指向int(int a, int b) 的「函數指標」 (Function pointer)

    printf("sizeof(x) = %d, sizeof(*x) = %d\n", (int)sizeof(x) , (int)sizeof(*x));  
    // sizeof(x) : pointer 的大小，sizeof(*x) : x 所指向的 char 的大小
    
    printf("sizeof(y) = %d, sizeof(*y) = %d\n", (int)sizeof(y), (int)sizeof(*y));   
    // sizeof(y) : pointer 的大小，sizeof(*y) : y 所指向的 int 的大小
    
    printf("sizeof(a) = %d, sizeof(*a) = %d\n", (int)sizeof(a), (int)sizeof(*a));   
    // sizeof(a) : pointer 的大小，sizeof(*a) : a 所指向的「指向char的pointer」的大小
    
    printf("sizeof(b) = %d, sizeof(*b) = %d\n", (int)sizeof(b), (int)sizeof(*b));   
    // sizeof(b) : pointer 的大小，sizeof(*b) : b 所指向的 char 的大小
    
    printf("sizeof(c) = %d, sizeof(*c) = %d\n", (int)sizeof(c), (int)sizeof(*c));   
    // sizeof(c) : pointer 的大小，sizeof(*c) : c 所指向的 char[20]陣列 的大小
    
    printf("sizeof(d) = %d, sizeof(*d) = %d\n", (int)sizeof(d), (int)sizeof(*d));   
    // sizeof(d) : pointer 的大小，sizeof(*d) : d 所指向的 char[20][1]陣列 的大小
    
    printf("sizeof(pt) = %d, sizeof(*pt) = %d\n", (int)sizeof(pt), (int)sizeof(*pt));   
    // sizeof(pt) : pointer 的大小，sizeof(*pt) : pt 所指向的 int(int a, int b) 的大小

/*
// 螢幕輸出 >
===============================
sizeof(x) = 8, sizeof(*x) = 1
sizeof(y) = 8, sizeof(*y) = 4
sizeof(a) = 8, sizeof(*a) = 8
sizeof(b) = 160, sizeof(*b) = 8
sizeof(c) = 8, sizeof(*c) = 20
sizeof(d) = 8, sizeof(*d) = 20
sizeof(pt) = 8, sizeof(*pt) = 1
===============================
*/

#endif


#if (EXAMPLE == 6)  // 6 : e.g. > 指向 const 的 pointer (指向 const 的 pointer)，e.g. : const int *pci
    
    int num = 5;
    const int limit = 500;  // 「整數常數」，值無法修改
    int *pi;                // 指向「整數」的指標
    const int *pci;         // 指向「整數常數」的指標。 const int *pci; 或是 int const *pci; 都可以

/*
===============================
# pci 宣告為指向「整數常數」的指標代表了 :

  - pci可以指派為指向其他「整數常數」。e.g. : pci = &limit;     其中 const int limit = 500;

  - pci可以指派為指向其他「非整數常數」。e.g. : pci = &num;      其中 int num = 5;

  - pci可以透過「解參考」讀取數值。e.g. : printf("value %d\n", *pci);

  - pci無法透過「解參考」改變指向的位址內容。e.g. : *pci = 200;
===============================
*/
    pi = &num;
    pci = &limit;

    printf("num - address %p value %d\n", &num, num);
    printf("limit - address %p value %d\n", &limit, limit);
    printf("pi - address %p value %p\n", &pi, pi);
    printf("pci - address %p value %p\n", &pci, pci);

    printf("value %d\n", *pci);     // 解參考「常數指標」，合法且必要

    pci = &num; // 合法
    /*
    ===============================
    *pci = 200;
    語法錯誤，指標認為只到的變數是「整數常數」，不允許透過指標修改內容，但仍然可以透過num修改內容，只是無法透過pci進行修改。
    // error: assignment of read-only location ‘*pci’
    ===============================
    */

/*
// 螢幕輸出 >
===============================
num - address 0x7ffdc4c04f00 value 5
limit - address 0x7ffdc4c04f04 value 500
pi - address 0x7ffdc4c04f08 value 0x7ffdc4c04f00
pci - address 0x7ffdc4c04f10 value 0x7ffdc4c04f04
value 500
===============================
*/

#endif

#if (EXAMPLE == 7)  // 7 : e.g. > 指向不是常數的指標常數 (指向 不是const 的 「const pointer」)，e.g. : int *const cpi

    int num;
    int *const cpi = &num;  // 指向 不是const 的 const pointer

/*
===============================
# int *const cpi = &num; 代表了 :

  - cpi 必須初始為指向「不是常數的變數」。因為cpi是「const pointer」
    
    e.g. : int *const cpi = &num;    
    
  - cpi 指標無法修改。表示永遠都指到num，無法修改。 因為cpi是「const pointer」

  - cpi 指到的資料可以修改。表示num的值可以修改。
===============================
*/
    const int limit = 500;  // 「整數常數」，值無法修改
    //int *const cpi1 = &limit;  // 語法錯誤
    // 語法錯誤，「指標常數」cpi指到「整數常數」limit，表示cpi 指到的資料可以修改，這不符合預期。
    // warning: initialization discards ‘const’ qualifier from pointer target type [-Wdiscarded-qualifiers]

    *cpi = limit;   // 合法
    *cpi = 25;      // 合法

#endif

#if (EXAMPLE == 8)  // 8 : e.g. > #define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))
    
#define ARRAYSIZE(arr) (int)(sizeof(arr)/sizeof(*arr))

/*
- ARRAYSIZE(arr) : 算出array裡面有幾個element，8個
- sizeof(arr) : array裡面 Total 幾個bytes
- sizeof(*arr) : 每單位 element 是 幾個bytes
*/
    int array[] =
    {
        0x12, 0x34,
        0x56, 0x78,
        0x12, 0x34,
        0x56, 0x78,
    };

    printf("ARRAYSIZE(array) %d, sizeof(array) %d, sizeof(*array) %d\n", 
        ARRAYSIZE(array), (int)sizeof(array), (int)sizeof(*array));
    // 螢幕輸出 > ARRAYSIZE(array) 8, sizeof(array) 32, sizeof(*array) 4

#endif

    return 0;
}



/*
===============================
printf("\n\033[1;35m[walter]+++++++++++++++++++++++++[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
printf("\n\033[1;35m[walter]-------------------------[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
===============================

int main(int argc, char *argv[]) {
    
    printf("arguments numbers : %d\n", argc);   // argc : 所帶參數的數目

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : 一個陣列，它會分拆所帶的參數放到陣列內
    }
    printf("\n");
    return 0;
}

# 螢幕輸出結果

cc@myfirst$gcc Temp_C_Code.c -o test
cc@myfirst$./test

arguments numbers : 1
[0] ./test



cc@myfirst$./test walter

arguments numbers : 2
[0] ./test
[1] walter



cc@myfirst$./test w a l t e r

arguments numbers : 7
[0] ./test
[1] w
[2] a
[3] l
[4] t
[5] e
[6] r



cc@myfirst$./test 1 2 3 4

arguments numbers : 5
[0] ./test
[1] 1
[2] 2
[3] 3
[4] 4

===============================
# 參考文件 :

C/C++ 程式設計教學：main 函數讀取命令列參數，argc 與 argv 用法
https://blog.gtwang.org/programming/c-cpp-tutorial-argc-argv-read-command-line-arguments/


MAIN(int argc, char *argv[ ]) 之用法
https://blog.xuite.net/tzeng015/twblog/113273095

===============================
*/


