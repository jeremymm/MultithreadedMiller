//***************************************************************************//
// Timer Class Interface
//
// Created May 14, 2005
// By: Jeremy Michael Miller
//
// Copyright (c) 2005-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2006-2016, Multithreaded Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_THREADS_TIMER_HPP
#define MST_THREADS_TIMER_HPP

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  /// \brief This enumeration is used to identify individual timers in the 
  /// Timer class.
  enum Timers
  {
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
    TIMER_6,
    TIMER_7,
    TIMER_8,
    NUMBER_OF_TIMERS
  }; // End of enum Timers
  //*************************************************************************//

  //*************************************************************************//
  /// \brief The Timer class is high resolution timer. It can manage up to 
  /// Timers::NUMBER_OF_TIMERS sets of time.
  class Timer
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // This data member is simply an array of the last tick count for individual
    // timestamps.
    long long mllStartClocks[NUMBER_OF_TIMERS];
    // This data member is calculated when this class is instantiated and used to 
    // convert time in terms of seconds from a tick count.
    double mdInverseClockRate;
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Timer();
    ~Timer();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method returns the the amount of time since the last time this 
    /// method was called.
    /// \param [in] eTimer
    /// This parameter is the timer to measure.
    /// \return 
    /// This method returns timer in units of seconds.
    double DT(enum Timers eTimer);
    /// This method returns the the amount of time since the last time the 
    /// DT() method was called.
    /// \param [in] eTimer
    /// This parameter is the timer to measure.
    /// \return 
    /// This method returns timer in units of seconds.
    double ET(enum Timers eTimer);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Timer
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//
#endif MST_THREADS_TIMER_HPP