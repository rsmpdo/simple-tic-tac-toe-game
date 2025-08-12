//---Tic Toc Toe game---

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defined constants:

#define BOARDSIZE 3
#define P_HUMAN 0
#define P_COMPUTER 1
#define GO_NO 0
#define GO_YES 1
#define DRAW_YES 1
#define DRAW_NO 0
#define WIN_YES 1
#define WIN_NO 0
#define DIFF_EASY 0
#define DIFF_HARD 1

// Global variables: {not only inside main() , available throughout the program. Can be accessed by any function below.}

char board[BOARDSIZE][BOARDSIZE];


// Function prototype:

void init_board();
void display_board();
int who2play(int nof_players);
int choose_diff();
int draw();
int win();
int row_win();
int column_win();
int diagonal_win();
int h_check_status();
int com_check_status();
void block_move();
void hmove();
void cmove();
void play_ttt();


int main()
{
   char c;

   srand(time(NULL));

   do
    {
    printf("\n---Welcome to the TIC TOC TOE game---\n\n");
    play_ttt();

    printf("\nPress press 'Q' to end the game and enter any other character to play again...\n");
    scanf(" %c", &c);   // space before %c to avoid scanning newline character

    /*switch(c)
     {
        case 'Q': printf("\n---Thank you for playing---\n"); exit(0); break;
        default : printf("\n---Welcome to the TIC TOC TOE game---\n\n"); play_ttt(); break;
     } */
    }
   while(c!='Q');

   printf("\n---Thank you for playing---\n\n");

   return 0;
}

int choose_diff()
{
    char level;
    int diff;
    printf("Choose difficulty (E- easy , H- hard):\n");
    scanf(" %c", &level);   // space before %c to avoid scanning newline character

    switch(level)
    {
    case 'E': return diff= DIFF_EASY; break;

    case 'H': return diff = DIFF_HARD; break;

    default: printf ("\nInvalid input!\n\n");choose_diff(); break;

    }
}

void init_board()
{
    int i,j;
    for(i=0;i<BOARDSIZE;i++){for(j=0;j<BOARDSIZE;j++){board[i][j]=' ';}}
}

void display_board()
{
    printf("\n  | 1| 2| 3 ");
    printf("\n------------");
    printf("\n 1| %c| %c| %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n------------");
    printf("\n 2| %c| %c| %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n------------");
    printf("\n 3| %c| %c| %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");
}

int who2play(int nof_players)
{
    //srand(time(NULL));
    return rand()%2;  // generate random numbers of modulus 2 : between 0-1
}

void hmove()
{ int x,y;
   do
   {
       printf("\nYour Move! Enter Coordinates (x, y):\n");
       scanf("%d %d", &x, &y);

       if (x < 1 || x > 3 || y < 1 || y > 3)
        {
            printf("Invalid coordinates! Please enter values between 1 and 3.\n");
        }

       if(board[x-1][y-1]=='X' || board[x-1][y-1]=='O')
       {
           printf("\nWrong Move!\n");
       }
   }
   while( x<1 || x>3 || y<1 || y>3 || board[x-1][y-1] !=' ');

    board[x-1][y-1]='X';
    display_board();
}

void block_move()
{
    int x,y,i;
    x=0; y=0;

    for (int i = 0; i < BOARDSIZE; i++)
    {
        //column block
        if (board[0][i]=='X' && board[1][i]=='X' && board[2][i]==' ')
        {
            x= 2;
            y= i;
            break;
        }
        else if (board[1][i]=='X' && board[2][i]=='X' && board[0][i]==' ')
        {
             x= 0;
             y= i;
             break;
        }

        //row block
        else if (board[i][0]=='X' && board[i][1]=='X' && board[i][2]==' ')
        {
            x= i;
            y= 2;
            break;
        }
        else if (board[i][1]=='X' && board[i][2]=='X' && board[i][0]==' ')
        {
            x= i;
            y= 0;
            break;
        }
    }
        // Diagonal blocks
        if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' ')
        {
            x=2;
            y=2;
        }
        else if (board[2][2] == 'X' && board[1][1] == 'X' && board[0][0] == ' ')
        {
            x=0;
            y=0;
        }
        else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == ' ')
        {
            x=2;
            y=0;
        }
        else if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == ' ')
        {
            x=0;
            y=2;
        }

        // if no block needed
        else
        {
             do
         {
           x= rand() %3;
           y= rand() %3;   // generate random numbers of modulus 3 : between 0-2

         }
        while( board[x][y] !=' ');
        }

   if( board[x][y] ==' ')
        {
            board[x][y]='O';
            display_board();
        }
}

