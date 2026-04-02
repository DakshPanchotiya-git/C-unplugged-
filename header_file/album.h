#ifndef ALBUM
#define ALBUM
#include"song.h"

extern int SONG_ID;
//extern int ALBUM_ID;

typedef struct album
{
    int id;
    char Name[200];
    song* song_head;
    struct album* next;
} album;

album* find_album(album* head, int id);
album* find_album_by_name(album* head, const char* name);
album* creat_album(const char* name,album** head);
void load_album(const char* filename,album** head);
void save_album(album* head,const char* filename);
void add_song_to_album(song* new_song, album* head, int album_id);
void delete_album(int album_id, album** head);
void delete_song_from_album(album* head, const char* s_name, int album_id);

#endif