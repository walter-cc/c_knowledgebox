/*===============================

# ���ɮ׬�ANSI�ɮ�

# �ڭ̥i�H�Q��**gcc -E**���[�ݵ{���X�Q�i�}���᪺�ˤl
gcc -E test.c

# �s�W�sĶ�M����B�J :

gcc test.c -o test
./test

��

1) gcc -c hello.c                   // ���ͥؼ���(object file) hello.o
2) gcc -o hello hello.o          // ���Ͱ�����(execute file) hello
3) ./hello                           // ���� execute file "hello"

��

gcc -o hello hello.c

===============================
# ���d�ҥi�H�ݨ� : �u�ߡv


# ���Ъ��򥻷�����²�� : �N�O�ӡu�s��O�����}�v���ܼơC

# ��ƫ��� (Function pointer) :

    - ���M��Ƥ��O�ܼơA�����b�O�Ф������@�Ӧ�}(��ƪ��_�l��})�A
    �N����}���w���Y�@�ӫ��СA����K�u�i�Q�Φ����ЩI�s�Ө�ơv�C
    
    - ���y�ܻ��A�o�Ӷ��q�i�N���з����A�A�U�Ӷ��q���Хi�����B


# ���а}�C (pointers of array) :

    - �@�ذ}�C�A�䤸���Ҭ��u���Сv�C
  

# �`�ƫ��� (constant pointer) :

    - ���V const �� pointer�A
        
      e.g. : const int *pci

    - ���V ���Oconst �� const pointer�A
    
      e.g. : int *const cpi


#define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))

    - ARRAYSIZE(arr) : ��Xarray�̭����X��element�A8��
    - sizeof(arr) : array�̭� Total �X��bytes
    - sizeof(*arr) : �C��� element �O �X��bytes

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
# �ù���X���G



===============================
# �ѦҤ�� :


===============================
*/

#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : ��X�r���`�ơA���t'\0'

#define EXAMPLE 8
/*
1 : simple example
2 : e.g. > �^�Ǥ@�ӫ��Vchar������
           int *op(int a, int b)
3 : e.g. > ��ƫ��� (Function pointer)
            int (*op)(int a, int b)     // �u()�v�����
4 : e.g. > ���а}�C (pointers of array)
5 : e.g. > size of pointer
6 : e.g. > ���V const �� pointer (���V const �� pointer)�Ae.g. : const int *pci
7 : e.g. > ���V���O�`�ƪ����б`�� (���V ���Oconst �� const pointer)�Ae.g. : int *const cpi
8 : e.g. > #define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))
*/

#if (EXAMPLE == 2)
/*
2 : e.g. > �^�Ǥ@�ӫ��Vchar������
           int *op(int a, int b)
*/

char *find(char *st, char ch)   // �^�Ǥ@�ӫ��Vchar������
{
    int count = 0;

    while(ch != st[count] && st[count] != '\0') // �p�G�r��������r�ꪺ��count�A�åB������'\0'���Ʀr���Acount++
    count++;

    if(count == strlen(st))
        return ((char *)0);     // �N0�j���૬��char *�Ǧ^
    else
        return (&st[count]);    // �N�r����}�Ǧ^
}
#endif

#if (EXAMPLE == 3)
/*
3 : e.g. > ��ƫ��� (Function pointer)
            int (*op)(int a, int b)     // �u()�v�����
*/
int add(int a, int b)
{
    return (a + b);
}

int mult(int a, int b)
{
    return (a * b);
}

typedef int (*OP) (int, int);  // �p�G�Ʊ�w�q�@�ӡu��ƫ��Сv�����A

#endif

/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

#if (EXAMPLE == 1)  // 1 : simple example
    //e.g. 1 :
    char ch[]={'g', 'e', 'e', 'k', 's', '\0'};
    printf("Length of string is: %ld\n", strlen(ch));   // strlen : ��X�r���`�ơA���t'\0'
    // �ù���X > Length of string is: 5


    //e.g. 2 :
    char str1[]= "geeks";   // �r���}�C
    printf("Length of string is: %ld\n", strlen(str1));
    // �ù���X > Length of string is: 5


    //e.g. 3 :
    char *str2 = "geeks";
    printf("Length of string is: %ld\n", strlen(str2));
    // �ù���X > Length of string is: 5
#endif

#if (EXAMPLE == 2)
/*
2 : e.g. > �^�Ǥ@�ӫ��Vchar������
           int *op(int a, int b)
*/
    char *find(char *st, char ch);
    char s[80], *ptr, c;

    printf("Input a string : ");
    fgets(s, sizeof(s), stdin);     // ���o�ϥΪ̿�J����Ӧr��A���]�A���U Enter
    // �ù���X > Input a string : walter is good

    printf("string is : ");
    puts(s);    // ��X��Ӧr��A�|�����i�洫��
    // �ù���X > string is : walter is good


    printf("Input a character : ");
    c = getchar();      // ���o�ϥΪ̿�J��"�r��"
    // �ù���X > Input a character : g

    putchar(c);         // �u�Q��X�@��"�r��"
    putchar('\n');
    // �ù���X > g


    ptr = find(s,c);

    if(ptr)
        printf("Address of %c is : %p\n", c, ptr);  // %c : �H�r���Φ��C�Lchar���A�����
    else
        printf("Not found\n");

