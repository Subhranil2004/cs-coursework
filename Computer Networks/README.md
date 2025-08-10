> In Linux Environment

## Assignment 1: Stream Socket

1. Write a program for a time server. The time server informs the current time to the client when the server gets a request from a client. Also, write the client program.

2. Write an EchoClient and EchoServer program using TCP sockets, where the server echoes the message sent by the client in reverse case (e.g., if the client says "Hello", the server replies with "hELLO"), and also prints the client’s IP address on the server’s console. Use separate machines on the same network for client and server, if possible.

3. Consider a networked system with two kinds of processes: **hater** (spreads hatred when contacted) and **lover** (teaches love to its contacts). Haters and lovers are servers in the system. Assume an environment where haters dominate (high probability, e.g., 0.8). When an ordinary process (client) contacts a server, the server disseminates its teaching (hatred or love) along with its identity. Although haters are densely populated, the instinct of an ordinary process is to search for love. The search ends when it contacts a lover.

   - (i) Write the server program as stated above. Use your ID as the identity of your server process. When your server responds to a client, your ID is appended in the response. Use port number **12345** for the server.
   - (ii) Write the client program for the stated purpose. The client repeatedly and arbitrarily contacts servers until it reaches a lover. The client reveals the identity of servers by printing their IDs.

4. Update the client program of Q3 to get the complete list of lovers and haters running in the system at a given time.

---

## Assignment 2: Concurrent Servers

1. Write a concurrent version of the server from Q3 of Assignment 1 (lover-hater server) by forking a child per client. Show the requesting client's ID and the serving child's PID. Point out its advantage compared to the previous version.

2. Write the above program using threads.

---

## Assignment 3: Datagram Socket

1. Write a day time client and server program using datagram sockets.

2. Consider the lover-hater problem from Assignment 1. Prepare the server using datagram sockets. Allow the client to broadcast a message "Your teaching" in the network. After receiving this message, lovers and haters reply to the requesting client by writing "love" and "hate" respectively. As before, append your ID in the message. The client program should output the IDs and the servers' identity (lover/hater). A final count of lovers and haters should also be reported.

---

## Assignment 4: Raw Socket

1. Write a program that reads all TCP, UDP, and ICMP packets arriving at the host and outputs the packet type (TCP, UDP, or ICMP) and sender’s IP address.

2. Run the ping program described in the given text (SockBook). Point out the limitations (compared with the available ping command) and modify the program to overcome those limitations.

3. Write a program to trace the route between two machines. The output should be a list of all routers along the path to a given destination.

   > **Hint:** The Time-To-Live (TTL) field in an IP header is used to recover from routing errors. When the datagram passes a router, the TTL field is decremented by 1. If it reaches 0, the router discards the datagram and sends an ICMP time exceeded (ICMP TIMXCEED) message back to the sender. The sender can then get the router’s IP address.

---

## Assignment 5: Packet Socket

1. Write a program to capture all the packets in promiscuous mode.
