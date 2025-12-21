#include <stdio.h>
#include <mpg123.h>

#include "play_audio.h"
#include "audio_decoder.h"

#define BUFFER_SIZE 8192

int main(int argc, char **argv) {
    AudioDecoder *decoder = audio_decoder_create();

    return 0;
}