/*
// �ù���X >
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
3 : e.g. > ��ƫ��� (Function pointer)
            int (*op)(int a, int b)     // �u()�v�����
*/

    int (*op1)(int a, int b);   // �ŧi�@��function pointer�A�^�ǭȬOint�A�ǤJ�ѼƬO(int, int)
    
    OP op2 = add;               // ������prototype "OP" �ӫŧi function pointer
    op1 = add;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

    op1 = mult;
    op2 = mult;
    printf("op1(3,5) = %d, op2(3,5) = %d\n", op1(3,5), op2(3,5));

/*
// �ù���X >
===============================
op1(3,5) = 8, op2(3,5) = 8
op1(3,5) = 15, op2(3,5) = 15
===============================
*/
#endif

#if (EXAMPLE == 4)  // 4 : e.g. > ���а}�C (pointers of array)

    // �r��}�C : ���O�O����Ŷ�
    static char days[7][10] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    // ���а}�C (pointers of array)
    static char *DAYS[7] = {    // �@�Ӱ}�C��7�Ӥ����A�����Ҭ����Vchar������
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    printf("*DAYS[3] = %c\n", *DAYS[3]);            // ��4�Ӥ�������1�Ӧr��
    printf("**(DAYS + 3) = %c\n", **(DAYS + 3));    // ��4�Ӥ�������1�Ӧr��
    printf("DAYS[3][0] = %c\n", DAYS[3][0]);        // ��4�Ӥ�������1�Ӧr��
    printf("DAYS[2] = %s\n", DAYS[2]);              // ��3�Ӥ������r��
    printf("*(DAYS + 2) = %s\n", *(DAYS + 2));      // ��3�Ӥ������r��

/*
// �ù���X >
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

    char *x;                    // ���Vchar��pointer
    int *y;                     // ���Vint��pointer
    char **a;                   // ���V�@�ӡu���Vchar��pointer�v��pointer
    char *b[20];                // ��20�ӫ��Vchar��pointer�A�s���u���а}�C�v
    char (*c)[20];              // ���Vchar[20]�}�C��pointer
    char (*d)[20][1];           // ���Vchar[20][1]�}�C��pointer
    int (*pt)(int a, int b);    // ���Vint(int a, int b) ���u��ƫ��Сv (Function pointer)

    printf("sizeof(x) = %d, sizeof(*x) = %d\n", (int)sizeof(x) , (int)sizeof(*x));  
    // sizeof(x) : pointer ���j�p�Asizeof(*x) : x �ҫ��V�� char ���j�p
    
    printf("sizeof(y) = %d, sizeof(*y) = %d\n", (int)sizeof(y), (int)sizeof(*y));   
    // sizeof(y) : pointer ���j�p�Asizeof(*y) : y �ҫ��V�� int ���j�p
    
    printf("sizeof(a) = %d, sizeof(*a) = %d\n", (int)sizeof(a), (int)sizeof(*a));   
    // sizeof(a) : pointer ���j�p�Asizeof(*a) : a �ҫ��V���u���Vchar��pointer�v���j�p
    
    printf("sizeof(b) = %d, sizeof(*b) = %d\n", (int)sizeof(b), (int)sizeof(*b));   
    // sizeof(b) : pointer ���j�p�Asizeof(*b) : b �ҫ��V�� char ���j�p
    
    printf("sizeof(c) = %d, sizeof(*c) = %d\n", (int)sizeof(c), (int)sizeof(*c));   
    // sizeof(c) : pointer ���j�p�Asizeof(*c) : c �ҫ��V�� char[20]�}�C ���j�p
    
    printf("sizeof(d) = %d, sizeof(*d) = %d\n", (int)sizeof(d), (int)sizeof(*d));   
    // sizeof(d) : pointer ���j�p�Asizeof(*d) : d �ҫ��V�� char[20][1]�}�C ���j�p
    
    printf("sizeof(pt) = %d, sizeof(*pt) = %d\n", (int)sizeof(pt), (int)sizeof(*pt));   
    // sizeof(pt) : pointer ���j�p�Asizeof(*pt) : pt �ҫ��V�� int(int a, int b) ���j�p

/*
// �ù���X >
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


#if (EXAMPLE == 6)  // 6 : e.g. > ���V const �� pointer (���V const �� pointer)�Ae.g. : const int *pci
    
    int num = 5;
    const int limit = 500;  // �u��Ʊ`�ơv�A�ȵL�k�ק�
    int *pi;                // ���V�u��ơv������
    const int *pci;         // ���V�u��Ʊ`�ơv�����СC const int *pci; �άO int const *pci; ���i�H

/*
===============================
# pci �ŧi�����V�u��Ʊ`�ơv�����ХN��F :

  - pci�i�H���������V��L�u��Ʊ`�ơv�Ce.g. : pci = &limit;     �䤤 const int limit = 500;

  - pci�i�H���������V��L�u�D��Ʊ`�ơv�Ce.g. : pci = &num;      �䤤 int num = 5;

  - pci�i�H�z�L�u�ѰѦҡvŪ���ƭȡCe.g. : printf("value %d\n", *pci);

  - pci�L�k�z�L�u�ѰѦҡv���ܫ��V����}���e�Ce.g. : *pci = 200;
===============================
*/
    pi = &num;
    pci = &limit;

    printf("num - address %p value %d\n", &num, num);
    printf("limit - address %p value %d\n", &limit, limit);
    printf("pi - address %p value %p\n", &pi, pi);
    printf("pci - address %p value %p\n", &pci, pci);

    printf("value %d\n", *pci);     // �ѰѦҡu�`�ƫ��Сv�A�X�k�B���n

    pci = &num; // �X�k
    /*
    ===============================
    *pci = 200;
    �y�k���~�A���л{���u�쪺�ܼƬO�u��Ʊ`�ơv�A�����\�z�L���Эק鷺�e�A�����M�i�H�z�Lnum�ק鷺�e�A�u�O�L�k�z�Lpci�i��ק�C
    // error: assignment of read-only location ��*pci��
    ===============================
    */

/*
// �ù���X >
===============================
num - address 0x7ffdc4c04f00 value 5
limit - address 0x7ffdc4c04f04 value 500
pi - address 0x7ffdc4c04f08 value 0x7ffdc4c04f00
pci - address 0x7ffdc4c04f10 value 0x7ffdc4c04f04
value 500
===============================
*/

#endif

#if (EXAMPLE == 7)  // 7 : e.g. > ���V���O�`�ƪ����б`�� (���V ���Oconst �� �uconst pointer�v)�Ae.g. : int *const cpi

    int num;
    int *const cpi = &num;  // ���V ���Oconst �� const pointer

/*
===============================
# int *const cpi = &num; �N��F :

  - cpi ������l�����V�u���O�`�ƪ��ܼơv�C�]��cpi�O�uconst pointer�v
    
    e.g. : int *const cpi = &num;    
    
  - cpi ���еL�k�ק�C��ܥû�������num�A�L�k�ק�C �]��cpi�O�uconst pointer�v

  - cpi ���쪺��ƥi�H�ק�C���num���ȥi�H�ק�C
===============================
*/
    const int limit = 500;  // �u��Ʊ`�ơv�A�ȵL�k�ק�
    //int *const cpi1 = &limit;  // �y�k���~
    // �y�k���~�A�u���б`�ơvcpi����u��Ʊ`�ơvlimit�A���cpi ���쪺��ƥi�H�ק�A�o���ŦX�w���C
    // warning: initialization discards ��const�� qualifier from pointer target type [-Wdiscarded-qualifiers]

    *cpi = limit;   // �X�k
    *cpi = 25;      // �X�k

#endif

#if (EXAMPLE == 8)  // 8 : e.g. > #define ARRAYSIZE(arr) (sizeof(arr)/sizeof(*arr))
    
#define ARRAYSIZE(arr) (int)(sizeof(arr)/sizeof(*arr))

/*
- ARRAYSIZE(arr) : ��Xarray�̭����X��element�A8��
- sizeof(arr) : array�̭� Total �X��bytes
- sizeof(*arr) : �C��� element �O �X��bytes
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
    // �ù���X > ARRAYSIZE(array) 8, sizeof(array) 32, sizeof(*array) 4

#endif

    return 0;
}



/*
===============================
printf("\n\033[1;35m[walter]+++++++++++++++++++++++++[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
printf("\n\033[1;35m[walter]-------------------------[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
===============================

int main(int argc, char *argv[]) {
    
    printf("arguments numbers : %d\n", argc);   // argc : �ұa�Ѽƪ��ƥ�

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
    }
    printf("\n");
    return 0;
}

# �ù���X���G

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
# �ѦҤ�� :

C/C++ �{���]�p�оǡGmain ���Ū���R�O�C�ѼơAargc �P argv �Ϊk
https://blog.gtwang.org/programming/c-cpp-tutorial-argc-argv-read-command-line-arguments/


MAIN(int argc, char *argv[ ]) ���Ϊk
https://blog.xuite.net/tzeng015/twblog/113273095

===============================
*/


