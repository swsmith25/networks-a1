# Networks-a1
Socket assignment for Networks class
## Group 17
### Bo Smith | swsmith25 | ss97732
### Harry    | harrymay  | hsm759

# Report

## Part 1
- iperfer client results when running it for 10 seconds in the given two_hosts_direct topology  
As seen in the image Throuput measure 144.3Mbps on the server and 144.4 on the client. There no information lost as both the sent and recieve data measurements wer equal. So there might be a relatively negligible discrepancy in the timing meansurements.
![Part1 Output](.\pt1_throughput_screenshot.png)
## Part 2
### Q1: Basic measurements
- Measure and report average RTT and throughput between two adjacent routers, r1 and r2.  
AVG RTT:    
675 ms / 10 packets = **67.5 ms**  
  
AVG Thrpughput:  
(640B * 8)/9.176s = **558Mbps**  
  
- Measure and report average RTT and throughput between two hosts, h1 and h4.  
    - AVG RTT:  
**1.193ms**  
  
    - AVG Throughput:  
640*8 / 9038 = **566Mbps**  
### Q2: Impact of multiplexing on latency.
-  Measure and report average RTT between two hosts, h1 and h4, while measuring bandwidth between h2 and h5.
    - AVG RTT:    
**82.414ms**  

- How does it compare to the measured latency in Q1 (RTT between h1 and h4)?     
The latency increased significantly while measuring bandwidth between h2 and h5. This behavior makes sense as the ping communication must share the inter-router link with the iperfer communication.

### Q3: Impact of multiplexing on throughput
- Report the throughput between a pair of hosts varying the number of host pairs that conduct measurements.
    - A(h1, h4) only
        - 116.9Mbps
    - A(h1, h4) and B(h2, h5)
        - A= 86.3 Mbps and B=91.7 Mbps
    - A(h1, h4) and B(h2, h5) and C(h3, h6)
        - A=60.9 Mbps and B= 44.9Mbps and C=77.8 Mbps

- How do the three measurements varying the number of concurrent host pairs compare to the measured throughput in Q1 (between h1 and h4)? What’s the trend between measured throughput and the number of host pairs?  
  
    The more host-pairs are communicating on the network, the lower the throughput becomes. Having one host-pair (h1, h4) resulted in the highest throughput. It didn't have to share the information highway with other pairs.  
    It is a similare result as in Q2.
      
### Q4: Impact of link capacity on end-to-end throughput and latency.
- Measure and report path latency (average RTT) and throughput between two hosts, h1 and h4. How does it change compared to Q1?    

    RTT stayed relatively the same, measured at 1.254 ms. Throughput aptly decreased to reflect the link capacity of 1Mbps. Througput measured at 1.1 Mbps with 1410 kilobytes sent between h1 and h4.

### Q5: Impact of link latency on end-to-end throughput and latency.
- For each case below, measure and report path latency (average RTT) and throughput between two hosts, h1 and h4.
    - 10ms link delay  
        - AVG_RTT= 12.427 ms
        - Throughput= 111.5 Mbps
    - 100ms link delay 
        - AVG_RTT= 111.43 ms
        - Througput= 83.2 Mbps
    - 1s link delay  
        - AVG_RTT= 1101 ms
        - Throughput= 3.1 Mbps


- What’s the trend between the measured throughput and latency?  
    As the link delay increased, the latency increased and the throughput decreased.
![P2-Q5 Output](.\q5_1sdelay_output.png)