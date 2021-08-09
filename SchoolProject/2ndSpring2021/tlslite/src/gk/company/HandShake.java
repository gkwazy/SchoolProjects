package gk.company;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DHParameterSpec;
import javax.crypto.spec.DHPublicKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.util.Arrays;

public class HandShake {
    //clients variables

    HandShake(){
    }
    //this is testing the keys and stuff without sockets
    static public void StartHandShake(ClientTls client, ServerTls server) throws Exception {
        byte[] message = client.makeHandShake();

        HandShakeMessage serverCerDH = server.serverCertDHMessage(message);

        HandShakeMessage clientCerDH = client.receiveServerCertDH(serverCerDH);

        server.receiveClientCertDH(clientCerDH);
        server.GenSixKeys();
        client.GenSixKeys();
        byte[] serverMacAllMessage = server.allMessageMac();
        byte[] clientMacAllMessage = client.allMessageMac();
        server.verifyAllMessage(clientMacAllMessage);
        client.verifyAllMessage(serverMacAllMessage);
        String startString = new String("Hello World");
        byte[] byteString = startString.getBytes();
        byteString = server.encryptText(byteString);
        byteString = client.decryptText(byteString);
        String mystring = new String(byteString);
        System.out.println(mystring);

    }
}
