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

# offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

- offsetof �w�q�b <linux/stddef.h>
- �Ψӭp��Y�@��struct���c�������۹��ӵ��c�_�l��}�������q( offset )�C
  (���� == ���_�l��}���h�����Z��)


# container_of(PTR, TYPE, MEMBER) :
- container_of �w�q�b <linux/kernel.h>
- ���ݭn�ޥ�offsetof�����A�����@�άO�Ψӡu���ostruct���c���_�l�I�v�A�u�n���D�ӵ��c�����@�Ӧ�������}�A�N�i�H�ϥ�container_of�����Ӻ�X�ӵ��c���_�l��}�C



===============================
# �ù���X���G



===============================
# �ѦҤ�� :

Linux��container_of �P offsetof����
https://myao0730.blogspot.com/2016/09/linuxcontainerof-offsetof.html?m=1

===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : ��X�r���`�ơA���t'\0'
#include <stdlib.h>     // for malloc(), free() functions


// �Ψӭp��Y�@��struct���c�������۹��ӵ��c�_�l��}�������q( offset )
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/*
- TYPE : structure name
- MEMBER : structure member

1. ((TYPE *)0) : �૬�� �uTYPE���Сv���O
2. &((TYPE *)0)->MEMBER : 0 �Q��@��TYPE���_�l�a�}�A�M��A���V�Y����
3. &((TYPE *)0)->MEMBER) : �o��MEMBER����}�C�]���_�l��}���� 0�A�ҥHMEMBER����}�]�N����MEMBER�P�_�l��}0������(offset)�C
4. offsetof(TYPE, MEMBER) : �Ψӭp��Y�@��struct���c�������۹��ӵ��c�_�l��}�������q( offset )
*/


// �Ψӡu���o struct���c TYPE���_�l�I�v
#define container_of(PTR, TYPE, MEMBER) ({\
        const typeof( ((TYPE *)0)->MEMBER ) *__mptr = (PTR);\
              (TYPE *)( (char *)__mptr - offsetof(TYPE,MEMBER) );})
/*
- PTR : ���V�ӵ��c���������O������
- TYPE :  structure name
- MEMBER :  structure member

1. typeof( ((TYPE *)0)->MEMBER ) : ���X�uMEMBER�v����ƫ��O
2. typeof( ((TYPE *)0)->MEMBER ) *__mptr : �w�q�@�ӡu���V MEMBER ���O�����Сv __mptr
3. const typeof( ((TYPE *)0)->MEMBER ) *__mptr = (PTR); : �N����PTR�ǵ�__mptr
4. (TYPE *)( (char *)__mptr - offsetof(TYPE,MEMBER) ); :
   �u__mptr����}�v - �uMEMBER�P���c�_�l�I������(�Q��offsetof)�v = �ӵ��c���_�l�I��}�C
*/


struct MY_DATA {    // ���]�_�l addr = 0x100

    int Data_A;     // ���] addr = 0x100
    int Data_B;     // ���] addr = 0x104, offset of Data_B = 4, 0x104 - 4 = 0x100 = �ӵ��c���_�l�I��}
    int Data_C;
    struct MY_DATA *next;

};



/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

    struct MY_DATA data ;
    struct MY_DATA *ptr;

    data.Data_A = 123;
    data.Data_B = 321;
    data.Data_C = 987;


    int *Data_B_ptr = &data.Data_B;     // the address of Data_B in "struct MY_DATA data"

    /*
        # container_of(PTR, TYPE, MEMBER)
        - PTR : ���V�ӵ��c���������O������
        - TYPE :  structure name
        - MEMBER :  structure member
    */
    ptr = container_of( Data_B_ptr, struct MY_DATA , Data_B );

    printf("\n== the example of container_of ==\n");
    printf("(struct MY_DATA data) addr = %p, addr from container_of = %p\n", &data, ptr);

    if( &data == ptr )
        printf("container_of function is ok!\n\n");

    printf("\n== the example of offsetof ==\n");
    printf("ptr->Data_A = %d\nptr->Data_B = %d\nptr->Data_C = %d\n\n",
        ptr->Data_A,
        ptr->Data_B,
        ptr->Data_C);

    printf("Data_A offset = %ld\n", offsetof(struct MY_DATA, Data_A));
    printf("Data_B offset = %ld\n", offsetof(struct MY_DATA, Data_B));
    printf("Data_C offset = %ld\n", offsetof(struct MY_DATA, Data_C));
    printf("ptr next offset = %ld\n\n", offsetof(struct MY_DATA, next));

    printf("sizeof(struct MY_DATA) = %ld\n", sizeof(struct MY_DATA));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(data.Data_A) = %ld\n", sizeof(data.Data_A));
    printf("sizeof(data.next) = %ld\n", sizeof(data.next));
    printf("sizeof(ptr) = %ld\n", sizeof(ptr));
/*
===============================
# �ù���X���G

== the example of container_of ==
(struct MY_DATA data) addr = 0x7ffe855c6410, addr from container_of = 0x7ffe855c6410
container_of function is ok!


== the example of offsetof ==
ptr->Data_A = 123
ptr->Data_B = 321
ptr->Data_C = 987

Data_A offset = 0
Data_B offset = 4
Data_C offset = 8
ptr next offset = 16

sizeof(struct MY_DATA) = 24
sizeof(int) = 4
sizeof(data.Data_A) = 4
sizeof(data.next) = 8
sizeof(ptr) = 8


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

