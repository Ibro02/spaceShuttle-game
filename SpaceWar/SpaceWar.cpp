// SpaceWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <mutex>
#include <cstdlib>

using namespace std;
enum Positions { UP=-1, DOWN=1 };

#pragma region functions
char* GetArrayOfCharacters(const char* text)
{
	int size = strlen(text) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, text);
	return temp;

}

#pragma endregion

#pragma region Objects
class Shuttle
{
	char* _lookOfSpaceShuttle;

public:
	Shuttle()
	{

		_lookOfSpaceShuttle = GetArrayOfCharacters("|>=|}c>");
	}
	virtual ~Shuttle()
	{
		delete[] _lookOfSpaceShuttle;
		_lookOfSpaceShuttle = nullptr;
	}

	int GetLength()
	{
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
	friend ostream& operator<< (ostream& COUT, Shuttle& obj)
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

	friend ostream& operator<<(ostream& COUT, SpaceShuttle&obj)
	{
		COUT << obj.shuttle;
		return COUT;
	}
};

//class Asteroids
//{
//@todo - napraviti enemy objekte
//};
#pragma endregion





//BASE OBJECT

//template<class T>
mutex mtx;
class Map
{
protected:
	//T **_map;
	char** _map;

	int* _vertical;
	int* _horizontal; //it refers for length of lines
	int* _positionOfObjectY;
	int* _positionOfObjectX;
	int* _length;
	int _move;
	bool _isEnd;
	SpaceShuttle* _shtl;
	
	void PrintMap()
	{
		for (size_t i = 0; i < *_vertical; i++)
		{

			for (size_t j = 0; j < *_horizontal; j++)
			{
				if (i == 0 || i == *_vertical - 1)
					_map[i][j] =  '#';
				else if (j == 0)
					_map[i][j] =  '#';
				else if (j == *_horizontal - 1)
					_map[i][j] =  '#';
				
		
			
			}
		cout << endl;
		}
		cout << endl;

	}


	/*void ExpandArray(int length)
	{
		char** temp = new char* [*_vertical];
		for (size_t i = 0; i < length; i++)
			temp[i] = new char[length + 1];

		if (_asteroids!=nullptr)
		delete[] _asteroids;

		_asteroids = temp;

	}
	*/
	void MoveAsteroids()
	{
		
		char** temp = new char*[*_vertical];
	/*	int brojac = 0;
		brojac++*/;
		for (size_t i = 0; i < *_vertical; i++)
		{
			temp[i] = new char[*_horizontal];
		}

		for (size_t i = 0; i < *_vertical; i++)
		{
			
			for (size_t j = *_horizontal; j > 0; j--)
			{
			

				if (j == *_positionOfObjectY && i == *_positionOfObjectX)
					temp[*_positionOfObjectX][*_positionOfObjectY] = _map[*_positionOfObjectX][*_positionOfObjectY];
				else if (j - 1 != -1)
					temp[i][j - 1] = _map[i][j];
				else if (i == 0)
					delete[] temp[i];
				
			}
		}
		delete[] _map;
		_map = temp;

	}
	//negativni objekti
	void CreateAsteroids(int lengthOfAsteroidRain = 0)
	{


		int brojac = 0;
		int randPosition = 1 + (rand() % (*_vertical - 2));
		int randLength = 1 + (rand() % (*_horizontal - 2));
		if (!_isEnd)
		{
			//	ExpandArray(lengthOfAsteroidRain);
				//if (lengthOfAsteroidRain > 1)
				//MoveAsteroids(lengthOfAsteroidRain);
			//	_asteroids[0][lengthOfAsteroidRain-1] = '@';

			//if (lengthOfAsteroidRain % 7 == 0)
			if (lengthOfAsteroidRain < *_horizontal)
			{
			
				lengthOfAsteroidRain++;

				for (size_t i = 0; i < *_vertical; i++)
				{

						//for(size_t j = lengthOfAsteroidRain-1; j >= 0; j++)
				
					for (size_t j = 0; j < lengthOfAsteroidRain; j++)
					{

						//cout << randPosition << endl;
						if (_map[i][*_horizontal - j] != '@')
							_map[i][*_horizontal - j] = ' ';

						if (lengthOfAsteroidRain % 7 == 0)
							if (i == randPosition)
								_map[i][*_horizontal - 2] = '@';


					}
					
				}
			}
			
					MoveAsteroids();
			brojac++;

		}
	


	}
public:
	Map()
	{
		_vertical = new int(50);
		_horizontal = new int(200);
		_isEnd = false;
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
		_vertical = new int(25);
		_horizontal = new int(100);
		_map = new char* [*_vertical];
		_isEnd = false;
		for (size_t i = 0; i < *_vertical; i++)
		{
			_map[i] = new char[*_horizontal];
		}
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

		int positionY = *_horizontal /10;
		

		for (size_t i = 0; i < length-1; i++)
		{
		_map[positionX][positionY+i] = obj.GetCharOfShuttle(i); 

		}
		
		int newY = positionY + length - 1;
		_positionOfObjectY = new int(positionY);
		_positionOfObjectX = new int(positionX);
		_length = new int(newY);
	/*	cout << "Pocetak -> " << positionY<<endl;
		cout << "Kraj -> " << newY << endl;*/

	}


