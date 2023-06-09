    #include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
class gameMechanics;
class userInfo;
class gameElements
{
    char map[10][10];
    int snake[100][3]; //first array stores blocks of snake (maximum = 100), second stores coordinates & direction of each block [0] for y, [1] for x, [2] for side towards which the block points
    bool gameEnd = false;
    int fruit[2];     //y[0] and x[1] coordinates for fruit
    int lastBlock[2][3]; //stores the coordinates of last block, [0] for last, [1] for sencond last

    int fruitNum = 0;
    int blockNum = 3;   //initial number of blocks of snake
    float incTime = 16.6; //time between each loop (in ms)
    int Life = 4;
    public:
    friend class gameMechanics;

    void displayLast_block()
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "Last Block " << i << "Y: " << lastBlock[i][0] << " X: " << lastBlock[i][1] << " D:" << lastBlock[i][2]<< endl;
        }
    }
    void getDirection(); //from keyboards interrupts
    void displaySnake(); //display coordinates of each block of snake
    void initializeSnake(); //initializes snake to a garbage value more than 10
    void initializeMap(); //initializes map to ' ' after every loop
    void store_lastBlock(); //stores the x,y coordinates and direction of last two blocks
    void mapSnake();  // projects the snake array into the map array
    void displayMap();// display map array
    void generateFruit();
    bool getLife(){if(Life <0){return false;}else{return true;}}
    void initializeLife(){Life = 4;}
};
class gameMechanics : public gameElements
{
    public:
    void gameStart(); //Generate random side, and then a random number from that side. Direction will be perpendicular to that side
    void snakeMotion();    //while loop with increments the graphics according to the given direction
    void checkLose();  //checks the Game variable after ever loop
    void operator = (const gameMechanics&); //reverses the snake by two two frames


};
void gameElements :: getDirection()
{
    char option;
    if(_kbhit())
    {
        
        switch (_getch())
        {
            case 'i': case 'w': { if (snake[0][2] != 2){snake[0][2] = 0;} break; }
            case 'j': case 'a': { if (snake[0][2] != 3){snake[0][2] = 1;} break; }
            case 'k': case 's': { if (snake[0][2] != 0){snake[0][2] = 2;} break; }
            case 'l': case 'd':{ if (snake[0][2] != 1){snake[0][2] = 3;} break; }
            case 'p': gameEnd = true;
            
        }
    }
}
void gameElements :: displaySnake()
{
    for (int i = 0; i<blockNum; i++)
    {
        cout << "Block " << i ;
        cout << "= Y: " << snake[i][0] << "; X: " << snake[i][1] <<endl;
    }
    cout << endl;
}
void gameElements :: initializeSnake()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            snake[i][j] = 123;
        }
    }
}
void gameElements :: initializeMap()
{
    for (int y = 0 ; y < 10; y++)
    {
        for (int x = 0 ; x < 10 ; x++)
        {  
            
            if (map[y][x] != 'O')
            {
                map[y][x] = ' ';
            }
            
        }
    }
}
void gameElements :: store_lastBlock()
{   
    lastBlock[1][0] = lastBlock[0][0];
    lastBlock[1][1] = lastBlock[0][1];
    lastBlock[1][2] = lastBlock[0][2];
    lastBlock[0][0] = snake[blockNum -1][0];
    lastBlock[0][1] = snake[blockNum -1][1];
    lastBlock[0][2] = snake[blockNum -1][2];
}
void gameElements :: mapSnake()
{   
   
    for (int i = 0 ; i < blockNum; i++)
    {
        char block;
        switch(snake[i][2])
        {
            case 0: block = '^';break;
            case 1: block = '<';break;
            case 2: block = 'v';break;
            case 3: block = '>';break;
        }
        if (snake[i][0] < 10 && snake [i][0] >=0 && snake[i][1] < 10 && snake[i][1] >=0 && map[snake[i][0]][snake[i][1]] != 'O')
        {
            map[snake[i][0]][snake[i][1]] = block;
        }
        else if (map[snake[i][0]][snake[i][1]] == 'O')
        {   
            blockNum++;
            snake[blockNum-1][0] = lastBlock[0][0];
            snake[blockNum-1][1] = lastBlock[0][1];
            snake[blockNum-1][2] = lastBlock[0][2];
            map[snake[i][0]][snake[i][1]] = block;
            fruitNum = 0;
        }
    }    
}
void gameElements :: displayMap()
{   
    int temp = 0;
    if(Life >=0){temp = Life;}
    cout << "  SCORE: " << blockNum - 3 << endl << "  LIVES: " << temp << endl;
    for (int y = 10 ; y >=-1 ; y--)
    {   
        if (y == 10 || y == -1)
        {
            for (int i = 0; i < 7; i++){cout << "# ";}
            cout << endl;
        }
        else
        {
            for (int x = -1 ; x <= 10 ; x++)
            {   
                if (x == 10){cout << " #";}
                else if (x == -1){cout << "#";}
                else 
                {
                    cout << map[y][x];
                }
            }
            cout << endl;
        }
    }
    cout << endl;
}
void gameElements :: generateFruit()
{
    //chacking number of fruits
    for (int y = 0 ; y < 10; y++)
    {
        for (int x = 0 ; x < 10 ; x++)
        {  
            if (map[y][x] == 'O')
            { 
                fruitNum++;
            }
        }
    }
    
    //if there are no fruits
    if (fruitNum == 0)
    { 
        srand(time(0));
        do
        {
            fruit[0] = rand()%10;
            fruit[1] = rand()%10;
        }
        while(map[fruit[0]][fruit[1]] !=' ');
        map[fruit[0]][fruit[1]] = 'O';
    } 
}
void gameMechanics :: gameStart()
{
    /* Side number
        ---0---
       |      |
       1      3
       |      |
        ---2---
    */
    Life = 4;
    blockNum = 3;
    gameEnd = false;
    initializeSnake();
    srand(time(0));
    int side;
    side = rand()%4; //randomly choosing side to start from
    switch(side)
    {  //initializing first block of 
       //           Y                         X                    Block direction         
        case 0:{ snake[0][0] = 9;         snake[0][1] = rand()%10; snake[0][2] = 2;  break;}
        case 1:{ snake[0][0] = rand()%10; snake[0][1] = 0;         snake[0][2] = 3;  break;}
        case 2:{ snake[0][0] = 0;         snake[0][1] = rand()%10; snake[0][2] = 0;  break;}
        case 3:{ snake[0][0] = rand()%10; snake[0][1] = 9;         snake[0][2] = 1;  break;}
    }

}
void gameMechanics :: snakeMotion()
{   
    while (true)
    {   
        getDirection();
        switch (snake[0][2])
        {   
            case 2:
            {
                snake[0][2] = 2;
                for (int i= 0; i < blockNum-1 ; i++)
                {
                    snake[(blockNum -1)-i][0] = snake[(blockNum -2)-i][0];
                    snake[(blockNum -1)-i][1] = snake[(blockNum -2)-i][1];
                    snake[(blockNum -1)-i][2] = snake[(blockNum -2)-i][2];
                }
                snake[0][0] --;
                if (snake[0][0] < 0){snake[0][0] = 9;}
                break;
            }
            case 3:
            {
                snake[0][2] = 3;
                for (int i= 0; i < blockNum-1 ; i++)
                {
                    snake[(blockNum -1)-i][0] = snake[(blockNum -2)-i][0];
                    snake[(blockNum -1)-i][1] = snake[(blockNum -2)-i][1];
                    snake[(blockNum -1)-i][2] = snake[(blockNum -2)-i][2];
                }
                
                snake[0][1] ++;
                if (snake[0][1] > 9){snake[0][1] = 0;}
                break;
            }
            case 0:
            {
                snake[0][2] = 0;
                for (int i= 0; i < blockNum-1 ; i++)
                {
                    snake[(blockNum -1)-i][0] = snake[(blockNum -2)-i][0];
                    snake[(blockNum -1)-i][1] = snake[(blockNum -2)-i][1];
                    snake[(blockNum -1)-i][2] = snake[(blockNum -2)-i][2];
                }
                snake[0][0] ++;
                if (snake[0][0] > 9){snake[0][0] = 0;}
                break;
            }
            case 1:
            {
                snake[0][2] = 1;
                for (int i= 0; i < blockNum-1 ; i++)
                {
                    snake[(blockNum -1)-i][0] = snake[(blockNum -2)-i][0];
                    snake[(blockNum -1)-i][1] = snake[(blockNum -2)-i][1];
                    snake[(blockNum -1)-i][2] = snake[(blockNum -2)-i][2];
                }
                snake[0][1] --; 
                if (snake[0][1] < 0){snake[0][1] = 9;}
                break;
            }
        }
        initializeMap();
        mapSnake();
        generateFruit();

        system("CLS");
        displayMap();
        checkLose();
        if(gameEnd){break;}
        store_lastBlock();
        Sleep(incTime);

        
    }    
}
void gameMechanics :: checkLose()
{
    for (int i = 0; i < blockNum; i++ )
    {
        for (int j = i+1    ; j < blockNum; j++)
        {
            if (snake[i][0] == snake[j][0] && snake[i][1] == snake[j][1])
            {      
                gameEnd = true;
            }
        }
    }
    if (gameEnd)
    {
        cout << "\nGame has ended\nScore = " << blockNum-3;
        if (blockNum-3 > 90) {cout << "\nYou are a snake God\n";}
    }
}
void gameMechanics :: operator = (const gameMechanics& g1)
{   
    srand(time(0));
    this->gameEnd = false;
    this->blockNum = g1.blockNum;
    if (this->Life >= 0){this-> Life = g1.Life-1;}
    
    for (int i = 0; i < blockNum-2; i++)
    {
        this->snake[i][0] = g1.snake[i+2][0];
        this->snake[i][1] = g1.snake[i+2][1];
        this->snake[i][2] = g1.snake[i+2][2];
    }
    for (int i = 0; i <2; i++)
    {
        this->snake[blockNum-1-i][0] = g1.lastBlock[1-i][0];
        this->snake[blockNum-1-i][1] = g1.lastBlock[1-i][1];
        this->snake[blockNum-1-i][2] = g1.lastBlock[1-i][2];
    }
    //changing direction to sideways
    switch (g1.snake[0][2])
    {
        case 2: 
        do
        {
            this->snake[0][2] = rand()%4;
        }
        while(this->snake[0][2] == 0 || this->snake[0][2] == 2);
        break;
        case 3: 
        do
        {
            this->snake[0][2] = rand()%4;
        }
        while(this->snake[0][2] == 1 || this->snake[0][2] == 3);
        break;
        case 0: 
        do
        {
            this->snake[0][2] = rand()%4;
        }
        while(this->snake[0][2] == 2 || this->snake[0][2] == 0);
        break;
        case 1: 
        do
        {
            this->snake[0][2] = rand()%4;
        }
        while(this->snake[0][2] == 3 || this->snake[0][2]== 1);
        break;
    }
    this->initializeMap();
    this->mapSnake();
    this->displayMap();

}
void countDown()
{
    cout << "STARTING IN ";
    for (int i = 3; i > 0; i--)
    {
        cout << i << " ";
        Sleep(800);
    }
    cout << endl;
}
int main()
{
    //gameMechanics* g = new gameMechanics[1];
    gameMechanics g1; 
    gameMechanics g2;
    char loopOption;
    int gameOption = 1, gameCount = 1;
    cout << "*****CONTROLS*****\n\n\t^\n\tW\n<A\t\tD>\n\tS\n\tv\n\n";
    cout << "Do you want to start?(y/n)"; cin >> loopOption;
    while (loopOption == 'y')
    {   if (gameOption == 1) 
        {   
            g1.initializeLife();
            g2.initializeLife();
            countDown();
            g1.gameStart();
            g1.snakeMotion();
            gameCount = 1;
        }
        cout << "\n1-Play Again\n2-Revive \n3-Exit \n4-Show Controls\nEnter option: "; cin >> gameOption;
        switch (gameOption)
        {
            case 1: loopOption = 'y'; break;
            case 2:
            { 
                //alternatingly using the = overloaded operator
                if (gameCount%2 != 0)
                {  
                    g2 = g1;
                    if (g2.getLife() == true)
                    {
                        countDown();
                        g2.snakeMotion();
                    }
                    else 
                    {
                        cout << "You ran out of Lives\n";
                    }
                    
                }
                else
                {   
                    g1 = g2;
                    if (g1.getLife() == true)
                    {
                        countDown();
                        g1.snakeMotion();
                    }
                    else 
                    {
                        cout << "You ran out of Lives\n";
                    }
                }
                gameCount ++;
                break;
            }
            case 3: loopOption = 'n'; break;
            case 4: cout << "*****CONTROLS*****\n\n\t^\n\tW\n<A\t\tD>\n\tS\n\tv\n\n"; break;
        }
    }

    return 0;
}