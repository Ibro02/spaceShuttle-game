// SpaceWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;
enum Positions { UP=-1, DOWN=1 };
const char* line = "\n------------------------------------------------------------------------\n";

#pragma region functions
char* GetArrayOfCharacters(const char* text)
{
	int size = strlen(text) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, text);
	return temp;

	delete[] temp;
	temp = nullptr;
}

#pragma endregion

#pragma region Objects
class Shuttle
{
	char* _lookOfSpaceShuttle;

public:
	Shuttle()
	{

		_lookOfSpaceShuttle = GetArrayOfCharacters(">");
	}
	virtual ~Shuttle()
	{
		delete[] _lookOfSpaceShuttle;
		_lookOfSpaceShuttle = nullptr;
	}

	int GetLength() const {
		return strlen(_lookOfSpaceShuttle) + 1;
	}
	virtual char *GetLookOfShuttle()
	{
		return _lookOfSpaceShuttle;
	}
	virtual char GetCharOfShuttle(int position)
	{
		return _lookOfSpaceShuttle[position];
	}
	friend ostream& operator<< (ostream& COUT,const Shuttle& obj)
	{
		COUT << obj._lookOfSpaceShuttle;
		return COUT;
	}
};
class SpaceShuttle : public Shuttle
{
	Shuttle shuttle;
public:
	SpaceShuttle():Shuttle()
	{

	}

	friend ostream& operator<<(ostream& COUT,const SpaceShuttle&obj)
	{
		COUT << obj.shuttle;
		return COUT;
	}
};

class Player
{
	string _userName;
	int* _points;
public:
	Player()
	{
		_points = new int(0);
	}
	Player(string userName)
	{
		_userName = userName;
	}
	Player(const Player& obj)
	{
		_userName = obj._userName;
		_points = new int(*obj._points);
	}
	~Player()
	{
		_points = nullptr;
	}


	void EnterUserName()
	{
		cout << "Username -> ";
		cin >> _userName;
		if (_userName == " ")
			throw exception("Error -> You have to enter your name!");
	}

	void SavePoints(int points)
	{

		_points = new int(points);
		ofstream enter("highscrores.txt", ios::app);
	if (enter.is_open())
		enter << _userName << " -> " << *_points << endl;
	enter.close();

	}

	void LoadPoints()
	{
		ifstream print("highscrores.txt");
		while (!print.eof())
		{
			string lineS;

			
			getline(print, lineS);
			if(lineS != " ")
			cout << lineS<<line<<endl;

		}
		print.close();
	}
};

#pragma endregion


//template<class T>
mutex mtx;
class Map
{
protected:
	char** _map;
	int* _vertical;
	int* _horizontal; //it refers for length of lines
	int* _positionOfObjectY;
	int* _positionOfObjectX;
	int* _length;
	int _move;
	SpaceShuttle* _shtl;
	
	
	void PrintMap()
	{
		for (size_t i = 0; i < *_vertical; i++)
		{

			for (size_t j = 0; j < *_horizontal; j++)
				if (i == 0 || i == *_vertical - 1)
					_map[i][j] =  '#';
				else if (j == 0)
					_map[i][j] =  '#';
				else if (j == *_horizontal - 1)
					_map[i][j] =  '#';
	
		cout << endl;
		}
		cout << endl;

	}

	void MoveAsteroids()
	{
		
		char** temp = new char*[*_vertical];
	/*	int counter = 0;
		counter++*/;
		for (size_t i = 0; i < *_vertical; i++)
			temp[i] = new char[*_horizontal];
	
		mtx.lock();
		for (size_t i = 0; i < *_vertical; i++)	
			for (size_t j = *_horizontal; j > 0; j--)
				if (j == *_positionOfObjectY && i == *_positionOfObjectX)
					temp[*_positionOfObjectX][*_positionOfObjectY] = *_shtl->GetLookOfShuttle();
				else if (j - 1 != -1)
					temp[i][j - 1] = _map[i][j];
				else if (i == 0)
					delete[] temp[i];	
		
		delete[] _map;
		_map = temp;
		mtx.unlock();
	}

