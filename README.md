# cache-hit-simulator

## About
A simulator that demonstrates cache memory behavior by calculating cache hit and miss rates under different configurations.

## Features
- Reads memory access traces from files using `fopen`, `fgets`, `strtol`, `feof`, and `fclose`.
- Converts data into memory block and set mappings based on cache size, block size, and associativity.
- Simulates cache hits and misses, calculating the miss rate for each configuration.
- Outputs results in a structured table.

## Example Results

| Cache Size (Byte) | Block Size (Byte) | n-way | Miss Rate |
|------------------|-----------------|-------|-----------|
| 128K | 16 | 1 | 0.5276 |
| 128K | 16 | 2 | 0.5236 |
| 128K | 16 | 4 | 0.5228 |
| 128K | 16 | 8 | 0.5226 |
| 512K | 32 | 4 | 0.3802 |
| 512K | 64 | 8 | 0.3080 |
| 1024K | 16 | 2 | 0.5226 |
| 1024K | 64 | 8 | 0.3080 |

*Full table omitted for brevity.*

## Implementation Notes
- Opened and read the trace file using standard C file I/O functions.  
- Parsed addresses into memory blocks and mapped them to cache sets.  
- Simulated cache hits and misses for each memory access.  
- Closed the file after processing.

## References
- [Cache (computing) - Wikipedia](https://en.wikipedia.org/wiki/Cache_(computing))
