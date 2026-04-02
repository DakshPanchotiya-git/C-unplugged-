#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"song.h"
#include"album.h"

extern int SONG_ID;
static int ALBUM_ID = 1;


album* find_album(album* head, int id)
{
    for(album* temp = head;temp != NULL;temp = temp->next)
    {
        if(temp->id == id)
        {
            return temp;
        }
    }
    return NULL;
}

album* find_album_by_name(album* head, const char* name)
{
    for(album* temp = head; temp != NULL; temp = temp->next)
    {
        if(strcmp(temp->Name, name) == 0)
        {
            return temp;
        }
    }
    return NULL;
}

album* creat_album(const char* al_name,album** head)
{
    if(find_album_by_name(*head, al_name) != NULL)
    {
        printf("album '%s' already exists \n try to create with another name or access that album\n", al_name);
        return NULL;
    }
    album* new = malloc(sizeof(album));
    if (new == NULL) 
    {
        printf("Error: Memory allocation failed for album!\n");
        return NULL;
    }
    new->id = ALBUM_ID++;
    strcpy(new->Name,al_name);
    new->next = NULL;
    new->song_head = NULL;
    if(*head == NULL)
    {
        *head = new;
    }
    else if(1)
    {
        album* temp;
        for(temp = *head;temp->next != NULL ;temp = temp->next)
        {
            //
        }
        temp->next = new;
    }

    printf("album '%s' is ceated successfully\n", al_name);
    return new;
}

void add_song_to_album(song* new_song, album* head, int album_id)
{
    album* album = find_album(head,album_id);
    if(album == NULL)
    {
        printf("album whose id is '%d' not found!\n", album_id);
        return;
    }
    for (song* temp = album->song_head; temp != NULL; temp = temp->next)
    {
        if (temp->id == new_song->id)
        {
            printf("Error: Song '%s' already exists in album whose id is'%d'.\n", new_song->name, album_id);
            return;
        }
    }
        song* newtemp = malloc(1*sizeof(song));
        if (newtemp == NULL) 
        {
            printf("Error: Memory allocation failed for song!\n");
            return;
        }

        *newtemp = *new_song; 
        newtemp->next = NULL;

        if(album->song_head == NULL)
        {
            album->song_head = newtemp;
        }
        else if(album->song_head != NULL)
        {
            song* temp = album->song_head;

            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newtemp;
        }
        printf("new song '%s' was added to album whose id is'%d'\n", new_song->name,album_id);
}


void save_album(album* head,const char* filename)
{
    FILE* fl = fopen(filename,"w");
    if(!fl)
    {
        printf("file '%s' not found!\n", filename);
        return;
    }
    for(album* temp = head;temp!=NULL;temp = temp->next)
    {

        for(song* subtemp = temp->song_head;subtemp != NULL;subtemp = subtemp->next)
        {
            fprintf(fl,"%s %s %f %s %d\n", subtemp->name,subtemp->artist,subtemp->duration,temp->Name,temp->id);
        }
        fprintf(fl,"\n");
    }
    fclose(fl);
    printf("albums saved in '%s' \n", filename);
}

void load_album(const char* filename,album** head)
{
    FILE* fp = fopen(filename,"r");
    if(fp ==  NULL)
    {
        printf("entered file '%s' does not exists!\n", filename);
        return;
    }

    char check_line[500];
    album* currant_temp;

    while(fgets(check_line,sizeof(check_line),fp))
    {
        if(check_line[0] == '\n')
        {
            continue;
        }

        char song_name[300];
        char artist_name[50];
        float duration;
        char album_name[100];
        int id;
        sscanf(check_line,"%199s %49s %f %99s %d", song_name,artist_name,&duration,album_name,&id);

        currant_temp = find_album_by_name(*head,album_name);

        if(currant_temp == NULL)
        {
            //currant_temp = creat_album(album_name,head);
            currant_temp = malloc(sizeof(album)); 
            if(currant_temp == NULL) continue;
            
            strcpy(currant_temp->Name, album_name);
            currant_temp->song_head = NULL;
            currant_temp->next = NULL;

        
            currant_temp->id = id;
            if(*head == NULL) {
                *head = currant_temp;
            } else {
                album* temp = *head;
                while(temp->next != NULL) temp = temp->next;
                temp->next = currant_temp;
            }
            if (id >= ALBUM_ID) {
                ALBUM_ID = id + 1;
            }
        }
        song* new_song = calloc(1,sizeof(song));
        if(!new_song)
        {
            printf("memory allocation failed!\n");
            continue;
        }

        new_song->id = SONG_ID++;

        strcpy(new_song->name,song_name);
        strcpy(new_song->artist,artist_name);
        strcpy(new_song->album,album_name);
        new_song->duration = duration;
        new_song->next = NULL;


        if(currant_temp->song_head == NULL)
        {
            currant_temp->song_head = new_song;
        }
        else if(currant_temp->song_head != NULL)
        {
            song* temp = currant_temp->song_head;
            for( ;temp->next != NULL;temp = temp->next)
            {
                //only need is to iterate through the link list
            }
            temp->next = new_song;
        }
    }
    fclose(fp);
    printf("successfully loaded album\n");
}

void delete_album(int album_id, album** head)
{
    album* temp_currant = *head;
    album* temp_previous = NULL;

    while(temp_currant != NULL)
    {
        if(temp_currant->id == album_id)
        {
            if(temp_previous == NULL)
            {
                *head = temp_currant->next;
            }
            else 
            {
                temp_previous->next = temp_currant->next;
            }

            song* temp;
            for(temp = temp_currant->song_head;temp != NULL; )
            {
                song* tempfree = temp;
                temp = temp->next;
                free(tempfree);
            }

            free(temp_currant);
            printf("album id '%d' is deleted!\n", album_id);
            return;
        }
        temp_previous = temp_currant;
        temp_currant = temp_currant->next;
    }
    printf("album whose id is '%d' not found!\n", album_id);
}

void delete_song_from_album(album* head, const char* s_name, int album_id)
{
    album* temp;
    for(temp = head;temp != NULL;temp = temp->next)
    {
        if(temp->id == album_id)
        {
            song* temp2_currant = temp->song_head;
            song* previous = NULL;
            while(temp2_currant != NULL)
            {
                if(strcmp(s_name,temp2_currant->name) == 0)
                {
                    if(previous == NULL)
                    {
                        temp->song_head = temp2_currant->next;
                    }
                    else if(previous != NULL)
                    {
                        previous->next = temp2_currant->next;
                    }

                    free(temp2_currant);
                    printf("song '%s' deleted successfully!\n", s_name);
                    return;
                }
                previous = temp2_currant;
                temp2_currant = temp2_currant->next;
            }
        }
    }
    printf("song '%s' not found in this album!\n",s_name);
}
