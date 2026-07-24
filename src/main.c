#define _DEFAULT_SOURCE()

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

void help(void);
void listContents();

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        listContents();
    }
    else if (
        argc > 3 ||
        strcasecmp(argv[1], "--help") == 0 || 
        strcasecmp(argv[1], "-h") == 0
       )
    {
        help();
        exit(EXIT_SUCCESS);
    }

    return 0;
}

void help(void)
{
    printf("Usage: ./main <flags>\n");
    printf("Coming Soon...\n");
}

void listContents()
{
    DIR *dir = opendir(".");
    
    if (dir == NULL)
    {
        printf("No files or directory found.\n");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    int directory = DT_DIR;
    int file = DT_REG;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == directory)
        {
            printf("%s \t", entry->d_name);
        }

        else if (entry->d_type == file)
        {
            printf("%s \t", entry->d_name);
        }
    }

    printf("\n");

    closedir(dir);
}

