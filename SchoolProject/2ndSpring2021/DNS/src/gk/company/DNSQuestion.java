package gk.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;

public class DNSQuestion {
    ByteArrayInputStream input;
    DNSMessage message;
    private byte[] tempName;
    byte[] name;
    int namelength = 0;
    int totalNameLength=0;
    byte[] type;
    byte[] dnsclass;
    String stringName;

    public DNSQuestion(ByteArrayInputStream input, DNSMessage message) throws IOException {
        this.input = input;
        this.message = message;
        this.tempName = new byte[250];
        parseQuestion();
    }

    void parseQuestion() throws IOException {
        boolean isQuestion = true;
        byte[] nextSegment = input.readNBytes(1);
        byte compressed = (byte) (nextSegment[0] & 0xC0);
        if(compressed == 0xC0){
            //change this to a DNS message to get the name
            tempName[0] = nextSegment[0];
            isQuestion = false;
        }
        int charaterAmount = nextSegment[0];
        totalNameLength = totalNameLength + charaterAmount+1;
        while(isQuestion && namelength < 250){
//            System.out.format("%02X \n", name[0]);
                if (charaterAmount == 0x00){
                    isQuestion = false;
                }else{
                    tempName[namelength] = (byte)charaterAmount;
                    namelength = namelength +1;
                    for(int i = 0; i < charaterAmount; i++){
                        tempName[namelength] = input.readNBytes(1)[0];
                        namelength = namelength +1;
                }
                    charaterAmount = input.readNBytes(1)[0];
                    totalNameLength = totalNameLength + charaterAmount +1 ;
            }
        }
        name = new byte[totalNameLength];
        System.arraycopy(tempName, 0, name, 0, totalNameLength);
        stringName = message.readDomainname(12);
        message.nameCompression.put(stringName, 12);
        type = input.readNBytes(2);
        dnsclass = input.readNBytes(2);

    }

    void writeBytes(ByteArrayOutputStream output) throws IOException {
        output.write(name);
        output.write(type);
        output.write(dnsclass);
    }

    @Override
    public String toString() {
        return "DNSQuestion{" +
                "input=" + input +
                ", message=" + message +
                ", tempName=" + Arrays.toString(tempName) +
                ", name=" + Arrays.toString(name) +
                ", namelength=" + namelength +
                ", totalNameLength=" + totalNameLength +
                ", type=" + Arrays.toString(type) +
                ", dnsclass=" + Arrays.toString(dnsclass) +
                '}';
    }
}
