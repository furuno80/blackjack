#include "hand.h"
#include <stdio.h>

void zig(struct hand **handp_loc, struct hand *target) {
	struct hand *root = *handp_loc;

	if (target == root->left) {
		root->left = target->right;
		target->right = root;
	} else {
		root->right = target->left;
		target->left = root;
	}
	*handp_loc = target;

}

int zigzag(struct hand **hanp_loc, struct hand *parent) {
	struct hand *root = *hanp_loc;
	struct hand *target, *new_left, *new_right;
	if(parent == root->left) {
		target = parent->right;
		new_left = parent;
		new_right = root;
	} else {
		target = parent->left;
		new_left = root;
		new_right = parent;
	}

	if (!target) {
		//Could not completely zig zag
		zig(hanp_loc, parent);
		return 0;
	}

	new_right->left = target->right;
	new_left->right = target->left;
	target->left = new_left;
	target->right = new_right;
	*hanp_loc = target;
	return 1;

}

//Assumes *handp_loc is not NULL
void splay(struct hand **handp_loc, int needle) {

	struct hand *hand = *handp_loc;
	while (needle != hand->card.rank) {
		struct hand *side;
		int factor = 1;
		if (needle < hand->card.rank) {
			side = hand->left;
		}
		 else  {
			 side = hand->right;
			 factor = -1;
		}
		if (!side) {
			//target does not exist, stop
			break;
	} else if (factor * (needle - side->card.rank)>0) {
		//Target is an inner node
		if(zigzag(&hand, side)) {
		continue;
		} else {
			//could not complete a zigzag, target does not exist
			break;
		}
	} else {
		//Target is on the outside
		zig(&hand, side);
		continue;
		}
	}
	*handp_loc = hand;
}

struct hand *build_hand(struct pile *pile) {
struct hand *new_hand = NULL;
while (pile) {
	add_card(&new_hand, pile->card);
	//printf("Building hand: %d\n", pile->card.rank);
	//pprint_hand(new_hand, 0);
	pile = pile->next;
}
pprint_hand(new_hand, 0);
return new_hand;

}

void add_card(struct hand **handp_loc, struct card card) {
	if (!handp_loc) {
		return;
	}
	struct hand *root = *handp_loc;
	struct hand *added_card = malloc(sizeof(struct hand));

	added_card->card = card;
	added_card->left = NULL;
	added_card->right = NULL;
	if (!root) {
		*handp_loc = added_card;
		return;
	}
	splay(&root, card.rank);
	if (card.rank < root->card.rank) {
		if(root->left && root->left->card.rank < card.rank) {
			added_card->left = root->left;
		}
		else if (root->left) {
			added_card->right = root->left;
		}
		root->left = added_card;
	}
	else {
		if(root->right && root->right->card.rank < card.rank){
			added_card ->left = root->right;

		} else if (root->right) {
			added_card->right = root-> right;
		}
	root->right = added_card;
	}
	splay(&root, card.rank);
	*handp_loc = root;

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

void pprint_hand(struct hand *hand, int space) {

	for(int n = 0; n < space; n++) {
		printf(" ");
	}
	if(!hand) {
		printf("NULL\n");
		return;
	}
	char buf[MAX_CARD_STR_LEN];
	if (!card_str(&hand->card, buf, sizeof(buf))) {
		printf("Invalid card\n");
	} else {
		printf("In hand: %s\n", buf);
	}
	pprint_hand(hand->left, space + 1);
	pprint_hand(hand->right, space + 1);
}
