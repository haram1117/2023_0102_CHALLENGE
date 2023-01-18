//
// Created by haram on 2023-01-17.
//

#include <iostream>
#include <queue>
using namespace std;

// 이진 트리 node 기본 구조
struct node{
    string position; // 회사 직책
    node* first; // 하위 노드에 대한 링크 1
    node* second; // 하위 노드에 대한 링크 2
};

// 조직도 tree 구조
struct org_tree{

    node* root;

    // 루트 노드 생성
    static org_tree create_org_structure(const string& pos){
        org_tree tree;
        tree.root = new node{pos, nullptr, nullptr};
        return tree;
    }

    static node* find(node* root, const string& value){
        if(root == nullptr)
            return nullptr;

        // 루트 노드 검사
        if(root->position == value)
            return root;

        // 왼쪽 서브 트리에서 찾기
        auto firstFound = find(root->first, value);

        // 왼쪽 서브 트리에 존재
        if(firstFound != nullptr)
            return firstFound;

        // 오른쪽 서브 트리에서 찾기
        return find(root->second, value);
    }

    [[nodiscard]] bool addSubordinate(const string& manager, const string& subordinate) const{
        auto managerNode = find(root, manager);

        // manager 이름을 가진 node를 찾을 수 없을 때
        if(!managerNode){
            cout << manager << " 을(를) 찾을 수 없습니다: " << endl;
            return false;
        }

        // manager node에 이미 두 개의 하위 노드가 존재할 때
        if(managerNode->first && managerNode->second){
            cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다." << endl;
            return false;
        }


        if(!managerNode->first) //manager node의 first 노드에 추가
            managerNode->first = new node{subordinate, nullptr, nullptr};
        else //manager node의 second 노드에 추가
            managerNode->second = new node{subordinate, nullptr, nullptr};
        cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다." << endl;
        return true;
    }
};

int main(){
    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinate("CEO", "부사장");
    tree.addSubordinate("부사장", "IT부장");
    tree.addSubordinate("부사장", "마케팅부장");
    tree.addSubordinate("IT부장", "보안팀장");
    tree.addSubordinate("IT부장", "앱개발팀장");
    tree.addSubordinate("마케팅부장", "물류팀장");
    tree.addSubordinate("마케팅부장", "홍보팀장");
    tree.addSubordinate("부사장", "재무부장");

    return 0;
}





















































