# C RPC Server

This repository contains a Remote Procedure Call (RPC) server written in C. It can register, locate, and call functions remotely using a simple client-server model.

## Table of Contents

1. [Features](#Features)
2. [Getting Started](#Getting-Started)
   - [Prerequisites](#Prerequisites)
   - [Installation](#Installation)
3. [Usage](#Usage)

## Features

- **Remote Procedure Call**: Allows remote function registration and invocation.
- **IPv6 support**: The server uses IPv6 for network communication.
- **Custom Data Structure**: Implements a custom data structure for handling requests.

## Getting Started

### Prerequisites

- GCC, a compiler for C and C++, is needed to compile and run this program.

### Installation

1. Clone this repository using git:

```
git clone https://github.com/shaneSleeman/rpc-server.git
```

2. Change to the project's directory:

```
cd rpc-server
```

3. Compile the program:

```
gcc -o server server.c
gcc -o client client.c
```

## Usage

1. Start the server:

```
./server
```

2. In another terminal, use the client to send requests to the server:

```
./client
```

The server and client communicate using a custom protocol for function registration, location, and invocation. The data structures used for this communication are defined in `rpc.h`.
