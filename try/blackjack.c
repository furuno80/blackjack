
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "table.h"


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


int main()

{

    struct pile *deck = standard_52();
    char *names[] = {"Joal", "Liam", "James"};
    struct table *players = build_table(10);

    shuffle(deck);
    for (int n = 0; n < 3; n++) {
    	struct hand *hand = build_hand(deal(&deck, 5));
    	store_table(players, names[n], hand);
    	printf("%s has a hand of:\n", names[n]);
    	print_hand(hand);
    }


    char asked[80];
    printf("Whose hand would you like to see?");
    scanf("%s", asked);
    print_hand(fetch_table(players, asked));
    free_deck(deck);

}
