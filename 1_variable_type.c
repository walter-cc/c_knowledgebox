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


#if 0
    //================================================
    printf("arguments numbers : %d\n", argc);   // argc : �ұa�Ѽƪ��ƥ�

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
    }
    printf("\n");
    //================================================
#endif

===============================
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

printf("\n\033[1;35m[walter]+++++++++++++++++++++++++[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);
printf("\n\033[1;35m[walter]-------------------------[%s][%d]\n\n\033[0m",__FUNCTION__,__LINE__);


===============================
*/


#include <stdio.h>          // standard I/O

void a(void);
void b(void);
void c(void);

int x = 1;  // global variable

/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

    int i;

    int x = 5;

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5, �|��������ۤv�̪��ܼƫ��A

    {
        int x = 7;
        printf("[%d]x = %d\n",__LINE__ , x);  //  = 7
    }

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5

    a();
    b();
    c();

    a();
    b();
    c();

    printf("[%d]x = %d\n",__LINE__ , x);  // x = 5

    return 0;
}

void a(void)
{
    int x = 25;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 25, x = 25

    ++x;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 26, x = 26
}

void b(void)
{
    static int x = 50;
    printf("[%d]x = %d\n",__LINE__ , x);  //x = 50, x = 51      // static variable

    ++x;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 51, x = 52     // static variable
}

void c(void)
{
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 1, x = 10      // global variable

    x *= 10;
    printf("[%d]x = %d\n",__LINE__ , x);  // x = 10, x = 100    // global variable
}




