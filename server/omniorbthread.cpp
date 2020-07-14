#include "omniorbthread.h"

#include <echo.hh>

#include <iostream>

class Echo_i : public POA_Echo
{
public:
  inline Echo_i() {}
  virtual ~Echo_i() {}
  virtual char* echoString(const char* mesg);
};
char* Echo_i::echoString(const char* mesg) 
{
  std::cout << "UPCALL: " <<  mesg << std::endl;
  return CORBA::string_dup(mesg);
}
OmniORBThread::OmniORBThread(int argc, char **argv, QObject *parent)
    : QThread(parent), _argc(argc), _argv(argv) 
{
}
OmniORBThread::~OmniORBThread() 
{
  std::cout << "OmniORBThread is over!" << std::endl;
}
void OmniORBThread::run()
{
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);

    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    Echo_i* myecho = new Echo_i();
      
    PortableServer::ObjectId_var myechoid = poa->activate_object(myecho);

    obj = myecho->_this();
    CORBA::String_var sior(orb->object_to_string(obj));
    std::cout << (char*)sior << std::endl;

    myecho->_remove_ref();

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    orb->run();
  }
  catch(CORBA::SystemException& ex) {
    std::cerr << "Caught CORBA::" << ex._name() << std::endl;
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
