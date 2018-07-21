#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
// new for sockets
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>

#define ERR_NUM -1
#define ERR_MEM -2

typedef struct {
	int value;
	char suit;
}card;


int myRandom(int size) {
	int i, n;
	static int nums = 0;
	static int *numArrs = NULL;

	// Initialize with a specific size.

	if (size >= 0) {
		if (numArrs != NULL)
			free(numArrs);
		if ((numArrs = malloc(sizeof(int) * size)) == NULL)
			return ERR_MEM;
		for (i = 0; i < size; i++)
			numArrs[i] = i;
		nums = size;
	}

	if (nums == 0)
		return ERR_NUM;

	n = rand() % nums;
	i = numArrs[n];
	numArrs[n] = numArrs[nums - 1];
	nums--;
	if (nums == 0) {
		free(numArrs);
		numArrs = 0;
	}
	return i;
}

void deckstart(card* inic, int deck[]);

int main(void) {
	int i;
	int j = 0;
	int deck[52];
	srand(time(NULL));
	i = myRandom(52);
	while (i >= 0) {
		deck[j] = i;
		++j;
		i = myRandom(-1);
	}
	int s0, s1;
	s0 = socket(AF_UNIX, SOCK_STREAM, 0);

	void ctrlc() {
		unlink("server");
		close(s0);
		exit(0);
	}

	struct sigaction news;
	struct sigaction olds;

	news.sa_handler = ctrlc;
	news.sa_flags = 0;

	sigaction(SIGINT, &news, &olds);

	card c[52];
	
	deckstart(c, deck);

	if (s0 == -1)
		return -1;

	struct sockaddr name0 = { AF_UNIX, "server" };
	socklen_t namelen0 = sizeof(struct sockaddr) + 7;

	bind(s0, &name0, namelen0);

	int x = 0;
	do {
		if (listen(s0, 1) == -1)
		{
			printf("listen() fail\n");
		}
		else {

			if ((s1 = accept(s0, NULL, NULL)) != -1) {

				write(s1, c, (sizeof(card) * 52));

				close(s1);

			}

		}
		ctrlc();
	} while (x = 0);
	return 0;
}

void deckstart(card* c, int deck[]) 
{

	char sc[] = { 'D','H','S','C' };

	int cnt = 0;
	while (cnt < 52) {

		int cal;
		cal = deck[cnt];
		int quot;
		int remains;

		quot = cal / 13;
		remains = cal % 13;

		if (quot == 0) {

			c[cnt].suit = sc[0];
		}
		if (quot == 1) {

			c[cnt].suit = sc[1];
		}
		if (quot == 2) {

			c[cnt].suit = sc[2];
		}
		if (quot == 3) {

			c[cnt].suit = sc[3];
		}

		c[cnt].value = remains;

		++cnt;

	}
}

