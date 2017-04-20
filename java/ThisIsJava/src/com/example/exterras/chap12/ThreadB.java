package com.example.exterras.chap12;

public class ThreadB extends Thread{
	public ThreadB(){
		setName("Thread B");
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 2; i++) {
			System.out.println(getName() + "가 출력한 내용");
		}
	}

}
