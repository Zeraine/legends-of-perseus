#include "stdafx.h"
#include "LevelLoader.h"

using namespace std;

inline vector<string> splitString( const string& s, const string& delimiter ){
  vector<string> result;
  string::size_type from = 0;
  string::size_type to = 0;

  while ( to != string::npos ){
    to = s.find( delimiter, from );
    if ( from < s.size() && from != to ){
      result.push_back( s.substr( from, to - from ) );
    }
    from = to + delimiter.size();
  }
  return result;
}

inline int stringToInt(const string s) {
	return atoi(s.c_str());
}

inline float stringToFloat(const string& s) {
	float x;
	x = atof(s.c_str());
	return x;
}

LevelLoader::LevelLoader(string levelFileName)
{
	//Prepare Level
	ifstream levelFile(levelFileName);
	levelCompleted = false;
	if (levelFile.is_open())
	{
		string monsterString;
		//If not end of file
		while ( levelFile.good() )
		{
			getline(levelFile, monsterString);
			if (monsterString.at(0) == '#') {
			} else {
				vector<string> monsterVector = splitString(monsterString, ";");
				newMonstersVector.push_back(monsterVector);
			}
		}
		levelFile.close();
	} else {
		cout << "Failed to load level data from: " << levelFileName << endl;
		exit(0);
	}
}


LevelLoader::~LevelLoader(void)
{
}

vector<Monster*> LevelLoader::checkForNewMonsters(int currentFrame) {
	vector<Monster*> newMonsters;
	if (newMonstersVector.size() > 0) {
		int monsterFrame = stringToInt(newMonstersVector[0][0]);
		while (currentFrame > monsterFrame && newMonstersVector.size() > 0) {
			Monster* newMonster = createMonster(newMonstersVector[0]);
			newMonsters.push_back(newMonster);
			newMonstersVector.erase(newMonstersVector.begin());
			if (newMonstersVector.size() > 0) {
				monsterFrame = stringToInt(newMonstersVector[0][0]);
			}
		}
	} else {
		levelCompleted = true;
	}
	return newMonsters;
}

Monster* LevelLoader::createMonster(vector<string> monsterString) {
	int monsterId = stringToInt(monsterString[1]);
	int monsterX = stringToInt(monsterString[2]);
	int monsterY = stringToInt(monsterString[3]);
	Monster* newMonster;

	switch (monsterId) {
	case 1:
		newMonster = new TestMonster(monsterX, monsterY);
		break;
	case 2:
		newMonster = new MedusaHead(monsterX, monsterY);
		break;
	case 3:
		newMonster = new FollowMonster(monsterX, monsterY);
		break;
	case 4:
		newMonster = new HoverMonster(monsterX, monsterY);
		break;
	/*case 5:
		newMonster = new LionHead(monsterX, monsterY);
		break;
	case 6:
		newMonster= new RamHead(monsterX, monsterY);
		break;
	case 7:
		newMonster= new SnakeHead(monsterX, monsterY);
		break;
	case 8:
		newMonster= new Chimera(monsterX, monsterY);
		break;*/
	default:
		newMonster = new TestMonster(monsterX, monsterY);
		break;
	}

	return newMonster;
}
std::vector<Monster*> LevelLoader::loadBoss(){
	buffer.loadFromFile("bossEnter.wav");
	sound.setBuffer(buffer);
	sound.play();
	vector<Monster*> newMonsters;
	//Chimera(newMonsters);
	/*newMonsters.push_back(new SnakeHead(700, 100));
	newMonsters.push_back(new LionHead(700, 300));
	newMonsters.push_back(new RamHead(700, 200));*/
	newMonsters.push_back(new Chimera(800, 285));

	return newMonsters;
}

