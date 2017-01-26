/*
 * Griffin Bruno
 * minimax.cpp : defines functions used by the AI and in ending the game loop
 */
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include "minimax.hpp"

using std::vector;
using std::string;


namespace minimax
{
  vector<int> getAvailableMove (string game) //getting available moves
  {
    vector<int> moves; //create a vector to hold the moves
    int size = game.size(); //get the size
    for (int i = 0; i < size; ++i) //go through each character in game
      {
        if (game[i] == ' ') //if the character is a space
          moves.push_back(i); //push the index onto the available moves
      }
    return (moves); //return moves
  }

  bool gameOver (string game, char &winner) //is the game over. using a reference char to return the winner as well
  {
    for (int i = 0; i < 3; ++i)
      {
        int h = i*3; //h is for checking the horizontals
        if (game[h] != ' ' && //make sure it is not a space character
            game[h] == game[h+1] &&
            game[h] == game[h+2])
          { //if it is a horizontal
            winner = game[h]; //set the winner amd return true
            return (true);
          }
        if (game[i] != ' ' && //check the vertical
            game[i] == game[i+3] &&
            game[i] == game[i+6])
          {
            winner = game[i]; //set the winner and return true
            return (true);
          }
      }

    if (game [0] != ' ' && //check the left => right diagonal
        game[0] == game[4] &&
        game[0] == game[8])
      {
        winner = game[0]; //set winner and return true
        return (true);
      }
    else if (game[2] != ' ' && //check the right => left diagonal
             game[2] == game[4] &&
             game[2] == game[6])
      {
        winner = game[2]; //set winner and return true
        return (true);
      }
    else //there was no winner
      {
        winner = ' '; //set the winner
        for (int i = 0; i < 9; ++i) //check that the board has another move to make
          {
            if (game[i] == ' ')
              return (false); //if so return false, the game is not over
          }
        return (true); //otherwise return true, the game is a draw
      }
  }

  vector<string> makeMove (string game, char player) //make a move on the current board
  {
    vector<int> moves = getAvailableMove (game); //get the available moves
    vector<string> oPMoves; //declare the string containing the moves made
    string next; //string to hold the current game configuration without touching the current game configuration
    int size = moves.size(); //the number of moves available
    for (int i = 0; i < size; ++i) //for each available move
      {
        next = game; //reset next
        next.replace(moves[i], 1, 1, player); //make that move
        oPMoves.push_back(next); //push that configuration onto the vector
      }

    return oPMoves; //return all move configurations
  }

  int score (char winner, char player, int depth) //scoring the game
  {
    if (winner == player) //if win
      return (10 - depth); //positive score adjusted for depth
    else if (winner == ' ') //if draw
      return (0); //return 0
    else //else it is a loss
      return (-(10 - depth)); //negative score adjusted for depth
  }

  //I adapted it to use any two characters, not just x and o
  int minimax (string game, char p1, char p2, int depth, bool turn)
  { 
    char winner; //winner variable
    if (gameOver (game, winner)) //if the game is over in that move
      {
        return score(winner, p1, depth); //return the score
      }

    vector<string> moves = makeMove(game, turn ? p1 : p2); //get the new moves
    vector<int> scores;                                    //create a vector to hold the scores for this level
    
    for (auto it = moves.begin(); it != moves.end(); ++it)  //populate the scores vector
      {
        scores.push_back((minimax(*it, p1, p2, depth+1, !(turn)))); //turn varaible negated to signify switching of turns, and depth increased
      }
    
    if (depth == 0) //if the depth is zero (top level of the minimax)
      {
        int temp = 0; //temporary holder for index
        int tempscore = 0; //temporary holder for score
        int size = scores.size(); //get the size (would use iterator, but the index is needed at this point, not the score)
        for (int i = 0; i < size; ++i) //find the highest score
          {
            if (scores[tempscore] <= scores[i])
              {
                temp = getAvailableMove(game)[i];
                tempscore = i;
              }
          }
        //return the index of the highest scoring play
        return (temp);
      }
    //otherwise, if not the top level of the algorithm
    return (getMinMax (scores, turn)); //return the min or max score from the scores vector
  }
  
  int getMinMax (vector<int> scores, bool mode) //return the min or max score
  {
    //from the algorithm library
    //returns an iterator pointing to the max_element/min_element between the provided begin and end vector
    vector<int>::iterator result = (
                                    mode ? //if the mode is true, return max, else, return min
                                    std::max_element(scores.begin(), scores.end()) :
                                    std::min_element(scores.begin(), scores.end())
                                    );
                                    
    return *result; //return the dereferenced pointer value
  }
}