	void CreateAsteroids(int lengthOfAsteroidRain)
	{


		int counter = 0;
		int randPosition = 1 + (rand() % (*_vertical - 2));
		int randLength = 1 + (rand() % (*_horizontal - 2));

		if (!isEnd())
		{
		
			if (lengthOfAsteroidRain < *_horizontal)
			{
			
				lengthOfAsteroidRain++;

				for (size_t i = 0; i < *_vertical; i++)
					for (size_t j = 0; j < lengthOfAsteroidRain; j++)
					{

						
						if (_map[i][*_horizontal - j] != '@')
							_map[i][*_horizontal - j] = ' ';

						//if (lengthOfAsteroidRain % 2 == 0)
							if (i == randPosition)
								_map[i][*_horizontal - 2] = '@';

							

					}
					
				
			}
			thread moveAsteroids(&Map::MoveAsteroids, this);
			moveAsteroids.join();
			//MoveAsteroids();
			counter++;

		}
	


	}
public:
	bool isEnd()
	{
		for (size_t i = 0; i < *_vertical; i++)
			for (size_t j = 0; j < *_horizontal; j++)
				if (_map[*_positionOfObjectX][*_positionOfObjectY + *_length] == '@')
					return true;
		
		return false;
	}
	Map()
	{
		_vertical = new int(50);
		_horizontal = new int(200);

		_map = new char*[*_vertical];
		for (size_t i = 0; i < *_vertical; i++)
			_map[i] = new char[*_horizontal];
	

		for (size_t i = 0; i < *_vertical; i++)
			for (size_t j = 0; j < *_horizontal; j++)
				_map[i][j] = ' ';

		_move = 1;
	//	_positionOfObjectY = nullptr;
		_length = nullptr;
	}
	Map(const SpaceShuttle& obj)
	{
		_vertical = new int(20);
		_horizontal = new int(50);
		_map = new char* [*_vertical];
	
		for (size_t i = 0; i < *_vertical; i++)
			_map[i] = new char[*_horizontal];
		
		_shtl = new SpaceShuttle(obj);
		
		for (size_t i = 0; i < *_vertical; i++)
			for (size_t j = 0; j < *_horizontal; j++)
				_map[i][j] = ' ';

		//	_positionOfObjectY = nullptr;
		_length = new int(_shtl->GetLength());
	}
	void StartPosition(SpaceShuttle& obj, int positionX = 0)
	{
		if (_map[0][0] != '#')
			PrintMap();

		int length = obj.GetLength();

		if (positionX == 0)
		 positionX = *_vertical / 2;

		int positionY = *_horizontal /2;
		
		for (size_t i = 0; i < length-1; i++)
		_map[positionX][positionY+i] = obj.GetCharOfShuttle(i); 
		
		int newY = positionY + length - 1;
		_positionOfObjectY = new int(positionY);
		_positionOfObjectX = new int(positionX);
		/*_length = new int(newY);*/
	/*	cout << "Start -> " << positionY<<endl;
		cout << "End -> " << newY << endl;*/

	}
	
	void Draw()
	{
		for (size_t i = 0; i < *_vertical; i++)
		{
			
			for (size_t j = 0; j < *_horizontal; j++)
			{
				if (i == 0 || i == *_vertical - 1)
					_map[i][j] = '#';
			/*	else if (j == 0)
					_map[i][j] = '#';
				else if (j == *_horizontal - 1)
					_map[i][j] = '#';*/
				cout<<_map[i][j];
		
			}
			cout << endl;
		}
	}

	void ChangePosition(int moving = 0)
	{

		
		int counter = 0; 
		_move = Moving();

		if (*_positionOfObjectX + _move > 0 && *_positionOfObjectX + _move <= *_vertical - 2 && *_positionOfObjectX + _move != *_positionOfObjectX)
		{
			for (size_t i = 0; i < *_length - 1; i++)
			{
				//_map[position][*_positionOfObjectY + i] = _shtl->GetCharOfShuttle(i);
				_map[*_positionOfObjectX + _move][*_positionOfObjectY] = *_shtl->GetLookOfShuttle();
				_map[*_positionOfObjectX][*_positionOfObjectY + i] = ' ';

			}
			if (_move == 1)
				*_positionOfObjectX += 1;
			else if (_move == -1)
				*_positionOfObjectX -= 1;
		}


		//thread asteroidRain(&Map::CreateAsteroids, this,moving);
		//asteroidRain.join(); @todo
	
		CreateAsteroids(moving);
		cout << *_positionOfObjectX;

	}
	
	int GetWidth() const {return *_horizontal;}
	int GetHeight() const {return *_vertical;}
	

	~Map()
	{
		for (size_t i = 0; i < *_vertical; i++)
		{
			_map[i] = nullptr;
			delete _map[i];
		}
		_map = nullptr;
		delete[] _map;


		
		 _positionOfObjectY = nullptr;
		 _positionOfObjectX = nullptr;

	
		 _length = nullptr;

		_horizontal = nullptr;
		_vertical = nullptr;
	}
	

int Moving()
{
#define KEY_UP 72
#define KEY_DOWN 80
	if (_kbhit())
		switch (_getch())
		{
		case 'w': case KEY_UP:
			return UP;
		case 's': case KEY_DOWN:
			return DOWN;
			
		default:
			return 0;
			break;
		}
	
}
};



void main()
{
	SpaceShuttle newSpaceShuttle;
	Map map(newSpaceShuttle); 
	Player player;
	map.StartPosition(newSpaceShuttle);
	map.Draw();
	int position = 1;
	int oldPosition = 1;
	int moving = 0;
	int points = 0;

	try {
	player.EnterUserName();
	}
	catch (exception(error))
	{
		cout << error.what() << endl;
	}

	while (!map.isEnd())
	{

		moving++;

			map.ChangePosition(moving);
			system("cls");
			map.Draw();
			if (moving == map.GetWidth())
				moving = 0;
			oldPosition = position;
		
			points += 2;
			cout << "SCORE -> " << points << endl;
	
	}
	
	for (size_t i = 0; i < (map.GetWidth() / 2)-5; i++)
		cout << "-";
	cout << "GAME OVER!";

	for (size_t i = 0; i < (map.GetWidth() / 2) - 5; i++)
		cout << "-";
	cout << endl;
	player.SavePoints(points);
	player.LoadPoints();


}

