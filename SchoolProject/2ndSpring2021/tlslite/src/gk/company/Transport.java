package gk.company;

import java.io.Serializable;

public class Transport implements Serializable {
    byte[] bytes;
    int length;

  Transport (int length, byte[] bytes){
        this.length = length;
        this.bytes = bytes.clone();
    }
}
