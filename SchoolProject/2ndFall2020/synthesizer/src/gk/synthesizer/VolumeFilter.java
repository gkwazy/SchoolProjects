package gk.synthesizer;

public class VolumeFilter implements AudioComponent {

    public double scale;
    public AudioComponent input;

    public VolumeFilter(double scale){
       scale = Math.abs(scale);
       this.scale = scale;
    }

    public static int clamp (int volumeLevel, short min, short max){
            return Math.max(min, Math.min(volumeLevel, max));
    }


    @Override
    public AudioClip getClip() {
        AudioClip oldClip = input.getClip();
        AudioClip newClip = new AudioClip();
        for(int i = 0; i < 88200; i++){
            double volume = oldClip.getSample(i)*scale;
            newClip.setSample(i, clamp((int)(volume), Short.MIN_VALUE, Short.MAX_VALUE));
        }
        return newClip;
    }

    public double getScale(){
        return scale;
    }

    public void setScale(double scale){
        scale = Math.abs(scale);
        this.scale = scale;
    }

    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent input) {
    this.input = input;
    }
}
