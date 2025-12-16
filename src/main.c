#include <stdio.h>
#include <mpg123.h>

#include "audio_decoder.h"

#define BUFFER_SIZE 8192

int main(int argc, char **argv) {
    AudioDecoder* decoder = create_audio_decoder();


    printf("Hello World!\n");
    return 0;
}
