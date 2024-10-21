#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Player.h"
using namespace std;

class Human : public Player{
public:
    Human(string name_in);
    
    const std::string & get_name() const;
    
    void add_card(const Card &c);
    
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const;
    
    void add_and_discard(const Card &upcard);
    
    Card lead_card(const std::string &trump);
    
    Card play_card(const Card &led_card, const std::string &trump);
    
    
private:
    string name;
    std::vector<Card> cardHand;
    
};
Human::Human(string name_in)
    :name(name_in) {}

const std::string& Human::get_name() const{
    return name;
}
void Human::add_card(const Card &c){
    assert(cardHand.size() < 5);
    cardHand.push_back(c);
    std::sort(cardHand.begin(), cardHand.end());
    return;
}
bool Human::make_trump(const Card &upcard, bool is_dealer,
                       int round, std::string &order_up_suit) const{
    
    assert(round == 1 || round == 2);
    for (size_t i = 0; i < cardHand.size(); ++i){
        cout << "Human player " << name << "'s hand: [" << i << "] ";
        operator<<(cout,cardHand[i]) << endl;
    }
    std::cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
    string decision;
    cin >> decision;
    if (decision == "pass"){
        return false;
    }
    else{
        order_up_suit = decision;
        return true;
    }
    // also if he's dealer he can't pass but we assume no cheating
}
void Human::add_and_discard(const Card &upcard){
    std::sort(cardHand.begin(), cardHand.end());
    for (size_t i = 0; i < cardHand.size(); ++i){
        cout << "Human player " << name << "'s hand: [" << i << "] ";
        operator<<(cout,cardHand[i]);
        cout << endl;
    }
    std::cout << "Discard upcard: [-1]" << endl;
    std::cout << "Human player " << name << ", please select a card to discard:" << endl;
    int discardNumber;
    cin >> discardNumber;
    for (int i = -1; i < MAX_HAND_SIZE; ++i){
        if (discardNumber == -1){
            break;
        }
        if (i == discardNumber && i != -1){
            cardHand[i] = upcard;
        }
    }
    return;
}
Card Human::lead_card(const std::string &trump){
    Card leadCard;
    sort(cardHand.begin(), cardHand.end());
    for (size_t i = 0; i < cardHand.size(); ++i){
        cout << "Human player " << name << "'s hand: [" << i << "] " <<
            cardHand[i] << endl;
    }
    cout << "Human player " << name << ", please select a card:" << endl;
    size_t card;
    cin >> card;
    for (size_t i = 0; i < cardHand.size(); ++i){
        if (i == card){
            leadCard = cardHand[i];
            cardHand.erase(cardHand.begin()+i);
        }
    }
    return leadCard;
}
Card Human::play_card(const Card &led_card, const std::string &trump){
    Card playCard;
    sort(cardHand.begin(), cardHand.end());
     for (size_t i = 0; i < cardHand.size(); ++i){
        cout << "Human player " << name << "'s hand: [" << i << "] "
            << cardHand[i] << endl;
     }
    cout << "Human player " << name << ", please select a card:" << endl;  
    size_t card;
    cin >> card;

    for (size_t i = 0; i < cardHand.size(); ++i){
        if (i == card){
            playCard = cardHand[i];
            cardHand.erase(cardHand.begin()+i);
        }
    }
    return playCard;
}


class Simple : public Player{
public:
    Simple(string name_in);
    
    const std::string& get_name() const;
   
    void add_card(const Card &c);
    
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const;
    
    void add_and_discard(const Card &upcard);
    
    Card lead_card(const std::string &trump);
    
    Card play_card(const Card &led_card, const std::string &trump);
private:
    string name;
    std::vector<Card> cardHand;
};

Simple::Simple(string name_in)
:name(name_in) {}

