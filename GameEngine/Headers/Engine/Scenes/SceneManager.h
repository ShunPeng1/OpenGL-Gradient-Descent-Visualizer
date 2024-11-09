#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void addScene(IScene* scene);
	void removeScene(IScene* scene);
	IScene* getScene(int index) const;

	void setCurrentScene(int index);
	IScene* getCurrentScene() const;

	void update(float deltaTime);
	void render();


#endif // !SCENE_MANAGER_H
