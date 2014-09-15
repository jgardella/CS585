class GameObject
{
	public:
		GameObject();
		bool update(float dt);
	private:
		SceneManager sceneManager;
		DynamicArray<Actor> actors;
};
