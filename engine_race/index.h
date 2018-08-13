//
// Created by FlyFish on 13/08/2018.
//

#ifndef KV_ENGINE_INDEX_H
#define KV_ENGINE_INDEX_H

#include "race.h"

namespace polar_race {

/*
 * construct from dbfile index
 * do not update when constructed;
 */
class Index {
public:
	Index(const std::string& db_file_dir): db_file_dir_(db_file_dir){}
	void insert(IndexKey, IndexValue);
	bool get(IndexKey, IndexValue&);

	// TODO: construct from dbfile index
	void constructFromDbFile() {}

private:
	map<IndexKey, IndexValue> db_file_dir_;
	std::string dir_;
	// size_t index_key_cnt_;
private:
	Index(const Index&) = delete;
	Index operator=(const Index&) = delete;
};
}

#endif //KV_ENGINE_INDEX_H
