#ifndef PLAYLIST_H
#define PLAYLIST_H

// Header file for handling file navigation operations
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Node for doubly linked list
typedef struct FileNode {
    char *filepath;
    char *title;
    struct FileNode *next;
    struct FileNode *prev;
} FileNode;

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
Playlist* playlist_init();
void playlist_add(Playlist* pl_node, char *filepath);
void playlist_remove_current(Playlist* node);
void playlist_clear(Playlist* node);

// Navigations
const char* playlist_get_current(Playlist* node);
const char* playlist_get_next(Playlist* node);
const char* playlist_get_previous(Playlist* node);
const char* playlist_goto(Playlist *playlist, int index);

// Utility functions
int playlist_size(Playlist* playlist);
int playlist_is_empty(Playlist* playlist);
void playlist_fetch(Playlist *playlist);

#endif
