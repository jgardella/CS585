#include "itickable.hh"
#include "ilistenercallback.hh"
#include "trie.hh"
#include "dynamicarray.hh"

class Dispatcher : public ITickable
{
	public:
		
		void addListener(std::string eventType, IListenerCallback* callback);

		void removeListener(std::string eventType, IListenerCallback* callback);

		void dispatch(std::string eventType);

	private:
		Trie<DynamicArray<IListenerCallback*>*> *callbacks;

};
