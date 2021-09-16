# socket-programming

core socket programming in C

- `/tcp` - IP and Port based network socket
- `/internal` - Domain based socket (Internal, linux file based)
- `/http` - Http based socket

## How to Run

`git clone ...`,

- `brew install gcc` or `xcode-select --install` for compiler
- `brew install cmake` to compile w/ cmake
- then,
    - `cd socket-programming`,
    - `./cmake.sh`, and
    - First `cd out/`,
      then Run as `./tcp_client` and `./tcp_server`
  