const std::string& Simple::get_name() const{
    return name;
}
void Simple::add_card(const Card &c){
    assert(cardHand.size() < 5);
    cardHand.push_back(c);
    std::sort(cardHand.begin(), cardHand.end());
}
bool Simple::make_trump(const Card &upcard, bool is_dealer,
                int round, std::string &order_up_suit) const{
    if (round == 1){
        int counter = 0;
        for (int i = 0; i < MAX_HAND_SIZE; ++i){
            if (cardHand[i].is_trump(order_up_suit) && cardHand[i].is_face()){
                counter++;
            }
        }
        if (counter >= 2){
            return true;
        }
        else {
            return false;
        }
    }
    if (round == 2){
        if (is_dealer == true){
            order_up_suit = Suit_next(order_up_suit);
            return true;
        }
        int counter = 0;
        for (int i = 0; i < MAX_HAND_SIZE; ++i){
            string suitNext = Suit_next(order_up_suit);
            if (cardHand[i].is_trump(suitNext) == true && cardHand[i].is_face() == true){
                counter++;
            }
        }
        if (counter >= 1){
            order_up_suit = Suit_next(order_up_suit);
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}
void Simple::add_and_discard(const Card &upcard){
    string trump = upcard.get_suit();
    std::sort(cardHand.begin(),cardHand.end());
    size_t repeat = 0;
    bool discardTheUpcard = true;
    for (size_t r = 0; r < cardHand.size() - 1; ++r) {
        if (Card_less(upcard, cardHand[r], upcard.get_suit()) == false)
            discardTheUpcard = false;
    }
    if (discardTheUpcard)
        return;

    while (repeat < cardHand.size()){
           for (size_t i = 0; i < cardHand.size() - 1; ++i){
               if (Card_less(cardHand[i], cardHand[i+1], trump) == false){
                   Card replaceCard;
                   replaceCard = cardHand[i];
                   cardHand[i] = cardHand[i+1];
                   cardHand[i+1] = replaceCard;
               }
           }
        repeat++;
    }
    cardHand[0] = upcard;
    return;
}
Card Simple::lead_card(const std::string &trump){
    Card leadCard;
    int counter = 0;
    for (size_t i = 0; i < cardHand.size(); ++i){
        if (cardHand[i].is_trump(trump) == false && counter == 0){
            leadCard = cardHand[i];
            counter++;
        }
        if (cardHand[i].is_trump(trump) == false && counter == 1){
            if (Card_less(leadCard, cardHand[i], trump) == true){
                leadCard = cardHand[i];
            }
        }
    }
    if (counter == 0){
         for (size_t i = 0; i < cardHand.size(); ++i){
             if (cardHand[i].is_trump(trump) == true && counter == 0){
                 leadCard = cardHand[i];
                 counter++;
             }
             bool card_less = Card_less(leadCard, cardHand[i], trump);
             if (cardHand[i].is_trump(trump) && counter == 1 && card_less){
                leadCard = cardHand[i];
             }
        }
    }
    for (size_t i = 0; i < cardHand.size(); i++){
        if (leadCard == cardHand[i]){
            cardHand.erase(cardHand.begin()+i);
        }
    }
    return leadCard;
}
Card Simple::play_card(const Card &led_card, const std::string &trump){
    Card playCard;
    std::sort(cardHand.begin(),cardHand.end());
    int counter = 0;
    for (size_t i = 0; i < cardHand.size(); ++i){
        if ((cardHand[i].get_suit(trump) == led_card.get_suit(trump) &&
             counter == 0) || (cardHand[i].get_suit(trump) == trump &&
            led_card.is_left_bower(trump) && counter == 0)){
            playCard = cardHand[i];
            counter++;
        }
        if (cardHand[i].get_suit(trump) == led_card.get_suit(trump) && counter == 1 &&
            Card_less(playCard, cardHand[i], trump)){
            playCard = cardHand[i];
        }
        if (cardHand[i].get_suit(trump) == trump && led_card.is_left_bower(trump) &&
            counter == 1 && (Card_less(playCard, cardHand[i], trump))){
            playCard = cardHand[i];
        }
    }
    if (counter == 0){

        for (size_t i = (cardHand.size()-1); i > 0; --i) {
            if (Card_less(cardHand[i-1], cardHand[i], trump) == false){
                Card replaceCard;
                replaceCard = cardHand[i-1];
                cardHand[i-1] = cardHand[i];
                cardHand[i] = replaceCard;
            }
        }

        playCard = cardHand[0];
    }

    for (size_t i = 0; i < cardHand.size(); i++){
        if (playCard == cardHand[i]){
            cardHand.erase(cardHand.begin()+i);
        }
    }
    return playCard;
}


Player * Player_factory(const std::string &name, const std::string &strategy){
    if (strategy == "Human"){
       return new Human(name);
    }
    else if (strategy == "Simple"){
        return new Simple(name);
    }
    else {
        assert(false);
        return nullptr;
    }
}
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}
