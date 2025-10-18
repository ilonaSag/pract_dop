
#include <iostream>
struct EventSystem
{
	void (**handlers)(const std::string& message);
	int count = 0;
	int capacity;
	EventSystem(int capa) {
		handlers = new (void(*[capa])(const std::string & message));
		capacity = capa;
	};
	~EventSystem() {
		delete[] handlers;
	};
};

void registerHandler(EventSystem& system, void(*handler)(const std::string& message)) {
	system.handlers[system.count] = handler;
	system.count++;
};

void triggerEvent(const EventSystem& system, const std::string& message) {
	for (int i = 0; i < system.count;i++) {
		system.handlers[i](message);
	}
};
 void onUserLogin(const std::string&message) {
	std::cout << "Пользователь вошел в систему" << "\n";
};
void onUserLogout(const std::string& message) {
	std::cout << "Пользователь вышел из системы" << "\n";
};
void onError(const std::string& message) {
	std::cout << "Произошла ошибка!" << "\n";
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
	triggerEvent(sys,"пока");
}

