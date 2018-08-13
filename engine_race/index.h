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
	Index(){}
	void insert(IndexKey, IndexValue);
	bool get(IndexKey, IndexValue&);
private:
	map<IndexKey, IndexValue> store_;
	// size_t index_key_cnt_;
private:
	Index(const Index&) = delete;
	Index operator=(const Index&) = delete;
};
}

#endif //KV_ENGINE_INDEX_H
