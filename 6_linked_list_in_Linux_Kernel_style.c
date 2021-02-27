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


# Node = Data field + link field

# Linked List �i�R���Ӧ��Ī��Q�Υi�ΰO����Ŷ��C�ڭ̤��ӭ���ϥΪ̦b�{������L�{���ϥΪ��`�I�ƶq�A�]���Ӱt�m�L�h���|�Ψ쪺�O����C�ڭ̥����ǥ�C�y�����ʺA�O����t�m�禡�umalloc()�v�Ӳ��ͷs�`�I�C

# Linux kernel�w�q�@�q�ε��c (struct list_head�Akernel\v4.19\include\linux\types.h)�A�ΥH��@���V�쵲��C (Doubly Linked List)

struct list_head {
    struct list_head *next, *prev;
};

�ҥH
struct student {
    char name[16];
    int id;
    struct student *next, *prev;
};
�ܦ�
struct student
{
    char name[16];
    int id;
    struct list_head list;  // �u�n�b�۩w�q�����c���[�Jstruct list_head���c��N�i�H�ϥ�Linux�@�t�C��link-list��ƦӤ��Φۦ漶�g�C
};

# list_head����Marco�PFunction �b kernel\v4.19\include\linux\list.h�AĴ�p�U����define

    - #define LIST_HEAD_INIT(name) { &(name), &(name) }

    - #define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

# ������������c�O�����V�`������A�u���u���w��v�A�ƾڰ�ھڨϥ�������H������ݨD�өw�C

# ��������]�p���� �G �J�M�������]�t�U�ƸU���A����N���u�U�ƸU���ӥ]�t����v�C


===============================
# �ù���X���G



===============================
# �ѦҤ�� :

- Linux��container_of �P offsetof����
https://myao0730.blogspot.com/2016/09/linuxcontainerof-offsetof.html?m=1
- ��Ƶ��c��ǫ��� �w �J����n��, 3/e�A���A��
- Linux Kernel: �j�j�S�n�Ϊ�list_head���c
http://adrianhuang.blogspot.com/2007/10/linux-kernel-listhead.html
- Linux�쵲��Cstruct list_head ��s                          ## 191204 : walter �g�g
https://myao0730.blogspot.com/2016/12/linux.html
- Linux��������X�X�ݳo�@�g�峹�N���F                          ## 191204 : walter �g�g
https://www.cnblogs.com/yangguang-it/p/11667772.html
- Linux Kernel Portability-Data type & Data Structure in Linux kernel (�G)
http://clhjoe.blogspot.com/2012/07/linux-kernel-portability-data-type-data_11.html
- �b�]�a Linux���� �J���g�A�i�ѭ�

===============================
*/


#include <stdio.h>      // standard I/O
#include <string.h>     // for int strlen(const char *str) : ��X�r���`�ơA���t'\0'
#include <stdlib.h>     // for malloc(), free() functions


//=========== list_head ���� Marco �P Function ===========================

/*
- Linux kernel�w�q�@�q�ε��c (struct list_head�Akernel\v4.19\include\linux\types.h)�A�ΥH��@���V�쵲��C (Doubly Linked List)�C
- �u�n�b�۩w�q�����c���[�Jstruct list_head���c��N�i�H�ϥ�Linux�@�t�C��link-list��ƦӤ��Φۦ漶�g�C
*/
struct list_head {
    struct list_head *next, *prev;
};
/*
�ŧi��ӫ��� *next, *prev ���V�ۤv
*/


// 1. �R�A��l�� : 
// �ŧi�@�� struct list_head �����c�ܼƨç@��l�ơA�]�N�O�Nperv�Pnext���Ы��V�ۤv�A�N���ۦ�list���Ū��C
#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)
/*
#define LIST_HEAD(name) \
                struct list_head name = { &(name), &(name) }

�ŧi�@���ܼ� name�A�䤸�� *next, *prev ����l�Ȭ��ۤv����}�A�]�N�O�Nperv�Pnext���Ы��V�ۤv
*/


