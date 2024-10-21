// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(test_player_get_name_human) {
  Player * alice = Player_factory("James", "Human");
  ASSERT_EQUAL(alice->get_name(), "James");
  delete alice;
}
static void add_cards_44(Player *player) {
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
  Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
  Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
  player->add_card(jack_spades);
  player->add_card(jack_clubs);
  player->add_card(ace_spades);
  player->add_card(king_spades);
  player->add_card(queen_spades);
}
static void add_cards(Player *player) {
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  player->add_card(jack_spades);
  player->add_card(queen_spades);
  player->add_card(ten_clubs);
  player->add_card(ace_diamonds);
  player->add_card(king_hearts);
}
TEST(test_simple_player_add_discard) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
  string trump = Card::SUIT_SPADES;
  bob->add_and_discard(queen_clubs);
  Card ledCard = bob->play_card(nine_clubs, trump);
  ASSERT_EQUAL(ledCard, queen_clubs);
  delete bob;
}
TEST(test_simple_player_add_discard2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_44(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
  string trump = Card::SUIT_SPADES;
  bob->add_and_discard(nine_spades);
  Card ledCard1 = bob->lead_card(trump);
  Card ledCard2 = bob->lead_card(trump);
  Card ledCard3 = bob->lead_card(trump);
  Card ledCard4 = bob->lead_card(trump);
  Card ledCard5 = bob->lead_card(trump);
  ASSERT_NOT_EQUAL(ledCard1, nine_spades);
  ASSERT_NOT_EQUAL(ledCard2, nine_spades);
  ASSERT_NOT_EQUAL(ledCard3, nine_spades);
  ASSERT_NOT_EQUAL(ledCard4, nine_spades);
  ASSERT_NOT_EQUAL(ledCard5, nine_spades);
  delete bob;
}
TEST(test_simple_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}
TEST(test_simple_player_make_trump_false_round_1) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_DIAMONDS;
  bool orderup = bob->make_trump(
      nine_diamonds,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);

  delete bob;
}
TEST(test_simple_player_lead_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_diamonds); //check led card
  delete bob;
}
TEST(test_simple_player_play_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
 // lead cards
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
// hand
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
  Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump);
  ASSERT_EQUAL(card_played, ace_diamonds);
  Card card_played_2 = bob->play_card(ten_diamonds, trump);
  ASSERT_EQUAL(card_played_2, ten_clubs);
  Card card_played_3 = bob->play_card(ten_spades, trump);
  ASSERT_EQUAL(card_played_3, queen_spades);
  Card card_played_4 = bob->play_card(queen_clubs, trump);
  ASSERT_EQUAL(card_played_4, jack_spades);
  Card card_played_5 = bob->play_card(queen_hearts, trump);
  ASSERT_EQUAL(card_played_5, king_hearts);
  delete bob;
}
static void add_cards_2(Player *player) {
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  player->add_card(jack_spades);
  player->add_card(jack_clubs);
  player->add_card(jack_hearts);
  player->add_card(jack_diamonds);
  player->add_card(king_hearts);
}
TEST(test_simple_player_make_trump_2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_2(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}
TEST(test_simple_player_play_card_2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_2(bob);
 // lead cards
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
// hand
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump);
  ASSERT_EQUAL(card_played, jack_spades);
  Card card_played_2 = bob->play_card(ten_diamonds, trump);
  ASSERT_EQUAL(card_played_2, jack_clubs);
  Card card_played_3 = bob->play_card(ten_spades, trump);
  ASSERT_EQUAL(card_played_3, king_hearts);
  Card card_played_4 = bob->play_card(queen_clubs, trump);
  ASSERT_EQUAL(card_played_4, jack_diamonds);
  Card card_played_5 = bob->play_card(queen_hearts, trump);
  ASSERT_EQUAL(card_played_5, jack_hearts);
  delete bob;
}
TEST(test_simple_player_play_card_3) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_2(bob);
 // lead cards
  Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
  Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
// hand
  Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_hearts, trump);
  ASSERT_EQUAL(card_played, jack_hearts);
  Card card_played_2 = bob->play_card(queen_hearts, trump);
  ASSERT_EQUAL(card_played_2, jack_diamonds);
  Card card_played_3 = bob->play_card(ten_diamonds, trump);
  ASSERT_EQUAL(card_played_3, jack_spades);
  Card card_played_4 = bob->play_card(ten_spades, trump);
  ASSERT_EQUAL(card_played_4, jack_clubs);
  Card card_played_5 = bob->play_card(queen_hearts, trump);
  ASSERT_EQUAL(card_played_5, king_hearts);
  delete bob;
}
static void add_cards_3(Player *player) {
  Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  player->add_card(king_clubs);
  player->add_card(queen_clubs);
  player->add_card(jack_hearts);
  player->add_card(queen_hearts);
  player->add_card(king_hearts);
}
TEST(test_simple_player_make_trump_pass) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_3(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);

  delete bob;
}
TEST(test_simple_player_make_trump_round_2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_3(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
  delete bob;
}
TEST(test_simple_player_make_trump_round_2_is_dealer) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_3(bob);

  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  bool orderup = bob->make_trump(
      ace_hearts,    //upcard
      true,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
  delete bob;
}
TEST(test_simple_player_make_trump_round_2_right_bower) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_3(bob);
  Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);

  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  bool orderup = bob->make_trump(
      ace_hearts,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
  delete bob;
}
TEST(test_simple_player_make_trump_round_2_pass) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_3(bob);
  Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
  Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);

  Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
    string trump = Card::SUIT_CLUBS;
  bool orderup = bob->make_trump(
      ace_clubs,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  delete bob;
}
static void add_cards_4(Player *player) {
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  player->add_card(ten_clubs);
  player->add_card(nine_clubs);
  player->add_card(jack_clubs);
  player->add_card(nine_diamonds);
  player->add_card(king_hearts);
}
TEST(test_simple_player_make_trump_non_face_cards) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_4(bob);

  Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
  string trump = Card::SUIT_CLUBS;
  bool orderup = bob->make_trump(
      king_clubs,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);

  delete bob;
}
TEST(test_simple_player_make_trump_round_2_face_cards) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_4(bob);

  Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      king_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}
TEST(test_simple_player_make_trump_round_2_face_fail) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_4(bob);

  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_HEARTS;
  bool orderup = bob->make_trump(
      ace_hearts,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);

  delete bob;
}
TEST(test_simple_player_lead_card_4) {
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_4(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(ace_diamonds);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, ace_diamonds); //check led card
  delete bob;
}
TEST(test_simple_player_play_card_4) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards_4(bob);
 // lead cards
  Card ace_clubs(Card::RANK_ACE, Card::SUIT_CLUBS);
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
  Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
// hand
  Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
  Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
  Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
  string trump = Card::SUIT_SPADES;
  Card card_played = bob->play_card(ace_clubs, trump);
  ASSERT_EQUAL(card_played, ten_clubs);
  Card card_played_2 = bob->play_card(ten_spades, trump);
  ASSERT_EQUAL(card_played_2, jack_clubs);
  Card card_played_3 = bob->play_card(ace_spades, trump);
  ASSERT_EQUAL(card_played_3, nine_clubs);
  Card card_played_4 = bob->play_card(queen_hearts, trump);
  ASSERT_EQUAL(card_played_4, king_hearts);
  Card card_played_5 = bob->play_card(queen_clubs, trump);
  ASSERT_EQUAL(card_played_5, nine_diamonds);
  delete bob;
}

// Add more tests here

TEST_MAIN()
