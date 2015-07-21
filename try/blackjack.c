
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "table.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>






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

void print_hand(int fd, struct hand *hand)
{
	if(!hand) {
		return;
	}

	print_hand(fd, hand->left);

	char buf[MAX_CARD_STR_LEN];
	if(!card_str(&hand->card, buf, sizeof(buf))) {
		write(fd, "Invalid card\n", 13);
	} else {
		write(fd, buf, strlen(buf));
		write(fd, "\n", 1);
	}
	print_hand(fd, hand->right);


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
    	//printf("%s has a hand of:\n", names[n]);
    	//print_hand(hand);
    }


    char asked[80];
    printf("Whose hand would you like to see?");
    scanf("%s", asked);
    int fd = creat(asked, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
    	perror("Could not create file");
    }
    print_hand(fd, fetch_table(players, asked));

    close(fd);
    //print_hand(fetch_table(players, asked));
    free_deck(deck);

}
