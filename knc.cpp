#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

using namespace std;

// 0 = blank
// 1 = knot
// 2 = cross
const int esc=27;

int b[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int turns=0;
int token=0, comp=0;
int hm=0;

void displayboard();
void play();
void reset();

void intro()
{
	int err=1;
	cout << "WELCOME TO XOXO\n\n";
	char ch;
	while(err)
	{
		cout << "Press 'X' key to be X or 'O' key to be O\n";
		cout << "Remember, X always starts first.\n\n";
		ch=getch();
		cout << ch << endl;
		if (ch=='0' || ch=='o')
		{
			token=1;
			comp=2;
			err=0;
		}
		else if (ch=='x')
		{
			token = 2;
			comp = 1;
			err = 0;
		}
		else cout << "INVALID SELECTION\n";
	}	
	cout << "Press A to play against a smart bot, or anything else to play against a dumb bot\n";
	ch = getch();
	cout << ch << endl;
	if (ch=='a')
		{
			hm=1;
			cout << "Good Luck.\n";
		}
	else cout << "Coward.\n";
}

void turn()
{
	int i=0, j=0;
	char ch;
	int err=1;
	cout << "\nYOUR TURN\n";
	while (err)
	{
		cout << "ENTER ROW :-";
		ch = getch();
		i = ch - '0';
		cout << i;
	
		cout << "\nENTER COLLUMN :-";
		ch = getch();
		j = ch - '0';
		cout << j << endl;
		
		if (i>2 || i<0 || j>2 || j<0)
			cout << "INVALID\n\n";
		else if (b[i][j]!=0)
			cout << "THAT SPACE IS OCCUPIED\n\n";
		else
		{
			b[i][j] = token;
			err=0;
			turns++;
			cout << "YOU PLAYED AT " << i << "," << j << endl;
			displayboard();
		}
	}	
}

void compturn()
{
	int err=1, i=0,j=0;
	while(err)
	{
		i=rand() % 3;
		j=rand() % 3;
		//cout << i << j;
		
		if (b[i][j]==0)
		{
			err=0;
			b[i][j]=comp;
			cout << "\n\nCOMPUTER PLAYED AT " << i << "," << j << endl;
			turns++;
			displayboard();
		}
	}
}

//AI

void ai();

void displayboard()
{
	cout << endl;
	cout << "        0  1  2 " << endl << endl;
	for (int i=0; i<3; i++)
	{
		cout << "     " << i << " ";
		for (int j=0; j<3; j++)
		{
			if (b[i][j] == 1)
				cout << " 0 ";
			else if (b[i][j]==2)
				cout << " X ";
			else 
				cout << " - ";
		}
		cout << endl << endl;
	}	
}

void windisplay()
{
	cout << endl << endl << endl;
	for (int i=0; i<3; i++)
	{
		cout << " || ";
		for (int j=0; j<3; j++)
		{
			if (b[i][j] == 1)
				cout << " 0 ";
			else if (b[i][j]==2)
				cout << " X ";
			else 
				cout << " - ";
		}
		cout << " || ";
		cout << endl << endl;
	}
}

int diagonals()
{
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] > 0)
		return b[0][0];
	else if (b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[2][0] > 0)
		return b[0][2];
	else return 0;
}

int verticals()
{
	for (int i=0; i<3; i++)
	{
		if (b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] > 0)
			{
				return	b[i][0];
			}
	}
	return 0;
}

int horizontals()
{
	for (int i=0; i<3; i++)
	{
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[2][i] > 0)
		{
			return	b[0][i];
		}
		
	}
	return 0;
}

int wincheck()
{	int w;
	w=diagonals();
	if (w>0)
		return w;
	else
		w=verticals();
	if (w>0)
		return w;
	else
		w=horizontals();
	if (w>0)
		return w;
	return  0;	
}

void checker()
{
	char tch, cch, ch;
	if (token==1)
	{
		tch='O';
		cch='X';
	}
	else
	{
		tch='X';
		cch='O';
	}
	int win=0;
	if (turns>=5)
		{
			win=wincheck();
			if(win!=0)
			{
				windisplay();
				turns=10;
				if (win==token)
					cout << "\nYOU WIN AS " << tch << endl << endl; 
				else cout << "\nCOMPUTER WINS AS " << cch << endl << endl;
			}
			
			else if (turns==9)
			{
				windisplay();
				cout << "DRAW\n\n";
			}
			
			if(turns>=9)
			{
				cout << "\nGOOD GAME\nPress ESC to EXIT or ANY OTHER KEY to PLAY AGAIN.\n";
				ch=getch();
				if(ch!=esc)
					play();
			}	
		}	
}

void play()
{
	reset();
	
	displayboard();
	intro();
	
	if (token==1)
	{
		cout << "\n COMPUTER STARTS\n\n";
		if (hm==0)
			compturn();
		else
			ai();
	}
	
	while(turns<9)
	{	
		turn();
		
		checker();
		
		if(turns>9)
			break;
			
		if(hm==0)
			compturn();
		else
			ai();
		
		checker();
		if(turns>9)
		
			break;
			
	}
}

