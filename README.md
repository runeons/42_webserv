# 42 Webserv

    
💙 C++ first real-life project  

#### Overview
This is a 42 project whose aim it to write a C++ HTTP server from scratch.

#### Introduced concepts
⭐ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Waiting for I/O - asynchronous interface using select()  
⭐ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;HTTP RFC reading (status codes + request/reponse headers)  
⭐ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MIME type detection  
⭐ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PHP CGI environment variables  
⭐ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sockets communication sequence  
> server : socket() --> setsockopt() --> bind() --> listen() --> accept() --> send()/recv()  


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
    
#### Authors

- [@tsantoni](https://www.github.com/voltaire-stn)
- [@tharchen](https://www.github.com/Bressack)
