/*
QGѡ����ҵ��������
time��2017��3��19��
test_content: ���������������
choice:ʹ�ò���ͷ��������
*/
#include <stdio.h>
#include <stdlib.h>
#define N 10

//����һ��ָ������
typedef struct Node {
    int data;
    struct Node *next;
} Node, *ptr_Node;

typedef enum Status
{
    SUCCESS, ERROR
}Status;

//����ѡ��,ʵ�ֵ������սڵ�ֵ��С��������
Status sort(ptr_Node *head);
//������������һ�������ɹ��򷵻�ͷ�ڵ㣬ʧ�ܷ��� NULL
ptr_Node create(int *arr, int n);
//���ٸ���������
void destroy(ptr_Node head);
//ȫ�������
void print(ptr_Node head);
//��������int������
void swap_int(int *, int *);

int main(void) {
    int a[N];
    int index;
    Status s;  //�жϲ����ɹ����

    printf("�������%d��int�Ͳ������ݴ����������У�\n", N);
    for (index = 0; index < N; index++) {      //����������ݴ洢��������
        scanf("%d", &a[index]);
    }
    ptr_Node head = create(a, N);       //������ת����һ��������
    print(head);                   //�������

    s = sort(&head);
    if (SUCCESS ==s) {
        printf("��������������");
        print(head);
    } else {
        printf("����ʧ�ܣ�");
    }

    destroy(head);  //��������

    return 0;
}

//������������һ�������ɹ��򷵻�ͷ�ڵ㣬ʧ�ܷ��� NULL
ptr_Node create(int *arr, int n) {
    if (n <= 0 || NULL == arr) {        //�жϴ�������
        return NULL;
    }

    int index;      //�����±�
    ptr_Node p, head;
    head = p = (ptr_Node)malloc(sizeof(Node));  //ͷָ���ָ��Pָ���һ���ڵ�
    p->data = arr[0];                        //����һ�����ݴ���

    for (index = 1; index < n; index++) {
        p->next = (ptr_Node)malloc(sizeof(Node));    //����ռ���Ϊ��һ���ڵ㲢ʹp->nextָ��
        p = p->next;                               //pָ����һ���ڵ�
        p->data = arr[index];                        //�������е����ִ����������
    }
    p->next = NULL;

    return head;
}

//���ٸ���������
void destroy(ptr_Node head) {
    if (NULL == head) {       //�ж�����ǿ�
        return;
    }

    if (NULL == head->next){    //�ж������Ƿ�ֻ��һ���ڵ�
        free(head);
    } else {
        ptr_Node p;
        while (NULL != head){
            p = head;           //ָ��pָ���һ���ڵ�
            head = p->next;     //��head����
            free(p);            //�ͷ�head
        }
    }
}

//��������ֵ����һ���ĸ�ʽ�����ÿ�ж��ٸ��Լ����壬��ʽԽƯ��Խ�ã�
void print(ptr_Node head) {
    if (NULL == head) {                 //�ж�ָ���Ƿ�Ϊ��
        printf("��ָ���쳣");
        return;
    }

    int index = 0;                          //�����������
    printf("\n--------------------------�����������--------------------------\n");
    while (NULL != head) {
        printf("|                    ����ĵ�%3d������Ϊ%3d                     |\n", index+1, head->data);
        head = head->next;
        index++;
    }
    printf("\n--------------------------�����������--------------------------\n");
}

//����ѡ��,ʵ�ֵ������սڵ�ֵ��С��������
Status sort(ptr_Node *head) {
    if (NULL == *head) {
        return ERROR;
    }
    //����ð������˼������
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

//��������int���ͱ�����ֵ
void swap_int(int * a, int * b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}







