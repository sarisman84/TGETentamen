#pragma once
#include <unordered_map>
#include <string>
namespace si
{
	class Scene;
	class SceneManager
	{
	public:
		SceneManager();
	public:
		static void RegisterScene(const std::string& aName, Scene* const aNewScene);
		static void LoadScene(const std::string& aName);
		static void Update(const float aDT);
		static void Render();
	public:
		static Scene* const GetCurrentScene();
	private:
		void LoadSceneFromFile(const std::string& aPath);
		Scene*& CurrentScene();
		const bool IsEmpty() const;
	private:
		std::unordered_map<std::string, Scene*> mySceneRegistry;
		std::string myCurrentScene = "empty";
	private:
		inline static SceneManager* ourInstance;
	};
}


