#include "Engine/Scenes/SceneManager.h"

SceneManager::SceneManager() : mCurrentScene(nullptr), mIsPlaying(false) {
	mScenes = std::vector<IScene*>();
}

SceneManager::~SceneManager() {
	for (IScene* scene : mScenes) {
		delete scene;
	}
}

void SceneManager::addScene(IScene* scene) {
	auto it = std::find(mScenes.begin(), mScenes.end(), scene);

	if (scene && it == mScenes.end()) {
		mScenes.push_back(scene);
		scene->load();
	}
}

void SceneManager::removeScene(IScene* scene) {
	auto it = std::find(mScenes.begin(), mScenes.end(), scene);
	if (it != mScenes.end()) {
		if (mCurrentScene == scene) {
			mCurrentScene = nullptr;
		}
		delete* it;
		mScenes.erase(it);
	}
}

void SceneManager::changeToScene(IScene* scene) {
	if (scene && std::find(mScenes.begin(), mScenes.end(), scene) != mScenes.end()) {
		mCurrentScene = scene;
	}
}

void SceneManager::changeToScene(int index) {
	if (index >= 0 && index < mScenes.size()) {
		mCurrentScene = mScenes[index];
	}
}

IScene* SceneManager::getScene(int index) const {
	if (index >= 0 && index < mScenes.size()) {
		return mScenes[index];
	}
	return nullptr;
}

IScene* SceneManager::getCurrentScene() const {
	return mCurrentScene;
}

void SceneManager::play() {
	if (mCurrentScene) {
		mIsPlaying = true;
		mCurrentScene->start();
	}
}

void SceneManager::stop() {
	if (mCurrentScene) {
		mIsPlaying = false;
		mCurrentScene->clear();
	}
}

void SceneManager::pause() {
	mIsPlaying = false;
}

void SceneManager::load(IScene* scene)
{
	if (scene) {
		scene->init();
		scene->start();
	}
}

void SceneManager::unload(IScene* scene)
{
	if (scene) {

	}
}

void SceneManager::update(float deltaTime) {
	if (mIsPlaying && mCurrentScene) {
		mCurrentScene->update(deltaTime);
	}
}

void SceneManager::render() {
	if (mCurrentScene) {
		mCurrentScene->render();
	}
}