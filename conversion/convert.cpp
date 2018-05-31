#include "../map.h"
using namespace std;

// need to create a function that finds lenght and width
// include length and width in file after conversion
int main(int argc, char** argv)
{
  ifstream fin;
  ofstream fout;
  string input;

  fin.open(argv[1]);
  fout.open(argv[2]);

  while(fin >> input)
  {
    for(int i = 0; i < input.size(); i++)
    {
      if(input[i] == '|')
        fout << WALL << endl;
      else if(input[i] == '=')
        fout << CEILING << endl;
      else if(input[i] == '7')
        fout << lCEILING_CORNER << endl;
      else if(input[i] == '9')
        fout << rCEILING_CORNER << endl;
      else if(input[i] == '1')
        fout << lFLOOR_CORNER << endl;
      else if(input[i] == '3')
        fout << rFLOOR_CORNER << endl;
      else if(input[i] == 'a')
        fout << EWAY_RIGHT << endl;
      else if(input[i] == 'b')
        fout << EWAY_LEFT << endl;
      else if(input[i] == 'c')
        fout << EWAY_UP << endl;
      else if(input[i] == 'd')
        fout << EWAY_DOWN << endl;
      else if(input[i] == '+')
        fout << EWAY << endl;
      else if(input[i] == '.')
        fout << POINT << endl;
      else if(input[i] == 'x')
        fout << 'x' << endl;
      else if(input[i] == 'X')
        fout << BACKGROUND << endl;
      else if(input[i] == 'o')
        fout << POWER << endl;
      else if(input[i] == '-')
        fout << OPEN << endl;
      else if(input[i] == '*')
        fout << BLANK_SPACE << endl;
    }
  }
  fin.close();
  fout.close();

  return 0;
}
