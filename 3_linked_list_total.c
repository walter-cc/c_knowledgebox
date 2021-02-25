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


# �ѦҤ�� :
��Ƶ��c��ǫ��� �w �J����n��, 3/e�A���A��


# Node = Data field + link field

# ���|�اΦ� :

    - ��V�쵲��C (Singly Linked List)

    - �����쵲��C (Circular Linked List)

    - ���V�쵲��C (Doubly Linked List)

    - ���V�����쵲��C (Circular Doubly Linked List)


# Linked List �S�� : �i�R���Ӧ��Ī��Q�Υi�ΰO����Ŷ��C�ڭ̤��ӭ���ϥΪ̦b�{������L�{���ϥΪ��`�I�ƶq�A�]���Ӱt�m�L�h���|�Ψ쪺�O����C�ڭ̥����ǥ�C�y�����ʺA�O����t�m�禡�umalloc()�v�Ӳ��ͷs�`�I�C

===============================

#if 0
    //================================================
    printf("arguments numbers : %d\n", argc);   // argc : �ұa�Ѽƪ��ƥ�

    for (i = 0; i < argc; i++) {
        printf("[%d] %s\n", i, argv[i]);    // argv : �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
    }
    printf("\n");
    //================================================
#endif

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


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : ��X�r���`�ơA���t'\0'
#include <stdlib.h>     // for malloc(), free() functions


#define EXAMPLE 2
/*
1 : e.g. > ²����V�쵲��C (Singly Linked List)
2 : e.g. > ��V�쵲��C (Singly Linked List) ����sample code
3 : e.g. > ���V�쵲��C (Doubly Linked List) ����sample code
*/

#define false   0
#define true    1

#if (EXAMPLE == 1)  // 1 : e.g. > ²����V�쵲��C (Singly Linked List)

struct sr {
    int i ;         // Data field
    struct sr *p;   // link field�C�u�ۧڰѦҾ���v�A����linked list��Ƶ��c�����n����C
};

#endif


#if (EXAMPLE == 2)  // 2 : e.g. > ��V�쵲��C (Singly Linked List) ����sample code

struct Node {           // ��V�쵲��C (Singly Linked List)
    int data;           // Data field
    struct Node *link;  // link field�C�u�ۧڰѦҾ���v�A����linked list��Ƶ��c�����n����C
};

typedef struct Node node;
typedef node *nodePointer;  // ���V�unode�v�� pointer

// �t�m�@�ӳ�V�쵲��C(Singly Linked List) �`�I(Node)
nodePointer GetNode()
{
    nodePointer NewNode;        // nodePointer :  ���V�unode�v�� pointer

    NewNode = (nodePointer) malloc(sizeof(node));   // sizeof(node) : �t�m�@�Ӹ`�I�һݭn���O����
                                                    // NewNode : ���V�s���Ŷ�
    if(NewNode == NULL)
        printf("memory is not enough\n");

    return NewNode;         // �^�Ǥ@�ӫ��V�u�s��node�v�� pointer
}

// ���J�s�`�I�bm�`�I����A���C = L -> m -> a -> NULL
int insertAfter(nodePointer L, nodePointer m, int d)    // L : List Head(�Ĥ@�Ӹ`�I), m : �Q���w���`�I, d : �s�`�I����
{
    nodePointer n = GetNode();  // ���o�@�ӷs�`�I��address, n

    if(n == NULL)
        return false;

    // �s�`�I n->NULL
    n->data = d;
    n->link = NULL;

    // 26->18->15->29->32->12->NULL
    // m�`�I = 18, d�`�I = 99

    if(m != NULL)
    {
        // �U����涶�Ǥ��i���
        n->link = m->link;      // L -> m -> a -> NULL  �ܦ�  L -> m,   n -> a -> NULL�C ���� : �쥻��2�ťD��(m)�]���ɩx�A�ҥH��쥻����U(m->link)�浹�s��2�ťD��(n)
        m->link = n;            // L -> m,   n -> a -> NULL  �ܦ�  L -> m -> n -> a -> NULL�C ���� : �s��2�ťD��(n)�N�ܦ�1�ťD��(m)����U
    }
    else    // ��C�쥻�O�Ŧ�C
        L = n;                  // L -> n

    return true;
}

// �`�ǫ��X��Ӧ�C
void LinkListTraverse(nodePointer L)        // L : List Head(�Ĥ@�Ӹ`�I)
{
    nodePointer w = L;      // �u�@����w���V�Ĥ@�Ӹ`�I�A �u�@���Хi���ʡA���������� for(i = 0;i < x;i++) �� i

    while(w != NULL)        // �b�٨S��F�̫�@�Ӹ`�I��
    {
        printf("%d->", w->data);    // ���L�ҫ����`�I��
        w = w->link;                // ���ʨ�U�@�Ӹ`�I
    }
    printf("NULL\n");
}

