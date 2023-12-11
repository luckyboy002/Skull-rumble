#include <iostream>
#include<conio.h>
#include<direct.h>
#include<Windows.h>
#include<time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
bool shieldActive = false;
int shieldDuration = 0;

char car[4][7] = {' ', ' ', '_', '_', '_', ' ', ' ',
                  ' ', '(', '0', ' ', '0', ')', ' ',
                  ' ', ' ', '|', '|', '|', ' ', ' ',
                  ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                  
char enemy[4][6] = {'\\', '^', '^', '^', '^', '/',
                   ' ', ' ', ' ', ' ', ' ', ' ',
                   '<', ' ', 'O', 'O', ' ', '>',
                   ' ', ' ', '|', '|', ' ', ' '};

char shieldModel[4][7] = {' ', '*', ' ', ' ', ' ', '*', ' ',
                          '*', ' ', '*', '*', ' ', ' ', '*',
                          ' ', ' ', ' ', ' ', '*', ' ', ' ',
                          ' ', '*', ' ', ' ', ' ', '*', ' '};
                   
	
int carPos = WIN_WIDTH/2;
int score = 0;

void gotoxy(int x, int y){
	CursorPosition.X =x;
	CursorPosition.Y =y;
	SetConsoleCursorPosition (console ,CursorPosition );
}
void setcursor(bool visible, DWORD size){
if (size == 0)	
    size = 20;
    
CONSOLE_CURSOR_INFO lpCursor;
lpCursor.bVisible =visible;
lpCursor.dwSize = size ;
SetConsoleCursorInfo(console,&lpCursor);

}

void drawBored() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 4; j < 14; j++) {
            gotoxy(4 + j, i);
            cout << "*";
            gotoxy(WIN_WIDTH - j, i);
            cout << "*";
        }
    }
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            if (shieldActive) {
                gotoxy(j + carPos, i + 22);
                cout << (car[i][j] == ' ' ? shieldModel[i][j] : car[i][j]);
            } else {
                gotoxy(j + carPos, i + 22);
                cout << car[i][j];
            }
        }
    }
}
    
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<7; j++){
			gotoxy(j+carPos, i+22); cout<<' ';
		}
	}
}

void genEnemy (int ind){
	enemyX[ind]=17+ rand()%(33);
}	
void drawEnemy(int ind) {
    if (enemyFlag[ind]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                gotoxy(enemyX[ind] + j, enemyY[ind] + i);
                cout << enemy[i][j];
            }
        }
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                gotoxy(enemyX[ind] + j, enemyY[ind] + i);
                cout << ' ';
            }
        }
    }
}

void resetEnemy(int ind){
	 eraseEnemy(ind);
	 enemyY[ind] = 1;
	 genEnemy(ind);
}


void activateShield() {
    shieldActive = true;
    shieldDuration = 100;
}

void deactivateShield() {
    shieldActive = false;
    shieldDuration = 0;
}




int collision (){
	if (shieldActive  && shieldDuration > 0) {
        return 0;
    }

	
	if( enemyY[0]+4>= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
				return 1;
		}
	}
	return 0;
}
void play();

void gameover() {
    Sleep(2000);
    system("cls");
    cout << endl;
    cout << "\t\t-------------------------" << endl;
    cout << "\t\t-------GAME OVER---------" << endl;
    cout << "\t\t-------------------------" << endl << endl;
    char choice;
    cout << "\ningin bermain lagi? (y/t): ";
    choice = getch(); 

    if (choice == 'y' || choice == 'Y') {
    	system("cls");
    	system("COLOR 0");
        play();
        
    } else if (choice == 't' || choice == 'T') {
        system("cls");
        return;
    } else {
        cout << "\nPastikan anda menekan tombol yang benar!"; 
        getch(); 
        gameover(); 
    }
}

