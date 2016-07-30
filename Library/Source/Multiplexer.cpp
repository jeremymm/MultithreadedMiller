//***************************************************************************//
// Multiplexer Implementation
//
// Created: Oct 6, 2008
// By: Jeremy Michael Miller
//
// Copyright (c) 2008-2016 Jeremy Michael Miller. 
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
// Local Includes
#include "Sync.hpp"
#include "Mutex.hpp"
#include "Multiplexer.hpp"
//***************************************************************************//

//***************************************************************************//
// System Includes
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
  //-------------------------------------------------------------------------//
  Multiplexer::Multiplexer()
  {
    this->mpMutex = new Mutex();
    mpArrayOfHandles = nullptr;
    mulCurrentArraySize = 0UL;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Multiplexer::~Multiplexer()
  {
    if(mpArrayOfHandles)
      delete [] mpArrayOfHandles;
    delete mpMutex;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Multiplexer::AddHandle(void* pHandle)
  {
    bool bReturnValue = true;
    this->mpMutex->Lock();

    // This assertion is to notify the callee of a limitation of this method
    // This method assumes that size of long* and void* are the same.  This
    // without casting void* to long* things like array subsscripts would 
    // not compile.
    assert(sizeof(void*) == sizeof(long*));
    if(this->mvPersistentHandles.size() < MAXIMUM_WAIT_OBJECTS)
    {
      this->mvPersistentHandles.push_back(pHandle);

      if(!mpArrayOfHandles || (mulCurrentArraySize < this->mvPersistentHandles.size()))
      {
        if(mpArrayOfHandles)
          delete [] mpArrayOfHandles;

        this->mpArrayOfHandles = new long[this->mvPersistentHandles.size()];
      }

      for(unsigned long i = 0; i < this->mvPersistentHandles.size(); i++)
         static_cast<long*>(this->mpArrayOfHandles)[i] = reinterpret_cast<long>(this->mvPersistentHandles[i]);

      this->mulCurrentArraySize = static_cast<unsigned long>(this->mvPersistentHandles.size());
    }
    else
      bReturnValue = false;
      
    this->mpMutex->Unlock();

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Multiplexer::WaitForTrigger(unsigned long ulWait) const
  {
    bool bReturnValue = true;

    if(this->mpMutex->Lock())
    {
      unsigned long ulResult = WaitForMultipleObjects(this->mulCurrentArraySize, static_cast<HANDLE*>(this->mpArrayOfHandles), false, ulWait);

      // Throw an assertion if the wait failed.
      assert(ulResult != WAIT_FAILED);
      if((ulResult == WAIT_TIMEOUT) || (ulResult == WAIT_FAILED) || (ulResult >= WAIT_ABANDONED_0))
        bReturnValue = false;
      else if(((ulResult - WAIT_OBJECT_0) > 0) && ((ulResult - WAIT_OBJECT_0) <= static_cast<int>(this->mulCurrentArraySize)))
        ResetEvent(reinterpret_cast<HANDLE>(static_cast<long*>(this->mpArrayOfHandles)[ulResult - WAIT_OBJECT_0]));

      this->mpMutex->Unlock();
    }

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//
} // End of namespace MST
//***************************************************************************//