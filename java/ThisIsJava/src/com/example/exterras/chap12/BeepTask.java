package com.example.exterras.chap12;

import java.awt.Toolkit;

public class BeepTask implements Runnable{

	@Override
	public void run() {
		
		int loopCount = 5;
		Toolkit toolkit = Toolkit.getDefaultToolkit(); // Toolkit 객체 얻기. 이 함수는 전역이다.
		
		for (int i = 0; i < loopCount; i++) {
			toolkit.beep();
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				
			}
		}
	}
	
}
