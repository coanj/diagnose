#include <iostream>
#include <thread>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
    Needs to be compiled with g++ std=c++11 -pthread
    flags in order to take advantage of the threading.
    
    "iperf -s -D" needs to be running on the server in order
    to test the bandwidth, -D makes it run in daemon mode.
*/

/*
    Used to diagnose the network/cpu using the python script
    "diagnose". It takes a string command, host ip, and pointer to
    the status variable. (status = 1 if goop, status will = 0 if bad)
*/
void diag(string command, char* host,int *status) {
    char s[200] = "./diagnose ";
    if(command=="ping"){
        strcat(s,"ping ");
        strcat(s,host);
    } else if (command == "bw"){
        strcat(s,"bw ");
        strcat(s,host);
    } else {
        strcat(s,"cpu");
    }
    FILE * cmd = popen( s, "r" );
    if ( cmd == 0 ) {
        fprintf( stderr, "Could not execute\n" );
        *status = -1;
        exit(-1);
    }
    char result[ sizeof(int) ];
    fgets( result, sizeof(int),  cmd );
    pclose( cmd );
    *status = (int)*result-48;
}

/*
    Other is for testing purposes and will show that as this thread
    runs, the status set by diag() will change at the same time and so
    can be used to stop this process.
*/
void other(int *status) {
    /*
        All of this is for testing purposes
        remove when done testing
        This first line may or may not return 0, depending on the test
        and if that test passes diag.
     */
    cout << "Status = " << *status << endl;     //  Test status while before loop
    cout << "Loop for pause to test multithreading\n";
    for(int i = 0; i <=1000000000; i++){}
    cout << "Status = " << *status << endl;     //  Test status after loop.
    
    /*
        If testing cpu with "stress -c 2" running which will cause the cpu test
        to change status to 0.
        
        If possible, altering the network connection to run less than a 28.8kbps
        modem will cause diag to set status to 0.
        
        If no network connection is made or packet loss occurs, diag will cause
        status to return 0.
    */
}


int main() {
    int netstat = 1;                //  Status of network/cpu (1=good, 0=bad)
    char host[200] = "127.0.0.1";   //  host to be tested
    
    /*
        The following spawns a new thread per each command, which allows
        other commands to be ran without stopping the system. The diag
        commands will set netstat to be either:
                0 (which means a bad result)
                1 (which means a good result)
        
        The second thread (other) is setup to work with the client or
        however we implement this system from the client side. As it is
        shown below, running the first thread(diag) will not interfere with
        whatever is ran in the second thread.
    */
    
    //  To test each, uncomment one at a time.
    thread first (diag, "ping", host, &netstat);    //  spawn new thread to test ping
    // thread first (diag, "bw", host, &netstat);      //  spawn new thread to test bw
    // thread first (diag, "cpu", host, &netstat);     //  spawn new thread to test cpu
    
    thread second (other, &netstat);     //  spawn new thread to run other processes

    // synchronize threads:
    first.join();   //  Diagnose thread
    second.join();  //  Other thread for client or whatever

    return 0;
}