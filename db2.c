#include <stdio.h>
#include <sql.h>
#include <sqlext.h>




void print_error(
    SQLSMALLINT htype, /* A handle type identifier */
    SQLHANDLE   hndl,  /* A handle */
    SQLRETURN   frc,   /* Return code to be included with error msg  */
    int         line,  /* Used for output message, indcate where     */
    char *      file   /* the error was reported from  */
    ) { 

  SQLCHAR     buffer[SQL_MAX_MESSAGE_LENGTH + 1] ;
  SQLCHAR     sqlstate[SQL_SQLSTATE_SIZE + 1] ;
  SQLINTEGER  sqlcode ;
  SQLSMALLINT length, i ; 
  SQLINTEGER NumRecords;

  fprintf(stderr, ">--- ERROR -- RC = %d Reported from %s, line %d ------------\n",
      frc,
      file,
      line
      ) ; 
  SQLGetDiagField(htype, hndl, 0,SQL_DIAG_NUMBER, &NumRecords, SQL_IS_INTEGER,NULL);
  //kartik_cleanup
    fprintf(stderr,"Total Number of diagnostic records: %d\n",NumRecords);
    fprintf(stderr,"Total Number of diagnostic records: %ld\n", (long int) NumRecords);
    //~kartik_cleanup
     i = 1 ; 
   while ( SQLGetDiagRec( htype, hndl, i,sqlstate,&sqlcode,buffer,SQL_MAX_MESSAGE_LENGTH + 1,&length ) == SQL_SUCCESS ) 
   {
             fprintf(stderr, "         SQLSTATE: %s\n", sqlstate ) ; 
             fprintf(stderr, "Native Error Code: %ld\n", (long int)sqlcode ) ; 
             fprintf(stderr, "%s \n", buffer ) ; 
            i++ ;
   }
  fprintf( stderr,">--------------------------------------------------\n" ) ; 
  }




























main()
{
   SQLHENV env;//Enviurnment handle
   
   SQLHDBC dbc;//db handle
   
   SQLHSTMT stmt;//statement handle
   
   SQLRETURN ret;

  SQLSMALLINT columns;
	
   SQLCHAR buf[ 5 ][ 64 ];

   int row = 0;

   SQLLEN indicator[ 5 ];

   int i;

 //  SQLINTEGER NumRecords;









SQLCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1] ;
SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1] ;
SQLINTEGER sqlcode ;
SQLSMALLINT length  ;
SQLINTEGER NumRecords;
      
  //SQLCHAR buff[ ]="insert into student (S_Id,S_Name,S_Add) values (104,'Satish Masal','Abegon')";


   SQLCHAR buff[ ]="select * from student";

  // SQLCHAR buff[ ]="delete from student where S_Id=102";


   SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);

   SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

   SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

   ret=SQLDriverConnect(dbc, NULL, "DSN=KomliAdServer_0;", SQL_NTS,
                    NULL, 0, NULL, SQL_DRIVER_COMPLETE);
   
    if (!SQL_SUCCEEDED(ret))
    {
          printf("\n\t An Error Occured During Connection To Database \n");
    }
    else
    {
          printf("\n\t Its ok, No Probleme In Connection=%d \n",ret);
    }
	

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    
    ret= SQLPrepare(stmt,buff,sizeof(buff));
    if (!SQL_SUCCEEDED(ret))
    {
          printf("\n\t An Error Occured During Prepare \n");
    }
    else
    {
          printf("\n\t Its ok, No Probleme In Prepare \n");
    }

    
    ret=SQLExecute(stmt);
    i=1;	
    if (!SQL_SUCCEEDED(ret))
    {
	  printf("\n\t An Error occured During Execute insert= %d\n",ret);
	 print_error((SQLSMALLINT)SQL_HANDLE_STMT,stmt, ret,__LINE__,__FILE__ );
	/*SQLGetDiagField(SQL_HANDLE_STMT, stmt, 0,SQL_DIAG_NUMBER, &NumRecords, SQL_IS_INTEGER,NULL);
	printf("Total Number of diagnostic records: %d\n",NumRecords); 



	while ( SQLGetDiagRec( SQL_HANDLE_STMT, stmt,i,sqlstate,&sqlcode,buffer,SQL_MAX_MESSAGE_LENGTH + 1,&length) == SQL_SUCCESS ) 
        {
		printf( " SQLSTATE: %sn", sqlstate ) ;
		printf( "Native Error Code: %ldn", sqlcode ) ;
		printf( "%s n", buffer ) ;
		i++ ;
	}*/

    }
    else
    {
    	  printf("\n\t Its ok, No Probleme \n");  
    } 
    


      SQLNumResultCols(stmt, &columns);

   for (i = 0; i < columns; i++) 
   {
      SQLBindCol( stmt, i + 1, SQL_C_CHAR,buf[ i ], sizeof( buf[ i ] ), &indicator[ i ] );
   }

   
   while (SQL_SUCCEEDED(SQLFetch(stmt))) 
   {
      for ( i = 0; i < columns; i ++ ) 
      {
         if (indicator[ i ] == SQL_NULL_DATA) 
	{
            printf("  Column %u : NULL\n", i);
        }
        else 
	{
            printf("  Column %u : %s\n", i, buf[ i ]);
        }
      }
  }


  /* ret=SQLRETURN SQLGetDiagRec(SQL_HANDLE_STMT,stmt,1,);
    if (!SQL_SUCCEEDED(ret))
    {
          printf("\n\t An Error occured During Execute insert= %d\n",ret);
    }
    else
    {
          printf("\n\t Its ok, No Probleme \n");
    }

*/

    
    
}

