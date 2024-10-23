# Exam

## 2009_code_lastK

![[assets/2009_code_lastk/09desc.png]]

```C++
#include <iostream>

struct Node {
    int data;
    Node* link;
};

void create(Node* p, int a[], int pos, int length) {
    if (pos < length) {
        p->data = a[pos];
        p->link = new Node;
        p->link->data = 0; // 用0作为结束标志
        create(p->link, a, pos + 1, length);
    }
}

int getLastK(Node* p, int k) {
    Node* p_fast = p, * p_slow = p;
    while (--k && p_fast->link != NULL) p_fast = p_fast->link;
    p_fast = p_fast->link;
    while (p_fast->data) {
        p_slow = p_slow->link;
        p_fast = p_fast->link;
    }
    return p_slow->data;
}

int main() {
    Node p;
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    create(&p, a, 0, 10);
    int ret = getLastK(&p, 7);
    cout << "倒数第7个元素是：" << ret << endl;
    return 0;
}
```

![[assets/2009_code_lastk/09.png]]
太复杂了，不要那么模块化，因为我是考试写的，因此，只需要必要的数据结构定义，然后一个 main 汉书就可以了，确保语法 c++ 标准，结构用结构体，不要清理内存，假设是已经有了数据结构

## 2010_code_circle_leftmove

```c++
#include <iostream>
#include <vector>

void reverse(std::vector<int>& a, int start, int end) {
    while (start < end) {
        std::swap(a[start], a[end]);
        ++start;
        --end;
    }
}

void move(std::vector<int>& a, int p) {
    reverse(a, 0, p - 1);
    reverse(a, p, a.size() - 1);
    reverse(a, 0, a.size() - 1);
}

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    move(a, 7);
    
    for (int num : a) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 2011_code_double_divide

```c++
#include <iostream>
#include <vector>

int getMiddle(const std::vector<int>& a, int start, int end) {
    return a[(start + end) / 2];
}

int getDoubleMid(const std::vector<int>& s1, const std::vector<int>& s2) {
    int length = s1.size();
    int i = 0, log_i = 1;
    while (log_i * 2 < length) { i++; log_i *= 2; }
    int start_a = 0, start_b = 0, end_a = length - 1, end_b = length - 1;
    
    while (i-- && start_a < end_a && start_b < end_b) {
        int mid_a = getMiddle(s1, start_a, end_a);
        int mid_b = getMiddle(s2, start_b, end_b);
        if (mid_a < mid_b) {
            start_a = (start_a + end_a) / 2 + 1;
            end_b = (start_b + end_b) / 2 - 1;
        } else {
            start_b = (start_b + end_b) / 2 + 1;
            end_a = (start_a + end_a) / 2 - 1;
        }
    }
    return std::min(s1[start_a], s2[start_b]);
}

int main() {
    std::vector<int> s1 = {1, 2, 3, 8, 9};
    std::vector<int> s2 = {4, 5, 6, 7, 10};
    int ret = getDoubleMid(s1, s2);
    std::cout << "Result: " << ret << std::endl;
    return 0;
}
```

## 2012_code_doublelink

```c++
#include <iostream>

struct Node {
    char data;
    Node* link;
};

void create(Node* p, const std::string& a, int pos) {
    if (pos < a.length()) {
        p->data = a[pos];
        p->link = new Node;
        p->link->data = '\0';
        create(p->link, a, pos + 1);
    }
}

Node* getSameNode(Node* a, Node* b) {
    int a_length = 0, b_length = 0;
    Node* a_p = a->link, * b_p = b->link;
    while (a_p->data != '\0') { a_length++; a_p = a_p->link; }
    while (b_p->data != '\0') { b_length++; b_p = b_p->link; }
    
    Node* a_scan = a->link, * b_scan = b->link;
    while (a_length < b_length) { b_scan = b_scan->link; b_length--; }
    while (b_length < a_length) { a_scan = a_scan->link; a_length--; }
    
    while (a_length-- > 0) {
        if (a_scan == b_scan) return a_scan;
        a_scan = a_scan->link;
        b_scan = b_scan->link;
    }
    return nullptr;
}

int main() {
    Node a, b;
    create(&a, "loading", 0);
    create(&b, "being", 0);
    
    Node* tmp = b.link->link->link;
    b.link->link = a.link->link->link->link;
    delete tmp;

    Node a_with_head, b_with_head;
    a_with_head.link = &a;
    b_with_head.link = &b;
    Node* same = getSameNode(&a_with_head, &b_with_head);
    
    if (same) {
        std::cout << "Same node found: " << same->data << std::endl;
    } else {
        std::cout << "No same node found" << std::endl;
    }
    
    return 0;
}
```

## 2013_code_mian_ele

```c++
#include <iostream>
#include <vector>

bool majority(const std::vector<int>& A) {
    int start = 0, count = 0;
    for (int j = 0; j < A.size(); j++) {
        if (A[start] == A[j]) count++;
        else count--;
        if (count == 0 && j < A.size() - 1) {
            start = ++j;
            count = 1;
        }
    }
    
    int mainElement = A[start];
    int countElement = 0;
    for (int num : A) {
        if (num == mainElement) countElement++;
    }
    return countElement > A.size() / 2;
}

int main() {
    std::vector<int> A = {1, 1, 0, 0, 0, 1, 1, 1, 0};
    bool isMajority = majority(A);
    if (isMajority) {
        std::cout << "有主元素" << std::endl;
    } else {
        std::cout << "没有主元素" << std::endl;
    }
    return 0;
}
```

## 2014_code_getwpl

```c++
#include <stdio.h>

#include <stdlib.h>

  

typedef struct treeNode {

int weight;

struct treeNode* left, * right;

}TNode;

  

/**

* 创建二叉树

*/

void create(TNode* node, int c[], int pos, int length) {

if (pos < length) {//填入数据

node->weight = c[pos];

if (pos * 2 + 1 < length) node->left = (TNode*)malloc(sizeof(TNode));

if (pos * 2 + 2 < length) node->right = (TNode*)malloc(sizeof(TNode));

create(node->left, c, pos * 2 + 1, length);

create(node->right, c, pos * 2 + 2, length);

}

}

  

int getWPL(TNode* root, int depth) {

if (root != NULL) {

int leftWeight = 0;

int rightWeight = 0;

if (root->left != NULL)leftWeight = getWPL(root->left, depth + 1);

if (root->right != NULL)rightWeight = getWPL(root->right, depth + 1);

return depth * root->weight + leftWeight + rightWeight;

}

else return 0;

}

  

int main() {

TNode* t = (TNode*)malloc(sizeof(TNode));

int c[] = { 54,4654,7565,234,436546,876876,353,757,2,345,23,445,1,235,0,6346 };

create(t, c, 0, 16);

int i = getWPL(t, 0);

printf("%d", i);

return 0;

}
```
