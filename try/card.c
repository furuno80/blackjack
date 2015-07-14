#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"


const char *const suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const int MAX_CARD_STR_LEN = 18;

int card_str(struct card *c, char *dst, size_t sz)
{
    if (!dst)
    {
        return 0;
    }

    char temp_rank[sz];
    char temp_suit[sz];
    if (c-> rank < 2)
    {
    	printf("THIS IS WHERE IT IS BREAKING !!!%i % i\n\n ", c->rank, c->suit);
        return 0;
    }
    else if (c->rank >= 2 && c->rank <= 10)
    {
        snprintf(temp_rank,sz, "%i", c->rank);
    }
    else if (c->rank == 11)
    {
        strncpy(temp_rank, "Jack", sz);

    }
    else if (c->rank == 12)
    {
        strncpy(temp_rank, "Queen", sz);
    }
    else if (c->rank == 13)
    {
        strncpy(temp_rank, "King", sz);
    }
    else if (c->rank == 14)
    {
        strncpy(temp_rank, "Ace", sz);
    }
    else
    {
        return 0;
    }


    if (c->suit == Clubs)
    {
        strncpy(temp_suit, "Clubs", sz);
    }
    else if (c->suit == Diamonds)
    {
        strncpy(temp_suit, "Diamonds", sz);
    }
    else if (c->suit == Hearts)
    {
        strncpy(temp_suit, "Hearts", sz);
    }
    else if (c->suit == Spades)
    {
        strncpy(temp_suit, "Spades", sz);
    }
    else
    {
        return 0;
    }

    snprintf(dst, sz, "%s of %s", temp_rank, temp_suit);
    return 1;
}



int blackjack_score(struct card *hand, size_t number_of_cards)
{
    int number[number_of_cards];
    int return_value = 0;
    for (int i = 0; i < number_of_cards; i++)
    {

        if (hand[i].rank > 0 && hand[i].rank < 11)
        {
            number[i] = hand[i].rank;

        }
        else if (hand[i].rank >10 && hand[i].rank < 14)
        {
            number[i] =10;
        }
        else if (hand[i].rank  == 14)
        {
            number[i] = 11;
        }
        else
        {
            return 0;
        }
        return_value += number[i];
    }
RETRY:
    while(return_value > 21)
    {
        for (int i = 0; i < number_of_cards; i++)
        {
            if (number[i] == 11)
            {
                number[i] = 1;
                return_value -= 10;
                //found ace
                goto RETRY;
            }


        }
        break;
    }


    return return_value;

}







/*
    if (hand[1].rank > 0 && hand[1].rank < 11) {
            number2 = hand[1].rank;
    } else if (hand[1].rank >10 && hand[1].rank < 14){
            number2 =10;
    } else if (hand[1].rank  == 14) {
            number2 = 11;
            }else {return 0;}

    number3 = number1 + number2;
    if (number3 == 21) {
    return number3;} else { return 0;}
    */

