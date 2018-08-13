//
// Created by FlyFish on 13/08/2018.
//

#include "index.h"

void Index::insert(IndexKey key, IndexValue value) {
	store_.[key] = value;
}

bool Index::get(IndexKey key, IndexValue& value) {
	if (store_.contains(key)) {
		value = store_[key];
		return true;
	}

	return false;
}

