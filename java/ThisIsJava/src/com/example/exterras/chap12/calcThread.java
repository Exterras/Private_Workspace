package com.example.exterras.chap12;

public class calcThread extends Thread{
	public calcThread(String name){
		setName(name);
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 2000000000; i++) {
			
		}
		System.out.println(getName());
	}
}
