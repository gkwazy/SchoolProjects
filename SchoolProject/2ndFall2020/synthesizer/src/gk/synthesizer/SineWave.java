package gk.synthesizer;


import gk.synthesizer.annotations.Slideable;

@gk.synthesizer.annotations.AudioComponent
public class SineWave implements AudioComponent{

    private int frequency;
    @Slideable(minValue = 1, MaxValue = 1000, defaultValue = 440)
    public SineWave(int frequency){
        this.frequency = frequency;
    }
    public int getFrequency(){
        return frequency;
    }
    public void setFrequency(int frequency){
        this.frequency = frequency;
    }

    @Override
    public AudioClip getClip() {
        int maxValue = Short.MAX_VALUE;
        short[] sineArray = new short [88200];
        for(int i = 0; i < sineArray.length; i++){
            sineArray[i] = (short) (maxValue * Math.sin(2*Math.PI*frequency * i / AudioClip.sampleRate));
        }
        return new AudioClip(sineArray) ;
    }

    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent gen) {
    }
}
