
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "deck.h"


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
int main()

{
    struct pile *deck = standard_52();
    shuffle(deck);
    //struct pile *curr = deck;
    struct pile *hand = deal(&deck, 5);

    print_deck(hand);
    printf("There are %i cards in the deck", pile_len(deck));

    free_deck(hand);
    free_deck(deck);




}
