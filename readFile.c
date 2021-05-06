#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

int main(int argc, char const *argv[])
{
    char *buffer = 0;
    long length;
    FILE *f = fopen("./topo983by450.txt", "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if (buffer)
        {
            fread(buffer, 1, length, f);
            buffer[length] = '\0';
        }
        fclose(f);
    }

    if (buffer)
    {
        int rows = 0;
        int cols = 0;
        int i = 0;
        int k = 0;
        char *line = malloc(sizeof(char *) * strlen(buffer));
        char *buffer_cpy = (char *)malloc(strlen(buffer));
        strcpy(buffer_cpy, buffer);
        char *c_ptr = (char *)buffer_cpy;
        i = 0;
        int n_count = 0;
        int bfcp_len = strlen(buffer_cpy);
        while (i < bfcp_len)
        {
            if (c_ptr[i] == (int)'\n')
            {
                c_ptr[i] = (int)' ';
                n_count++;
            }
            i++;
        }

        int wanted_word = 6;
        k = 0;
        int s_temp = sizeof(char *) * 100;
        char *tmp = (char *)malloc(s_temp);
        memset(tmp, ' ', s_temp);
        int prev_char_was_blank = TRUE;
        int is_curr_char_blank = FALSE;
        for (i = 0; k < wanted_word; i++)
        {
            if (c_ptr[i] == (int)' ')
            {
                is_curr_char_blank = TRUE;
                if (!prev_char_was_blank)
                {
                    k++;
                }
            }
            if (!is_curr_char_blank)
            {
                tmp[i] = c_ptr[i];
                prev_char_was_blank = FALSE;
            }
            else
            {
                if (k == wanted_word)
                {
                    break;
                }
                if (!prev_char_was_blank)
                {
                    memset(tmp, ' ', s_temp);
                }
                prev_char_was_blank = TRUE;
            }
            is_curr_char_blank = FALSE;
        }
        puts(tmp);

        // puts(buffer_cpy);
        // // printf("%i New Line characters replaced!\n",n_count);
        // line = strtok(buffer_cpy, " ");
        // cols = atoi(strtok(NULL, " "));
        // //strtok(NULL," ");
        // rows = atoi(strtok(NULL, " "));
        // i=0;
        // for (; i < 7; i++)
        // {
        //     line = strtok(NULL, " ");
        //     // puts(line);
        // }
        // for ( i = 0; i < rows; i++)
        // {
        //     for ( k = 0; k < cols; k++)
        //     {
        //         line = strtok(NULL, " ");
        //         strcat(line, " ");
        //         puts(line);
        //     }
        //     puts("\n");

        // }

        //getc(stdin);
        // for (i = 0; i < 2; i++)
        // {
        // if (i == 0)
        // {
        // line = strtok(buffer_cpy, " ");
        // };
        // puts(line);
        // line = strtok(NULL, " ");
        // puts(line);
        // line = strtok(NULL, " ");
        // puts(line);
        // line = strtok(NULL, " ");
        // puts(line);
        // line = strtok(NULL, " ");
        // puts(line);
        // }
    }

    return 0;
}
