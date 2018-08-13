//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_WAL_H
#define KV_ENGINE_WAL_H

#include "race.h"

namespace polar_race {

class Wal {
public:
	Wal(string log_path);
	void write(WalLogEntry);

private:
	const char *wal_index_file_name_ = "wal_index.idx";
	const char *wal_file_name_ = "wal.log";
	const char *wal_pos_file_name_ = "wal_pos.ps";

private:
	string log_path_;
	size_t write_entry_cnt_;
};

} // namespace polar_race

#endif //KV_ENGINE_WAL_H
