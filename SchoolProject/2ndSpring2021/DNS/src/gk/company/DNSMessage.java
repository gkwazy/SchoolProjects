package gk.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;

public class DNSMessage {
    byte[] wholeMessage;
    byte[] finalMessage;
    DNSHeader dnsHeader;
    DNSQuestion dnsQuestion;
    DNSRecord dnsRecord;
    HashMap<String, Integer> nameCompression = new HashMap<>();

    public DNSMessage(byte[] bytes,DNSHeader dnsHeader) throws IOException {
        ByteArrayInputStream inputStream = new ByteArrayInputStream(bytes);
        inputStream.skip(12);
        this.wholeMessage = bytes;
        this.dnsHeader = dnsHeader;
        this.dnsQuestion = new DNSQuestion(inputStream,this);
        this.dnsRecord = new DNSRecord(inputStream, this);
    }

    private String[] realDomainName(InputStream input) throws IOException {
        int lengthOfSegment = input.read();
        if(lengthOfSegment == 0){
            return null;
        }
        String[] tempName = new String [250];
        int stringcount = 0;
        boolean reading = true;
        while(reading) {
            for (int i = 0; i < lengthOfSegment; i++) {
                byte[] tempArray = new byte[lengthOfSegment];
                tempArray = input.readNBytes(lengthOfSegment);
                tempName[stringcount] = new String(tempArray);
                stringcount++;
                int charatersMore = input.read();
                if (charatersMore == 0) {
                    String[] shortName = new String[stringcount];
                    System.arraycopy(tempName, 0, shortName,0,stringcount);
                    return shortName;
                }else{
                    lengthOfSegment = charatersMore;
                }
            }
        }
        return null;
    }

    public String readDomainname(int firstByte) throws IOException {
        ByteArrayInputStream stream = new ByteArrayInputStream(wholeMessage);
        stream.skip(firstByte);
        String[] nameArray = realDomainName(stream);
        String domainName = "";
        for(int i=0; i< nameArray.length-1;i++){
            domainName = domainName + nameArray[i] + ".";
        }
        domainName = domainName + nameArray[nameArray.length-1];
        return domainName;
    }

    private byte[] toBytes(DNSHeader header) throws IOException {
        ByteArrayOutputStream outputBytes = new ByteArrayOutputStream();
        header.writeBytes(outputBytes);
        dnsQuestion.writeBytes(outputBytes);
        dnsRecord.writeBytes(outputBytes);
        byte[] responseBytes = outputBytes.toByteArray();
        return responseBytes;
    }

//    public static void writeDomainName(ByteArrayOutputStream output,
//                                HashMap<String, Integer> domainLocations,
//                                String[] domainPieces){
//
//    }

    public String octetsToString(String[] nameArray){
        String domainName = "";
        for(int i=0; i< nameArray.length-1;i++){
            domainName = domainName + nameArray[i] + ".";
        }
        domainName = domainName + nameArray[nameArray.length];
        return domainName;
    }

    public byte[] inMemoryResponse(InetAddress addressesKnown) throws IOException {
      dnsHeader.changeToResponse();
      dnsRecord.buildResponse(addressesKnown,dnsQuestion.stringName);
      byte[] response = toBytes(dnsHeader);
      return response;
    }

    public byte[] askGoogle() throws IOException {
        DNSHeader googleHeader = new DNSHeader();
        byte[] askBytes = toBytes(googleHeader);
        return askBytes;
    }

    public byte[] googleResponse(DNSCache cache, DNSMessage inputMessage) throws IOException {
        dnsHeader.ID = inputMessage.dnsHeader.ID;
        dnsHeader.question_Response = (byte)-128;
        dnsRecord.timestampValid();
        byte[] response = toBytes(dnsHeader);
        return response;
    }

    public void storeAddress(HashMap<String,InetAddress> addressesKnown) throws UnknownHostException {
        System.out.println("Saving address");
        InetAddress wantedAddress = InetAddress.getByAddress(dnsRecord.ipAddress);
        System.out.println(wantedAddress.getHostAddress());
        addressesKnown.put(dnsQuestion.stringName, wantedAddress );
    }

}
