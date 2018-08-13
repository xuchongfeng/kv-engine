//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_MEMTABLE_H
#define KV_ENGINE_MEMTABLE_H

#include <map>

#include "race.h"

namespace polar_race {
class Memtable {
public:
	explicit Memtable(char* file_dir, size_t entry_cnt=memtable_key_cnt): file_dir_(file_dir){
		data_.resize(entry_cnt);
	}

	string getFileName();

	void insert(TableKey);
	void dump();

private:
	map<TableKey, TableValue> data_;
	size_t entry_cnt_;

private:
	char file_dir_[max_path_length];
};

} // namespace polar_race




#endif //KV_ENGINE_MEMTABLE_H
