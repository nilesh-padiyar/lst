#define _DEFAULT_SOURCE
#define MAX_PATH_LEN 1024

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void help(void);
void listContents(const char *path, int showHidden, int fileStats);

int main(int argc, char **argv)
{
    int fileStats = 0;
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
                else if (argv[i][j] == 'l')
                {
                    fileStats = 1;
                }
                else
                {
                    fprintf(stderr, "lst: invalid option -- '%c'\n", argv[i][j]);
                    fprintf(stderr, "Try 'lst --help' for more information.\n");
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

    listContents(lstPath, showHidden, fileStats);

    return EXIT_SUCCESS;
}

void help(void)
{
    printf("Usage: lst [FLAGS] [DIRECTORY]\n");
    printf("Flags:\n");
    printf("  -a            Don't ignore hidden entries\n");
    printf("  -l            Show long listing format\n");
    printf("  -h, --help    Display this help menu\n");
}

void listContents(const char *path, int showHidden, int fileStats)
{
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        printf("lst: can't access '%s': %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct stat st;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (!showHidden && entry->d_name[0] == '.')
        {
            continue;
        }

        char fullPath[MAX_PATH_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (fileStats)
        {
            if (stat(fullPath, &st) != -1)
            {
                printf("%s - %ld bytes\n", entry->d_name, st.st_size);
            }
            else
            {
                printf("lst: can't access '%s': %s\n", fullPath, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("%s  ", entry->d_name);
        }
    }

    printf("\n");

    closedir(dir);
}
