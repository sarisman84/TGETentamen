#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
namespace si
{
	class ScoreSystem
	{
	public: //Setup
		ScoreSystem();
	public: //Communicators
		static void IncrementScore(const uint32_t someAmount);
		static void ResetScore();
		static void SaveScore(const std::string& aName);
		static std::unordered_map<std::string, uint32_t> LoadHighScores();
	public: //Getters and Setters
		inline static const uint32_t GetCurrentScore() { return ourInstance->myCurrentScore; }
	private://Internal logic
		void SaveScoreImpl(const std::string& aName);
		std::unordered_map<std::string, uint32_t> LoadHightscoresImpl();
	private://Data
		uint32_t myCurrentScore;
		std::string myDataPath;
	private://Keyword definitions (ommiting standard formating to fit json standards)
		const std::string highscore = "highscore";
		const std::string name = "name";
	private://Instance
		inline static ScoreSystem* ourInstance;
	};
}