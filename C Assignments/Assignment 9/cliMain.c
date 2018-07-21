#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define ERR_NO_NUM -1
#define ERR_NO_MEM -2

typedef struct {
	int value;
	char suit;
}card;

int playIt();
int getBet(int bank);
void report(int nhands, int nwins, int nlosses, int nchip);
void displayHand(card* deck, int ncards);
void swap(int *xp, int *yp);
void sortIt(int arr[], int n);
int fourkind(card* deck, int ncards);
int StraightFlush(card* deck, int ncards);
int isFlush(card* deck, int ncards);
int isStraight(card* deck, int ncards);
int isTrip(card* deck, int ncards);
int is2Pair(card* deck, int ncards);
int isPair(card* deck, int ncards);
int Rando(int size);

void main()
{
	int s0, s1;
	s0 = socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr name0 = { AF_UNIX, "server" };
	socklen_t namelen0 = sizeof(struct sockaddr) + 7;

	if (connect(s0, &name0, namelen0) == -1)
	{
		printf("connect() fail\n");
		exit(1);
	}

	card c[52];

	read(s0, c, (sizeof(card) * 52));

	

	printf("\n\tWelcome to 4 Card Poker");
	printf("   Your initial bank roll is $100.00");

	int bank = 100;
	int nHands = 0;
	int nWins = 0;
	int nLosses = 0;

	const int FOAK = 20825;
	const int SFL = 6153;
	const int TOAK = 108;
	const int STR = 98;
	const int FL = 96;
	const int TP = 96;
	const int OP = 3;

	int exit = 0;

	int ncards = 0;

	do {
		// ask the user if play or not
		if (playIt() == 1) {
			++nHands;

			int bet = getBet(bank);

			//check there are enough cards for the player
			//otherwise the client will ask the server for the 'new' shuffle


			if (nHands == 13) {

				printf("Not many cards left, friend. Do you want to play more?");

				if (playIt() == 1) {


					int i;
					int j = 0;
					card d[52];
					srand(time(NULL));
					i = Rando(52);
					while (i >= 0) {
						d[j] = c[i];
						++j;
						i = Rando(-1);
					}

					ncards = 0;
					memcpy(&c, &d, sizeof(d));
				}

			}

			printf("\nLet the cards fall where they may ...\n");
			displayHand(c, ncards);

			printf("\n");

			if (fourkind(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * FOAK;
				printf("4 of a kind! You've won $ %d.", bet * FOAK);
				printf("\n");
			}
			else if (StraightFlush(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * SFL;
				printf("Straight Flush! You've won $ %d.", bet * SFL);
				printf("\n");
			}

			else if (isTrip(c, ncards) == 1) {
				++nWins;
				ncards += 4;
				bank += bet * TOAK;
				printf("3 of a Kind! You've won $ %d.", bet * TOAK);
				printf("\n");
			}

			else if (isStraight(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * STR;
				printf("Straight! You've won $ %d.", bet * STR);
				printf("\n");
			}
			else if (isFlush(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * FL;
				printf("Flush! You've won $ %d.", bet * FL);
				printf("\n");
			}
			else if (is2Pair(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * TP;
				printf("Two Pair! You've won $ %d.", bet * TP);
				printf("\n");
			}
			else if (isPair(c, ncards) == 1) {
				nWins++;
				ncards += 4;
				bank += bet * OP;
				printf("Pair! You'v won $ %d.", bet * OP);
				printf("\n");
			}
			else // Bubkiss
			{
				nLosses++;
				ncards += 4;
				bank -= bet;
				printf("Nope. You've lost $ %d.", bet);
				printf("\n");

			}
			printf("ncards is %d\n", ncards);
		}
		else if (playIt() == 2) {
			exit = 1;
		}
	} while (bank > 0 && exit != 1 && ncards != 52);
	report(nHands, nWins, nLosses, bank);
	printf("\n");
}

int playIt() {
	char c;
	int x = 0;

	while (x == 0) {
		printf("Play a hand [ y / n ] ? ");
		scanf("%c", &c);
		if (c == 'y') {
			x = 1;
		}
		if (c == 'n') {
			x = 2;
		}
	}
	printf("\n");
	return x;

}

int getBet(int bank) {

	int askBet;

	do {
		printf("Place your bet [1,%d]: ", bank);
		scanf("%d", &askBet);

	} while (!(askBet >= 1 && askBet <= bank));

	printf("\n");
	return askBet;// ask the user to enter the valid bet
}

void report(int nhands, int nwins, int nlosses, int nchip) {

	printf("Thanks for playing ... \n");
	printf("Total Hands Played: %d hands\n", nhands);
	printf("Hands Won: %d\n", nwins);
	printf("Hands Lost: %d\n", nlosses);
	printf("Total Winnings: $ %d\n", (nchip - 100)); // print
}

void displayHand(card* deck, int ncards) {

	int cindex = ncards;
	int i;
	for (i = 0; i < 4; ++i) {

		//display card
		printf("card %d is %d%c\n", i, deck[cindex + i].value, deck[cindex + i].suit);
	}
	printf("\n");
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void sortIt(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++) {

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

int fourkind(card* deck, int ncards) {
	int checkisfok = 0;
	if (deck[ncards + 0].value == deck[ncards + 1].value && deck[ncards + 0].value == deck[ncards + 2].value
		&& deck[ncards + 0].value == deck[ncards + 3].value && deck[ncards + 1].value == deck[ncards + 2].value
		&& deck[ncards + 1].value == deck[ncards + 3].value && deck[ncards + 2].value == deck[ncards + 3].value
		&& deck[ncards + 3].value == deck[ncards + 4].value)
	{
		checkisfok = 1;
	}
	return checkisfok;// compare all Quad cases and return the result of
					  // comparison
}

int StraightFlush(card* deck, int ncards) {
	int checkisStraightFlu = 0;

	if (deck[ncards + 0].suit == deck[ncards + 1].suit
		&& deck[ncards + 0].suit == deck[ncards + 2].suit
		&& deck[ncards + 0].suit == deck[ncards + 3].suit
		&& deck[ncards + 1].suit == deck[ncards + 2].suit
		&& deck[ncards + 1].suit == deck[ncards + 3].suit
		&& deck[ncards + 2].suit == deck[ncards + 3].suit)
	{

		int arr[4];
		arr[0] = deck[ncards + 0].value;
		arr[1] = deck[ncards + 1].value;
		arr[2] = deck[ncards + 2].value;
		arr[3] = deck[ncards + 3].value;

		//sorting in an ascendent order
		sortIt(arr, 4);

		if (arr[0] + 1 == arr[1] && arr[0] + 2 == arr[2] && arr[0] + 3 == arr[3]) {

			checkisStraightFlu = 1;
		}
	}
	return checkisStraightFlu; // if Striaght and Flush
}

int isTrip(card* deck, int ncards) {//3 of a kind
	int checkisTrip = 0;
	if ((deck[ncards + 0].value == deck[ncards + 1].value && deck[ncards + 0].value == deck[ncards + 2].value)
		|| (deck[ncards + 0].value == deck[ncards + 1].value && deck[ncards + 0].value == deck[ncards + 3].value)
		|| (deck[ncards + 1].value == deck[ncards + 2].value && deck[ncards + 1].value == deck[ncards + 3].value)) {
		checkisTrip = 1;
	}
	return checkisTrip; // compare all Trip(3 of a kind) cases and return the result of
						// comparison
}

int isFlush(card* deck, int ncards) {
	int checkisFlush = 0;
	if (deck[ncards + 0].suit == deck[ncards + 1].suit
		&& deck[ncards + 0].suit == deck[ncards + 2].suit
		&& deck[ncards + 0].suit == deck[ncards + 3].suit
		&& deck[ncards + 1].suit == deck[ncards + 2].suit
		&& deck[ncards + 1].suit == deck[ncards + 3].suit
		&& deck[ncards + 2].suit == deck[ncards + 3].suit)
	{

		checkisFlush = 1;
	}
	return checkisFlush; // compare all Flush cases and return the result of
						 // comparison
}

int isStraight(card* deck, int ncards) {
	int checkisStraight = 0;
	int arr[4];
	arr[0] = deck[ncards + 0].value;
	arr[1] = deck[ncards + 1].value;
	arr[2] = deck[ncards + 2].value;
	arr[3] = deck[ncards + 3].value;

	//sorting in an ascendent order
	sortIt(arr, 4);

	if (arr[0] + 1 == arr[1] && arr[0] + 2 == arr[2] && arr[0] + 3 == arr[3]) {

		checkisStraight = 1;
	}
	return checkisStraight; // compare all Striaght cases and return the
							// result of comparison
}

int is2Pair(card* deck, int ncards) {
	int checkis2Pair = 0;
	if ((deck[ncards + 0].value == deck[ncards + 1].value && deck[ncards + 2].value == deck[ncards + 3].value)
		|| (deck[ncards + 0].value == deck[ncards + 2].value && deck[ncards + 1].value == deck[ncards + 3].value)
		|| (deck[ncards + 0].value == deck[ncards + 3].value && deck[ncards + 1].value == deck[ncards + 2].value)) {
		checkis2Pair = 1;
	}
	return checkis2Pair; // compare all 2Pair cases and return the result of
						 // comparison
}

int isPair(card* deck, int ncards) {
	int checkisPair = 0;
	if ((deck[ncards + 0].value == deck[ncards + 1].value) || (deck[ncards + 0].value == deck[ncards + 2].value)
		|| (deck[ncards + 0].value == deck[ncards + 3].value) || (deck[ncards + 1].value == deck[ncards + 2].value)
		|| (deck[ncards + 1].value == deck[ncards + 3].value) || (deck[ncards + 2].value == deck[ncards + 3].value)) {
		checkisPair = 1;
	}
	return checkisPair; // compare all Pair cases and return the result of
						// comparison
}
int Rando(int size) {
	int i, n;
	static int numNums = 0;
	static int *numArr = NULL;

	// Initialize with a specific size.

	if (size >= 0) {
		if (numArr != NULL)
			free(numArr);
		if ((numArr = malloc(sizeof(int) * size)) == NULL)
			return ERR_NO_MEM;
		for (i = 0; i < size; i++)
			numArr[i] = i;
		numNums = size;
	}

	// Error if no numbers left in pool.

	if (numNums == 0)
		return ERR_NO_NUM;
	// Get random number from pool and remove it (rnd in this
	//   case returns a number between 0 and numNums-1 inclusive).

	n = rand() % numNums;
	i = numArr[n];
	numArr[n] = numArr[numNums - 1];
	numNums--;
	if (numNums == 0) {
		free(numArr);
		numArr = 0;
	}

	return i;
}