#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"song.h"
#include"album.h"
#include"queue.h"

void print_menu() {
    printf("\n   +==== MUSIC LIBRARY MENU ====+\n\n");
    printf("    -- COLLECTION --\n");
    printf("     (1) Show all songs (Main Collection)\n");
    printf("     (2) Play song directly from main collection\n");
    printf("\n    -- MY LIBRARY (ALBUMS) --\n");
    printf("     (3) Show all my albums\n");
    printf("     (4) Create a new album\n");
    printf("     (5) Add song from collection to album\n");
    printf("     (6) Add a *brand new* song to an album\n");
    printf("     (7) Delete an album\n");
    printf("\n    -- QUEUE (Circular Player) --\n");
    printf("     (8) Add song from collection to Queue\n");
    printf("     (9) Add song from Album to Queue\n");
    printf("    (10) View Queue\n");
    printf("    (11) Play Queue\n");
    printf("\n    -- HISTORY --\n"); 
    printf("    (12) View Play History\n");
    printf("\n    -- SYSTEM --\n");
    printf("    (13) Save my library\n");
    printf("    (14) Save and Exit\n"); 
    printf("    (15) Show logs\n");
    printf("    (16)Basic usage Guide\n");
    printf("\n   +============================+\n\n");
    printf("\n   write '_' insted of space in string input\n");
    printf("i.e- write 'YOU_TUBE' insted of 'YOU TUBE'\n\n");
    printf("   > Enter your choice: ");
}

 
void show_albums(album* album_head)
{
    printf("\n   === YOUR ALBUM LIBRARY ===\n");
    if (album_head == NULL) {
        printf("   (You have no albums yet)\n");
        return;
    }
    int album_num = 1;
    for (album* temp_album = album_head; temp_album != NULL; temp_album = temp_album->next)
    {
        printf("\n");
        printf(" .---------------------------------------------------------------------------------.\n");
        printf(" | ALBUM #%-3d |  ID: %-5d  |  Name: %-42s |\n", 
               album_num, temp_album->id, temp_album->Name);
        printf(" '---------------------------------------------------------------------------------'\n");
        if (temp_album->song_head == NULL) {
            printf("    (This album is empty)\n");
        } else {
            show_songs(temp_album->song_head);
        }
        album_num++;
    }
    printf("\n====================================================================================\n");
}


void addlog(char* log) {
    FILE* fp = fopen("dot_txt_files/log.txt", "a");
    if (fp == NULL) return;
    fprintf(fp, "LOG: %s\n", log);
    fclose(fp);
}

