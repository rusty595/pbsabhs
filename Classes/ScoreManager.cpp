#include "ScoreManager.h"

ScoreManager* ScoreManager::instance = NULL;

ScoreManager::ScoreManager()
{
	setHighscore(getHighscoreFromFile());
	resetScore();
}

ScoreManager* ScoreManager::sharedScoreManager()
{
	if (instance == NULL)
	{
		instance = new ScoreManager();
	}

	return instance;
}

void ScoreManager::addToScore(float point)
{
	score += point;
}

void ScoreManager::subtractFromScore(float point)
{
	score -= point;
}

float ScoreManager::getScore()
{
	return score;
}

void ScoreManager::resetScore()
{
	score = 0;
}

void ScoreManager::compareScoreToHighscore()
{
	if (score > highScore)
	{
		setHighscore(score);
	}
}

void ScoreManager::setHighscore(int newScore)
{
	highScore = newScore;
	storeHighscoreToFile(highScore);
}

int ScoreManager::getHighscore()
{
	return highScore;
}

void ScoreManager::storeHighscoreToFile(int highScore)
{
	// Insert code to save highscore to file
	std::string path = getFilePath();

	FILE *fp = fopen(path.c_str(), "w");

	if (!fp) {
		CCLOG("Cannot create file in %s", path.c_str());
		return;
	}

	std::string value = StringUtils::format("%d", highScore);

	fputs(value.c_str(), fp);
	fclose(fp);
}

int ScoreManager::getHighscoreFromFile()
{
	// Insert code to get highscore from file
	std::string path = getFilePath();

	FILE *fp = fopen(path.c_str(), "r");
	char buf[50] = { 0 };

	if (!fp) {
		CCLOG("The file cannot be opened in %s", path.c_str());
		return 0;
	}

	fgets(buf, 50, fp);
	CCLOG("Content Read %s", buf);

	int highscore = atoi(buf);

	fclose(fp);

	return highscore;
}

std::string ScoreManager::getFilePath()
{
	std::string path = "";

	// testing
	std::string writableDir = CCFileUtils::getInstance()->getWritablePath();

	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
		path = writableDir + "\highscoredata.txt";
	}
	else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		path = writableDir + "\highscoredata.txt";
	}

	return path;
}

ScoreManager::~ScoreManager()
{
}