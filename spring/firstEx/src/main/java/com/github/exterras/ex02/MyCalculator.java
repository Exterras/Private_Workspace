package com.github.exterras.ex02;

public class MyCalculator {
	public Calculator calculator; 
	private int firstNum;
	private int secondNum;
	
	public int getFirstNum() {
		return firstNum;
	}
	public void setFirstNum(int firstNum) {
		this.firstNum = firstNum;
	}
	
	public int getSecondNum() {
		return secondNum;
	}
	public void setSecondNum(int secondNum) {
		this.secondNum = secondNum;
	}
	
	public void add(){
		calculator.add(firstNum, secondNum);
	}
	
	public void sub(){
		calculator.sub(firstNum, secondNum);
	}
	
	public void mul(){
		calculator.mul(firstNum, secondNum);
	}
	 
 	public void div(){
 		calculator.div(firstNum, secondNum);
	}
}