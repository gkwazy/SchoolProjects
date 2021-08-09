package gk.company;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.Scanner;

public class HTTPRequest {
    public HTTPRequest() {

    }

    //.transferToPutStream from a file stream.
   public HashMap<String, String> ParseHeader(Socket client) throws IOException {
       InputStream in = client.getInputStream();
       Scanner scanner = new Scanner(in, "UTF-8");
       String data = scanner.useDelimiter(" ").nextLine();
       String[] request = data.split(" ");
       HashMap <String, String> mapRequest = new HashMap<String, String>();
       mapRequest.put("method", request[0]);
       mapRequest.put("path", request[1]);
       mapRequest.put("protocol", request[2]);
       while(true){
           String nextLine = scanner.nextLine();
           if (nextLine.equals("")){
               break;
           }
            String [] tempRequest  = nextLine.split(": ");
            mapRequest.put(tempRequest[0], tempRequest[1]);
       }
       return mapRequest;
    }
}
