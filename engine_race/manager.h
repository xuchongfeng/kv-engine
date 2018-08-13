//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_MANAGER_H
#define KV_ENGINE_MANAGER_H

#include "race.h"
#include "cache.h"
#include "index.h"
#include "wal.h"

namespace polar_race {
class Manager {
public:
	static Manager* getInstance(const std::string& dir) {
		if (nullptr == instance_) {
			instance_ = new Manager(dir);
			instance_.init();
		}
	}
	void init(dir);
	virtual ~Manager();
private:
	Manager(dir):cache(), index(), wal(dir){};
	Manager(const Manager&) = delete;
	Manager operator=(const Manager&) = delete;

private:
	static Manager* instance_;

	Cache<CacheKey, CacheValue> cache;
	Index index;
	Wal wal;
};

} // namespace polar_race

#endif //KV_ENGINE_MANAGER_H
