#include <mpg123.h>
#include <stdlib.h>

#include "audio_decoder.h"

// Initialize mpg123 library
AudioDecoder* create_audio_decoder(void) {
    AudioDecoder *decoder = malloc(sizeof(AudioDecoder));
    int err;

    // Check malloc allocation
    if (!decoder) {
        fprintf(stderr, "Failed to allocate memory for AudioDecoder.\n");
        return NULL;
    }

    // 1. initialize the mpg123 library
    if (mpg123_init() != MPG123_OK) {
        fprintf(stderr, "Failed to initialize mpg123.\n");
        free(decoder);
        return NULL;
    }

    // 2. Create a new handle
    decoder->handle = mpg123_new(NULL, &err);
    if (!decoder->handle) {
        fprintf(stderr, "Unable to create mpg123 handle: %s\n", mpg123_plain_strerror(err));
        mpg123_exit();
        free(decoder);
        return NULL;
    }

    return decoder;
}

// For closing the mp3 handle and freeing the struct
void free_audio_decoder(AudioDecoder *decoder) {
    mpg123_close(decoder->handle);
    mpg123_delete(decoder->handle);
    free(decoder);
    mpg123_exit();
}
