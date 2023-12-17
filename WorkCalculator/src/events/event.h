#pragma once

#include "pch.h"

// FIXME: Event are currently blocking => Fix that!

enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory {
	None = 0,
	EventCategoryApplication	= BIT(0),
	EventCategoryInput			= BIT(1),
	EventCategoryKeyboard		= BIT(2),
	EventCategoryMouse			= BIT(3),
	EventCategoryMouseButton	= BIT(4)
};

#define EVENT_CLASS_TYPE(type)				static EventType Get_Static_Type() { return EventType::##type; }					\
											virtual EventType Get_Event_Type() const override { return Get_Static_Type(); }		\
											virtual std::string Get_Name() const override { return #type; }

#define	EVENT_CLASS_CATEGORY(category)		virtual int Get_Category_Flag() const override { return category; }

class Event {

public:
	bool handeled = false;

	virtual EventType Get_Event_Type() const = 0;
	virtual std::string Get_Name() const = 0;
	virtual int Get_Category_Flag() const = 0;
	virtual std::string ToString() const { return Get_Name(); }

	inline bool Is_In_Category(EventCategory category) { return(Get_Category_Flag() & category); }
};

class EventDispacher {

	template<typename T>
	using EventFn = std::function<void(T&)>;
public:
	EventDispacher(Event& event) : m_Event(event) {}

	template<typename T>
	bool Dispach(EventFn<T> func) {
		
		if (m_Event.Get_Event_Type() == T::Get_Static_Type()) {
			
			m_Event.handeled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}

private:
	Event& m_Event;
};