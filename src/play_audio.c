#include "play_audio.h"
#include "audio_decoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define BUFFER_SIZE 8192

void init_audio() {
    if(SDL_Init(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void play_audio(const char *filename) {
    if(!filename) {
        fprintf(stderr, "Error: filename is NULL.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize audio first
    init_audio();

    // Open and initialize audio decoder
    AudioDecoder *decoder = audio_decoder_create();
    if(!decoder || !decoder->is_initialized) {
        fprintf(stderr, "Error: decoder does not exist or not initialized.\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Open audio file
    if(audio_decoder_open(decoder, filename) != 0) {
        fprintf(stderr, "Error opening audio file.\n");
        audio_decoder_free(decoder);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Defining spec for the audio
    SDL_AudioSpec spec;
    spec.freq = decoder->sample_rate;
    spec.format = AUDIO_S16SYS;
    spec.channels = decoder->channels;
    spec.samples = 4096;
    spec.callback = NULL;

    // Open audio device
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if(dev == 0) {
        fprintf(stderr, "Failed to open audio device: %s\n", SDL_GetError());
        audio_decoder_free(decoder);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Start playback
    SDL_PauseAudioDevice(dev, 0);

    size_t bytes_read;
    int status;

    // Read and play audio
    while((status = audio_decoder_read(decoder, &bytes_read)) == 0) {
        SDL_QueueAudio(dev, decoder->buffer, bytes_read);

        // Prevent queue from getting too large
        while(SDL_GetQueuedAudioSize(dev) > BUFFER_SIZE * 2) {
            SDL_Delay(10);
        }
    }

    // Handle final chunk if EOF reached
    if(status == 1 && bytes_read > 0) {
        SDL_QueueAudio(dev, decoder->buffer, bytes_read);
    }

    // Wait for playback to finish
    while(SDL_GetQueuedAudioSize(dev) > 0) {
        SDL_Delay(10);
    }

    // Cleanup
    SDL_CloseAudioDevice(dev);
    audio_decoder_free(decoder);
    SDL_Quit();
}

void close_audio(AudioDecoder *decoder) {
    audio_decoder_free(decoder);
    SDL_Quit();
}
