#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void help(void);

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Enter \"list --help\" or \"list -h\" for help.\n");
    }

    if (argv[1] == NULL)
    {
        printf("Enter \"list --help\" or \"list -h\" for help.\n");
        exit(EXIT_FAILURE);
    }

    // printf("argc: %d\n", argc);
    // printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
    
    if (strcasecmp(argv[1], "--help") == 0 || strcasecmp(argv[1], "-h") == 0)
    {
        help();
    }

    return 0;
}

void help(void)
{
    printf("Usage: list <flags>\n");
    printf("Coming Soon...\n");
}

