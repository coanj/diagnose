# Cloud-Robotics
OSU Senior Capstone 2015-2016

##Network and CPU diagnostic tool - DIAGNOSE

###usage:
* diagnose bw host
* diagnose ping host
* diagnose cpu

####returns:	
* -1 = error
*  1 = ready to go

###Minimum bandwidth:
minBW = 150 Kbps  <---  Subject to change

###CPU Load threshold:
thresh = 0.75%  <---  Subject to change

####Threshold notes for clarity:
Threshold for average cpu load over 1 minute span.
* cpu < 1.00 means room for more traffic
* cpu = 1.00 means the cpu is exactly at capacity
* cpu > 1.00 means there's backup

setting threshold at 0.75 gives room for other processes and no backup.
All tools have been tested and are functional over a network.

##Driver for DIAGNOSE
######Compile using g++ std=c++11 -pthread
######Server needs to be running "iperf -s -D" in order to test bandwidth

This will test DIAGNOSE in a thread while allowing another process to be ran in the secondary thread.

If testing cpu with "stress -c 2" running which will cause the cpu test to change status to 0.
If possible, altering the network connection to run less than a 28.8kbps modem will cause diag to set status to 0.
If no network connection is made or packet loss occurs, diag will cause status to return 0.

* netstat = (1=good, 0=bad) depending on the return value from DIAGNOSE
* host = (ip address of host to be tested)

In order to test each aspect, uncomment the thead in main with the command that needs to be tested. Leave the second thread to run at the same time. The second thread will show the status before and after a short amount of time has passed. This will show that diag() can be ran simultaineously as another thread runs and can change the status, which can be used to alter the behavior of the second thread.
