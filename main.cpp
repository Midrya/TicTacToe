/*
 * Griffin Bruno
 * main.cpp : defines the tictactoe game
 */
#include <string>
#include <vector>
#include <ncurses.h>
#include "minimax.hpp"
#include "draw.hpp"

using std::vector;

bool validPlay(int play, vector<int> validPlays);

int main()
{
  initscr();            //start curses
  cbreak();             //disable line buffering, and take signal character as regular input
  keypad(stdscr, TRUE); //enable the keypad as input
  noecho();             //do not print input while being typed
  refresh();            //refresh stdscr to avoid display errors
  start_color();        //begin color mode

  //declaration of all full scope varaibles
  char t;                //used as a control and swap variable
  char p1 = 'x';         //two play variables, for turn switching
  char p2 = 'o';
  bool turn;             //turn variable
  WINDOW *board;         //board window
  WINDOW *squares[9];    //window for each square on the board
  WINDOW *messages;      //window for displaying messages
  std::string game =     //holds the current game state
    "   "
    "   "
    "   ";
  int row, col;          //row and column counts for the terminal/stdscr
  
  getmaxyx(stdscr, row, col); //set row and col

  //these are used to create a square-ish (row = cols) board
  //as well as creating the message window
  bool bAdjust = row < col;                             //is the terminal fat or tall
  int adjust = bAdjust ? row : col;                     //get the smaller dimension
  int displace = (bAdjust ? col - row : row - col) / 2; //the displacement based on the dimension

  board = curseDraw::drawBoard(bAdjust, adjust, displace); //creating the board with the adjusted dimensions

  for (int i = 0; i < 9; ++i) //populating the play squares
    {
      squares[i] = newwin(
			  (adjust / 3) - 2, // make it fit
			  (adjust / 3) - 2, // make it fit
			  ((adjust * (i / 3)) / 3) + (bAdjust ? 0 : displace) + 1, //starty adjustment
			  (adjust * (i % 3))/3 + (bAdjust ? displace : 0) + 1);    //startx adjustment
    }

  messages = newwin(displace - 1, displace - 1, 0, 0); //creating the messages window
  wprintw(messages, "Make First Move: (y/N)");         //ask the player if they would like to play first
  wrefresh(messages);                                  //refresh the message window
  
  turn = ((t = getch()) != 'y');                       //set the turn varaible to match the input given
  
  mvwprintw(messages, 0, 0, "Controls\nMOVE: arrow keys\nSELECT: enter or home key"); //print controls
  wrefresh(messages);                                  //refresh the message window
  
  mvaddch(row, col,' '); //move the cursor to the bottom of the screen

  //the game loop
  while (!minimax::gameOver(game, t)) //while the game isn't over
    {
      int play = -1; //set the play variable to -1, so no valid move has been made yet
      if (turn) //AI turn
	{
	  play = minimax::minimax(game,	p1, p2,	0, true); //run the minimax algorithm
	}
      else //player turn
	{
	  vector<int> valid = minimax::getAvailableMove(game); //get available (valid) moves
	  int position = valid[0]; //set the initial position to the first available valid move
	  squares[position] = curseDraw::highlightWin(squares[position]); //highlight the selected square
	  int ch; //int must be used to accept the values being accepted (keypad characters)
	  
	  while (!validPlay(play, valid)) //while the play is not valid
	    {
	      ch = getch(); //get the key stroke
	      switch (ch) //switch based on the key stroke
		{
		case KEY_LEFT: //left arrow
		  if (position % 3 != 0) //if you can move left do it
		    {
		      //explained here, same in other cases, with adjustment for movement direction
		      squares[position] = curseDraw::unHighlightWin(squares[position]); //unhighlight the current position
		      --position; //update the position variable
		      squares[position] = curseDraw::highlightWin(squares[position]); //highlight the new position
		    }
		  break; //and break
		case KEY_RIGHT: //right arrow
		  if (position % 3 != 2) //if you can move right do it
		    {
		      squares[position] = curseDraw::unHighlightWin(squares[position]);
		      ++position;
		      squares[position] = curseDraw::highlightWin(squares[position]);
		    }
		  break;
		case KEY_UP: //up arrow
		  if (position/3 != 0) //if you can move up do it
		    {
		      squares[position] = curseDraw::unHighlightWin(squares[position]);
		      position -= 3;
		      squares[position] = curseDraw::highlightWin(squares[position]);
		    }
		  break;
		case KEY_DOWN: //down arrow
		  if (position/3 != 2) //if you can move down do it
		    {
		      squares[position] = curseDraw::unHighlightWin(squares[position]);
		      position += 3;
		      squares[position] = curseDraw::highlightWin(squares[position]);
		    }
		  break;
		case '\n': case KEY_HOME: //KEY_ENTER is not the same as NL character, for some godforsaken reason, also included home character
		  play = position; //update the play variable
		  break;
		default: //in the default case do absolutely nothing
		  break;
		}
	    }
	  squares[position] = curseDraw::unHighlightWin(squares[position]); //unhighlight the selected square
	  
	}
      game.replace(play, 1, 1, p1); //update the board with whatever move was made by which play

      //redraw the selected square with the correct symbol
      if (game[play] == 'x')
	squares[play] = curseDraw::drawX(squares[play]);
      else if (game[play] == 'o')
	squares[play] = curseDraw::drawO(squares[play]);

      //swap the player variables for the next turn
      t = p1;
      p1 = p2;
      p2 = t;
      turn = !turn; //change the turn to the other player
    }
  switch (t) //displaying the winner
    {
      case ' ':
	wprintw(messages, "\nDRAW");
	break;
      case 'x':
	wprintw(messages, "\nX WINS");
	break;
      case 'o':
	wprintw(messages, "\nO WINS");
	break;
      default:
	break;
      }
  wrefresh(messages); //refresh the message window to display the winner
    
  getch(); //getch to avoid spontaneous closing
  endwin(); //end curses mode

  return 0;
}

bool validPlay(int play, vector<int> validPlays) //validity check
{
  for (auto it = validPlays.begin(); it != validPlays.end(); ++it)
    {
      if (play == *it) //if the play equals a valid move
	return (true); //return true
    }
  return (false); //return false if nothing is found
}
