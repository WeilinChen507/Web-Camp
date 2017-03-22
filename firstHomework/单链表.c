/*
QG第一次作业（单链表）
time：2017年3月18日-3月19日
test_content: 单链表的生成，销毁，插入，删除，查找，修改，输出的函数的编写及其调用测试
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

//根据数组生成一条链表，成功则返回头节点，失败返回 NULL
ptr_Node create(int *arr, int n);
//销毁给定的链表
void destroy(ptr_Node head);
//在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert(ptr_Node *head, ptr_Node node, int index);
//删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
//删除成功返回 SUCCESS，其他情况返回 ERROR
Status delete(ptr_Node *head, int index, int *data);
//在链表中查找节点值与 data 相等的节点，并返回找到的第一个节点的前一个节点的位置
//（例：头节点相等，返回 0），没找到或者其他情况返回-1
int search(ptr_Node head, int data);
//将链表中 index 位点后面的结点的值修改为(*data)，将原值保存到(*data)
//修改成功返回 SUCCESS，其他情况返回 ERROR
Status edit(ptr_Node head, int index, int *data);
//将链表结点值按照一定的格式输出（每行多少个自己定义，格式越漂亮越好）
void print(ptr_Node head);


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

    Node insert_node;
    int insert_index;
    printf("\n输入插入的节点的int型测试数据以及位置：\n");
    scanf("%d %d", &insert_node.data, &insert_index);
    insert_node.next = NULL;
    s = insert(&head, &insert_node, insert_index);   //插入已输入的数据到指定位置并全链表输出
    if (SUCCESS == s) {
        print(head);
    } else {
        printf("插入错误！\n");
    }

    int deleted_data;
    int delete_index;
    printf("\n输入删除的数据的位置：\n");
    scanf("%d", &delete_index);
    s = delete(&head, delete_index, &deleted_data);      //删除指定的数据并全链表输出
    if (SUCCESS == s) {
        printf("\n被删除的数据为%d", deleted_data);
        print(head);
    } else {
        printf("找不到需要删除的数据！\n");
    }

    int search_data;
    printf("\n输入需要查找的数据：\n");
    scanf("%d", &search_data);
    int n = search(head, search_data);          //删除指定数据并全链表输出
    if (-1 == n) {
        printf("没有找到该数据！\n");
    } else {
        printf("该数据的前一个节点数为%d", n);
        print(head);
    }

    int edit_index;
    int edit_data;
    printf("\n输入修改后的int型测试数据及其位置:\n");
    scanf("%d %d", &edit_data, &edit_index);
    s = edit(head, edit_index, &edit_data);             //修改并输出全链表和被修改的位置的原数据
    if (ERROR == s) {
        printf("修改失败！");
    } else {
        printf("该位置上的原数据为%d", edit_data);
        print(head);
    }

    destroy(head);          //销毁链表防止内存泄漏

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

//在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert(ptr_Node *head, ptr_Node node, int index) {
    if (NULL == *head || index < 0) {     //判断头指针是否为空
        return ERROR;
    }

    if (0 == index) {       //判断插入点是否为0
        node->next = *head;
        *head = node;
    } else {
        ptr_Node p = *head;
        int i;
        for (i = 1; i < index; i++) {   //找到要插入位置的前一个节点
            p = p->next;
            if (NULL == p) {            //index超出链表长度
                return ERROR;
            }
        }
        node->next = p->next;                //要插入的节点指向插入后的下一个节点
        p->next = node;                     //插入位置的前一个节点指向插入的节点
    }

    return SUCCESS;
}

//删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
//删除成功返回 SUCCESS，其他情况返回 ERROR
Status delete(ptr_Node *head, int index, int *data) {
    if (NULL == *head || index < 0) {
        return ERROR;
    }

    ptr_Node p = *head;
    if (0 == index) {       //判断删除的是不是首个节点
        *data = (*head)->data;
        *head = (*head)->next;
        free(p);
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {   //找到要删除节点的前一个节点
            p = p->next;
            if (NULL == p) {
                return ERROR;          //index超出链表长度
            }
        }
        ptr_Node p2 = p->next;          //p2删除节点
        p->next = p2->next;             //p指向删除节点的下一个节点
        *data = p2->data;               //记录删除节点的内容
        free(p2);                       //释放需要删除的节点的空间
        return SUCCESS;
    }
}

//在链表中查找节点值与 data 相等的节点，并返回找到的第一个节点的前一个节点的位置
//（例：头节点相等，返回 0），没找到或者其他情况返回-1
int search(ptr_Node head, int data) {
    if (NULL == head) {         //判断head是否指向链表
        return -1;
    }

    int index = 0;
    for (index = 0; head->data != data; index++) {         //不断后移head找出位置
        head = head->next;
        if (NULL == head) {             //判断index是否超出链表长度
            return -1;
        }
    }
    return index;
}

//将链表中 index 位点后面的结点的值修改为(*data)，将原值保存到(*data)
//修改成功返回 SUCCESS，其他情况返回 ERROR
Status edit(ptr_Node head, int index, int *data) {
    if (NULL == head || index < 0) {        //判断head是否指向链表以及index是否合法
        return ERROR;
    }

    int i;
    for (i = 0; i < index; i++) {   //不断后移head找到需要修改的位置
        head = head->next;
        if (NULL == head) {         //判断需要修改的位置是否超出链表长度
            return ERROR;
        }
    }
    head->data = head->data + *data;        //修改该位置的数据并将原数据存于*data中
    *data = head->data - *data;
    head->data = head->data - *data;
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






