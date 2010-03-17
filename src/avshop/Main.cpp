#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "Wt/WServer"

#include "ShopApplication.h"

void killExistingPid()
{
    int pid;
    ifstream myfile ("/tmp/avshopstub.pid");
    if (myfile.is_open())
    {
      while (! myfile.eof() )
      {        
        myfile >> pid;        
        if (pid)
        {
            cout << "kill " << pid << endl;

            kill(pid, SIGTERM);
            pid = 0;
        }
      }
      remove("/tmp/avshop.pid");
      sleep(1);
      myfile.close();
    }
}

void storePid()
{
    ofstream myfile("/tmp/avshopstub.pid");
    if ( ! myfile )
    {
      cout << "Coudln't open pid file!" << endl;
    }
    else
    {
        std::cout << "Pid: " << getpid() << std::endl;
        std::cout << "Ppid: " << getppid() << std::endl;

        myfile << getpid() << std::endl;
        myfile << getppid() << std::endl;

        myfile.close();
    }
}

void killExistingWebServer()
{
    try
    {
        killExistingPid();
        storePid();
    }
    catch(...)
    {
        std::cout << "Couldn't kill existing webserver.";
    }
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new ShopApplication(env);
}

int WRun2(int argc, char *argv[], ApplicationCreator createApplication)
{
  try {
    // use argv[0] as the application name to match a suitable entry
    // in the Wt configuration file, and use the default configuration
    // file (which defaults to /etc/wt/wt_config.xml unless the environment
    // variable WT_CONFIG_XML is set)
    WServer server(argv[0]);

    // WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

    // add a single entry point, at the default location (as determined
    // by the server configuration's deploy-path)
    server.addEntryPoint(Wt::Application, createApplication, "/a");
    if (server.start()) {
      int sig = WServer::waitForShutdown();

      std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
      server.stop();
    }
  } catch (WServer::Exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << "\n";
    return 1;
  }
}

int main(int argc, char **argv)
{
    //--docroot ./var/www --config ./etc/wt_config.xml --pid-file /tmp/avshop.pid --http-address 0.0.0.0 --http-port 8080

    killExistingWebServer();

    /*
    * Your main method may set up some shared resources, but should then
    * start the server application (FastCGI or httpd) that starts listening
    * for requests, and handles all of the application life cycles.
    *
    * The last argument to WRun specifies the function that will instantiate
    * new application objects. That function is executed when a new user surfs
    * to the Wt application, and after the library has negotiated browser
    * support. The function should return a newly instantiated application
    * object.
    */
    return WRun(argc, argv, &createApplication);
}


