#include "ievent.hh"

class IListenerCallback
{
	public:
		virtual void execute(IEvent event) = 0;
}
