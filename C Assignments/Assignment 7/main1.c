#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define BSIZE 2048

struct mdata
{
    char name[255];
    FILE *fp;
    int size;
    int nsize;
    int ssize;
    struct mdata *next;
};

struct mdata *mhead = NULL, *current = NULL;

int min(int x, int y)
{
    if(x < y) return x;
    else return y;
}

int getsize(FILE *fp)
{
    int size = 0;
    fseek(fp, 0L, SEEK_END);      
    size  = ftell(fp);
    fseek(fp, 0L, SEEK_SET);   
    return size;
}

int add_create(char *name)
{    
    FILE *fp;
    char ntemp[255];
    struct mdata *newm;
    newm = (struct mdata *)malloc(sizeof(struct mdata));
    strcpy(newm->name, name);    
    fp = fopen(name, "r+");  

    newm->fp = fp;
    newm->size = getsize(fp);  
    newm->nsize = strlen(name);
    sprintf(ntemp, "%d", newm->size);
    newm->ssize = strlen(ntemp);
    newm->next = NULL;
    printf("File %s is being processed...\n", name);
    if(mhead == NULL) 
    {
        mhead = newm;
        current = newm;
    }
    else
    {
        current->next = newm;
        current = newm;
    }
}

int preproc(int argc, char** argv)
{

    DIR *directory;
    struct dirent* file;
    FILE *a;
    char ch;

    directory = opendir(argv[2]);
    if (directory == NULL) {
        printf("Error\n");
        exit(2);
    }

    while ((file=readdir(directory)) != NULL) {
        if(file->d_name[0] == '.')
            continue;
        char dir[250];
        strcpy(dir, argv[2]);
        strcat(dir, "/");
        strcat(dir, file->d_name);
        add_create(dir);
    }

    closedir(directory);
}

int add_extract(char *name, int size)
{    
    char ntemp[255];
    struct mdata *newm;
    newm = (struct mdata *)malloc(sizeof(struct mdata));
    strcpy(newm->name, name);    
    newm->size = size;
    newm->nsize = strlen(name);
    sprintf(ntemp, "%d", newm->size);
    newm->ssize = strlen(ntemp);
    newm->next = NULL;
    printf("File %s is being processed...\n", name);
    if(mhead == NULL) 
    {
        mhead = newm;
        current = newm;
    }
    else
    {
        current->next = newm;
        current = newm;
    }
}

int readh(FILE *fp1)
{
    int i = 0, j= 1 ;    
    int hsize = 0, size = 0;
    int byte;
    char shsize[50]; 
    char name[255];
    char ssize[50];
    while((byte = fgetc(fp1))!='_')
    {
        shsize[i] = (char)byte;
        i++;
    }
    shsize[i] = '\0';
    hsize = atoi(shsize);
    hsize += strlen(shsize);
    printf("The total size of header is %d.\n", hsize);
    printf("Contents starts at %dth byte.\n", hsize);
    //COLLECT NAMES AND SIZES
    j = strlen(shsize)+1;
    while(j <= hsize-1)
    {
        i = 0;
        while((byte = fgetc(fp1))!='_')
        {

            name[i++] = byte;
            j++;
        }
        j++;
        name[i] = '\0';
        i = 0;
        while((byte = fgetc(fp1))!='_')
        {
            ssize[i++] = byte;
            j++;
        }     
        j++;
        ssize[i] = '\0';
        size = atoi(ssize);
        printf("File '%s' with size %d added to list.\n", name, size);
        add_extract(name, size);
        printf("File '%s' processing completed.\n", name);
    }
    printf("File meta data collection successfully completed.\n");
    return hsize;
}

