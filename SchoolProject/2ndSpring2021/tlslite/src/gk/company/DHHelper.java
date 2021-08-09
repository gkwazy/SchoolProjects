package gk.company;

import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.spec.InvalidKeySpecException;

public class DHHelper {

    static public BigInteger makeDHPubKey(PrivateKey privateKey) {
        BigInteger g = new BigInteger("2");
        BigInteger N = new BigInteger("32317006071311007300338913926423828248817941241140239112842009751400741706634354222619689417363569347117901737909704191754605873209195028853758986185622153212175412514901774520270235796078236248884246189477587641105928646099411723245426622522193230540919037680524235519125679715870117001058055877651038861847280257976054903569732561526167081339361799541336476559160368317896729073178384589680639671900977202194168647225871031411336429319536193471636533209717077448227988588565369208645296636077250268955505928362751121174096972998068410554359584866583291642136218231078990999448652468262416972035911852507045361090559");
        BigInteger key = new BigInteger(privateKey.getEncoded());
        BigInteger myDHPubKey = g.modPow(key, N);
        return myDHPubKey;
    }

    static public Signature makeSignedDH(BigInteger myDHPubKey, PrivateKey privateKey) throws NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initSign(privateKey);
        signature.update(myDHPubKey.toByteArray());
        signature.sign();
        return signature;
    }

    static public SecretKey buildSharedDH(PrivateKey myKey, BigInteger otherDHKey) throws NoSuchAlgorithmException {
        BigInteger N = new BigInteger("32317006071311007300338913926423828248817941241140239112842009751400741706634354222619689417363569347117901737909704191754605873209195028853758986185622153212175412514901774520270235796078236248884246189477587641105928646099411723245426622522193230540919037680524235519125679715870117001058055877651038861847280257976054903569732561526167081339361799541336476559160368317896729073178384589680639671900977202194168647225871031411336429319536193471636533209717077448227988588565369208645296636077250268955505928362751121174096972998068410554359584866583291642136218231078990999448652468262416972035911852507045361090559");
        BigInteger priKey = new BigInteger(myKey.getEncoded());
        BigInteger sharedDH = otherDHKey.modPow(priKey,N);
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
        SecureRandom secureRandom = new SecureRandom();
        int keyBitSize = 256;
        keyGenerator.init(keyBitSize, secureRandom);
        SecretKey DHKey = new SecretKeySpec(sharedDH.toByteArray(), 0, sharedDH.toByteArray().length, "AES");
        return DHKey;
    }
}
