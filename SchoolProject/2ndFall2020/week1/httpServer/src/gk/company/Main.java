package gk.company;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class Main {
    private static ServerSocket server;
    public static void main(String[] args) throws IOException {
        server = new ServerSocket(8080);
        System.out.println("Listening for connection on port 8080 ....");
        while(true) {
            Socket clientSocket = server.accept();
            Thread serverThread = new Thread(() -> {
                System.out.println("started thread ... " + Thread.currentThread().getId());
                try {
                    HTTPRequest httpRequest = new HTTPRequest();
                    HTTPResponse httpResponse = new HTTPResponse();
                    String[] request = httpRequest.parseRequest(clientSocket);
                    httpResponse.sendInfo(clientSocket, request);
//                    clientSocket.close();
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
            });
            serverThread.start();
        }
    }
}
