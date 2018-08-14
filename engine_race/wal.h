//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_WAL_H
#define KV_ENGINE_WAL_H

#include <mutex>

#include "race.h"

namespace polar_race {

	/*
	 * TODO: 写文件使用异步队列
	 */

class Wal {
public:
	Wal(string log_path): log_path_(log_path), write_entry_cnt_(0){
		wal_pos_file_path_ = log_path_ + "/" + wal_pos_file_name_;
		index_file_path_ = log_path_ + "/" + wal_pos_file_name_;
		wal_file_path_ = log_path_ + "/" + wal_file_name_;
		init();
	};
	void init();
	bool needRecovery();
	void recovery();
	void write(WalLogEntry);

	virtual ~Wal() {}

private:
	bool fileExists(const std::string& path);

private:
	const std::string wal_index_file_name_ = "wal_index.idx";
	const std::string wal_file_name_ = "wal.log";
	const std::string wal_pos_file_name_ = "wal_pos.ps";

	std::string wal_pos_file_path_;
	std::string index_file_path_;
	std::string wal_file_path_;

private:
	string log_path_;
	size_t write_entry_cnt_;

	int wal_index_file_fd_;
	int wal_file_fd_;
	int wal_pos_file_fd_;

	std::mutex m_;
};

} // namespace polar_race

#endif //KV_ENGINE_WAL_H