// 2. �ʺA��l�� :
// �]�i�H�ϥ� INIT_LIST_HEAD �o�Ө禡�Ӫ�l���Y�`�I�A���O�o�˪��@�k�n���ŧi�@ struct list_head�ܼ� �M��A����INIT_LIST_HEAD����l�ơCproject use this
void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}
/*
e.g. :
struct student {
    char name[16];
    int id;
    struct list_head list;
};

struct student stu;
INIT_LIST_HEAD(&stu.list);
*/


// �ˬd�o�Ӧ�C�O�_���šC
int list_empty(const struct list_head *head) {
    return head->next == head;
}
/*
head->next == head : next���Ы��V�ۤv�A��ܦ�List���šC
*/


// __list_add �o�Ө禡�|�N�@�ӷs���`�I�[�J�@��w�����e(prev)/��(next)�ݸ`�I�����A�]�N�O���쥻�۳s��2�Ӻ��I�����|���J�@�ӷs�`�I�C
static  void __list_add(struct list_head *new_lst,
                              struct list_head *prev,
                              struct list_head *next)
{
    next->prev = new_lst;
    new_lst->next = next;
    new_lst->prev = prev;
    prev->next = new_lst;
}
/*
struct list_head *new_lst   : ���V �s�W��node �� pointer
struct list_head *prev      : ���V �e�@��node �� pointer
struct list_head *next      : ���V ��@��node �� pointer


before : prev node <-> next node
after  : prev node <-> new node <-> next node

1. next->prev = new_lst; : new node <- next node�C
   �s�W�`�I����} (new_lst) �Q ��@�Ӹ`�I��prev���� (next->prev) ��
2. new_lst->next = next; : new node <-> next node
   ��@�Ӹ`�I����} (next) �Q �s�W�`�I��next���� (new_lst->next) ��
3. new_lst->prev = prev; : prev node <- new node <-> next node
   �e�@�Ӹ`�I����} (prev) �Q �s�W�`�I��prev���� (new_lst->prev) ��
4. prev->next = new_lst; : prev node <-> new node <-> next node
   �s�W�`�I����} (new_lst) �Q �e�@�Ӹ`�I��next���� (prev->next) ��
*/


/*
- �N__list_add���s�]�ˡA���@�ӷs���`�I�[�J��C���}�Y(�N��ƥ[�J��doubly linked list�̫e��)�A�s�`�I�|�ܦ�HEAD���V��next�A�s�[�J���`�I����O�V�e�ݴ��J�C
- PS: �bLDD�o�Ѥ���o�˪��ާ@��묰Stack(LIFO)�C
*/
void list_add(struct list_head *new_lst,
              struct list_head *head)
{
    __list_add(new_lst, head, head->next);
}
/*
# __list_add(new_lst, head, head->next);

- new_lst       : ���V �s�W��node �� pointer
- head          : ���V �e�@��node �� pointer�C�b�o�̪���Y�`�I
- head->next    : ���V ��@��node �� pointer�C�b�o�̪���Y�`�I���U�@�Ӹ`�I (1st node)

before : head node <-> 1st node
after  : head node <-> new node <-> 1st node
*/


/*
- �N__list_add���s�]�ˡA���@�ӷs���`�I�[�J��C���ݤ��A�s�`�I�|�ܦ�HEAD���V��prev�A�s�[�J���`�I����O�V���ݴ��J�C
- PS: �bLDD�o�Ѥ���o�˪��ާ@��묰Queue(FIFO)�A�ƹ�W���ٯu���ள�ӹ�@Queue�C
*/
void list_add_tail(struct list_head *new_lst, struct list_head *head)
{
    __list_add(new_lst, head->prev, head);
}
/*
# __list_add(new_lst, head->prev, head);

- new_lst       : ���V �s�W��node �� pointer
- head->prev    : ���V �e�@��node �� pointer�C�b�o�̪���Y�`�I���U�@�Ӹ`�I (1st node)
- head          : ���V ��@��node �� pointer�C�b�o�̪���Y�`�I

before : head node <-> 1st node
after  : head node <-> 1st node <-> new node
*/


