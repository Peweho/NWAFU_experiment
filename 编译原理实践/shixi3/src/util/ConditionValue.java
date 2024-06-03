package util;

import java.util.ArrayList;
import java.util.Iterator;

public class ConditionValue {
	public ArrayList<QTInfo> trueChain = new ArrayList<QTInfo>();
	public ArrayList<QTInfo> falseChain = new ArrayList<QTInfo>();
	
	public void mergeTrue(QTInfo qtTrue){
		trueChain.add(qtTrue);
	}
	public void mergeFalse(QTInfo qtFalse){
		falseChain.add(qtFalse);
	}

	public int getMergeTrueLength(){ return trueChain.size();}

	public int getMergeFalseLength(){ return falseChain.size();}


	public void RemoveMergeFalse(){falseChain.remove(getMergeFalseLength()-1);}

	public void copyFalse(ConditionValue cv){
		Iterator<QTInfo> itr = falseChain.iterator();
		while(itr.hasNext()){
			cv.mergeFalse(itr.next());
		}
	}

	public void copyTrue(ConditionValue cv){
		Iterator<QTInfo> itr = trueChain.iterator();
		while(itr.hasNext()){
			cv.mergeTrue(itr.next());
		}
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

	public void mergeTrue(ConditionValue p2){
		int pos = p2.trueChain.size()-1;
		if(p2.trueChain.get(pos).getResult().equals("0")){
			QTInfo qt = p2.trueChain.get(pos);
			while(qt.getResult().equals("0") && pos >= 0){
				pos -= 1;
				qt = p2.trueChain.get(pos);
			}
			p2.trueChain.get(pos).setResult(trueChain.get(trueChain.size()-1).getResult());
		} // else
	}
}
