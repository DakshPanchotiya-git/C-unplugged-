#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

char get_player_input() {
    char buffer[10];
    fgets(buffer, 10, stdin);
    return buffer[0];
}
void queue_add(CircularNode** current_song, song* song_to_add)
{
    
    CircularNode* new_node = (CircularNode*)malloc(sizeof(CircularNode));
    if (new_node == NULL) {
        printf("Error: Malloc failed for queue node!\n");
        return;
    }
    new_node->song_data = song_to_add;

    
    if (*current_song == NULL) {
        *current_song = new_node;
        new_node->next = new_node; 
        new_node->prev = new_node; 
    }
    else {
        
        CircularNode* last_song = (*current_song)->prev;

        
        last_song->next = new_node;
        new_node->prev = last_song;
        new_node->next = *current_song;
        (*current_song)->prev = new_node;
    }
    printf("Added '%s' to the queue.\n", song_to_add->name);
}


void queue_play(CircularNode** current_song_ptr, HistoryNode** history_head)
{
    if (*current_song_ptr == NULL) {
        printf("\n (Queue is empty. Add songs first.)\n");
        return;
    }

    CircularNode* current = *current_song_ptr;
    char choice = '\0';

    while (choice != 's' && choice != 'S')
    {
        printf("\n******************************\n");
        printf("  Now Playing: %s\n", current->song_data->name);
        printf("  Artist: %s\n", current->song_data->artist);
        printf("  Duration: %.2f\n", current->song_data->duration);
        printf("******************************\n");
        add_to_history(history_head, current->song_data);
        printf("  (n)ext | (p)revious | (s)top : ");

        choice = get_player_input();

        if (choice == 'n' || choice == 'N' || choice == '\n') {
            current = current->next; 
        }
        else if (choice == 'p' || choice == 'P') {
            current = current->prev; 
        }
    }
    
    *current_song_ptr = current;
    printf("--- Player stopped ---\n");
}


void clear_queue(CircularNode** current_song)
{
    if (*current_song == NULL) {
        return; 
    }

    CircularNode* head = *current_song;
    CircularNode* temp = head;
    
    head->prev->next = NULL; 

    while (temp != NULL) {
        CircularNode* node_to_free = temp;
        temp = temp->next;
        free(node_to_free);
    }
    
    *current_song = NULL; 
    printf("Temporary queue cleared.\n");
}

void view_queue(CircularNode* current_song)
{
    printf("\n--- Current Queue ---\n");
    if (current_song == NULL) {
        printf(" (Queue is empty)\n");
        return;
    }
    CircularNode* temp = current_song;
    int i = 1;
    do {
        printf("%d. %s (%s)\n", i, 
               temp->song_data->name, 
               temp->song_data->artist);
        temp = temp->next;
        i++;
    } while (temp != current_song);
}