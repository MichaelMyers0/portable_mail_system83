#include "search.h"

static open_dir(dirp, name);
static close_dir(dirp);
static path_concat(dest, src1, src2);

static open_dir(dirp, name)
DIR** dirp;
const char* name;
{
	errno = 0;
	*dirp = opendir(name);
	if (!*dirp)
	{
		perror("open_dir()\n");
		exit(1);
	}
}

static close_dir(dirp)
DIR* dirp;
{
	int res;
	errno = 0;
	res = closedir(dirp);
	if (res == -1)
	{
		perror("close_dir()\n");
		exit(2);
	}	
}

static path_concat(dest, src1, src2)
char* dest;
const char* src1;
const char* src2;
{
	size_t len;
	strcpy(dest, src1);
        strcat(dest, back_slash);
        strcat(dest, src2);
        len = strlen(dest);
        *(dest + len) = 0;
}

search(name, path, s)
const char* name;
char* path;
struct stack* s;
{
	DIR* dirp;
	struct dirent* ent;
	size_t len;
	array_pointer ap;
	open_dir(&dirp, *top(s));
	while ((ent = readdir(dirp)))
	{
		if (0 == strcmp(ent->d_name, ".") || 0 == strcmp(ent->d_name, ".."))
			continue;
		if (ent->d_type == DT_DIR && 0 == strcmp(ent->d_name, name))
		{
			ap = top(s);
			path_concat(path, *ap, ent->d_name);
			break;
		}
	}
	close_dir(dirp);
}
