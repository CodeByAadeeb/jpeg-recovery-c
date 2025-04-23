# JPEG Recovery Tool

This is a simple command-line tool written in C that recovers deleted JPEGs from a raw memory card file. It scans the file in 512-byte chunks, looks for the signature bytes that mark the start of a JPEG, and then writes the data into new `.jpg` files.

It starts a new image when it finds a JPEG header and continues writing until the next one appears. The output images are named incrementally as `000.jpg`, `001.jpg`, and so on.

To use it, compile the code using `make recover`, and then run the program like this:

```bash
./recover card.raw
