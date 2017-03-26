/*
QG��һ����ҵ��������
time��2017��3��18��-3��19��
test_content: ����������ɣ����٣����룬ɾ�������ң��޸ģ�����ĺ����ı�д������ò���
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

//������������һ�������ɹ��򷵻�ͷ�ڵ㣬ʧ�ܷ��� NULL
ptr_Node create(int *arr, int n);
//���ٸ���������
void destroy(ptr_Node head);
//�ڵ� index λ������� node ���
//����ɹ����� SUCCESS��ʧ�ܷ��� ERROR
Status insert(ptr_Node *head, ptr_Node node, int index);
//ɾ���� index λ�ڵ����Ľڵ㣬��ɾ���Ľ���ֵ���浽��*data����
//ɾ���ɹ����� SUCCESS������������� ERROR
Status delete(ptr_Node *head, int index, int *data);
//�������в��ҽڵ�ֵ�� data ��ȵĽڵ㣬�������ҵ��ĵ�һ���ڵ��ǰһ���ڵ��λ��
//������ͷ�ڵ���ȣ����� 0����û�ҵ����������������-1
int search(ptr_Node head, int data);
//�������� index λ�����Ľ���ֵ�޸�Ϊ(*data)����ԭֵ���浽(*data)
//�޸ĳɹ����� SUCCESS������������� ERROR
Status edit(ptr_Node head, int index, int *data);
//��������ֵ����һ���ĸ�ʽ�����ÿ�ж��ٸ��Լ����壬��ʽԽƯ��Խ�ã�
void print(ptr_Node head);


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

    Node insert_node;
    int insert_index;
    printf("\n�������Ľڵ��int�Ͳ��������Լ�λ�ã�\n");
    scanf("%d %d", &insert_node.data, &insert_index);
    insert_node.next = NULL;
    s = insert(&head, &insert_node, insert_index);   //��������������ݵ�ָ��λ�ò�ȫ�������
    if (SUCCESS == s) {
        print(head);
    } else {
        printf("�������\n");
    }

    int deleted_data;
    int delete_index;
    printf("\n����ɾ�������ݵ�λ�ã�\n");
    scanf("%d", &delete_index);
    s = delete(&head, delete_index, &deleted_data);      //ɾ��ָ�������ݲ�ȫ�������
    if (SUCCESS == s) {
        printf("\n��ɾ��������Ϊ%d", deleted_data);
        print(head);
    } else {
        printf("�Ҳ�����Ҫɾ�������ݣ�\n");
    }

    int search_data;
    printf("\n������Ҫ���ҵ����ݣ�\n");
    scanf("%d", &search_data);
    int n = search(head, search_data);          //ɾ��ָ�����ݲ�ȫ�������
    if (-1 == n) {
        printf("û���ҵ������ݣ�\n");
    } else {
        printf("�����ݵ�ǰһ���ڵ���Ϊ%d", n);
        print(head);
    }

    int edit_index;
    int edit_data;
    printf("\n�����޸ĺ��int�Ͳ������ݼ���λ��:\n");
    scanf("%d %d", &edit_data, &edit_index);
    s = edit(head, edit_index, &edit_data);             //�޸Ĳ����ȫ����ͱ��޸ĵ�λ�õ�ԭ����
    if (ERROR == s) {
        printf("�޸�ʧ�ܣ�");
    } else {
        printf("��λ���ϵ�ԭ����Ϊ%d", edit_data);
        print(head);
    }

    destroy(head);          //���������ֹ�ڴ�й©

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

//�ڵ� index λ������� node ���
//����ɹ����� SUCCESS��ʧ�ܷ��� ERROR
Status insert(ptr_Node *head, ptr_Node node, int index) {
    if (NULL == *head || index < 0) {     //�ж�ͷָ���Ƿ�Ϊ��
        return ERROR;
    }

    if (0 == index) {       //�жϲ�����Ƿ�Ϊ0
        node->next = *head;
        *head = node;
    } else {
        ptr_Node p = *head;
        int i;
        for (i = 1; i < index; i++) {   //�ҵ�Ҫ����λ�õ�ǰһ���ڵ�
            p = p->next;
            if (NULL == p) {            //index����������
                return ERROR;
            }
        }
        node->next = p->next;                //Ҫ����Ľڵ�ָ���������һ���ڵ�
        p->next = node;                     //����λ�õ�ǰһ���ڵ�ָ�����Ľڵ�
    }

    return SUCCESS;
}

//ɾ���� index λ�ڵ����Ľڵ㣬��ɾ���Ľ���ֵ���浽��*data����
//ɾ���ɹ����� SUCCESS������������� ERROR
Status delete(ptr_Node *head, int index, int *data) {
    if (NULL == *head || index < 0) {
        return ERROR;
    }

    ptr_Node p = *head;
    if (0 == index) {       //�ж�ɾ�����ǲ����׸��ڵ�
        *data = (*head)->data;
        *head = (*head)->next;
        free(p);
        return SUCCESS;
    } else {
        int i;
        for (i = 1; i < index; i++) {   //�ҵ�Ҫɾ���ڵ��ǰһ���ڵ�
            p = p->next;
            if (NULL == p) {
                return ERROR;          //index����������
            }
        }
        ptr_Node p2 = p->next;          //p2ɾ���ڵ�
        p->next = p2->next;             //pָ��ɾ���ڵ����һ���ڵ�
        *data = p2->data;               //��¼ɾ���ڵ������
        free(p2);                       //�ͷ���Ҫɾ���Ľڵ�Ŀռ�
        return SUCCESS;
    }
}

//�������в��ҽڵ�ֵ�� data ��ȵĽڵ㣬�������ҵ��ĵ�һ���ڵ��ǰһ���ڵ��λ��
//������ͷ�ڵ���ȣ����� 0����û�ҵ����������������-1
int search(ptr_Node head, int data) {
    if (NULL == head) {         //�ж�head�Ƿ�ָ������
        return -1;
    }

    int index = 0;
    for (index = 0; head->data != data; index++) {         //���Ϻ���head�ҳ�λ��
        head = head->next;
        if (NULL == head) {             //�ж�index�Ƿ񳬳�������
            return -1;
        }
    }
    return index;
}

//�������� index λ�����Ľ���ֵ�޸�Ϊ(*data)����ԭֵ���浽(*data)
//�޸ĳɹ����� SUCCESS������������� ERROR
Status edit(ptr_Node head, int index, int *data) {
    if (NULL == head || index < 0) {        //�ж�head�Ƿ�ָ�������Լ�index�Ƿ�Ϸ�
        return ERROR;
    }

    int i;
    for (i = 0; i < index; i++) {   //���Ϻ���head�ҵ���Ҫ�޸ĵ�λ��
        head = head->next;
        if (NULL == head) {         //�ж���Ҫ�޸ĵ�λ���Ƿ񳬳�������
            return ERROR;
        }
    }
    head->data = head->data + *data;        //�޸ĸ�λ�õ����ݲ���ԭ���ݴ���*data��
    *data = head->data - *data;
    head->data = head->data - *data;
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






