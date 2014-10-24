#ifndef _RENDERSIM_HH_
#define _RENDERSIM_HH_

class RenderSim
{
	public:

		// Loads the game config at the specified path.
		// Parameters:
		// std::string gameConfigPath - path to the game config json file
		void config(std::string gameConfigPath);

		// Initiates the game.
		void run();

};

#endif
