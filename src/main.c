#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

void help(void);
void listContents(const char *path, int showHidden);

int main(int argc, char **argv)
{
    int showHidden = 0;
    const char *lstPath = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcasecmp(argv[i], "--help") == 0 || strcasecmp(argv[i], "-h") == 0)
        {
            help();
            return EXIT_SUCCESS;
        }

        if (argv[i][0] == '-')
        {
            for (int j = 1; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == 'a')
                {
                    showHidden = 1;
                }
                else
                {
                    fprintf(stderr, "lst: invalid option -- '%c'\n", argv[i][j]);
                    fprintf(stderr, "Try './lst --help' for more information.\n");
                    return EXIT_FAILURE;
                }
            }
        }

        else
        {
            if (lstPath == NULL)
            {
                lstPath = argv[i];
            }
        }
    }

    if (lstPath == NULL)
    {
        lstPath = ".";
    }

    listContents(lstPath, showHidden);

    return EXIT_SUCCESS;
}

void help(void)
{
    printf("Usage: lst [FLAGS] [DIRECTORY]\n");
    printf("Flags:\n");
    printf("  -a            Do not ignore entries starting with .\n");
    printf("  -h, --help    Display this help menu\n");
}

void listContents(const char *path, int showHidden)
{
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        perror("lst");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (!showHidden && entry->d_name[0] == '.')
        {
            continue;
        }

        printf("%s  ", entry->d_name);
    }

    printf("\n");

    closedir(dir);
}

