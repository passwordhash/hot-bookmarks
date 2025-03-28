#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <ApplicationServices/ApplicationServices.h>

CGEventRef keyboard_callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

#endif // KEYBOARD_H
