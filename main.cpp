#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
/*=======================================================================================================================*/
typedef struct playground{

    void initializePlayground(char field[5][5]) {
    srand(time(NULL)); // necessary to create "real" random numbers
    int relictAmount = 0;

        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){

                int randomNumber = rand() % 10;

                if(randomNumber < 4){
                    field[i][j] = '.';
                }else if(randomNumber < 8){
                    field[i][j] = 'D';
                }else if(randomNumber == 8){
                    field[i][j] = 'R';
                    relictAmount++;
                }else if(randomNumber == 9){
                    field[i][j] = 'F';
                }
            }
        }
//to ensure that there is at least 1 Relict
        if(relictAmount == 0){
            int randomRelict = rand() % 5;
            field[randomRelict][randomRelict] = 'R';
        }

//startposition Player
        field[0][0] = {'P'};
}

    void printPlayground(char field[5][5]){

        for(int i = 0; i < 5; i++){
            for(int y = 0; y < 5; y++){
            cout << field[i][y] << " ";
            }
            cout << endl;
        }
            cout << endl;
    };
} playground;
/*=======================================================================================================================*/
typedef struct player{

    int life = 5;
    int relict = 0;
    int positionX = 0;
    int positionY = 0;

} player;

/*forward decleration=======================================================================================================================*/
void introMessage(player* characterA, int relictsAmount);
int countRelicts(char field[5][5]);
void moveUp(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain);
void moveRight(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain);
void moveDown(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain);
void moveLeft(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain);
void winMessage();
void deathMessage();
/*=======================================================================================================================*/
int main()
{
    playground start;
    player characterA;
    char field[5][5];
    char playerInput = ' ';
    int relictsAmount = 0;
    int inputError = 0;
    int movementErr = 0;
    int lifeSteal = 0;
    int lifeGain = 0;
    int relictGain = 0;

    string inputMsg = "Invalid move! Please use the buttons w,a,s,d to move and x to leave.\n\n";
    string movementError = "Invalid move. You can't leave the Playground.\n\n";
    string lifeStealMsg = "You've fallen into a trap. You lose one life point.\n\n";
    string lifeGainMsg = "You could fortify yourself with fresh spring water. You gain one life point.\n\n";
    string relictGainMsg = "Congratulations you've found an ancient relict! Keep on searching!\n\n";

    start.initializePlayground(field);
    relictsAmount = countRelicts(field);


    while(playerInput != 'x' && characterA.life > 0 && characterA.relict != relictsAmount){

        introMessage(&characterA, relictsAmount);
        start.printPlayground(field);

//Errormessages
        if(movementErr == 1){
            cout << movementError;
        }else if(lifeSteal == 1){
            cout << lifeStealMsg;
        }else if(lifeGain == 1){
            cout << lifeGainMsg;
        }else if(relictGain == 1){
            cout << relictGainMsg;
        }else if(inputError == 1){
            cout << inputMsg;
        }

        movementErr = 0;
        lifeSteal = 0;
        lifeGain = 0;
        relictGain = 0;
        inputError = 0;

//Player input
        cout << "Please enter your direction and press Enter to move: ";
        cin >> playerInput;

        switch(playerInput){

            case 'w':   if(characterA.positionY == 0){
                            movementErr = 1;
                        }else if(characterA.positionY > 0){
                            moveUp(field, &characterA, lifeSteal, lifeGain, relictGain);
                        }
                        break;

            case 'd':   if(characterA.positionX == 4){
                            movementErr = 1;
                        }else if(characterA.positionX < 4){
                            moveRight(field, &characterA, lifeSteal, lifeGain, relictGain);
                        }
                        break;

            case 's':   if(characterA.positionY == 4){
                            movementErr = 1;
                        }else if(characterA.positionY < 4){
                            moveDown(field, &characterA, lifeSteal, lifeGain, relictGain);
                        }
                        break;

            case 'a':   if(characterA.positionX == 0){
                            movementErr = 1;
                        }else if(characterA.positionX > 0){
                            moveLeft(field, &characterA, lifeSteal, lifeGain, relictGain);
                        }
                        break;

            default:    inputError = 1;
        }

        system("cls");

    }

    if(characterA.relict == relictsAmount){
        winMessage();
    }else if(characterA.life == 0){
        deathMessage();
    }



    return 0;
}



