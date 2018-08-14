//
// Created by FlyFish on 14/08/2018.
//

#include <unistd.h>
#include "wal.h"

namespace polar_race {

	void Wal::init() {
		bool need_recovery = needRecovery();

		wal_pos_file_fd_ = open(wal_pos_file_path_.to_str(), O_APPEND | O_CREATE);
		wal_index_file_fd_ = open(index_file_path_.to_str(), O_APPEND | O_CREATE);
		wal_file_fd_ = open(wal_file_path_.to_str(), O_APPEND | O_CREATE);

		if (need_recovery) {
			recovery();
		}
	}

	void Wal::write(WalLogEntry walLogEntry) {
		// write log file
		// write index
		// write pos file
		std::lock_guard<std::mutex> lock(m_);
		write(wal_file_fd_, (void *)walLogEntry, sizeof(walLogEntry));

		int offset = lseek(wal_file_fd_, 0, SEEK_CUR);
		write(wal_index_file_fd_, (void *)&offset, sizeof(offset));

		write_entry_cnt_++;
		write(wal_pos_file_fd_, (void*)&write_entry_cnt_, sizeof(write_entry_cnt_));
	}

	bool Wal::needRecovery() {
		string wal_pos_file_path = log_path_ + "/" + wal_pos_file_name_;
		if (FileExists(wal_pos_file_path)) return true;
	}

	bool fileExists(const std::string& path) {
		return access(path.c_str(), F_OK) == 0;
	}

	Wal::~Wal() {
		remove(wal_pos_file_path_);
		remove(wal_index_file_path_);
		remove(wal_pos_file_path_);
	}

	void Wal::recovery() {
		// 1 读取位置文件，获取当前位置
		// 2 读取索引文件，获取当前文件偏移位置
		// 3 读取日志文件，将数据写入memtable
	}
}

