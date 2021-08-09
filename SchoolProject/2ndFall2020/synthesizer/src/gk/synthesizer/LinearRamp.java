package gk.synthesizer;

public class LinearRamp implements AudioComponent {
    public AudioComponent input;
    float start;
    float stop;

   public LinearRamp(float start, float stop){
    this.start = start;
    this.stop = stop;
   }

    @Override
    public AudioClip getClip() {
        AudioClip newClip = new AudioClip();
        for(int i = 0; i < 88200; i++){
            newClip.setSample(i , (int) ((start*(88200 - i) + stop*i)/88200));
        }

        return newClip;
    }

    @Override
    public boolean hasInput() {
        return false;
    }
    @Override
    public void connectInput(AudioComponent input) {
    }
}
