#include <stdio.h>
#include <string.h>

int main() {
  FILE * fp;
  char row[24];
  unsigned int i;

  /* Windows�n�̏ꍇ��"test.txt"�ɂ��� */
  fp = fopen( "./test.txt" , "r" );
  if( fp == NULL ) {
    printf( "�t�@�C���I�[�v���G���[\n" );
    return -1;
  }

  while( fgets( row , sizeof( row ) , fp ) != NULL ) {
    printf( "row=%s" , row );/* row�̖�����\n\0 */
    for( i=0;i<strlen( row );i++ ) {
      /* 1�o�C�g���\�� */
      printf( "row[%d]=0x%02x\n" , i , row[i] );
    }
  }

  fclose( fp );

  return 0;

}