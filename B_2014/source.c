//
//  source.c
//  TeraCoder2014
//
//  Created by kuroneko on 2014/12/19.
//  Copyright (c) 2014年 kuroneko. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * データセットの数を取得する
 * @return
 *	データセット数
 */
int getNumber( void );

/**
 * 学年の表示を行う
 * @param n
 *	入力値
 */
void grade( char *id );

/**
 * データ読み込み時のバッファ
 */
char buffer[1024];

int main( void ){
	int number = getNumber();
	while( number-- ){
		if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
			return EXIT_FAILURE;
		}
		grade( buffer );
	}
	return EXIT_SUCCESS;
}

int getNumber( void ){
	if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	return atoi( buffer );
}

void grade( char *id ){
	id[3] = '\0';
	int number = atoi( id + 1 );
	if( 11 <= number && number <= 14 ){
		printf( "B%d\n" , 15 - number );
	}
	else{
		puts( "ERROR" );
	}
	return;
}
