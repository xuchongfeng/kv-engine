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

		size_t offset = lseek(wal_file_fd_, 0, SEEK_CUR);
		write(wal_index_file_fd_, (void *)&offset, sizeof(offset));

		// write_entry_cnt_++;
		char c = '0';
		write(wal_pos_file_fd_, (void*)&c, 1);
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
		int read_size = 40 * 1024 * 1024;
		char* buffer = new char(read_size);
		while (true) {
			int size = read(wal_pos_file_fd_, buffer, read_size);
			if (size == 0) {
				break;
			}

			if (size == -1) {
				printf("read pos file error\n");
			}
			write_entry_cnt_ += size;
		}


		// 2 读取索引文件，获取当前文件偏移位置
		size_t index_offset = 4 * (write_entry_cnt_ - 1);
		lseek(wal_index_file_fd_, index_offset, SEEK_SET);

		// 3 读取日志文件，将数据写入memtable
		// TODO: continue
		while (true) {
			int size = read(wal_index_file_fd_, buffer, read_size);
			if (size == 0) {
				break;
			}
		}
	}
}

