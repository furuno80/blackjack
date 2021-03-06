
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

void puts_hand(FILE *fh, struct hand *hand);

void print_hand(int fd, struct hand *hand)
{
	if(!hand) {
		return;
	}

	print_hand(fd, hand->left);

	char buf[MAX_CARD_STR_LEN];
	if(!card_str(&hand->card, buf, sizeof(buf))) {
		if(13 != write(fd, "Invalid card\n", 13)){
			perror("Could not write to placeholder");
		}
	} else {
		write(fd, buf, strlen(buf));
		write(fd, "\n", 1);
	}
	print_hand(fd, hand->right);


}

void puts_hand(FILE *fh, struct hand *hand)
{
	if(!hand) {
		return;
	}

	puts_hand(fh, hand->left);

	char buf[MAX_CARD_STR_LEN];
	if(!card_str(&hand->card, buf, sizeof(buf))) {
		if(!fputs("Invalid card\n", fh)){
			perror("Could not put placeholder");
		}
	} else {
		if(strlen(buf) + 1 != fprintf(fh, "%s\n", buf)){
			perror("Could not put card");

	puts_hand(fh, hand->right);

		}
	}
}




void library_save(char *name, struct hand *hand) {

	FILE *fh = fopen(name, "w");
	if(!fh) {
		perror("Could not open file %s");
		return;
	} else {

		if(fclose(fh)) {
			perror("Could not close file");
		}
		puts_hand(fh, hand);
	}

}

void system_save(char *name, struct hand *hand) {
	int fd = creat(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("Could not create file");
		//print_hand(fd, hand);
	} else {
		print_hand(fd, hand);
	}
	if (-1  ==close(fd)) {
		perror("Could not close file");
	}

}

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
    //print_hand(fd, fetch_table(players, asked));
    system_save(asked, fetch_table(players, asked));
    close(fd);
    //print_hand(fetch_table(players, asked));
    free_deck(deck);

}
