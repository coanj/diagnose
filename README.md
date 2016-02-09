# Cloud-Robotics
OSU Senior Capstone 2015-2016

##Network and CPU diagnostic tool
######Server needs to be running "iperf -s" in order to test bandwidth

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

