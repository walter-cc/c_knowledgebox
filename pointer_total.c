/*===============================
    新增編譯和執行步驟 :
    gcc pointer_total.c -o test
    ./test
===============================
# 此範例可以看到 : 「習」

# 指標的基本概念很簡單 : 就是個存放記憶體位址的變數。

# 函數指標 (Function pointer) :

  - 雖然函數不是變數，但它在記憶中佔有一個位址(函數的起始位址)，將此位址指定給某一個指標，之後便「可利用此指標呼叫該函數」。

  - 換句話說，這個階段可將指標當成函數A，下個階段指標可當成函數B

# 指標陣列 (pointers of array) :

  - 一種陣列，其元素皆為指標。
===============================
# 螢幕輸出結果

===============================*/

#include <stdio.h>
#include <string.h>     // for int strlen(const char *str) : 算出字元總數，不含'\0'

#define EXAMPLE 5
/*
1 : simple example
2 : e.g. > 回傳一個指向char的指標
           int *op(int a, int b)
3 : e.g. > 函數指標 (Function pointer)
            int (*op)(int a, int b)     // ()不能省
4 : e.g. > 指標陣列 (pointers of array)
5 : e.g. > size of pointer
*/


#if (EXAMPLE == 2)
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
int add(int a, int b)
{
    return (a + b);
}

int mult(int a, int b)
{
    return (a * b);
}

typedef int (*OP) (int, int);  // 如果希望定義一個"函數指標"的型態

#endif

int main(void) {

    /*============= example of strlen(ch) ==================*/
#if (EXAMPLE == 1)
    //e.g. 1 :
    char ch[]={'g', 'e', 'e', 'k', 's', '\0'};
    printf("Length of string is: %ld\n", strlen(ch));
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
    char *find(char *st, char ch);
    char s[80], *ptr, c;

    printf("Input a string :");
    fgets(s, sizeof(s), stdin);     // 取得使用者輸入的整個字串，不包括按下 Enter
    // 螢幕輸出 > Input a string :walter is good

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
        printf("Address of %c is:%p\n",c, ptr);
    else
        printf("Not found\n");

// 螢幕輸出 >
/*
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


*/
#endif

#if (EXAMPLE == 3)
    int (*op1)(int a, int b);    // 宣告一個function pointer，回傳值是int，傳入參數是(int, int)
    OP op2 = add;   // 直接用prototype "OP" 來宣告 function pointer
    op1 = add;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

    op1 = mult;
    op2 = mult;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

// 螢幕輸出
/*
op1(3,5) = 8, op2(3,5) = 8
op1(3,5) = 15, op2(3,5) = 15
*/
#endif

#if (EXAMPLE == 4)
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

    printf("*DAYS[3] = %c\n", *DAYS[3]);
    printf("**(DAYS + 3) = %c\n", **(DAYS + 3));
    printf("DAYS[3][0] = %c\n", DAYS[3][0]);
    printf("DAYS[2] = %s\n", DAYS[2]);
    printf("*(DAYS + 2) = %s\n", *(DAYS + 2));

// 螢幕輸出
/*
*DAYS[3] = W
**(DAYS + 3) = W
DAYS[3][0] = W
DAYS[2] = Tuesday
*(DAYS + 2) = Tuesday
*/
#endif

#if (EXAMPLE == 5)

    char *x;            // 指向char的pointer
    int *y;             // 指向int的pointer
    char **a;           // 指向一個"指向char的pointer"的pointer
    char *b[20];        // 有20個指向char的pointer，叫做「指標陣列」
    char (*c)[20];      // 指向char[20]陣列的pointer
    char (*d)[20][0];   // 指向char[20][0]陣列的pointer
    int (*pt)(int a, int b);   // 指向int(int a, int b)的函數的pointer

    printf("sizeof(x) = %d, sizeof(*x) = %d\n", (int)sizeof(x) , (int)sizeof(*x));
    printf("sizeof(y) = %d, sizeof(*y) = %d\n", (int)sizeof(y), (int)sizeof(*y));
    printf("sizeof(a) = %d, sizeof(*a) = %d\n", (int)sizeof(a), (int)sizeof(*a));
    printf("sizeof(b) = %d, sizeof(*b) = %d\n", (int)sizeof(b), (int)sizeof(*b));
    printf("sizeof(c) = %d, sizeof(*c) = %d\n", (int)sizeof(c), (int)sizeof(*c));
    printf("sizeof(d) = %d, sizeof(*d) = %d\n", (int)sizeof(d), (int)sizeof(*d));
    printf("sizeof(pt) = %d, sizeof(*pt) = %d\n", (int)sizeof(pt), (int)sizeof(*pt));

// 螢幕輸出
/*
cc@c_knowledgebox$gcc pointer_total.c -o test
cc@c_knowledgebox$./test
sizeof(x) = 8, sizeof(*x) = 1
sizeof(y) = 8, sizeof(*y) = 4
sizeof(a) = 8, sizeof(*a) = 8
sizeof(b) = 160, sizeof(*b) = 8
sizeof(c) = 8, sizeof(*c) = 20
sizeof(d) = 8, sizeof(*d) = 0
sizeof(pt) = 8, sizeof(*pt) = 1

*/
#endif

    return 0;
}





