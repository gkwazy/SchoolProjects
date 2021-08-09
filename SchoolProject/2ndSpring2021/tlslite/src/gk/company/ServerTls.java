package gk.company;

import javax.crypto.*;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class ServerTls {
    byte[] messageHistory;
    private byte[] clientNonce;
    Certificate myCert;
    private  PublicKey publicKey;
    private PrivateKey privateKey;
    BigInteger myDHPubKey;
    Signature mySignedDHPubKey;
    byte[] byteSignedDHPubKey;
    HandShakeMessage clientHandShake;
    SecretKey sharedDHKey;
    SixKeys sixkeys;

    ServerTls() throws NoSuchAlgorithmException, IOException, InvalidKeySpecException, CertificateException, InvalidKeyException, SignatureException {
        myCert = CertificateHelper.makeCertificate("src/gk/company/CASignedServerCertificate.pem");
        privateKey = CertificateHelper.makePrivateKey("src/gk/company/serverPrivateKey.der");
        publicKey = CertificateHelper.makePubKey(myCert);
        myDHPubKey = DHHelper.makeDHPubKey(privateKey);
        mySignedDHPubKey = DHHelper.makeSignedDH(myDHPubKey,privateKey);
        byteSignedDHPubKey = mySignedDHPubKey.sign();

    }

    public HandShakeMessage serverCertDHMessage(byte[] clientNonce) throws IOException, SignatureException, CertificateEncodingException {
        this.clientNonce = clientNonce;
        this.messageHistory = clientNonce.clone();
        HandShakeMessage message = new HandShakeMessage(myCert,myDHPubKey,byteSignedDHPubKey);
        ByteArrayOutputStream messageOutput = new ByteArrayOutputStream();
        ObjectOutputStream streamOutput = new ObjectOutputStream(messageOutput);
        streamOutput.writeObject(myCert);
        streamOutput.writeObject(myDHPubKey);
        streamOutput.writeObject(mySignedDHPubKey.sign());
        updateMessageHistory(message.myCert.getEncoded());
        updateMessageHistory(message.myDHPubKey.toByteArray());
        return message;
    }

    private void updateMessageHistory(byte[] message) throws IOException {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream( );
        outputStream.write( messageHistory );
        outputStream.write( message );
        messageHistory = outputStream.toByteArray();
    }

    public void receiveClientCertDH(HandShakeMessage message) throws InvalidKeyException, CertificateEncodingException, SignatureException, IOException, NoSuchAlgorithmException {
        this.clientHandShake = message;
        CheckSign(clientHandShake);
        updateMessageHistory(clientHandShake.myCert.getEncoded());
        updateMessageHistory(clientHandShake.myDHPubKey.toByteArray());
        sharedDHKey = DHHelper.buildSharedDH(privateKey,clientHandShake.myDHPubKey);
    }

    public void GenSixKeys() throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException {
        sixkeys = new SixKeys(sharedDHKey.getEncoded(), "mackey".getBytes(), clientNonce);
    }

    private void CheckSign(HandShakeMessage handShake) throws InvalidKeyException, SignatureException, NoSuchAlgorithmException {
        handShake.verifySigned();
    }

    public byte[] allMessageMac() throws InvalidKeyException, NoSuchAlgorithmException, IOException {
       byte[] message = Message.makeMessageMac(messageHistory, sixkeys.serverMAC);
        return message;
    }

    public void verifyAllMessage(byte[] macAllMessage) throws Exception {
       Message.verify(macAllMessage, sixkeys.clientMAC);
    }

    public byte[] messageMac(byte[] file) throws InvalidKeyException, NoSuchAlgorithmException, IOException {
        byte[] message = Message.makeMessageMac(file, sixkeys.serverMAC);
        return message;
    }
    public byte[] deMessageMac(byte[] input) throws Exception {
        Message.verify(input,sixkeys.clientMAC);
        byte[] output = Message.parseOutMessage(input);
        return output;
    }

    public byte[] encryptText(byte[] message) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidKeyException, UnsupportedEncodingException, BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException {
        System.out.println(sixkeys.serverEncrypt.getEncoded().length);
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, sixkeys.serverEncrypt,sixkeys.serverIV);
        byte[] cipherText = cipher.doFinal(message);
        return cipherText;
    }
    public byte[] decryptText(byte[] message) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidKeyException, UnsupportedEncodingException, BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException {

        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, sixkeys.clientEncrypt,sixkeys.clientIV);
        byte[] cipherText = cipher.doFinal(message);
        return cipherText;
    }
}
