// video player
// - rlyeh, public domain

#include "engine.h"

int main() {
    // 75% window, msaa x2
    app_create( 75, APP_MSAA2 );

    // load video
    int do_rgb = flag("--rgb") ? 1 : 0;
    video_t *v = video( "pexels-pachon-in-motion-17486489.mp4", VIDEO_LOOP | (do_rgb ? VIDEO_RGB : VIDEO_YCBCR) );

    while( app_swap() && !input(KEY_ESC) ) {
        // decode video frame and get associated textures (audio is automatically sent to audiomixer)
        texture_t *textures = video_decode( v );

        // present decoded textures as a fullscreen composed quad
        blit(textures, 0, do_rgb ? BLIT_RGB : BLIT_YCBCR);

        // ui video
        if( ui_panel("Video", 0) ) {
            if( ui_button("Rewind") )  video_seek(v, video_position(v) - 3);
            if( ui_button("Pause") )   video_pause(v, video_is_paused(v) ^ 1);
            if( ui_button("Forward") ) video_seek(v, video_position(v) + 3);
            ui_panel_end();
        }

#if HAS_AUDIO
        // audio
        if( ui_panel("Audio", 0)) {
            static float master = 1;
            if( ui_slider2("Master", &master, va("%.2f", master))) audio_volume_master(master);
            ui_panel_end();
        }
#endif
    }
}
