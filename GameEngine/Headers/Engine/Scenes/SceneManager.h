#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Engine/Interfaces/IScene.h"

class SceneManager 
{
public:
	SceneManager();
	~SceneManager();

	void addScene(IScene* scene);
	void removeScene(IScene* scene);
	void changeToScene(IScene* scene);
	void changeToScene(int index);
	IScene* getScene(int index) const;
	IScene* getCurrentScene() const;


	void play();
	void stop();
	void pause();


public:
	void load(IScene* scene);
	void unload(IScene* scene);

	void update(float deltaTime);
	void render();


private:
	std::vector<IScene*> mScenes;
	IScene* mCurrentScene;
	bool mIsPlaying;
};


#endif // !SCENE_MANAGER_H
