#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 
#define BOARD_HEIGHT 20 // ┃개수
#define BOARD_WIDTH 10  // ━개수 
#define BOARD_X 4 //보드열x좌표 
#define BOARD_Y 2 //보드행y좌표 
#define CBLOCK_X 13 
#define CBLOCK_Y 2 
#define DELAY 100//지연 
#define RAND 4//난수 
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32 

int static score=0; //게임점수 
int static level=1; //게임레벨
int static speed=180;
int curX,curY; //콘솔커서
int board[BOARD_HEIGHT+1][BOARD_WIDTH+2]={0,}; 
int block[][4][4]={ {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}},{{0,0,1,0}, {0,0,1,0}, {0,1,1,0}, {0,0,0,0}},{{1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0}},{{1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0}},        
                  { {0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0} },   { {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0} },    { {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },    { {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },
                  { {0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0} },   { {0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0} },    { {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0} },    { {0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0} },
                  { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} },   { {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0} },    { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} },    { {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0} },
                  { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },   { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },    { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },    { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
                  { {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },   { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0} },    { {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },   { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0} },
                  { {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} },   { {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }, {   {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} },   { {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }, }; 

void removeCursor(void)
{
  CONSOLE_CURSOR_INFO curInfo; 
  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
  curInfo.bVisible=0;  
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
}

void setCursor(int x, int y)
{
  COORD pos={x,y};   
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

COORD getCursor(void) 
{
  COORD cur;   
  CONSOLE_SCREEN_BUFFER_INFO curInfo; 
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);   
  cur.X=curInfo.dwCursorPosition.X;  
  cur.Y=curInfo.dwCursorPosition.Y;    
  
  return cur;
} //

void showBlock(int rotation);

void showBoard(void)
{
  int x,y;  //중앙보드라인     
  
  for(x=1; x<=BOARD_WIDTH+1; x++)    
  {
    board[BOARD_HEIGHT][x]=1; //board 배열중앙1인식       
    setCursor((BOARD_X)+x*2, BOARD_Y+BOARD_HEIGHT);  //콘솔좌표   
    printf("━);  
           }         //왼쪽보드라인   
           for(y=0; y<BOARD_HEIGHT+1; y++)       
           {            
             board[y][0]=1; //board 배열왼쪽1인식      
             setCursor(BOARD_X, BOARD_Y+y);     
             
             if(y==BOARD_HEIGHT)     
               printf("┗);       
                      else      
                      printf("┃);    
                             }         //오른쪽보드라인      
                             for(y=0; y<BOARD_HEIGHT+1; y++)   
                             {
                               board[y][BOARD_WIDTH+1]=1; //board 배열오른쪽1인식         
                              setCursor(BOARD_X+(BOARD_WIDTH+2)*2, BOARD_Y+y);   
                               
                               if(y==BOARD_HEIGHT)   
                                 printf("┛);   
                                        else      
                                        printf("┃);     
                                               }                  //모서리값값변경     
                                               board[20][0]=1;    
                                               board[20][11]=1;                  //보드판숫자보기      
                                               setCursor(6,2);         
                                               for(y=0; y<=BOARD_HEIGHT; y++)
                                             {         
                                               for(x=0; x<=BOARD_WIDTH+1; x++)
                                               {                      
                                                 setCursor(4+(x*2),2+y);         //         
                                                 printf("%d ",board[y][x]);         //  
                                               }         //      
                                               printf("\n");         //
                                             }   
                                               puts(" ");
                                               }
                                               void initial(int x,int y)
                                               {
                                                 curX=x;      
                                                 curY=y;     
                                                 setCursor(x,y);
                                               } //removeBlock함수작동전벽인or 아닌지확인 
                                               
                                               int detect(int rotation,int move1,int move2)
                                               {
                                                 int x,y;      
                                                 int arrX,arrY; //배열좌표저장     
                                                 
                                                 COORD pos=getCursor();
                                                 arrX=pos.X+move1; 
                                                 arrY=pos.Y+move2;   
                                                 arrX=(arrX/2)-2;
                                                 arrY=arrY-BOARD_Y;
                                                 
                                                 for(y=0; y<4; y++)        
                                                 {
                                                   for(x=0; x<4; x++)     
                                                   {
                                                     if( (block[rotation][y][x]==1) && board[arrY+y][arrX+x]==1)   
                                                       return 1;  //보드와벽돌겹침     
                                                   }       
                                                 }    
                                                 return 0;  //겹치지않음 
                                               }
                                               //벽돌생성
                                               void showBlock(int rotation)
                                               {
                                                 int x,y;      
                                                 COORD cursor=getCursor();   
                                                 int prove;  
                                                 //
                                                 int n=(rotation-1)%4;    
                                                 prove=detect(rotation,0,0);   
                                                 
                                                 if(prove==0)   
                                                 {   
                                                   //콘솔창위치설정배열값에서1은■출력은출력없음      
                                                   for(y=0; y<4; y++)       
                                                   {          
                                                     for(x=0; x<4; x++)        
                                                     {          
                                                       setCursor(cursor.X + (x*2), cursor.Y+ y);        
                                                       
                                                       if(block[rotation][y][x]==1)        
                                                         printf("■);       
                                                                }          
                                                                }     
                                                                setCursor(cursor.X, cursor.Y);       
                                                                }
                                                                }
                                                                void removeBlock(int rotation,int move1,int move2) 
                                                                {
                                                                  int pr;    
                                                                  int x,y; 
                                                                  COORD cursor=getCursor();  
                                                                  pr=detect(rotation,move1,move2);    
                                                                  
                                                                  if(pr==0)   
                                                                  {
                                                                    for(y=0; y<4; y++)
                                                                    {     
                                                                      for(x=0; x<4; x++)     
                                                                      {      
                                                                        setCursor(cursor.X+ (x*2), cursor.Y+y);   
                                                                        
                                                                        if(block[rotation][y][x]==1)    
                                                                          printf(" ");     
                                                                      } 
                                                                    }     
                                                                    
                                                                    setCursor(cursor.X+move1, cursor.Y+move2);      
                                                                  }
                                                                } //블록보드판에서1인식 
                                                                
                                                                void boardConginition(int n,int move1, int move2) 
                                                                {
                                                                  int x1,y1;  
                                                                  COORD pos=getCursor();      
                                                                  int arrX = pos.X + move1;  //콘솔좌표열       
                                                                  int arrY = pos.Y + move2;  //콘솔좌표행        
                                                                  int x,y;         //커서위치정보배열위치정보변경    
                                                                  arrX=arrX/2-2; //콘솔좌표배열열변환값   
                                                                  arrY=arrY-2;     //콘솔좌표배열행변환값    
                                                                  //보드판에서블록이동시1인식    
                                                                  for(y=0; y<4; y++)
                                                                  {         
                                                                    for(x=0; x<4; x++)     
                                                                    {        
                                                                      if(block[n][y][x]==1)     
                                                                      {        
                                                                        board[arrY+y][arrX+x] =1;   
                                                                      }         
                                                                    }    
                                                                  }         return ;
                                                                } //배열블록옮김 
                                                                
                                                                void array_down(int column) 
                                                                {
                                                                int y,x;         
                                                                  //board배열값행다운     
                                                                  for(y=column; y>=0; y--)
                                                                  {      
                                                                    for(x=1; x<=10; x++)        
                                                                    {  
                                                                      board[y][x]=board[y-1][x];   
                                                                    }
                                                                  }         //board배열0행에0삽입     
                                                                  for(x=1; x<=10; x++)
                                                                    board[0][x]=0;   
                                                                  /*board배열1값전체출력*/     
                                                                  for(y=1; y<=19; y++)  
                                                                  {   
                                                                    for(x=1; x<=10; x++)        
                                                                    {
                                                                      setCursor((BOARD_X)+x*2+1, y+BOARD_Y);    
                                                                      
                                                                      if(board[y][x]==1)   
                                                                        printf("■);  
                                                                      else
                                                                        printf("  ");  
                                                                               }
                                                                               }     
                                                                               } //레벨스코어출력 
                                                                               void scoreLevel(void)
                                                                               {
                                                                                 setCursor(40,3);    
                                                                                 printf("★레벨게임클리어★);     
                                                                                        setCursor(40,5);  
                                                                                        printf("레벨\n",level);  
                                                                                        setCursor(40,7);   
                                                                                        printf("점수\n",score); } //레벨스코어계산 
                                                                                        
                                                                                        void countScore(void) 
                                                                                        {
                                                                                          score+=10;    
                                                                                          
                                                                                          if(score%30==0)  
                                                                                          {      
                                                                                            level+=1;       
                                                                                            speed-=30; 
                                                                                          }       
                                                                                          scoreLevel(); 
                                                                                        } /* 1~10까지행의열전체가1로되면블록사라짐         사라지면array_down함수실행*/ 
                                                                                        
                                                                                        void control(void)
                                                                                        {
                                                                                          int i;    
                                                                                          int x,y;      
                                                                                          int z=0;      
                                                                                          //19행부터시작해서1행까지반복        
                                                                                          
                                                                                          for(y=19; y>=1; y--)   
                                                                                          {
                                                                                            //행기준으로4번반복         
                                                                                            for(z=0; z<4; z++)  
                                                                                            {       
                                                                                              i=0;      
                                                                                              //1열부터10열까지증가          
                                                                                              for(x=1; x<11; x++)
                                                                                              {
                                                                                                //행기준         
                                                                                                if(board[y][x]==1)    
                                                                                                {
                                                                                                  i++;     
                                                                                                  //1이10개면행블록삭제     
                                                                                                  if(i==10)  
                                                                                                  {  
                                                                                                    for(x=1; x<11; x++)  
                                                                                                    {        
                                                                                                      setCursor((x+2)*2,y+2); 
                                                                                                      printf("  ");  
                                                                                                    }      
                                                                                                    //행기준으로블록내리기
                                                                                                    countScore();
                                                                                                    array_down(y);   
                                                                                                  }
                                                                                                }
                                                                                              }
                                                                                            }
                                                                                          }
                                                                                        }
                                                                                        
                                                                                        int gameOver(int rotation)
                                                                                        {
                                                                                          if(detect(rotation,0,0))    
                                                                                            return 5; 
                                                                                          //게임끝   
                                                                                          else        
                                                                                            return 0; 
                                                                                        }
                                                                                        
                                                                                        int gameWin(void) 
                                                                                        {
                                                                                          if(level==10)   
                                                                                            return 1; //게임승    
                                                                                          else    
                                                                                            return 0; 
                                                                                        } 
                                                                                        
                                                                                        void moveBlock(void)
                                                                                        {  
                                                                                          int n;    
                                                                                          int kb;   
                                                                                          int prove; 
                                                                                          int winOver;//게임결과        
                                                                                          srand(time(NULL));
                                                                                          int c=2; 
                                                                                          //게임시작끝     
                                                                                          
                                                                                          while(1)   
                                                                                          {
                                                                                            initial(CBLOCK_X,CBLOCK_Y); //블록생성위치좌표       
                                                                                            n=(rand()%RAND)*4;//난수생성                 
                                                                                            n=rand()%RAND;        
                                                                                            n=rand()%7;//블록모양결정       
                                                                                            n = n * 4;  
                                                                                            //
                                                                                            n = 6;      
                                                                                            
                                                                                            if(gameWin())       
                                                                                            { 
                                                                                              setCursor(35,20);    
                                                                                              printf("GAME WIN");   
                                                                                              getchar();  
                                                                                              exit(1);      
                                                                                            }       
                                                                                            
                                                                                            if(gameOver(n))  
                                                                                              break   
                                                                                              //블록한개위밑이동       
                                                                                              
                                                                                              while(1)   
                                                                                              {
                                                                                                int ww=0;    
                                                                                                int var; 
                                                                                                int k=0; 
                                                                                                int tmp;  
                                                                                                //블록아래로이동     
                                                                                                while(!_kbhit())    
                                                                                                {
                                                                                                  //블록쇼      
                                                                                                  showBlock(n);    
                                                                                                  //딜레이타임     
                                                                                                  Sleep(DELAY+speed);
                                                                                                  //아래이동시1있느지확인      
                                                                                                  if(detect(n,0,1)==1) 
                                                                                                  {       
                                                                                                    ww=1;    
                                                                                                    boardConginition(n,0,0);//보드벽돌배열1추가    
                                                                                                    control();  
                                                                                                    break  
                                                                                                  }
                                                                                                  removeBlock(n,0,1);  //board배열+1행     
                                                                                                }           
                                                                                                //detect함수에서배열값1발견시중지       
                                                                                                if(ww==1)     
                                                                                                  break      
                                                                                                  kb=_getch();     
                                                                                                //방향키        
                                                                                                switch(kb)
                                                                                                {
                                                                                                  case LEFT:    
                                                                                                    removeBlock(n,-2,0); 
                                                                                                    showBlock(n);    
                                                                                                    break      
                                                                                                      case RIGHT:     
                                                                                                    removeBlock(n,2,0);    
                                                                                                    showBlock(n);     
                                                                                                    break      
                                                                                                      case UP:      
                                                                                                    // 첫수를구한다       
                                                                                                    k = n / 4;     
                                                                                                    k *= 4;         
                                                                                                    // 다음수가끝수이하인가     
                                                                                                    if((n+1) <= (k+3))    
                                                                                                    {       
                                                                                                      k = n + 1;     
                                                                                                    }      
                                                                                                    prove=detect(k,0,0);  
                                                                                                    
                                                                                                    if(prove==0)       
                                                                                                    { 
                                                                                                      removeBlock(n,0,0);
                                                                                                      n = k;      
                                                                                                      showBlock(n);      
                                                                                                      break      
                                                                                                    }   
                                                                                                    break     
                                                                                                      case DOWN:     
                                                                                                    removeBlock(n,0,2);       
                                                                                                    //
                                                                                                    
                                                                                                    showBlock(n); 
                                                                                                    break      
                                                                                                      case SPACE:  
                                                                                                    while(1)     
                                                                                                    {   
                                                                                                      removeBlock(n,0,1);     
                                                                                                      if(detect(n,0,1)==1 )        
                                                                                                      {                     
                                                                                                        showBlock(n);   
                                                                                                        boardConginition(n,0,0);      
                                                                                                        break    
                                                                                                      } 
                                                                                                    } 
                                                                                                }
                                                                                              }
                                                                                          }
                                                                                          setCursor(35,20);   
                                                                                          printf("GAME OVER"); 
                                                                                        }
                                                                                        
                                                                                        int main() 
                                                                                        {
                                                                                          removeCursor(); //커서깜박이제거     
                                                                                          setCursor(2,1); //보드표시시작위치설정      
                                                                                          showBoard(); //보드출력   
                                                                                          scoreLevel();     
                                                                                          moveBlock(); //보드출력움직임      
                                                                                          getchar();
                                                                                        }
                                                                                        
                                                                                        
