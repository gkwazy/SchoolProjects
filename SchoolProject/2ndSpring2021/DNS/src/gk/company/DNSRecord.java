package gk.company;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.util.Calendar;

public class DNSRecord {
    ByteArrayInputStream input;
    DNSMessage message;
    byte[] nameAnswer;
    byte[] typeAnswer;
    byte[] dnsclassAnswer;
    byte[] ipAddress;
    int namelengthAnswer;
    byte[] timeToLive;
    byte[] dataLength;
    byte[] additionalRecords;
    Calendar receivedTime;


    public DNSRecord(ByteArrayInputStream input, DNSMessage message) throws IOException {
        this.input = input;
        this.message = message;
        receivedTime = Calendar.getInstance();
        parseAnswer();

    }

    public void parseAnswer() throws IOException {
        if(message.dnsHeader.question_Response == -128) {
            boolean isAnswer = true;
            byte[] tempNameAnswer = new byte[250];
            byte[] nextSegment = input.readNBytes(1);
            byte isCompressed = (byte) (nextSegment[0] & 0xC0);
            if (isCompressed == -64) {
                //change this to a DNS message to get the name
                tempNameAnswer[0] = nextSegment[0];
                byte [] temp = input.readNBytes(1);
                tempNameAnswer[1] = temp.clone()[0];
                namelengthAnswer = 2;
                isAnswer = false;
            }else {
                while (isAnswer && namelengthAnswer < 250) {

                    if (nextSegment[0] == 0) {
                        System.out.println("done");
                        isAnswer = false;
                    } else {
                        tempNameAnswer[namelengthAnswer] = nextSegment[0];
                        namelengthAnswer++;
                    }
                }
            }
            nameAnswer = new byte[namelengthAnswer];
            System.arraycopy(tempNameAnswer,0,nameAnswer,0, namelengthAnswer);
            typeAnswer = input.readNBytes(2);
            dnsclassAnswer = input.readNBytes(2);
            timeToLive = input.readNBytes(4);
            dataLength = input.readNBytes(2);
            ipAddress = input.readNBytes(4);
        }
        additionalRecords = input.readAllBytes();
    }

    public void buildResponse(InetAddress addressesKnown, String wantedDomain){
        int compression = message.nameCompression.get(wantedDomain);
        nameAnswer = new byte []{(byte) 0xC0, (byte) compression};
        typeAnswer = new byte[]{(byte) 0x00,(byte)0x01};
        dnsclassAnswer = new byte[]{(byte) 0x00,(byte)0x01};;
        ipAddress = AddressToByte(addressesKnown);
        timeToLive = new byte[]{(byte)0x00, (byte)0x00, (byte)0x01, (byte)0x1F};;
        dataLength = new byte[]{(byte)0x00, (byte)0x04};
    }

    private byte[] AddressToByte(InetAddress address){
        byte[] bytes = address.getAddress();
        return bytes;
    }

    boolean timestampValid(){
        int temptime = java.nio.ByteBuffer.wrap(timeToLive).getInt();
        Calendar tempCal = (Calendar) receivedTime.clone();
        Calendar currentTime = Calendar.getInstance();
        tempCal.add(Calendar.SECOND,temptime);
        if (tempCal.getTimeInMillis() - currentTime.getTimeInMillis() < 0){
           return false;
        }
        return true;
    }

    public void writeBytes(ByteArrayOutputStream output) throws IOException {
        if(message.dnsHeader.question_Response == -128) {
            output.write(nameAnswer);
            output.write(typeAnswer);
            output.write(dnsclassAnswer);
            output.write(timeToLive);
            output.write(dataLength);
            output.write(ipAddress);
        }
        output.write(additionalRecords);
    }
}
