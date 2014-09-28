#include "itickable.hh"
#include "ilistenercallback.hh"

class Dispatcher : public ITickable
{
	public:
		
		void addListener(std::string eventType, IListenerCallback callback);

		void removeListener(std::string eventType, IListenerCallback callback);

		void dispatch(std::string eventType);
}
