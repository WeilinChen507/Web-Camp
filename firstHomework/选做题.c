/*
QG选座作业（单链表）
time：2017年3月19日
test_content: 单链表的升序排序
choice:使用不带头结点的链表
*/
#include <stdio.h>
#include <stdlib.h>
#define N 10

//定义一个指针类型
typedef struct Node {
    int data;
    struct Node *next;
} Node, *ptr_Node;

typedef enum Status
{
    SUCCESS, ERROR
}Status;

//此题选做,实现单链表按照节点值大小升序排序
Status sort(ptr_Node *head);
//根据数组生成一条链表，成功则返回头节点，失败返回 NULL
ptr_Node create(int *arr, int n);
//销毁给定的链表
void destroy(ptr_Node head);
//全链表输出
void print(ptr_Node head);
//交换两个int型数据
void swap_int(int *, int *);

int main(void) {
    int a[N];
    int index;
    Status s;  //判断操作成功与否

    printf("输入测试%d个int型测试数据储存于链表中：\n", N);
    for (index = 0; index < N; index++) {      //将输入的数据存储于数组中
        scanf("%d", &a[index]);
    }
    ptr_Node head = create(a, N);       //将数组转换成一个单链表
    print(head);                   //输出链表

    s = sort(&head);
    if (SUCCESS ==s) {
        printf("升序排序后的链表：");
        print(head);
    } else {
        printf("排序失败！");
    }

    destroy(head);  //销毁链表

    return 0;
}

//根据数组生成一条链表，成功则返回头节点，失败返回 NULL
ptr_Node create(int *arr, int n) {
    if (n <= 0 || NULL == arr) {        //判断传入数组
        return NULL;
    }

    int index;      //数组下标
    ptr_Node p, head;
    head = p = (ptr_Node)malloc(sizeof(Node));  //头指针和指针P指向第一个节点
    p->data = arr[0];                        //将第一个数据储存

    for (index = 1; index < n; index++) {
        p->next = (ptr_Node)malloc(sizeof(Node));    //申请空间作为下一个节点并使p->next指向
        p = p->next;                               //p指向下一个节点
        p->data = arr[index];                        //将数组中的数字储存进链表中
    }
    p->next = NULL;

    return head;
}

//销毁给定的链表
void destroy(ptr_Node head) {
    if (NULL == head) {       //判断链表非空
        return;
    }

    if (NULL == head->next){    //判断链表是否只有一个节点
        free(head);
    } else {
        ptr_Node p;
        while (NULL != head){
            p = head;           //指针p指向第一个节点
            head = p->next;     //将head后移
            free(p);            //释放head
        }
    }
}

//将链表结点值按照一定的格式输出（每行多少个自己定义，格式越漂亮越好）
void print(ptr_Node head) {
    if (NULL == head) {                 //判断指针是否为空
        printf("空指针异常");
        return;
    }

    int index = 0;                          //遍历链表并输出
    printf("\n--------------------------输出数据如下--------------------------\n");
    while (NULL != head) {
        printf("|                    储存的第%3d个数据为%3d                     |\n", index+1, head->data);
        head = head->next;
        index++;
    }
    printf("\n--------------------------数据输出如上--------------------------\n");
}

//此题选做,实现单链表按照节点值大小升序排序
Status sort(ptr_Node *head) {
    if (NULL == *head) {
        return ERROR;
    }
    //采用冒泡排序思想排序
    ptr_Node p1, p2;
    for (p1 = *head; NULL != p1->next; p1 = p1->next) {
        for (p2 = p1->next; NULL != p2; p2 = p2->next) {
            if (p1->data > p2->data) {
                swap_int(&(p1->data), &(p2->data));
            }
        }
    }
    return SUCCESS;
}

//交换两个int类型变量的值
void swap_int(int * a, int * b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}







