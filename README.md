# 🔥 BlazeHTTP

### High-Performance Event-Driven HTTP Server (C++ / epoll)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-orange)
![I/O Model](https://img.shields.io/badge/I%2FO-epoll-purple)
![Architecture](https://img.shields.io/badge/Model-Event--Driven-green)

BlazeHTTP is a lightweight, high-performance HTTP server built in modern C++ using Linux’s `epoll` event notification system.

It demonstrates event-driven architecture, non-blocking sockets, routing, static file serving, and scalable connection handling.

This project mirrors foundational concepts used in production systems such as **Nginx**, **Node.js**, and other high-performance networking systems.

---

# 📑 Table of Contents

* [Overview](#-overview)
* [Features](#-features)
* [Screenshots](#-screenshots)
* [Architecture Overview](#-architecture-overview)
* [How It Works](#-how-it-works)
* [Project Structure](#-project-structure)
* [Build Instructions](#-build-instructions-linux--wsl)
* [Run the Server](#-run-the-server)
* [Testing the Server](#-testing-the-server)
* [Example Routes](#-example-routes)
* [Engineering Concepts Demonstrated](#-engineering-concepts-demonstrated)
* [Performance Characteristics](#-performance-characteristics)
* [Future Enhancements](#-future-enhancements)
* [Author](#-author)
* [License](#-license)

---

# 📖 Overview

BlazeHTTP is built around a single-threaded, event-driven model using:

* Non-blocking sockets
* `epoll` for scalable I/O multiplexing
* Custom router abstraction
* Static file serving from a `public/` directory
* Keep-alive HTTP support

Unlike thread-per-connection models, BlazeHTTP handles thousands of connections efficiently without creating multiple threads.

---

# 🚀 Features

✔ Non-blocking TCP sockets
✔ epoll-based event loop
✔ Event-driven architecture
✔ Custom routing system
✔ Static file serving
✔ Keep-alive support
✔ Modular code design
✔ Linux-native implementation
✔ Clean separation of concerns

---

# 📸 Screenshots

## 🚀 Server Running
<img width="931" height="123" alt="Screenshot 2026-03-03 125853" src="https://github.com/user-attachments/assets/ab03342e-f093-428e-b068-8d9de02f7251" />




---

## 🌐 Browser Access via WSL IP

<img width="819" height="506" alt="http server" src="https://github.com/user-attachments/assets/e41650a5-9e33-4eed-b037-a0ca1a370dbf" />



---

## 🌐 Browser Access via localhost

<img width="780" height="293" alt="image" src="https://github.com/user-attachments/assets/5a7bbae4-da7e-41c5-a5c8-4dea1db476c8" />


---

# 🏗 Architecture Overview

BlazeHTTP follows this model:

```
Socket → Non-blocking → epoll → Event Loop → Route → Response
```

Core components:

* **HttpServer**

  * Manages sockets
  * Registers file descriptors with epoll
  * Accepts and processes connections

* **Router**

  * Maps URL paths to handler functions
  * Returns response body

* **public/**

  * Static file directory

---

# ⚙️ How It Works

1. Create TCP server socket
2. Set socket to non-blocking mode
3. Register server socket with epoll
4. epoll waits for events
5. On connection:

   * Accept client
   * Add client FD to epoll
6. On readable event:

   * Parse HTTP request
   * Route path
   * Build HTTP response
   * Send response
   * Close or keep-alive

This avoids blocking calls and scales efficiently.

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
├── http server.png
├── https.png
├── server works.png
│
└── README.md
```

---

# 🛠 Build Instructions (Linux / WSL)

BlazeHTTP uses Linux-specific headers:

* `<sys/epoll.h>`
* `<unistd.h>`
* `<fcntl.h>`
* `<netinet/in.h>`

Compile using:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o blazehttp
```

---

# ▶️ Run the Server

```bash
./blazehttp
```

Expected output:

```
BlazeHTTP running on port 8080
```

---

# 🌐 Testing the Server

Open in browser:

```
http://localhost:8080/
http://localhost:8080/status
http://localhost:8080/index.html
```

If using WSL2:

```
http://<WSL-IP>:8080/
```

Find WSL IP using:

```bash
ip addr show eth0
```

---

# 📌 Example Routes

| Route         | Description                    |
| ------------- | ------------------------------ |
| `/`           | Welcome message                |
| `/status`     | Health check endpoint          |
| `/index.html` | Static file from public folder |

---

# 🧠 Engineering Concepts Demonstrated

* Event-driven architecture
* Non-blocking I/O
* epoll system call usage
* Basic HTTP parsing
* Socket programming
* File descriptor management
* Router abstraction
* Separation of concerns
* Scalable connection handling

---

# 📊 Performance Characteristics

BlazeHTTP:

* Avoids thread-per-connection overhead
* Uses edge-triggered event notification (epoll)
* Minimizes context switching
* Handles concurrent connections efficiently
* Scales better than blocking models

---

# 🚀 Future Enhancements

* Full HTTP/1.1 compliance
* MIME type detection
* Access logging
* Middleware support
* Thread pool model
* HTTPS (OpenSSL integration)
* Benchmarking with `wrk`
* CMake build system
* Docker support
* CI/CD integration

---

# 👨‍💻 Author

Katlego

---

# 📜 License

MIT License

---

