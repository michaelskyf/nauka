/*
    This file is part of This program.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program. If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	union {
		struct{char *x, *y, *z, *pl;};
		char *v[4];
	};
} record_t;

record_t *array = NULL;
size_t asize = 0;

int score = 0;
int words = 0;

void push_record(char *x, char *y, char *z, char *pl);
void init_array(void);
int random_word(void);

int main(void)
{
	array = malloc(0);
	srand(time(NULL));

	init_array();

	while(!random_word())
	{

	}

	for(int i = 0; i < asize; i++)
	{
		free(array[i].x);
		free(array[i].y);
		free(array[i].z);
		free(array[i].pl);
	}
	free(array);

	return 0;
}

int random_word(void)
{
	size_t index = random() % asize;
	short word = 3;//random() % 4;
	char *w = NULL;
	char buffer[1024];
	int failed = 0;

	_Bool set = 0;

	for(int i = 0; i < 4; i++)
	{
		if(!set)
			i = word;
		else if(i == word)
			continue;

		w = array[index].v[i];
start:
		switch(i)
		{
			case 0:
				printf("Pierwsze: ");
			break;

			case 1:
				printf("Drugie: ");
			break;

			case 2:
				printf("Trzecie: ");
			break;

			case 3:
				printf("Po polsku: ");
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
			if(!strcasecmp("STOP", buffer))
				return -1;
			if(!strcasecmp("HELP", buffer))
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

	return 0;
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
		for(int i = 0; i < sizeof(buffer); i++)
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
