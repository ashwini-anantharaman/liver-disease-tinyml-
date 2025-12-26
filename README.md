# liver-disease-tinyml-
Python, C++,TensorFlow Lite,Arduino IDE, Scikit-Learn, Pandas, Embedded Systems. Created a low-power, offline inference engine for medical diagnostics. Trained a neural network on the ILPD dataset, handled class imbalance via resampling, and deployed the quantized model to an Arduino Nano 33 BLE to classify patient health status via LED indicators.

# TinyML Liver Disease Detector 🏥

An offline, embedded AI device capable of diagnosing liver disease risk in real-time. This project runs a quantized neural network directly on an **Arduino Nano 33 BLE**, demonstrating edge computing capabilities for medical diagnostics.

## 🚀 Overview
* **Device:** Arduino Nano 33 BLE
* **Model:** Deep Neural Network (trained in TensorFlow/Keras)
* **Input:** 10 Biomarkers (Age, Bilirubin, Enzymes, Proteins, etc.)
* **Output:** Real-time Risk Assessment (Low Risk / High Risk) via LED indicators.

## 🛠️ Tech Stack
* **Python:** Pandas, Scikit-Learn, TensorFlow (Model Training)
* **C++:** Arduino Wiring (Firmware)
* **Edge AI:** TensorFlow Lite for Microcontrollers

## 📂 Project Structure
* `python/`: Contains the Jupyter Notebook used to clean data, train the model, and convert it to a C byte array.
* `arduino/`: Contains the source code (`.ino`) and the model header file (`model.h`) for the microcontroller.

## ⚙️ How it Works
1.  **Data Processing:** The model was trained on the *Indian Liver Patient Dataset (ILPD)* using Python.
2.  **Quantization:** The trained model was converted to a TensorFlow Lite `int8` model and exported as a C++ byte array.
3.  **Inference:** The Arduino accepts patient data via the Serial Monitor, normalizes the inputs, and runs inference on-chip.
4.  **Result:** * **LED OFF:** Prediction < 0.5 (Healthy)
    * **LED ON (Orange):** Prediction > 0.5 (Potential Liver Disease)

## 🩺 Usage
1.  Connect the Arduino Nano 33 BLE via USB.
2.  Open the Serial Monitor (9600 baud).
3.  Input patient data in the following CSV format:
    `Age, Gender(0/1), TB, DB, Alkphos, Sgpt, Sgot, TP, Albumin, AG_Ratio`
4.  Example Input: `65, 1, 0.7, 0.1, 187, 16, 18, 6.8, 3.3, 0.9`

---
*Created by [Your Name]*
