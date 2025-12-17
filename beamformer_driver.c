#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "beamformer_driver.h"

/* Internal data structure */
struct bf_channel_cfg {
    int gain_db;
    int phase_deg;
};

 /* Pointer of Beamformer data structure */
static struct bf_channel_cfg *bf_channels; 

/* Mutex for synchronization */
static pthread_mutex_t bf_lock;   

/* ---------SPI PLACEHOLDER ------------- */
static int spi_write_reg(int reg, int value)
{
    printf("[SPI] WRITE reg=0x%X value=%d\n", reg, value);
    return 0;
}

//      Driver init
  
int bf_init(void)
{
    int i;

    printf("Beamformer init function\n");

    bf_channels = malloc(sizeof(struct bf_channel_cfg) * BF_MAX_CHANNELS);
    if (!bf_channels) {
        perror("malloc failed");
        return -1;
    }
    else
    {
       printf("\n Beamformer internal structure memory allocation successful");
    }

    pthread_mutex_init(&bf_lock, NULL);

    pthread_mutex_lock(&bf_lock);
    // Intialization of beamformer datastruct with zero
    for (i = 0; i < BF_MAX_CHANNELS; i++) {
        bf_channels[i].gain_db = 0;
        bf_channels[i].phase_deg = 0;
    }
    pthread_mutex_unlock(&bf_lock);

    return 0;
}

//        Set Phase

int bf_set_phase(int channel, int degree)
{
    if (channel < 0 || channel >= BF_MAX_CHANNELS)
        return -1;

    if (degree < 0 || degree > 360)
        return -1;

    pthread_mutex_lock(&bf_lock);

    bf_channels[channel].phase_deg = degree;
    spi_write_reg(ADAR_REG_PHASE_BASE + channel, degree);

    pthread_mutex_unlock(&bf_lock);

    printf("Channel %d phase set to %d deg\n", channel, degree);
    return 0;
}

//            Set gain

int bf_set_gain(int channel, int gain_db)
{
    if (channel < 0 || channel >= BF_MAX_CHANNELS)
        return -1;

    pthread_mutex_lock(&bf_lock);

    bf_channels[channel].gain_db = gain_db;
    spi_write_reg(ADAR_REG_GAIN_BASE + channel, gain_db);

    pthread_mutex_unlock(&bf_lock);

    printf("Channel %d gain set to %d dB\n", channel, gain_db);
    return 0;
}

//               Beam angle

int bf_set_beam_angle(int angle_degree)
{
    int ch;
    int phase;

    printf("Setting beam angle: %d deg\n", angle_degree);

    pthread_mutex_lock(&bf_lock);

    for (ch = 0; ch < BF_MAX_CHANNELS; ch++) {
        phase = (ch * angle_degree) % 360;
        bf_channels[ch].phase_deg = phase;
        spi_write_reg(ADAR_REG_PHASE_BASE + ch, phase);
    }

    pthread_mutex_unlock(&bf_lock);

    return 0;
}

//          Deinit

int bf_deinit(void)
{
    pthread_mutex_destroy(&bf_lock);
    
    free(bf_channels);
    bf_channels = NULL;

    printf("Beamformer deinit\n");
    return 0;
}