// @ kernel\v4.19\include\linux\poison.h
/*
* These are non-NULL pointers that will result in page faults
* under normal circumstances, used to verify that nobody uses
* non-initialized list entries.
*/
// LIST_POISON1�PLIST_POISON2�ΨӼаO���ǨS���Q��l�ƥH�ΨS���b�����list���A�����̤��i�Q�X�ݡC
#define POISON_POINTER_DELTA 0
#define LIST_POISON1  ((void *) 0x100 + POISON_POINTER_DELTA)
#define LIST_POISON2  ((void *) 0x200 + POISON_POINTER_DELTA)


/*
- __list_del�o�Ө禡�|�R���Y�@�Ӹ`�I entry�A�o�ݭn�����Dentry���e(prev)/��(next)�ݸ`�I�C
- entry�쥻���e�ݸ`�I��next���з|���Ventry�쥻����ݸ`�I�A
  �ӫ�ݸ`�I��prev���з|���Ventry���e�ݸ`�I�A�o�ˤ@�ӴN�S���䥦�`�I�����з|���Ventry�A�F��R�����ĪG�C
*/
static  void __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}
/*
- prev  : ���V �e�@��node �� pointer�C
- next  : ���V ��@��node �� pointer�C

before : prev node <-> useless node <-> next node
after  : prev node <-> next node

1. next->prev = prev; : prev node <- next node�C
   �e�@�Ӹ`�I����} (prev) �Q ��@�Ӹ`�I��prev���� (next->prev) ��
2. prev->next = next; : new node <-> next node�C
   ��@�Ӹ`�I����} (next) �Q �e�@�Ӹ`�I��next���� (prev->next) ��
*/


// ��list_del���F�I�s__list_del���~�A�ٷ|�Nentry��prev/next���Ы��VLIST_POISON1�PLIST_POISON2�o��ӯS�O��}�C
void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
//    entry->next = LIST_POISON1;
//    entry->prev = LIST_POISON2;
}
/*
- entry->prev  : ���V �e�@��node �� pointer�C
- entry->next  : ���V ��@��node �� pointer�C

- �ȱo�`�N���O�A�R����C�����ɭԷ|�ϥΨ�list_del�禡�A�b�o�̼ȮɱN entry->next = LIST_POISON1 �M entry->prev = LIST_POISON2 �o2����ѱ��A
  �]���ڭ̤��O�b�g�X�ʵ{���ӬO�buser space�ϥΡA�i�H��entry->{prev/next}�]��NULL�A
  �N��ӫ��ШS�����V����F��A�Ϊ̤]�i�H�⥦���s��l�ơA�ϥ�INIT_LIST_HEAD(entry)�C
*/


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

/*
- ���o��doubly linked list�Ҧ���ơC
- �ѩw�q�i�H���D�O�b���X����쵲��C�Apos���@�Ӥu�@���Шë��V�Ĥ@�Ӷ���(head->next)�A�H�����_�I�@���X�ݤU�h�A�פ����O��pos���Vhead�ɡA�N��w�g���X���@��F�C
*/
#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

/*
- �z�L���禡�K���X���c���_�l��}�A�ð����c�૬�K����o���c�����
- �ҥH�Alist_for_each �M ist_entry �o��ӥ����f�t�ϥδN�i�H�s������쵲��C�C
*/
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)


/**
* list_first_entry - get the first element from a list
* @ptr:    the list head to take the element from.
* @type:    the type of the struct this is embedded in.
* @member:    the name of the list_head within the struct.
*
* Note, that list is expected to be not empty.
*/
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
* list_next_entry - get the next element in list
* @pos:    the type * to cursor
* @member:    the name of the list_head within the struct.
*/
#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, typeof(*(pos)), member)

