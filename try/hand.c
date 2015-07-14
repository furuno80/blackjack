#include "hand.h"

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
