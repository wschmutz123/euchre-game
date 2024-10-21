#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
using namespace std;

Pack::Pack(){
    next = 0;
    int suit = 0;
    int rank = 7;
    for (int i = 0; i < PACK_SIZE; ++i){
        Card card (RANK_NAMES_BY_WEIGHT[rank], SUIT_NAMES_BY_WEIGHT[suit]);
        cards[i] = card;
        rank++;
        if (rank == 13){
            rank = 7;
            suit++;
        }
    }
}
Pack::Pack(std::istream& pack_input){
    next = 0;
    for (int i = 0; i < PACK_SIZE; ++i){
        string stringRank;
        string of;
        string stringSuit;
        pack_input >> stringRank;
        pack_input >> of;
        pack_input >> stringSuit;
        Card card(stringRank,stringSuit);
        cards[i] = card;
    }
}
Card Pack::deal_one(){
    Card card = cards[next];
    next++;
    return card;
}
void Pack::reset(){
    next = 0;
}
void Pack::shuffle(){
    std::array<Card, PACK_SIZE / 2> topCards;
    std::array<Card, PACK_SIZE / 2> bottomCards;
    int counter = 0;
    while (counter < 7){
    int j = 0;
    for (int i = 0; i < PACK_SIZE; ++i){
        if (i < 12){
            topCards[i] = cards[i];
        }
        else{
            bottomCards[j] = cards[i];
            j++;
        }
    }
        int b = 0;
        int t = 0;
        for (int i = 0; i < PACK_SIZE; ++i){
            if (i % 2 == 0){
                cards[i] = bottomCards[b];
                ++b;
            }
            else{
                cards[i] = topCards[t];
                ++t;
            }
        }
    reset();
    counter++;
    }
}
bool Pack::empty() const{
    if (next == 24){
        return true;
    }
    return false;
}
