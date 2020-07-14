#include "omniorbthread.h"

#include <echo.hh>
#include <ncurses.h>

#include <iostream>

OmniORBThread::OmniORBThread(int argc, char **argv, QObject *parent)
    : QThread(parent), _argc(argc), _argv(argv)
{
}

OmniORBThread::~OmniORBThread()
{
    cout << "OmniORBThread is over!";
}

void OmniORBThread::run()
{
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);

    if( _argc != 2 ) {
      std::cerr << "usage: <object reference>" << std::endl;
      exit(1);
    }

    CORBA::Object_var obj = orb->string_to_object(_argv[1]);
    Echo_var echoref = Echo::_narrow(obj);
    if( CORBA::is_nil(echoref) ) {
      std::cerr << "Can't narrow reference to type Echo (or it was nil)." << std::endl;
      exit(1);
    }
 		
		char input;                    
    CORBA::String_var dest = "";
 		initscr();
    printw("Please start to type your text!\n For exit press escape character! (ESC:u001B)\n");                   
 		refresh();
    do { 
			input = (char)getch();
      dest = echoref->echoString(&input);
		} while (input != '\u001B');
    endwin();


    orb->destroy();
  }
  catch(CORBA::TRANSIENT&) {
    std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << std::endl;
  }
  catch(CORBA::SystemException& ex) {
    std::cerr << "Caught a CORBA::" << ex._name() << std::endl;
  }
  catch(CORBA::Exception& ex) {
    std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
  }
  catch(omniORB::fatalException& fe) {
    std::cerr << "Caught omniORB::fatalException:" << std::endl;
    std::cerr << "  file: " << fe.file() << std::endl;
    std::cerr << "  line: " << fe.line() << std::endl;
    std::cerr << "  mesg: " << fe.errmsg() << std::endl;
  }
}
