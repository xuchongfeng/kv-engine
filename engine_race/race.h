//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_RACE_H
#define KV_ENGINE_RACE_H

#include <string>


namespace polar_race {
	// race env setting
	const size_t key_size_bytes = 4;
	const size_t value_size_bytes = 4096;

	const size_t max_path_length = 100;
	const size_t max_file_name_length = 10;

	// global config
	const int memtable_key_cnt = 1000000;
	const int compaction_key_cnt = 1000000;
	const int cache_key_cnt = 1000000;
	const int file_cache_key_cnt = 10000;
	const int max_key_cnt = 32 * 1000000;

	typedef unsigned int size_t;

	// wal
	struct LogEntry {
		char key[key_size_bytes];
		size_t offset;
	};

	typedef LogEntry WalLogEntry;

	// memtable
	typedef LogEntry TableKey;
	typedef char TableValue[value_size_bytes];

	// index
	typedef char IndexKey[key_size_bytes];

	struct IndexEntry {
		char file_name[max_file_name_length];
		size_t offset;
	};
	typedef IndexEntry IndexValue;

	// cache
	typedef char CacheKey[key_size_bytes];
	typedef char CacheValue[value_size_bytes];

	// db
	typedef LogEntry DbLogEntry;


} // namespace polar_race

#endif //KV_ENGINE_RACE_H
