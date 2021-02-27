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


# typeof(x) : ����u�A����x ���ܶq�����v�C


typeof(int *)

int *x;
typeof(x)  y;       // �۷�� int *y
typeof(*x) y;       // �۷�� int y
typeof(&x) y;       // �۷�� int **x;


===============================
# �ù���X���G



===============================
# �ѦҤ�� :

C�y����gcc�X�i�y�k(6)-typeof�����ޥ�
https://kknews.cc/code/6e44g3p.html

===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : ��X�r���`�ơA���t'\0'
#include <stdlib.h>     // for malloc(), free() functions

struct MY_DATA {

    int Data_A;
    int Data_B;
    int Data_C;

};



/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

    int x;
    char y;
    struct MY_DATA z;

    typeof(x) x1;       // �۷�� int x1
    typeof(y) y1;       // �۷�� char y1
    typeof(z) z1;       // �۷�� struct MY_DATA z1

    printf("sizeof(x) = %ld, sizeof(x1) = %ld\n", sizeof(x), sizeof(x1));
    printf("sizeof(y) = %ld, sizeof(y1) = %ld\n", sizeof(y), sizeof(y1));
    printf("sizeof(z) = %ld, sizeof(z1) = %ld\n", sizeof(z), sizeof(z1));
/*
===============================
# �ù���X���G

sizeof(x) = 4, sizeof(x1) = 4
sizeof(y) = 1, sizeof(y1) = 1
sizeof(z) = 12, sizeof(z1) = 12

===============================
*/
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

