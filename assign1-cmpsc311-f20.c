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
    
    int i;
    //modern method
    for( i = num_cards - 1; i > 1; i--) 
    {
        int j = getRandomValue( 0, i );

        int temp = cards[ i ];
        cards[ i ] = cards[ j ];
        cards[j] = temp;
    }

    //could not implement original


    //int tempDeck[NUM_CARDS];

    //gets rid of garbage data in tempDeck array

    /*for( i = 0; i < NUM_CARDS; i++)
    {
        tempDeck[i] = 0;
    }*/
    


    // takes random card from given deck and assigns
    // logic--------- 
    


    /*for( i = 0; i < num_cards; i++ )
    {
        int index = 0, count = 0, countTo = 0;
        
        //reverses deck correctly with
        // countTo = (num_ cards - i );
        //getRandomValue( 0, (num_cards - i - 2 ))

        countTo = ( getRandomValue( 0, (num_cards - i - 1 ))  ) ;

        while( count < countTo )
        {
            
            if( cards[ index ]  < 52 )
            {
                count++;
            }
            index++;
        }

        tempDeck[i] = cards[index];
        cards[index] = NUM_CARDS + 10 ;
    }*/



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

    /*for( i = 0; i < num_cards; i++ )
    { 
        //printf("%d", tempDeck[i]);
        //printf(" ");
        cards[i] = tempDeck[i];
    }*/
    //printf("\n");
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
        if ( ( handValue > WIN_AMOUNT) && (aceCheck == 11) )
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
///home/jps6562/Assignment1/assign1/assign1-cmpsc311-f20.c
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
    //a
    printf("\n---- New hand -----\n");
    shuffle_cards( deck, num_cards);

    //b
    //deal first two cards
    int playerHand[NUM_CARDS], dealerHand[NUM_CARDS];
    playerHand[0] = deck[0];
    dealerHand[0] = deck[1];
    playerHand[1] = deck[2];
    dealerHand[1] = deck[3];
    int pCardNum = 2, dCardNum = 2, deckNum = 4;;

    printf( "Dealer cards : ");
    print_card( dealerHand[0] ); 
    printf( "  XX \n" );

    printf( "Player Cards : ");
    print_cards( playerHand, pCardNum );  
    printf("\n");

    //c
    //d
    if( hand_value( playerHand, pCardNum ) == 21 )
    {
        printf( "Player has Blackjack!, wins $7.50 \n" );
        *player_money = *player_money + (float)7.5; 
        return 1;
    }

    //e
    int count = 0;
    do
    {
        if( player_play( playerHand, pCardNum, dealerHand[0] ) == 1) 
        {
            playerHand[ count + pCardNum ] = deck[deckNum];
            pCardNum++;
            deckNum++;
            printf( "Player Hit (" );
            printf( "%d", hand_value(playerHand, pCardNum) );
            printf( ") : ");
            print_cards( playerHand, pCardNum ); 
        }
        else if ( player_play( playerHand, pCardNum, dealerHand[0] ) == 0 )
        {
            printf( "Player Stays (" );
            printf( "%d", hand_value(playerHand, pCardNum) );
            printf( ") : ");
            print_cards( playerHand, pCardNum ); 
            break;
        }
        
        
    }while ( hand_value(playerHand, pCardNum) < 21);

    if (hand_value(playerHand, pCardNum) > 21)
    {
        printf("Player BUSTS ... dealer wins!\n\n");
        *player_money -=5;
    }

    //f
    //g
    count = 0;
    do
    {
        if( dealer_play(dealerHand, dCardNum ) == 1) 
        {
            dealerHand[ count + dCardNum ] = deck[deckNum];
            dCardNum++;
            deckNum++;
            printf( "Dealer Hit (" );
            printf( "%d", hand_value(dealerHand, dCardNum) );
            printf( ") : ");
            print_cards( dealerHand, dCardNum ); 
        }
        else if ( dealer_play( dealerHand, dCardNum ) == 0)
        {
            printf( "Dealer Stay (" );
            printf( "%d", hand_value(dealerHand, dCardNum) );
            printf( ") : ");
            print_cards( dealerHand, dCardNum ); 
            break;
        }
        
        
    }while ( hand_value(dealerHand, dCardNum) < 21);

    if (hand_value(dealerHand, dCardNum) > 21)
    {
        printf("Dealer BUSTS ... player wins!\n\n");
        *player_money += 5;
    }

    //h
    if( hand_value(playerHand, pCardNum) > hand_value(dealerHand, dCardNum))
    {
        *player_money += 5;
        printf( "Player Wins!\n");
        return 1;
    }
    else
    {
        *player_money -= 5; 
        printf( "Dealer Wins!\n");
        return 0;
    }

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
    int i, j;

    printf("                                                PLAYER CASH BY ROUND\n");
    printf("     -----------------------------------------------------------------------------------------------------"); 
    printf("\n");
    for ( i = 0; i < 40; i++)
    {
        printf("%5d", (200 - 5*i) );
        printf(" |");
        for( j = 0; j < 101; j++)
        {
            if( money_rounds[j] >= (200 - 5*i) )
            {
                printf("X");
            }
            else
            {
                printf(".");
            }
        }
        printf("|\n");
    }
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
    getRandomValue(0,0);
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

            /*printf("Made it here\n");
        for(i = 0; i < NUM_CARDS; i++)
        {
            printf("%d",cmp311_deck[i]); 
            printf(" ");
        }
        printf("\n");*/
    print_cards( cmp311_deck, NUM_CARDS );
    /* Step #6 - sort the cards */
    sort_cards( cmp311_deck, NUM_CARDS );
    /* Step #7 - print the sorted deck of cards */
    print_cards( cmp311_deck, NUM_CARDS );
    /* Step #9 - deal the hands */
        float player_money = 100; 
    float money_rounds[100];
    int count = 0, winTracker = 0;
    do
    {
        winTracker += play_hand(cmp311_deck, NUM_CARDS, &player_money);
        money_rounds[count] = player_money; 
        printf("After hand ");
        printf("%d", count + 1 );
        printf(" player has ");
        printf("%.2f", player_money);
        printf("$ left.\n");
        count++;
    }while( player_money >= 5 && count < 100 );
    /* Step 10 show historgrapm */

    printf("Blackjack done - player won ");
    printf("%d", winTracker);
    printf(" out of ");
    printf("%d", (count + 1) );
    printf(" hands.\n");

    show_player_money_histogram( money_rounds, (count + 1) );
    printf("\n          1         2         3         4         5         6         7         8         9         10\n");
    
    /* Exit the program successfully */

    


    printf( "\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n" );
    return( 0 );
}