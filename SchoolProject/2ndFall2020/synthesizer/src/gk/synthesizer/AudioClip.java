package gk.synthesizer;

import java.util.Arrays;

public class AudioClip {
    static final float duration = (float) 2.0;
    static final float sampleRate = 44100;
    byte[] myBytes= new byte[176400];



    public AudioClip() {
        }

    public AudioClip(short[] sineArray) {
        for(int i = 0; i < sineArray.length; i++){
            setSample(i,sineArray[i]);
        }
    }


    public int getSample(int index) {
        index = index*2;
        int second = myBytes[index];
        second = second << 24;
        second = second >>> 24;
        int first = myBytes[index+1];
        first = first << 8;
        int wanted = first+second;
        return wanted;
    }

   public void setSample(int index, int value){
        index = index*2;
        int second = (value & 0xFF);
        int first = (byte) ((value >> 8));
        myBytes[index+1] = (byte)first;
        myBytes[index] = (byte)second;
   }

   public byte[] getData(){
        byte[] byteCopy = Arrays.copyOf(myBytes,176400);
        return byteCopy;
   }


}
