#ifndef QUEUE_H
#define QUEUE_H

#include "song.h" 

typedef struct CircularNode {
    song* song_data;
    struct CircularNode* next; 
    struct CircularNode* prev;
} CircularNode;

void queue_add(CircularNode** current_song, song* song_to_add);
void view_queue(CircularNode* current_song);
void queue_play(CircularNode** current_song_ptr, HistoryNode** history_head);
void clear_queue(CircularNode** current_song);


#endif