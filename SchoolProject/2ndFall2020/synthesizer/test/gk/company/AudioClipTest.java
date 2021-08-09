package gk.synthesizer;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AudioClipTest {

    @Test
    void getSample() {
                AudioClip testClip = new AudioClip();
                testClip.setSample(0,32767);
                assertEquals(32767, testClip.getSample(0));
                testClip.setSample(1,-5593);
                assertEquals(-5593, testClip.getSample(1));

                for( int i = -32768; i < 32768; i++){
                    testClip.setSample(i+32768,i);
                }
                for( int i = -32768; i < 32768; i++){
                    assertEquals(i, testClip.getSample(i+32768));
                }
            }
        }

//    @Test
//    void setSample() {
//    }
