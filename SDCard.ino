void inicijalizacijaIPisanje() {
  Serial.print("Initializing SD card...");
  /* initialize SD library with Soft SPI pins, if using Hard SPI replace with this SD.begin()*/
  
  byte CS = 14; 
  byte mosi = 27;
  byte miso = 25;
  byte sck = 26;
  
  if (!SD.begin(CS, mosi, miso, sck)) { 
    Serial.println("Inicijalizacija neuspesna");
    return;
  }
  Serial.println("Inicijalizacija uspesna");
  /* Begin at the root "/" */
  root = SD.open("/");
  if (root) {
    printDirectory(root, 0);
    root.close();
  } else {
    Serial.println("Greska prilikom otvaranja fajla");
  }
  /* open "test.txt" for writing */
  root = SD.open("test1.txt", FILE_WRITE);
  /* if open succesfully -> root != NULL
    then write string "Hello world!" to it
  */
  if (root) {
    root.println("Proba upisivanja");
    root.flush();
    /* close the file */
    root.close();
  } else {
    /* if the file open error, print an error */
    Serial.println("Greska prilikom probe upisivanja");
  }
  delay(1000);
}

void procitajFajl() {
  root = SD.open("test1.txt");
  if (root) {
    /* read from the file until there's nothing else in it */
    while (root.available()) {
      /* read the file and print to Terminal */
      Serial.write(root.read());
    }
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }

  Serial.println("done!");
}

  void printDirectory(File dir, int numTabs) {

  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');   // we'll have a nice indentation
    }
    // Print the name
    Serial.print(entry.name());
    /* Recurse for directories, otherwise print the file size */
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      /* files have sizes, directories do not */
      Serial.print("\t\t");
      Serial.println(entry.size());
    }
    entry.close();
  }
}