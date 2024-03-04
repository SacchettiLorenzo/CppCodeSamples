#include <iostream>
#include <vector>
using namespace std;

struct ChatRoom;

struct Person {
	string name;
	ChatRoom* room = nullptr;
	vector<string> chat_log;

	Person(const string& name);

	void receive(const string& origin, const string& message) {
		cout << "message from " << origin << ": " << message << endl;
		string s = origin + ": " + message + "\n";
		chat_log.emplace_back(chat_log);
	}

	void say(const string& message) const {
		room->broadcast(name, message);
	}

	void pm(const string& who, const string& message)const {
		room->message(name, who, message);
	}
};

struct ChatRoom {
	vector<Person*> people;

	void join(Person* p);
	void broadcast(const string& origin, const string& message);
	void message(const string& origin, const string& who, const string& message);

};


void ChatRoom::join(Person* p) {
	string join_msg = p->name + " joins the chat";
	broadcast("room", join_msg);
	p->room = this;
	people.push_back(p);
}

void ChatRoom::broadcast(const string& origin, const string& message) {
	for (auto p : people) {
		if (p->name != origin) {
			p->receive(origin, message);
		}
	}
}

void ChatRoom::message(const string& origin, const string& who, const string& message)
{
	auto target = find_if(begin(people), end(people), [&](const Person* p) {
		return p->name == who;
		});
	if (target != end(people)) {
		(*target)->receive(origin, message);
	}
}



int main() {
	ChatRoom room;
	Person john{ "john" };
	Person jane{ "jane" };
	room.join(&john);
	room.join(&jane);

	john.say("hi room");
	jane.say("oh, hei john");

	Person simon{ "simon" };
	room.join(&simon);
	simon.say("hi everyone!");

	jane.pm("simon", "glad you could join us, simon");
}

//The mediator design pattern is a mechanism for facilitating communication between the components
//there are situations when you don't want objects to be necessarily aware of each other's presence

//in the example it is implemented a chat room