/*
 * Griffin Bruno
 * draw.cpp : defines functions used to draw a tictactoe game
 */
#include <ncurses.h>
#include <string>
#include "draw.hpp"


namespace curseDraw
{
  WINDOW *highlightWin(WINDOW *local_win) //highlight the provided window
    {
      init_pair(2, COLOR_RED, COLOR_BLACK); //create a color pairing
      wattron(local_win, COLOR_PAIR(2)); //turn the pairing on
      int row, col; //get the row and col count for the provided window
      getmaxyx(local_win, row, col);
      box(local_win, ' ', ' '); //create a box, which has ' ' for sides, and visible corner pieces
      wrefresh(local_win); //refresh the window
      wattroff(local_win, COLOR_PAIR(2)); //turn off the color
      return local_win; //return the window
    }
  WINDOW *unHighlightWin(WINDOW *local_win) //unhighlight the provided window
    {
      wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); //set all border characters to ' '
      wrefresh(local_win); //refresh
      return (local_win); //return the window
    }

  void destroyWin(WINDOW *local_win) //used for deleting a window, not used in main function, not particularly great as a method
    {
      wborder(local_win, ' ',' ',' ',' ',' ',' ',' ',' '); //blank out the border
      wrefresh(local_win); //refresh to display border changes
      delwin(local_win); //delete window
    }

  WINDOW *drawBoard(bool bAdjust, int adjust, int displace) //draw the game board
    {
      WINDOW *local_win; //create a window to work with
      init_pair(1, COLOR_WHITE, COLOR_WHITE); //create a color pair
      local_win = newwin( //initialize the window with the provided adjustments
			 adjust,
			 adjust,
			 (bAdjust ? 0 : displace),
			 (bAdjust ? displace : 0));

      wattron(local_win, COLOR_PAIR(1)); //turn the color on
      for (int i = 0; i < adjust; ++i) //going through the rows of the window
	{
	  if (i == (adjust/3) || i == (((adjust*2)/3))) //if at a third... 
	    {
	      for (int j = 0; j < adjust; ++j) //draw a bar across the window row
		mvwaddch(local_win, i, j, '#');
	    }
	  else
	    {
	      //draw the vertical bar at the correct column in the row
	      mvwaddch(local_win, i, adjust / 3, '#'); 
	      mvwaddch(local_win, i, (adjust*2) / 3, '#');
	    }
	}
      wattroff(local_win, COLOR_PAIR(1)); //turn off the color

      wrefresh(local_win); //refresh the window
      return (local_win); //return the window

    }

  WINDOW *drawX(WINDOW *local_win) //drawing an x
    {
      //the window provided is assumed to be a square, and given the construction of the board, it will be
      int row, col;
      getmaxyx(local_win, row, col); //get the rows and cols
      for (int i = 0; i < (row - 1); ++i) //for each row - 1, so it doesn't clip into the board
	{
	  //add an 'x' to the i position of the i row, and its opposing position on the same row
	  mvwaddch(local_win, i, i, 'x'); 
	  mvwaddch(local_win, i, (row - 1) - i, 'x');
	}
      wrefresh(local_win); //refresh the window
      return (local_win); //return the window
    }

  WINDOW *drawO(WINDOW *local_win) //drawing an o
    {
      //as with x, square window is assumed
      int row, col; 
      getmaxyx(local_win, row, col); //get the rows and cols
      for (int i = 0; i < (row-1)/2; ++i) //for half the rows - 1
	{
	  if ((row - 1)/2 - i != (row -1)/2 + i)
	    {
	      //essentially, exactly what was done in x, but translated up, with wrap around to the bottom
	      mvwaddch(local_win, i, (row - 1)/2 - i, 'o');
	      mvwaddch(local_win, i, (row - 1)/2 + i, 'o');
	      mvwaddch(local_win, row - (i + 1), (row - 1)/2 - i, 'o');
	      mvwaddch(local_win, row - (i + 1), (row - 1)/2 + i, 'o');
	    }
	}
      wrefresh(local_win); //refresh the window
      return (local_win); //return the window
    }
}

class Drawing
{
  struct Cell
  {
    char state;
  };
  
  struct Board
  {
    Cell board[9];
  };

};
