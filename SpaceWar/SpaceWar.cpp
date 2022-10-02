// SpaceWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>

using namespace std;

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
#pragma endregion
//BASE OBJECT

//template<class T>
class Map
{
protected:
	//T **_map;
	char** _map;
	int *_vertical;
	int *_horizontal; //it refers for length of lines
	char* _positionOfObject;
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
	//velicina objekta
	//pozicija objekta?
	//negativni objekti
public:
	Map()
	{
		_vertical = new int(50);
		_horizontal = new int(200);
		_map = new char*[*_vertical];
		for (size_t i = 0; i < *_vertical; i++)
		{
			_map[i] = new char[*_horizontal];
		}

		for (size_t i = 0; i < *_vertical; i++)
			for (size_t j = 0; j < *_horizontal; j++)
				_map[i][j] = ' ';

		_positionOfObject = nullptr;
	}


	void StartPosition(SpaceShuttle& obj)
	{
		if (_map[0][0] != '#')
			PrintMap();
		int length = obj.GetLength();

		int positionX = *_vertical / 2;
		int positionY = *_horizontal /10;
		
		for (size_t i = 0; i < length-1; i++)
		{
		_map[positionX][positionY+i] = obj.GetCharOfShuttle(i); //@todo - napraviti pokazivac na poziciju space shuttle - a; napraviti kretanje (GORE - DOLJE)

		}
		int newY = positionY + length - 1;
		//_positionOfObject = &_map[positionX][newY]; ---- ideja
	}
	void Play()
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

	~Map()
	{
		
		for (size_t i = 0; i < *_vertical; i++)
		{
			_map[i] = nullptr;
			delete _map[i];
		}
		_map = nullptr;
		delete[] _map;

		//delete[] _positionOfObject;
		// _positionOfObject = nullptr;
		_horizontal = nullptr;
		_vertical = nullptr;
	}
};

void main()
{
	Map mapa; 
	mapa.Play();
	SpaceShuttle novi;
	mapa.StartPosition(novi);
	mapa.Play();

	


}

