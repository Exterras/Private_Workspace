package com.example.exterras.chap12;

public class ThreadA extends Thread{
	public ThreadA(){
		setName("Thread A");
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 2; i++) {
			System.out.println(getName() + "가 출력한 내용");
		}
	}
	
	
}
