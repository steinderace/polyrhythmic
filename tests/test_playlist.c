#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"
#include "playlist.h"

// Test creating nodes
int test_create_node() {
    FileNode* node = create_node();

    ASSERT(node!=NULL, "Node creation failed.");

    return 0;
}

// Testing adding songs to the playlist
int test_add_song() {
    Playlist *playlist = playlist_init();

    ASSERT(playlist!=NULL, "Playlist creation failed.");

    playlist_add(playlist, "song1.mp3");
    playlist_add(playlist, "song2.mp3");
    playlist_add(playlist, "song3.mp3");

    ASSERT(strcmp(playlist_get_current(playlist), "song1.mp3") == 0, "Current should be song1.mp3\n");

    playlist_get_next(playlist);
    ASSERT(strcmp(playlist_get_current(playlist), "song2.mp3") == 0, "Current should be song2.mp3\n");

    playlist_get_next(playlist);
    ASSERT(strcmp(playlist_get_current(playlist), "song3.mp3") == 0, "Current should be song3.mp3\n");

    playlist_get_next(playlist);
    ASSERT(strcmp(playlist_get_current(playlist), "song1.mp3") == 0, "Current should be song1.mp3\n");

    return 0;
}

// Main test runner
int main() {
    int failed = 0;
    if (test_add_song()!=0) failed++;
    if (test_create_node()!=0) failed++;

    if(failed == 0){
        printf("All playlist tests passed.\n");
        return 0;
    } else {
        printf("All playlist tests failed.\n");
        return 1;
    }
}
