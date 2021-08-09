package gk.company;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;

public class CertificateHelper {

    static public PrivateKey makePrivateKey(String privateKeyFileName) throws NoSuchAlgorithmException, InvalidKeySpecException, IOException {
        Path path = Paths.get(privateKeyFileName);
        byte[] privKeyByteArray = Files.readAllBytes(path);
        PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(privKeyByteArray);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PrivateKey myPrivKey = keyFactory.generatePrivate(keySpec);
        myPrivKey.hashCode();
        return myPrivKey;
    }

    static public PublicKey makePubKey(Certificate cert){
        return cert.getPublicKey();
    }

    static public Certificate makeCertificate(String file) throws CertificateException, FileNotFoundException {
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream certificateInputStream = new FileInputStream(file);
        Certificate certificate = certificateFactory.generateCertificate(certificateInputStream);
        return certificate;
    }

    static public BigInteger makeDHPubKey(PublicKey certificatePublicKey, BigInteger g, BigInteger N) throws NoSuchAlgorithmException, InvalidAlgorithmParameterException, InvalidKeySpecException {
        BigInteger myDHPubKey = g.modPow(BigInteger.valueOf(certificatePublicKey.hashCode()),N);
        return myDHPubKey;
    }
}
