# 🔥 BlazeHTTP

### High-Performance Event-Driven HTTP Server (C++ / epoll)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-orange)
![Concurrency](https://img.shields.io/badge/I/O-epoll-purple)
![Architecture](https://img.shields.io/badge/Model-Event--Driven-green)

BlazeHTTP is a lightweight, high-performance HTTP server built in modern C++ using Linux’s `epoll` event notification system.

It demonstrates event-driven architecture, non-blocking sockets, routing, static file serving, and scalable connection handling.

This project mirrors foundational concepts used in production systems like Nginx and Node.js.

---

# 🚀 Features

* ⚡ Non-blocking TCP sockets
* 🔄 epoll-based event loop
* 🧭 Basic HTTP request parsing
* 🛣 Custom routing system
* 📁 Static file serving
* 🔁 Keep-alive connection support
* 🧱 Modular architecture (Router + Server separation)
* 🐧 Linux-native implementation

---

# 🏗 Architecture Overview

BlazeHTTP follows an event-driven model:

```
Socket → Non-blocking → epoll → Event Loop → Route → Response
```

Flow:

1. Create server socket
2. Set non-blocking mode
3. Register with epoll
4. Accept connections
5. Parse HTTP request
6. Route request
7. Send response
8. Close or keep-alive connection

This avoids thread-per-connection overhead and scales efficiently.

---

# 📁 Project Structure

```
BlazeHTTP/
│
├── src/
│   ├── main.cpp
│   ├── HttpServer.cpp
│   └── Router.cpp
│
├── include/
│   ├── HttpServer.h
│   └── Router.h
│
├── public/
│   └── index.html
│
└── README.md
```

---

# 🛠 Build Instructions (Linux / WSL)

BlazeHTTP uses Linux-specific headers (`epoll`, `unistd`, `fcntl`).

Compile with:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o blazehttp
```

---

# ▶️ Run

```bash
./blazehttp
```

You should see:

```
BlazeHTTP running on port 8080
```

---

# 🌐 Test in Browser

Open:

```
http://localhost:8080/
http://localhost:8080/status
http://localhost:8080/index.html
```

---

# 📌 Example Routes

| Route         | Description                |
| ------------- | -------------------------- |
| `/`           | Welcome message            |
| `/status`     | Health check endpoint      |
| `/index.html` | Static file from `public/` |

---

# 🧠 Engineering Concepts Demonstrated

* Event-driven architecture
* Non-blocking I/O
* epoll system calls
* Basic HTTP protocol handling
* Router abstraction
* Separation of concerns
* Scalable connection management

---

# ⚙️ Technologies Used

* C++17
* STL
* Linux system calls
* epoll
* TCP/IP sockets

---

# 🚀 Future Enhancements

* Full HTTP header parsing
* MIME type detection
* Logging middleware
* Thread pool worker model
* TLS support (OpenSSL)
* Benchmark testing (wrk)
* CMake build system
* Docker containerization

---

# 👨‍💻 Author

Katlego

---

# 📜 License

MIT License

---

