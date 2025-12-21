#ifndef PLAY_AUDIO_H
#define PLAY_AUDIO_H

#include "audio_decoder.h"
#include <SDL.h>

void init_audio();
void play_audio(AudioDecoder* decoder);

#endif
