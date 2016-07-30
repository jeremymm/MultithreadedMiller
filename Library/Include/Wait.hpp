//***************************************************************************//
// Sleep Method Interface
//
// Created: Jun 23, 2008
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

#ifndef MST_THREADS_WAIT_HPP
#define MST_THREADS_WAIT_HPP

//***************************************************************************//
namespace MST
{
  /// This method will block while waiting for the passed in amount of time to
  /// expire.
  /// \param [in] ulTime
  /// This parameter this is amount of time this method will block. This 
  /// parameters units are in milliseconds.
  void _cdecl Wait(unsigned long ulTime);
} // End of namespace MST
//***************************************************************************//

#endif MST_THREADS_WAIT_HPP