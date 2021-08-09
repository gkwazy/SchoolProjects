package assignment06;

import java.util.ArrayList;

public class TimingCode {

  public static void main(String[] args) {
    long startTime, midpointTime, stopTime;
    BadHashFunctor badHash = new BadHashFunctor();
    MediocreHashFunctor medHash = new MediocreHashFunctor();
    GoodHashFunctor goodHash = new GoodHashFunctor();
   int tableSize = 1000;
//	ChainingHashTable chain = new ChainingHashTable(tableSize, badHash);
	ChainingHashTable chain = new ChainingHashTable(tableSize, goodHash);
//	ChainingHashTable chain = new ChainingHashTable(tableSize, goodHash);
	ArrayList<String> wordList = new ArrayList<String>();
	
    String[] wordArray = {"VdtvfQpzmNqAbTKiClZq",
                          "ShSfEeCIcBTsVxnXcsjy",
                          "sjEbtzfgtpzUvzOYKcZW",
                          "QHxZnqFcudjaCwZZLhOW",
                          "gwrrtEtPrMdHGazAAbzb",
                          "qkpsDcZmQUUXIwUkFmjZ",
                           "XobMaUfaeEnHDHUpabXE",
                          "bruaqoSNwXHBzKKzOLTq",
                          "UfXBrxKqYIDnAMZyPVt",
                          "FfTeFGVMsQuvyMFoxJZs",
                          //10
                          "YrPCdJGLMDzUzblOFzNb",
                          "pgZAjisUiPIgZwxQVylb",
                          "QlcHLznOShjbmYqGvRym",
                          "czxXADdlaEljbzXvyrcJ",
                          "nXINNgRltWgLDSYTrbUx",
                          "MVQcnPJIikLeOylfMHwz",
                          "IiUPqYgUCOGyePiVfygn",
                          "IgGItjTennTTyeIXyDmw",
                          "AdOOioEBGsxvEtpLtIGU",
                          "DRZRAKBMxYdeOvzisYAc",
    //20
    "kZenVLzZPmbDxKJcIjhh",
    "ymiXKrPdolGErVUnRUBP",
    "LmRmKvmfvKTTMmkldqKo",
    "mZIuzJCnskslCtrGpFcB",
    "zYZUXWDJfBwMiaBLvGQw",
    "xfMkkVWvGgnhbHGVteWC",
    "vxJwcMXrcFVKRhKmTwUV",
    "skeUSSuFHmVHOwaDttaR",
    "NjnztrBhSyUrlnqGpNHV",
    "njogUHpLYBEoXNcekpKt",
    "VWGcFLaYKHvFXUtapoiu",
    "LqpwuKsbbEcPsubAhlTZ",
    "lgfuuAdEdAROFQqJtufW",
    "SlHPgmvfqeLGQHtcpBAk",
    "aWDfgnzcamPOSBHCBBwP",
    "qVAvQKhvwPboLTiWsQJF",
    "EQWYTiQAJcAhPcHNBwRN",
    "dmUZHseEyAUdSdxXpUpR",
    "oiPqfuPpmZaJvnuoPQRt",
    "HjlWbeANIHQalRHeHAwQ",
    "ounTqWbBwcPWcfifcpSg",
    "NQdciTGMCynYGpqKCnAN",
    "HMaSHJyWHNnjSvbVSvNx",
    "yPcuuEuDSAPjClCgNRGS",
    "IXjoyKLqgHOMZuXpVoWn",
    "ooTtVNdguEXkSdNewxjx",
    "BpJthzidSHvdvVcHcSNb",
    "cTVjeeukIGuSJbnSIeok",
    "fYfMcJIxCBZzWFhmfbsi",
    "JgqlurKFCNRJEQLRDMEf",
    "NDAMhgwvDOiCzouFmMhA",
    "JAaGpzVarfFYNLVAnnuY",
    "MDCAAYOULXlVrnRDUpkS",
    "xuEROrGBZwZyQefxumNg",
    "jEzNbhiuIYKxvgxYSMyr",
    "ouGsLCQlOoIuccbgrmxR",
    "nEGtKXSdbDsvNMusFGqa",
    "VQflMYehuWJiJEaIWpjD",
    "dnoNMGrQkNhVCSnyIcZo",
    "OojPLlqueRWMOpWmRuPS",
//60
    "tkzAEabjxxKEEnAvhimI",
    "oKwTLpCijEXUwmTuMpXz",
    "nzvzEfxNReXYZwGfaZfV",
    "pHEwJZUeRnpGekglBqZU",
    "VFMYDcMVFajEdnXPgQJg",
    "FDlRVtePxaGvyTfbdUqO",
    "UQsLcWSvsFYizPTuhapD",
    "ztZuPoOFAEbmuvaDsXAM",
    "jbicVMrFSNrDDKpWzdSq",
    "iZIUjffrXqZQspNtscxT",
    "imiywFxmJktEOwbTdhdx",
    "NOKHswGOmdzZcCDFlZnA",
    "jhDHimyVsFOwbYrtcdCi",
    "NxmiVHkEPfUVIIHtoveZ",
    "JDPFptEpSxvnATvQvWNc",
    "VMFXWxGTQEiNjMSGQfWu",
    "CqNDOokKSklsoRzteWnf",
    "zGmTRxyDpehqyJZFIVTX",
    "mYDlnvzuLCDslrJMBHdr",
    "FCctyiQonPiLAvaxwHuP",
    "dNqEhZESXoIcpVJLRYlU",
    "guYzSwtiHRnsLsZtlaKu",
    "aRQyzuCrFYStaUchQHgY",
    "qTqIPqnqCcjjkIzWSaGC",
    "PcGsHKFNJMFiHLCdjUXk",
    "uUCUSFMeOpXUTyYCXpbL",
    "NwaSTcBrsTXnAXOvipeU",
    "EbBJnbYeAgdhSLTPFMad",
    "ZPsvfQleIpmAaNZhiJwA",
    "YroAIrmosWKvKfaJOAvi",
    "prlGatvdCVtGhIpiKgZU",
    "bTjzhXwxbxguLBVLkjSm",
    "iaRRudvbnikkqJmjivNw",
    "HpHVZXttiHRDggFHNNoQ",
    "iopLiYrgeAaEXKkSYayZ",
    "pObPTSuJnwrfTSIlwJZL",
    "URvoFJNMXwnhtsYfgnik",
    "HMOilBiJWwUbDkaNHXAk",
    "vAvMtbDmSceFqIvEuLVv",
    "HmlfRCWoBziCIwYMywin",
    "WDmCFofFWXbmgMiquFMZ",
    "YAWnumrYxSyCxJYxvMPl",
    "gbnrlvUYfYSKvxyaiGap",
    "IVvVwpTnoVBjPwhyNPmq",
    "reWQksFQWrbLxJdpwjmF",
    "PALiINLNfjnzCtKSVcox",
    "snkdRBLOfhAkZKhDxVjK",
    "qeoqKueqVRfHRbauBcNG",
    "eLNGKnVRDWAdNKTPtSsf",
    "bRVHsVrWTPwNAVCqVifn",
    "pCGlQiKYwUgmfRlMFNBN",
    "hYozlHjkxhimNDIxDQxg",
    "omaGUfuRSyOdQpSdiISH",
    "LjcLBVZymfVAOMxeBCvz",
    "ltBXFQCuCKLhjObSbuuN",
    "kuzwylokTYBckgOYbOpe",
    "RoNlCdmtHvPwONoMtuYC",
    "CgcFmCJxsdtzBTqycIRX",
    "eTWbUzYVkpkkIhtivrJr",
    "yxCtJSFZIfkINXghXvfp",
//    120
   "XFrswguhNNqHLIitjDWS",
   "VKnLpuMBqJeouHUmMboz",
   "bSkOrvWQPfVkVTjUXNkN",
   "ybBrUmjNpLkNRYuvXbvD",
   "CwqEFLhtteBgTzmSOBnS",
   "PvPoiGCxANkFjtWduoVY",
   "liHINLwpdoZwBhBFcKEi",
   "dXhBhUXbKCZfLvwoaJSI",
   "JpSRgMRVusrHNTpVjCfg",
   "bXrsRTbElhJPyQdzplHo",
   "tETLcabqoZHOHGFevYLr",
   "tdDAPLpeQakYnDIVEdCU",
   "NuHdQrUxwNSCDFeaLTCn",
   "VujFRoMPnRIgbjpURoea",
   "JZsFONmwDyvCeMqlZCDH",
   "rvbOKBchaNsCQzsqptVK",
   "usTwQcCtnVdhioAPxDrf",
   "euGiQeEYQaWLTyyNTPoM",
   "qbLktKVEnAiVDpaokGSS",
   "kvryExLyPPdIIaOtbcTW",
   "tPSkkLYYwHskqfcTAiTb",
   "gcnXxShUjYVMRFKZINxD",
   "PAjZFaAKcABsQamwXIEv",
   "RcZZuxrVhTkggeKWguUA",
   "vffkKnLbeNmZFOznFcXZ",
   "BQesgQghblXNQxwetpEv",
   "csPmhjbXPqGEuriDZyOR",
   "auXTzzlZdArVSQfyHaMA",
   "rpKoNmQYZaEdvkVWqdqx",
   "naxVLIkELINsPiturpea",
   "fcqfmKfcVkopIBpBsYIN",
   "MadipiMOWEtApxQtbfdq",
   "WvqNAvNXrvJtiZAtYhGT",
   "fLqdxdIZmOtrqCfCXkEg",
   "HsNobjDQzkfFbjcWOOah",
   "JymgvBSVbyJNAVFuIryP",
   "aCgIhgJuPAYZGQpAcwgt",
   "AfmWLfeeSnGspvabQwsk",
   "OrsPtwOJkkTjzXZOSvZp",
   "uzQnYKMmQJOLrcLvrnTk",
   "zCBNGFTTbflQGtifgWTa",
   "YGwQIZsTTwVwfvXVVuwO",
   "uiCIzebtjLnGbwPxVkuC",
   "PuMhYbLgqevUMWMLVxbI",
   "fkAvcVwnYxuzLIbSszFd",
   "JsGVywoKryfNbzNUDUCP",
   "THvcyjdCuxxAeIYUesmw",
   "FIQkZKVWEcoPUzYGJjIp",
   "zgDVlEapSmpPJldveSGM",
   "VhOUPKkjiQRPAoeDsWiQ",
   "kVUAeerxgcmNwSVaYkQB",
   "hmHCDjPtHDsioVpRJcjM",
   "PcKqyuiAiQEYTBLcbonb",
   "DtZkemGicvwxTVwhWwXP",
   "ySWpHTPvxSxTspnjNWqD",
   "NrIktTJaYimdiVKcEZTr",
   "FSRwNtBSrsKrGilmESVV",
   "vWJwYknRiWMwKjgijWiU",
   "GhUOhDlNAuYiNEtwkmCq",
   "PLsHeiJuurqNWdISfDlD",
   "lWUwuyDNlhGmaDdpYckt",
   "vvwYsskaCfoBWuBMiVio",
   "lJPNcNCPQjnBjaHjdHvF",
   "tbICiKgUwRhIgWCjJwJO",
   "iwAXjEkAtEpxTJfAQGxc",
   "TttiRpXqoFHGMFAPzAxA",
   "JUJzdlamZLwByxaRXplE",
   "ReBsyfnsjXmwXCuXuqNm",
   "GZbopPGPMDEruODlCFNk",
   "OHNCQcbnmYifZSvptpJz",
   "HvGSrraQRUvRGeKKCMGs",
   "mrwfcgjbnMhhkTyLMBIx",
   "CROnlfyWlBPbWVVqplLH",
   "MIxQqRmdylkhiPjKpoUX",
   "YrAiCqSgXwPGbgVoTRns",
   "XLcuYSkaSUIeuSbQaszG",
   "dXRFRokKnjLjuEuFPrwt",
   "RlpzQbjVHXArYjHbEhfa",
   "QbSrwYZXEoFvEUYiRGpq",
   "GpsIHgOJGiQoEZcNKqBc",
   "ImXFqBYZvCkQgDqwQTts",
   "AZCilxcdRgzyEgEdcfsg",
   "pjnIUWPEODhzmXpjYHVh",
   "ozSOwpfNaRWPOrQPiciF",
   "AEodamHyRlXQrsyFxoJI",
   "MxFTLquFXuKLJVWOKhTD",
   "DwsQhmmgUnJUrYFdXGrJ",
   "ZnzRRsKSAZmbDEoLDLJP",
   "wHBbpXlOluKcFlXYDymu",
   "TLbQvhIDCQGMBfilyfkh",
   "hFLCXCJejWPxeggiEOGb",
   "ljVzkCTAsSTQuhYoGiNs",
   "xVLlXKcsWnBmsTQSmyFH",
   "bCxUNBXWpValMEABYJDf",
   "xitWQojUzXemcjsgCXRa",
   "OcHiEqREuHMrMyuufLoB",
   "JuRZNRTTavnBUUtleFGK",
   "FmWonQFQEBtfyTTaQcJw",
   "hZssOkeXDtRxGIuFCwiw",
   "XvMxQNcRTDwjqlGIKMZm",
   "djofekcsvWRgmzuUwLjk",
   "ydtRLhoiqJLQyQGoCWXv",
   "fGRuDJixQNfYzGwhawNd",
   "YmNeniGwwyGGPtmiwjeA",
   "pqrsYYODmUteuYcbbVJt",
   "PEaNBuKHGObIpSEFnKfl",
   "CFyMxfxMKjgGzQyewxAS",
   "vtGZXzWjKZZdiIZkAbLt",
   "XBQKtJzoYJTHypBdDACJ",
   "KpJqpAxTEvpGMMJiPLpY",
   "DKhSKLRRLiBUcqgWNPkm",
   "LrFBCFgPPwFmfYjbGKKl",
   "kwutcxONCeUBRtniBRWC",
   "FRcBvYQnmMxoJUqHUYko",
   "jFKizMgkXfnVuCLPSDfs",
   "ivNhDmeMnwGpgRtscweI",
   "pAVOpDqmanXOucrzOenz",
   "JfmkUlzzVJNKIwahMzqG",
   "wThwAWAMpCtKeaLoUIOs",
   "uAxoJoWdOQnOcCoawWCp"};
    
    //240
    
    for(int i = 0; i < wordArray.length; i++) {
    	wordList.add(wordArray[i]);
    }
    
    
    
    // First, spin computing stuff until one second has gone by.
    // This allows this thread to stabilize.
for(int j = 0; j < 5; j++ ) {
    startTime = System.nanoTime();
    while (System.nanoTime() - startTime < 1000000000) { // empty block
    }

    // Now, run the test.

    long timesToLoop = 1000;
    chain.addAll(wordList);

    startTime = System.nanoTime();

    for (long i = 0; i < timesToLoop; i++) {
    	chain.contains("kVUAeerxgcmNwSVaYkQB");
    	chain.contains( "FRcBvYQnmMxoJUqHUYko");
    	
    }
      
    	  
    	  //stuff for code goes here. 

    midpointTime = System.nanoTime();

    // Run an empty loop to capture the cost of running the loop.

    for (long i = 0; i < timesToLoop; i++) { // empty block
    }

    stopTime = System.nanoTime();

    // Compute the time, subtract the cost of running the loop
    // from the cost of running the loop and computing square roots.
    // Average it over the number of runs.

    double averageTime = ((midpointTime - startTime) - (stopTime - midpointTime)) / timesToLoop;
//    System.out.println(chain.collisions);
//    System.out.println(chain.size);
//    System.out.println(chain.capacity);

    System.out.println(
        averageTime );
//    System.out.println(tableSize);
tableSize *= 2;
chain = new ChainingHashTable(tableSize, goodHash);
chain.addAll(wordList);
  }
System.out.println(tableSize);
  }
  
};
