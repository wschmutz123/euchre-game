// Will Schmutz, 2/4/222
// Driver program
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

// Game ADT
class Game {
    private:
        vector<Player*> players;
        Pack pack;
        int team1_score = 0;
        int team2_score = 0;
        int numHands = 0;
        int pointsToWin;
        char *shuffleStatus;

    public:
        Game(vector<Player*> inputPlayers, Pack inputPack, int inputPoints, char *shuffle)
        : players(inputPlayers), pack(inputPack),
          pointsToWin(inputPoints), shuffleStatus(shuffle) {}
        

        void hand() {
        cout << "Hand " << numHands << "\n";
        if (strcmp(shuffleStatus, "shuffle") == 0) {
            pack.shuffle();
        }
        else
            pack.reset();
        
        int team1_tricks = 0;
        int team2_tricks = 0;
        int numTricks = 0;
        string trump;
        deal();
        cout << (*players[numHands%4]).get_name() << " deals" << endl;
        int teamToCall = makeTrump(trump, (numHands % 4));
        // The first person to lead will always be left of the dealer
        // In our case this is +1 index from dealer
            int lead = (numHands + 1) % 4;
            while (numTricks < 5){
                // returns the index of the player to lead the nect hand
                lead = playTrick(trump, lead);
                if (lead % 2 == 0){
                    team1_tricks++;
                }
                else{
                    team2_tricks++;
                }
                numTricks++;
            }
            determineScoring(team1_tricks, team2_tricks, teamToCall);
            // Print the score at the end of every hand
            cout << (*players[0]).get_name() << " and " << (*players[2]).get_name() <<
                    " have " << team1_score << " points\n";
            cout << (*players[1]).get_name() << " and " << (*players[3]).get_name() <<
                    " have " << team2_score << " points\n";
            cout << endl;
            numHands++;
        }
        int makeTrump(string &trump, int dealer) {
            // Deal the upcard
            Card upCard = pack.deal_one();
            cout << upCard << " turned up" << "\n";
            string orderSuit = upCard.get_suit();
            bool trumpMade = false;
            int teamToCall;
            int round = 1;
                for (int i = 1; i < 9; ++i) {
                    // Switch round to 2 after eveyone has gone once
                    if (i == 5)
                        round = 2;
                    
                    // Find the player who's turn it is to call
                    Player *playerUp = (players[(dealer+i)%4]);
                    // Special circumstances if dealer calls trump in round 1
                    if ((dealer+i)%4 == dealer && round == 1)
                      trumpMade = (*playerUp).make_trump(upCard, true, round, orderSuit);
                        
                    // Invoke stick the dealer conditions
                    else if ((dealer+i)%4 == dealer && round == 2){
                      trumpMade = (*playerUp).make_trump(upCard, true, round, orderSuit);
                    }
                    else{
                      trumpMade = (*playerUp).make_trump(upCard, false, round, orderSuit);
                    }

                    // If trump has been made, determine which team called it
                    if (trumpMade && round == 1) {
                        cout << (*playerUp).get_name() << " orders up " << orderSuit;
                        cout << endl;
                        (*players[dealer]).add_and_discard(upCard);
                        cout << endl;
                        teamToCall = ((dealer+i)%2) + 1;   
                        trump = orderSuit;
                        return teamToCall;
                    }
                    else if (trumpMade && round != 1){
                        teamToCall = ((dealer+i)%2) + 1;
                        cout << (*playerUp).get_name() << " orders up " << orderSuit;
                        cout << endl << endl;
                        trump = orderSuit;
                        return teamToCall;
                    }
                    else {
                        cout << (*playerUp).get_name() << " passes" << endl;
                    }
                }
            return -1;
        }

