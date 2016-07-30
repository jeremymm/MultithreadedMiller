//***************************************************************************//
// Mutex Class Interface
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

#ifndef MST_THREADS_MUTEX_HPP
#define MST_THREADS_MUTEX_HPP

//***************************************************************************//
// System Includes
#include <limits.h> // Used for ULONG_MAX
//***************************************************************************//

//***************************************************************************//
// Local includes
#include "Sync.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief Mutex is class that provides synchronization of critical sections
  /// between more than one threads. Single threads that repeatedly call this class's
  /// locking methods will not block.  However, calls to this class's locking 
  /// methods by more than one thread have to potential to block.
  class Mutex : public Sync
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    Mutex();
    ~Mutex();

    /// This method will block and therefore protect a critical section if this
    /// method will called by more than one thread. If them method is called
    /// by the same thread more than once, it will not block
    /// \param [in] ulWait
    /// This parameter is the amount of time this method attempts to attain a
    /// lock.  If no wait time is specified this method will block indefinitely or 
    /// until the lock is attained.
    /// \return
    /// This method will return true if the lock was attained. Otherwise, if the 
    /// wait time has expired before the lock is attained, this method will 
    /// return false.
    bool _cdecl Lock(unsigned long ulWait = ULONG_MAX) const;
    /// This method will releases an attained locks. If no lock was attained by 
    /// the calling method, this method has no effect.
    void _cdecl Unlock() const;
    //***********************************************************************//
  }; // End of class Mutex
  //*************************************************************************//
} // End of namespace HabuThread
//***************************************************************************//

#endif MST_THREADS_MUTEX_HPP