// Copyright [2018] Alibaba Cloud All rights reserved
#ifndef ENGINE_RACE_ENGINE_RACE_H_
#define ENGINE_RACE_ENGINE_RACE_H_
#include <string>
#include "include/engine.h"

namespace polar_race {

class EngineRace : public Engine  {
 public:
  static RetCode Open(const std::string& name, Engine** eptr);

  explicit EngineRace(const std::string& dir) {
  }

  ~EngineRace();

  RetCode Write(const std::string& key,
      const std::string& value) override;

  RetCode Read(const std::string& key,
      std::string* value) override;

  RetCode Range(const std::string& lower,
      const std::string& upper,
      Visitor &visitor) override;

 private: 

};

}  // namespace polar_race

#endif  // ENGINE_RACE_ENGINE_RACE_H_
