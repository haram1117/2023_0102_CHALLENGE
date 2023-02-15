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
        if(!current){ // current nullptr (값 찾지 못함)
            cout << "\n";
            return nullptr;
        }

        if(value == current->data){
            cout << value << "를 찾았습니다.\n";
            return current;
        }

        else if(value > current->data){
            cout << current->data << "에서 오른쪽으로 이동\n";
            find_impl(current->right, value);
        }

        cout << current->data << "에서 왼쪽으로 이동\n";
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

        // 삭제할 노드 탐색
        if(current->data > value)
            current->left = delete_impl(current->left, value);
        else if(current->data < value)
            current->right = delete_impl(current->right, value);
        else{ // 삭제할 노드 탐색 완료
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

            // 자식 노드가 둘 다 있을 때
            auto tmp = successor(current);
            current->data = tmp->data;

            current->right = delete_impl(current->right, tmp->data);
        }
        return current;
    }

public:
    // 검색
    node* find(int value){
        return find_impl(root, value);
    }

    // 삽입
    void insert(int value){
        if(!root)
            root = new node{value, nullptr, nullptr};
        else
            insert_impl(root, value);
    }

    // 순회
    void inOrder(){ // 중위 순회 -> 오름차순
        inorder_impl(root);
    }

    // 후손 노드
    node* successor(node* start){
        auto current = start->right;
        while(current && current->left)
            current = current->left;
        return current;
    }

    // 삭제
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

    cout << "중위 순회 : ";
    tree.inOrder();
    cout << "\n";

    tree.deleteValue(12);
    cout << "12 삭제 후 중위 순회: ";
    tree.inOrder();
    cout << "\n";

    if(tree.find(12))
        cout << "yes\n";
    else
        cout << "no\n";

    return 0;
}