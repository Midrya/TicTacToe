/*
 * Griffin Bruno
 * draw.hpp : header file to draw.cpp
 */
namespace curseDraw
{
  WINDOW *highlightWin(WINDOW *local_win);
  WINDOW *unHighlightWin(WINDOW *local_win);
  void destroyWin(WINDOW *local_win);
  WINDOW *drawBoard(bool bAdjust, int adjust, int displace);
  WINDOW *drawX(WINDOW *local_win);
  WINDOW *drawO(WINDOW *local_win);
}
