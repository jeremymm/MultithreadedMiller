//***************************************************************************//
// Sync Class Interface
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

#ifndef MST_THREADS_SYNC_HPP
#define MST_THREADS_SYNC_HPP

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief Sync is very simple base class that holds a handle to used by 
  /// derived classes.  This handle is required by other 
  /// synchronization mechanisms.
  class Sync
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  protected:
    //***********************************************************************//
    // This pointer will point to the OS dependent synchronization object.
    // This is also called a "handle" to the synchronization object buy some
    // operating systems. This library will follow that convention.
    void* mvpSyncObject;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Sync();
    virtual ~Sync();

    /// This method provides public read only access to the synchronization objects
    /// handle.
    /// \return
    /// This method will return the handle to the synchronization handle.
    void* _cdecl Handle() const;
    //***********************************************************************//
  }; // End of class Sync
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_THREADS_SYNC_HPP