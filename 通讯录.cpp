//项目名称:简单的通讯录管理程序
//项目功能:实现通讯录的增删改查功能
#include <iostream>
#include <cstring>
using namespace std;

//定义联系人结构体
struct Contact
{
    char name[50];
    char phone[12];
    struct Birthday
    {
        int year;
        int month;
        int day;
    }birthday;
    int age;
};

//【重点】Node结构体放前面！所有函数才能识别Node*
struct Node
{
    Contact data;
    Node* next;
};

// ========== 函数声明（提前声明，解决找不到标识符C3861） ==========
Node* InitAddressBook();
bool CreateAddressBookHead(Node* head, Contact data);
bool CreateAddressBookTail(Node* head, Contact data);
Contact InputContact();
void OutputContact(Contact data);
void OutputAddressBook(Node* head);
Node* SearchContactByName(Node* head, char* name);
Node* SearchContactByPhone(Node* head, char* phone);
bool InsertContactAfter(Node* head, Node* target, Contact data);
Node* SearchPreNode(Node* head, Node* target);
bool InsertContactBefore(Node* head, Node* target, Contact data);
bool DeleteContact(Node* head, Node* target);
bool DeleteContactNext(Node* head, Node* target);
int PrintMenu();
void ModifyContact(Node* head);
void FindContact(Node* head);
void DelContact(Node* head);
void FreeBook(Node* head);

// ========== 下面是函数定义 ==========
Node* InitAddressBook()
{
    Node* head=new Node;
    if(head==NULL)
    {
        cout<<"内存分配失败!"<<endl;
    }
    else
    {
        head->next=NULL;
    }
    return head;
}

bool CreateAddressBookHead(Node* head, Contact data)
{
    Node* node=new Node;
    if(node==NULL)
    {
        cout<<"内存分配失败!"<<endl;
        return false;
    }
    node->data=data;
    node->next=head->next;
    head->next=node;
    return true;
}

bool CreateAddressBookTail(Node* head, Contact data)
{
    static Node* tail=head;
    Node* node=new Node;
    if(node==NULL)
    {
        cout<<"内存分配失败!"<<endl;
        return false;
    }
    node->data=data;
    node->next=NULL;
    tail->next=node;
    tail=node;
    return true;
}

Contact InputContact()
{
    Contact data;
    cout<<"请输入联系人姓名:";
    cin >> data.name;
    cout<<"请输入联系人电话:";
    cin>>data.phone;
    cout<<"请输入联系人生日(年月日):";
    cin >> data.birthday.year >> data.birthday.month >> data.birthday.day;
    data.age= 2026 - data.birthday.year;
    return data;
}

void OutputContact(Contact data)
{
    cout<<"姓名:"<<data.name <<endl;
    cout<<"电话:"<<data.phone<<endl;
    cout<<"生日:"<<data.birthday.year <<"年"<<data.birthday.month<<"月"<<data.birthday.day <<"日"<<endl;
    cout<<"年龄:"<< data.age << endl;
    cout<<"-------------------------"<<endl;
}

void OutputAddressBook(Node* head)
{
    Node* node = head->next;
    if(node == nullptr)
    {
        cout<<"通讯录为空！"<<endl;
        return;
    }
    while (node)
    {
        OutputContact(node->data);
        node=node->next;
    }
}

Node* SearchContactByName(Node* head, char* name)
{
    Node* node=head->next;
    while (node)
    {
        if(strcmp(node->data.name, name)==0)
            return node;
        node=node->next;
    }
    return NULL;
}

Node* SearchContactByPhone(Node* head, char* phone)
{
    Node* node= head->next;
    while (node)
    {
        if (strcmp(node->data.phone, phone)==0)
            return node;
        node = node->next;
    }
    return NULL;
}

bool InsertContactAfter(Node* head, Node* target, Contact data)
{
    Node* node=new Node;
    if(node != nullptr)
    {
        node->data=data;
        node->next=target->next;
        target->next=node;
        return true;
    }
    return false;
}

