#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus.h>
#include <stdio.h>
#include "opus_interface.h"


typedef enum
{
  SAMPLING_FREQ_8000 = 8000,
  SAMPLING_FREQ_16000 = 16000
} OUTPUT_FREQ_TypeDef;

/**
  * @brief Channels input number enumerator
  */
typedef enum
{
  IN_CHANNELS_1 = 0x1,
  IN_CHANNELS_2 = 0x2,
  IN_CHANNELS_3 = 0x3,
  IN_CHANNELS_4 = 0x4
} INPUT_MIC_TypeDef;

/**
  * @brief Channels output number enumerator
  */
typedef enum
{
  OUT_CHANNELS_1 = 0x1,
  OUT_CHANNELS_2 = 0x2,
  OUT_CHANNELS_3 = 0x3,
  OUT_CHANNELS_4 = 0x4,
  OUT_CHANNELS_5 = 0x5,
  OUT_CHANNELS_6 = 0x6,
  OUT_CHANNELS_7 = 0x7,
  OUT_CHANNELS_8 = 0x8
} OUTPUT_CH_TypeDef;

typedef enum
{
  OPT_SUCCESS = 1,
  OPT_ERROR = 0
} OPT_StatusTypeDef;

#define AUDIO_CHANNELS_IN                  (uint16_t) (IN_CHANNELS_1)		        /*!< Input channels number.*/
#define AUDIO_CHANNELS_OUT                 (uint16_t) (OUT_CHANNELS_1)             /*!< Output channels number.*/
#define AUDIO_IN_SAMPLING_FREQUENCY        (uint16_t) (SAMPLING_FREQ_16000)		/*!< Audio acquisition sampling frequency.*/
#define AUDIO_OUT_SAMPLING_FREQUENCY       (uint16_t) (SAMPLING_FREQ_16000)		/*!< Audio USB output sampling frequency.*/
#define PCM_IN_SAMPLES_PER_MS              (AUDIO_IN_SAMPLING_FREQUENCY/1000)	     /*!< Number of PCM samples for each ms of audio acquired.*/
#define PCM_OUT_SAMPLES_PER_MS             (AUDIO_OUT_SAMPLING_FREQUENCY/1000)	     /*!< Number of PCM samples for each ms of audio given as output.*/
#define AUDIO_IN_MS                        (20)//N_MS_PER_INTERRUPT  /*!< Audio frame size used for Opus compression.*/
#define PCM_AUDIO_IN_SAMPLES               (PCM_IN_SAMPLES_PER_MS * AUDIO_IN_MS)     /*!< Number of PCM samples input total.*/ //320
#define AUDIO_OUT_MS                       (20)  				     /*!< Number of ms of Audio buffered in Rx before USB.*/
#define PCM_BUFFER_USB_LEN                 (PCM_OUT_SAMPLES_PER_MS * AUDIO_OUT_MS)   /*!< Number of PCM samples output total.*/

ENC_Opus_ConfigTypeDef EncConfigOpus;   /*!< opus encode configuration.*/
DEC_Opus_ConfigTypeDef DecConfigOpus;   /*!< opus decode configuration.*/

static OPT_StatusTypeDef Opus_App_EncInit(void);
static OPT_StatusTypeDef Opus_App_DecInit(void);

long GetFileSize(const char *filename)
{
    long size;
    FILE *f;

    f = fopen(filename, "rb");
    if (f == NULL)
        return -1;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fclose(f);

    return size;
}


