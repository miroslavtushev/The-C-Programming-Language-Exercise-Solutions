// Exercise 8-5. Modify the fsize program to print the other information
// contained in the inode entry.

#include <stdio.h>
#include <sys/stat.h>
#include <sys/dirent.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 1024

void fsize(char *);
void dirwalk(char *dir, void (*fcn)(char *));

int main(int argc, char **argv)
{
    if (argc == 1)
		 fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
    return 0;
}

void fsize(char *name)
{
	struct stat stbuf;
	
	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if (S_ISDIR(stbuf.st_mode))
		dirwalk(name, fsize);
	time_t t = stbuf.st_mtime;
	time_t t1 = stbuf.st_atime;
	printf("%s\n", name);
	printf("Last modified: %s", asctime(gmtime(&t)));
	printf("Last accessed: %s", asctime(gmtime(&t1)));
	printf("Size: %lld\n", stbuf.st_size);
	printf("Flags: %d\n", stbuf.st_flags);
	printf("Blocks alloc: %lld\n", stbuf.st_blocks);
}

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;
	
	if ((dfd = opendir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s%s too long\n", dir, dp->d_name);
		else
		{
			sprintf(name, "%s%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
