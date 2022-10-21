#include <stdio.h>
#include <string.h>

#define MAX_PATH			1000
#define MAX_ENCRYPT_KEY		100
#define ERROR_NOERROR		0
#define ERROR_READERROR		1
#define ERROR_WRITEERROR	2

int RemoveUnwantedCharacters(char* szBuffer);

int main( int argc, char* argv[] ) 
{

	FILE*	fpInput;
	FILE*	fpOutput;
	char	szFileName[MAX_PATH+1];
	char	szFileName1[MAX_PATH+1];
	char	szEncryptionKey[MAX_ENCRYPT_KEY+1];
	int		nEncryptKeyLength;
	int		nByte;
	int     nCount;
	int     nError;
	long int	byte = 0;

	if( argc == 4 ){

		strcpy( szFileName1, argv[1] );
		strcpy( szFileName, argv[2] );

		if( strcmp( szFileName1, szFileName )==0 ){

			printf("\n\nError: Source file and destination file cannot be the same.\n\nType %s /? for usage.\n\n", argv[0]);
			return 1;

		}
	}

	else{
	
		printf( "\n\nSecuresoft Data Encryptor 1.0.0.0\n\nCreated by D3fault(d3fault.spk@doomed.com)\nSecuresoft Corporation Inc.\n\nProtected by Copyright law 2001\n\n\n" );
		printf( "USAGE:\n\nEncrypt: %s [Source file] [Destination file] [Encryption key]\n\nDecrypt: %s [Encrypted file] [Destination file] [Encryption key used to encrypt]\n\n", argv[0], argv[0] );
		return 1;
	}
	
	do
	{
		memset( szEncryptionKey, MAX_ENCRYPT_KEY+1, 0 );
		strcpy( szEncryptionKey, argv[3] );
		RemoveUnwantedCharacters( szEncryptionKey );
		nEncryptKeyLength = strlen( szEncryptionKey );

	}	
	while( nEncryptKeyLength == 0 );
	
	printf( "\n\n" );
	printf( "Using [%s] as key.\n\n",argv[3] );
	printf( "Working...\tPlease wait...\n" );
	printf( "\n" );
	
	fpInput = fopen( szFileName1, "rb" );
	if( fpInput == NULL )
	{
		printf( "Error: Unable to open %s for reading.\n\n", argv[1] );
		return 2;
	}

	fpOutput = fopen( szFileName, "wb" );
	if( fpOutput == NULL )
	{
		printf( "Error: Unable to open %s for writing.\n\n", szFileName );
		return 3;
	}
	nCount = 0;
	nError = ERROR_NOERROR;

	while( ( nByte = fgetc( fpInput ) ) != EOF )
	{
		if( fputc( nByte ^ szEncryptionKey[nCount], fpOutput ) == EOF )
		{
			nError = ERROR_WRITEERROR;
			break;
		}
		nCount++;

		byte++;

		if( nCount >= nEncryptKeyLength ) nCount = 0;
	}

	if( ! feof( fpInput ) ) nError = ERROR_READERROR;

	fclose( fpInput );
	fclose( fpOutput );

	switch( nError )
	{
		case ERROR_NOERROR:
			printf( "Success.\n\nWrote %d byte(s).\n", byte );
			break;
		case ERROR_READERROR:
			printf( "Error: unable to perform READ operation on file [%s]\n\n", argv[1] );
			break;
		case ERROR_WRITEERROR:
			printf( "Error: unable to perform WRITE operation on file [%s]\n\n", szFileName );
			break;
		default:
			printf( "Error: Unknown Error, please contact your support(d3fault.spk@doomed.com).\n\n" );
			break;
	}

	return 0; 
}


int RemoveUnwantedCharacters( char* szBuffer )
{
	while( *szBuffer != 0 )
	{
		if( *szBuffer == 0x0a || *szBuffer == 0x0d ) *szBuffer = 0;
		szBuffer++;
	}
	return 0;
}