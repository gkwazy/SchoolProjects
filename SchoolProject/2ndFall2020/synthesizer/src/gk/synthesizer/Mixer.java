package gk.synthesizer;

import java.util.ArrayList;

public class Mixer implements AudioComponent{

    public ArrayList<AudioComponent> inputs = new ArrayList<>();

    @Override
    public AudioClip getClip() {
        AudioClip clip = new AudioClip();
        for (int i = 0; i < inputs.size(); i++){
            AudioClip together = inputs.get(i).getClip();
            for (int j = 0; j<88200; j++){
                short sample = (short)together.getSample(j);
                clip.setSample(j, VolumeFilter.clamp(sample + clip.getSample(j),
                        Short.MIN_VALUE, Short.MAX_VALUE));
            }
        }
        return clip;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        inputs.add(input);
    }
}
