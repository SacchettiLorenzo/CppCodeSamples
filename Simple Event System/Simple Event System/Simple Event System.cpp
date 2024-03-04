
#include <iostream>

#include <functional>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class Event {
protected:
    T _type;
    std::string _name;
    bool _handled = false;
public:
    Event() = default;
    Event(T type, const std::string& name = "") : _type(type), _name(name) {};
    inline const T type() const { return _type; }
    inline const std::string& getName() const { return _name; }
    virtual bool isHandled() { return _handled; }
};



template<typename T>
class Dispatcher {
private:
    using SlotType = std::function<void(const Event<T>&)>;
    std::map<T, std::vector<SlotType>> _observers;
public:
    void subscribe(T type, const SlotType& funct) {
        _observers[type].push_back(funct);
    }

    void post(Event<T>& event) {
        if (_observers.find(event.type()) == _observers.end()) {
            return;
        }

        for (auto&& observer : _observers.at(event.type())) {
            if (!event.isHandled()) observer(event);
        }
    }

};

enum class EventType1 {
    TEST_EVENT,
    TEST_EVENT2,
    TEST_EVENT3
};

enum class EventType2 {
    TEST_EVENT,
    TEST_EVENT2,
    TEST_EVENT3
};

class DemoEvent : public Event<EventType1>
{
public:
    DemoEvent() : Event<EventType1>(EventType1::TEST_EVENT, "DemoEvent") {};
    virtual ~DemoEvent() = default;
};

class DemoEventAlt : public Event<EventType2>
{
private:
public:
    DemoEventAlt() : Event<EventType2>(EventType2::TEST_EVENT, "DemoEventAlt") {};
    virtual ~DemoEventAlt() = default;
};


void onEvent1(const Event<EventType1>& event) {
    if (event.type() == EventType1::TEST_EVENT) {
        std::cout << "Function Event TYPE: EventType1::TEST_EVENT " << event.getName() << std::endl;
    }
}

void onEvent2(const Event<EventType2>& event) {
    if (event.type() == EventType2::TEST_EVENT) {
        std::cout << "Function Event TYPE: EventType2::TEST_EVENT " << event.getName() << std::endl;
    }
}

class ClassObserver1
{
public:
    void handle(const Event<EventType1>& e)
    {
        if (e.type() == EventType1::TEST_EVENT)
        {
            // This demonstrates how to obtain the underlying event type in case a
            // slot is set up to handle multiple events of different types.
            // const DemoEvent& demoEvent = static_cast<const DemoEvent&>( e );
            // std::cout << __PRETTY_FUNCTION__ << ": " << demoEvent.type() << std::endl;
            std::cout << "Class Event EventType1::TEST_EVENT " << e.getName() << std::endl;
        }
    }
};

int main(int, char**)
{
    ClassObserver1 classObserver1;

    Dispatcher<EventType1> dispatcher1;
    Dispatcher<EventType2> dispatcher2;
    Dispatcher<EventType1> dispatcher3;

    dispatcher1.subscribe(EventType1::TEST_EVENT, onEvent1);
    dispatcher1.subscribe(EventType1::TEST_EVENT, std::bind(&ClassObserver1::handle, classObserver1, std::placeholders::_1));
    dispatcher2.subscribe(EventType2::TEST_EVENT, onEvent2);
    dispatcher3.subscribe(EventType1::TEST_EVENT2, onEvent1);

    std::cout << "#\n"
        << "# Posting a demo event. This should trigger two observers\n"
        << "#\n";
    DemoEvent e;
    dispatcher1.post(e);

    std::cout << "#\n"
        << "# Posting a demo event. This should trigger one observer\n"
        << "#\n";
    DemoEventAlt e2;
    dispatcher2.post(e2);

    std::cout << "#\n"
        << "# Posting a demo event. This should trigger no observers\n"
        << "#\n";
    dispatcher3.post(e);
    return 0;
}

