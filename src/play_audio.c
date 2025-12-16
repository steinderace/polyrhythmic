#include "play_audio.h"

#include <stdio.h>
#include <stdlib.h>

void play_audio(AudioDecoder *decoder) {
    if(!decoder || !decoder->initialized) {
        fprintf(stderr, "Error: decoder does not exist or not initialized.\n");
        exit(EXIT_FAILURE);
    }

    printf(
        "Sample rate: %d\nChannels: %d\nEncoding: %d\n",
        decoder->sample_rate,
        decoder->channels,
        decoder->encoding
    );


}
