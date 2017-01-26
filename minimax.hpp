/*
 * Griffin Bruno
 * minimax.hpp : header to minimax.cpp
 */
using std::vector;
using std::string;
namespace minimax
{
  vector<int> getAvailableMove(string game);
  bool gameOver (string game, char &winner);
  vector<string> makeMove (string game, char player);
  int minimax (string game, char p1, char p2, int depth, bool turn);
  int getMinMax (vector<int> scores, bool mode);
}
