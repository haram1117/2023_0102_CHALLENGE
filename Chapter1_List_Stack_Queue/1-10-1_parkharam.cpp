//
// Created by haram on 2023-01-15.
//
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Job{
    int id;
    string userName;
    int pageNum;
public:
    Job(int _id, string _userName, int _pageNum): id(_id), userName(_userName), pageNum(_pageNum){}
    string printJob(){
        return to_string(id) + ", " + userName + ", " + to_string(pageNum);
    }
};
class Printer{
    queue<Job> jobQueue;
public:
    void Add(Job job){
        jobQueue.push(job);
    }

    string Execute(){
        string result = "";
        while(!jobQueue.empty()){
            Job job = jobQueue.front();
            jobQueue.pop();
            result += "\n" + job.printJob();
        }
        return result;
    }
};


int main(){
    Printer printer;
    printer.Add(Job(0, "user0", 15));
    printer.Add(Job(1, "user1", 16));
    printer.Add(Job(2, "user2", 17));
    printer.Add(Job(3, "user3", 5));
    printer.Add(Job(4, "user4", 18));

    cout << printer.Execute();

}