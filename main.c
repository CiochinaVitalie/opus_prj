#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus.h>
#include <stdio.h>

/*The frame size is hardcoded for this sample code but it doesn't have to be*/
#define FRAME_SIZE 960
#define SAMPLE_RATE 8000
#define CHANNELS 1
#define APPLICATION OPUS_APPLICATION_AUDIO
#define BITRATE 8000
#define MAX_FRAME_SIZE 6 * 960
#define MAX_PACKET_SIZE (3 * 1276)

int main(int argc, char **argv)
{
    /*Holds the state of the encoder and decoder */
    OpusEncoder *encoder;
    OpusDecoder *decoder;
    int err;
    return 0;
}