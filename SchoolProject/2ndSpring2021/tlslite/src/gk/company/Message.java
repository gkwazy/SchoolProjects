package gk.company;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

public class Message {

//    Message(byte[] message, SecretKeySpec key) throws InvalidKeyException, NoSuchAlgorithmException, IOException {
//        this.message = message;
//        this.key = key;
//        this.messageMac = makeMessageMac(this.message);
//    }


    static public byte[] makeMessageMac(byte[] message, SecretKeySpec key) throws NoSuchAlgorithmException, InvalidKeyException, IOException {
        Mac mac = Mac.getInstance("HmacSHA256");
        String algorithm  = "RawBytes";
        SecretKeySpec tempKey = new SecretKeySpec(key.getEncoded(), algorithm);
        mac.init(tempKey);
        byte[] finalMac = mac.doFinal(message);
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream( );
        outputStream.write( message );
        outputStream.write( finalMac );
        byte[] messageWithMac = outputStream.toByteArray( );
        return messageWithMac;
    }

    static public byte[] parseOutMessage(byte[] rawMessage) throws Exception {
        if (rawMessage.length <= 32){
            throw new Exception("message too short, cant parse");
        }
        byte[] message = Arrays.copyOfRange(rawMessage,0, rawMessage.length-32);
        return message;
    }

    static public byte[] parseOutMAC(byte[] rawMessage) throws Exception {
        if (rawMessage.length <= 32){
            throw new Exception("message too short, cant parse");
        }
        byte[] mac = Arrays.copyOfRange(rawMessage,rawMessage.length-31, rawMessage.length-1);
        return mac;
    }

    static public void verify(byte[] messageMac,SecretKeySpec key) throws Exception {
        byte[] message = parseOutMessage(messageMac);
        byte[] reMacMessage = makeMessageMac(message,key);
        byte[] mac = parseOutMAC(messageMac);
        byte[] reMac = parseOutMAC(reMacMessage);
        boolean match = Arrays.equals(reMac,mac);
        if (!match){
            throw new Exception("message MAC miss match");
        };
    }
}
