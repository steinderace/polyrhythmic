#include "audio_decoder.h"

#include <mpg123.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 8192

// For checking if the mpg123 is initalized
static bool mpg123_library_initialized = false;

// Initialize mpg123 library
AudioDecoder* audio_decoder_create(void) {
    // 1. Check if mpg123 library is initialized and then initialize it if not
    if (!mpg123_library_initialized) {
        if(mpg123_init() != MPG123_OK) {
            fprintf(stderr, "Failed to initialize mpg123 library.\n");
            return NULL;
        }
        mpg123_library_initialized = true;
    }

    AudioDecoder *decoder = malloc(sizeof(AudioDecoder));
    int err;

    // Check malloc allocation
    if (!decoder) {
        fprintf(stderr, "Failed to allocate memory for AudioDecoder.\n");
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

    decoder->is_initialized = true;
    decoder->is_open = false;

    return decoder;
}

// For opening the audio decoder
int audio_decoder_open(AudioDecoder* decoder, const char *filename) {
    if(!decoder || !decoder->is_initialized) {
        fprintf(stderr, "Decoder has not been initialized.\n");
        return -1;
    }

    // Close if previous file has been open
    if(decoder->is_open) {
        mpg123_close(decoder->handle);
    }

    // Open the mp3 file
    if(mpg123_open(decoder->handle, filename) != MPG123_OK) {
        fprintf(stderr, "Unable to open file.\n");
        mpg123_close(decoder->handle);
        return -1;
    }

    // Get audio format
    if(mpg123_getformat(
        decoder->handle,
        &decoder->sample_rate,
        &decoder->channels,
        &decoder->encoding
    ) != MPG123_OK) {
        fprintf(stderr, "Unable to get audio format.\n");
        mpg123_close(decoder->handle);
        return -1;
    }

    decoder->is_open = true;

    printf(
        "Sample rate: %d\nChannels: %d\nEncoding: %d\n",
        decoder->sample_rate,
        decoder->channels,
        decoder->encoding
    );

    return 0;
}

int audio_decoder_read(AudioDecoder* decoder, size_t* bytes_read) {
    if(!decoder || !decoder->is_open) {
        fprintf(stderr, "File has not opened yet.\n");
        return -1;
    }

    int result = mpg123_read(
        decoder->handle,
        decoder->buffer,
        BUFFER_SIZE,
        bytes_read
    );

    if(result == MPG123_OK) {
        return 0;  // Opened file
    } else if(result == MPG123_DONE) {
        return 1; // EOF
    } else {
        return -1; // Error
    }
}

// For closing the mp3 handle and freeing the struct
void audio_decoder_free(AudioDecoder *decoder) {
    mpg123_close(decoder->handle);
    mpg123_delete(decoder->handle);
    free(decoder);
    mpg123_exit();
}
