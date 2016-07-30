//***************************************************************************//
// Multiplexer Interface
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

#ifndef MST_THREADS_MULTIPLEXER_HPP
#define MST_THREADS_MULTIPLEXER_HPP

//***************************************************************************//
// System Includes
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief Multiplexer is synchronization mechanism for multiple individual 
  /// synchronization objects.
  class Multiplexer
  {
  private:
    //***********************************************************************//
    // This Mutex is used for protecting the state of this object from possible
    // race conditions.
    class Mutex* mpMutex;

    // This vector holds handles (void*) to the synchronization instances passed
    // to this class.  This class retains the handles so that other class state
    // can be modified to accommodate new handles
    std::vector<void*> mvPersistentHandles;

    // This is array of handles (void*) this class will block on.
    void* mpArrayOfHandles;
    // This data member holds the current number of handles (void*) in the array
    // of handles.
    unsigned long mulCurrentArraySize;
  public:
    //***********************************************************************//
    Multiplexer();
    ~Multiplexer();

    /// This method will add an handle to synchronization object to this class.
    /// For the life of this class, that handle will be able to trigger a release 
    /// of hold the state of class as blocked, until it releases or another added
    /// handles releases.
    /// \param [in] pHandle
    /// Handle to synchronization to be added. NOTE, caller cannot safely free resources
    /// pointed to by the passed handle until caller's instance of this class is destroyed.               
    /// \return 
    /// This method will return true if the handle was successfully added. Otherwise,
    /// it will return false.
    bool _cdecl AddHandle(void* pHandle);
    /// This method will block until one of the added handles releases or until
    /// the specified wait time has expired. If no wait time is specified and no handle
    /// releases, the method will block indefinitely.
    /// \param [in] ulWait
    /// This parameter is the maximum amount of time this method will block while
    /// waiting for a handles to release.  This parameter is in milliseconds.
    /// \return
    /// This method will return true if a handle released. Otherwise, if no handle
    /// released and the wait time expired then the method will return false.
    /// The method will never return if no handle released and no wait time was
    /// passed in.
    bool _cdecl WaitForTrigger(unsigned long ulWait = ULONG_MAX) const;
    //***********************************************************************//
  }; // End of class Multiplexer 
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_THREADS_MULTIPLEXER_HPP