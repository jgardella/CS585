// scene node should contain information for collision and position

class SceneNode
{
	public:
		int getXCoordinate();
		int getYCoordinate();
	private:
		int xCoordinate, yCoordinate;
		Collider col;
}
