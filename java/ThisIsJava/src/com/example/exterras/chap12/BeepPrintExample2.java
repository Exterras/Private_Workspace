package com.example.exterras.chap12;

import java.awt.Toolkit;

public class BeepPrintExample2 {
	public static void main(String[] args) {
		int loopCount = 5;
		
		Runnable beeptask = new BeepTask();
		Thread thread = new Thread(beeptask);
		thread.start();
		// 9 라인에서 BeepTask 객체 생성
		// 10라인에서 beeptask 객체를 매개값으로 하여 작업 스레드를 생성한다.
		// 11라인에서 작업 스레드의 start()를 호출하여 작업 스레드에 의해 
		// beeptask 객체의 run()가 실행되어 비프음이 발생한다.
		
		/* Thread thread2 = new Thread(new Runnable() {
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
		}); */ // 두번째 방법
		
		/* Thread thread3 = new Thread(() -> {
			int loopCount = 5;
			Toolkit toolkit = Toolkit.getDefaultToolkit(); // Toolkit 객체 얻기. 이 함수는 전역이다.
			
			for (int i = 0; i < loopCount; i++) {
				toolkit.beep();
				try {
					Thread.sleep(1000);
				} catch (Exception e) {
					
				}
			}
		}); */ // 세번째 방법, 람다식
		
		for (int i = 0; i < loopCount; i++) {
			System.out.println("띵");
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				
			}
		}
	}
}
