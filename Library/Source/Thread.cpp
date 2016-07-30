//***************************************************************************//
// Thread Class Implementation
//
// Created: Feb 16, 2009
// By: Jeremy Michael Miller
//
// Copyright (c) 2009-2016 Jeremy Michael Miller. 
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
// System Include
#include <Windows.h>
#include <process.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Event.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  Thread::Thread()
  {
    mfpRoutine         = nullptr;
    mvpDerivedThis     = nullptr;
    mbThreadRunning    = false;
    mulPauseTime       = 0;
    mpThreadMutex      = new Mutex();
    mpResumeEvent      = new Event();
    mpThreadStartEvent = new Event();
    mpThreadStopEvent  = new Event();
  }
  //-------------------------------------------------------------------------//
  
  //-------------------------------------------------------------------------//
  Thread::~Thread()
  {
    this->mpThreadMutex->Lock();
    delete mpResumeEvent;
    delete mpThreadStartEvent;
    delete mpThreadStopEvent;
    this->mpThreadMutex->Unlock();
    delete mpThreadMutex;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SetRoutine(void (*fpRoutine)(void*), void* pThis)
  {
    mfpRoutine = fpRoutine;
    mvpDerivedThis = pThis;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SignalStarted()
  {
    if(!this->mbThreadRunning)
    {
      this->mpThreadMutex->Lock();
      this->mbThreadRunning = true;
      this->mpThreadStartEvent->Signal();
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SignalStopped()
  {
    this->mbThreadRunning = false;
    this->mpThreadStopEvent->Signal();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Continue()
  {
    if(this->mbThreadRunning)
    {
      if(this->mulPauseTime)
      {
        this->mpResumeEvent->WaitForSignal(this->mulPauseTime);
        this->mulPauseTime = 0UL;
      }
    }
    return this->mbThreadRunning;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::End() const
  {
    this->mpThreadMutex->Unlock();
    _endthread();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Start() const
  {
    bool bReturnvalue = false;
    if(!this->mbThreadRunning)
    {
      this->mpThreadMutex->Unlock();
      _beginthread(mfpRoutine, 0L, mvpDerivedThis);
      this->mpThreadStartEvent->WaitForSignal();
      bReturnvalue = true;
    }
    return bReturnvalue;

  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Stop(unsigned long ulTimeout)
  {
    this->mbThreadRunning = false;
    this->mulPauseTime = 0;
    this->mpResumeEvent->Signal();
    this->mpThreadStopEvent->WaitForSignal(ulTimeout);
    return true;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Pause(unsigned long ulTime)
  {
    bool bReturnValue = false;
    if(this->mbThreadRunning && ulTime)
    {
      this->mulPauseTime = ulTime;
      bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Resume()
  {
    bool bReturnValue = false;
    if(this->mbThreadRunning && this->mulPauseTime)
    {
      this->mulPauseTime = 0;
      if(this->mpResumeEvent->Signal())
        bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Running() const
  {
    return this->mbThreadRunning;
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//