package com.github.exterras.ex02;

public class Calculator {

	public void add(int _f, int _s){
		System.out.println("add");
		System.out.println(_f + " + " + _s + " = " + (_f + _s));
	}
	
	public void sub(int _f, int _s){
		System.out.println("sub");
		System.out.println(_f + " - " + _s + " = " + (_f - _s));
	}
	
	public void mul(int _f, int _s){
		System.out.println("mul");
		System.out.println(_f + " * " + _s + " = " + (_f * _s));
	}
	 
 	public void div(int _f, int _s){
		System.out.println("div");		 		 
		System.out.println(_f + " / " + _s + " = " + ((double)_f / (double)_s));
	}
}
