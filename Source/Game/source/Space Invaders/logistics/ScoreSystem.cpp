#include "ScoreSystem.h"
#include "logging/Logger.h"

#include <tge/settings/settings.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

si::ScoreSystem::ScoreSystem()
{
	ourInstance = this;
	myDataPath = Tga::Settings::GetAsset("Data/Other/");
}

void si::ScoreSystem::IncrementScore(const uint32_t someAmount)
{
	ourInstance->myCurrentScore += someAmount;
}

void si::ScoreSystem::ResetScore()
{
	ourInstance->myCurrentScore = 0;
}

void si::ScoreSystem::SaveScore(const std::string& aName)
{
	if (!ourInstance) return;

	ourInstance->SaveScoreImpl(aName);
}

std::unordered_map<std::string, uint32_t> si::ScoreSystem::LoadHighScores()
{
	if (!ourInstance)
		return std::unordered_map<std::string, uint32_t>();
	return ourInstance->LoadHightscoresImpl();
}

void si::ScoreSystem::SaveScoreImpl(const std::string& aName)
{
	//Some init stuff
	using namespace nlohmann;
	std::unordered_map<std::string, uint32_t> content;
	json data;
	const std::string file = myDataPath + "highscore.json";


	//If the file exists, read it and cache its content
	std::ifstream highscoreIfs(file);
	if (highscoreIfs.good())
	{
		data = json::parse(highscoreIfs);
	}
	else
	{
		data = json::array();
	}

	//Parse the data as its own object, then store that object into an array in the json file
	json entry = json::object();
	entry[name] = aName;
	entry[highscore] = myCurrentScore;

	data.push_back(entry);

	//Write into the file
	std::ofstream highscoreOfs(file);
	highscoreOfs << data;
}

std::unordered_map<std::string, uint32_t> si::ScoreSystem::LoadHightscoresImpl()
{
	//Some init stuff
	using namespace nlohmann;
	std::unordered_map<std::string, uint32_t> content;
	json data;
	const std::string file = myDataPath + "highscore.json";

	std::ifstream highscoreIfs(file);
	if (!highscoreIfs.good())
	{
		ERROR_LOG("File " + file + " was not found in " + myDataPath + ".");
		return std::unordered_map<std::string, uint32_t>();
	}

	data = json::parse(highscoreIfs);


	for (auto& entry : data)
	{
		content[entry[name]] = entry[highscore];
	}

	return content;
}
