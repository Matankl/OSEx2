// TODO
// make sure the imput contains all the numbers in the range of 1-9 and every is used only and at most once
// make sure the input is not too long or too short (9 characters)

#include <iostream>
#include <string>

#define BOARD_SIZE 3
#define INPUT_SIZE 9
#define PLAYER 1
#define ALIEN 2

int main(int argc, char const *argv[]){

    //make sure only one argument is passed
    if (argc != 2){
        std::cout << "Please enter the input and just the input" << std::endl;
        return 1;
    }
    
    //get the input
    const char *input = argv[1];
    // check if the input is the right size
    if (input.length() != INPUT_SIZE){
        std::cout << "The input is not the right size" << std::endl;
        return 1;
    }

    // check if the input contains all the numbers in the range of 1-9 and every is used only and at most once
    // the check is done by using a boolean array of size 9 so making sure that the input contais all the range of 1-9 is made by the pigeonhole principle
    bool numbers[BOARD_SIZE] = {false};
    for (int i = 0; i < INPUT_SIZE; i++){
    
        if (input[i] < '1' || input[i] > '9'){
            std::cout << "The input contains a digite not in the range of 1-9" << std::endl;
            return 1;
        }

            int num = input[i] - '0';
        if (numbers[num - 1]){
            std::cout << "The input contains a number more than once" << std::endl;
            return 1;
        }
        numbers[num - 1] = true;
    }



    //TTT TODO
    //method to pick the aliens move 
    //setBoard method to set the board by the input of the player or the alien
    //method to check if the game is over that returns 0 if the game is not over, 1 if the player won, 2 if the alien won, 3 if it is a tie
    //method to print the board
    //method to print the result of the game

    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    gameStatus = 0;
    int alienIndex = 0;

    while (gameStatus == 0){
        //alien move
        moveMade = makeMove(board, ALIEN, (int)input[alienIndex]);
        while(!moveMade){
            alienIndex++;
            moveMade = makeMove(board, ALIEN, (int)input[alienIndex]);
        }
        alienIndex++;
        moveMade = false;

        //check if the game is over
        //player move
        std::cout << "Enter your move: ";
        int playerMove;
        std::cin >> playerMove;
        moveMade = makeMove(board, PLAYER, playerMove);
        while(!moveMade){
            std::cout << "invalid move, enter a valid move: ";
            std::cin >> playerMove;
            moveMade = makeMove(board, PLAYER, playerMove);
        }
        //check if the game is over
    }


        
    






    return 0;
}

  bool makeMove(int board[BOARD_SIZE][BOARD_SIZE], int player, int move){

    }