int create(int argc, char** argv){
    printf("Creating archive\n");
    mhead = NULL, current = NULL;

    char block[BSIZE];
    char stsize[5];
    char shsize[100];
    int rsize = 0;
    int tnsize = 0, tssize = 0, hsize = 0, scount = 0;
    struct mdata *ptr;
    FILE *fpar, *fp;

    //CREATE HEADER
    printf("Pre-processing the files to collect meta data...\n");
    preproc(argc, argv);printf("I am here");
    printf("Pre-processing completed.\n");

    printf("Compiling header information.\n");
    fpar = fopen(argv[argc-1], "w+");
    ptr = mhead;
    while(ptr != NULL)
    {
        tnsize += ptr->nsize;        
        tssize += ptr->ssize;
        ptr = ptr->next;
        scount +=2;
    }
    hsize = tnsize+tssize+scount+1; 
    printf("Total length of file names is %d\n", tnsize);
    printf("Total length of file sizes is %d\n", tssize);
    printf("Total size of header except file size is %d.\n", hsize);
    sprintf(shsize, "%d_", hsize); //10 bytes of header size
    fwrite(shsize, 1, strlen(shsize), fpar);
    ptr = mhead;
    while(ptr != NULL)
    {
        fwrite(ptr->name, 1, ptr->nsize, fpar);   
        fwrite("_", 1, 1, fpar);
        sprintf(stsize, "%d", ptr->size);
        fwrite(stsize, 1, ptr->ssize, fpar);  
        fwrite("_", 1, 1, fpar);
        ptr = ptr->next;
    }    
    printf("The header created and written to archieve file.\n");
    //CREATE BODY
    ptr = mhead;
    while(ptr != NULL)
    {
        fp = ptr->fp;
        while(rsize = fread(block, 1, sizeof(block), fp))
        {
            fwrite(block, 1, rsize, fpar);
        }
        ptr = ptr->next;
    }   
    printf("Contents of all files written to archieve file.\n ***** ARCHIVE SUCCESSFULL ***** \n");
    fclose(fpar);  
    return 0;
}

int extract(int argc, char** argv){
    mhead = NULL, current = NULL;
    printf("Extracting archive\n");

    char block[BSIZE];
    char stsize[5];
    char shsize[100];
    int rsize = 0;
    int tnsize = 0, tssize = 0, hsize = 0, scount = 0;
    int totsize = 0;
    int unreadcount = 0;
    struct mdata *ptr;
    FILE *fpar, *fp;

    //COLLECTING HEADER
    printf("Opening file %s...\n", argv[argc-1]);
    fpar = fopen(argv[argc-1], "r+");

    if(fpar == NULL)
    {
        printf("Error opening file %s.\n", argv[argc-1]);
    }

    hsize = readh(fpar);
    ptr = mhead;

    fseek(fpar, hsize, SEEK_SET);

    while(ptr != NULL)
    {
        totsize = ptr->size;
        printf("Creating file %s...\n", ptr->name);

        char dir[250];
        memset (dir, 0, sizeof(dir));
        // strcpy(dir, argv[2]);
        // strcat(dir, "/");
        strcat(dir, ptr->name);

        printf("%s\n", dir);

        fp = fopen(dir, "w+"); 
        printf("Writing %d bytes of %s...\n", ptr->size, ptr->name);
        unreadcount = ptr->size;
        //printf("Number of chars is %d\n", unreadcount);
        while(unreadcount > 0)
        {
            char ch = fgetc (fpar); 
            // printf("%c\n", ch);
            putc (ch , fp);
            unreadcount--;

        }
        printf("Written %d bytes to file %s.\n", totsize, ptr->name);
        ptr = ptr->next;
        fclose(fp); 
    }
    printf("***** ARCHIVE EXTRACTION COMPLETE *****\n");
    fclose(fpar);  
    return 0;
}

int append(int argc, char** argv){
    mhead = NULL, current = NULL;
    printf("Appending Archive\n");
    extract(argc, argv);
    mhead = NULL, current = NULL;
    create(argc, argv);
}

int main(int argc, char** argv){
    if(strcmp(argv[1], "-c") == 0){
        create(argc, argv);
    }
    else if(strcmp(argv[1], "-a") == 0){
        append(argc, argv);
    }
    else if(strcmp(argv[1], "-e") == 0){
        extract(argc, argv);
    }
}

// % ./archive -c . my_archive
// % ./archive -a . my_archive
// % ./archive -e ./explode_test my_archive