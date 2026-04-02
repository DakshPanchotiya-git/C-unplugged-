#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"song.h"


                //history functions

void add_to_history(HistoryNode** head, song* song_to_add)
{
    HistoryNode* new_node = (HistoryNode*)malloc(sizeof(HistoryNode));
    if (new_node == NULL) {
        printf("Error: Malloc failed for history node!\n");
        return;
    }
    
    new_node->song_data = song_to_add;
    
    new_node->next = *head;
    
    *head = new_node;
}

void show_history(HistoryNode* head)
{
    printf("\n--- Play History (Most Recent First) ---\n");
    if (head == NULL) {
        printf(" (Play history is empty)\n");
        return;
    }
    
    int i = 1;
    for (HistoryNode* temp = head; temp != NULL; temp = temp->next)
    {
        printf("%d. %s (%s)\n", i, temp->song_data->name, temp->song_data->artist);
        i++;
    }
}

void clear_history(HistoryNode** head)
{
    HistoryNode* current = *head;
    while (current != NULL)
    {
        HistoryNode* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void save_history(HistoryNode* head, const char* filename)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open history file '%s' for writing.\n", filename);
        return;
    }
    for (HistoryNode* temp = head; temp != NULL; temp = temp->next)
    {
        fprintf(fp, "%s\n", temp->song_data->name);
    }

    fclose(fp);
}

void load_history(HistoryNode** head, const char* filename, song* master_song_list)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No history file found. Starting fresh.\n");
        return;
    }

    char song_name[200];
    HistoryNode* tail = NULL;
    while (fgets(song_name, sizeof(song_name), fp))
    {
        song_name[strcspn(song_name, "\n")] = 0;
        song* found_song = find_song_by_name(master_song_list, song_name);

        if (found_song != NULL)
        {
            HistoryNode* new_node = (HistoryNode*)malloc(sizeof(HistoryNode));
            new_node->song_data = found_song;
            new_node->next = NULL;
            if (*head == NULL) {
                *head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    fclose(fp);
}





                    //song functions




song* load_songs(const char* file_name)
{
    FILE* fp;
    fp = fopen(file_name,"r");
    if(!fp)
    {
        printf("file %s not found\n", file_name);
        return NULL;
    }

    song* start = NULL;
    song* end = NULL;

    char song_data[300];

    while(fgets(song_data,sizeof(song_data),fp))
    {
        song* new = calloc(1,sizeof(song));
        if(!new)
        {
            printf("Error : memory allocation failed\n");
            break;
        }
        int r = sscanf(song_data,"%199s %49s %f %99s", new->name,new->artist,&new->duration,new->album);
        if(r<4)
        {
            free(new);
            continue;
        }
        new->id = SONG_ID++;
        new->next = NULL;

        if(start == NULL)   start = new;
        else end->next = new;

        end = new;
    }

    fclose(fp);
    printf("songs loaded successfully\n");
    return start;
}

void show_songs(song *head)
{
    int i = 0;
    printf("\n");
    printf("%-6s %-4s %-30s %-25s %-10s %-20s\n", 
           "ID", "No.", "Song Name", "Artist Name", "Duration", "Album");
    printf("------+----+------------------------------+-------------------------+----------+--------------------\n");

    for (song *temp = head; temp != NULL; temp = temp->next)
    {
        i++;
        printf("%-6d %-4d ", temp->id, i);
        printf("%-30s ", temp->name);
        if (strlen(temp->artist) == 0 || strcmp(temp->artist, "-") == 0)
        {
            printf("%-25s ", "-");
        }
        else 
        {
            printf("%-25s ", temp->artist);
        }
        if (temp->duration == 0.0)
        {
            printf("%-10s ", "-");
        }
        else 
        {
            printf("%-10.2f ", temp->duration);
        }
        if (strlen(temp->album) == 0 || strcmp(temp->album, "-") == 0)
        {
            printf("%-20s\n", "-");
        }
        else 
        {
            printf("%-20s\n", temp->album);
        }
    }
    printf("------+----+------------------------------+-------------------------+----------+--------------------\n");
}


void play_song(song* head, int id, struct HistoryNode** history_head)
{
    for (song* temp_s = head; temp_s != NULL; temp_s = temp_s->next)
    {
        if (temp_s->id == id)
        {
            printf("\n==============================\n");
            printf("  Now Playing: %s\n", temp_s->name);
            printf("  Artist: %s\n", temp_s->artist);
            //printf("  (From original album: %s)\n", temp_s->album);
            printf("  Duration: %.2f\n", temp_s->duration);
            printf("__________________________________\n");
            add_to_history(history_head, temp_s);
            return; 
        }
    }
    printf("\nError: Song whose id is '%d' not found\n", id);
    return;
}


song* find_song(song* head, int id)
{
    for (song* temp_s = head; temp_s != NULL; temp_s = temp_s->next)
    {
        if (temp_s->id == id)
        {
            return temp_s; 
        }
    }
    printf("\nError: Song whose song id is '%d' not found\n", id);
    return NULL;
}

song* find_song_by_name(song* head, const char* name)
{
    for (song* temp_s = head; temp_s != NULL; temp_s = temp_s->next)
    {
        if (strcmp(temp_s->name, name) == 0)
        {
            return temp_s; 
        }
    }
    return NULL;
}

void delete_form_file(song** head,const char* name)
{
    song* cur = *head;
    song* pre = NULL;
    while(cur!= NULL)
    {
        if(strcmp(cur->name,name) == 0)
        {
            if(pre == NULL)
            {
                *head = cur->next;
                return;
            }
            else
            {
                pre->next = cur->next;
            }
            free(cur);
            printf("song '%s' deleted successfully!\n", name);
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    printf("song '%s' not found in list!\n", name);
    return;
}


void add_song_to_file(song** head,song* new)
{
    if(head == NULL)
    {
        *head = new;
        (*head)->next = NULL;
        return;
    }
    else
    {
        song* temp = *head;
        while(temp->next == NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        temp->next->next =NULL;
        return;
    }
}

void assign_new_song_id(song* s) {
    extern int SONG_ID; 
    s->id = SONG_ID++;
}