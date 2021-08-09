package gk.company;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import com.google.gson.Gson;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Scanner;

public class WSResponse {

    public static String openChannel(Socket client) throws IOException {
            byte[] message = parseData(client);
            sendData(client, message);
            String messageString = new String(message, StandardCharsets.UTF_8);
            return messageString;
    }
    public static void loopingChannel(Socket client, Room room) throws IOException {
        while(true) {
            byte[] message = parseData(client);
            String messageString = new String(message, StandardCharsets.UTF_8);
            String[] json = messageString.split(" ",2);
            UserMessage newMessage = new UserMessage(json[0],json[1]);
            room.addMessage(newMessage);
//            Gson gson = new Gson();
//            String jsonString = gson.toJson(newMessage);
            String jsonString = "{ \"user\":\"" + json[0] +"\"," + "\"message\":\"" + json[1]+ "\"}";
            message = jsonString.getBytes();
            for (int i = 0; i < room.clients.size(); i++) {
                sendData(room.clients.get(i), message);
            }
        }
    }

    public static byte[] parseData(Socket client) throws IOException {
            InputStream in = client.getInputStream();
            DataInputStream data = new DataInputStream(in);
            byte byteOpener = data.readByte();
            byte byteMaskLength = data.readByte();
            int intDataLength = ((byteMaskLength) & 0x7f);

            if (byteMaskLength == 126){
                short temp = data.readShort();
                intDataLength = temp;
            } else if( byteMaskLength == 127){
                long temp = data.readLong();
                intDataLength += temp;
            }
            byte[] mask = new byte[4];
            for(int i = 0; i < 4 ; i++){
                mask[i] = data.readByte();
            }
            byte[] maskedResponse = new byte[intDataLength];
            byte[] response = new byte[intDataLength];

            for(int i = 0; i < intDataLength; i++){
                maskedResponse[i] = data.readByte();
                response[i] = (byte) (maskedResponse[i] ^ mask[i%4]);
            }
            return response;
    }

    public static void sendData(Socket client, byte[] message) throws IOException {
        OutputStream out = client.getOutputStream();
        byte[] response = new byte[2 + message.length];
        response[0] = (byte) 0x81;
        response[1] = (byte) message.length;

        if (message.length > 65536 ){
            response[2] = (byte) ((message.length >> 16) & 0xFF);
            response[3] = (byte) ((message.length >> 16) & 0xFF);
            response[4] = (byte) ((message.length >> 8) & 0xFF);
            response[5] = (byte) message.length;
            response[1] = 127;

        }else if (message.length > 125 ){
            response[2] = (byte) ((message.length >> 8) & 0xFF);
            response[3] = (byte) message.length;
            response[1] = 126;
        }
        for(int i = 0; i < message.length; i++){
            response[i+2] = message[i];
        }
//        response[2] = message[0];
        out.write(response, 0, response.length);
    }
}
