////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmpsc311-f16-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMPSC311 at Penn State University.  See the related
//                   assignment page for details.
//
//   Author        : John Selnekovic
//   Last Modified : ????
//

// Include Files
#include <stdio.h>
#include <cmpsc311_util.h>
#include <time.h>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define WIN_AMOUNT 21
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card( int card ) {

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = { SPADE, CLUB, HEART, DIAMOND };
    int suit = card / 13, cardty = card % 13;
    if ( cardty == 8 ) {
        printf( "10%s", card_suits[suit] );
    } else {
        printf( "%c%s", card_faces[cardty], card_suits[suit] );
    }
    
    // Return zero
    return( 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards( int cards[], int num_cards ) 
{
    
    int loopCount = 0; //tracks loop runs to print to next line after a suit of cards
    
    int i = 0;
    for( i = 0; i < num_cards; i++)
    {
        print_card( cards[i] );
        loopCount++;
        if(loopCount == 13)
        {
            printf("\n");
            loopCount = 0;
        }
    } 
    printf( "\n" );
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : shuffle the cars
//
// Inputs       : cards - the array of cards to shuffle
//                num_cards - the number of cards in the shuffle deck
// Outputs      : 0 always

int shuffle_cards( int cards[], int num_cards ) 
{ 
    // pointer to an int array
    // malloc creates a section of memory a certian bit size
    // memory set aside(total bits) is the size of an int(in bits) * by the number of slots we want
    int *tempDeck;
    tempDeck = malloc( sizeof(int) * num_cards);

    //gets rid of garbage data in tempDeck array
    int i;
    for( i = 0; i < num_cards; i++)
    {
        tempDeck[i] = 0;
    }


    // takes random card from given deck and assigns
    // logic--------- 
    
    for( i = 0; i < num_cards; i++ )
    {
        int index = 0, count = 0, countTo = 0;
        countTo = ( (getRandomValue(  0,  num_cards - i) ) );

        while( count < countTo )
        {
            index++;
            if( cards[ index ] < 52 )
            {
                count++;
            }
        }

        tempDeck[i] = cards[index];
        cards[index] = NUM_CARDS + 1 ;
    }



    /*
    int indexDrawn;
    int trackIndexDrawn[NUM_CARDS];
    for( i = 0; i < NUM_CARDS; i++ )
    {
        trackIndexDrawn[i] = 0;
    }

    for( i = 0; i < num_cards; i++)
    {   
        do
        {
            indexDrawn = (getRandomValue( __uint32_t min, __uint32_t max )) % num_cards ; 
        } while ( trackIndexDrawn[indexDrawn] > 0 );
        
        trackIndexDrawn[ indexDrawn ] += 1;
        
    }*/




    for( i = 0; i < num_cards; i++ )
    {
        cards[i] = tempDeck[i];
    }

    free(tempDeck);

    return 0;
}

 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : value of the hand

int hand_value( int cards[], int num_cards ) 
{
    int card_faces[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
    int handValue = 0, i = 0, aceCheck = 0;
    for( i = 0; i < num_cards; i++ )
    {
        aceCheck = card_faces[ cards[i] % 13 ];
        if ( handValue > WIN_AMOUNT) && (aceCheck == 11)) )
        {
            handValue += aceCheck - 10;
        }
        else
        {
            handValue += aceCheck;
        }
        
    }
    return handValue;
}
 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards( int hand[], int num_cards ) 
{
    int i, j;
    for( i = 0; i < num_cards; i++)
    {
        for( j = 0; j < num_cards - i -1; j++)
        {
            if( hand[j] > hand[j+1] )
            {
                int placeHold = hand[j];
                hand[j] = hand[j+1];
                hand[j+1] = placeHold;
            }
            
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less 
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play( int hand[], int num_cards ) 
{
    if( hand_value( hand, num_cards) >= 17 )
    {
        return 0;
    }
    else
    {
        return 1;
    }    
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play( int hand[], int num_cards, int dealer_card ) 
{
    if( hand_value( hand, num_cards) >= 17 )
    {
        return 0;
    }
    else if ( ( (dealer_card % 13) < 7 ) && (hand_value( hand, num_cards) > 12) ) 
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : play_hand
// Description  : play a hand of black jack
//
// Inputs       : deck - the whole deck of cards
//                num_cards - the number of cards in the deck
//                player_money - pointer to player amount of money
// Outputs      : 1 if player wins, 0 if dealer wins

int play_hand( int deck[], int num_cards, float *player_money ) 
{
    printf("\n---- New hand -----");
    shuffle_cards( deck, num_cards);
    int playerHand[MAX_CARDS], dealerHand[MAX_CARDS];
    int i;
    for( i = 0; i < 2; i++)
    {
        
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram( float money_rounds[], int last_round ) 
{
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMPSC311 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main( int argc, char **argv ) 
{

    /* Local variables */
    int cmp311_deck[NUM_CARDS];  // This is the deck of cards

    /* Preamble information */
    printf( "CMPSC311 - Assignment #1 - Fall 2020\n\n" );
    srand(time(NULL)) ;

    /* Step #1 - create the deck of cards */
    int i; 
    for( i = 0; i < NUM_CARDS; i++)
    {
        cmp311_deck[i] = i;
    }
    /* Step #2 - print the deck of cards */
    print_cards( cmp311_deck, NUM_CARDS);

    /* Step #4 - shuffle the deck */
    shuffle_cards( cmp311_deck, NUM_CARDS);
    /* Step #5 - print the shuffled deck of cards */
    print_cards( cmp311_deck, NUM_CARDS );
    /* Step #6 - sort the cards */
    sort_cards( cmp311_deck, NUM_CARDS );
    /* Step #7 - print the sorted deck of cards */
    print_cards( cmp311_deck, NUM_CARDS );
    /* Step #9 - deal the hands */

    /* Step 10 show historgrapm */

    /* Exit the program successfully */
    printf( "\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n" );
    return( 0 );
}