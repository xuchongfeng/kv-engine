//
// Created by FlyFish on 10/08/2018.
//

#ifndef KV_ENGINE_CONFIG_H
#define KV_ENGINE_CONFIG_H

class Config {
public:
	static int memtable_key_cnt = 1000000;
	static int compaction_key_cnt = 1000000;
	static int cache_key_cnt = 1000000;
	static int file_cache_key_cnt = 10000;
};

#endif //KV_ENGINE_CONFIG_H
