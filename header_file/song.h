#ifndef SONG_H
#define SONG_H


static int SONG_ID = 1;


typedef struct song 
{
    int id;
    char name[200];
    char artist[50];
    float duration;
    char album[100];
    struct song* next;
}song;

typedef struct HistoryNode {
    song* song_data;
    struct HistoryNode* next;
} HistoryNode;



void add_to_history(HistoryNode** head, song* song_to_add);
void show_history(HistoryNode* head);
void clear_history(HistoryNode** head);
void save_history(HistoryNode* head, const char* filename);
void load_history(HistoryNode** head, const char* filename, struct song* master_song_list);

song* load_songs(const char* file_name);
void show_songs(song *head); 
void play_song(song* head, int id, struct HistoryNode** history_head);
void add_song_to_file(song** head,song* new);
void delete_form_file(song** head,const char* name);
song* find_song(song* head,int id);
song* find_song_by_name(song* head, const char* name);
void assign_new_song_id(song* s);

#endif