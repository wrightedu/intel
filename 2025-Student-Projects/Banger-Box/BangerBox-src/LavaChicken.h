//Both the Doom theme, Never going to give you up, and the basic song code were made by Robson Couto 
//Lava chicken and The crab rave were made by MG Davis
//All other code was done by Emily Creed and Nick Pontious
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

#define tempo 75
#define buzzer 11
#define red 6
#define blue 5
#define green 3

void lavaChicken() {
    int divider = 0, noteDuration = 0;
    int wholenote = (60000 * 2) / tempo;
    
    // notes of the melody followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    // lava chicken
    int melody[] = {
        REST, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8,
        NOTE_C5, 4, NOTE_A4, 4, REST, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8,
        NOTE_C5, 4, NOTE_A4, 4, REST, 2,
        NOTE_D5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_G4, 8,
        NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_C5, 4, REST, 4,
        NOTE_D5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_G4, 8,
        NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_C5, 4, REST, 4,
        NOTE_D5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_G4, 8,
        NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_D5, 8, NOTE_C5, 4, REST, 4,
        NOTE_D5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_G4, 8,
        NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 0.5
    };

    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int leds[] = {red, green, blue};


    for (int currNote = 0; currNote < notes * 2; currNote += 2) {
        // calculates the duration of each note
        divider = melody[currNote + 1];

        for (int i = 0; i < 3; i++) 
          analogWrite(leds[i], (rand() % 255) + 1);

        if (divider > 0) 
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;  // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[currNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
    }
}