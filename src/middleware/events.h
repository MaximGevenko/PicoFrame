#ifndef _EVENTS_H
#define _EVENTS_H

enum class EventType {
    BUTTON_DOWN,
    BUTTON_UP,
    WIRE_BRIDGED
};

struct Event {
    EventType type;
    int data;
};

#endif /*_EVENTS_H*/