        int playTrick(string &trump, int lead) {
           // I changed the return value on this function to return the index of
           // the player who won the trick. This helped establish who will lead the 
           // next hand in the hand() function
            vector<Card> cards;
            Card ledCard = (*players[lead]).lead_card(trump);
            operator<<(cout,ledCard) << " led by " 
                << (*players[(lead)]).get_name() << endl;
            Card cardOne = (*players[(lead+1)%4]).play_card(ledCard, trump);
            operator<<(cout,cardOne) << " played by " 
                << (*players[((lead+1)%4)]).get_name() << endl;
            Card cardTwo = (*players[(lead+2)%4]).play_card(ledCard, trump);
            operator<<(cout,cardTwo) << " played by " 
                << (*players[((lead+2)%4)]).get_name() << endl;
            Card cardThree = (*players[(lead+3)%4]).play_card(ledCard, trump);
            operator<<(cout,cardThree) << " played by " 
                << (*players[((lead+3)%4)]).get_name() << endl;
            cards.push_back(ledCard);
            cards.push_back(cardOne);
            cards.push_back(cardTwo);
            cards.push_back(cardThree);
            size_t counter = 0;
                while (counter < cards.size()){
                // find largest card
                for (size_t i = 0; i < (cards.size() -1); ++i){
                    if (Card_less(cards[i], cards[i+1], ledCard, trump)){
                        Card replaceCard;
                        replaceCard = cards[i];
                        cards[i] = cards[i+1];
                        cards[i+1] = replaceCard;
                }
                }
                counter++;
                }
            if (cards[0] == cardOne){
                cout << (*players[(lead+1)%4]).get_name() << " takes the trick\n" << endl;
                lead = (lead + 1)%4;
            }
            else if (cards[0] == cardTwo){
                cout << (*players[(lead+2)%4]).get_name() << " takes the trick\n" << endl;
                lead = (lead + 2)%4;
            }
            else if (cards[0] == cardThree){
                cout << (*players[(lead+3)%4]).get_name() << " takes the trick\n" << endl;
                lead = (lead + 3)%4;
            }
            else{
                cout << (*players[lead%4]).get_name() << " takes the trick\n" << endl;
            }
            return lead;
        }
    void deal() {
           // Same function you wrote but can now accesss the pointers-to-Player
           int blatches = 0;
           int dealer = numHands % 4;
           int playerReceivingCard = dealer;
           while (blatches < 4){
                if (blatches % 2 == 0){
                    (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                    (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                    (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                }
                else {
                    (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                    (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                }
                playerReceivingCard++;
                blatches++;
            }
            while (blatches < 8){
                    if (blatches % 2 == 0){
                        (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                        (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                    }
                    else {
                        (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                        (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                        (*players[(playerReceivingCard+1)%4]).add_card(pack.deal_one());
                    }
                playerReceivingCard++;
                blatches++;
            }
        }
        void playGame() {
           // Play game runs the hand() function until a team wins
            while (team1_score < pointsToWin && team2_score < pointsToWin)
                hand();
                
            // Once the game is over, print the winning team
            if (team1_score >= pointsToWin) {
                cout << (*players[0]).get_name() << " and " << (*players[2]).get_name()
                 << " win!" << endl;
            }
            else if (team2_score >= pointsToWin) {
                cout << (*players[1]).get_name() << " and " << (*players[3]).get_name()
                 << " win!" << endl;
            }
        }

        void determineScoring(int team1_tricks, int team2_tricks, int teamToCall) {
            // This block determines the scoring that came from the hand
            if (team1_tricks == 3 || team1_tricks == 4){
                if (teamToCall == 1){
                    cout << (*players[0]).get_name() << " and " <<
                    (*players[2]).get_name() << " win the hand" << endl;
                    team1_score++;
                }
                else {
                    cout << (*players[0]).get_name() << " and " <<
                    (*players[2]).get_name() << " win the hand" << endl;
                    cout << "euchred!" << endl;
                    team1_score += 2;
                }
            }
            if (team1_tricks == 5){
                if (teamToCall == 1){
                    cout << (*players[0]).get_name() << " and " <<
                    (*players[2]).get_name() << " win the hand" << endl;
                    cout << "march!" << endl;
                    team1_score += 2;
                }
                else {
                    cout << (*players[0]).get_name() << " and " <<
                    (*players[2]).get_name() << " win the hand" << endl;
                    cout << "euchred!" << endl;
                    team1_score += 2;
                }
            }
            if (team2_tricks == 3 || team2_tricks == 4){
                if (teamToCall == 2){
                    cout << (*players[1]).get_name() << " and " <<
                    (*players[3]).get_name() << " win the hand" << endl;
                    team2_score++;
                }
                else {
                    cout << (*players[1]).get_name() << " and " <<
                    (*players[3]).get_name() << " win the hand" << endl;
                    cout << "euchred!" << endl;
                    team2_score += 2;
                }
            }
            if (team2_tricks == 5){
                if (teamToCall == 2){
                    cout << (*players[1]).get_name() << " and " <<
                    (*players[3]).get_name() << " win the hand" << endl;
                    cout << "march!" << endl;
                    team2_score += 2;
                }
                else {
                    cout << (*players[1]).get_name() << " and " <<
                    (*players[3]).get_name() << " win the hand" << endl;
                    cout << "euchred!" << endl;
                    team2_score += 2;
                }
            }
            // End of determining scoring from the hand
        }

};


int main(int argc, char *argv[]) {
    // Check for input errors
    // Initial checks to make sure the simulator can advance
    // The error checks are in the project specs
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return -1;
    }
    else if (stoi(argv[3]) < 0 || stoi(argv[3]) > 100) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return -2;
    }
    else if (strcmp(argv[2], "shuffle") != 0 && strcmp(argv[2], "noshuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

        return -3;
    }
    for (int i = 5; i <= 11; i += 2) {
        if (strcmp(argv[i], "Simple") != 0 && strcmp(argv[i], "Human")) {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;

        return -4;
        }
    }
  

    // All initial checks are done and the simulator can proceed
    Player *one = Player_factory(argv[4], argv[5]);
    Player *two = Player_factory(argv[6], argv[7]);
    Player *three = Player_factory(argv[8], argv[9]);
    Player *four = Player_factory(argv[10], argv[11]);
    vector<Player*> players;
    players.push_back(one);
    players.push_back(two);
    players.push_back(three);
    players.push_back(four);
    ifstream file;
    file.open(argv[1]);
    if (!file.is_open()) {
        cout << "Error opening " << argv[1]<< endl;
    }
    Pack pack(file);
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << "\n";
    Game game(players, pack, stoi(argv[3]), argv[2]);
    game.playGame();
    
    // Delete the vector of pointers to Players
    for (int i = 0; i < 4; ++i){
        delete players.at(i);
    }
    
    return 0;

}
