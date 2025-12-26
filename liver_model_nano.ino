#include <EloquentTinyML.h>
#include "model.h"

// ---------------------------------------------------------
// 1. SETTINGS FOR VERSION 0.0.10
// ---------------------------------------------------------
#define NUMBER_OF_INPUTS 10
#define NUMBER_OF_OUTPUTS 1
// 60KB is usually the sweet spot for un-optimized models on Nano 33 BLE
#define TENSOR_ARENA_SIZE 60 * 1024 

// Define the ML Object (Version 0.0.10 Syntax)
Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(9600);
    delay(3000);
    Serial.println("Initializing Liver Monitor (v0.0.10)...");
    
    // Initialize the model
    ml.begin(model_data);
    Serial.println("Model Loaded!");
    
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        input.replace(" ", ""); // Safety: remove spaces
        
        // ---------------------------------------------------------
        // 2. PARSING (Robust method)
        // ---------------------------------------------------------
        float user_input[NUMBER_OF_INPUTS];
        int r = 0;
        int t = 0;

        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == ',') {
                if(t < NUMBER_OF_INPUTS) {
                    user_input[t] = input.substring(r, i).toFloat();
                    t++;
                }
                r = i + 1;
            }
        }
        // Catch the last number
        if(t < NUMBER_OF_INPUTS) {
             user_input[t] = input.substring(r).toFloat();
        }

        // ---------------------------------------------------------
        // 3. YOUR SPECIFIC MATH (Pre-filled)
        // ---------------------------------------------------------
        float MEANS[] = { 44.74614065, 0.75643224, 3.29879931, 1.48610634, 290.57632933, 80.71355060, 109.91080617, 6.48319039, 3.14185248, 0.94056603 };
        float SCALES[] = { 16.17594241, 0.42923478, 6.20419395, 2.80608792, 242.72954813, 182.46366758, 288.67063666, 1.08452016, 0.79483625, 0.32768095 };

        // Normalize inputs
        float processed_input[NUMBER_OF_INPUTS];
        for (int i=0; i<NUMBER_OF_INPUTS; i++) {
            processed_input[i] = (user_input[i] - MEANS[i]) / SCALES[i];
        }

        // ---------------------------------------------------------
        // 4. PREDICT
        // ---------------------------------------------------------
        float prediction = ml.predict(processed_input);
        
        Serial.print("Raw Score: ");
        Serial.println(prediction);

        // Logic: 0 = Healthy, 1 = Disease
        // We use > 0.5 as the cutoff
        if (prediction > 0.5) {
            Serial.println("Diagnosis: POSITIVE (High Risk)");
            digitalWrite(LED_BUILTIN, HIGH);
        } else {
            Serial.println("Diagnosis: NEGATIVE (Healthy)");
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}
