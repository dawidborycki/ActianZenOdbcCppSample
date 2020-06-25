#include <stdio.h>
#include <string>
#include "string.h"
#include <iostream>
#include <cmath>
#include "connection.hpp"
#include "tableHelper.hpp"

double* generateSignal(int length) {
    auto phaseStep = 2 * M_PI / length;

    auto signal = new double[length];

    for (int i = 0; i < length; i++) {
        auto phase = 1.0 * i * phaseStep;        

        signal[i] = sin(phase);
    }

    return signal;
}

int main() {
  // Connect to DEMODATA 
  SQLCHAR connectionString[] = "DSN=DEMODATA";  
  auto handleConnection = connect(connectionString);

  // Drop table (if exists)
  dropSineWaveTable(handleConnection);

  // Create table
  createSineWaveTable(handleConnection);   

  // Generate and insert data
  const int N = 512;
  auto data = generateSignal(N);  

  insertData(handleConnection, data, N);

  // Delete signal
  delete data;

  // Fetch data from the database
  fetchData(handleConnection);

  // Disconnect
  disconnect(handleConnection);  
}