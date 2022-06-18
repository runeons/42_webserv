# 42 Webserv

#### Overview
⭐ C++ first real-life project  
This is a 42 project whose aim it to write a C++ HTTP server from scratch.
#### Introduced concepts
⭐ HTTP communication functions

server : 
    socket --> bind --> listen --> accept --> send/recv
⭐ select() -> asynchronous communication
⭐ HTTP RFC reading 
⭐ HTTP status codes  
⭐ HTTP headers + body  
    - request parsing  
    - response writing  
⭐ MIME type detection  
⭐ PHP CGI environment variables  
⭐ select/socket/listen suite    
⭐ select/socket/listen suite     
⭐   
⭐   
⭐   
#### Description
- Write an HTTP server in C++ that enables:
    - GET, POST, DELETE methods
    - multiple ports listening
    - files upload
    - CGI execution
- Read configuration file, that can set up:
    - host and port
    - default error pages
    - client body size limit
    - routes configuration
    - autoindex option
    - upload option
    - 301 redirection
#### Restrictions
- C++ 98 standard
#### Usage
    make && ./webserv [configuration file]
On web browser :  

    127.0.0.1:8000 (default port)
