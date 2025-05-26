#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <rspq_profile.h>
#include <malloc.h>
#include <math.h>

int main()
{
  debug_init_isviewer();
  debug_init_usblog();
    
  dfs_init(DFS_DEFAULT_LOCATION);

  display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS_DEDITHER);

  rdpq_init();
  gl_init();

  joypad_init();

  rspq_profile_start();

  glEnable(GL_MULTISAMPLE_ARB);

  uint64_t frames = 0;
  while (1)
  {
    joypad_poll();
    // joypad_buttons_t pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    // joypad_buttons_t held = joypad_get_buttons_held(JOYPAD_PORT_1);
    // joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1);


    // render();
    {
      surface_t *disp = display_get();
      surface_t *zbuf = display_get_zbuf();

      rdpq_attach(disp, zbuf);

      gl_context_begin();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glBegin(GL_TRIANGLES);
        glColor3f( 1, 0, 0 ); // red
        glVertex2f( -0.5f, -0.5f );

        glColor3f( 0, 1, 0 ); // green
        glVertex2f( 0.5f, -0.5f );

        glColor3f( 0, 0, 1 ); // blue
        glVertex2f( 0, 0.5f );
      glEnd();

      gl_context_end();

      rdpq_detach_show();

      rspq_profile_next_frame();

      if (((frames++) % 60) == 0) {
          rspq_profile_dump();
          rspq_profile_reset();
          debugf("frame %lld\n", frames);
      }
    }
  }

}
