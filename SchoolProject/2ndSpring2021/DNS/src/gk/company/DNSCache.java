package gk.company;

import java.util.HashMap;
import java.util.Map;

public class DNSCache {

    HashMap<DNSQuestion, DNSRecord> cacheRecords;


    public DNSCache(){
        this.cacheRecords = new HashMap<>();
    }

    public void add(DNSQuestion question, DNSRecord record){
        cacheRecords.put(question, record);
        checkOldRecords();
    }

    private void checkOldRecords(){
        cacheRecords.forEach((question,record)->{
            if(!record.timestampValid()){
                cacheRecords.remove(question);
            }
        });
    }
}
