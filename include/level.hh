#ifndef _LEVEL_HH_
#define _LEVEL_HH_

class Level
{
	public:
		// Constructs a level with a world of the given width and height.
		// Parameters:
		// int width - the width of the world
		// int height - the height of the world
		Level(int width, int height);

		int getWorldWidth();
		int getWorldHeight();
	private:
		int width;
		int height;

};

#endif