		//for (size_t i = 0; i < length; i++)
		//{
		//	temp[i + 1] = _asteroids[i];
		//}
		//if (_asteroids != nullptr)
		//	delete[] _asteroids;

		//_asteroids = temp;

	
	void Draw()
	{
		for (size_t i = 0; i < *_vertical; i++)
		{
			
			for (size_t j = 0; j < *_horizontal; j++)
			{
				cout<<_map[i][j];
			}
			cout << endl;
		}
	}

	void ChangePosition(int moving)
	{

		
		int counter = 0; 
		_move = Moving();
	/*	if (_positionOfObjectY != nullptr)
			_positionOfObjectY = nullptr;*/
	
//if (position > 0 && position <= mapa.GetHeight() - 2 && position != oldPosition)

		if (*_positionOfObjectX + _move > 0 && *_positionOfObjectX + _move <= *_vertical-2 && *_positionOfObjectX + _move != *_positionOfObjectX)
		{
			for (size_t i = 0; i < *_length - 1; i++)
			{
				//_map[position][*_positionOfObjectY + i] = _shtl->GetCharOfShuttle(i);
				_map[*_positionOfObjectX + _move][*_positionOfObjectY + i] = _map[*_positionOfObjectX][*_positionOfObjectY + i];
				_map[*_positionOfObjectX][*_positionOfObjectY + i] = ' ';
			}
		if (_move == 1)
			*_positionOfObjectX += 1;
		else if (_move == -1)
			*_positionOfObjectX -= 1;
		}
		/*
		thread asteroidRain(&Map::CreateAsteroids, this, moving);
		asteroidRain.join();*/
	//	if (moving%7==0)
		CreateAsteroids(moving);
		

		cout << _move;




	}
	
	int GetWidth()
	{
		return *_horizontal;
	}
	int GetHeight()
	{
		return *_vertical;
	}
	


	~Map()
	{
		//char** _map;
		//char** _asteroids;
		//int* _vertical;
		//int* _horizontal; //it refers for length of lines
		//int* _positionOfObjectY;
		//int* _positionOfObjectX;
		//int* _length;
		//int _move;
		//bool _isEnd;
		//SpaceShuttle* _shtl;
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
	{
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
}
};



void main()
{
	SpaceShuttle novi;
	Map mapa(novi); 
	mapa.StartPosition(novi);
	mapa.Draw();
	int position = 1;
	int oldPosition = 1;
	int kretanje = 0;
	while (true)
	{

		//if (Moving() > 0 && Moving() <= mapa.GetHeight() - 2 && Moving() != oldPosition)
		//if (position > 0 && position <= mapa.GetHeight() - 2 && position != oldPosition)
		
		kretanje++;

			mapa.ChangePosition(kretanje);
			system("cls");
			mapa.Draw();
			if (kretanje == mapa.GetWidth())
				kretanje = 0;
			oldPosition = position;
		
	/*	else
			cout << "Greska" << endl;*/
	}
	


}

