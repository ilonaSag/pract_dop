
#include <iostream>
struct EventSystem
{
	void (**handlers)(const std::string&);
	int count = 0;
	int capacity;
	EventSystem(int capa) {
		handlers = new (void(*[capa])(const std::string&));
		capacity = capa;
	};
	void Valid(int newCapa) {
		if (newCapa <= capacity) { return; }
			void (**newHandlers)(const std::string&) = new (void(*[newCapa])(const std::string&));
			for (int i = 0; i < count; i++)
			{
				newHandlers[i] = handlers[i];
			}
			delete[]handlers;
			capacity = newCapa;
			handlers = newHandlers;
		}
	~EventSystem() {
		delete[] handlers;
	};
};

void registerHandler(EventSystem& system, void(*handler)(const std::string& message)) {
	if (system.count >= system.capacity) {
		system.Valid(system.capacity * 2);
	}
	system.handlers[system.count] = handler;
	system.count++;
};

void triggerEvent(const EventSystem& system, const std::string& message) {
	for (int i = 0; i < 1;i++) {
		system.handlers[i](message);
	}
};
 void onUserLogin(const std::string&message) {
	std::cout << message << "\n";
};
void onUserLogout(const std::string& message) {
	std::cout << message << "\n";
};
void onError(const std::string& message) {
	std::cout << message << "\n";
};
int main()
{
	setlocale(LC_ALL, "Russian");
	int p;
	std::cin >> p;
	EventSystem sys(p);
	registerHandler(sys, onUserLogin);
	registerHandler(sys, onUserLogout);
	registerHandler(sys, onError);
	triggerEvent(sys, "Пользователь вошел в систему");
	triggerEvent(sys, "Пользователь вышел из системы");
	triggerEvent(sys, "Произошла ошибка!");
}

