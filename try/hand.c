#include "hand.h"

void zig(struct hand **handp_loc) {
	struct hand *root = *handp_loc;
	struct hand *target = root->left;

	root->left = target->right;
	target->right = root;

	*handp_loc = target;

}

void zigzag(struct hand **hanp_loc) {
	struct hand *root = *hanp_loc;
	struct hand *parent = root->left;
	struct hand *target = parent->right;
	;
	if (!target) {
		zig(hanp_loc);
		return;
	}
	root->left = target->right;
	parent->right = target->left;
	target->left = parent;
	target->right = root;

}

//Assumes *handp_loc is not NULL
void splay(struct hand **handp_loc, int needle) {

	struct hand *hand = *handp_loc;
	while (needle != hand->card.rank) {

		if (needle < hand->left->card.rank) {
			if (!hand->left) {
				return;
			}
		 else if (hand->left->card.rank < needle && hand->left->right) {
			//Target is right of our left, zigzag splay and try again
			zigzag(&hand);
			continue;
		} else {
			zig(&hand);
			continue;
		}
	} else if (needle > hand->left->card.rank) {
		if (!hand->right) {
			return;
		} else if (hand->right->card.rank >= needle) {
			zig
		}
	}

}
}

struct hand *build_hand(struct pile *pile) {
struct hand *new_hand = NULL;
while (pile) {
	add_card(&new_hand, pile->card);
	pile = pile->next;
}
return new_hand;

}

void add_card(struct hand **handp_loc, struct card card) {
if (!handp_loc) {
	return;
}
struct hand *handp = *handp_loc;
if (!handp) {
	handp = malloc(sizeof(struct hand));
	handp->card = card;
	handp->left = NULL;
	handp->right = NULL;
	*handp_loc = handp;
} else if (card.rank < handp->card.rank) {
	add_card(&handp->left, card);
} else {
	add_card(&handp->right, card);
}
}

void free_hand(struct hand *hand) {
if (!hand) {
	return;
	//This will break from the current function
	//and go to the previous function
	//being the previous iteration of hand
}

free_hand(hand->left);
free_hand(hand->right);
free(hand);

}
