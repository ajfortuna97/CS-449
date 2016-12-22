// Assignment 1
# include <stdio.h>
# include <stdlib.h>
# include <time.h>


int ace(){return 11;} // returns 11 at first, will have a check later if busting to recalculate with a 1
int two(){return 2;}
int three(){return 2;}
int four(){return 4;}
int five(){return 5;}
int six(){return 6;}
int seven(){return 7;}
int eight(){return 8;}
int nine(){return 9;}
int ten(){return 10;}
int jack(){return 10;}
int queen(){return 10;}
int king(){return 10;}
int (*f[13])() = {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};



void main()
{
	char* cards[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	//printf("%s", cards[0]);
	// first, let's seed the random number generator
	srand(time(NULL));
	
	int dealerBust = 0;
	int dealerSum = 0;	
	int i;
	int cardValue = 0;
	int (*cardCheck)() = NULL;
	for(i = 0; i < 13; i++)
	{
		cardCheck = f[i];
		cardValue = (*cardCheck)();
		//printf("Your card's value is: %d\n", cardValue);
	}
	
	// now, because we can assume that there is an infinite deck of cards
	// the true maximum card hand is 21 cards
	// so, we'll create a player hand and a dealer hand of 21 cards
	int playerHand[21] = {};
	int dealerHand[21] = {};
	
	// so we can access everything from here, we'll make the dealer hand simply take the values of the number gen
	
	// now, let's deal out the first four cards
	int dealtCard = 0;
	dealtCard = rand() % (0 - 12 + 1) + 0;
	playerHand[0] = dealtCard;
	dealtCard = rand() % (0 - 12 + 1) + 0;
	playerHand[1] = dealtCard;
	
	int playerCardCount = 2;
	
	
	dealtCard = rand() % (0 - 12 + 1) + 0;
	dealerHand[0] = dealtCard;
	dealtCard = rand() % (0 - 12 + 1) + 0;
	dealerHand[1] = dealtCard;
	
	int dealerCardCount = 2;
	
	//cardCheck = f[dealtCard];
	//playerHand[0] = (*cardCheck)();
	
	//dealtCard = rand() % (0 - 12 + 1) + 0;
		
	//cardCheck = f[dealtCard];
	//playerHand[1] = (*cardCheck)();
	
	cardCheck = f[dealerHand[0]];
	int dealerRevealed = 0;
	dealerRevealed = (*cardCheck)();
	
	printf("The Dealer's Hand is: \n");
	//printf("? + %s\n", cards[dealerHand[0]]);
	printf("? + %d\n", dealerRevealed);
	printf(" \n");
	
	int playerSum = 0;
	i = 0;
	
	//printf("Your cards are:\n");
	
	for (i = 0; i < playerCardCount; i++)
	{
		//printf("%s ", cards[playerHand[i]]);
		cardCheck = f[playerHand[i]];
		playerSum = playerSum + (*cardCheck)();
	}
	printf(" \n");
	printf("Your hand value is: %d + %d = %d\n", (*f[playerHand[0]])(), (*f[playerHand[1]])(), playerSum);
	
	int playerTurn = 0;
	int playerBust = 0;
	
	while(!playerTurn)
	{
	printf("Would you like to hit or stay? ");
	char* response[5];
	scanf("%s", &response);
	//printf("Your response is: %s\n", response);
	if(strcmp(response, "hit") == 0)
	{
		//printf("You've chosen to hit.\n");
		//playerTurn = 1;
		
		// add another card
		dealtCard = rand() % (0 - 12 + 1) + 0;
		playerHand[playerCardCount] = dealtCard; // starts off at 2 and goes up
		//playerCardCount++;
		// now we check if you busted
		cardCheck = f[playerHand[playerCardCount]];
		playerSum = playerSum + (*cardCheck)();
		playerCardCount++;
		
		if(playerSum > 21)
		{
			// first, let's check if you have an ace!
			int haveAce = 0;
			for(i = 0; i < playerCardCount; i++)
			{
				if(playerHand[i] == 0)
				{
					haveAce = 1;
				}
			}
			
			
			
			if(haveAce)
			{
				// switching an Ace from 11 to 1 is essentially subtracting 10
				//printf("Your cards are:\n");
				for (i = 0; i < playerCardCount; i++)
					{
					//	printf("%s ", cards[playerHand[i]]);
						cardCheck = f[playerHand[i]];
						//playerSum = playerSum + (*cardCheck)();
					}
				playerSum = playerSum - 10;
				printf("Your hand value is: %d\n", playerSum);
			}
			else
			{
			//printf("Your cards are:\n");
			for (i = 0; i < playerCardCount; i++)
				{
				//	printf("%s ", cards[playerHand[i]]);
				}
			printf(" \n");
			printf("Your hand value is: %d\n", playerSum);
			printf("You busted!\n");
			playerTurn = 1;
			playerBust = 1;
			}
		}
		else
		{
			//printf("Your cards are:\n");
			for (i = 0; i < playerCardCount; i++)
			{
				//printf("%s ", cards[playerHand[i]]);
				cardCheck = f[playerHand[i]];
				//playerSum = playerSum + (*cardCheck)();
			}
			printf(" \n");
			printf("Your hand value is: %d\n", playerSum);
		}
		
	}
	else if (strcmp(response, "stay") == 0)
	{
		//printf("You've chosen to stay.\n");
		playerTurn = 1;
	}
	else
	{
		printf("Error. Please put in a valid choice.\n");
	}
	
	}
	
	// now it's the dealer's turn
	// if the dealer is below 17, he must go
	// if at 17 or higher, stay
	
	if(playerBust == 0)
	{
	
	printf("Dealer's turn.\n");
	//printf("The Dealer's hand is: ");
	//int dealerSum = 0;
	//int dealerBust = 0;
	for (i = 0; i < dealerCardCount; i++)
		{
			//printf("%s ", cards[dealerHand[i]]);
			cardCheck = f[dealerHand[i]];
			dealerSum = dealerSum + (*cardCheck)();
			//printf("%d", dealerSum);
		}
	printf(" \n");
	printf("The Dealer's hand value is: %d + %d = %d\n", (*f[dealerHand[0]])(), (*f[dealerHand[1]])(), dealerSum);
	
	while(dealerSum < 17)
	{
		dealtCard = rand() % (0 - 12 + 1) + 0;
		dealerHand[dealerCardCount] = dealtCard; // starts off at 2 and goes up
		//dealerCardCount++;
		// now we check if you busted
		cardCheck = f[dealerHand[dealerCardCount]];
		dealerSum = dealerSum + (*cardCheck)();
		dealerCardCount++;
		
		if(dealerSum > 21)
		{
			// first, let's check if you have an ace!
			int haveAce = 0;
			for(i = 0; i < dealerCardCount; i++)
			{
				if(dealerHand[i] == 0)
				{
					haveAce = 1;
				}
			}
					
					
					
			if(haveAce)
			{
				// switching an Ace from 11 to 1 is essentially subtracting 10
				//printf("The Dealer's cards are:\n");
				for (i = 0; i < dealerCardCount; i++)
					{
						//printf("%s ", cards[dealerHand[i]]);
						cardCheck = f[dealerHand[i]];
						//dealerSum = dealerSum + (*cardCheck)();
					}
				dealerSum = dealerSum - 10;
				printf("The Dealer's hand value is: %d\n", dealerSum);
			}
			else
			{
			//printf("Dealer Draws.");
			//printf("The Dealer's cards are:\n");
			//for (i = 0; i < dealerCardCount; i++)
			//	{
			//		printf("%s ", cards[dealerHand[i]]);
			//	}
			//printf(" \n");
			printf("The Dealer's hand value is now: %d\n", dealerSum);
			printf("Dealer Busts!\n");
			//dealerTurn = 1;
			dealerBust = 1;
			}
		}
		else
		{
			printf("Dealer Draws.");
			//printf("The Dealer's cards are:\n");
			for (i = 0; i < dealerCardCount; i++)
			{
				//printf("%s ", cards[dealerHand[i]]);
				cardCheck = f[dealerHand[i]];
				//dealerSum = dealerSum + (*cardCheck)();
			}
			printf(" \n");
			printf("The Dealer's hand value is now: %d\n", dealerSum);
		}
	}
	}
	
	
	// now we compare everything!
	// first, let's check for busts.
	
	//int dealerBust = 0;
	if(playerBust)
	{
		if(dealerBust)
		{
			printf("Both busted. Tie.\n");
		}
		else
			printf("You lost...\n"); // you busted, dealer did not
	}
	else if(dealerBust)
	{
		// this means player did NOT bust
		printf("Dealer busts! You win!\n");
	} // now we do the regular comparasions
	else if(playerSum > dealerSum)
	{
		printf("You win!\n");
	}
	else if(playerSum < dealerSum)
	{
		printf("You lose...\n");
	}
	else
	{
		printf("Tie game!\n");
	}
	
	
}