int main(int argc, char **argv)
{
   char *inFile;
   FILE *fin;
   char *outFile;
   FILE *fout;
   opus_int16 in[320];
   opus_int16 out[320];
   opus_uint8 enc_data[40];

   //unsigned char cbits[320];
   int nbBytes;

   int err;
   if (argc != 3)
   {
      fprintf(stderr, "usage: trivial_example input.pcm output.pcm\n");
      fprintf(stderr, "input and output are 16-bit little-endian raw files\n");
      return EXIT_FAILURE;
   }

   err = Opus_App_EncInit();
   if (err==OPT_ERROR)
   {
      fprintf(stderr, "failed to init enc_opus: %s\n", opus_strerror(err));
      return EXIT_FAILURE;
   }
  err = Opus_App_DecInit();
   if (err==OPT_ERROR)
   {
      fprintf(stderr, "failed to init dec_opus: %s\n", opus_strerror(err));
      return EXIT_FAILURE;
   }


   inFile = argv[1];
   fin = fopen(inFile, "r");
   if (fin==NULL)
   {
      fprintf(stderr, "failed to open input file: %s\n", strerror(errno));
      return EXIT_FAILURE;
   }

   long res = GetFileSize((char*)inFile);
   fprintf(stderr, "FILE size is : %ld\n", res);

   outFile = argv[2];
   fout = fopen(outFile, "w");
   if (fout==NULL)
   {
      fprintf(stderr, "failed to open output file: %s\n", strerror(errno));
      return EXIT_FAILURE;
   }

   while (1)
   {
      int i;
      unsigned char pcm_bytes[640];
      int frame_size;
      /* Read a 16 bits/sample audio frame. */
      fread(enc_data, sizeof(unsigned char), 40, fin);
      if (feof(fin))
         break;
      /* Convert from little-endian ordering. */
      // for (i=0;i<320;i++)
      //    in[i]=pcm_bytes[2*i+1]<<8|pcm_bytes[2*i];
      /* Encode the frame. */
   //   nbBytes = ENC_Opus_Encode(in,enc_data);//EncConfigOpus.pInternalMemory

      // if (nbBytes<0)
      // {
      //    fprintf(stderr, "encode failed: %s\n", opus_strerror(nbBytes));
      //    return EXIT_FAILURE;
      // }
      /* Decode the data. In this example, frame_size will be constant because
         the encoder is using a constant frame size. However, that may not
         be the case for all encoders, so the decoder must always check
         the frame size returned. */
  
      frame_size = DEC_Opus_Decode(enc_data,40,(uint8_t *)out);//DecConfigOpus.pInternalMemory,EncConfigOpus.pInternalMemory

      if (frame_size<0)
      {
         fprintf(stderr, "decoder failed: %s\n", opus_strerror(frame_size));
         return EXIT_FAILURE;
      }
      
      /* Convert to little-endian ordering. */
      for(i=0;i<320;i++)//frame_size
      {
         pcm_bytes[2*i]=out[i]&0xFF;//DecConfigOpus.pInternalMemory
         pcm_bytes[2*i+1]=(out[i]>>8)&0xFF;//DecConfigOpus.pInternalMemory
      }
      /* Write the decoded audio to file. */
      fwrite(pcm_bytes, sizeof(short), 320, fout);
   }
   /*Destroy the encoder state*/
   ENC_Opus_Deinit();
   DEC_Opus_Deinit(); 

   fclose(fin);
   fclose(fout);
   return EXIT_SUCCESS;
}

/**
 * @brief  Handle init opus encoder command.
 * @param  Message received.
 * @retval OPT_SUCCESS in case of success OPT_ERROR otherwise.
 */
static OPT_StatusTypeDef Opus_App_EncInit(void)
{
  Opus_Status status;

  if(ENC_Opus_IsConfigured())
   {
     return OPT_ERROR;
   }

  EncConfigOpus.application = OPUS_APPLICATION_VOIP;
  EncConfigOpus.bitrate = 16000;
  EncConfigOpus.channels = AUDIO_CHANNELS_IN;//AUDIO_CHANNELS_IN
  EncConfigOpus.complexity = 0;
  EncConfigOpus.ms_frame = AUDIO_IN_MS;//AUDIO_IN_MS
  EncConfigOpus.sample_freq = AUDIO_IN_SAMPLING_FREQUENCY;//AUDIO_IN_SAMPLING_FREQUENCY

  uint32_t enc_size = ENC_Opus_getMemorySize(&EncConfigOpus);
 // printf("enc_size = %d",enc_size);
  EncConfigOpus.pInternalMemory = (uint8_t *)malloc(enc_size);

  int opus_err;

  status = ENC_Opus_Init(&EncConfigOpus, &opus_err);

  if(status != OPUS_SUCCESS)
  {
     return OPT_ERROR;
  }

  status = ENC_Opus_Set_CBR();
   if(status != OPUS_SUCCESS)
   {
     return OPT_ERROR;
   }

   status = ENC_Opus_Force_CELTmode();//ENC_Opus_Force_SILKmode();//ENC_Opus_Force_CELTmode();
   if(status != OPUS_SUCCESS)
   {
     return OPT_ERROR;
   }

   return OPT_SUCCESS;

}
/**
 * @brief  Handle init opus decoder command.
 * @param  Message received.
 * @retval OPT_SUCCESS in case of success OPT_ERROR otherwise.
 */
static OPT_StatusTypeDef Opus_App_DecInit(void)
{
  Opus_Status status;

  if(DEC_Opus_IsConfigured())
  {
    return OPT_ERROR;
  }

  DecConfigOpus.channels = AUDIO_CHANNELS_OUT;//AUDIO_CHANNELS_OUT1
  DecConfigOpus.ms_frame = AUDIO_OUT_MS;//AUDIO_OUT_MS
  DecConfigOpus.sample_freq = AUDIO_OUT_SAMPLING_FREQUENCY;//AUDIO_OUT_SAMPLING_FREQUENCY

  uint32_t dec_size = DEC_Opus_getMemorySize(&DecConfigOpus);

  DecConfigOpus.pInternalMemory = (uint8_t *)malloc(dec_size);

  int opus_err;
  status = DEC_Opus_Init(&DecConfigOpus, &opus_err);

  if(status != OPUS_SUCCESS)
  {
      return OPT_ERROR;
  }

  return OPT_SUCCESS;
}