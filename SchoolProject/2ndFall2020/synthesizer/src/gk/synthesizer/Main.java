package gk.synthesizer;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;

public class Main{

    public static void main(String[] args) throws LineUnavailableException {

        Clip c = AudioSystem.getClip(); //terrible name, different from our AudioClip class

//This is the format that we're following, 44.1KHz mono audio, 16 bits per sample
        AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);

        AudioComponent gen = new SineWave(340);
        AudioComponent alpha = new SineWave(120);
        AudioComponent volumeLow = new VolumeFilter(1);
        AudioComponent volumeHigh = new VolumeFilter(1);
        AudioComponent linearRamp = new LinearRamp(50,10000);
        AudioComponent vfSine = new VFSineWave();

        linearRamp.connectInput(gen);
        vfSine.connectInput(linearRamp);


        Mixer mix = new Mixer();
        volumeLow.connectInput(gen);
        volumeHigh.connectInput(alpha);

//        mix.connectInput(volumeLow);
//        mix.connectInput(volumeHigh);
        mix.connectInput(vfSine);


        AudioClip clip = mix.getClip();


        c.open(format16, clip.getData(), 0, clip.getData().length); //reads data from my byte array to play it

        System.out.println("about to play");
        c.start(); //plays it
        c.loop(2); //plays it 2 more times if desired, so 3 seconds total

//makes sure the program doesn't quit before the sound plays
        while(c.getFramePosition() < AudioClip.sampleRate || c.isActive() || c.isRunning()){}

        System.out.println("done");
        c.close();
    }


}
