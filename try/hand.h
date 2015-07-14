#ifndef HAND_H
#define HAND_H
#include "card.h"
#include "deck.h"


struct hand {

	struct card card;
	struct hand *left;
	struct hand *right;

};

struct hand *build_hand(struct pile *pile);
void free_hand(struct hand *hand);
void add_card(struct hand **handp_loc, struct card card);


#endif /*HAND_H*/
