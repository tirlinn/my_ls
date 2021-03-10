
typedef struct directory
{
    char* name;
    int type;               // 1 - directory, 0 - file
    long long int time;
} tdirectory;

typedef struct keep
{
    int size;
    tdirectory* file;
} tkeep;

int my_strlen(char *p1)
{
    int i = 0;
    while ( (p1[i++]) );
    return --i;
}

void my_strcpy (char *p1, char *p2)
{
    char* out = p1;
    while( (*out++ = *p2++) );
}

void my_strcat (char *p1, char *p2)
{
    char *out = p1 + my_strlen(p1);
    while( (*out++ = *p2++) );
}

int my_strcmp(char *p1, char *p2)
{
    int i = 0;
    while ( (p1[i]) && p1[i] == p2[i] )
        i++;
    return p1[i] - p2[i];
}

void swap(tdirectory *p1, tdirectory *p2)
{
    tdirectory temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int isDir(int p1)
{
    if( p1 / 16384 == 1)
    {
        return 1;
    }
    return 0;
}

int compareLex(tdirectory *p1, tdirectory *p2)
{
    for (int i = 0; p1->name[i] ; i++)
        if (p1->name[i] > p2->name[i])
            return 1;
    return 0;
}

void sortLex(tkeep *p1)
{
    for (int j = 0; j < p1->size - 1; j++)
    {
        int min = j;

        for (int i = j + 1; i < p1->size; i++)
        {
            if ( my_strcmp(p1->file[min].name, p1->file[i].name) > 0 )
            {
                min = i;
            }
        }
        swap (&p1->file[min], &p1->file[j]);
    }
}

void sortTime(tkeep *p1)
{
    for (int i = 0; i < p1->size - 1; i++)
    {
        int latest = i;
        
        for (int j = i + 1; j < p1->size; j++)
        {
            if ( p1->file[latest].time == p1->file[j].time )
            {
                if ( my_strcmp(p1->file[latest].name, p1->file[j].name) > 0)
                {
                    latest = j;
                }
            }
            else if (p1->file[latest].time < p1->file[j].time)
            {
                latest = j;
            }
        }
        swap (&p1->file[latest], &p1->file[i]);
    }
}
