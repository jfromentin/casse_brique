#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "window.hpp"
#include "world.hpp"

//! Handle all event
//! Return true for quit event
bool event_handler(Window* window, World* world);


//! Wait for a given time
//! \param delay time to wait in ms
void wait(int delay);

#endif
