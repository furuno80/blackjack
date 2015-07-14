
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "deck.h"
#include "hand.h"


void print_deck(struct pile *curr) {
    char buf[MAX_CARD_STR_LEN];

    while(curr) {
    	if(!card_str(&curr->card, buf, MAX_CARD_STR_LEN)) {
    		printf("Invalid card\n");
    	} else {
    		printf("%s\n", buf);
    	}
    	curr = curr->next;
    }

}

void print_hand(struct hand *hand)
{
	if(!hand) {
		return;
	}

	print_hand(hand->left);
	print_hand(hand->right);

	char buf[MAX_CARD_STR_LEN];
	if(!card_str(&hand->card, buf, sizeof(buf))) {
		printf("Invalid card\n");
	} else {
		printf("In hand: %s\n", buf);
	}

}


int main()

{
    struct pile *deck = standard_52();
    shuffle(deck);
    //struct pile *curr = deck;
    struct pile *dealt = deal(&deck, 5);

    //print_deck(dealt);
    struct hand *myhand = build_hand(dealt);
    print_hand(myhand);
    printf("There are %i cards in the deck", pile_len(deck));

    free_deck(dealt);
    free_deck(deck);




}
