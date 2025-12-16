#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

#include <mpg123.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    mpg123_handle *handle;
    long sample_rate;
    int channels;
    int encoding;
    unsigned char buffer[BUFFER_SIZE];
    bool is_initialized;
    bool is_open;
} AudioDecoder;

// Declaring functions for the header file here
AudioDecoder* audio_decoder_create(void);
int audio_decoder_open(AudioDecoder* decoder, const char *filename);
int audio_decoder_read(AudioDecoder* decoder, size_t* bytes_read);
void audio_decoder_free(AudioDecoder* decoder);

#endif
