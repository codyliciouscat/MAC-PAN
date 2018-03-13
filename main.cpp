#include "character.h"
#include "/root/GitHub/Cody-Caleb-Collab/Ampersand-Alpha/utility/inputmanager.h"
//#include "print.h"
using namespace std;

// compile with -lX11 flag
int main()
{
  World fuck("level.txt");
  Character pacman("C", term::foreground_color(255, 255, 0), term::background_color(0, 0, 0), 18, 19, 5);
  TimeManager time;
  InputManager input;
  double stop_time = 0, start_time = 0;

  cout << term::alternate_terminal() << term::cursor_hide();
  while(true)
  {
    if((stop_time - start_time) > 0.25)
    {
      start_time = stop_time;
      pacman.waka();
    }
    input.update();
    time.update();

    if(input.get_key_state(XK_a))
      pacman.move('a', fuck, time);
    if(input.get_key_state(XK_d))
      pacman.move('d', fuck, time);
    if(input.get_key_state(XK_w))
      pacman.move('w', fuck, time);
    if(input.get_key_state(XK_s))
      pacman.move('s', fuck, time);
    if(input.get_key_state(XK_Escape))
    {
      input.flush_stdin_until(27);
      break;
    }

    pacman.update_character(fuck, time);
    fuck.print();
    cout << flush;

    stop_time = time.get_runtime();
  }
  cout << term::normal_terminal() << term::cursor_show();
    //cout << "\e[19;18HC";
  return 0;
}
