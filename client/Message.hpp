#include <string>

using namespace std;

/**
 * Copyright (c) 2019 Cody Brobston
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ FLTK client UI for Message management.
 * This class extends the Gui component class MessageGui and demonstrates
 * sample control functions that respond to button clicks drop-down selects.
 * This software is meant to run on Linux and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author  Cody Brobston
 * @file    Message.hpp
 * @date    September, 2019
 **/
class Message {

public:
  Message(string to, string from, string subj, string msg);

  string getHeader();

  string getTo();

  string getFrom();

  string getSubject();

  string getMessage();

  string getDate();

private:
  string makeHeader();

  std::string header;

  std::string toUser;

  std::string fromUser;

  std::string subject;

  std::string message;

  time_t date;

};
