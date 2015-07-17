#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"

struct pile *standard_52(void) {
	struct pile *deck = NULL;
	struct pile *previous = NULL;

	//srand(time(NULL));

	for (int i = 0; i < 4; i++) {
		for (int p = 2; p < 15; p++) {
			struct pile *curr = malloc(sizeof(struct pile));
			if (!curr) {
				free(deck);
				return NULL;
			}
			curr->card.rank = p;
			curr->card.suit = i;
			curr->next = NULL;
			if (previous) {
				previous->next = curr;
			} else {
				deck = curr;
			}
			previous = curr;

		}
	}

//randomize the deck

	return deck;
}
//This should walk through how ever many cards that have been specified
struct pile *after(struct pile *deck, int count){
	while(count--) {
		deck = deck->next;
	}
	return deck;

}

void shuffle(struct pile *deck) {
	int size = pile_len(deck);

	while(size && deck) {
		int pos = rand() %size;
		struct pile *to_swap = after(deck, pos);
		if(!to_swap) {
			fprintf(stderr, "Hit end of deck unexpectedly: %d, %d\n", size, pos);
		}
		struct card tmp = deck->card;
		deck->card = to_swap->card;
		to_swap->card = tmp;
		deck = deck->next;
		size--;

	}


}

struct pile *deal(struct pile **deck, int count) {
	if(!deck || !*deck) {
		return NULL;
	}
	struct pile *hand = *deck;
	//Gives teh end of the new hand, so count-1 instead of count
	struct pile *end = after(hand, count-1);
	if(!end) {
		return NULL;
	}
	*deck = end->next;
	end->next = NULL;

	return hand;

}



void free_deck(struct pile *deck) {

	while(deck) {
		struct pile *next = deck->next;
		free(deck);
		deck = next;
	}
}

int pile_len(struct pile *deck){
	int x = 0;
	while(deck) {
		deck = deck->next;
		x++;
	}
	return x;
	//printf("There are %i in deck", x);
}
