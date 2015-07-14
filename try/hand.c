#include "hand.h"

struct hand *build_hand(struct pile *pile) {
	struct hand *new_hand = NULL;
	while(pile) {
		add_card(&new_hand, pile->card);
		pile = pile->next;
	}
	return new_hand;


}


void add_card(struct hand **handp_loc, struct card card) {
	if(!handp_loc) {
		return;
	}
	struct hand *handp = *handp_loc;
	if(!handp) {
		handp = malloc(sizeof(struct hand));
		handp->card = card;
		handp->left = NULL;
		handp->right = NULL;
		*handp_loc = handp;
	} else if (card.rank < handp->card.rank) {
		add_card(&handp->left, card);
	} else  {
		add_card(&handp->right, card);
	}
}


void free_hand(struct hand *hand)
{
	if(!hand) {
		return;
		//This will break from the current function
		//and go to the previous function
		//being the previous iteration of hand
	}

	free_hand(hand->left);
	free_hand(hand->right);
	free(hand);

}
