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
static int buildPath(char *buffer,
                     size_t size,
                     const char *path,
                     const char *name);
static int isHidden(const struct dirent *entry);
static void printLongEntry(const char *fullPath, const struct dirent *entry);
static void printPermissions(mode_t mode);

int main(int argc, char **argv)
{
    int showHidden = 0;
    int longFormat = 0;
    const char *lstPath = ".";

    for (int i = 1; i < argc; i++)
    {
        if (strcasecmp(argv[i], "--help") == 0 ||
            strcasecmp(argv[i], "-h") == 0)
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
                    fprintf(stderr,
                            "lst: invalid option -- '%c'\n",
                            argv[i][j]);
                    fprintf(stderr,
                            "Try 'lst --help' for more information.\n");
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

static int buildPath(char *buffer,
                     size_t size,
                     const char *path,
                     const char *name)
{
    int written = snprintf(buffer, size, "%s/%s", path, name);

    return written >= 0 && (size_t)written < size;
}

static void printLongEntry(const char *fullPath, const struct dirent *entry)
{
    struct stat st;

    if (stat(fullPath, &st) == -1)
    {
        fprintf(stderr,
                "lst: can't access '%s': %s\n",
                fullPath,
                strerror(errno));
        return;
    }

    /* File type */
    if (S_ISREG(st.st_mode))
    {
        putchar('-');
    }
    else if (S_ISDIR(st.st_mode))
    {
        putchar('d');
    }
    else if (S_ISLNK(st.st_mode))
    {
        putchar('l');
    }
    else if (S_ISCHR(st.st_mode))
    {
        putchar('c');
    }
    else if (S_ISBLK(st.st_mode))
    {
        putchar('b');
    }
    else if (S_ISFIFO(st.st_mode))
    {
        putchar('p');
    }
    else if (S_ISSOCK(st.st_mode))
    {
        putchar('s');
    }
    else
    {
        putchar('?');
    }

    /* Permissions */
    printPermissions(st.st_mode);

    /* File size and name */
    printf(" %8ld %s\n", (long)st.st_size, entry->d_name);
}

static void printPermissions(mode_t mode)
{
    /* Owner */
    putchar(mode & S_IRUSR ? 'r' : '-');
    putchar(mode & S_IWUSR ? 'w' : '-');
    putchar(mode & S_IXUSR ? 'x' : '-');

    /* Group */
    putchar(mode & S_IRGRP ? 'r' : '-');
    putchar(mode & S_IWGRP ? 'w' : '-');
    putchar(mode & S_IXGRP ? 'x' : '-');

    /* Others */
    putchar(mode & S_IROTH ? 'r' : '-');
    putchar(mode & S_IWOTH ? 'w' : '-');
    putchar(mode & S_IXOTH ? 'x' : '-');
}

static void listContents(const char *path, int showHidden, int longFormat)
{
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        fprintf(stderr,
                "lst: can't access '%s': %s\n",
                path,
                strerror(errno));
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

            if (!buildPath(fullPath,
                           sizeof(fullPath),
                           path,
                           entry->d_name))
            {
                fprintf(stderr,
                        "lst: path too long: '%s/%s'\n",
                        path,
                        entry->d_name);
                continue;
            }

            printLongEntry(fullPath, entry);
        }
        else
        {
            printf("%s  ", entry->d_name);
        }
    }

    if (!longFormat)
    {
        putchar('\n');
    }

    closedir(dir);
}
