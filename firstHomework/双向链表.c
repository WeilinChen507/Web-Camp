/*
QG��һ����ҵ��˫������
time��2017��3��19��
test_content: ˫�������ɾ���Ͳ�������ĺ�����д�Լ�����
choice:ʹ�ò���ͷ��������
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

//����˫������
ptr_TNode create_T(int *arr, int n);
//�������
void print(ptr_TNode head);
//˫������,ɾ���� index λ�ڵ����Ľڵ㣬��ɾ���Ľ���ֵ���浽��*data����
Status delete_T(ptr_TNode *head, int index, int *data);
//˫������,�ڵ� index λ������� node ���
//����ɹ����� SUCCESS��ʧ�ܷ��� ERROR
Status insert_T(ptr_TNode *head, ptr_TNode node, int index);

int main(void) {
    int a[N] = {0};
    int i;
    Status s;       //�����жϲ����Ƿ�ɹ�

    printf("����ʮ���������ݣ�\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    ptr_TNode head = create_T(a, N);        //��������
    print(head);            //��������õ�����

    printf("\n������Ҫɾ���Ľڵ��λ�ã�\n");
    scanf("%d", &i);
    int delete_data;
    s = delete_T(&head, i, &delete_data);   //ɾ��ָ��λ�õ����ݲ����ɾ���������
    if (SUCCESS == s) {
        printf("��ɾ���ĸ�λ���ϵ�ԭ������%d\n", delete_data);
        print(head);
    } else {
        printf("ɾ��ʧ�ܣ�");
    }

    TNode insert_Tnode;
    insert_Tnode.pre = NULL;
    insert_Tnode.next = NULL;
    printf("\n����Ҫ��������ݺ�λ�ã�\n");
    scanf("%d %d", &insert_Tnode.data, &i);
    s = insert_T(&head, &insert_Tnode, i);
    if (SUCCESS == s) {
        print(head);
    } else {
        printf("����ʧ�ܣ�");
    }

    return 0;
}

//����һ��˫������
ptr_TNode create_T(int *arr, int n) {
    if (NULL == arr || n <= 0) {    //�ж�ָ���Ƿ�Ϊ�պ����鳤���Ƿ�Ϸ�
        return NULL;
    }

    int index = 0;      //�����±�
    ptr_TNode p, head;
    head = p = (ptr_TNode)malloc(sizeof(TNode));  //ͷָ���ָ��Pָ���һ���ڵ�
    head->pre = NULL;                           //��һ���ڵ��preָ��Ϊ��
    head->data = arr[0];                        //����һ�����ݴ���

    for (index = 1; index < n; index++) {
        p->next = (ptr_TNode)malloc(sizeof(TNode));    //����ռ���Ϊ��һ���ڵ㲢ʹp->nextָ��
        p->next->pre = p;                           //��һ���ڵ��preָ��ָ����һ���ڵ�
        p = p->next;                               //pָ����һ���ڵ�
        p->data = arr[index];                        //�������е����ִ����������
    }
    p->next = NULL;

    return head;

}

//�������
void print(ptr_TNode head) {
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


//˫������,ɾ���� index λ�ڵ����Ľڵ㣬��ɾ���Ľ���ֵ���浽��*data����
Status delete_T(ptr_TNode *head, int index, int *data) {
    if (NULL == *head || index < 0) {       //�ж�ָ���index�Ƿ�Ϸ�
        return ERROR;
    }

    ptr_TNode p = *head;
    if (0 == index) {                     //�ж�ɾ�����Ƿ�Ϊ��һ���ڵ�
        *data = (*head)->data;
        *head = (*head)->next;
        (*head)->pre = NULL;
        free(p);
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {       //�ҵ�Ҫɾ���Ľڵ�ǰһ��λ��
            p = p->next;
            if (NULL == p) {
                return ERROR;               //�ж�index�Ƿ񳬳�������
            }
        }
            ptr_TNode delete_p = p->next;   //����ɾ��ǰ��ڵ�����
            p->next = delete_p->next;
            if (NULL != delete_p->next) {     //�жϱ�ɾ���������Ƿ�Ϊ���һ��
                delete_p->next->pre = p;
            }
            *data = delete_p->data;
            free(delete_p);
    }
    return SUCCESS;
}

//˫������,�ڵ� index λ������� node ���
//����ɹ����� SUCCESS��ʧ�ܷ��� ERROR
Status insert_T(ptr_TNode *head, ptr_TNode node, int index) {
    if (NULL == *head || index < 0) {       //�ж�index��head�Ƿ�Ϸ�
        return ERROR;
    }

    ptr_TNode p = *head;
    if (0 == index) {       //�ж��Ƿ��������ǰ��
        node->pre = NULL;       //������ǰ����*head�����ƶ�ͷָ��λ��
        node->next = *head;
        (*head)->pre = node;
        *head = node;
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {       //�ҵ���Ҫ�����ǰһ���ڵ�
            p = p->next;
            if (NULL == p) {
                return ERROR;               //�ж�index�Ƿ񳬳�������
            }
        }
        node->next = p->next;               //���Ӳ���Ľڵ�
        if (NULL != p->next) {              //�ж�p�Ƿ�Ϊ���һ���ڵ�
            p->next->pre = node;
        }
        p->next = node;
        node->pre = p;
    }
    return SUCCESS;
}
















