//#include "pacman.h"
#include "ghost.h"
#include "/root/GitHub/Cody-Caleb-Collab/Ampersand-Alpha/utility/inputmanager.h"
//#include "print.h"
// time manager class not needed to be passed into move function
using namespace std;

// compile with -lX11 flag
int main()
{
  World fuck("level.txt");
  PathTable path_table("graphing/level_path.txt");
  Pacman pacman("C", term::foreground_color(255, 255, 0), term::background_color(0, 0, 0), 18, 19, 5);
  Ghost ghost;
  vector<Node> path;
  TimeManager time;
  InputManager input;
  double stop_time = 0, start_time = 0;

  Vertex target_prev = Vertex(0, 0);
  Vertex target = Vertex(fuck.WORLD_WIDTH - 1, fuck.WORLD_LENGTH - 1);
  target_prev = target;
  path = path_table.table[ghost.nearest_vertex(fuck)][target];

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
    //ghost.move(rand_move(), fuck, time);
    /*if(!(target_prev == target))
    {
      target_prev = target;
      path = path_table.table[ghost.nearest_vertex(fuck)][target];
      ghost.move(ghost.prepend_path(fuck, path), fuck, time);
    }*/

    //cout << "CHECK" << endl;
    cout << "GHOST COORD: (" << ghost.get_x_coord() << ", " << ghost.get_y_coord() << ")" << endl;
    cout << "PATH SIZE: " << path.size() << endl;
    cout << "NEXT VERTEX IN PATH: (" << path[0].location.x_coord << ", " << path[0].location.y_coord << "); INPUT: " << path[0].move << endl;
    if(Vertex(ghost.get_x_coord(), ghost.get_y_coord()) == path[0].location)
    {
      ghost.move(path[0].move, fuck, time);
      path.erase(path.begin());
    }
    //cout << "CHECK 2" << endl;

    pacman.update_character(fuck, time);
    ghost.update_ghost(fuck, time);
    fuck.print();
    cout << flush;
    //cout << "CHECK 3" << endl;

    stop_time = time.get_runtime();
  }
  cout << term::normal_terminal() << term::cursor_show();
    //cout << "\e[19;18HC";
  return 0;
}
