#ifndef PLAYLIST_H
#define PLAYLIST_H

// Header file for handling file navigation operations
#include <stdbool.h>
#include <stdlib.h>

// Node for doubly linked list
typedef struct FileNode FileNode;

// Node for doubly linked list
struct FileNode {
    char *filepath;
    char *title;
    FileNode *next;
    FileNode *prev;
};

// Struct for playlist manager
typedef struct {
    FileNode *head;
    FileNode *tail;
    FileNode *current;
    int count;
    bool loop;                  // For looping the playlist
    bool shuffle;               // For shuffling the playlist
} Playlist;

// Function declarations
FileNode* create_node();
void node_destroy(FileNode* node);

// Playlist operations
void playlist_add(Playlist* node, char *filepath);
void playlist_remove_current(Playlist* node);
void playlist_clear(Playlist* node);

// Navigations
const char* playlist_get_current(Playlist* node);
const char* playlist_get_next(Playlist* node);
const char* playlist_get_previous(Playlist* node);
bool playlist_goto(Playlist *playlist, int index);

// Utility functions
int playlist_size(Playlist* playlist);
bool playlist_is_empty(Playlist* playlist);
void playlist_fetch(Playlist *playlist);

#endif
