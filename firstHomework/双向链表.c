/*
QG第一次作业（双向链表）
time：2017年3月19日
test_content: 双向链表的删除和插入操作的函数编写以及测试
choice:使用不带头结点的链表
*/
#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct TNode
{
     int data;
     struct TNode *next;
     struct TNode *pre;
}TNode, *ptr_TNode;

typedef enum Status
{
    SUCCESS, ERROR
}Status;

//创建双向链表
ptr_TNode create_T(int *arr, int n);
//输出链表
void print(ptr_TNode head);
//双向链表,删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
Status delete_T(ptr_TNode *head, int index, int *data);
//双向链表,在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert_T(ptr_TNode *head, ptr_TNode node, int index);

int main(void) {
    int a[N] = {0};
    int i;
    Status s;       //用于判断操作是否成功

    printf("输入十个测试数据：\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    ptr_TNode head = create_T(a, N);        //创建链表
    print(head);            //输出创建好的链表

    printf("\n输入需要删除的节点的位置：\n");
    scanf("%d", &i);
    int delete_data;
    s = delete_T(&head, i, &delete_data);   //删除指定位置的数据并输出删除后的链表
    if (SUCCESS == s) {
        printf("被删除的该位置上的原数据是%d\n", delete_data);
        print(head);
    } else {
        printf("删除失败！");
    }

    TNode insert_Tnode;
    insert_Tnode.pre = NULL;
    insert_Tnode.next = NULL;
    printf("\n输入要插入的数据和位置：\n");
    scanf("%d %d", &insert_Tnode.data, &i);
    s = insert_T(&head, &insert_Tnode, i);
    if (SUCCESS == s) {
        print(head);
    } else {
        printf("插入失败！");
    }

    return 0;
}

//创建一个双向链表
ptr_TNode create_T(int *arr, int n) {
    if (NULL == arr || n <= 0) {    //判断指针是否为空和数组长度是否合法
        return NULL;
    }

    int index = 0;      //数组下标
    ptr_TNode p, head;
    head = p = (ptr_TNode)malloc(sizeof(TNode));  //头指针和指针P指向第一个节点
    head->pre = NULL;                           //第一个节点的pre指针为空
    head->data = arr[0];                        //将第一个数据储存

    for (index = 1; index < n; index++) {
        p->next = (ptr_TNode)malloc(sizeof(TNode));    //申请空间作为下一个节点并使p->next指向
        p->next->pre = p;                           //下一个节点的pre指针指向上一个节点
        p = p->next;                               //p指向下一个节点
        p->data = arr[index];                        //将数组中的数字储存进链表中
    }
    p->next = NULL;

    return head;

}

//输出链表
void print(ptr_TNode head) {
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


//双向链表,删除第 index 位节点后面的节点，将删除的结点的值保存到（*data）中
Status delete_T(ptr_TNode *head, int index, int *data) {
    if (NULL == *head || index < 0) {       //判断指针和index是否合法
        return ERROR;
    }

    ptr_TNode p = *head;
    if (0 == index) {                     //判断删除的是否为第一个节点
        *data = (*head)->data;
        *head = (*head)->next;
        (*head)->pre = NULL;
        free(p);
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {       //找到要删除的节点前一个位置
            p = p->next;
            if (NULL == p) {
                return ERROR;               //判断index是否超出链表长度
            }
        }
            ptr_TNode delete_p = p->next;   //将被删除前后节点连接
            p->next = delete_p->next;
            if (NULL != delete_p->next) {     //判断被删除的数据是否为最后一个
                delete_p->next->pre = p;
            }
            *data = delete_p->data;
            free(delete_p);
    }
    return SUCCESS;
}

//双向链表,在第 index 位后面插入 node 结点
//插入成功返回 SUCCESS，失败返回 ERROR
Status insert_T(ptr_TNode *head, ptr_TNode node, int index) {
    if (NULL == *head || index < 0) {       //判断index和head是否合法
        return ERROR;
    }

    ptr_TNode p = *head;
    if (0 == index) {       //判断是否插入在最前端
        node->pre = NULL;       //连接最前端与*head，并移动头指针位置
        node->next = *head;
        (*head)->pre = node;
        *head = node;
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {       //找到需要插入的前一个节点
            p = p->next;
            if (NULL == p) {
                return ERROR;               //判断index是否超出链表长度
            }
        }
        node->next = p->next;               //连接插入的节点
        if (NULL != p->next) {              //判断p是否为最后一个节点
            p->next->pre = node;
        }
        p->next = node;
        node->pre = p;
    }
    return SUCCESS;
}
















