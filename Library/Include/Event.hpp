//***************************************************************************//
// Event Class Interface
//
// Created: Oct 22, 2006
// By: Jeremy Michael Miller
//
// Copyright (c) 2006-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2006-2016, Multithreaded Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_THREADS_EVENT_HPP
#define MST_THREADS_EVENT_HPP

//***************************************************************************//
// System Includes
#include <limits.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Sync.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief The Event class provides the ability to use signals to trigger 
  /// a notification in waiting thread about events happening in other threads. 
  class Event : public Sync
  {
  private:
  public:
    //***********************************************************************//
    Event();
    ~Event();

    /// This method will signal to any waiting thread.
    /// \return 
    /// This method will return true if the signal was successfully sent.
    /// Otherwise, this method will return false.
    bool _cdecl Signal();
    /// This method will reset event so that it can be signaled again.
    /// \return 
    /// This method will return true if the event was successfully reset.
    /// Otherwise, the method will return false.
    bool _cdecl Reset();
    /// This method will block while waiting for a signal to occur on an Event
    /// instance. 
    /// \param [in] ulWait
    /// This parameter will inform the method how long it should wait while 
    /// waiting for the Event to signaled. This parameters units are in 
    /// milliseconds.
    /// \return
    /// This method will return true of method successfully detected a signal 
    /// on the Event. Otherwise, if the wait time has expired before any signal 
    /// was detected, this method will return false.
    bool _cdecl WaitForSignal(unsigned long ulWait = ULONG_MAX);
    //***********************************************************************//
  }; // End of class Event
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_THREADS_EVENT_HPP