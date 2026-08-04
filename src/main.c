#define _DEFAULT_SOURCE
#define MAX_PATH_LEN 1024

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

static void help(void);
static void listContents(const char *path, int showHidden, int longFormat);
static void buildPath(char *buffer, size_t size, const char *path, const char *name);
static int isHidden(const struct dirent *entry);
static void printLongEntry(const char *fullPath, const struct dirent *entry);

int main(int argc, char **argv)
{
    int showHidden = 0;
    int longFormat = 0;
    const char *lstPath = ".";

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
                switch (argv[i][j])
                {
                case 'a':
                    showHidden = 1;
                    break;

                case 'l':
                    longFormat = 1;
                    break;

                default:
                    fprintf(stderr, "lst: invalid option -- '%c'\n", argv[i][j]);
                    fprintf(stderr, "Try 'lst --help' for more information.\n");
                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
            lstPath = argv[i];
        }
    }

    listContents(lstPath, showHidden, longFormat);

    return EXIT_SUCCESS;
}

static void help(void)
{
    printf("Usage: lst [FLAGS] [DIRECTORY]\n");
    printf("Flags:\n");
    printf("  -a            Don't ignore hidden entries\n");
    printf("  -l            Show long listing format\n");
    printf("  -h, --help    Display this help menu\n");
}

static int isHidden(const struct dirent *entry)
{
    return entry->d_name[0] == '.';
}

static void buildPath(char *buffer, size_t size, const char *path, const char *name)
{
    snprintf(buffer, size, "%s/%s", path, name);
}

static void printLongEntry(const char *fullPath, const struct dirent *entry)
{
    struct stat st;

    if (stat(fullPath, &st) == -1)
    {
        fprintf(stderr, "lst: can't access '%s': %s\n", fullPath, strerror(errno));
        return;
    }

    printf("%s - %ld bytes\n", entry->d_name, st.st_size);
}

static void listContents(const char *path, int showHidden, int longFormat)
{
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        fprintf(stderr, "lst: can't access '%s': %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (!showHidden && isHidden(entry))
        {
            continue;
        }

        if (longFormat)
        {
            char fullPath[MAX_PATH_LEN];

            buildPath(fullPath, sizeof(fullPath), path, entry->d_name);

            printLongEntry(fullPath, entry);
        }
        else
        {
            printf("%s  ", entry->d_name);
        }
    }

    if (!longFormat)
    {
        printf("\n");
    }

    closedir(dir);
}
