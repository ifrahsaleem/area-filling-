#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "stack.h"

using namespace std;

int row, cols;

void findingPathway(char ** & arr, char fchar, int x, int y, DynIntStack & stack, int row, int n)
{ 
	bool other_options = true, occ = false, entered = false, start_pos = false;
	//filling starting position
	arr[x][y] = fchar;

	do
	{
		if ( x!= 0 && y != n-1 && y != 0 && x != row - 1) // if coordinate is not on the boundary
		{
			//north
			if ((arr[x-1][y] != fchar) && (arr[x-1][y] != 'x' && arr[x-1][y] != 'X'))
			{
				stack.push(x, y);
				arr[x-1][y] = fchar;
				x = x - 1;
				entered = true;
			}

			//south
			else if ((arr[x+1][y] != fchar) && (arr[x+1][y] != 'x' && arr[x+1][y] != 'X'))
			{
				stack.push(x, y);
				arr[x+1][y] = fchar;
				x = x + 1;
				entered = true;
			}

			//west
			else if (( arr[x][y-1] != fchar) && (arr[x][y-1] != 'x' && arr[x][y-1] != 'X'))
			{
				stack.push(x, y);
				arr[x][y-1] = fchar;
				y = y - 1;
				entered = true;
			}

			//east
			else if ((arr[x][y+1] != fchar) && (arr[x][y+1] != 'x' && arr[x][y+1] != 'X'))
			{
				stack.push(x, y);
				arr[x][y+1] = fchar;
				y = y + 1;
				entered = true;
			}

			else 
				start_pos = true; // if did not go in any direction // for the case if only one coordinate is being filled which is start coordinate

			if (!stack.isEmpty() & !entered) // if stack is not empty, and didnt go in any direction as well 
			{
				stack.pop(x, y);
				occ = true;
				start_pos = false;
			}
			entered = false;
		}

		else 
			entered = false;

		if (stack.isEmpty() && occ && arr[x][y+1] != ' ' && arr[x][y-1] != ' ' && arr[x+1][y] != ' ' && arr[x-1][y] != ' ') 
			//if stack is emoty, cell is stuck and all other directions are occupied 
			other_options = false; // no other options available, stop the loop 
	}while(other_options & !start_pos);
}

void printPathway(char ** & arr, int row, int n) // simply prints the updated matrix
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << " " ;
		}
		cout << endl;
	}
}

bool RowColsCheck(bool & alph, string & s)
{
	bool check = false;

	if (cin >> row)
	{
		if ( row > 2)
		{
			check = true;
		}
	}

	else
	{
		check = false;
		alph = true;
		cin.clear();
		cin >> s;
	}

	return check;
}

int main()
{
	int r , c;
	bool check1, check2, alph = false;
	DynIntStack stack;
	string s;

	//******************************************************************************************************
	do //checking validity of number of rows
	{
		cout << "Enter the number of rows: " ;
		check1 = RowColsCheck(alph, s);
		if (!check1)
		{
			if (!alph)
				cout << row << " is not valid!" << endl;
			else
				cout << s << " is not valid!" << endl;
		}
	} while(!check1);

	alph = false;
	//******************************************************************************************************
	do //checking validity of number of columns
	{
		cout << "Enter the number of columns: " ;
		check2 = RowColsCheck(alph, s);
		if (!check2)
		{
			if (!alph)
				cout << row << " is not valid!" << endl;
			else 
				cout << s << " is not valid!" << endl;
		}
	} while(!check2);

	ifstream input1;
	string fname;

	//******************************************************************************************************
	//rading the file
	do
	{
		cout << "Please enter file name: " ;
		cin >> fname; // entering file name 
		cout << endl;

		input1.open(fname.c_str()); // opening file 

		if (input1.fail()) // if file fails to open
			cout << endl << "Cannot find a file named " << fname << endl << endl;
	} while(input1.fail());


	//******************************************************************************************************
	//first reading of file to get the number of rows and columns
	string line;
	int row = 1, n = 0;
	char ch;
	while (getline(input1, line))
	{
		if (row == 1)
		{
			while(input1.get(ch) && ch != '\n')
			{
				n++;
			}
		}
		row++;
	}

	input1.clear();
	input1.seekg(0);

	//******************************************************************************************************
	//dynamic allocation of 2D array
	char** arr = new char*[row];
	for(int i=0; i<row; i++) 
	{
		arr[i] = new char[n];
	}
	
	//******************************************************************************************************
	//reading file again to fill the 2D array
	r = 0, c = 0;
	while(input1.get(ch))
	{
		if (ch != '\n')
		{
			if (ch == ' ')
			{
				arr[r][c] = ' ';
			}

			else
				arr[r][c] = ch;
			c++;
		}

		else
		{
			r++;
			c = 0;
		}
	}

	//******************************************************************************************************
	// checking the validity of the coordinates 
	int x = 0, y = 0;
	bool coord = false, occupied = false, terminated = false;
	string h, a;
	do
	{
		cout << "Enter the starting point: " ;
		if (cin >> x) 
		{
			if (cin >> y)
			{
				if ((x > -1 && x <= r) && (y > -1 && y <= c))
				{
					coord = true;
				}
			}

			else 
			{
				cin.clear();
				cin >> h;
			}
		}
				
		else
		{
			cin.clear();
			cin >> h >> a;
		}

		if (!coord)
		{
			cout << "Invalid coordinate!" << endl;
		}

		//check if cell is occupied 
		if (coord && arr[x][y] != ' ')
		{
			cout << "Starting point is already occupied." << endl << "Terminating..." << endl;
			occupied = true;
			terminated = true;
		}
	} while (!coord && !occupied);

	if (!terminated)
	{
		//******************************************************************************************************
		//filling char 

		char fchar;
		bool check = false;
		do
		{
			cout << "Enter the filling char: " ;
			cin >> fchar;

			if (fchar == 'x' || fchar == 'X')
			{
				cout << "Filling char is not valid! " << endl;
			}

			else
				check = true;
		}while(!check);

		//******************************************************************************************************
		//finding pathway

		findingPathway(arr, fchar, x, y, stack, row, n);

		//******************************************************************************************************
		//printing pathway
		cout << endl;

		printPathway(arr, row ,n);
		//******************************************************************************************************
		//end
	}

	for(int i=0; i<row; i++) 
	{
		delete[] arr[i];
	}

	delete [] arr;
	return 0;
}