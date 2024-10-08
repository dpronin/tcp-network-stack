#pragma once
#include "byte_stream.hh"
#include <string>
#include <vector>

using namespace std;
class Reassembler
{
public:
  /*
   * Insert a new substring to be reassembled into a ByteStream.
   *   `first_index`: the index of the first byte of the substring
   *   `data`: the substring itself
   *   `is_last_substring`: this substring represents the end of the stream
   *   `output`: a mutable reference to the Writer
   *
   * The Reassembler's job is to reassemble the indexed substrings (possibly out-of-order
   * and possibly overlapping) back into the original ByteStream. As soon as the Reassembler
   * learns the next byte in the stream, it should write it to the output.
   *
   * If the Reassembler learns about bytes that fit within the stream's available capacity
   * but can't yet be written (because earlier bytes remain unknown), it should store them
   * internally until the gaps are filled in.
   *
   * The Reassembler should discard any bytes that lie beyond the stream's available capacity
   * (i.e., bytes that couldn't be written even if earlier gaps get filled in).
   *
   * The Reassembler should close the stream after writing the last byte.
   */
  void insert( uint64_t first_index, string data, bool is_last_substring, Writer& output );

  // How many bytes are stored in the Reassembler itself?
  uint64_t bytes_pending() const;

private:
  // A vector of characters representing the fragmented data. Stores the data bytes in the order they arrive.
  vector<char> bytes = {};

  // A vector of boolean flags, parallel to the 'bytes' vector, indicating whether a corresponding byte in the
  // 'bytes' vector is filled or not.
  vector<bool> filled = {};

  // A boolean flag that is set to true when the last substring in the data stream is received.
  bool last = false;

  // A counter for the number of bytes pending reassembly. Returns in bytes_pending() method.
  uint64_t pending = 0;
};
