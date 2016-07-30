//***************************************************************************//
// Event Class Implementation
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

//***************************************************************************//
#include "Event.hpp"
//***************************************************************************//

//***************************************************************************//
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
#ifdef WINDOWS_THREADS
#include <windows.h>
#endif 
//***************************************************************************//

//***************************************************************************//
namespace MST
{

  //*************************************************************************//
  Event::Event()
  {
#ifdef WINDOWS_THREADS
    mvpSyncObject = CreateEvent(NULL, true, false, NULL); 
    assert(mvpSyncObject);
#endif
  }
  //*************************************************************************//

  //*************************************************************************//
  Event::~Event()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::Signal()
  {
    assert(mvpSyncObject);
    bool bReturnValue = false;
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      // Using tertiary operator because the visual studio compiler is stupid.
      bReturnValue = SetEvent(this->mvpSyncObject) ? true : false;
#endif 
    }
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::Reset()
  {
    assert(mvpSyncObject);
    bool bReturnValue = false;
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      // Using tertiary operator because the visual studio compiler is stupid.
      bReturnValue = ResetEvent(this->mvpSyncObject) ? true : false;
#endif 
    }
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::WaitForSignal(unsigned long ulWait)
  {
    assert(mvpSyncObject);

    //-----------------------------------------------------------------------//
    if(this->mvpSyncObject)
    {
      unsigned long ulResult = 0L;

      if(ulWait == ULONG_MAX)
      {
#ifdef WINDOWS_THREADS
        ulResult = WaitForSingleObject(this->mvpSyncObject, INFINITE);
#endif
      } // End of if(ulWait == ULONG_MAX)
      else
      {
#ifdef WINDOWS_THREADS
        ulResult = WaitForSingleObject(this->mvpSyncObject, ulWait);
#endif
      }

#ifdef WINDOWS_THREADS
      if(ulResult & WAIT_FAILED || ulResult & WAIT_TIMEOUT)
        return false;
#endif

      return true;
    } // End of if(this->mvpSyncObject)
    //-----------------------------------------------------------------------//
    else
      return false;
  }
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//
