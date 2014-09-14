// Singleton class for managing scene.
class SceneManager
{
	public:
		SceneManager* getInstance();
		void tick(float dt);
		void addTickable(ITickable tickable);
		void addSceneNode(SceneNode node);
	private:
		SceneManager();
		Debug(Debug const&);
		SceneManager& operator=(Debug const&);
		~Debug();
		
		static SceneManager* instance;
		DynamicArray<ITickable> tickables;
		DynamicArray<SceneNode> sceneNodes;
		ISceneGraph sceneGraph;
};
