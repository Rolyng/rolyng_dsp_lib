#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include "rdsp.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (256)

static int paCallback(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData) {
    // Copy the input buffer to the output buffer for playback
    memcpy(outputBuffer, inputBuffer, framesPerBuffer * sizeof(float));
    return paContinue;
}

int run(void) {
    PaStream *stream;
    PaError err;

    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError) {
        fprintf(stderr, "PortAudio initialization failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    // Open a stream for recording and playback
    err = Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, paCallback, NULL);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream opening failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    // Start the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream starting failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    printf("Recording and playing. Press Enter to stop.\n");
    getchar(); // Wait for user to press Enter

    // Stop and close the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream stopping failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio stream closing failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    // Terminate PortAudio
    err = Pa_Terminate();
    if (err != paNoError) {
        fprintf(stderr, "PortAudio termination failed: %s\n", Pa_GetErrorText(err));
        goto error;
    }

    return 0;

error:
    // Handle errors and cleanup
    Pa_Terminate();
    return 1;
}

