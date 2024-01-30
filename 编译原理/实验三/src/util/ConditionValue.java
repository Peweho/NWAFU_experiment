package util;

import java.util.ArrayList;
import java.util.Iterator;

public class ConditionValue {
	private ArrayList<QTInfo> trueChain = new ArrayList<QTInfo>();
	private ArrayList<QTInfo> falseChain = new ArrayList<QTInfo>();
	
	public void mergeTrue(QTInfo qtTrue){
		trueChain.add(qtTrue);
	}
	public void mergeFalse(QTInfo qtFalse){
		falseChain.add(qtFalse);
	}
	
	public void backpatchTrueChain(int result){
		Iterator<QTInfo> itr = trueChain.iterator();
		while(itr.hasNext()){
			itr.next().setResult(result);
		}
	}
	public void backpatchFalseChain(int result){
		Iterator<QTInfo> itr = falseChain.iterator();
		while(itr.hasNext()){
			itr.next().setResult(result);
		}
	}
}
