#include "hand.h"

void add_card(struct hand *hand, struct card card) {
	if(!hand) {
		hand = malloc(sizeof(struct hand));
		hand.card = card;
		hand->left = NULL;
		hand->right = NULL;
	} else if (card.rank < hand->card.rank) {
		add_card(hand->left, card);
	} else  {
		add_card(hand->right, card);
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
