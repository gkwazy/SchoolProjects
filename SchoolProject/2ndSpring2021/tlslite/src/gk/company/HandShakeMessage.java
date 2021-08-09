package gk.company;

import javax.crypto.spec.DHPublicKeySpec;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.io.Serializable;

public class HandShakeMessage implements Serializable{
    Certificate myCert;
    BigInteger myDHPubKey;
    byte[] signedDH;

    HandShakeMessage(Certificate myCert, BigInteger myDHPubKey, byte[] signedDH){
        this.myCert = myCert;
        this.myDHPubKey = myDHPubKey;
        this.signedDH = signedDH;

    }
    public void verifySigned() throws NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        PublicKey key = myCert.getPublicKey();
        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initVerify(key);
        signature.update(signedDH);
        boolean testing = signature.verify(signedDH);


    }
}
