package gk.company;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Base64;
import java.util.HashMap;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) throws IOException, NoSuchAlgorithmException {
        ServerSocket server = new ServerSocket(80);
        System.out.println("Server has started\r\nWaiting for a connection...");
        ArrayList<Room> rooms = new ArrayList<Room>();

        while (true) {
            System.out.println("waiting");
            Socket client = server.accept();
            System.out.println("connect....");

            Thread clientThread = new Thread(() ->{
                    System.out.println("New Connection made");
                    try {
                        HTTPRequest httpRequest = new HTTPRequest();
                        HashMap<String, String> requestMap = null;
                        requestMap = httpRequest.ParseHeader(client);
                        System.out.println(requestMap);
                        HTTPResponse httpResponse = new HTTPResponse();

                        //Get methods
                        if (requestMap.containsKey("Upgrade")) {

                            httpResponse.openWebSocket(requestMap, client);
                           String message = WSResponse.openChannel(client);
                           String messageArray[] = message.split( " ");
                           boolean foundRoom = false;
                           Room wantedRoom = null;
                            for(int i = 0; i < rooms.size(); i++){
                                if (rooms.get(i).name.equals(messageArray[1])){
                                    rooms.get(i).addSocket(client);
                                    wantedRoom = rooms.get(i);
                                    foundRoom = true;
                                }
                            }
                            if (!foundRoom){
                                Room newRoom = new Room(messageArray[1]);
                                rooms.add(newRoom);
                                wantedRoom = newRoom;
                                newRoom.addSocket(client);
                            }
                            WSResponse.loopingChannel(client,wantedRoom);
                        } else {

                            httpResponse.sendInfo(client, requestMap.get("path"));
                        }

                    } catch (IOException | NoSuchAlgorithmException | InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println("end");
            });
            clientThread.start();
        }
    }
}
