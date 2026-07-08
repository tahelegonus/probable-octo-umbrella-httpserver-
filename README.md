# probable-octo-umbrella-httpserver-
this is a tcp based http server written in using windows winsock api! i created this project after doing some research on C, socket creation, tcp, binding ports and accepting client conncections!

as im approaching my senior year, i wanted to get into the practice of actually using the knoweldge i paid for to some good use for fun labs in my free time. i have a pretty good u
nderstanding of "textbook networking", however i have only done network programming a few times. this low level network program was a great start to get my engine turning, and really understand how web servers work benath all the libraries and frameworks.

the server demonstrates the basic lifecycle of a **tcp server**: creating a **socket**, **binding it to an address and port**, listenting for incoming connections, accepting **clients**, and finally managing network comms using the **windows sockets api**

my orginal plan was to focus more on processing http traffic through html websites i made through powershell, however i realized i was getting a little ahead of myself, and needed to start with establishing connections first! 

# Features
- creates a TCP server socket using winsock2
- initalizes and manages the windows netowrking enviorment
- binds the server to localhost:8080 
- listens for incoming TCP connections
- accepts client connections
- handles basic client connection events
- provides console based server status messages!
- 
# Tech Used 
- C progaming language ( low level systems programming)
- windows sockets (winsock2 api) ( tcp/ip networking on windows)
- tcp/ip netowrking ( client server communication fundementals) 
- visual studio/minGW compatible ( compatible development enviorments)
- sockets programming ( direct interaction with network connections)

# Project Goals
 my main goal for this project was to truly understand how i can use programming, and network applications can be used together at a lower level. i am used to just seeing everything all clean in pretty in pcap files, and event logs, but i wanted to see things from the beggining. 

# How does proable octo umbrella work? 
proable octo umbrella follows the basic tcp serverflow. tcp might be my favorite componet of network layering, just becasue it gets stuff done! 

**intialize winsock:** before creating sockets, the winsock library must be intialzied, which is the key for this entire program to work!

WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData);
  
**create server socket:** the server creates a tcp socket (endpoint) that will be used to accept incoming client connections. specifcally, i used AF_NET for ipv4 communication, and SOCK_STREAM for tcp based socket.

SOCKET serverSocket; 
serverSocket = socket( 
AF_INET, 
SOCK_STREAM, 
IPPROTO_TCP 
);

**bind socket to lcoalhost:8080:** the socket is assgined to the local machine and port 8080, where using binding tells the operating system where the server should recieve incoming connec tions.

bind(
    serverSocket,
    (struct sockaddr*)&serverAddress,
    sizeof(serverAddress)
);
   
**listen for incoming connections:** the server switches into listening mode and waits for clients! 

listen(serverSocket, SOMAXCONN);
   
**accept client connections:**  when a client connections, the server accepts the connection and creates a client socket!

SOCKET clientSocket; 
clientSocket = accept( 
serverSocket, 
NULL, 
NULL 
);

**close the connection:** after handeling the client, the sockets are closed and winsock is cleaned up! this process releases the network resources used by the application! 

closesocket(clientSocket); 
closesocket(serverSocket); 
WSACleanup();

# How was proable octo umbrella tested? 
long story short, the server was tested by attempting to connect to the open tcp port, which i used powershell to simulate this test!

start the server: 
.\httpserver.exe

the server  displayed:

server starting...
socket created!
server bound to port 8080!
server listening...

then, in another PowerShell window, i ran:

Test-NetConnection localhost -Port 8080

output:
ComputerName     : localhost
RemotePort       : 8080
TcpTestSucceeded : True

with a sucessful connection, it seals the deal that the connection to the server happend correctly! 

# FUTURE IMRPOVEMENTS !
Now, a disclaimer, like i mentioned previously, after this intital test, it only accepts the tcp connections, so it does not send http responses. even though the server opens: http://localhost:8080, it does connect not fully show a webpage. for my step up from this project, i will allow the sever to parse the rquests and return html content! 

**improvements for the future:**
- parse http requests
- return http response headers
- serve html files
- support multiple clients
- add logging
- add multithreading

# Author 
created as a networking and systems programming project!! 








