package com.example.exterras.chap12;

import java.awt.Toolkit;

public class BeepPrintExample1 {
	public static void main(String[] args) {
		
		int loopCount = 5;
		
		Toolkit toolkit = Toolkit.getDefaultToolkit(); // Toolkit 객체 얻기. 이 함수는 전역이다.
		for (int i = 0; i < loopCount; i++) {
			toolkit.beep();
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				
			}
		}
		// 먼저 앞의 for문이 실행된 후에 
		
		
		for (int i = 0; i < loopCount; i++) {
			System.out.println("띵");
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				
			}
		}
		// 뒤의 for문이 실행된다. 즉 메인 스레드는 동시에 두 가지 작업을 할 수 없다.
		
	}
}
