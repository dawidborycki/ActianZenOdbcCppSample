SQLRETURN executeSqlStatement(SQLHDBC handleConnection, SQLCHAR *statement) {
  // Allocate SQL statement handle
  SQLHSTMT handleStatement = SQL_NULL_HSTMT;  
  SQLAllocHandle(SQL_HANDLE_STMT, handleConnection, &handleStatement);

  // Execute SQL statement
	SQLRETURN statusCode = SQLExecDirect(handleStatement, statement, SQL_NTS);

  // Free SQL statement handle
  SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);

  // Return status code
  return statusCode;
}

void dropSineWaveTable(SQLHDBC handleConnection) {
  SQLCHAR dropSineWaveTableStatement[] = "DROP TABLE IF EXISTS sineWave";

  executeSqlStatement(handleConnection, dropSineWaveTableStatement);
}

void createSineWaveTable(SQLHDBC handleConnection) {  
  SQLCHAR createSineWaveTableStatement[] = "CREATE TABLE sineWave (timecaptured autotimestamp, signal real, signalReversed real)";

  auto statusCode = executeSqlStatement(handleConnection, createSineWaveTableStatement);
  
  if(statusCode == SQL_SUCCESS || statusCode == SQL_SUCCESS_WITH_INFO) {
    std::cout << "Table created" << std::endl;
  }
  else {
    std::cout << "Table creation error" << std::endl;
  }
}

void insertPoint(SQLHDBC handleConnection, 
  double pointSignal, double pointSignalReversed) {

  // Prepare statement  
  std::string insertPointStatement = 
    "INSERT INTO sineWave (signal, signalReversed) VALUES("    
    + std::to_string(pointSignal) + ", "
    + std::to_string(pointSignalReversed) + ")";    

  // Convert to SQLCHAR
  SQLCHAR sqlStatement[1024];
  strcpy((char *)sqlStatement, insertPointStatement.c_str()); 

  // Execute
  executeSqlStatement(handleConnection, sqlStatement);  
}

void insertData(SQLHDBC handleConnection, double* signal, int signalLength) {
  for(int i = 0; i < signalLength; i++) {
    insertPoint(handleConnection, signal[i], -signal[i]);
  }
}

void fetchData(SQLHDBC handleConnection) {
  // SELECT statement
  SQLCHAR fetchDataStatement[] = "SELECT signal, signalReversed FROM sineWave";

  // Allocate statement handle
  SQLHSTMT handleStatement = SQL_NULL_HSTMT;  
  SQLAllocHandle(SQL_HANDLE_STMT, handleConnection, &handleStatement);

  // Execute
  SQLRETURN statusCode = SQLExecDirect(handleStatement, 
    fetchDataStatement, SQL_NTS);  
 
  // Bind to columns  
  double signal, signalReversed;  

  const int columnCount = 2;
  SQLLEN indicator[columnCount];  
    
  SQLBindCol(handleStatement, 1, SQL_C_DOUBLE, &signal, 0, &indicator[0]);
  SQLBindCol(handleStatement, 2, SQL_C_DOUBLE, &signalReversed, 0, &indicator[1]);  

  // Loop through the results
  std::cout << "Fetching data ..." << std::endl;

  while(true)
  {
    auto statusCode = SQLFetch(handleStatement);        

    // Check status code, and display row data
    if(statusCode == SQL_SUCCESS || statusCode == SQL_SUCCESS_WITH_INFO)
    {
      std::cout << signal << " " << signalReversed << std::endl;
    }
    else
    {
      break;
    }    
  }

  std::cout << "Fetching complete" << std::endl;

  // Free statement handle
  SQLFreeHandle(SQL_HANDLE_STMT, handleStatement);
}