#include <stdlib.h>
#include <string>
#include <ctime>

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
 * @file    Message.cpp
 * @date    September, 2019
 **/
class Message {

private:
  std::string header;

  std::string toUser;

  std::string fromUser;

  std::string subject;

  std::string message;

  time_t date;

public:
  Message(string to, string from, string subj, string msg) {

    // none of these require a custom destructor
    toUser = to;
    fromUser = from;
    subject = subj;
    message = msg;
    date = time(0); // date object for current time at creation

    // temp data, helper method to set header
    header = makeHeader();

  }

  string getHeader() {
    return header;
  }

  string getTo() {
    return toUser;
  }

  string getFrom() {
    return fromUser;
  }

  string getSubject() {
    return subject;
  }

  string getMessage() {
    return message;
  }

  string getDate() {
    char* dateTime = ctime(&date);
    return dateTime;
  }

  //TODO: to and from JSON

  //Setters shouldn't be needed. Messages will not need adjusted after construction

private:
  string makeHeader() {
    string header = fromUser + "\t";
    char* dateTime = ctime(&date);
    header.append(dateTime);
    return header;
  }

};
