package com.example.exterras.chap12;

public class BeepPrintExample3 {
	public static void main(String[] args) {
		int loopCount = 5;
		Thread thread = new BeepThread();
		thread.start();
		
		for (int i = 0; i < loopCount; i++) {
			System.out.println("띵");
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				
			}
		}
	}
}
