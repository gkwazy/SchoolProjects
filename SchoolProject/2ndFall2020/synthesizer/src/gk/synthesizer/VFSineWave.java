package gk.synthesizer;

public class VFSineWave implements AudioComponent{
    AudioComponent input;



    @Override
    public AudioClip getClip() {
       AudioClip oldClip = input.getClip();
       AudioClip newClip = new AudioClip();
        float phase = 0;
        for (int i = 0; i < 88200; i++) {
            phase += 2 * (Math.PI * oldClip.getSample(i)) / oldClip.sampleRate;
            newClip.setSample(i, (int) (Short.MAX_VALUE * Math.sin(phase)));

        }
        return newClip;
    }
//    @Override
//    public AudioClip getClip() {
//        System.out.println("I am getting into VFSinwaveGetClip!");
//        AudioClip clip = connection.getClip();
//        AudioClip newClip = new AudioClip();
//        float phase = 0;
//        for(int i = 0; i < clip.totalSamples(); i++){
//            phase+= 2 * (Math.PI * clip.getSample(i))/44100;
//            newClip.setSample(i, (int) (Short.MAX_VALUE * Math.sin(phase)));
//        }
//        return newClip;
//    }
    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent input) {
        this.input = input;
    }
}
