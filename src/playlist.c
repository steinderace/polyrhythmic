#include "playlist.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FileNode* create_node() {
    FileNode* node = malloc(sizeof(FileNode));

    if(!node) {
        fprintf(stderr, "Failed to allocate memory for playlist.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    node->filepath = NULL;
    node->title = NULL;

    return node;
}

void node_destroy(FileNode* node) {
    free(node->filepath);
    free(node->title);
    free(node);
}

// Creating a playlist struct
Playlist* playlist_init() {
    Playlist* playlist = malloc(sizeof(Playlist));

    if(!playlist) {
        fprintf(stderr, "Failed to allocate memory for playlist.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
    playlist->count = 0;

    return playlist;
}

// For adding a new song to the playlist
void playlist_add(Playlist* pl_node, char* filepath) {
    if(!pl_node || !filepath) {
        fprintf(stderr, "No playlist node or filepath found.\n");
        exit(EXIT_FAILURE);
    }

    FileNode *node = create_node();
    if(!node) {
        fprintf(stderr, "Failed to allocate memory for playlist node.\n");
        exit(EXIT_FAILURE);
    }

    node->filepath = strdup(filepath);
    if(!node->filepath) {
        free(node);
    }

    node->title = NULL;
    node->next = NULL;
    node->prev = NULL;

    if(pl_node->head == NULL) {
        // Add to empty list
        pl_node->head = node;
        pl_node->tail = node;
        pl_node->current = node;
    } else {
        // Not empty list
        node->prev = pl_node->tail;
        pl_node->tail->next = node;
        pl_node->tail = node;
    }

    pl_node->count++;
}

// Returns current song
const char* playlist_get_current(Playlist* pl_node) {
    if(!pl_node) {
        fprintf(stderr, "Playlist empty. \n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    return pl_node->current->filepath;
}

// Returns next song
const char* playlist_get_next(Playlist* pl_node) {
    if(!pl_node || !pl_node->current) {
        fprintf(stderr, "Playlist empty. \n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    if(pl_node->current->next == NULL) {
        fprintf(stderr, "No next song available.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    return pl_node->current->next->filepath;
}

// Returns previous song
const char* playlist_get_previous(Playlist* pl_node) {
    if(!pl_node || !pl_node->current) {
        fprintf(stderr, "Playlist empty. \n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    if(pl_node->current->prev == NULL) {
        fprintf(stderr, "No previous song available.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    return pl_node->current->prev->filepath;
}

// Returns playlist size
int playlist_size(Playlist* playlist) {
    return playlist->count;
}

// Returns if playlist is empty or not
int playlist_is_empty(Playlist* playlist) {
    return (playlist == NULL);
}
