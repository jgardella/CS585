class IEvent
{
	public:

		IEvent(std::string type);

		std::string getType();
	
	private:

		std::string eventType;
};
