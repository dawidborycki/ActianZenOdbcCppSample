#include <sql.h>
#include <sqlext.h>

SQLHDBC connect(SQLCHAR *connectionString) {          
  // Allocate an environment handle
  SQLHENV handleEnvironment;
  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnvironment);
  
  // Set ODBC 3 support
  SQLSetEnvAttr(handleEnvironment, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
  
  // Allocate a connection handle 
  SQLHDBC handleConnection;
  SQLAllocHandle(SQL_HANDLE_DBC, handleEnvironment, &handleConnection);
  
  // Connect  
  auto statusCode = SQLDriverConnect(handleConnection, NULL, connectionString, SQL_NTS,
    NULL, 0, NULL, SQL_DRIVER_COMPLETE);

  // Report connecton status
  if (SQL_SUCCEEDED(statusCode)) {
    std::cout << "Connection succeded" << std::endl;
  } 

  // Free environment handle
  SQLFreeHandle(SQL_HANDLE_ENV, handleConnection);

  return handleConnection;
} 

void disconnect(SQLHDBC handleConnection) {
  // Disconnect
  SQLDisconnect(handleConnection);               
  
  // Free up allocated handle
  SQLFreeHandle(SQL_HANDLE_DBC, handleConnection);

  // Report status
  std::cout << "Disconnected" << std::endl;
}