//***************************************************************************//
// Thread Class Interface
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

#ifndef MST_THREADS_THREAD_HPP
#define MST_THREADS_THREAD_HPP 

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief Thread is base class that provides basic thread control to the 
  /// derived class. This class is designed to support the pattern of treating
  /// threads as objects instead of methods.  This class is designed to be base 
  /// class.
  class Thread
  {
  private:
    //***********************************************************************//
    // This Mutex is used to protect against race conditions that could make an
    // instance of this class unstable.
    class Mutex* mpThreadMutex;
    // This Event is used to signal a paused thread that it can resume running.
    class Event* mpResumeEvent;
    // this Event is used to signal to any other thread waiting that the 
    // threaded routine has started.
    class Event* mpThreadStartEvent;
    // This Event is used to signal to any other thread waiting that the 
    // threaded routine has been stopped.
    class Event* mpThreadStopEvent;
    // This data member is used to point to the any derived class that using this
    // class as base class.  This provides a way for data member from the derived
    // class to be accessed in the threaded routine.
    void* mvpDerivedThis;
    //***********************************************************************//
  protected:
    //***********************************************************************//
    // This is function pointer to the routine to be run as its own thread.
    void (*mfpRoutine)(void*);
    // This boolean is used to quickly return if the threaded routine is running
    // or not.
    bool mbThreadRunning;
    // This data member is used to pause the threaded routine. This data member units
    // are milliseconds.
    unsigned long mulPauseTime;

    /// This method most be used by the derived class to inform this class what 
    /// routine will be used as the threaded routine.
    /// \param [in] fpRoutine
    /// This parameter is function pointer that points to the routine to thread
    /// \param [in] pThis
    /// This parameter is the pointer to the derived class. This will allow the
    /// threaded routine, which should be method of the derived class, to have
    /// access to the derived class's members.
    void _cdecl SetRoutine(void (*fpRoutine)(void*), void* pThis);
    /// This method should be used in the derived class's threaded routine to 
    /// signal to this class that the threaded routing as started.
    void _cdecl SignalStarted();
    /// This method should be used in the derived class's threaded routine to 
    /// signal to this class that the threaded routing as stopped.
    void _cdecl SignalStopped();
    /// This method should be checked on each iteration of the threaded routine 
    /// that is defined in the derived class. This method will block if any pause
    /// time is required and will return false if the threaded routine should
    /// return/exit
    /// \return
    /// This method will return true if the threaded routine should continue to run.
    /// Otherwise, it will return false.  If returning false the calling threaded
    /// routine should return/exit.
    bool _cdecl Continue();
    void _cdecl End() const;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Thread();
    virtual ~Thread();

    /// This method will start the threaded routine from the derived class.
    /// \return
    /// This method returns true if the threaded routine was started otherwise it
    /// returns false.
    bool _cdecl Start() const;
    /// This method will start the threaded routine from the derived class.
    /// \param [in] ulTimeout
    /// This parameter denotes now long this method will wait for the thread
    /// to stop. This parameters unit are in milliseconds.
    /// \return
    /// This method returns true if the threaded routine was stopped before the
    /// specified timeout. Otherwise, it returns false.
    bool _cdecl Stop(unsigned long ulTimeout = 0xFFFFFFFF);

    /// This method will pause the threaded routine a given amount of time. The
    /// start of pause will occur when the threaded routine calls this class's
    /// Continue() method.  This method will not pause the threaded routine mid 
    /// iteration.
    /// \param [in] ulTime
    /// This parameter is the amount of time to pause at that start of the next
    /// iteration of the threaded routine.  This parameters units are milliseconds.
    /// \return
    /// This method will return true if the pause time was set. Otherwise, the method
    /// will return false.
    bool _cdecl Pause(unsigned long ulTime = 0xFFFFFFFF);
    /// This method will resume a paused thread.  The method will cut short the pause
    /// time set by this class's Pause() method.
    /// \return
    /// This method will return true if the threaded routine was successfully signaled to
    /// resume iterating. Otherwise, this method will return false.
    bool _cdecl Resume();

    /// This method will inform the caller if the threaded routine is currently
    /// running of is paused.
    /// \return
    /// This method will return true if the threaded routine is currently running
    /// or is paused.  Otherwise this method will return false.
    bool _cdecl Running() const;
    //***********************************************************************//
  }; // End of class Thread
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_THREADS_THREAD_HPP