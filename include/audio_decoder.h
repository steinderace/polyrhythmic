#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

#define BUFFER_SIZE 8192

#include <mpg123.h>
#include <stdlib.h>

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
AudioDecoder* create_audio_decoder(void);
void exit_audio_decoder(AudioDecoder* decoder);

#endif