// �إߤ@�ӳ�V�쵲��C (Singly Linked List)�A�Ѱ}�C���Ѹ`�Idata��
// data : �}�C�An : �}�C�����ƥ�
nodePointer CreateAll(int *data, int x)  /* �p�ը���  4-2 */
{
    nodePointer L = NULL;           // nodePointer :  ���V�unode�v�� pointer
    int i;

    for(i = x - 1; i >= 0; i--)     // �q�}�C���̫�@�Ӥ����}�l
    {
        nodePointer n = GetNode();   // ���o�@�ӷs�`�I��address, n

        if(n == NULL)
            exit(1);

        // data[6] = 26, 18, 15, 29, 32, 12,

        n->data = data[i];   // �N�}�C��i�ӭȶ�J�`�I
        n->link = L;         // �N�Ӹ`�I���VNULL
        L = n;               // �N�ӷs�`�I��address��L�A���P��Ӹ`�I�ܦb�̫�@��
        printf("�b��C�}�Y�B���J�@�Ӹ`�I%d.....OK!\n",data[i]);
    }
/*
// �ù���X >
===============================

�b��C�}�Y�B���J�@�Ӹ`�I12.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I32.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I29.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I15.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I18.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I26.....OK!

====================================
*/
    return L;   // �N�Ĥ@�Ӹ`�I��address�^��

}

/*
- �R��m�`�I�A���C = L -> m -> a -> NULL
- �R��m�`�I�e�A�����n�����Dm�`�I���e�@�өM��@�Ӹ`�I
- m->link : ��m�`�I����@�Ӹ`�I
- PreNode : ��m�`�I���e�@�Ӹ`�I�A�z�L�j��ӧ�C
*/
nodePointer PreNode(nodePointer L, nodePointer m)   // L : List Head(�Ĥ@�Ӹ`�I), m : �Q���w���`�I
{
    nodePointer B = L;

    while((B != NULL) && (B->link != m)) // ���٨S��̫�@�Ӹ`�I�A�H���٨S���m�`�I���e�@�Ӹ`�I��
    {
        B = B->link;        // ���ʨ�U�@�Ӹ`�I
    }

    return B;   // ��B��NULL�ɡA��ܨS���m�`�I�A�]�� ��B��NULL�� = �w�g���̫�@�Ӹ`�I�F
}

int DeleteNode(nodePointer L, nodePointer m)    // L : List Head(�Ĥ@�Ӹ`�I), m : �Q���w���`�I
{
    nodePointer B;

    if(L == m)          // �u���@�Ӹ`�I
        return false;

    B = PreNode(L,m);   //��m�`�I���e�@�Ӹ`�I

    if(B == NULL)       // ��B��NULL�ɡA��ܨS���m�`�I�A�]�� ��B��NULL�� = �w�g���̫�@�Ӹ`�I�F
        return false;

    B->link = m->link;  // ��um����@�Ӹ`�I�v�����um���e�@�Ӹ`�I��link�v
    free(m);            // �M������m�`�I���O����Ŷ�

    return true;
}

// �s����ӳ�V�쵲��C (Singly Linked List) L1, L2
nodePointer Concatenate(nodePointer L1, nodePointer L2)
{
    nodePointer w = L1;

    if(w != NULL)   // L1�����Ŧ�C
    {
        while(w->link != NULL)  // ���٨S��̫�@�Ӹ`�I
            w = w->link;        // �ܦ� L -> ... -> w -> NULL�A�Nw���ʨ�L1���̫�@�Ӹ`�I

        w->link = L2;           // �NL2���Y�`�I(List Head)�s��L1���̫�@�Ӹ`�I
    }
    else            // L1�쥻�O�Ŧ�C
        L1 = L2;

    return L1;
}
#endif




/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

#if (EXAMPLE == 1)  // 1 : e.g. > ²����V�쵲��C (Singly Linked List)

                    // first -> sr1 -> sr2 -> NULL

    struct sr *first;       // List Head�C�@��|�ϥΤ@�ӡu��C�Y�v(List Head)�ӫ��V�Y�`�I(sr1)�Cfirst = &sr1;
    struct sr sr1, sr2;     // �ŧi2�Ӹ`�I

    first = &sr1;           // �ϥ� : first -> sr1
    sr1.i = 10;

    sr1.p = &sr2;           // �ϥ� : sr1 -> sr2
    sr2.i = 30;

    sr2.p = NULL;           // �������V�ۦP���c�骺�ܼơA�άONULL�C sr2 -> NULL
    (*(sr1.p)).i = 40;      // ����sr2.i���ȡA*(sr1.p) = sr2

    printf("sr2.i = %d, (*(sr1.p)).i = %d\n", sr2.i, (*(sr1.p)).i);

