#ifndef _EVENT_H
#define _EVENT_H

#include "common/pch.h"

enum class EventType {
    MousePress, MouseRelease, MouseMove,
    KeyPress, KeyRelease,
    ButtonPress, FieldMofify,
    WindowClose,
};

// Used to set the EventType statically of the class statically, but also dynamically for the parent Event class.
// This allows the event dispatcher to determine an generic Event reference's child type.
// eventType is one of the EventType enum values
#define SET_EVENTTYPE(eventType) \
    public: \
        static EventType getStaticType() { return eventType; } \
        virtual EventType getEventType() const override { return getStaticType(); }\
        virtual std::string getName() const override { return #eventType; }

class Event {
public:
    virtual ~Event() = default;
    // These functions are implemented automatically my using the SET_EVENTTYPE macro
    virtual EventType getEventType() const = 0;
    virtual std::string getName() const = 0;

    // Set E as the desired child Event you wish to dispatch
    template<typename E>
    static bool dispatch(Event& e, std::function<void(E&)> func) {
        if (e.getEventType() == E::getStaticType()) {
            func(static_cast<E&>(e));
            return true;
        }
        return false;
    }
};

using EventCallbackFn = std::function<void(Event&)>;


class ButtonPressEvent : public Event {
    SET_EVENTTYPE(EventType::ButtonPress)
public:
    ButtonPressEvent(const std::string ID) : m_buttonID{ID} {}
    std::string getButtonID() const { return m_buttonID; }
private:
    const std::string m_buttonID;
};


class WindowCloseEvent : public Event {
    SET_EVENTTYPE(EventType::WindowClose)
};


class FieldModifyEvent : public Event {
    SET_EVENTTYPE(EventType::FieldMofify)
public:
    FieldModifyEvent(const std::string ID) : m_fieldID{ID} {}
    std::string getFieldID() const { return m_fieldID; }
private:
    const std::string m_fieldID;
};

#endif