void cmove(int diff)
{
    int x,y;

    printf("\nComputer Move!\n");
    if (diff==DIFF_EASY)
{
    do
     {
       x= rand() %3;
       y= rand() %3;   // generate random numbers of modulus 3 : between 0-2

    }
    while( board[x][y] !=' ');

    if( board[x][y] ==' ')
    {
        board[x][y]='O';
        display_board();
    }
}
    else if(diff==DIFF_HARD)
{
    block_move();
}


}

int win()
{
    int status = WIN_NO;

                if(column_win() || row_win() || diagonal_win())
                {
                    status = WIN_YES;
                }

    return status;
}

int draw()
{
    int status = DRAW_YES;
    int i,j;
    for(i=0;i<BOARDSIZE;i++)
      {
          for(j=0;j<BOARDSIZE;j++)
            {
                if(board[i][j]==' ')
                {
                    status = DRAW_NO;
                    break;
                }
            }
      }
    return status;
}

int row_win()
{
    int i;
    int row_win_status=WIN_NO;
    for(i=0;i<BOARDSIZE;i++)
      {
        if (board [i][0]!=' ' && board[i][0]==board[i][1] && board[i][0]==board[i][2])
        {
            row_win_status=WIN_YES;
        }
      }
    return row_win_status;
}

int column_win()
{
     int i;
    int col_win_status=WIN_NO;
    for(i=0;i<BOARDSIZE;i++)
      {
        if (board [0][i]!=' ' && board[0][i]==board[1][i] && board[0][i]==board[2][i])
        {
            col_win_status=WIN_YES;
        }
      }
    return col_win_status;
}

int diagonal_win()
{
    int diag_win_status=WIN_NO;

          if ((board[0][0]!=' ' && board[0][0]==board[1][1] && board[0][0]==board[2][2]) ||
             (board[0][2]!=' ' && board[0][2]==board[1][1] && board[0][2]==board[2][0]))
        {
            diag_win_status=WIN_YES;
        }

    return diag_win_status;
}

int h_check_status()
{
    int player,gameover= GO_NO;

     if (win())
                {
                    printf("\nYou Win !!!\n");
                    gameover = GO_YES;
                }
                else if (draw())
                {
                    printf("\nDraw !!!\n");
                    gameover = GO_YES;
                }
        return gameover;
}

int com_check_status()
{
    int player,gameover= GO_NO;

    if (win())
                {
                    printf("\nYou Lost !!!\n");
                    gameover = GO_YES;
                }
                else if (draw())
                {
                    printf("\nDraw !!!\n");
                    gameover = GO_YES;
                }
        return gameover;
}

void play_ttt()
{
    int player;
    int gameover;
    int diff;

    diff= choose_diff();
    init_board();
    display_board();
    player = who2play(2);

    gameover = GO_NO;

    do
    {
        switch(player)
        {
            case P_HUMAN:
                hmove();
                gameover= h_check_status();
                if(gameover==GO_NO)
                {
                    player = P_COMPUTER;
                }
                 break;

            case P_COMPUTER:
                cmove(diff);
                gameover= com_check_status();
                if(gameover==GO_NO)
                {
                    player = P_HUMAN;
                }
                 break;

        }
    }
    while(gameover==GO_NO);
}




/* Extra notes :-


//fflush(stdin);  // to remove repetition caused by next line character


2D array :-  int[5][10];
                x[2][1]=4;

Can't input 2d array as a parameter just like an array to a function. you need to specify the column. Better use 2d array as global variable.

int x=srand(time(NULL));  // srand() - start random  // time() included in in time.h library
   int i;
   i=x;
   while(i<100)
    {
        printf("%d ", rand());   // rand() - to get random numbers
        i++;
    }

*/
