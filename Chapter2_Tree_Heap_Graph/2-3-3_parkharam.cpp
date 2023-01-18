//
// Created by haram on 2023-01-17.
//

#include <iostream>
#include <queue>
using namespace std;

// ���� Ʈ�� node �⺻ ����
struct node{
    string position; // ȸ�� ��å
    node* first; // ���� ��忡 ���� ��ũ 1
    node* second; // ���� ��忡 ���� ��ũ 2
};

// ������ tree ����
struct org_tree{

    node* root;

    // ��Ʈ ��� ����
    static org_tree create_org_structure(const string& pos){
        org_tree tree;
        tree.root = new node{pos, nullptr, nullptr};
        return tree;
    }

    static node* find(node* root, const string& value){
        if(root == nullptr)
            return nullptr;

        // ��Ʈ ��� �˻�
        if(root->position == value)
            return root;

        // ���� ���� Ʈ������ ã��
        auto firstFound = find(root->first, value);

        // ���� ���� Ʈ���� ����
        if(firstFound != nullptr)
            return firstFound;

        // ������ ���� Ʈ������ ã��
        return find(root->second, value);
    }

    [[nodiscard]] bool addSubordinate(const string& manager, const string& subordinate) const{
        auto managerNode = find(root, manager);

        // manager �̸��� ���� node�� ã�� �� ���� ��
        if(!managerNode){
            cout << manager << " ��(��) ã�� �� �����ϴ�: " << endl;
            return false;
        }

        // manager node�� �̹� �� ���� ���� ��尡 ������ ��
        if(managerNode->first && managerNode->second){
            cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��� �� �����ϴ�." << endl;
            return false;
        }


        if(!managerNode->first) //manager node�� first ��忡 �߰�
            managerNode->first = new node{subordinate, nullptr, nullptr};
        else //manager node�� second ��忡 �߰�
            managerNode->second = new node{subordinate, nullptr, nullptr};
        cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��߽��ϴ�." << endl;
        return true;
    }
    static void preOrder(node* start){
        if(!start)
            return;
        cout << start->position << ", ";
        preOrder(start->first);
        preOrder(start->second);
    }

    static void inOrder(node* start){
        if(!start)
            return;
        inOrder(start->first);
        cout << start->position << ", ";
        inOrder(start->second);
    }

    static void postOrder(node* start){
        if(!start)
            return;
        postOrder(start->first);
        postOrder(start->second);
        cout << start->position << ", ";
    }

    static void levelOrder(node* start){
        if(!start)
            return;

        queue<node*> q;
        q.push(start);

        while (!q.empty()){
            int size = q.size();
            for(int i = 0; i < size; i++){
                auto current = q.front();
                q.pop();

                cout << current->position << ", ";
                if(current->first)
                    q.push(current->first);
                if(current->second)
                    q.push(current->second);
            }
            cout << "\n";
        }
    }
};

int main(){
    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinate("CEO", "�λ���");
    tree.addSubordinate("�λ���", "IT����");
    tree.addSubordinate("�λ���", "�����ú���");
    tree.addSubordinate("IT����", "��������");
    tree.addSubordinate("IT����", "�۰�������");
    tree.addSubordinate("�����ú���", "��������");
    tree.addSubordinate("�����ú���", "ȫ������");
    tree.addSubordinate("�λ���", "�繫����");

    tree.preOrder(tree.root);
    cout << "\n";
    tree.inOrder(tree.root);
    cout << "\n";
    tree.postOrder(tree.root);
    cout << "\n";
    tree.levelOrder(tree.root);

    return 0;
}