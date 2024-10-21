// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

  //EFFECTS Initializes Card to the Two of Spades
  Card::Card()
    : rank("Two"), suit("Spades") {}

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(const std::string &rank_in, const std::string &suit_in)
    : rank(rank_in), suit(suit_in) {}

  //EFFECTS Returns the rank
  string Card::get_rank() const {
    return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  string Card::get_suit() const {
    return suit;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  string Card::get_suit(const std::string &trump) const {
    if (trump == "Spades" && rank == "Jack" && suit == "Clubs")
             return "Spades";
         else if (trump == "Clubs" && rank == "Jack" && suit == "Spades")
             return "Clubs";
         else if (trump == "Hearts" && rank == "Jack" && suit == "Diamonds")
             return "Hearts";
         else if (trump == "Diamonds" && rank == "Jack" && suit == "Hearts")
             return "Diamonds";
         else
             return suit;
  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face() const {
      int testRank = 0;
      for (int i = 0; i < 13; ++i){
          if (rank == RANK_NAMES_BY_WEIGHT[i]){
              testRank = i;
          }
      }
      if (testRank > 8){
          return true;
      }
      return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const {
      if (suit == trump && rank == RANK_JACK){
          return true;
      }
      return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    std::string suitNext = Suit_next(trump);
    if (suit == suitNext && rank == "Jack"){
        return true;
    }
    return false;
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (suit == trump){
        return true;
    }
    if (is_left_bower(trump)){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
    string lhsRank = lhs.get_rank();
    string rhsRank = rhs.get_rank();
    string lhsSuit = lhs.get_suit();
    string rhsSuit = rhs.get_suit();
    int lRank = 0;
    int rRank = 0;
    for (int i = 0; i < 13; ++i){
        if (lhsRank == RANK_NAMES_BY_WEIGHT[i]){
            lRank = i;
        }
        if (rhsRank == RANK_NAMES_BY_WEIGHT[i]){
            rRank = i;
        }
    }
    if (lRank == rRank){
        int lSuit = 0;
        int rSuit = 0;
        for (int i = 0; i < 4; ++i){
           if (lhsSuit == SUIT_NAMES_BY_WEIGHT[i]){
               lSuit = i;
           }
           if (rhsSuit == SUIT_NAMES_BY_WEIGHT[i]){
               rSuit = i;
           }
        }
        if (lSuit < rSuit){
             return true;
        }
        return false;
    }
    if (lRank < rRank){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    if (operator<(lhs,rhs) == false && operator==(lhs,rhs) == false){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
     string lhsRank = lhs.get_rank();
     string rhsRank = rhs.get_rank();
     string lhsSuit = lhs.get_suit();
     string rhsSuit = rhs.get_suit();
     int lRank = 0;
     int rRank = 0;
     int lSuit = 0;
     int rSuit = 0;
     for (int i = 0; i < 13; ++i){
        if (lhsRank == RANK_NAMES_BY_WEIGHT[i]){
            lRank = i;
        }
        if (rhsRank == RANK_NAMES_BY_WEIGHT[i]){
            rRank = i;
        }
     }
    for (int i = 0; i < 4; ++i){
       if (lhsSuit == SUIT_NAMES_BY_WEIGHT[i]){
           lSuit = i;
       }
       if (rhsSuit == SUIT_NAMES_BY_WEIGHT[i]){
           rSuit = i;
       }
    }
    if (lRank == rRank && lSuit == rSuit){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if (operator==(lhs,rhs) == false){
        return true;
    }
    return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    if (suit == "Spades"){
        return "Clubs";
    }
    else if (suit == "Clubs"){
           return "Spades";
    }
    else if (suit == "Hearts"){
           return "Diamonds";
    }
    else{
        return "Hearts";
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
    for (size_t i = 0; i < card.get_rank().length(); ++i){
        os << card.get_rank()[i];
    }
    os << " of ";
    for (size_t i = 0; i < card.get_suit().length(); ++i){
        os << card.get_suit()[i];;
    }
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    std::string aSuit = a.get_suit();
    std::string bSuit = b.get_suit();
    std::string suit_next = Suit_next(trump);
    // Both cards are trump
    if (aSuit == trump && bSuit == trump) {
        if (a.get_rank() == "Jack")
            return false;
        else if (b.get_rank() == "Jack")
            return true;
        else
            return (a < b);       
    }
    // Neither card is trump
    else if (aSuit != trump && bSuit != trump) {
        if (a.is_left_bower(trump))
            return false;
        else if (b.is_left_bower(trump))
            return true;
        else
            return (a<b);
    }
    // a is trump and b is not trump
    else if (aSuit == trump && bSuit != trump) {
        if (b.is_left_bower(trump)) {
            if (a.is_right_bower(trump))
                return false;
            else
                return true;
        }
        else
            return false;
    }
    // a is not trump and a is trump
    else if (aSuit != trump && bSuit == trump) {
        if (a.is_left_bower(trump)) {
            if (b.is_right_bower(trump))
                return true;
            else
                return false;
        }
        else
            return true;
    }
    return true;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    std::string aSuit = a.get_suit();
    std::string bSuit = b.get_suit();
    std::string leadSuit = led_card.get_suit();
    std::string leadRank = led_card.get_rank();
    std::string suit_next = Suit_next(trump);
    string arank = a.get_rank();
    string brank = b.get_rank();
    
    if (a.is_trump(trump) || b.is_trump(trump))
        return Card_less(a,b,trump);
    else if (a.is_right_bower(trump))
        return false;
    else if (b.is_right_bower(trump))
        return true;
    else if (a.is_left_bower(trump))
        return false;
    else if (b.is_left_bower(trump))
        return true;
    else if (aSuit == leadSuit && bSuit == leadSuit) {
        if (leadSuit == trump || (leadSuit == suit_next && leadRank == "Jack"))
            return Card_less(a,b,trump);
        else
            return (a < b);       
    }
    else if (leadSuit == trump && !(a.is_trump(trump) || b.is_trump(trump)))
        return (a<b);
    else if (leadSuit == aSuit && leadSuit != bSuit)
        return false;
    else if (leadSuit != aSuit && leadSuit == bSuit)
        return true; 
    else
        return (a<b);

}