/*=======================================================================================================================*/
void introMessage(player* characterA, int relictsAmount){

    cout << "  _____________________________" << endl;
    cout << "  \\                           /" << endl;
    cout << "   \\ Welcome to OASENCRAWLER /" << endl;
    cout << "    \\ step into the unknown /     " << endl;
    cout << "     \\_____________________/\n" << endl;
    cout << "The position of the current Player is marked with a \"P\" symbol." << endl;
    cout << "Please use the Buttons W=(up), A=(left), S=(down), D=(right) to move your Player." << endl;
    cout << "To win the game collect all relicts marked with an 'R'.\n" << endl;
    cout << "But be careful! Fields with an 'D' could be dangerous.\nIf you lost life, try to get to a fountain marked with 'F' to regain life.\n" << endl;
    cout << "If you want to leave the game, please press the X button.\n" << endl;
    cout << "Player Position: " << characterA->positionY << "|" << characterA->positionX << endl;
    cout << "Health: " << characterA->life << endl;
    cout << "Relicts: " << characterA->relict << "/" << relictsAmount << endl << endl;
};
/*=======================================================================================================================*/
void moveUp(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain){

    srand(time(NULL));

        if(field[characterA->positionY-1][characterA->positionX] == 'D'){
            int randomNumber = rand() % 6;
            if(randomNumber == 4){
                characterA->life = characterA->life -1;
                lifeSteal = 1;
            }
        }else if(field[characterA->positionY-1][characterA->positionX] == 'F'){
            characterA->life = characterA->life +1;
            lifeGain = 1;
        }else if(field[characterA->positionY-1][characterA->positionX] == 'R'){
            characterA->relict = characterA->relict +1;
            relictGain = 1;
        }


        field[characterA->positionY-1][characterA->positionX] = 'P';
        field[characterA->positionY][characterA->positionX] = '.';
        characterA->positionY = characterA->positionY -1;

};
/*=======================================================================================================================*/
void moveRight(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain){

    srand(time(NULL));

        if(field[characterA->positionY][characterA->positionX+1] == 'D'){
            int randomNumber = rand() % 6;
            if(randomNumber == 4){
                characterA->life = characterA->life -1;
                lifeSteal = 1;
            }
        }else if(field[characterA->positionY][characterA->positionX+1] == 'F'){
            characterA->life = characterA->life +1;
            lifeGain = 1;
        }else if(field[characterA->positionY][characterA->positionX+1] == 'R'){
            characterA->relict = characterA->relict +1;
            relictGain = 1;
        }


        field[characterA->positionY][characterA->positionX+1] = 'P';
        field[characterA->positionY][characterA->positionX] = '.';
        characterA->positionX = characterA->positionX +1;

};
/*=======================================================================================================================*/
void moveDown(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain){

    srand(time(NULL));

        if(field[characterA->positionY+1][characterA->positionX] == 'D'){
            int randomNumber = rand() % 6;
            if(randomNumber == 4){
                characterA->life = characterA->life -1;
                lifeSteal = 1;
            }
        }else if(field[characterA->positionY+1][characterA->positionX] == 'F'){
            characterA->life = characterA->life +1;
            lifeGain = 1;
        }else if(field[characterA->positionY+1][characterA->positionX] == 'R'){
            characterA->relict = characterA->relict +1;
            relictGain = 1;
        }


        field[characterA->positionY+1][characterA->positionX] = 'P';
        field[characterA->positionY][characterA->positionX] = '.';
        characterA->positionY = characterA->positionY +1;

};
/*=======================================================================================================================*/
void moveLeft(char field[5][5], player* characterA, int& lifeSteal, int& lifeGain, int& relictGain){

    srand(time(NULL));

        if(field[characterA->positionY][characterA->positionX-1] == 'D'){
            int randomNumber = rand() % 6;
            if(randomNumber == 4){
                characterA->life = characterA->life -1;
                lifeSteal = 1;
            }
        }else if(field[characterA->positionY][characterA->positionX-1] == 'F'){
            characterA->life = characterA->life +1;
            lifeGain = 1;
        }else if(field[characterA->positionY][characterA->positionX-1] == 'R'){
            characterA->relict = characterA->relict +1;
            relictGain = 1;
        }


        field[characterA->positionY][characterA->positionX-1] = 'P';
        field[characterA->positionY][characterA->positionX] = '.';
        characterA->positionX = characterA->positionX -1;

};
/*=======================================================================================================================*/
int countRelicts(char field[5][5]){

    int relictsAmount = 0;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){

            if(field[i][j] == 'R'){
                relictsAmount++;
            }

        }
    }

return relictsAmount;
}
/*=======================================================================================================================*/
void winMessage(){

 cout << "           CONGRATULATIONS" << endl;
 cout << "              You won!!!\n" << endl;
 cout << "             ___________" << endl;
 cout << "            '._==_==_=_.'" << endl;
 cout << "            .-\\:      /-." << endl;
 cout << "           | (|:.     |) |" << endl;
 cout << "            '-|:.     |-'" << endl;
 cout << "              \\::.    /" << endl;
 cout << "               '::. .'" << endl;
 cout << "                 ) (" << endl;
 cout << "               _.' '._\n\n" << endl;
 cout << "        Ready for the next Level?\n" << endl;
}
/*=======================================================================================================================*/
void deathMessage(){

 cout << "                GAME OVER" << endl;
 cout << "               You lost!!!\n" << endl;
 cout << "                  _____" << endl;
 cout << "                 /     \\" << endl;
 cout << "                | () () |" << endl;
 cout << "                 \\  ^  /" << endl;
 cout << "                  |||||" << endl;
 cout << "                  |||||\n\n" << endl;
 cout << "        Brave enough to try again?\n" << endl;
}

