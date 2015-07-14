#ifndef CARD_H
#define CARD_H
extern const int MAX_CARD_STR_LEN;
#include <stdlib.h>

enum card_suit {Clubs, Diamonds, Hearts, Spades};
struct card
{
    int rank;
    enum card_suit suit;
};
extern const char *const suit_names[];
//Returns score of the hand, given some number_of_cards
int blackjack_score(struct card *hand, size_t number_of_cards);
//Puts a string representation of c into dst.  dst must be of sz bites
int card_str(struct card *c, char *dst, size_t sz);


#endif
const int MAX_CARD_STR_LEN;
