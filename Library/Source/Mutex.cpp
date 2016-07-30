//***************************************************************************//
// Mutex Class Implementation
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
#include "Mutex.hpp"
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
#include <sstream>
//***************************************************************************//

//***************************************************************************//
#ifdef WINDOWS_THREADS
#include <windows.h>
#endif 
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  Mutex::Mutex()
  {
#ifdef WINDOWS_THREADS
    mvpSyncObject = CreateMutex(nullptr, false, nullptr);
    assert(mvpSyncObject);
#endif
  }
  //************************************************************************//

  //*************************************************************************//
  Mutex::~Mutex()
  {
#ifdef WINDOWS_THREADS
    CloseHandle(mvpSyncObject);
#endif 
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Mutex::Lock(unsigned long ulWait) const
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

  //*************************************************************************//
  void Mutex::Unlock() const
  {
    assert(this->mvpSyncObject);
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      ReleaseMutex(this->mvpSyncObject);
      //ReleaseSemaphore(this->mvpSyncObject, 1, NULL);
#endif 
    }
  }
  //*************************************************************************//

} // End of namespace MST
//***************************************************************************//