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
 * FizzBuzz の表示を行う
 * @param n
 *	入力値
 */
void fizzbuzz( int n );

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
		fizzbuzz( atoi( buffer ) );
	}
	return EXIT_SUCCESS;
}

int getNumber( void ){
	if( fgets( buffer , sizeof( buffer ) , stdin ) == NULL ){
		exit( EXIT_FAILURE );
	}
	return atoi( buffer );
}

void fizzbuzz( int n ){
	if( n % 3 == 0 || n % 5 == 0 ){
		if( n % 3 == 0 ){
			fputs( "Fizz" , stdout );
		}
		if( n % 5 == 0 ){
			fputs( "Buzz" , stdout );
		}
	}
	else{
		printf( "%d" , n );
	}
	fputc( '\n' , stdout );
	return;
}
