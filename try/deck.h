#include "card.h"

struct pile {
	struct card card;
	struct pile *next;


};
//Create the deck of cards
struct pile *standard_52(void);
//free the deck of cards when finished
void free_deck(struct pile *deck);
//shuffle the cards
void shuffle(struct pile *deck);
//get the length of the cards
int pile_len(struct pile *deck);
//deal
struct pile *deal(struct pile **deck, int count);
