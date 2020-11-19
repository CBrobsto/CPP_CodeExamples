#include "MessageGui.cpp"
#include "Message.cpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <list>
#include <vector> // remove later
#include <stdlib.h>

#include <fstream>
#include <string>
#include <json/json.h>


using namespace std;

/**
 * Copyright (c) 2019 Tim Lindquist, Cody Brobston
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
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @author Cody Brobston
 * @file    Controller.cpp
 * @date    September, 2019
 **/
class SampleStudentClient : public MessageGui {

   /** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */
   static void ClickedX(Fl_Widget * w, void * userdata) {
      std::cout << "You clicked Exit" << std::endl;
      exit(1);
   }

   static void ClickedGet(Fl_Widget * w, void * userdata) {
      // since this is a static method, it does not have access to any instance variables.
      // get access through the userdata argument which is the instance.
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      std::cout << "You clicked Get" << std::endl;
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;
      Fl_Check_Browser * headers = anInstance->headerFCB;

      // clear all existing entries from the list of message headers
      headers->clear();

      // lets setup some sample entries in the FCB
      // first get the date and place its string form into dateFI
      // get the time in a string
      auto aClk = std::chrono::system_clock::now();
      auto aTime = std::chrono::system_clock::to_time_t(aClk);
      std::string aDateStr(ctime(&aTime));
      // the conversion to string adds a new line at the end of the string. Trim it.
      std::string trimmed(trimMe(aDateStr));
      // load the date field with the current time in string form
      //dateFI->value(ctime(&aTime));
      dateFI->value(trimmed.c_str());
      std::cout << "date un-trimmed: "<<aDateStr<<". Date from the UI control: "
                << dateFI->value()<<std::endl;
      // get the instance's userId string so we know who is sending messages
      std::string userId = anInstance->userId;
      // all FLTK controls are loaded via c strings, not c++ string objects.
      headers->add((userId+"   "+trimmed).c_str());
      // select this first element in the list. the first arg is the index into the
      // list (1st entry) beginning at 1. The second arg is 0 for unchecked and 1 for
      // checked.
      headers->checked(1,1);
      // fill in the corresponding fields as if we are displaying a real message.
      toFI->value(userId.c_str());
      fromFI->value(userId.c_str());
      dateFI->value(trimmed.c_str());
      subjectFI->value("Sample Message");
      std::string msg("Hello,\n    FLTK stands for Full Light ToolKit\nEnjoy!");
      messageFMI->value(msg.c_str());
      // add another header
      headers->add("Kevin.Gary   Thu Dec 20 1:25:00 2018");

  }

   static void ClickedDelete(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Input * from = anInstance->fromFI;
      std::string fr(from->value());
      std::cout << "You clicked Delete" << std::endl;
   }

   static std::string& trimMe (std::string& str) {
      // right trim
      while (str.length() > 0 && (str[str.length()-1] == ' ' || str[str.length()-1] == '\t'
                                  || str[str.length()-1] == '\n' ||  str[str.length()-1] == '\r')){
         str.erase(str.length ()-1, 1);
      }
      // left trim
      while (str.length () > 0 && (str[0] == ' ' || str[0] == '\t')){
         str.erase(0, 1);
      }
      return str;
   }

   static void SelectedHeader(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Check_Browser * headers = anInstance->headerFCB;
      int howMany = headers->nitems();
      int which = headers->value();
      std::cout << "You selected a new message header. Index: " << which << std::endl;

      // unselect all but the item just selected. Note, first item is item 1 not 0
      for(int i=1; i<howMany+1; i++){
         if(i != which ){
            headers->checked(i,0);
            std::cout << "calling checked("<< i << ")" << std::endl;
         }
      }
      std::cout << "You selected item " << which << " text " << headers->text(which)
                << "\nbrowser size is " << howMany
                << std::endl;
   }

public:
   std::string userId;

   // TODO: rename
   SampleStudentClient(const char * name = 0) : MessageGui(name) {
      getButt->callback(ClickedGet, (void*)this);
      deleteButt->callback(ClickedDelete, (void*)this);
      headerFCB->callback(SelectedHeader, (void*)this);
      headerFCB->when(FL_WHEN_CHANGED);

      callback(ClickedX);

      userId = "Cody.Brobston";
   }

};

int main() {
   SampleStudentClient cm("Cody Brobston's Message Browser");

   cout << "Sample Message Headers:\n";
   Message* msg1 = new Message("To someone", "From someone", "sample subject", "message contents");
   Message* msg2 = new Message("someone else", "from me", "sample subject #2", "message contents #2");

   std::list<Message*> myMsgs;
   myMsgs.push_back(msg1);
   myMsgs.push_back(msg2);

   std::list<Message*>::iterator iter;
   iter = myMsgs.begin();
   while( iter != myMsgs.end() ) {
     cout << (*iter)->getHeader() << std::endl;
     iter++;
   }

   return (Fl::run());

}
