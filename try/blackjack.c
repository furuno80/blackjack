
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

	char buf[MAX_CARD_STR_LEN];
	if(!card_str(&hand->card, buf, sizeof(buf))) {
		printf("Invalid card\n");
	} else {
		printf("In hand: %s\n", buf);
	}
	print_hand(hand->right);


}

void build_table(struct hand *hand, char *name[]) {

}




int main()

{

    struct pile *deck = standard_52();
    char *names[] = {"Joal", "Liam", "James"};

    //This is a change
    shuffle(deck);
    //struct pile *curr = deck;
    for (int n = 0; n < 3; n++) {
    	struct hand *hand = build_hand(deal(&deck, 5));
    	//store_table(players, name[n], build_hand(deal(&deck, 5));
    	printf("%s has a hand of:\n", names[n]);
    	print_hand(hand);
    }

    //struct pile *James = deal(&deck, 5);
    //struct pile *Joal = deal(&deck, 5);
    //struct pile *Liam = deal(&deck, 5);
    //struct pile *dealt = deal(&deck, 5);
    //print_deck(James);
    printf("\n\n");
    //print_deck(Joal);
    printf("\n\n");
    //print_deck(Liam);
    printf("\n\n");
    //struct hand *myhand = build_hand(dealt);
    //struct hand *James_hand = build_hand(James);
    //struct hand *Joals_hand = build_hand(Joal);
    //struct hand *Liams_hand = build_hand(Liam);
    //print_hand(myhand);
    //printf("James' hand: \n\n");
    //print_hand(James_hand);
    //printf("\n\nJoal's hand:\n\n");
    //print_hand(Joals_hand);
    //printf("\n\nLiam's hand:\n\n");
    //print_hand(Liams_hand);
    printf("\n\nThere are %i cards in the deck\n", pile_len(deck));

    //free_hand(myhand);
    //free_deck(dealt);
    free_deck(deck);

}
