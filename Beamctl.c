#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <beamformer_driver.h>
// User space cli apllication
int main(int argc, char *argv[])
{
    bf_init();

    if (argc < 2) {
        printf("Usage:\n");
        printf("./beamctl --phase <ch> <deg>\n");
        printf("./beamctl --gain <ch> <db>\n");
        printf("./beamctl --angle <deg>\n");
        return -1;
    }

    if (!strcmp(argv[1], "--phase")) {
         printf("\n Phase of channel %d is set to %d degree",atoi(argv[2]), atoi(argv[3]));
         bf_set_phase(atoi(argv[2]), atoi(argv[3]));
    } else if (!strcmp(argv[1], "--gain")) {
         printf("\n Gain of channel %d is set to %d db",atoi(argv[2]), atoi(argv[3]));
         bf_set_gain(atoi(argv[2]), atoi(argv[3]));
    } else if (!strcmp(argv[1], "--angle")) {
         printf("\n Beam angle is set to %d degree",atoi(argv[2]));
         bf_set_beam_angle(atoi(argv[2]));
    }

    bf_deinit();
    return 0;
}