/**
* list_for_each_entry    -    iterate over list of given type
* @pos:    the type * to use as a loop cursor.
* @head:    the head for your list.
* @member:    the name of the list_head within the struct.

list_for_each_entry�A�q�L��W�r�ڭ̤]��q����\��Alist_for_each�O�M������A
�W�[entry���A��ܹM�����ɭԡA�٭n���entry�]���ء^�A�Y�������e�����c���a�}�C
*/
#define list_for_each_entry(pos, head, member)                \
    for (pos = list_first_entry(head, typeof(*pos), member);    \
         &pos->member != (head);                    \
         pos = list_next_entry(pos, member))

/**
* list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
* @pos:    the type * to use as a loop cursor.
* @n:        another type * to use as temporary storage
* @head:    the head for your list.
* @member:    the name of the list_head within the struct.
*/
#define list_for_each_entry_safe(pos, n, head, member)            \
    for (pos = list_first_entry(head, typeof(*pos), member),    \
        n = list_next_entry(pos, member);            \
         &pos->member != (head);                     \
         pos = n, n = list_next_entry(n, member))

static inline void __list_splice(const struct list_head *list,
                 struct list_head *prev,
                 struct list_head *next)
{
    struct list_head *first = list->next;
    struct list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

/**
* list_splice - join two lists, this is designed for stacks
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
static inline void list_splice(const struct list_head *list,
                struct list_head *head)
{
    if (!list_empty(list))
        __list_splice(list, head, head->next);
}

/**
* list_splice_tail - join two lists, each list being a queue
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
static inline void list_splice_tail(struct list_head *list,
                struct list_head *head)
{
    if (!list_empty(list))
        __list_splice(list, head->prev, head);
}
//======================================================================


#define EXAMPLE 5
/*
1 : e.g. > User space ���V�쵲��C (Doubly Linked List) ����sample code
2 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��1�اΦ�
3 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��2�اΦ�
4 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��3�اΦ�
5 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : �V�M�Φ�
*/

#if (EXAMPLE == 1)  // 1 : e.g. > User space ���V�쵲��C (Doubly Linked List) ����sample code

struct My_DATA {
    int Data_1;
    int Data_2;
    int Data_3;
    struct list_head list;
};

// �X�ݾ�Ӧ�C�æL�X��C����address�Mdata���e�C
void print_List(struct list_head *head){

    struct list_head *pos;  // �u�@����
    struct My_DATA *entry;

    printf("\n*********************************************************************************\n");
    printf("(HEAD addr = %p, next = %p, prev = %p)\n", head, head->next, head->prev);

    list_for_each(pos, head) {

        entry = list_entry(pos, struct My_DATA, list);  // ���o�Ӹ`�I���c���_�l�I��}�C

        printf("entry->Data_1 = %d | list addr = %p | next = %p | prev = %p\n",
                entry->Data_1, &entry->list, entry->list.next, entry->list.prev);
    }
    printf("*********************************************************************************\n");

}

// �q��C���ݥ[�J�@�ӷs���`�I
struct My_DATA *add_Node_tail(struct list_head *head){
    struct My_DATA *entry;
    entry = (struct My_DATA*)malloc(sizeof(struct My_DATA));
    list_add_tail(&entry->list, head);
    return entry;
}

// �q��C�e�ݥ[�J�@�ӷs���`�I
struct My_DATA *add_Node(struct list_head *head){
    struct My_DATA *entry;
    entry = (struct My_DATA*)malloc(sizeof(struct My_DATA));
    list_add(&entry->list, head);
    return entry;
}

/*
- �R����@�Ӹ`�I
- �ȱo�`�N���O�A�R����C�����ɭԷ|�ϥΨ�list_del�禡�A�b�o�̼ȮɱN entry->next = LIST_POISON1 �M entry->prev = LIST_POISON2 �o2����ѱ��A
  �]���ڭ̤��O�b�g�X�ʵ{���ӬO�buser space�ϥΡA�i�H��entry->{prev/next}�]��NULL�A
  �N��ӫ��ШS�����V����F��A�Ϊ̤]�i�H�⥦���s��l�ơA�ϥ�INIT_LIST_HEAD(entry)�C
*/
void remove_Node(struct My_DATA *entry){

    printf("\nremove: Data_1 = %d (list %p, next %p, prev %p)\n",
            entry->Data_1, &entry->list, entry->list.next, entry->list.prev);

    list_del(&entry->list);
    free(entry);
    entry = NULL;
}

// �P����Ӧ�C
void free_List(struct list_head *head)
{
    struct list_head *pos;      // �u�@����
    struct My_DATA *entry;

    list_for_each(pos, head) {

        entry = list_entry(pos, struct My_DATA, list);

        printf("\nFree: entry->Data_1 = %d | list addr = %p | next = %p | prev = %p\n",
                entry->Data_1, &entry->list, entry->list.next, entry->list.prev);

        free(entry);
        entry = NULL;
    }
}

#endif  // #if (EXAMPLE == 1)

#if (EXAMPLE == 2)  // 2 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��1�اΦ�
struct person
{
    struct list_head list;
    int age;
};
#endif // #if (EXAMPLE == 2)

#if (EXAMPLE == 3)  // 3 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��2�اΦ�
/*
��������O���Y�`�I���A�@��Ө��Y�`�I���ƾڰ�ڭ̤��ϥΡA���]���ϥ��Y�`�I�ƾڰ�O��������ת���{��k�C
�Y�`�I��ꤣ�O���ݪ��A���@���ǲߡA�ڭ̥i�H��{�@�U
*/
struct person_head {        // �s�W�Y�`�I
    int len;
    struct list_head list;
};

struct person {
    int age;
    struct list_head list;
};
#endif // #if (EXAMPLE == 3)

#if (EXAMPLE == 4)  // 4 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��3�اΦ�
struct person
{
    int age;
    struct list_head list;
};
#endif // #if (EXAMPLE == 4)

#if (EXAMPLE == 5)  // 5 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : �V�M�Φ�
struct person {
    int age;
    struct list_head list;
};
struct My_DATA {
    int Data_1;
    int Data_2;
    int Data_3;
    struct list_head my_data_list;
};
#endif // #if (EXAMPLE == 5)


/*
- argc : argument count(�Ѽ��`�M)���Y�g�A�N��]�A���O�������ѼƭӼơC
- argv :argument value ���Y�g�C �@�Ӱ}�C�A���|����ұa���ѼƩ��}�C��
*/
int main(int argc, char *argv[]) {

#if (EXAMPLE == 1)  // 1 : e.g. > User space ���V�쵲��C (Doubly Linked List) ����sample code
    int i;

    printf("arguments numbers : %d\n", argc);

    for (i = 0; i < argc; i++)
        printf("[%d] %s\n", i, argv[i]);

    LIST_HEAD(HEAD);    // ��l�Ƥ@��List

    struct My_DATA *itemPtr_1 = add_Node(&HEAD);    // �q��C�e�ݥ[�J�@�ӷs���`�I�AitemPtr_1 : �s�`�I����}
    itemPtr_1->Data_1 = 100 ;

    struct My_DATA *itemPtr_2 = add_Node(&HEAD);
    itemPtr_2->Data_1 = 200 ;

    struct My_DATA *itemPtr_3 = add_Node(&HEAD);
    itemPtr_3->Data_1 = 300 ;

    struct My_DATA *itemPtr_4 = add_Node(&HEAD);
    itemPtr_4->Data_1 = 400 ;

    print_List(&HEAD);      // �X�ݾ�Ӧ�C�æL�X��C����address�Mdata���e�C

    remove_Node(itemPtr_3); // �R����@�Ӹ`�I
    print_List(&HEAD);

    free_List(&HEAD);       // �P����Ӧ�C

/*

===============================
# ���浲�G :

�q���G�i�H�ݥX��C���O�V�e�ݥ[�J�A�b�L�X��C�ɱqhead->next�}�l�L�X�A��M�P����C�ɤ]�O�@�˱qhead->next�}�l�A�o�˪��B�@�Ҧ��N�p�PLDD�Ѥ�������LIFO(��i���X)�Ҧ��C

[mtk18157@mtkslt207 testhome]$gcc list_linux_kernel_sample.c -o test
[mtk18157@mtkslt207 testhome]$./test
arguments numbers : 1
[0] ./test

*********************************************************************************
(HEAD addr = 0x7fffd15cf4a0, next = 0x1d740b0, prev = 0x1d74020)
entry->Data_1 = 400 | list addr = 0x1d740b0 | next = 0x1d74080 | prev = 0x7fffd15cf4a0
entry->Data_1 = 300 | list addr = 0x1d74080 | next = 0x1d74050 | prev = 0x1d740b0
entry->Data_1 = 200 | list addr = 0x1d74050 | next = 0x1d74020 | prev = 0x1d74080
entry->Data_1 = 100 | list addr = 0x1d74020 | next = 0x7fffd15cf4a0 | prev = 0x1d74050
*********************************************************************************

remove: Data_1 = 300 (list 0x1d74080, next 0x1d74050, prev 0x1d740b0)

*********************************************************************************
(HEAD addr = 0x7fffd15cf4a0, next = 0x1d740b0, prev = 0x1d74020)
entry->Data_1 = 400 | list addr = 0x1d740b0 | next = 0x1d74050 | prev = 0x7fffd15cf4a0
entry->Data_1 = 200 | list addr = 0x1d74050 | next = 0x1d74020 | prev = 0x1d740b0
entry->Data_1 = 100 | list addr = 0x1d74020 | next = 0x7fffd15cf4a0 | prev = 0x1d74050
*********************************************************************************

Free: entry->Data_1 = 400 | list addr = 0x1d740b0 | next = 0x1d74050 | prev = 0x7fffd15cf4a0

Free: entry->Data_1 = 200 | list addr = 0x1d74050 | next = 0x1d74020 | prev = 0x1d740b0

Free: entry->Data_1 = 100 | list addr = 0x1d74020 | next = 0x7fffd15cf4a0 | prev = 0x1d74050
===============================
*/

#endif  // #if (EXAMPLE == 1)

#if (EXAMPLE == 2)  // 2 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��1�اΦ�

    int i;
    struct person *p;
    struct person person1;  // �Y�`�I
    struct list_head *pos;  // �u�@����

    /*
        - �ʺA��l�Ƥ@��Linked List
        - �ݭn���w�q�XLinked List������A�M��Nperson1���a�}�ǻ�����l�ƨ�ƧY�i�����������l�ơC
        - �Y�`�I���ƾڰ줣���n�A�i�H�ھڻݭn�Q���Y�`�I���ƾڰ�A�@��Ө��A�Y�`�I�ƾڰ줣�ϥΡA�b�ϥ��Y�`�I�ƾڰ쪺���p�U�A�@��]�ȶȰO����������׫H��
    */
    INIT_LIST_HEAD(&person1.list);

    for(i = 0; i < 5; i++){
        p = (struct person *)malloc(sizeof(struct person));     // �إ߷s�`�I
        p->age = i * 10;

        // �Y���k�A�Y�C�����J���`�I�����W�@�Ӹ`�I���e�A��p�W�@�Ӹ`�I�Ohead->1->head�A�����ϥ��Y���k���J����A������c�ܦ��Fhead->2->1->head�C
        list_add(&p->list, &person1.list);
    }

    // �M������A�X�ݨ�ƾڰ쪺���e�A����X�{pos == head�ɡA�`������N�M�������F�C
    list_for_each(pos, &person1.list){
        /*
            struct person {
                struct list_head list;
                int age;
            };
            �ѩ�ڭ̱N�����b���c�骺���a�}�B�A���򦹮����list���a�}�A�Mstruct person ���a�}�O�@�P���A
            �ҥH�q�Lpos���a�}�A�N��j���ഫ��struct person *�N�i�H�X��age�����F�C
        */
        printf("age = %d\n",((struct person *)pos)->age);
        /*
        struct person {
            int age;
            struct list_head list;
        };
        - �p�G�令�o�ˡAprintf("age = %d\n",((struct person *)pos)->age); �A�o�q�N���ॿ�`�u�@�F�A
        �]�����ɱj�������ഫ�o��a�}���A�Ostruct person���c�����a�}�A�i��->age�ާ@�ɡA���w���������T�C
        �ҥH�A�]�N�X�{�Fcontainer_of�Aoffsetof�o��Ӽs���H�������C
        - �շQ�A�p�G�ڭ̯���q�L�Npos���w�ǻ����Y�ӧ��Ϊ̨�ơA�Ө�ƩΪ̧�����q�Lpos��^�]�tpos�e���o�ӵ��c�骺�a�}�A
        ����ڭ̤��N�i�H���`�X��age�F�ܡC����M�A container_of���A�N�O�o�ӧ@�ΰڡA�b���֤��A�N��S�ʸ˦��F list_entry��
        */
    };
/*
===============================
# �ù���X���G

age = 40
age = 30
age = 20
age = 10
age = 0

===============================
*/

#endif  // #if (EXAMPLE == 2)

#if (EXAMPLE == 3)  // 3 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��2�اΦ�

    int i;
    struct person *p;
    struct person_head head;    // �Y�`�I
    struct list_head *pos;      // �u�@����

    INIT_LIST_HEAD(&head.list);     // �ʺA��l�Ƥ@��Linked List
    head.len = 0;

    for(i = 0; i < 5; i++) {
        p = (struct person *)malloc(sizeof(struct person));     // �إ߷s�`�I
        p->age = i * 10;

        // �Y���k
        list_add(&p->list, &head.list);
    }

    // �M������A�X�ݨ�ƾڰ쪺���e�A����X�{pos == head�ɡA�`������N�M�������F�C
    list_for_each(pos, &head.list) {
        p = list_entry(pos, struct person, list);   // ���o�Ӹ`�I���c���_�l�I��}�C
        printf("age = %d\n", p->age);
        head.len++;
    };
    printf("list length = %d\n",head.len);
/*
===============================
# �ù���X���G

age = 40
age = 30
age = 20
age = 10
age = 0
list length = 5

===============================
*/

#endif  // #if (EXAMPLE == 3)

#if (EXAMPLE == 4)  // 4 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : ��3�اΦ�

    int i;
    struct person *p;
    struct person head;     // �Y�`�I
    struct person *pos;     // �u�@����
    struct person *n;       // �w�s����

    INIT_LIST_HEAD(&head.list);     // �ʺA��l�Ƥ@��Linked List

    for(i = 0; i < 5; i++) {
        p = (struct person *)malloc(sizeof(struct person));
        p->age = i * 10;

        // �Y���k
        list_add(&p->list, &head.list);
    }

    list_for_each_entry(pos, &head.list, list) {
        if(pos->age == 30){
            list_del(&pos->list);
            break;      // �p�G���ϥ�break�F�|�o�Ͳ��`�C
        }
    };

    /*
        - �ϥγo�ӧ��A�i�H�b�M������ɦw���a����R���ާ@
        - ���z�N�O�����@�Ӹ`�I���X�Өϥ�n�@���w�s�A�o�˦b�٨S�R���`�I�ɡA�N�o��F�n�R���`�I���U�@�Ӹ`�I���a�}�A�q���קK�F�{�ǥX���C
          ���ϥΤF�@�Ӥ����ܶq�w�s����k�A��{�󬰦w�����ܶq�����k
    */
    list_for_each_entry_safe(pos, n, &head.list, list){
        if(pos->age == 20){
            list_del(&pos->list);
            //break;
        }
    };

    /*
        - �M����������entry(�Y�������e�����c���a�})�C
        - �ӧ�����pos�������e�����c���������w�A�o�P�e��list_for_each�����ϥΪ��������A�ۦP
    */
    list_for_each_entry(pos, &head.list, list){
        printf("age = %d\n", pos->age);
    };
/*
===============================
# �ù���X���G

age = 40
age = 10
age = 0

===============================
*/

#endif  // #if (EXAMPLE == 4)

#if (EXAMPLE == 5)  // 5 : e.g. > Linux kernel ���V�쵲��C (Doubly Linked List) ����sample code : �V�M�Φ�

    int i;
    struct person *p1, *p2;
    struct My_DATA head1, head2;    // �Y�`�I
    struct person *pos;             // �u�@����
    struct person *tmp_pos;         // �w�s����

    INIT_LIST_HEAD(&head1.my_data_list);    // �ʺA��l�Ƥ@��Linked List
    INIT_LIST_HEAD(&head2.my_data_list);    // �ʺA��l�Ƥ@��Linked List

    printf("begin, p1 return of list_empty = %d\n", list_empty(&head1.my_data_list));
    // �ù���X���G > begin, p1 return of list_empty = 1

    for (i = 1; i < 6; i++) {
        p1 = (struct person *)malloc(sizeof(struct person));    // �إ߷s�`�I
        p1->age = i * 10;

        // �Y���k
        list_add(&p1->list, &head1.my_data_list);   // �Y�`�I : struct My_DATA�A�`�I : struct person


        p2 = (struct person *)malloc(sizeof(struct person));    // �إ߷s�`�I
        p2->age = i * 3;

        // �����k�A�p�G��ӬOhead->1->head,�����k�@�Ӹ`�I�����ܦ��Fhead->1->2->head�C
        list_add_tail(&p2->list,&head2.my_data_list);   // �Y�`�I : struct My_DATA�A�`�I : struct person
    }

    list_for_each_entry_safe(pos, tmp_pos, &head1.my_data_list, list) {
        printf("before del, p1 age = %d\n", pos->age);
    }
/*
===============================
# �ù���X���G

before del, p1 age = 50
before del, p1 age = 40
before del, p1 age = 30
before del, p1 age = 20
before del, p1 age = 10

===============================
*/

    list_for_each_entry_safe(pos, tmp_pos, &head2.my_data_list, list) {
        printf("p2 age = %d\n", pos->age);
    }
/*
===============================
# �ù���X���G

p2 age = 3
p2 age = 6
p2 age = 9
p2 age = 12
p2 age = 15

===============================
*/

    list_for_each_entry_safe(pos, tmp_pos, &head1.my_data_list, list) {
        if (pos->age == 30)
            list_del(&pos->list);
    }

    list_for_each_entry_safe(pos, tmp_pos, &head1.my_data_list, list) {
        printf("after del, p1 age = %d\n", pos->age);
    }
/*
===============================
# �ù���X���G

after del, p1 age = 50
after del, p1 age = 40
after del, p1 age = 20
after del, p1 age = 10

===============================
*/
    printf("end, p1 return of list_empty = %d\n", list_empty(&head1.my_data_list));
    // �ù���X���G > end, p1 return of list_empty = 0

    tmp_pos = list_first_entry(&head1.my_data_list, struct person, list);   // get the first element from a list

    printf("p1 get from list_first_entry, age = %d\n", tmp_pos->age);
    // �ù���X���G > p1 get from list_first_entry, age = 50

    list_splice_tail(&head2.my_data_list, &head1.my_data_list);     // join two lists, each list being a queue

    list_for_each_entry_safe(pos, tmp_pos, &head1.my_data_list, list) {
        printf("after list_splice_tail, p1 age = %d\n", pos->age);
    }
/*
===============================
# �ù���X���G

after list_splice_tail, p1 age = 50
after list_splice_tail, p1 age = 40
after list_splice_tail, p1 age = 20
after list_splice_tail, p1 age = 10
after list_splice_tail, p1 age = 3
after list_splice_tail, p1 age = 6
after list_splice_tail, p1 age = 9
after list_splice_tail, p1 age = 12
after list_splice_tail, p1 age = 15

===============================
*/

#endif  // #if (EXAMPLE == 5)
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

