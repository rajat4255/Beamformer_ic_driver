#ifndef BEAMFORMER_DRIVER_H
#define BEAMFORMER_DRIVER_H

#define BF_MAX_CHANNELS 4

/* Register map (dummy, for structure only) */
#define ADAR_REG_GAIN_BASE   0x20   
#define ADAR_REG_PHASE_BASE  0x40

/* Public APIs */
int bf_init(void); // Beam former init function
int bf_set_phase(int channel, int degree);   // By this function we can set beam phase 0 to 360 degree
int bf_set_gain(int channel, int gain_db);   // Gain setting function in db //
int bf_set_beam_angle(int angle_degree);     // Set beam Angle in degree//
int bf_deinit(void); // Beam former deinit

#endif

