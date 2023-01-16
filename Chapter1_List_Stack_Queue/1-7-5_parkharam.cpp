//
// Created by haram on 2023-01-15.
//
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// 카드 정보 구조체
struct card{
    int number;
    enum suit{
        HEART,
        SPADE,
        CLUB,
        DIAMOND
    } suit;

    [[nodiscard]] string to_string() const{
        ostringstream os;
        if(number > 1 && number <= 10){
            os << number;
        }
        else{
            switch (number) {
                case 1:
                    os << "Ace";
                    break;
                case11:
                    os << "Jack";
                    break;
                case12:
                    os << "Queen";
                    break;
                case13:
                    os << "King";
                    break;
                default:
                    return "Invalid";
            }
        }
        os << " of ";
        switch (suit) {
            case HEART:
                os << "hearts";
                break;
            case SPADE:
                os << "spades";
                break;
            case CLUB:
                os << "clubs";
                break;
            case DIAMOND:
                os << "diamonds";
                break;
        }
        return os.str();
    }
};

// 게임 전체를 관리하는 클래스
class gameManager{
private:
    array<card, 52> deck;

    vector<vector<card>> players;

    vector<card> player1;
    vector<card> player2;
    vector<card> player3;
    vector<card> player4;

public:
    // 카드 초기화
    void initCard(){
        for(int i = 0; i < 13; i++){
            deck[i] = card{i + 1, card::HEART};
        }
        for(int i = 0; i < 13; i++){
            deck[i + 13] = card{i + 1, card::SPADE};
        }
        for(int i = 0; i < 13; i++){
            deck[i + 26] = card{i + 1, card::CLUB};
        }
        for(int i = 0; i < 13; i++){
            deck[i + 39] = card{i + 1, card::DIAMOND};
        }
    }
    // 카드 섞기
    void mixCard(){
        shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device()()));
    }

    // 카드 나누기
    void divideCard(){
        player1 = {deck.begin(), deck.begin() + 13};
        player2 = {deck.begin() + 13, deck.begin() + 26};
        player3 = {deck.begin() + 26, deck.begin() + 39};
        player4 = {deck.begin() + 39, deck.end()};
        players = {player1, player2, player3, player4};
    }

    // 카드 비교
    bool checkCard(vector<card>& player1, vector<card>& player2){
        if(player1.back().number == player2.back().number){
            player1.pop_back();
            player2.pop_back();
            return true;
        }
        return false;
    }
    void play(){
        if(checkCard(player1, player2)){
            checkCard(player1, player3);
            return;
        }
        if(checkCard(player1, player3)){
            checkCard(player2, player4);
            return;
        }
        if(checkCard(player1, player4)){
            checkCard(player2, player3);
            return;
        }
        if(checkCard(player2, player3)){
            return;
        }
        if(checkCard(player2, player4))
            return;
        if(checkCard(player3, player4))
            return;

        shuffle(player1.begin(), player1.end(), std::mt19937(std::random_device()()));
        shuffle(player2.begin(), player2.end(), std::mt19937(std::random_device()()));
        shuffle(player3.begin(), player3.end(), std::mt19937(std::random_device()()));
        shuffle(player4.begin(), player4.end(), std::mt19937(std::random_device()()));
    }
    string winner(){
        if(player1.empty())
            return "player1";
        if(player2.empty())
            return "player2";
        if(player3.empty())
            return "player3";
        if(player4.empty())
            return "player4";
    }
    void playGame(){
        while(!player1.empty() && !player2.empty() && !player3.empty() && !player4.empty())
            play();
    }
};

int main(){
    gameManager game;
    game.initCard();
    game.mixCard();
    game.divideCard();
    game.playGame();
    cout << game.winner();
    return 0;
}