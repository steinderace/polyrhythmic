#include "playlist.h"

#include <stdbool.h>
#include <stdlib.h>

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

// For adding a new song to the playlist
void playlist_add(Playlist* node, char* filepath) {

}