void show_logs() {
    FILE* fp = fopen("dot_txt_files/log.txt", "r");
    if (fp == NULL) {
        printf("\n(No logs found yet)\n");
        return;
    }
    
    char buffer[300];
    printf("\n   === SYSTEM LOGS ===\n");
    printf("--------------------------------------------------\n");
    while(fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    printf("--------------------------------------------------\n");
    fclose(fp);
}

int main()
{
    //FILE* fp = fopen("dot_txt_files/song.txt","r");
    song* start = load_songs("dot_txt_files/song.txt");
    album* album_head = NULL; 
    CircularNode* queue_player_pos = NULL; 
    HistoryNode* history_head = NULL;
    load_album("dot_txt_files/my_albums.txt",&album_head);
    load_history(&history_head, "dot_txt_files/my_history.txt", start);
    for(int i=0; ; )
    {
        print_menu();
        int x;
        scanf("%d", &x);

        if(x<1 || x>16)
        {
            printf("Invalid Input!\n");
            continue;
        }

        if(x==1)
        {
            addlog("(1) Show all songs (Main Collection)");
            show_songs(start);
        }


        else if(x==2)
        {
            addlog("(2) Play song directly from main collection");
            show_songs(start);
            for(int j=0; ; )
            {
                printf("Enter the song ID : ");
                int song_id;
                scanf("%d", &song_id);
                play_song(start,song_id,&history_head);
                int l;
                printf("1.want to listen more from collection\n");
                printf("2.do not want to listen song directly from collection\n");
                printf("3.show collection of songs\n");
                scanf("%d", &l);
                if(l<1 || l>3)
                {
                    printf("Invalid Input!\n");
                    break;
                }
                if(l == 1)
                {
                    continue;
                }
                else if(l == 2)
                {
                    break;
                }
                else if(l == 3)
                {
                    show_songs(start);
                    int m;
                    printf("1.want to listen more from collection\n");
                    printf("2.do not want to listen song directly from collection\n");
                    scanf("%d", &m);
                    if(m<1 || m>2)
                    {
                        printf("Invalid Input!\n");
                        continue;
                    }
                    if(m == 1)
                    {
                        continue;
                    }
                    else if(m == 2)
                    {
                        break;
                    }
                }
            }
        }


        else if(x==3)
        {
            addlog("(3) Show all my albums");
            show_albums(album_head);
        }


        else if(x==4)
        {
            addlog("(4) Create a new album");
            printf("Enter the name of the new album : ");
            char Name[100];
            scanf("%s", Name);
            album* new_alb = creat_album(Name, &album_head);
            for(int j=0; ; )
            {
                int d;
                printf("1.want to add BRANDNEW song into the album %s\n", Name);
                printf("2,do not want to add song in to the album %s\n", Name);
                printf("Enter your choice : ");
                scanf("%d", &d);
                if(d<1 || d>2)
                {
                    printf("Invalid Input\n");
                }
                if(d == 1){
                    song* news = malloc(sizeof(song));
                    assign_new_song_id(news);
                    printf("Enter the name of new song : ");
                    scanf("%s", news->name);
                    printf("Enter the name of new song's artist : ");
                    scanf("%s", news->artist);
                    printf("Enter the duration of song : ");
                    scanf("%f", &(news->duration));
                    strcpy(news->album,Name);
                    add_song_to_album(news,album_head,new_alb->id);
                    free(news);
                }
                if(d ==2)
                {
                    break;
                }
            }
        }


        else if(x==5)
        {
            addlog("(5) Add song from Database to album");
            printf("here is the collection\n");
            show_songs(start);
            printf("Enter the ID of album : ");
            int al_id;
            scanf("%d",&al_id);
            printf("Enter the ID of song from collection : ");
            int s_id;
            scanf("%d", &s_id);
            song* temp3 = find_song(start,s_id);
            if(temp3 == NULL)
            {
                continue;
            }
            else
            {
                //strcpy(temp3->album,temp1);
                add_song_to_album(temp3,album_head,al_id);
            }
        }


        else if(x==6)
        {
            addlog("(6) Add a *brand new* song to an album");
            song* new = malloc(sizeof(song));
            assign_new_song_id(new);
            int al_id;
            printf("Enter the ID of album in which you want to add the song : ");
            scanf("%d",&al_id);
            printf("Enter the name of song : ");
            scanf("%s", new->name);
            printf("Enter the name of artist of this song : ");
            scanf("%s", new->artist);
            printf("Enter the duration (e.g., 3.45 or -):");
            scanf("%f", &(new->duration));
            //strcpy(new->album,temp1);
            add_song_to_album(new,album_head,al_id);
            free(new);
        }


        else if(x==7)
        {
            addlog("(7) Delete an album");
            show_albums(album_head);
            printf("Enter the ID of album : ");
            int id;
            scanf("%d",&id);
            delete_album(id,&album_head);
        }


        else if(x == 8)
        {
            addlog("(8) Add song from Database to Queue");
            int sid;
            show_songs(start);
            printf("Enter the ID of the song:");
            scanf("%d", &sid);
            song* new = find_song(start,sid);
            if(new == NULL)continue;
            queue_add(&queue_player_pos, new);
        }


        else if(x==9)
        {
            addlog("(9) Add song from Album to Queue");
            int alid;
            int sid;
            album* temp3;
            show_albums(album_head);
            printf("Enter the ID of album:");
            scanf("%d", &alid);
            temp3 = find_album(album_head,alid);
            if(temp3 == NULL)
            {
                printf("album whose ID is '%d' not found!\n", alid);
                continue;
            }
            printf("Enter the ID of song:");
            scanf("%d",&sid);
            song* new = find_song(temp3->song_head,sid);
            if(new == NULL)
            {
                printf("song ID %d not found in album ID %d\n",sid,alid);
                continue;
            }
            queue_add(&queue_player_pos, new);
        }



        else if(x==10)
        {
            addlog("(10) View Queue");
            view_queue(queue_player_pos);
        }
        else if(x==11)
        {
            addlog("(11) Play Queue");
            queue_play(&queue_player_pos, &history_head);
        }

        else if(x==12)
        {
            addlog("(12) View Play History");
            show_history(history_head);
        }
        else if(x==13)
        {
            addlog("(13) Save my library");
            save_history(history_head, "dot_txt_files/my_history.txt"); 
            save_album(album_head, "dot_txt_files/my_albums.txt");
        }
        else if(x == 14)
        {
            addlog("(14) Save and Exit");
            save_history(history_head, "dot_txt_files/my_history.txt");
            save_album(album_head, "dot_txt_files/my_albums.txt");
            printf("Goodbye!\n");   
            clear_queue(&queue_player_pos);
            clear_history(&history_head);
            break;
        }
        else if(x==15)
        {
            addlog("(13) User viewed Logs");
            show_logs();       
        }
        else if(x==16)
        {
            addlog("(15)Basic usage Guide");
            printf("1.In string Input you must enter '_' insted of space otherwise it may crash this Application\n");
            printf("2.In create new album you can create new album with your desired name after that this has also 2 options....\n");
            printf("      (I)want to add BRANDNEW song to album-\n");
            printf("                 this simply means you have expected to enter all details of new song\n");
            printf("                 if you do not want to add new song than you can chose second option\n");
            printf("                 after leaving create album option you can add song from collection to album via option (5)\n");
            printf("                 if you want to add your desired song to     album which is not in collection then chose add BRANDNEW song to album option\n");
            printf("      (II)do not want to add song in to the album-\n");
            printf("                 this option simply leaves from create album and goes to main menu\n");
            printf("3.In queue options you can add your desired song in queue and can play it one after another\n");
            printf("  make sure that this queue is temporary it automatically deleted after closing the app\n");
            printf("  if you want to make your playlist like collection then use the album featurs\n");
            printf("4.you can not directly play song from album you have to add the song from album to queue and then you can play..\n");
            printf("\n\n WE HOPE YOUR EXPERINCE WILL BE GOOD\n");
        }
    }
    return 0;
}
