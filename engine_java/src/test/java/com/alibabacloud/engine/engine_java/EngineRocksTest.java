package com.alibabacloud.engine.engine_java;

import com.alibabacloud.polar_race.engine.common.AbstractEngine;
import com.alibabacloud.polar_race.engine.common.EngineRace;
import com.alibabacloud.polar_race.engine.common.exceptions.EngineException;

public class EngineRocksTest {

	public static void main(String[] args) {
		AbstractEngine engineRock = new EngineRace();
		try {
			engineRock.open("/Users/zechaoz/test");
			String key = "hahaha";
			engineRock.write(key, "lalala");
//			key = "hahaha11";
			String value = engineRock.read(key);
			System.out.println(value);
			
		} catch (EngineException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally {
			engineRock.close();
		}
	}

}
