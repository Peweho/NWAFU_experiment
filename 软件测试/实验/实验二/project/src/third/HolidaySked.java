package third;

import java.util.BitSet;

public class HolidaySked {
    BitSet sked;

    public static void main(String[] arguments){
        HolidaySked cal=new HolidaySked();
        if(arguments.length>0){
            try{
                int whichDay=Integer.parseInt(arguments[0]);
                if(cal.isHoliday(whichDay)){
                    System.out.println(whichDay+"is a holiday.");}
                else
                {System.out.println(whichDay+"is not a holiday.");}

            }catch(NumberFormatException nfe){
                System.out.println("Error: "+nfe.getMessage());}
        }
}
    public void addHoliday(int daytoAdd) {
        sked.set(daytoAdd);
    }
    public boolean isHoliday(int dayToCheck){
        boolean result=sked.get(dayToCheck);
        return result;
    }
    public HolidaySked(){
        sked=new BitSet(365);
        int[] holiday={1,20,43,48,53,115,131,146,165,166,185,244,286,315,327,359};
        //集合中假日是随机设定的，可根据今年的情况自行调整
        for(int i=0;i<holiday.length;i++){
            addHoliday(holiday[i]);
        }
    }
}
