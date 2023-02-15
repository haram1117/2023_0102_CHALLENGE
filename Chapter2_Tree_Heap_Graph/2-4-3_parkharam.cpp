//
// Created by haram on 2023-02-15.
//
#include <iostream>

using namespace std;

struct node{
    int data;
    node* left;
    node* right;
};

struct bst{
    node* root = nullptr;

private:
    node* find_impl(node* current, int value){
        if(!current){ // current nullptr (�� ã�� ����)
            cout << "\n";
            return nullptr;
        }

        if(value == current->data){
            cout << value << "�� ã�ҽ��ϴ�.\n";
            return current;
        }

        else if(value > current->data){
            cout << current->data << "���� ���������� �̵�\n";
            find_impl(current->right, value);
        }

        cout << current->data << "���� �������� �̵�\n";
        find_impl(current->left, value);
    }

    void insert_impl(node* current, int value){
        if (value < current->data){
            if(!current->left){
                current->left = new node{value, nullptr, nullptr};
            }
            else{
                insert_impl(current->left, value);
            }
        }
        else{
            if(!current->right){
                current->right = new node{value, nullptr, nullptr};
            }
            else{
                insert_impl(current->right, value);
            };
        }
    }

    void inorder_impl(node* current){
        if(!current)
            return;

        inorder_impl(current->left);
        cout << current->data << " ";
        inorder_impl(current->right);
    }

    node* delete_impl(node* current, int value){
        if(!current)
            return nullptr;

        // ������ ��� Ž��
        if(current->data > value)
            current->left = delete_impl(current->left, value);
        else if(current->data < value)
            current->right = delete_impl(current->right, value);
        else{ // ������ ��� Ž�� �Ϸ�
            if(!current->left){
                auto tmp = current->right;
                delete current;
                return tmp;
            }
            if(!current->right){
                auto tmp = current->left;
                delete current;
                return tmp;
            }

            // �ڽ� ��尡 �� �� ���� ��
            auto tmp = successor(current);
            current->data = tmp->data;

            current->right = delete_impl(current->right, tmp->data);
        }
        return current;
    }

public:
    // �˻�
    node* find(int value){
        return find_impl(root, value);
    }

    // ����
    void insert(int value){
        if(!root)
            root = new node{value, nullptr, nullptr};
        else
            insert_impl(root, value);
    }

    // ��ȸ
    void inOrder(){ // ���� ��ȸ -> ��������
        inorder_impl(root);
    }

    // �ļ� ���
    node* successor(node* start){
        auto current = start->right;
        while(current && current->left)
            current = current->left;
        return current;
    }

    // ����
    void deleteValue(int value){
        delete_impl(root, value);
    }

};

int main(){
    bst tree;
    tree.insert(12);
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    cout << "���� ��ȸ : ";
    tree.inOrder();
    cout << "\n";

    tree.deleteValue(12);
    cout << "12 ���� �� ���� ��ȸ: ";
    tree.inOrder();
    cout << "\n";

    if(tree.find(12))
        cout << "yes\n";
    else
        cout << "no\n";

    return 0;
}