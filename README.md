# Networks-a1
Socket assignment for Networks class
## Group 17
### Bo Smith | swsmith25 | ss97732
### Harry    | harrymay  | hsm759

# Report

## Part 1
iperfer client results when running it for 10 seconds in the given two_hosts_direct topology.

- Two hosts, h1 and h2, are directly connected to each other in this topology.
You can start a Kathara lab and connect to a virtual network device as in A0.
In the terminal for each host, your binary is located in /shared directory. This is a mirror of files located in labs/two_hosts_direct/shared directory on the CloudLab node.
## Part 2
### Q1: Basic measurements
- Measure and report average RTT and throughput between two adjacent routers, r1 and r2.
- Measure and report average RTT and throughput between two hosts, h1 and h4.
### Q2: Impact of multiplexing on latency.
-  Measure and report average RTT between two hosts, h1 and h4, while measuring bandwidth between h2 and h5.
- How does it compare to the measured latency in Q1 (RTT between h1 and h4)?
### Q3: Impact of multiplexing on throughput
Report the throughput between a pair of hosts varying the number of host pairs that conduct measurements.
The host pairs are (h1,h4), (h2,h5), (h3,h6).
e.g., First, measure throughput between (h1,h4). Then measure throughput between (h1, h4) and throughput between (h2,h5) simultaneously. 
Finally, do the measurements on (h1,h4), (h2,h5), and (h3,h6) simultaneously.
- How do the three measurements varying the number of concurrent host pairs compare to the measured throughput in Q1 (between h1 and h4)?
- What’s the trend between measured throughput and the number of host pairs?
### Q4: Impact of link capacity on end-to-end throughput and latency.
Decrease link rate between r1 and r2 to 1Mbps. This can be done by uncommenting line #5 in the labs/six_hosts_two_routers/r1.startup and labs/six_hosts_two_routers/r2.startup files. You have to clean up the previous Kathara lab before every change. Relaunch it after the changes.
- Measure and report path latency (average RTT) and throughput between two hosts, h1 and h4.
- How does it change compared to Q1?
### Q5: Impact of link latency on end-to-end throughput and latency.
Comment out the lines that you uncommented for the previous question.
For each case below, measure and report path latency (average RTT) and throughput between two hosts, h1 and h4.
Change the link delay between r1 and r2 to 10ms by uncommenting line #6 of the r1.startup file.
Change the link delay between r1 and r2 to 100ms by uncommenting line #7 of the r1.startup file. Comment out its line #6.
Change the link delay between r1 and r2 to 1s by uncommenting line #8 of the r1.startup file. Comment out its line #7.
- What’s the trend between the measured throughput and latency?