void updateScore(){
	gotoxy(WIN_WIDTH + 6,5);cout<<"point: "<<score<<endl;
}
void instructions(){
	system("cls");
	cout<<"tutorial bermain";
	cout<<"\n----------------";
	cout<<"\n Hindari musuh yang datang dari atas";
	cout<<"\n tekan 'a' untuk pindah ke kiri";
	cout<<"\n tekan 'd' untuk pindah ke kanan";
	cout<<"\n tekan apapun untuk kembali ke menu!";
	getch();
}
void play(){
	system("COLOR F");
	int difficultyLevel = 1;
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] =1;
	enemyFlag[1] =0;
	enemyY[0]= enemyY[1] = 1;
	
	system("cls");
	drawBored();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7,2);cout<<"SKULL RUMBLE";
	gotoxy(WIN_WIDTH + 6,4);cout<<"-----------";
	gotoxy(WIN_WIDTH + 6,6);cout<<"-----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Tombol";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------";

	gotoxy(WIN_WIDTH + 2, 14);cout<<"Tombol A - kiri";
    gotoxy(WIN_WIDTH + 2, 15);cout<<"Tombol D - kanan";
    
    
    gotoxy(18, 5);cout<<"   Tekan dong, jangan ngelamun aja:) ";
    getch();
    gotoxy(18, 5);cout<<"                                     ";



  
  while(1){
  	
  	
  	if(kbhit()){
  		char ch = getch();
  		if( ch== 'a' || ch=='A' ){
  			if( carPos > 18 )
  			    carPos -= 4;
	    }
	    if(ch =='d' || ch=='D' ){
	    	if( carPos < 50 )
	    	    carPos += 4;
		}
		 else if (ch == 'x' || ch == 'X') {
                activateShield();
        }
         else if (ch == 'f' || ch == 'F') {
                deactivateShield();
        }
        
        
        if(ch==27){
    	   break;
	    }
    }
    
    if(score >= 0){
    	difficultyLevel + 0.9;
	}
	enemyY[0] += 1 * difficultyLevel;
	enemyY[0] += 1 * difficultyLevel;

    
  drawCar();
  drawEnemy(0);
  drawEnemy(1);
  if( collision() == 1 ){
  	  system("COLOR 4");
  	  gameover();
  	  return;
  }
  Sleep(100);
  eraseCar();
  eraseEnemy(0);
  eraseEnemy(1);
  
  if( enemyY[0] == 10 )
      if( enemyFlag[1] == 0 )
 	      enemyFlag[1] == 1;
 		  
  if( enemyFlag[0] == 1 )
      enemyY[0] += 1;
      
  if( enemyFlag[1] == 1 )
      enemyY[1] += 1;
      
  if( enemyY[0] > SCREEN_HEIGHT-4){
  	  resetEnemy(0);
  	  score++;
  	  updateScore();
    }
  if( enemyY[1] > SCREEN_HEIGHT-4){
  	  resetEnemy(1);
  	  score++;
  	  updateScore();
    }
  }
  }
 


int main()
{  
    
	system("COLOR 02");
	system("cls");
	printf("\e[?251");
	
	SetConsoleCP(473);
	SetConsoleOutputCP(437);
	int bar1 = 177 , bar2 = 219;
	
	
	
	cout<<"\n\n\n\t\t\t\ta                     loading...";
	cout<<"\n\n\n\t\t\t\t";
	
	for(int i = 0; i < 25; i++)
		cout<<(char)bar1;
	
	
	cout<<"\r";
	cout<<"\t\t\t\t";
	for(int i = 0; i < 25; i++){
		cout<<(char)bar2;
		Sleep(150);
	}
	
	cout<<"\n\t\t\t\t"<<(char)1<<"!";
	system("pause");

    setcursor(0,0);
    srand( (unsigned)time(NULL));

    do{ 
        system("COLOR f");
	    system("cls");
	    gotoxy(10,5); cout<<"--------------------------";
	    gotoxy(10,6); cout<<"|      SKULL RUMBLE      |";
	    gotoxy(10,7); cout<<"--------------------------";
	    gotoxy(10,9); cout<<"tekan 1 untuk mulai game ";
	    gotoxy(10,10); cout<<"tekan 2 untuk tutorial bermain game ";
	    gotoxy(10,11); cout<<"tekan 3 untuk keluar game";
	    char op = getch();
	    
	    if( op=='1')play();
	    else if( op=='2') instructions();
	    else if( op=='3') exit(0);
}while(1);

return 0;
}

