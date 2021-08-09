package gk.company;

import java.io.*;
import java.util.Arrays;
import java.util.Objects;
import java.util.Random;

public class DNSHeader {
    ByteArrayInputStream input;
    byte[] ID;
    byte[] flags;
    byte[] questionCount;
    byte[] answerCount;
    byte[] authority;
    byte[] additional;
    byte question_Response;
    byte opCode;
    byte aaheader;
    byte tcheader;
    byte rdheader;
    byte raheader;
    byte zheader;
    byte rcodeheader;
    byte[] finalFlag;

    public DNSHeader(){
        Random rand = new Random();
        int part1ID = rand.nextInt(120);
        int part2ID = rand.nextInt(120);
        this.ID = new byte[]{(byte) part1ID, (byte) part2ID};
        this.flags = new byte[]{(byte) 0x01, (byte) 0x20};
        this.questionCount = new byte[]{(byte) 0x00, (byte) 0x01};
        this.answerCount = new byte[]{(byte) 0x00, (byte) 0x00};
        this.authority = new byte[]{(byte) 0x00, (byte) 0x00};
        this.additional = new byte[]{(byte) 0x00, (byte) 0x01};
    }

    public DNSHeader(ByteArrayInputStream input) throws IOException {
        this.input = input;
        this.ID = input.readNBytes(2);
        this.flags = input.readNBytes(2);
        this.questionCount = input.readNBytes(2);
        this.answerCount = input.readNBytes(2);
        this.authority = input.readNBytes(2);
        this.additional = input.readNBytes(2);

        parseFlags(flags);
    }

    public void changeToResponse(){
        question_Response = (byte) -128;
        answerCount[0] = 0x00;
        answerCount[1] = 0x01;
    }

    public void writeBytes(ByteArrayOutputStream output) throws IOException {
        finalFlag = makeFinalFlag();
        output.writeBytes(ID);
        output.writeBytes(finalFlag);
        output.writeBytes(questionCount);
        output.writeBytes(answerCount);
        output.writeBytes(authority);
        output.writeBytes(additional);
        byte[] responseBytes =  output.toByteArray();
    }
//assigns flags to the variables above.
    private void parseFlags(byte[] flags){
    this.question_Response = (byte) (flags[0] & 0xC0);
    this.opCode = (byte) (flags[0] & 0x78);
    this.aaheader = (byte) (flags[0] & 0x04);
    this.tcheader = (byte) (flags[0] & 0x02);
    this.rdheader = (byte) (flags[0] & 0x01);
    this.raheader = (byte) (flags[1] & 0x80);
    this.zheader = (byte) (flags[1] & 0x070);
    this.rcodeheader = (byte) (flags[1] & 0x0F);
    }

    private byte[] makeFinalFlag(){
        byte[] returnBytes = new byte[2];
        returnBytes[0] = (byte) (question_Response | opCode<<3);
        returnBytes[0] = (byte) (returnBytes[0] | aaheader<<2);
        returnBytes[0] = (byte) (returnBytes[0] | tcheader<<1);
        returnBytes[0] = (byte) (returnBytes[0] | rdheader);
        returnBytes[1] = (byte) (raheader | zheader | rcodeheader);
        return returnBytes;
    }

    @Override
    public String toString() {
        return "DNSHeader{" +
                "input=" + input +
                ", ID=" + Arrays.toString(ID) +
                ", flags=" + Arrays.toString(flags) +
                ", questionCount=" + Arrays.toString(questionCount) +
                ", answerCount=" + Arrays.toString(answerCount) +
                ", authority=" + Arrays.toString(authority) +
                ", additional=" + Arrays.toString(additional) +
                ", question_Response=" + question_Response +
                ", opCode=" + opCode +
                ", aaheader=" + aaheader +
                ", tcheader=" + tcheader +
                ", rdheader=" + rdheader +
                ", raheader=" + raheader +
                ", zheader=" + zheader +
                ", rcodeheader=" + rcodeheader +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof DNSHeader)) return false;
        DNSHeader dnsHeader = (DNSHeader) o;
        return question_Response == dnsHeader.question_Response &&
                opCode == dnsHeader.opCode &&
                aaheader == dnsHeader.aaheader &&
                tcheader == dnsHeader.tcheader &&
                rdheader == dnsHeader.rdheader &&
                raheader == dnsHeader.raheader &&
                zheader == dnsHeader.zheader &&
                rcodeheader == dnsHeader.rcodeheader &&
                Objects.equals(input, dnsHeader.input) &&
                Arrays.equals(ID, dnsHeader.ID) &&
                Arrays.equals(flags, dnsHeader.flags) &&
                Arrays.equals(questionCount, dnsHeader.questionCount) &&
                Arrays.equals(answerCount, dnsHeader.answerCount) &&
                Arrays.equals(authority, dnsHeader.authority) &&
                Arrays.equals(additional, dnsHeader.additional);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(input, question_Response, opCode, aaheader, tcheader, rdheader, raheader, zheader, rcodeheader);
        result = 31 * result + Arrays.hashCode(ID);
        result = 31 * result + Arrays.hashCode(flags);
        result = 31 * result + Arrays.hashCode(questionCount);
        result = 31 * result + Arrays.hashCode(answerCount);
        result = 31 * result + Arrays.hashCode(authority);
        result = 31 * result + Arrays.hashCode(additional);
        return result;
    }
};
