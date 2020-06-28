#ifndef _REACTOR_CPP
#define _REACTOR_CPP

#include <algorithm>
#include <functional>

#include "Reactor.h"
#include "Event_Handler.h"

Reactor *
Reactor::instance_ = 0;

Reactor::Reactor ()
  : run_event_loop_ (true)
{
}

Reactor::~Reactor ()
{
  std::for_each (dispatch_table_.begin (),
                 dispatch_table_.end (),
                 [](Event_Handler *event_handler) {
                   // Remove each event_handler.
                   Reactor::instance ()->remove_input_handler (event_handler);
                 });
}

Reactor *
Reactor::instance ()
{
  if (Reactor::instance_ == nullptr)
    Reactor::instance_ = new Reactor;

  return Reactor::instance_;
}

void
Reactor::register_input_handler (Event_Handler *eh)
{
  dispatch_table_.push_back (eh);
}

void
Reactor::remove_input_handler (Event_Handler *eh)
{
  auto itr = std::remove (dispatch_table_.begin (),
	                      dispatch_table_.end (),
	                      eh);
  dispatch_table_.erase(itr, dispatch_table_.end());
  eh->delete_this ();
}

void 
Reactor::run_event_loop ()
{
  while (run_event_loop_)
    std::for_each (dispatch_table_.begin (),
                   dispatch_table_.end (),
                   std::mem_fn (&Event_Handler::handle_input));
}

void
Reactor::end_event_loop ()
{
  run_event_loop_ = false;
}

#endif /* _REACTOR_CPP */
