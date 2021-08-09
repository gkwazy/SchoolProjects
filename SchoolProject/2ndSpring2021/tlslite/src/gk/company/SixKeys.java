package gk.company;

import javax.crypto.Mac;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.util.Arrays;

public class SixKeys {
    private byte[] sharedDHKey;
    private byte[] sharedString;
    byte[] prk;
    SecretKeySpec serverEncrypt;
    SecretKeySpec clientEncrypt;
    SecretKeySpec serverMAC;
    SecretKeySpec clientMAC;
    IvParameterSpec serverIV;
    IvParameterSpec clientIV;
    private Mac myMac;




    SixKeys(byte[] sharedDHKey, byte[] startingString, byte[] clientNonce) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        this.sharedDHKey = sharedDHKey;
        this.sharedString = startingString;

        prk = startHKDF(sharedDHKey,startingString);

        byte[] serverEncryptBytes = hkdfExpand(prk, "server encrypt");
        this.serverEncrypt = new SecretKeySpec(serverEncryptBytes,"AES");

        byte[] clientEncryptBytes = hkdfExpand(serverEncrypt.getEncoded(), "client encrypt");
        this.clientEncrypt = new SecretKeySpec(clientEncryptBytes,"AES");
        System.out.println(clientEncrypt.getEncoded().length);

        byte[] serverMACBytes = hkdfExpand(clientEncrypt.getEncoded(), "server MAC");
        this.serverMAC = new SecretKeySpec(serverMACBytes,"server MAC");

        byte[] clientMACBytes = hkdfExpand(serverMAC.getEncoded(), "client MAC");
        this.clientMAC = new SecretKeySpec(clientMACBytes,"client MAC");

        byte[] serverIVBytes = hkdfExpand(clientMAC.getEncoded(), "server IV");
        this.serverIV = new IvParameterSpec(serverIVBytes);

        byte[] clientIVBytes = hkdfExpand(serverIV.getIV(), "client IV");
        this.clientIV = new IvParameterSpec(clientIVBytes);
        System.out.println(clientIV.getIV().length);
    }

    private Mac MakeMac(byte[] bytes, String algor) throws NoSuchAlgorithmException, InvalidKeyException {
        Mac mac = Mac.getInstance("HmacSHA256");
        byte[] keyBytes   = bytes;
        String algorithm  = algor;
        SecretKeySpec key = new SecretKeySpec(keyBytes, algorithm);
        mac.init(key);
        return mac;
    }

    private byte[] startHKDF(byte[] input, byte[] tag) throws NoSuchAlgorithmException, InvalidKeyException {
        byte[] tagArray =  tag.clone();
        myMac = MakeMac(sharedDHKey,"RawBytes");
        myMac.update(input);
        myMac.update(tagArray);
        byte[] macBytes = myMac.doFinal();
        byte[] macBytesShorter = Arrays.copyOfRange(macBytes,0,16);
        return macBytesShorter;
    }

    private byte[] hkdfExpand(byte[] input, String tag) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException { //tag is a string, but probably convenient to take its contents as byte[]
        byte[] tagArray =  tag.getBytes();
        tagArray = Arrays.copyOf(tagArray, tagArray.length+1);
        tagArray[tagArray.length-1] = (byte)1;
        Mac mac = MakeMac(input, tag);
        mac.update(input);
        mac.update(tagArray);
        byte[] macBytes = mac.doFinal();
        byte[] macBytesShorter = Arrays.copyOfRange(macBytes,0,16);
        return macBytesShorter;
    }
}
