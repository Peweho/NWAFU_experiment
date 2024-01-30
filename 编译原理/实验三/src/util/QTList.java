package util;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Iterator;

public class QTList {
	public ArrayList<QTInfo> QTList = new ArrayList<QTInfo>();
	public static boolean flag = true;

	public void addQTInfo(QTInfo info) {
		QTList.add(info);
	}

	public void addQTInfo(int index, QTInfo info) {
		QTList.add(index, info);
	}

	public QTInfo get(int index) {
		return (QTInfo) QTList.get(index);
	}

	public QTInfo remove(int index) {
		return QTList.remove(index - 1);
	}

	public void clear() {
		QTList.clear();
		QTInfo.size = 0;
	}

	public void printQTTable(FileOutputStream out) {
		// System.out.println(toString());
		Iterator<QTInfo> itr = QTList.iterator();
		try {
			while (itr.hasNext()) {
				QTInfo tmp = (QTInfo) itr.next();
//				System.out.println(tmp.toString());
				out.write(tmp.toString().getBytes());
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