/*
// �ù���X >
===============================
// first -> sr1 -> sr2 -> NULL
===============================
*/

#endif


#if (EXAMPLE == 2)  // 2 : e.g. > ��V�쵲��C (Singly Linked List) ����sample code

                    // first -> sr1 -> sr2 -> NULL

    // �ϥ� : first ->
    nodePointer first = NULL;           // �ŧi���V�unode�v�� pointer�AList Head

    int data[6] = {26, 18, 15, 29, 32, 12};
    int i;

    printf("matrix data[%d] = ", (int)(sizeof(data)/sizeof(*data))); // (sizeof(data)/sizeof(*data)) : ��X�X�Ӥ���
    // �ù���X >  matrix data[6] =

    for(i = 0; i < (int)(sizeof(data)/sizeof(*data)); i++)
        printf("%d, ", data[i]);
        // �ù���X >  26, 18, 15, 29, 32, 12,

    printf("\n\n");


    /*================= �p�ը���  4-2 =================*/
    // �إߤ@�ӳ�V�쵲��C (Singly Linked List)�A�Ѱ}�C���Ѹ`�Idata��
    printf("�إߤ@�ӳ�V�쵲��C (Singly Linked List)�A�Ѱ}�C���Ѹ`�Idata��\n");

    // first = CreateAll(data, 6);
    first = CreateAll(data, (int)(sizeof(data)/sizeof(*data)));     // �ϥ� : first -> data[i] -> ...
    LinkListTraverse(first);    // �`�ǫ��X��Ӧ�C

/*
// �ù���X >
===============================

26->18->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("���J�s�`�I�bm�`�I����\n");
    {
        int d = 99;   // �s�`�I����

        // ���J�s�`�I�bm�`�I����
        printf("m�`�I = %d, �s�`�I = %d\n", first->link->data, d);

        insertAfter(first, first->link, d);     // L : List Head(�Ĥ@�Ӹ`�I), m : �Q���w���`�I, d : �s�`�I����
        LinkListTraverse(first);                // �`�ǫ��X��Ӧ�C
    }
/*
// �ù���X >
===============================

���J�s�`�I�bm�`�I����
m�`�I = 18, �s�`�I = 99
26->18->99->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("�R��m�`�I\n");
    {
        // ���J�s�`�I�bm�`�I����
        printf("�R��m�`�I = %d\n", first->link->link->data);

        DeleteNode(first, first->link->link);    // L : List Head(�Ĥ@�Ӹ`�I), m : �Q���w���`�I
        LinkListTraverse(first);                    // �`�ǫ��X��Ӧ�C
    }
/*
// �ù���X >
===============================

�R��m�`�I
�R��m�`�I = 99
26->18->15->29->32->12->NULL

====================================
*/

    printf("====================================\n\n");
    printf("�s����ӳ�V�쵲��C (Singly Linked List) L1, L2\n");
    {
        nodePointer L1 = NULL, L2 = NULL;   // �ŧi2�� List Head
        int d1[3] = {26,18,15};
        int d2[3] = {26,18,15};

        L1 = CreateAll(d1, (int)(sizeof(d1)/sizeof(*d1)));
        LinkListTraverse(L1);
        printf("\n");

        L2 = CreateAll(d2, (int)(sizeof(d2)/sizeof(*d2)));
        LinkListTraverse(L2);
        printf("\n");

        L1 = Concatenate(L1,L2);    // �s����ӳ�V�쵲��C (Singly Linked List) L1, L2

        printf("L1 + L2\n");
        LinkListTraverse(L1);
    }

/*
// �ù���X >
===============================


matrix data[6] = 26, 18, 15, 29, 32, 12,

�إߤ@�ӳ�V�쵲��C (Singly Linked List)�A�Ѱ}�C���Ѹ`�Idata��
�b��C�}�Y�B���J�@�Ӹ`�I12.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I32.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I29.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I15.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I18.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I26.....OK!
26->18->15->29->32->12->NULL
====================================

���J�s�`�I�bm�`�I����
m�`�I = 18, �s�`�I = 99
26->18->99->15->29->32->12->NULL
====================================

�R��m�`�I
�R��m�`�I = 99
26->18->15->29->32->12->NULL
====================================

�s����ӳ�V�쵲��C (Singly Linked List) L1, L2
�b��C�}�Y�B���J�@�Ӹ`�I15.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I18.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I26.....OK!
26->18->15->NULL

�b��C�}�Y�B���J�@�Ӹ`�I15.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I18.....OK!
�b��C�}�Y�B���J�@�Ӹ`�I26.....OK!
26->18->15->NULL

L1 + L2
26->18->15->26->18->15->NULL


===============================
*/

#endif


    return 0;
}




