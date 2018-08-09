package com.alibabacloud.polar_race.engine.common;

import org.rocksdb.Options;
import org.rocksdb.RocksDB;
import org.rocksdb.RocksDBException;
import org.rocksdb.RocksIterator;

import com.alibabacloud.polar_race.engine.common.AbstractEngine;
import com.alibabacloud.polar_race.engine.common.exceptions.EngineException;
import com.alibabacloud.polar_race.engine.common.exceptions.RetCodeEnum;

public class EngineRace extends AbstractEngine {
	private RocksDB db;

	@Override
	public void open(String path) throws EngineException {
		Options options = new Options();
		options.setCreateIfMissing(true);
		try {
			db = RocksDB.open(options, path);
		} catch (RocksDBException e) {
			throw new EngineException(RetCodeEnum.IO_ERROR, "open rocksdb failed");
		}
		System.out.println("open rocksdb success");
	}
	
	@Override
	public void write(String key, String value) throws EngineException {
		try {
			db.put(key.getBytes(), value.getBytes());
		} catch (RocksDBException e) {
			throw new EngineException(RetCodeEnum.IO_ERROR, "write to rocksdb failed, key=" + key);
		}
	}
	
	@Override
	public String read(String key) throws EngineException {
		String value = null;
		
		try {
			byte[] values = db.get(key.getBytes());
			if(values == null)
				throw new EngineException(RetCodeEnum.NOT_FOUND, "read to rocksdb failed, key=" + key + " is not exist");
			value = new String(values);
				
		} catch (RocksDBException e) {
			throw new EngineException(RetCodeEnum.IO_ERROR, "read to rocksdb failed, key=" + key);
		}
		return value;
	}
	
	@Override
	public void range(String lower, String upper, AbstractVisitor visitor) throws EngineException {
		RocksIterator iterator = db.newIterator();
		if(lower == null || lower.isEmpty())
			iterator.seekToFirst();
		else
			iterator.seek(lower.getBytes());
		
		while (iterator.isValid() 
				&&  upper == null || upper.isEmpty() || (new String(iterator.key()).compareTo(upper) > 0 )) {
			visitor.visit(new String(iterator.key()), new String(iterator.value()));
			iterator.next();
		}
	}
	
	@Override
	public void close() {
		this.db.close();
	}

}
