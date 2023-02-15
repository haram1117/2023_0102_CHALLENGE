//
// Created by haram on 2023-02-15.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node{
    string name;
    bool isDirectory;
    vector<node*> children;
};

struct nTree{
private:
    node* root = new node{"/", true};
    node* currentDirectory = root;

    node* search_impl(node* current, string path){

        if(path == ""){
            return current;
        }
        string target = "";
        string remain = "";
        if(path[0] == '/'){ // 절대 경로
            path = path.substr(1);
            int tmpIndex = path.find('/');
            target = path.substr(0, tmpIndex);
            remain = path.substr(tmpIndex + 1);

            if(tmpIndex == -1){
                target = remain;
                remain = "";
            }
        }
        else{ // 상대 경로
            int tmpIndex = path.find('/');
            if(tmpIndex == -1){
                target = path;
                remain = "";
            }
            else{
                target = path.substr(0, tmpIndex);
                remain = path.substr(tmpIndex);
            }
        }
        for(int i = 0; i < current->children.size(); i++){
            if(current->children[i]->name == target){
                return search_impl(current->children[i], remain);
            }
        }
    }



public:
    void search(string path){
        node* result;
        if(path[0] == '/'){
            result = search_impl(root, path);
        }
        else
            result = search_impl(currentDirectory, path);

        if(result)
            cout << "Found : " << (result->isDirectory ? "d" + result->name : "-" + result->name) << "\n";
        else
            cout << "Can't Find\n";
    }

    void changeCurrentDirectory(string path){
        if(path[0] == '/'){
            auto tmp = search_impl(root, path);
            if(!tmp->isDirectory){
                cout << "\n" << path << "is not a directory\n";
            }else{
                currentDirectory = search_impl(root, path);
                cout << "\ncurrentDirectory : " << path;
            }
        }
        else{
            auto tmp = search_impl(currentDirectory, path);
            if(!tmp->isDirectory){
                cout << "\n" << path << "is not a directory\n";
            }else{
                currentDirectory = search_impl(currentDirectory, path);
                cout << "\ncurrentDirectory : " << path;
            }
        }
    }

    // 현재 위치에 디렉토리 / 파일 추가
    void insert(string name, bool isDirectory){
        node* newNode = new node{name, isDirectory};
        currentDirectory->children.push_back(newNode);
    }

    // 현재 위치에서의 디렉토리 / 파일 출력
    void print(){
        cout << "\nPrint Directories / Files : \n";
        for(auto elem : currentDirectory->children){
            cout << (elem->isDirectory ? "d" + elem->name : "-" + elem->name) << "\n";
        }
    }
};

int main(){
    nTree nTree;
    nTree.insert("a", true);

    nTree.insert("b", false);
    nTree.insert("dd", true);
    nTree.search("a");
    nTree.search("b");
    nTree.changeCurrentDirectory("/a");
    nTree.insert("cc", true);
    nTree.print();

    nTree.changeCurrentDirectory("/b");

    return 0;
}