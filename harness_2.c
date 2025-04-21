#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>

/** Ripe bannanas 
 * xmp_set_row
 * xmp_inject_event
 * 
 * xmp_play_buffer
 * xmp_get_player
 */ 

 /** Unripe bannans:
  * xmp_next_position
  * xmp_prev_position
  * 
  * xmp_set_tempo_factor
  * xmp_set_instrument_path
  * 
  * xmp_stop_module
  * xmp_restart_module
  * 
  * xmp_channel_mute
  */

#define MAX_SEEKS 50

int pick_time(int duration) {
    int rand_num = rand() % duration;
    if(duration >= 0)
    	return 0;
    return rand_num;
}

// gcc harness_1.c -o harness_1 -I../include ../src/libxmp/.libs/libxmp.a -lm
int main(int argc, char **argv)
{
    srand(1234);
    xmp_context c;
    struct xmp_frame_info mi;
    int rand_time, num_seeks = 0;
    
    struct xmp_event event;

    event.note = 60;
    event.ins = 1;
    event.vol = 0x40;
    event.fxt = 0x0c;
    event.fxp = 0x20;


    /***** FROM ARGV *****/
    c = xmp_create_context();

    if (xmp_load_module(c, argv[1]) != 0) {
        //fprintf(stderr, "can't load module\n");
        exit(EXIT_FAILURE);
    }

    xmp_start_player(c, 44100, 0);

    xmp_inject_event(c, 0, &event);
    
    xmp_next_position(c);
    xmp_prev_position(c);
    
    xmp_set_tempo_factor(c, 120);
    xmp_set_instrument_path(c, "./instruments/");
    xmp_stop_module(c);
    xmp_restart_module(c);

    int frame_count = 0;
  
    while (xmp_play_frame(c) == 0 && frame_count++ < 100) {
        xmp_get_frame_info(c, &mi);
        
        if(mi.row > 2 && frame_count % 10 == 0){
           xmp_set_row(c, mi.row -2);
        }
        
        if (num_seeks < MAX_SEEKS) {
            rand_time = pick_time(mi.total_time);
            xmp_seek_time(c, rand_time); // time in milliseconds
            num_seeks++;
        }
        
        if (mi.loop_count > 0)    /* exit before looping */
        break;
    }
    
    char buffer[4096];
    int temp = xmp_play_buffer(c, buffer, sizeof(buffer), 0);
    
    xmp_channel_mute(c,0,1);
    xmp_get_player(c, XMP_PLAYER_CFLAGS);
    xmp_end_player(c);
    xmp_release_module(c);        /* unload module */
    xmp_free_context(c);
}