Node* SearchPreNode(Node* head, Node* target)
{
    for(Node* pre = head;pre->next != NULL; pre = pre->next)
    {
        if(pre->next == target)
            return pre;
    }
    return NULL;
}

bool InsertContactBefore(Node* head, Node* target, Contact data)
{
    Node* pre=SearchPreNode(head, target);
    if(pre)
    {
        Node* node=new Node;
        if(node != nullptr)
        {
            node->data=data;
            node->next=target;
            pre->next=node;
            return true;
        }
    }
    return false;
}

bool DeleteContact(Node* head, Node* target)
{
    Node* pre=SearchPreNode(head, target);
    if(pre)
    {
        pre->next=target->next;
        delete target;
        return true;
    }
    return false;
}

bool DeleteContactNext(Node* head, Node* target)
{
    if(target->next)
    {
        Node* node=target->next;
        target->next=node->next;
        delete node;
        return true;
    }
    return false;
}

int PrintMenu()
{
    int choice;
    cout<<"====通讯录管理程序====" << endl;
    cout<<"1.添加联系人"<<endl;
    cout<<"2.删除联系人"<<endl;
    cout<<"3.查找联系人"<<endl;
    cout<<"4.修改联系人"<<endl;
    cout<<"5.显示所有联系人"<<endl;
    cout<<"6.退出程序"<<endl;
    cout<<"======================"<<endl;
    cout<<"请输入您的选择(1-6):";
    cin>>choice;
    return choice;
}

void ModifyContact(Node* head)
{
    char name[50];
    cout<<"请输入要修改的联系人姓名：";
    cin>>name;
    Node* p = SearchContactByName(head,name);
    if(p == nullptr)
    {
        cout<<"未找到该联系人！"<<endl;
        return;
    }
    cout<<"找到联系人，请输入新信息："<<endl;
    Contact newInfo = InputContact();
    p->data = newInfo;
    cout<<"修改完成！"<<endl;
}

void FindContact(Node* head)
{
    int op;
    cout<<"1.按姓名查找  2.按电话查找，请选择：";
    cin>>op;
    if(op == 1)
    {
        char name[50];
        cout<<"输入要查找的姓名：";
        cin>>name;
        Node* res = SearchContactByName(head,name);
        if(res) OutputContact(res->data);
        else cout<<"没有找到该联系人\n";
    }
    else if(op ==2)
    {
        char phone[12];
        cout<<"输入要查找的电话：";
        cin>>phone;
        Node* res = SearchContactByPhone(head,phone);
        if(res) OutputContact(res->data);
        else cout<<"没有找到该联系人\n";
    }
}

void DelContact(Node* head)
{
    char name[50];
    cout<<"输入要删除联系人姓名：";
    cin>>name;
    Node* p = SearchContactByName(head,name);
    if(p == nullptr)
    {
        cout<<"找不到联系人\n";
        return;
    }
    bool ok = DeleteContact(head,p);
    if(ok) cout<<"删除成功\n";
    else cout<<"删除失败\n";
}

void FreeBook(Node* head)
{
    Node* cur = head;
    while(cur != nullptr)
    {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
}

int main()
{
    Node* book = InitAddressBook();
    int select;
    while(true)
    {
        select = PrintMenu();
        switch(select)
        {
            case 1:{
                Contact c = InputContact();
                CreateAddressBookTail(book,c);
                cout<<"添加成功！\n";
                break;
            }
            case 2:
                DelContact(book);
                break;
            case 3:
                FindContact(book);
                break;
            case 4:
                ModifyContact(book);
                break;
            case 5:
                OutputAddressBook(book);
                break;
            case 6:
                FreeBook(book);
                cout<<"程序退出\n";
                return 0;
            default:
                cout<<"输入无效，请输入1~6\n";
        }
    }
    return 0;
}
