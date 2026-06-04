# ft_traceroute

_This project has been created as part of the 42 curriculum by tmilin._

## Description

`ft_traceroute` is a simplified re-implementation of the standard `traceroute`.
This project uses RAW sockets to craft `ICMP` (Echo Request) control packets and process network responses.

## Features

- **DNS Resolution**: Supports both IPv4 addresses and Fully Qualified Domain Names (FQDN).
- **Supported Options**:
- 
    `--help`: Displays the help list and usage instructions.
  
- **Statistics Engine**: Tracks __transmitted/received__ packets, calculates packet loss percentage, and computes __RTT__ (min/avg/max).
- **Signal Handling**: Clean exit and final statistics display upon receiving __SIGINT__ (Ctrl+C).

- ## Project Architecture

```bash
.
├── lib
│   └── traceroute.h
├── Makefile
└── src
    ├── ICMP
    │   ├── checksum.c
    │   └── packets.c
    ├── init
    │   └── init.c
    ├── parsing
    │   ├── arguments.c
    │   └── printTexte.c
    ├── resolvAndSocket
    │   └── addrinfo.c
    └── traceroute.c

```

## Usage
```bash
# Simple ping to an IP address
./ft_traceroute 8.8.8.8

# Ping a domain name
./ft_traceroute google.com

# Show help
./ft_traceroute --help
```
