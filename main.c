#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char *x;
	char *y;
	char *z;
	char *pl;
} record_t;

record_t *array = NULL;
size_t asize = 0;

int score = 0;
int words = 0;

void push_record(char *x, char *y, char *z, char *pl);
void init_array(void);
void random_word(void);

int main(void)
{
	array = malloc(0);
	srand(time(NULL));

	init_array();

	while(1)
		random_word();

	return 0;
}

void random_word(void)
{
	size_t index = random() % asize;
	short word = random() % 4;
	char *w;
	char buffer[1024];
	int failed = 0;

	_Bool set = 0;

	for(int i = 0; i < 4; i++)
	{
		if(!set)
			i = word;
		else if(i == word)
			continue;
start:
		switch(i)
		{
			case 0:
				printf("Pierwsze: ");
				w = array[index].x;
			break;

			case 1:
				printf("Drugie: ");
				w = array[index].y;
			break;

			case 2:
				printf("Trzecie: ");
				w = array[index].z;
			break;

			case 3:
				printf("Po polsku: ");
				w = array[index].pl;
			break;
		}
		if(i == word)
		{
			printf("%s\n", w);
			set = 1;
			i = -1;
			continue;
		}

		fgets(buffer, sizeof(buffer), stdin);
		buffer[strlen(buffer)-1] = '\0';

		if(strcmp(w, buffer))
		{
			if(!strcmp("STOP", buffer))
				return;
			if(!strcmp("HELP", buffer))
			{
				printf("%s %s %s %s\n", array[index].x, array[index].y, array[index].z, array[index].pl);
				failed = 1;
				goto start;
			}

			printf("Źle!\n");
			failed = 1;
			goto start;
		}
	}
	printf("Dobrze!\n");
	if(!failed)
		score++;
	words++;

	printf("Wynik: %d/%d (%d%%)\n\n", score, words, (score * 100)/words);
}

void init_array(void)
{
	FILE *fp = fopen("niemiecki2.txt", "r");

	if(!fp)
	{
		printf("Failed to open file\n");
		return;
	}

	char buffer[1024];
	char x[128];
	char y[128];
	char z[128];
	char pl[128];

	while(fgets(buffer, sizeof(buffer), fp))
	{
		char *h = x;
		int offset = 0;
		for(int i = 0; i < 1024; i++)
		{
			while(i < sizeof(buffer) && ((h != pl && buffer[i] != ' ') || h == pl) && buffer[i] != '\0' && buffer[i] != '\n')
			{
				h[offset++] = buffer[i++];
			}

			h[offset] = '\0';

			if(h == x)
			{
				h = y;
			} else if(h == y)
			{
				h = z;
			} else if(h == z)
			{
				h = pl;
			} else
			{
				break;
			}
			offset = 0;
		}

		push_record(x, y, z, pl);
	}

	fclose(fp);
}

void push_record(char *x, char *y, char *z, char *pl)
{
	array = realloc(array, ++asize * sizeof(record_t));

	char *newx = malloc(strlen(x)+1);
	char *newy = malloc(strlen(y)+1);
	char *newz = malloc(strlen(z)+1);
	char *newpl = malloc(strlen(pl)+1);

	strcpy(newx, x);
	strcpy(newy, y);
	strcpy(newz, z);
	strcpy(newpl, pl);

	array[asize-1].x = newx;
	array[asize-1].y = newy;
	array[asize-1].z = newz;
	array[asize-1].pl = newpl;
}
