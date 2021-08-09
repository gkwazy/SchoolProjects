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

public class ClientTls {
    byte[] messageHistory;
    byte myNonce[] = new byte[32];
    Certificate myCert;
    private  PublicKey publicKey;
    private PrivateKey privateKey;
    BigInteger myDHPubKey;
    SecretKey sharedDHKey;
    Signature mySignedDHPubKey;
    HandShakeMessage serverHandShake;
    SixKeys sixkeys;

    ClientTls() throws NoSuchAlgorithmException, IOException, InvalidKeySpecException, CertificateException, SignatureException, InvalidKeyException {
        myNonce = makeHandShake();
        myCert = CertificateHelper.makeCertificate("src/gk/company/CASignedClientCertificate.pem");
        privateKey = CertificateHelper.makePrivateKey("src/gk/company/clientPrivateKey.der");
        publicKey = CertificateHelper.makePubKey(myCert);
        myDHPubKey = DHHelper.makeDHPubKey(privateKey);
        mySignedDHPubKey = DHHelper.makeSignedDH(myDHPubKey,privateKey);


    }

    public byte[] makeHandShake() {
        SecureRandom random = new SecureRandom();
        random.nextBytes(this.myNonce);
        byte[] myBytes = random.generateSeed(32);
        myNonce = myBytes.clone();
        messageHistory = myBytes.clone();
        return myBytes;
    }

    private void updateMessageHistory(byte[] message) throws IOException {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream( );
        outputStream.write( messageHistory );
        outputStream.write( message );
        messageHistory = outputStream.toByteArray( );
    }

    public HandShakeMessage receiveServerCertDH(HandShakeMessage message) throws CertificateEncodingException, IOException, SignatureException, InvalidKeyException, NoSuchAlgorithmException {
        this.serverHandShake = message;
        CheckSign(serverHandShake);

        updateMessageHistory(serverHandShake.myCert.getEncoded());
        updateMessageHistory(serverHandShake.myDHPubKey.toByteArray());

        HandShakeMessage myHandShake = buildResponseToServerHandShake();

        updateMessageHistory(myHandShake.myCert.getEncoded());
        updateMessageHistory(myHandShake.myDHPubKey.toByteArray());

        sharedDHKey = DHHelper.buildSharedDH(privateKey,serverHandShake.myDHPubKey);
        return myHandShake;

    }
    private HandShakeMessage buildResponseToServerHandShake() throws IOException, SignatureException {
        HandShakeMessage message = new HandShakeMessage(myCert,myDHPubKey,mySignedDHPubKey.sign());
        return message;
    }

    public void GenSixKeys() throws UnsupportedEncodingException, NoSuchAlgorithmException, InvalidKeyException {
        sixkeys = new SixKeys(sharedDHKey.getEncoded(), "mackey".getBytes(),myNonce);
    }

    private void CheckSign(HandShakeMessage handShake) throws InvalidKeyException, SignatureException, NoSuchAlgorithmException {
        handShake.verifySigned();
    }

    public byte[] allMessageMac() throws InvalidKeyException, NoSuchAlgorithmException, IOException {
        byte[] message = Message.makeMessageMac(messageHistory, sixkeys.clientMAC);
        return message;
    }
    public byte[] messageMac(String string) throws InvalidKeyException, NoSuchAlgorithmException, IOException {
        byte[] message = Message.makeMessageMac(string.getBytes(), sixkeys.clientMAC);
        return message;
    }
    public byte[] deMessageMac(byte[] input) throws Exception {
        Message.verify(input,sixkeys.serverMAC);
        byte[] output = Message.parseOutMessage(input);
        return output;
    }

    public void verifyAllMessage(byte[] macAllMessage) throws Exception {
        Message.verify(macAllMessage, sixkeys.serverMAC);
    }


    public byte[] encryptText(byte[] message) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidKeyException, UnsupportedEncodingException, BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, sixkeys.clientEncrypt,sixkeys.clientIV);
        byte[] cipherText = cipher.doFinal(message);
        return cipherText;
    }
    public byte[] decryptText(byte[] message) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidKeyException, UnsupportedEncodingException, BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException {
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE,sixkeys.serverEncrypt,sixkeys.serverIV);
        byte[] cipherText = cipher.doFinal(message);
        return cipherText;
    }
}
