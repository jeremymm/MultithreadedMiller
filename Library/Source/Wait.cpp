//***************************************************************************//
// Wait method Implementation
//
// Created: July 1, 2008
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
#ifdef WINDOWS_THREADS
#include <Windows.h>
#endif
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Wait.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //-------------------------------------------------------------------------//
  void Wait(unsigned long ulMilliseconds)
  {
#ifdef WINDOWS_THREADS
    Sleep(ulMilliseconds);
#endif
  }
  //-------------------------------------------------------------------------//
} // End of namespace MST
//***************************************************************************//
