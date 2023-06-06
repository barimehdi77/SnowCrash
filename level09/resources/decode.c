i#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int ac, char** av)
{

        FILE *in_file  = fopen(av[1], "r");

        char string[100];

        fgets(string, 100, in_file);
	int i = 0;
        while(string[i]) {
                string[i] = string[i] - i;
		i++;
        }

        printf("%s\n", string);
}
