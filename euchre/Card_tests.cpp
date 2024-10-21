// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_card_suit_and_rank) {
    Card two_spades(RANK_NAMES_BY_WEIGHT[12],SUIT_NAMES_BY_WEIGHT[3]);
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_ACE);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_DIAMONDS);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}
TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_SPADES);
    ASSERT_TRUE(three_spades.is_face());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(three_spades.is_trump(Card::SUIT_CLUBS));
}
TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_Card_less_self_casic) {
    Card five_spades = Card(Card::RANK_FIVE, Card::SUIT_SPADES);
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(three_spades, five_spades, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(three_spades, five_spades, three_spades,
                           Card::SUIT_CLUBS));
}
TEST(test_Card_less_self_trump) {
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(jack_diamonds,
                           king_clubs, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(jack_diamonds, king_clubs, king_clubs,
                           Card::SUIT_DIAMONDS));
}
TEST(test_Card_less_self_leftbower) {
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(jack_diamonds,
                           king_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_diamonds, king_hearts, king_hearts,
                           Card::SUIT_HEARTS));
}
TEST(test_Card_less_self_leadcard) {
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(king_diamonds,
                           ten_diamonds, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(king_diamonds, ten_diamonds, nine_clubs,
                           Card::SUIT_HEARTS));
}
TEST(test_Card_less_self_leadcard2) {
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(king_hearts,
                           ten_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_hearts, ten_diamonds, nine_diamonds,
                           Card::SUIT_SPADES));
}
TEST(test_Card_less_leftvsright) {
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(jack_hearts,
                           jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_hearts, jack_diamonds, nine_diamonds,
                           Card::SUIT_HEARTS));
}
TEST(test_Card_less_right_trump) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(queen_hearts,
                           queen_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(queen_hearts, queen_diamonds, nine_diamonds,
                           Card::SUIT_DIAMONDS));
}
TEST(test_Card_less_trump_vs_lead) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(queen_diamonds,
                           ace_hearts, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(queen_diamonds, ace_hearts, nine_hearts,
                           Card::SUIT_DIAMONDS));
}
TEST(test_Card_same_card) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_diamonds2 = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(queen_diamonds,
                           queen_diamonds2, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(queen_diamonds, queen_diamonds2, nine_hearts,
                           Card::SUIT_DIAMONDS));
}
TEST(test_Card_same_value) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(queen_diamonds,
                           queen_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(queen_diamonds, queen_spades, nine_hearts,
                           Card::SUIT_CLUBS));
}
TEST(test_Card_different_value) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(queen_diamonds,
                           king_spades, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(queen_diamonds, king_spades, nine_hearts,
                           Card::SUIT_CLUBS));
}
TEST(test_Card_trump_value) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(queen_diamonds,
                           king_spades, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(queen_diamonds, king_spades, nine_spades,
                           Card::SUIT_DIAMONDS));
}
TEST(test_Card_new_value) {
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(queen_diamonds,
                           queen_hearts, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(queen_diamonds, queen_hearts, nine_spades,
                           Card::SUIT_DIAMONDS));
}
TEST(test_card_self_comparison) {
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(ten_diamonds < king_diamonds);
    ASSERT_FALSE(ten_diamonds > king_diamonds);
    ASSERT_FALSE(ten_diamonds == king_diamonds);
    ASSERT_TRUE(ten_diamonds != king_diamonds);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

// Add more test cases here

TEST_MAIN()
