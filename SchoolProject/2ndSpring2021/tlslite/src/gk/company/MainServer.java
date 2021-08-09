package gk.company;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class MainServer {

    public static void main(String[] args) throws Exception {
        ServerTls server = new ServerTls();
        System.out.println("im the server");
        ServerSocket serverSocket = new ServerSocket(8085);
        System.out.println("Listening for connection.......");

        Socket clientSocket = serverSocket.accept();
        ObjectInputStream inputStream = new ObjectInputStream(clientSocket.getInputStream());
        ObjectOutputStream outputStream = new ObjectOutputStream((clientSocket.getOutputStream()));
        System.out.println("Connection received");
        byte[] message = (byte[]) inputStream.readObject();
        System.out.println("reading input");
        HandShakeMessage serverCerDH = server.serverCertDHMessage(message);
        System.out.println("sending DH to client...");

        outputStream.writeObject(serverCerDH.myCert);
        outputStream.writeObject(serverCerDH.myDHPubKey);
        outputStream.writeObject(serverCerDH.signedDH);
        //sending first response to client
        System.out.println("waiting for client response...");
        HandShakeMessage clientCerDH = (HandShakeMessage) inputStream.readObject();
        server.receiveClientCertDH(clientCerDH);
        System.out.println("making keys...");
        server.GenSixKeys();
        byte[] serverMacAllMessage = server.allMessageMac();
        outputStream.writeObject(serverMacAllMessage);
        byte[] clientMacAllMessage = (byte[]) inputStream.readObject();
        System.out.println("verifing MAC");
        server.verifyAllMessage(clientMacAllMessage);
        File myFile = new File("src/gk/company/testfile.txt");
        byte[] byteFileArray = new byte[(int)myFile.length()];
        FileInputStream fis = new FileInputStream(myFile);
        BufferedInputStream bis = new BufferedInputStream(fis);
        System.out.println("encrpting file");
        bis.read(byteFileArray,0,byteFileArray.length);
        System.out.println(byteFileArray.length+ " here");
        fis.close();
        bis.close();
        byte[] macArray = server.messageMac(byteFileArray);
        byte[] encryptedArray = server.encryptText(macArray);
        Transport transp = new Transport(encryptedArray.length, encryptedArray);
        System.out.println("Sending");
        outputStream.writeObject(transp);
        outputStream.flush();
        System.out.println("Done.");
        byte[] thankyoubytes = (byte[]) inputStream.readObject();
        byte[] thankyouDe = server.decryptText(thankyoubytes);
        byte[] thankyou = server.deMessageMac(thankyouDe);
        String ty = new String(thankyou);
        System.out.println(ty);

        outputStream.close();


//        while(true){
//
//        }



//        server.serverCertDHMessage(message);
    }
}