void reset()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			b[i][j]=0;
		}
	}
	turns=0;
	token=0;
	comp=0;
	hm=0;
	
	//random seed
	srand(time(NULL));
}

int main()
{
	play();
	return 0;
}

// AI STARTS HERE - AI STARTS HERE - AI STARTS HERE - AI STARTS HERE

void ai()
{
	int x,y, win=0, err=1, randerr=1;
	
	while(err)
	{

	//checkwin
	if(turns>=3)
	{
	//check horizontals
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<2; j++)
		{
			if (b[i][j]==b[i][j+1] && b[i][j]>0)
			{
				if (j==0 && b[i][2]==0)
				{
					x=i;
					y=2;
					win=1;
					err=0;
					if (b[i][j]==comp)
						break;
				}
				else if (j==1 && b[i][0]==0)
				{
					x=i;
					y=0;
					win=1;
					err=0;
					if (b[i][j]==comp)
						break;
				}
			}
		}
		if (b[i][0]==b[i][2] && b[i][0] > 0)
		{
			if (b[i][1]==0)
			{
				x=i;
				y=1;
				win=1;
				err=0;
				if (b[i][0]==comp)
					break;
			}
		}
	}
	
	//checkverticals
	if(!win)
	{
		for (int j=0; j<3; j++)
		{
			for (int i=0; i<2; i++)
			{
				if (b[i][j]==b[i+1][j] && b[i][j]>0)
				{
					if (i==0 && b[2][j]==0)
					{
						x=2;
						y=j;
						win=1;
						err=0;
						if (b[i][j]==comp)
							break;
					}
					else if (i==1 && b[0][j]==0)
					{
						x=0;
						y=j;
						win=1;
						err=0;
						if (b[i][j]==comp)
							break;
					}
				}
			}
			if (b[0][j]==b[2][j] && b[0][j]>0)
			{
				if(b[1][j]==0)
				{
					x=1;
					y=j;
					win=1;
					err=0;
					if(b[0][j]==comp)
						break;
				}
			}
		}
	}
	
	//checkdiagonals
	if(!win)
	{
		for (int i=0; i<2; i++)
		{
			if (b[i][i] == b[i+1][i+1] && b[i][i] > 0)
			{
				if (i==0 && b[2][2]==0)
				{
					x=2;
					y=2;
					win=1;
					err=0;
					if (b[i][i]==comp)
						break;
				}
				else if(i==1 && b[0][0]==0)
				{
					x=0;
					y=0;
					win=1;
					err=0;
					if (b[i][i]==comp)
						break;
				}
			}
			if (b[i][2-i]==b[i+1][1-i] && b[i][2-i] > 0)
			{
				if (i==0 && b[2][0]==0)
				{
					x=2;
					y=0;
					win=1;
					err=0;
					if(b[0][2]==comp)
						break;
				}
				else if (i==1 && b[0][2] == 0)
				{
					x=0;
					y=2;
					win=1;
					err=0;
					if(b[2][0]==comp)
						break;
				}
			}
		}
		if(b[0][0]==b[2][2] && b[0][0]>0)
		{
			if (b[1][1]==0)
			{
				x=1;
				y=1;
				win=1;
				err=0;
				if(b[0][0]==comp)
					break;
			}
		}
		if(b[0][2]==b[2][0] && b[0][2]>0)
		{
			if (b[1][1]==0)
			{
				x=1;
				y=1;
				win=1;
				err=0;
				if(b[0][2]==comp)
					break;
			}
		}
	}
	}
	
	//dirtytactics
	if(!win && turns==1)
	{
		if(comp==1)
		{
			if(b[1][1]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	if(!win && turns==3)
	{
		if(comp==1)
		{
			if(b[1][1]==comp)
			{
				if((b[0][0]==token && b[2][2]==token) || (b[0][2]==token && b[2][0]==token))
				{
					x=0;
					y=1;
					err=0;
					win=1;
				}
			}
			else if(b[1][1]==token && b[2][2]==token)
			{
				x=2;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	if(!win && comp==2)
	{
		if(turns==2)
		{
			//winner1
			if(b[0][0]==token)
			{
				x=2;
				y=2;
				win=1;
				err=0;
			}
			else if(b[0][2]==token)
			{
				x=2;
				y=0;
				win=1;
				err=0;
			}
			else if(b[2][0]==token)
			{
				x=0;
				y=2;
				win=1;
				err=0;
			}
			else if(b[2][2]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
			
			//winner2
			if(b[0][1]==token || b[1][0]==token)
			{
				x=2;
				y=2;
				win=1;
				err=0;
			}
			else if(b[1][2]==token || b[2][1]==token)
			{
				x=0;
				y=0;
				win=1;
				err=0;
			}
		}
	}
	
	//randomizer, for now
	if(!win)
	{
		if(b[1][1]==0)
		{
			x=1;
			y=1;
			err=0;
		}
		else
		
			while(randerr)
			{
				x=rand() % 3;
				y= rand() % 3;
				
				if (b[x][y]==0)
				{
					randerr=0;
					err=0;
				}	
			}	
	}
	
	b[x][y]=comp;
	turns++;
	cout << "THE COMPUTER PLAYED AT " << x << ", " << y << endl;
	displayboard();
	
	}
	
}
