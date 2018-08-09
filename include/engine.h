// Copyright [2018] Alibaba Cloud All rights reserved
#ifndef INCLUDE_ENGINE_H_
#define INCLUDE_ENGINE_H_
#include <string>

namespace polar_race {

enum RetCode {
  kSucc = 0,
  kNotFound = 1,
  kCorruption = 2,
  kNotSupported = 3,
  kInvalidArgument = 4,
  kIOError = 5,
  kIncomplete = 6,
  kTimedOut = 7,
  kFull = 8,
  kOutOfMemory = 9,
};

// Pass to Engine::Range for callback
class Visitor {
 public:
  virtual ~Visitor() {}

  virtual void Visit(const std::string &key, const std::string &value) = 0;
};

class Engine {
 public:
  // Open engine
  static RetCode Open(const std::string& name,
      Engine** eptr);

  Engine() { }

  // Close engine
  virtual ~Engine();

  // Write a key-value pair into engine
  virtual RetCode Write(const std::string& key,
      const std::string& value) = 0;

  // Read value of a key
  virtual RetCode Read(const std::string& key,
      std::string* value) = 0;

  // Applies the given Vistor::Visit function to the result
  // of every key-value pair in the key range [first, last),
  // in order
  virtual RetCode Range(const std::string& lower,
      const std::string& upper,
      Visitor &visitor) = 0;
};

}  // namespace polar_race

#endif  // INCLUDE_ENGINE_H_
