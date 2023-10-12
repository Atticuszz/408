#include <iostream>
#include <vector>

using namespace std;

#pragma region ������ͷ��������

#define ElemType int
#define _for(i, a, b) for(int i=(a);i<(b);i++)

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//��ʼ������
bool InitList(LinkList &L) {
    //����һ��ͷ���
    L = (LNode *) malloc(sizeof(LNode));
    //�ڴ治�㣬����ʧ��
    if (L == NULL) {
        return false;
    }
    //ͷ���֮����ʱ��û�нڵ�
    L->next = NULL;
    return true;
}


//�ж��Ƿ�Ϊ��
bool IsEmpty(LinkList L) {
    return ((L->next) == NULL);
}

//ʹ��β�巨����
LinkList CreatList(vector<int> data) {
    if (data.size() < 1) {
        return NULL;
    }
    //ͷ���
    LNode *head = (LinkList) malloc(sizeof(LNode));
    head->data = NULL;
    head->next = NULL;
    LinkList p = head;
    _for(i, 0, data.size()) {
        LNode *s = (LinkList) malloc(sizeof(LNode));
        s->data = data[i];
        s->next = NULL;
        p->next = s;
        p = s;
    }
    return head;
}

//�������
void PrintList(LinkList list) {
    list = list->next;
    while (list != NULL) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

#pragma endregion

//P278.7(2)
//���Ա��и����ļ������ʲ���ʱ,�������²������˳�������Ч��:���ҵ�ָ����
//���,�򽫸ý�����ǰ�����(������)����, ʹ�þ����������Ľ�㾡��λ�ڱ��
//ǰ�ˡ��������˳��ṹ����ʽ�ṹ�����Ա���ʵ���������Ե�˳�������㷨��

//��ʽʵ��

int Search(LinkList &head, ElemType key) {

    int i = 0;
    LinkList p = head->next, pre = head;
    while (p && p->data != key) {
        i++;
        pre = p;
        p = p->next;
    }
    if (p) {
        swap(p->data, pre->data);
        return --i;
    }
    return -1;
}

int main() {
    vector<int> data{2, 4, 6, 8, 13, 23, 36, 41, 63};
    LinkList head;
    InitList(head);
    head = CreatList(data);
    PrintList(head);
    cout << "λ��Ϊ��" << Search(head, 8) << endl;
    cout << "λ��Ϊ��" << Search(head, 8) << endl;
    cout << "λ��Ϊ��" << Search(head, 8) << endl;
    cout << "λ��Ϊ��" << Search(head, 41) << endl;
    cout << "λ��Ϊ��" << Search(head, 41) << endl;
    PrintList(head);
    return 0;
}
