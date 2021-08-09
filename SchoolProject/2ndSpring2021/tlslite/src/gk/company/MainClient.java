package gk.company;

import java.io.*;
import java.math.BigInteger;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;


public class MainClient {

	public MainClient() throws IOException {
	}

	public static void main(String[] args) throws Exception {
    	ClientTls client = new ClientTls();

    	String host = "localhost";
    	Socket socket = new Socket(host,8085);
		ObjectOutputStream outStream = new ObjectOutputStream(socket.getOutputStream());
		ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());
		byte[] startHandShake = client.makeHandShake();
		System.out.println("starting connection...");
		outStream.writeObject(startHandShake);
		System.out.println("waiting for reasonse...");
		Certificate cert = (Certificate) inputStream.readObject();
		BigInteger BigInt = (BigInteger) inputStream.readObject();
		byte[] signed = (byte[]) inputStream.readObject();
		HandShakeMessage serverCerDH = new HandShakeMessage(cert,BigInt,signed);
		System.out.println("sending DH key...");
		HandShakeMessage clientCerDH = client.receiveServerCertDH(serverCerDH);
		outStream.writeObject(clientCerDH);
		System.out.println("waiting for AllMac");
		byte[] serverMacAllMessage = (byte[]) inputStream.readObject();
		System.out.println("Making keys");
		client.GenSixKeys();
		byte[] clientMacAllMessage = client.allMessageMac();
		outStream.writeObject(clientMacAllMessage);
		System.out.println("verifing AllMac");
		client.verifyAllMessage(serverMacAllMessage);
		Transport inputFile = (Transport) inputStream.readObject();
		System.out.println("crap");
		byte[] deCryptFile = client.decryptText(inputFile.bytes);
		byte[] deMacFile = client.deMessageMac(deCryptFile);
		String testing = new String(deMacFile);
		System.out.println(testing);
		String thankyou = new String("Thank you very Much");
		byte[] macThank = client.messageMac(thankyou);
		byte[] encryptThanks = client.encryptText(macThank);
		outStream.writeObject(encryptThanks);

	}

}
