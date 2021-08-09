package gk.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.HashMap;

public class DNSServer {
    DatagramSocket socket;
//    DatagramSocket googleSocket;
    HashMap<String,InetAddress> addressesKnown;
    DNSCache dnsCache;

    public DNSServer() throws SocketException {
        dnsCache = new DNSCache();
        socket = new DatagramSocket(8053);
    }

    private void sendPackets (DatagramSocket socket, byte[] bytes, int port,InetAddress address) throws IOException {
        DatagramPacket sendPacket = new DatagramPacket(bytes, bytes.length,address,port);
        socket.send(sendPacket);
    }
    public void open() throws IOException {
        System.out.println("Running and listen for requests");
        HashMap<String,InetAddress> addressesKnown = new HashMap<>();
        InetAddress google = InetAddress.getByName("8.8.8.8");
        addressesKnown.put("google.com", google);

        byte[] buffer = new byte[250];
        while (true) {
            DatagramPacket inputPacket = new DatagramPacket(buffer, buffer.length);
            System.out.println("waiting");
            socket.receive(inputPacket);
            System.out.println("package incoming");
            byte[] smallerBuffer = new byte[inputPacket.getLength()];
            System.arraycopy(inputPacket.getData(),0,smallerBuffer,0,inputPacket.getLength());
            ByteArrayInputStream inputStream = new ByteArrayInputStream(smallerBuffer);
            DNSHeader inputHeader = new DNSHeader(inputStream);
            DNSMessage inputMessage = new DNSMessage(smallerBuffer, inputHeader);
            String wantedDomain = inputMessage.readDomainname(12);

            if (addressesKnown.containsKey(wantedDomain)){
                InetAddress wantedAddress = addressesKnown.get(wantedDomain);
                System.out.println(wantedDomain + " in memory - sending to client");
                byte[] requestBytes = inputMessage.inMemoryResponse(wantedAddress);
                sendPackets(socket,requestBytes,inputPacket.getPort(), inputPacket.getAddress());
            }else{
                System.out.println(wantedDomain + " Asking google - then forwarding response");
                byte[] googleBytes = inputMessage.askGoogle();

                DatagramSocket googleSocket = new DatagramSocket();
                InetAddress googleAddress = InetAddress.getByName("8.8.8.8");
                DatagramPacket googlePacket = new DatagramPacket(googleBytes, googleBytes.length,googleAddress,53);
                googleSocket.send(googlePacket);

                byte[] googleBuffer = new byte[250];
                DatagramPacket responsePacket = new DatagramPacket(googleBuffer, googleBuffer.length);
                System.out.println("request sent");
                googleSocket.receive(responsePacket);

                System.out.println("Google response received, forwarding");
                byte[] smallerResponseBuffer = new byte[responsePacket.getLength()];
                System.arraycopy(responsePacket.getData(),0,smallerResponseBuffer,0,responsePacket.getLength());

                ByteArrayInputStream responseStream = new ByteArrayInputStream(smallerResponseBuffer);
                DNSHeader responseHeader = new DNSHeader(responseStream);
                DNSMessage responseMessage = new DNSMessage(smallerResponseBuffer, responseHeader);

                byte[] responseBytes = responseMessage.googleResponse(dnsCache, inputMessage);
                responseMessage.storeAddress(addressesKnown);
                System.out.println("send");
                sendPackets(socket,responseBytes,inputPacket.getPort(), inputPacket.getAddress());
            }
        }

//        byte [] arrayQueryAndAnswer = new byte[]{
//                //      |  header | |  Flags | QDCount  |
//                (byte) 0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //header
//                , 0x03, 0x77, 0x77, 0x77, 0x0c , 0x6e, 0x6f, 0x72 , 0x74, 0x68, 0x65, 0x61, 0x73, 0x74, 0x65, 0x72, 0x6e,
//                0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01, (byte) 0xdb, 0x42, (byte) 0x81, (byte) 0x80, 0x00,
//                0x01, 0x00, 0x01,0x00, 0x00, 0x00, 0x00, 0x03, 0x77, 0x77, 0x77,
//                0x0c, (byte) 0x6e, 0x6f, 0x72,0x74, 0x68, 0x65, 0x61, 0x73, 0x74, 0x65, 0x72 , 0x6e, 0x03, 0x65, 0x64,
//                0x75, 0x00,0x00, 0x01, 0x00, 0x01, (byte) 0xc0, 0x0c, 0x00, 0x01,  0x00, 0x01, 0x00, 0x00, 0x02, 0x58,
//                0x00, 0x04, (byte) 0x9b, 0x21, 0x11, 0x44,
//        };
//       byte[] responseArray = new byte[]{
//                /*header*/ (byte) 0xdb, 0x42, (byte) 0x81, (byte) 0x80, 0x00, 0x01, 0x00, 0x01,0x00, 0x00, 0x00, 0x00, /*3*/ 0x03,/*www*/ 0x77, 0x77, 0x77,
//                /*12*/ 0x0c, /*northeastern.com*/(byte) 0x6e, 0x6f, 0x72,0x74, 0x68, 0x65, 0x61, 0x73, 0x74, 0x65, 0x72 , 0x6e, /*3*/0x03,/*edu*/ 0x65, 0x64,
//                0x75,/*end*/ 0x00,0x00, 0x01, 0x00, 0x01, (byte)/*Compression*/ 0xc0, 0x0c, 0x00, 0x01,  0x00, 0x01, 0x00, 0x00, 0x02, 0x58,
//                0x00, 0x04, (byte) 0x9b, 0x21, 0x11, 0x44 };
//
//       byte[] googleQuest = new byte[] {
//               (byte) 0xfa, 0x75, 0x01, 0x20, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x67, 0x6f, 0x6f, 0x67, 0x6c,
//               0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x29, 0x10, 0x00, 0x00, 0x00,
//               0x00, 0x00, 0x00, 0x00};
//        for (byte c : googleQuest) {
//            System.out.format("%02X ", c);
//        }
//        //making testing send message;
//        HashMap<String, Integer> passAddresses = new HashMap<>();
//        ByteArrayInputStream input = new ByteArrayInputStream(googleQuest);
//        ByteArrayOutputStream outputHeaderBytes = new ByteArrayOutputStream();
//        DNSHeader inputHeader = new DNSHeader(input);
//        DNSMessage inputMessage = new DNSMessage(arrayQueryAndAnswer,inputHeader);
//        DNSQuestion inputQuestion = new DNSQuestion(input,inputMessage);
//        DNSRecord inputRecord = new DNSRecord(input, inputMessage);
//        inputHeader.writeBytes(outputHeaderBytes);
//        inputQuestion.writeBytes(outputHeaderBytes,passAddresses);
//        inputRecord.writeBytes(outputHeaderBytes,passAddresses);
//        byte[] requestBytes =  outputHeaderBytes.toByteArray();
//        System.out.println();
//        for (byte c : requestBytes) {
//            System.out.format("%02X ", c);
//        }
//
//
///// making testing response from google.
//        byte[] buffer = new byte[250];
//        InetAddress address = InetAddress.getByName("8.8.8.8");
//        DatagramPacket packet = new DatagramPacket(requestBytes, requestBytes.length,address,53);
//        socket.send(packet);
////        while (true) {
//            DatagramPacket responsePacket = new DatagramPacket(buffer, buffer.length);
//            System.out.println("waiting");
//            socket.receive(responsePacket);
//            System.out.println(responsePacket.getLength());
//            byte[] smallerBuffer = new byte[responsePacket.getLength()];
//            System.arraycopy(responsePacket.getData(),0,smallerBuffer,0,responsePacket.getLength());
//            System.out.println("new buffer");
//            for( byte c: smallerBuffer){
//                System.out.format("%02X ", c);
//            }
//            System.out.println();
//        ByteArrayInputStream responseInput = new ByteArrayInputStream(smallerBuffer);
//        ByteArrayOutputStream responseOutputBytes = new ByteArrayOutputStream();
//        DNSHeader responseHeader = new DNSHeader(responseInput);
//        DNSMessage responseMessage = new DNSMessage(smallerBuffer,responseHeader);
//        DNSQuestion responseQuestion = new DNSQuestion(responseInput,responseMessage);
//        DNSRecord responseRecord = new DNSRecord(responseInput, responseMessage);
//        responseHeader.writeBytes(responseOutputBytes);
//        responseQuestion.writeBytes(responseOutputBytes,addressesKnown);
//        responseRecord.writeBytes(responseOutputBytes,passAddresses);
//        byte[] responseBytes =  responseOutputBytes.toByteArray();
//        for (byte c : responseBytes) {
//            System.out.format("%02X ", c);
//        }
////        }
    }
}
